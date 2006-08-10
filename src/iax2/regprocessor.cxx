#include <ptlib.h>
#include <ptclib/random.h>
#include <typeinfo>

#ifdef P_USE_PRAGMA
#pragma implementation "processor.h"
#endif

#include <iax2/causecode.h>
#include <iax2/frame.h>
#include <iax2/iax2con.h>
#include <iax2/iax2ep.h>
#include <iax2/iax2medstrm.h>
#include <iax2/ies.h>
#include <iax2/processor.h>
#include <iax2/regprocessor.h>
#include <iax2/sound.h>
#include <iax2/transmit.h>

#define new PNEW

IAX2RegProcessor::IAX2RegProcessor(
    IAX2EndPoint &ep, 
    const PString & inHost, 
    const PString & inUsername,
    const PString & inPassword,
    PINDEX inRegistrationRefreshTime
    )
  : IAX2Processor(ep), host(inHost), userName(inUsername), password(inPassword), 
    registrationRefreshTime(inRegistrationRefreshTime)
{
  registrationTimer.SetNotifier(PCREATE_NOTIFIER(OnDoRegistration));
  registrationState = registrationStart;
  
  PIPSocket::Address ip;
  if (!PIPSocket::GetHostAddress(host, ip))
     PTRACE(0, "Failed to lookup " << host);

  remote.SetRemoteAddress(ip);
  
  Activate();
  Resume();
}

IAX2RegProcessor::~IAX2RegProcessor()
{
}

void IAX2RegProcessor::PrintOn(ostream & strm) const
{
  strm << "In registration call with " << callToken  << endl
       << "  Call has been up for " << setprecision(0) << setw(8)
       << (PTimer::Tick() - callStartTick) << " milliseconds" << endl;
}

void IAX2RegProcessor::OnNoResponseTimeout()
{
  PWaitAndSignal m(stateMutex);
  
  if (registrationState == registrationHappening) {
    //retry registration when the refresh time occurs
    registrationState = registrationWait;
    registrationTimer = registrationRefreshTime;
    
    endpoint.OnRegistered(host, userName, TRUE);
  }
  
  if (registrationState == registrationUnregistering) {
    registrationState = registrationUnregistered;
    endpoint.OnUnregistered(host, userName, TRUE);
    Terminate();
  }
}

void IAX2RegProcessor::ProcessLists()
{
  PWaitAndSignal m(stateMutex);
  while(ProcessOneIncomingEthernetFrame());
  
  if (registrationState == registrationStart) {
    PTRACE(2, "starting registration cycle");
    ResetCall();
    
    IAX2FullFrameProtocol * f = new IAX2FullFrameProtocol(this, IAX2FullFrameProtocol::cmdRegReq,
      IAX2FullFrameProtocol::callIrrelevant);
    f->AppendIe(new IAX2IeUserName(userName));
    f->AppendIe(new IAX2IeRefresh((short)registrationRefreshTime));
    
    TransmitFrameToRemoteEndpoint(f);
    registrationState = registrationHappening;
    StartNoResponseTimer();    
  } else if (registrationState == registrationUnregisterStart) {    
    PTRACE(2, "starting registration release");
    ResetCall();
    
    IAX2FullFrameProtocol * f = new IAX2FullFrameProtocol(this, IAX2FullFrameProtocol::cmdRegRel,
      IAX2FullFrameProtocol::callIrrelevant);
    f->AppendIe(new IAX2IeUserName(userName));    
    
    TransmitFrameToRemoteEndpoint(f);
    registrationState = registrationUnregistering;
    StartNoResponseTimer();
  }  
}

void IAX2RegProcessor::ProcessNetworkFrame(IAX2MiniFrame * /*src*/)
{
  PTRACE(1, "unexpected Mini Frame");
}

void IAX2RegProcessor::ProcessFullFrame(IAX2FullFrame & fullFrame)
{
  switch(fullFrame.GetFrameType()) {
  case IAX2FullFrame::iax2ProtocolType:        
    PTRACE(3, "Build matching full frame    fullFrameProtocol");
    ProcessNetworkFrame(new IAX2FullFrameProtocol(fullFrame));
    break;
    
  default:
    PTRACE(3, "Build matching full frame, Type not expected");
  }
  
}

void IAX2RegProcessor::ProcessNetworkFrame(IAX2FullFrameProtocol * src)
{
  PTRACE(3, "ProcessNetworkFrame(IAX2FullFrameProtocol * src)");  
  src->CopyDataFromIeListTo(ieData);
  
  //check if the common method can process it?
  if (ProcessCommonNetworkFrame(src))
    return;
  
  if (registrationState == registrationHappening) {
    switch (src->GetSubClass()) {
    case IAX2FullFrameProtocol::cmdRegAuth:
      ProcessIaxCmdRegAuth(src);
      break;
    case IAX2FullFrameProtocol::cmdRegAck: 
      ProcessIaxCmdRegAck(src);  
      break;
    case IAX2FullFrameProtocol::cmdRegRej:
      ProcessIaxCmdRegRej(src);
      break;
    default:
      PTRACE(1, "Process Full Frame Protocol registering, Type not expected");
    }
  }
  
  if (registrationState == registrationUnregistering) {
    switch (src->GetSubClass()) {
    case IAX2FullFrameProtocol::cmdRegAuth: 
      ProcessIaxCmdUnRegAuth(src);  
      break;
    case IAX2FullFrameProtocol::cmdRegAck:
      ProcessIaxCmdUnRegAck(src);
      break;
    case IAX2FullFrameProtocol::cmdRegRej:
      ProcessIaxCmdUnRegRej(src);
      break;
    default:
      PTRACE(1, "Process Full Frame Protocol unregistering, Type not expected");
    }
  }
     
  delete src;
  
  
}

void IAX2RegProcessor::ProcessIaxCmdRegAuth(IAX2FullFrameProtocol * /*src*/)
{
  PTRACE(3, "ProcessIaxCmdRegAuth(IAX2FullFrameProtocol * src)");
  
  StopNoResponseTimer();
  
  IAX2FullFrameProtocol *f = new IAX2FullFrameProtocol(this, IAX2FullFrameProtocol::cmdRegReq, 
    IAX2FullFrameProtocol::callIrrelevant);

  f->AppendIe(new IAX2IeUserName(userName));
  Authenticate(f, password); 
  f->AppendIe(new IAX2IeRefresh((short)registrationRefreshTime));
  
  TransmitFrameToRemoteEndpoint(f);
  
  StartNoResponseTimer();
}

void IAX2RegProcessor::ProcessIaxCmdRegAck(IAX2FullFrameProtocol * src)
{
  PINDEX refreshTime;
  
  PTRACE(3, "ProcessIaxCmdRegAuth(IAX2FullFrameProtocol * src)");
  
  StopNoResponseTimer();
  refreshTime = ieData.refresh;
  if (refreshTime < 10) //prevent very low refresh times
    refreshTime = 10;
  
  //convert time to milliseconds and give it a random refresh time
  //in order to not overload the server.  The time is slightly less than
  //the time requested by the server this is to allow time for the packets
  //to travel there.
  int minRefreshTime = (int)refreshTime * 900;
  int randomPart = (int)(regRandom.Number() % refreshTime) * 50;
  PTRACE(4, "Requested max refresh time " << refreshTime << " Chosen refresh time "
    << (minRefreshTime + randomPart));
  registrationTimer = PTimeInterval(minRefreshTime + randomPart);
  
  endpoint.OnRegistered(host, userName, FALSE);
  registrationState = registrationWait;
  
  SendAckFrame(src);
}

void IAX2RegProcessor::ProcessIaxCmdRegRej(IAX2FullFrameProtocol * src)
{
  PTRACE(3, "ProcessIaxCmdRej(IAX2FullFrameProtocol * src)");
  
  StopNoResponseTimer();
  endpoint.OnRegistered(host, userName, TRUE);
  /* This is an optimistic approach - retrying the registration
     once the timer event is triggered. even though our password
     failed.*/
  registrationState = registrationWait;
  registrationTimer = registrationRefreshTime * 1000; //convert to milliseconds
  
  SendAckFrame(src);
}

void IAX2RegProcessor::ProcessIaxCmdUnRegAuth(IAX2FullFrameProtocol * /*src*/)
{
  PTRACE(3, "ProcessIaxCmdUnRegAuth(IAX2FullFrameProtocol * src)");
  
  StopNoResponseTimer();
  
  IAX2FullFrameProtocol *f = new IAX2FullFrameProtocol(this, IAX2FullFrameProtocol::cmdRegRel,
    IAX2FullFrameProtocol::callIrrelevant);

  f->AppendIe(new IAX2IeUserName(userName));  
  Authenticate(f, password);
  TransmitFrameToRemoteEndpoint(f);
  
  StartNoResponseTimer();
}

void IAX2RegProcessor::ProcessIaxCmdUnRegAck(IAX2FullFrameProtocol * src)
{
  PTRACE(3, "ProcessIaxCmdUnRegAck(IAX2FullFrameProtocol * src)");
  
  StopNoResponseTimer();
  SendAckFrame(src);
  
  registrationState = registrationUnregistered;
  endpoint.OnUnregistered(host, userName, FALSE);
  Terminate();
}

void IAX2RegProcessor::ProcessIaxCmdUnRegRej(IAX2FullFrameProtocol * /*src*/)
{
  PTRACE(3, "ProcessIaxCmdRej(IAX2FullFrameProtocol * src)");
  
  //if the server didn't let us unregister then lets
  //just ditch it.
  StopNoResponseTimer();  
  registrationState = registrationUnregistered;
  endpoint.OnUnregistered(host, userName, TRUE);
  Terminate();
}

void IAX2RegProcessor::OnDoRegistration(PTimer &, INT)
{
  //this is run in a different thread
  PWaitAndSignal m(stateMutex);
  PTRACE(3, "Registration timer called");
  if (registrationState == registrationWait) {
    registrationState = registrationStart;
    Activate();
  }
}

void IAX2RegProcessor::Unregister()
{
  PTRACE(2, "Unregistration called");
  {
    PWaitAndSignal m(stateMutex);
    if (registrationState != registrationUnregistered) {
      registrationState = registrationUnregisterStart;     
      Activate();
    }
  }
  
  //this will block until the registration is released or there is
  //a timeout.  This is not optimal because the thread calling this
  //method will be suspended.  In the future there will be another thread
  //just closing down various processors to prevent this problem.
  WaitForTermination();
}

void IAX2RegProcessor::ResetCall()
{
  //to prevent creating a new regprocessor instance for each
  //registration time.  We just emulate a new call by resetting
  //our source call number and the sequence numbers. 
  endpoint.ReleaseSrcCallNumber(this);
  
  int callno = endpoint.NextSrcCallNumber(this);
  if (callno != -1)
    remote.SetSourceCallNumber(callno);
    
  sequence.ZeroAllValues();
  callStartTick = PTimer::Tick();
}
