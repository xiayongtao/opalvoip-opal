/*
 * h323t120.cxx
 *
 * H.323 T.120 logical channel establishment
 *
 * Open H323 Library
 *
 * Copyright (c) 1998-2000 Equivalence Pty. Ltd.
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
 * The Original Code is Open H323 Library.
 *
 * The Initial Developer of the Original Code is Equivalence Pty. Ltd.
 *
 * Contributor(s): ______________________________________.
 *
 * $Log: h323t120.cxx,v $
 * Revision 1.2003  2001/08/13 05:10:40  robertj
 * Updates from OpenH323 v1.6.0 release.
 *
 * Revision 2.1  2001/08/01 05:05:49  robertj
 * Major changes to H.323 capabilities, uses OpalMediaFormat for base name.
 *
 * Revision 2.0  2001/07/27 15:48:25  robertj
 * Conversion of OpenH323 to Open Phone Abstraction Library (OPAL)
 *
 * Revision 1.3  2001/08/06 03:08:57  robertj
 * Fission of h323.h to h323ep.h & h323con.h, h323.h now just includes files.
 *
 * Revision 1.2  2001/07/18 02:27:24  robertj
 * Fixed GNU warning.
 *
 * Revision 1.1  2001/07/17 04:44:32  robertj
 * Partial implementation of T.120 and T.38 logical channels.
 *
 */

#include <ptlib.h>

#ifdef __GNUC__
#pragma implementation "h323t120.h"
#endif

#include <t120/h323t120.h>
#include <h323/h323ep.h>
#include <h323/h323con.h>
#include <h323/transaddr.h>
#include <t120/t120proto.h>
#include <t120/x224.h>
#include <asn/h245.h>


#define new PNEW


/////////////////////////////////////////////////////////////////////////////

H323_T120Capability::H323_T120Capability()
  : H323DataCapability(OpalT120Protocol::MediaFormat)
{
}


PObject * H323_T120Capability::Clone() const
{
  return new H323_T120Capability(*this);
}


unsigned H323_T120Capability::GetSubType() const
{
  return H245_DataApplicationCapability_application::e_t120;
}


PString H323_T120Capability::GetFormatName() const
{
  return "T.120";
}


H323Channel * H323_T120Capability::CreateChannel(H323Connection & connection,
                                                 H323Channel::Directions direction,
                                                 unsigned,
                                const H245_H2250LogicalChannelParameters *) const
{
  return new H323_T120Channel(connection, *this, direction);
}


BOOL H323_T120Capability::OnSendingPDU(H245_DataApplicationCapability & cap) const
{
  cap.m_maxBitRate = 825000;
  cap.m_application.SetTag(H245_DataApplicationCapability_application::e_t120);
  H245_DataProtocolCapability & proto = cap.m_application;
  proto.SetTag(H245_DataProtocolCapability::e_separateLANStack);
  return TRUE;
}


BOOL H323_T120Capability::OnReceivedPDU(const H245_DataApplicationCapability & cap)
{
  if (cap.m_application.GetTag() != H245_DataApplicationCapability_application::e_t120)
    return FALSE;

  const H245_DataProtocolCapability & dataCap = cap.m_application;

  return dataCap.GetTag() == H245_DataProtocolCapability::e_separateLANStack;
}


/////////////////////////////////////////////////////////////////////////////

H323_T120Channel::H323_T120Channel(H323Connection & connection,
                                   const H323Capability & capability,
                                   Directions direction)
  : H323DataChannel(connection, capability, direction)
{
  t120handler = NULL;
  PTRACE(3, "H323T120\tCreated logical channel for T.120");
}


void H323_T120Channel::Receive()
{
  PTRACE(2, "H323T120\tReceive thread started.");

  if (t120handler == NULL)
    PTRACE(1, "H323T120\tNo protocol handler, aborting thread.");
  else if (listener == NULL)
    PTRACE(1, "H323T120\tNo listener, aborting thread.");
  else if ((transport = listener->Accept(30000)) == NULL)  // 30 second wait for connect back
    PTRACE(1, "H323T120\tAccept failed, aborting thread.");
  else
    t120handler->Answer(*transport);

  connection.CloseLogicalChannelNumber(number);

  PTRACE(2, "H323T120\tReceive thread ended");
}


void H323_T120Channel::Transmit()
{
  PTRACE(2, "H323T120\tTransmit thread started.");

  if (t120handler == NULL)
    PTRACE(1, "H323T120\tNo protocol handler, aborting thread.");
  else if (transport == NULL)
    PTRACE(1, "H323T120\tNo transport, aborting thread.");
  else
    t120handler->Originate(*transport);

  connection.CloseLogicalChannelNumber(number);

  PTRACE(2, "H323T120\tTransmit thread ended");
}


BOOL H323_T120Channel::OnSendingPDU(H245_OpenLogicalChannel & open) const
{
  if (!H323DataChannel::OnSendingPDU(open))
    return FALSE;

  if (!((H323_T120Channel*)this)->CreateListener()) {
    PTRACE(1, "H323T120\tCould not create listener");
    return FALSE;
  }

  PTRACE(3, "H323T120\tOnSendingPDU");

  open.IncludeOptionalField(H245_OpenLogicalChannel::e_separateStack);
  open.m_separateStack.IncludeOptionalField(H245_NetworkAccessParameters::e_distribution);
  open.m_separateStack.m_distribution.SetTag(H245_NetworkAccessParameters_distribution::e_unicast);
  open.m_separateStack.m_networkAddress.SetTag(H245_NetworkAccessParameters_networkAddress::e_localAreaAddress);
  H245_TransportAddress & h245addr = open.m_separateStack.m_networkAddress;
  H323TransportAddress h323addr = listener->GetLocalAddress(connection.GetControlChannel().GetLocalAddress());
  return h323addr.SetPDU(h245addr);
}


void H323_T120Channel::OnSendOpenAck(const H245_OpenLogicalChannel & /*open*/,
                                     H245_OpenLogicalChannelAck & ack) const
{
  PTRACE(3, "H323T120\tOnSendOpenAck");

  if (listener != NULL || transport != NULL) {
    ack.IncludeOptionalField(H245_OpenLogicalChannelAck::e_separateStack);
    ack.m_separateStack.IncludeOptionalField(H245_NetworkAccessParameters::e_distribution);
    ack.m_separateStack.m_distribution.SetTag(H245_NetworkAccessParameters_distribution::e_unicast);
    ack.m_separateStack.m_networkAddress.SetTag(H245_NetworkAccessParameters_networkAddress::e_localAreaAddress);
    H245_TransportAddress & h245addr = ack.m_separateStack.m_networkAddress;

    H323TransportAddress h323addr;
    if (listener != NULL)
      h323addr = listener->GetLocalAddress(connection.GetControlChannel().GetLocalAddress());
    else
      h323addr = transport->GetLocalAddress();
    h323addr.SetPDU(h245addr);
  }
}


BOOL H323_T120Channel::OnReceivedPDU(const H245_OpenLogicalChannel & open,
                                     unsigned & errorCode)
{
  number = H323ChannelNumber(open.m_forwardLogicalChannelNumber, TRUE);

  PTRACE(3, "H323T120\tOnReceivedPDU for channel: " << number);

  H323EndPoint & endpoint = connection.GetEndPoint();

  t120handler = endpoint.CreateT120ProtocolHandler();
  if (t120handler == NULL) {
    PTRACE(1, "H323T120\tCould not create protocol handler");
    errorCode = H245_OpenLogicalChannelReject_cause::e_dataTypeNotAvailable;
    return FALSE;
  }

  BOOL listen = connection.HadAnsweredCall();

  H323TransportAddress address;
  if (open.HasOptionalField(H245_OpenLogicalChannel::e_separateStack) &&
    open.m_separateStack.m_networkAddress.GetTag() == H245_NetworkAccessParameters_networkAddress::e_localAreaAddress) {
    address = (const H245_TransportAddress &)open.m_separateStack.m_networkAddress;
    if (open.m_separateStack.HasOptionalField(H245_NetworkAccessParameters::e_t120SetupProcedure))
      listen = open.m_separateStack.m_t120SetupProcedure.GetTag() ==
                            H245_NetworkAccessParameters_t120SetupProcedure::e_waitForCall;
  }

  if (listen) {
    if (!address)
      listener = address.CreateCompatibleListener(endpoint);
    else {
      // No address specified, assume same IP as the transport and use default port
      PIPSocket::Address ip;
      WORD port;
      if (!connection.GetControlChannel().GetLocalAddress().GetIpAndPort(ip, port)) {
        PTRACE(1, "H323T120\tOnly IPv4 supported");
        errorCode = H245_OpenLogicalChannelReject_cause::e_separateStackEstablishmentFailed;
        return FALSE;
      }
      listener = new OpalListenerTCP(endpoint, ip, OpalT120Protocol::DefaultTcpPort, FALSE);
    }

    if (!listener->Open(NULL)) {
      PTRACE(1, "H323T120\tCould not open listener");
      errorCode = H245_OpenLogicalChannelReject_cause::e_separateStackEstablishmentFailed;
      return FALSE;
    }

    PTRACE(2, "H323T120\tCreated listener on " << listener->GetLocalAddress());
  }
  else {
    if (address.IsEmpty()) {
      // No address specified, assume same IP as the transport and use default port
      PIPSocket::Address ip;
      WORD port;
      if (!connection.GetControlChannel().GetRemoteAddress().GetIpAndPort(ip, port)) {
        PTRACE(1, "H323T120\tOnly IPv4 supported");
        errorCode = H245_OpenLogicalChannelReject_cause::e_separateStackEstablishmentFailed;
        return FALSE;
      }
      address = OpalTransportAddress(ip, OpalT120Protocol::DefaultTcpPort);
    }

    transport = address.CreateTransport(endpoint);
    if (transport == NULL) {
      PTRACE(1, "H323T120\tCould not create transport");
      errorCode = H245_OpenLogicalChannelReject_cause::e_separateStackEstablishmentFailed;
      return FALSE;
    }

    if (!transport->SetRemoteAddress(address)) {
      PTRACE(1, "H323T120\tCould not set transport remote address");
      errorCode = H245_OpenLogicalChannelReject_cause::e_separateStackEstablishmentFailed;
      return FALSE;
    }

    PTRACE(2, "H323T120\tCreated transport from "
           << transport->GetLocalAddress() << " to " << transport->GetRemoteAddress());
  }

  return TRUE;
}


BOOL H323_T120Channel::OnReceivedAckPDU(const H245_OpenLogicalChannelAck & /*ack*/)
{
  PTRACE(3, "H323T120\tOnReceivedAckPDU");

  return TRUE;
}

    
/////////////////////////////////////////////////////////////////////////////
