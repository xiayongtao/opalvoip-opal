/*
 * sipep.cxx
 *
 * Session Initiation Protocol endpoint.
 *
 * Open Phone Abstraction Library (OPAL)
 *
 * Copyright (c) 2000 Equivalence Pty. Ltd.
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is Open Phone Abstraction Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log: sipep.cxx,v $
 * Revision 1.2005  2002/04/09 08:04:01  robertj
 * Fixed typo in previous patch!
 *
 * Revision 2.3  2002/04/09 07:18:33  robertj
 * Fixed the default return address for PDU requests not attached to connection.
 *
 * Revision 2.2  2002/04/05 10:42:04  robertj
 * Major changes to support transactions (UDP timeouts and retries).
 *
 * Revision 2.1  2002/02/01 04:53:01  robertj
 * Added (very primitive!) SIP support.
 *
 */

#include <ptlib.h>

#ifdef __GNUC__
#pragma implementation "sipep.h"
#endif

#include <sip/sipep.h>

#include <sip/sippdu.h>
#include <sip/sipcon.h>

#include <opal/manager.h>


#define new PNEW


////////////////////////////////////////////////////////////////////////////

SIPEndPoint::SIPEndPoint(OpalManager & mgr)
  : OpalEndPoint(mgr, "sip", CanTerminateCall),
    registrationID(OpalGloballyUniqueID().AsString()),
    registrationName(PProcess::Current().GetUserName()),
    retryTimeoutMin(500),     // 0.5 seconds
    retryTimeoutMax(0, 4),    // 4 seconds
    nonInviteTimeout(0, 16),  // 16 seconds
    pduCleanUpTimeout(0, 5),  // 5 seconds
    inviteTimeout(0, 32),     // 32 seconds
    ackTimeout(0, 32)         // 32 seconds
{
  defaultSignalPort = 5060;
  mimeForm = FALSE;
  maxRetries = 10;
  lastSentCSeq = 0;

  PTRACE(3, "SIP\tCreated endpoint.");
}


SIPEndPoint::~SIPEndPoint()
{
  // Shut down the listeners as soon as possible to avoid race conditions
  listeners.RemoveAll();

  PTRACE(3, "SIP\tDeleted endpoint.");
}


void SIPEndPoint::NewIncomingConnection(OpalTransport * transport)
{
  PTRACE_IF(2, transport->IsReliable(), "SIP\tListening thread started.");

  transport->SetBufferSize(SIP_PDU::MaxSize);

  do {
    HandlePDU(*transport);
  } while (transport->IsOpen() && transport->IsReliable());

  PTRACE_IF(2, transport->IsReliable(), "SIP\tListening thread finished.");
}


void SIPEndPoint::HandlePDU(OpalTransport & transport)
{
  // create a SIP_PDU structure, then get it to read and process PDU
  SIP_PDU * pdu = new SIP_PDU;

  PTRACE(4, "SIP\tWaiting for PDU on " << transport);
  if (pdu->Read(transport)) {
    if (!transport.IsReliable()) {
      // Calculate default return address
      if (pdu->GetMethod() != SIP_PDU::NumMethods) {
        PString via = pdu->GetMIME().GetContact();
        transport.SetRemoteAddress(via.Mid(via.FindLast(' ')));
      }
    }
    if (!OnReceivedPDU(transport, pdu))
      delete pdu;
  }
  else if (transport.good()) {
    PTRACE(1, "SIP\tMalformed request received on " << transport);
    SIP_PDU response(*pdu, SIP_PDU::Failure_BadRequest);
    response.Write(transport);
    delete pdu;
  }
}


BOOL SIPEndPoint::SetUpConnection(OpalCall & call,
                                  const PString & remoteParty,
                                  void * userData)
{
  if (remoteParty.Find("sip:") != 0)
    return FALSE;

  PStringStream callID;
  OpalGloballyUniqueID id;
  callID << id << '@' << PIPSocket::GetHostName();
  SIPConnection * connection = CreateConnection(call, callID, userData, NULL, NULL);
  if (connection == NULL)
    return FALSE;

  connection->Lock();
  AddNewConnection(connection);
  connection->InitiateCall(remoteParty);
  connection->Unlock();

  return TRUE;
}


BOOL SIPEndPoint::IsAcceptedAddress(const SIPURL & /*toAddr*/)
{
  return TRUE;
}


SIPConnection * SIPEndPoint::CreateConnection(OpalCall & call,
                                              const PString & token,
                                              void * /*userData*/,
                                              OpalTransport * transport,
                                              SIP_PDU * /*invite*/)
{
  return new SIPConnection(call, *this, token, transport);
}


void SIPEndPoint::AddNewConnection(SIPConnection * conn)
{
  PWaitAndSignal m(inUseFlag);
  connectionsActive.SetAt(conn->GetToken(), conn);
}


BOOL SIPEndPoint::OnReceivedPDU(OpalTransport & transport, SIP_PDU * pdu)
{
  SIPConnection * connection = GetSIPConnectionWithLock(pdu->GetMIME().GetCallID());
  if (connection != NULL) {
    connection->QueuePDU(pdu);
    connection->Unlock();
    return TRUE;
  }

  // An INVITE is a special case
  switch (pdu->GetMethod()) {
    case SIP_PDU::Method_INVITE :
      return OnReceivedINVITE(transport, pdu);

    case SIP_PDU::Method_REGISTER :
      {
        SIP_PDU response(*pdu, SIP_PDU::Failure_MethodNotAllowed);
        response.GetMIME().SetAt("Allow", "INVITE");
        response.Write(transport);
      }
      break;

    default :
      {
        SIP_PDU response(*pdu, SIP_PDU::Failure_TransactionDoesNotExist);
        response.Write(transport);
      }
  }

  return FALSE;
}


BOOL SIPEndPoint::OnReceivedINVITE(OpalTransport & transport, SIP_PDU * request)
{
  // send a response just in case this takes a while
  SIP_PDU trying(*request, SIP_PDU::Information_Trying);
  trying.Write(transport);

  SIPMIMEInfo & mime = request->GetMIME();

  // parse the incoming To field, and check if we accept incoming calls for this address
  SIPURL toAddr(mime.GetTo());
  if (!IsAcceptedAddress(toAddr)) {
    PTRACE(1, "SIP\tIncoming INVITE from " << request->GetURI() << " for unknown address " << toAddr);
    SIP_PDU response(*request, SIP_PDU::Failure_NotFound);
    response.Write(transport);
    return FALSE;
  }

  // ask the endpoint for a connection
  SIPConnection * connection = CreateConnection(*GetManager().CreateCall(),
                                                mime.GetCallID(), NULL, &transport, request);
  if (connection == NULL) {
    PTRACE(2, "SIP\tFailed to create SIPConnection for INVITE from " << request->GetURI() << " for " << toAddr);
    SIP_PDU response(*request, SIP_PDU::Failure_NotFound);
    response.Write(transport);
    return FALSE;
  }

  // add the connection to the endpoint list
  AddNewConnection(connection);

  // Get the connection to handle the rest of the INVITE
  connection->QueuePDU(request);
  return TRUE;
}


static BOOL WriteREGISTER(OpalTransport & transport, PObject * param)
{
  SIPEndPoint & endpoint = *(SIPEndPoint *)param;

  SIPTransaction request(endpoint, transport);
  SIPURL name(endpoint.GetRegistrationName(),
              transport.GetLocalAddress(),
              endpoint.GetDefaultSignalPort());
  SIPURL contact(name.GetUserName(),
                 transport.GetLocalAddress(),
                 endpoint.GetDefaultSignalPort());
  request.BuildREGISTER(name, contact);

  return request.Start();
}


BOOL SIPEndPoint::Register(const PString & server)
{
  if (listeners.IsEmpty())
    return FALSE;

  OpalTransportAddress address(server, defaultSignalPort, OpalTransportAddress::UdpPrefix);

  OpalTransport * transport = address.CreateTransport(*this, OpalTransportAddress::NoBinding);
  transport->ConnectTo(address);

  transport->WriteConnect(WriteREGISTER, this);

  SIP_PDU response;
  transport->SetReadTimeout(15000);
  if (!response.Read(*transport)) {
    delete transport;
    return FALSE;
  }

  transport->SetReadTimeout(PMaxTimeInterval);
  transport->EndConnect(transport->GetLocalAddress());

  PTRACE(2, "SIP\tSelecting reply from " << *transport);

  while (response.GetStatusCode() < SIP_PDU::Successful_OK) {
    if (!response.Read(*transport))
      break;
  }

  delete transport;
  return response.GetStatusCode() == SIP_PDU::Successful_OK;
}


// End of file ////////////////////////////////////////////////////////////////
