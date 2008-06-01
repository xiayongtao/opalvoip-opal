//
// h4609.cxx
//
// Code automatically generated by asnparse.
//

#ifdef P_USE_PRAGMA
#pragma implementation "h4609.h"
#endif

#include <ptlib.h>
#include "h460/h4609.h"

#define new PNEW


#if ! H323_DISABLE_H4609



//
// EstimatedEnd2EndDelay
//

H4609_EstimatedEnd2EndDelay::H4609_EstimatedEnd2EndDelay(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Integer(tag, tagClass)
{
  SetConstraints(PASN_Object::FixedConstraint, 0, 4294967295U);
}


H4609_EstimatedEnd2EndDelay & H4609_EstimatedEnd2EndDelay::operator=(int v)
{
  SetValue(v);
  return *this;
}


H4609_EstimatedEnd2EndDelay & H4609_EstimatedEnd2EndDelay::operator=(unsigned v)
{
  SetValue(v);
  return *this;
}


PObject * H4609_EstimatedEnd2EndDelay::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_EstimatedEnd2EndDelay::Class()), PInvalidCast);
#endif
  return new H4609_EstimatedEnd2EndDelay(*this);
}


//
// CalculatedJitter
//

H4609_CalculatedJitter::H4609_CalculatedJitter(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Integer(tag, tagClass)
{
  SetConstraints(PASN_Object::FixedConstraint, 0, 4294967295U);
}


H4609_CalculatedJitter & H4609_CalculatedJitter::operator=(int v)
{
  SetValue(v);
  return *this;
}


H4609_CalculatedJitter & H4609_CalculatedJitter::operator=(unsigned v)
{
  SetValue(v);
  return *this;
}


PObject * H4609_CalculatedJitter::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_CalculatedJitter::Class()), PInvalidCast);
#endif
  return new H4609_CalculatedJitter(*this);
}


//
// Extension
//

H4609_Extension::H4609_Extension(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 1, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H4609_Extension::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+14) << "extensionId = " << setprecision(indent) << m_extensionId << '\n';
  if (HasOptionalField(e_extensionContent))
    strm << setw(indent+19) << "extensionContent = " << setprecision(indent) << m_extensionContent << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_Extension::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_Extension), PInvalidCast);
#endif
  const H4609_Extension & other = (const H4609_Extension &)obj;

  Comparison result;

  if ((result = m_extensionId.Compare(other.m_extensionId)) != EqualTo)
    return result;
  if ((result = m_extensionContent.Compare(other.m_extensionContent)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_Extension::GetDataLength() const
{
  PINDEX length = 0;
  length += m_extensionId.GetObjectLength();
  if (HasOptionalField(e_extensionContent))
    length += m_extensionContent.GetObjectLength();
  return length;
}


PBoolean H4609_Extension::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_extensionId.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_extensionContent) && !m_extensionContent.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_Extension::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_extensionId.Encode(strm);
  if (HasOptionalField(e_extensionContent))
    m_extensionContent.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_Extension::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_Extension::Class()), PInvalidCast);
#endif
  return new H4609_Extension(*this);
}



#ifndef PASN_NOPRINTON
const static PASN_Names Names_H4609_QosMonitoringReportData[]={
      {"periodic",0}
     ,{"final",1}
     ,{"interGK",2}
};
#endif
//
// QosMonitoringReportData
//

H4609_QosMonitoringReportData::H4609_QosMonitoringReportData(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Choice(tag, tagClass, 3, TRUE
#ifndef PASN_NOPRINTON
    ,(const PASN_Names *)Names_H4609_QosMonitoringReportData,3
#endif
)
{
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4609_QosMonitoringReportData::operator H4609_PeriodicQoSMonReport &() const
#else
H4609_QosMonitoringReportData::operator H4609_PeriodicQoSMonReport &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4609_PeriodicQoSMonReport), PInvalidCast);
#endif
  return *(H4609_PeriodicQoSMonReport *)choice;
}


H4609_QosMonitoringReportData::operator const H4609_PeriodicQoSMonReport &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4609_PeriodicQoSMonReport), PInvalidCast);
#endif
  return *(H4609_PeriodicQoSMonReport *)choice;
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4609_QosMonitoringReportData::operator H4609_FinalQosMonReport &() const
#else
H4609_QosMonitoringReportData::operator H4609_FinalQosMonReport &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4609_FinalQosMonReport), PInvalidCast);
#endif
  return *(H4609_FinalQosMonReport *)choice;
}


H4609_QosMonitoringReportData::operator const H4609_FinalQosMonReport &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4609_FinalQosMonReport), PInvalidCast);
#endif
  return *(H4609_FinalQosMonReport *)choice;
}


#if defined(__GNUC__) && __GNUC__ <= 2 && __GNUC_MINOR__ < 9
H4609_QosMonitoringReportData::operator H4609_InterGKQosMonReport &() const
#else
H4609_QosMonitoringReportData::operator H4609_InterGKQosMonReport &()
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4609_InterGKQosMonReport), PInvalidCast);
#endif
  return *(H4609_InterGKQosMonReport *)choice;
}


H4609_QosMonitoringReportData::operator const H4609_InterGKQosMonReport &() const
#endif
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(PAssertNULL(choice), H4609_InterGKQosMonReport), PInvalidCast);
#endif
  return *(H4609_InterGKQosMonReport *)choice;
}


PBoolean H4609_QosMonitoringReportData::CreateObject()
{
  switch (tag) {
    case e_periodic :
      choice = new H4609_PeriodicQoSMonReport();
      return TRUE;
    case e_final :
      choice = new H4609_FinalQosMonReport();
      return TRUE;
    case e_interGK :
      choice = new H4609_InterGKQosMonReport();
      return TRUE;
  }

  choice = NULL;
  return FALSE;
}


PObject * H4609_QosMonitoringReportData::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_QosMonitoringReportData::Class()), PInvalidCast);
#endif
  return new H4609_QosMonitoringReportData(*this);
}


//
// RTCPMeasures_mediaSenderMeasures
//

H4609_RTCPMeasures_mediaSenderMeasures::H4609_RTCPMeasures_mediaSenderMeasures(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 2, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H4609_RTCPMeasures_mediaSenderMeasures::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  if (HasOptionalField(e_worstEstimatedEnd2EndDelay))
    strm << setw(indent+29) << "worstEstimatedEnd2EndDelay = " << setprecision(indent) << m_worstEstimatedEnd2EndDelay << '\n';
  if (HasOptionalField(e_meanEstimatedEnd2EndDelay))
    strm << setw(indent+28) << "meanEstimatedEnd2EndDelay = " << setprecision(indent) << m_meanEstimatedEnd2EndDelay << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_RTCPMeasures_mediaSenderMeasures::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_RTCPMeasures_mediaSenderMeasures), PInvalidCast);
#endif
  const H4609_RTCPMeasures_mediaSenderMeasures & other = (const H4609_RTCPMeasures_mediaSenderMeasures &)obj;

  Comparison result;

  if ((result = m_worstEstimatedEnd2EndDelay.Compare(other.m_worstEstimatedEnd2EndDelay)) != EqualTo)
    return result;
  if ((result = m_meanEstimatedEnd2EndDelay.Compare(other.m_meanEstimatedEnd2EndDelay)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_RTCPMeasures_mediaSenderMeasures::GetDataLength() const
{
  PINDEX length = 0;
  if (HasOptionalField(e_worstEstimatedEnd2EndDelay))
    length += m_worstEstimatedEnd2EndDelay.GetObjectLength();
  if (HasOptionalField(e_meanEstimatedEnd2EndDelay))
    length += m_meanEstimatedEnd2EndDelay.GetObjectLength();
  return length;
}


PBoolean H4609_RTCPMeasures_mediaSenderMeasures::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (HasOptionalField(e_worstEstimatedEnd2EndDelay) && !m_worstEstimatedEnd2EndDelay.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_meanEstimatedEnd2EndDelay) && !m_meanEstimatedEnd2EndDelay.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_RTCPMeasures_mediaSenderMeasures::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  if (HasOptionalField(e_worstEstimatedEnd2EndDelay))
    m_worstEstimatedEnd2EndDelay.Encode(strm);
  if (HasOptionalField(e_meanEstimatedEnd2EndDelay))
    m_meanEstimatedEnd2EndDelay.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_RTCPMeasures_mediaSenderMeasures::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_RTCPMeasures_mediaSenderMeasures::Class()), PInvalidCast);
#endif
  return new H4609_RTCPMeasures_mediaSenderMeasures(*this);
}


//
// RTCPMeasures_mediaReceiverMeasures
//

H4609_RTCPMeasures_mediaReceiverMeasures::H4609_RTCPMeasures_mediaReceiverMeasures(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 6, TRUE, 0)
{
  m_cumulativeNumberOfPacketsLost.SetConstraints(PASN_Object::FixedConstraint, 0, 4294967295U);
  m_packetLostRate.SetConstraints(PASN_Object::FixedConstraint, 0, 65535);
  m_fractionLostRate.SetConstraints(PASN_Object::FixedConstraint, 0, 65535);
}


#ifndef PASN_NOPRINTON
void H4609_RTCPMeasures_mediaReceiverMeasures::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  if (HasOptionalField(e_cumulativeNumberOfPacketsLost))
    strm << setw(indent+32) << "cumulativeNumberOfPacketsLost = " << setprecision(indent) << m_cumulativeNumberOfPacketsLost << '\n';
  if (HasOptionalField(e_packetLostRate))
    strm << setw(indent+17) << "packetLostRate = " << setprecision(indent) << m_packetLostRate << '\n';
  if (HasOptionalField(e_worstJitter))
    strm << setw(indent+14) << "worstJitter = " << setprecision(indent) << m_worstJitter << '\n';
  if (HasOptionalField(e_estimatedThroughput))
    strm << setw(indent+22) << "estimatedThroughput = " << setprecision(indent) << m_estimatedThroughput << '\n';
  if (HasOptionalField(e_fractionLostRate))
    strm << setw(indent+19) << "fractionLostRate = " << setprecision(indent) << m_fractionLostRate << '\n';
  if (HasOptionalField(e_meanJitter))
    strm << setw(indent+13) << "meanJitter = " << setprecision(indent) << m_meanJitter << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_RTCPMeasures_mediaReceiverMeasures::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_RTCPMeasures_mediaReceiverMeasures), PInvalidCast);
#endif
  const H4609_RTCPMeasures_mediaReceiverMeasures & other = (const H4609_RTCPMeasures_mediaReceiverMeasures &)obj;

  Comparison result;

  if ((result = m_cumulativeNumberOfPacketsLost.Compare(other.m_cumulativeNumberOfPacketsLost)) != EqualTo)
    return result;
  if ((result = m_packetLostRate.Compare(other.m_packetLostRate)) != EqualTo)
    return result;
  if ((result = m_worstJitter.Compare(other.m_worstJitter)) != EqualTo)
    return result;
  if ((result = m_estimatedThroughput.Compare(other.m_estimatedThroughput)) != EqualTo)
    return result;
  if ((result = m_fractionLostRate.Compare(other.m_fractionLostRate)) != EqualTo)
    return result;
  if ((result = m_meanJitter.Compare(other.m_meanJitter)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_RTCPMeasures_mediaReceiverMeasures::GetDataLength() const
{
  PINDEX length = 0;
  if (HasOptionalField(e_cumulativeNumberOfPacketsLost))
    length += m_cumulativeNumberOfPacketsLost.GetObjectLength();
  if (HasOptionalField(e_packetLostRate))
    length += m_packetLostRate.GetObjectLength();
  if (HasOptionalField(e_worstJitter))
    length += m_worstJitter.GetObjectLength();
  if (HasOptionalField(e_estimatedThroughput))
    length += m_estimatedThroughput.GetObjectLength();
  if (HasOptionalField(e_fractionLostRate))
    length += m_fractionLostRate.GetObjectLength();
  if (HasOptionalField(e_meanJitter))
    length += m_meanJitter.GetObjectLength();
  return length;
}


PBoolean H4609_RTCPMeasures_mediaReceiverMeasures::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (HasOptionalField(e_cumulativeNumberOfPacketsLost) && !m_cumulativeNumberOfPacketsLost.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_packetLostRate) && !m_packetLostRate.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_worstJitter) && !m_worstJitter.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_estimatedThroughput) && !m_estimatedThroughput.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_fractionLostRate) && !m_fractionLostRate.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_meanJitter) && !m_meanJitter.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_RTCPMeasures_mediaReceiverMeasures::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  if (HasOptionalField(e_cumulativeNumberOfPacketsLost))
    m_cumulativeNumberOfPacketsLost.Encode(strm);
  if (HasOptionalField(e_packetLostRate))
    m_packetLostRate.Encode(strm);
  if (HasOptionalField(e_worstJitter))
    m_worstJitter.Encode(strm);
  if (HasOptionalField(e_estimatedThroughput))
    m_estimatedThroughput.Encode(strm);
  if (HasOptionalField(e_fractionLostRate))
    m_fractionLostRate.Encode(strm);
  if (HasOptionalField(e_meanJitter))
    m_meanJitter.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_RTCPMeasures_mediaReceiverMeasures::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_RTCPMeasures_mediaReceiverMeasures::Class()), PInvalidCast);
#endif
  return new H4609_RTCPMeasures_mediaReceiverMeasures(*this);
}


//
// ArrayOf_Extension
//

H4609_ArrayOf_Extension::H4609_ArrayOf_Extension(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Array(tag, tagClass)
{
}


PASN_Object * H4609_ArrayOf_Extension::CreateObject() const
{
  return new H4609_Extension;
}


H4609_Extension & H4609_ArrayOf_Extension::operator[](PINDEX i) const
{
  return (H4609_Extension &)array[i];
}


PObject * H4609_ArrayOf_Extension::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_ArrayOf_Extension::Class()), PInvalidCast);
#endif
  return new H4609_ArrayOf_Extension(*this);
}


//
// ArrayOf_RTCPMeasures
//

H4609_ArrayOf_RTCPMeasures::H4609_ArrayOf_RTCPMeasures(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Array(tag, tagClass)
{
}


PASN_Object * H4609_ArrayOf_RTCPMeasures::CreateObject() const
{
  return new H4609_RTCPMeasures;
}


H4609_RTCPMeasures & H4609_ArrayOf_RTCPMeasures::operator[](PINDEX i) const
{
  return (H4609_RTCPMeasures &)array[i];
}


PObject * H4609_ArrayOf_RTCPMeasures::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_ArrayOf_RTCPMeasures::Class()), PInvalidCast);
#endif
  return new H4609_ArrayOf_RTCPMeasures(*this);
}


//
// ArrayOf_PerCallQoSReport
//

H4609_ArrayOf_PerCallQoSReport::H4609_ArrayOf_PerCallQoSReport(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Array(tag, tagClass)
{
}


PASN_Object * H4609_ArrayOf_PerCallQoSReport::CreateObject() const
{
  return new H4609_PerCallQoSReport;
}


H4609_PerCallQoSReport & H4609_ArrayOf_PerCallQoSReport::operator[](PINDEX i) const
{
  return (H4609_PerCallQoSReport &)array[i];
}


PObject * H4609_ArrayOf_PerCallQoSReport::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_ArrayOf_PerCallQoSReport::Class()), PInvalidCast);
#endif
  return new H4609_ArrayOf_PerCallQoSReport(*this);
}


//
// RTCPMeasures
//

H4609_RTCPMeasures::H4609_RTCPMeasures(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 4, TRUE, 0)
{
  m_sessionId.SetConstraints(PASN_Object::FixedConstraint, 1, 255);
}


#ifndef PASN_NOPRINTON
void H4609_RTCPMeasures::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+13) << "rtpAddress = " << setprecision(indent) << m_rtpAddress << '\n';
  strm << setw(indent+14) << "rtcpAddress = " << setprecision(indent) << m_rtcpAddress << '\n';
  strm << setw(indent+12) << "sessionId = " << setprecision(indent) << m_sessionId << '\n';
  if (HasOptionalField(e_nonStandardData))
    strm << setw(indent+18) << "nonStandardData = " << setprecision(indent) << m_nonStandardData << '\n';
  if (HasOptionalField(e_mediaSenderMeasures))
    strm << setw(indent+22) << "mediaSenderMeasures = " << setprecision(indent) << m_mediaSenderMeasures << '\n';
  if (HasOptionalField(e_mediaReceiverMeasures))
    strm << setw(indent+24) << "mediaReceiverMeasures = " << setprecision(indent) << m_mediaReceiverMeasures << '\n';
  if (HasOptionalField(e_extensions))
    strm << setw(indent+13) << "extensions = " << setprecision(indent) << m_extensions << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_RTCPMeasures::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_RTCPMeasures), PInvalidCast);
#endif
  const H4609_RTCPMeasures & other = (const H4609_RTCPMeasures &)obj;

  Comparison result;

  if ((result = m_rtpAddress.Compare(other.m_rtpAddress)) != EqualTo)
    return result;
  if ((result = m_rtcpAddress.Compare(other.m_rtcpAddress)) != EqualTo)
    return result;
  if ((result = m_sessionId.Compare(other.m_sessionId)) != EqualTo)
    return result;
  if ((result = m_nonStandardData.Compare(other.m_nonStandardData)) != EqualTo)
    return result;
  if ((result = m_mediaSenderMeasures.Compare(other.m_mediaSenderMeasures)) != EqualTo)
    return result;
  if ((result = m_mediaReceiverMeasures.Compare(other.m_mediaReceiverMeasures)) != EqualTo)
    return result;
  if ((result = m_extensions.Compare(other.m_extensions)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_RTCPMeasures::GetDataLength() const
{
  PINDEX length = 0;
  length += m_rtpAddress.GetObjectLength();
  length += m_rtcpAddress.GetObjectLength();
  length += m_sessionId.GetObjectLength();
  if (HasOptionalField(e_nonStandardData))
    length += m_nonStandardData.GetObjectLength();
  if (HasOptionalField(e_mediaSenderMeasures))
    length += m_mediaSenderMeasures.GetObjectLength();
  if (HasOptionalField(e_mediaReceiverMeasures))
    length += m_mediaReceiverMeasures.GetObjectLength();
  if (HasOptionalField(e_extensions))
    length += m_extensions.GetObjectLength();
  return length;
}


PBoolean H4609_RTCPMeasures::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_rtpAddress.Decode(strm))
    return FALSE;
  if (!m_rtcpAddress.Decode(strm))
    return FALSE;
  if (!m_sessionId.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_nonStandardData) && !m_nonStandardData.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_mediaSenderMeasures) && !m_mediaSenderMeasures.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_mediaReceiverMeasures) && !m_mediaReceiverMeasures.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_extensions) && !m_extensions.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_RTCPMeasures::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_rtpAddress.Encode(strm);
  m_rtcpAddress.Encode(strm);
  m_sessionId.Encode(strm);
  if (HasOptionalField(e_nonStandardData))
    m_nonStandardData.Encode(strm);
  if (HasOptionalField(e_mediaSenderMeasures))
    m_mediaSenderMeasures.Encode(strm);
  if (HasOptionalField(e_mediaReceiverMeasures))
    m_mediaReceiverMeasures.Encode(strm);
  if (HasOptionalField(e_extensions))
    m_extensions.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_RTCPMeasures::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_RTCPMeasures::Class()), PInvalidCast);
#endif
  return new H4609_RTCPMeasures(*this);
}


//
// PerCallQoSReport
//

H4609_PerCallQoSReport::H4609_PerCallQoSReport(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 3, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H4609_PerCallQoSReport::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  if (HasOptionalField(e_nonStandardData))
    strm << setw(indent+18) << "nonStandardData = " << setprecision(indent) << m_nonStandardData << '\n';
  strm << setw(indent+21) << "callReferenceValue = " << setprecision(indent) << m_callReferenceValue << '\n';
  strm << setw(indent+15) << "conferenceID = " << setprecision(indent) << m_conferenceID << '\n';
  strm << setw(indent+17) << "callIdentifier = " << setprecision(indent) << m_callIdentifier << '\n';
  if (HasOptionalField(e_mediaChannelsQoS))
    strm << setw(indent+19) << "mediaChannelsQoS = " << setprecision(indent) << m_mediaChannelsQoS << '\n';
  if (HasOptionalField(e_extensions))
    strm << setw(indent+13) << "extensions = " << setprecision(indent) << m_extensions << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_PerCallQoSReport::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_PerCallQoSReport), PInvalidCast);
#endif
  const H4609_PerCallQoSReport & other = (const H4609_PerCallQoSReport &)obj;

  Comparison result;

  if ((result = m_nonStandardData.Compare(other.m_nonStandardData)) != EqualTo)
    return result;
  if ((result = m_callReferenceValue.Compare(other.m_callReferenceValue)) != EqualTo)
    return result;
  if ((result = m_conferenceID.Compare(other.m_conferenceID)) != EqualTo)
    return result;
  if ((result = m_callIdentifier.Compare(other.m_callIdentifier)) != EqualTo)
    return result;
  if ((result = m_mediaChannelsQoS.Compare(other.m_mediaChannelsQoS)) != EqualTo)
    return result;
  if ((result = m_extensions.Compare(other.m_extensions)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_PerCallQoSReport::GetDataLength() const
{
  PINDEX length = 0;
  if (HasOptionalField(e_nonStandardData))
    length += m_nonStandardData.GetObjectLength();
  length += m_callReferenceValue.GetObjectLength();
  length += m_conferenceID.GetObjectLength();
  length += m_callIdentifier.GetObjectLength();
  if (HasOptionalField(e_mediaChannelsQoS))
    length += m_mediaChannelsQoS.GetObjectLength();
  if (HasOptionalField(e_extensions))
    length += m_extensions.GetObjectLength();
  return length;
}


PBoolean H4609_PerCallQoSReport::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (HasOptionalField(e_nonStandardData) && !m_nonStandardData.Decode(strm))
    return FALSE;
  if (!m_callReferenceValue.Decode(strm))
    return FALSE;
  if (!m_conferenceID.Decode(strm))
    return FALSE;
  if (!m_callIdentifier.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_mediaChannelsQoS) && !m_mediaChannelsQoS.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_extensions) && !m_extensions.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_PerCallQoSReport::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  if (HasOptionalField(e_nonStandardData))
    m_nonStandardData.Encode(strm);
  m_callReferenceValue.Encode(strm);
  m_conferenceID.Encode(strm);
  m_callIdentifier.Encode(strm);
  if (HasOptionalField(e_mediaChannelsQoS))
    m_mediaChannelsQoS.Encode(strm);
  if (HasOptionalField(e_extensions))
    m_extensions.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_PerCallQoSReport::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_PerCallQoSReport::Class()), PInvalidCast);
#endif
  return new H4609_PerCallQoSReport(*this);
}


//
// PeriodicQoSMonReport
//

H4609_PeriodicQoSMonReport::H4609_PeriodicQoSMonReport(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 1, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H4609_PeriodicQoSMonReport::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+14) << "perCallInfo = " << setprecision(indent) << m_perCallInfo << '\n';
  if (HasOptionalField(e_extensions))
    strm << setw(indent+13) << "extensions = " << setprecision(indent) << m_extensions << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_PeriodicQoSMonReport::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_PeriodicQoSMonReport), PInvalidCast);
#endif
  const H4609_PeriodicQoSMonReport & other = (const H4609_PeriodicQoSMonReport &)obj;

  Comparison result;

  if ((result = m_perCallInfo.Compare(other.m_perCallInfo)) != EqualTo)
    return result;
  if ((result = m_extensions.Compare(other.m_extensions)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_PeriodicQoSMonReport::GetDataLength() const
{
  PINDEX length = 0;
  length += m_perCallInfo.GetObjectLength();
  if (HasOptionalField(e_extensions))
    length += m_extensions.GetObjectLength();
  return length;
}


PBoolean H4609_PeriodicQoSMonReport::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_perCallInfo.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_extensions) && !m_extensions.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_PeriodicQoSMonReport::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_perCallInfo.Encode(strm);
  if (HasOptionalField(e_extensions))
    m_extensions.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_PeriodicQoSMonReport::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_PeriodicQoSMonReport::Class()), PInvalidCast);
#endif
  return new H4609_PeriodicQoSMonReport(*this);
}


//
// FinalQosMonReport
//

H4609_FinalQosMonReport::H4609_FinalQosMonReport(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 2, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H4609_FinalQosMonReport::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+12) << "mediaInfo = " << setprecision(indent) << m_mediaInfo << '\n';
  if (HasOptionalField(e_nonStandardData))
    strm << setw(indent+18) << "nonStandardData = " << setprecision(indent) << m_nonStandardData << '\n';
  if (HasOptionalField(e_extensions))
    strm << setw(indent+13) << "extensions = " << setprecision(indent) << m_extensions << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_FinalQosMonReport::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_FinalQosMonReport), PInvalidCast);
#endif
  const H4609_FinalQosMonReport & other = (const H4609_FinalQosMonReport &)obj;

  Comparison result;

  if ((result = m_mediaInfo.Compare(other.m_mediaInfo)) != EqualTo)
    return result;
  if ((result = m_nonStandardData.Compare(other.m_nonStandardData)) != EqualTo)
    return result;
  if ((result = m_extensions.Compare(other.m_extensions)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_FinalQosMonReport::GetDataLength() const
{
  PINDEX length = 0;
  length += m_mediaInfo.GetObjectLength();
  if (HasOptionalField(e_nonStandardData))
    length += m_nonStandardData.GetObjectLength();
  if (HasOptionalField(e_extensions))
    length += m_extensions.GetObjectLength();
  return length;
}


PBoolean H4609_FinalQosMonReport::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_mediaInfo.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_nonStandardData) && !m_nonStandardData.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_extensions) && !m_extensions.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_FinalQosMonReport::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_mediaInfo.Encode(strm);
  if (HasOptionalField(e_nonStandardData))
    m_nonStandardData.Encode(strm);
  if (HasOptionalField(e_extensions))
    m_extensions.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_FinalQosMonReport::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_FinalQosMonReport::Class()), PInvalidCast);
#endif
  return new H4609_FinalQosMonReport(*this);
}


//
// InterGKQosMonReport
//

H4609_InterGKQosMonReport::H4609_InterGKQosMonReport(unsigned tag, PASN_Object::TagClass tagClass)
  : PASN_Sequence(tag, tagClass, 2, TRUE, 0)
{
}


#ifndef PASN_NOPRINTON
void H4609_InterGKQosMonReport::PrintOn(ostream & strm) const
{
  int indent = strm.precision() + 2;
  strm << "{\n";
  strm << setw(indent+12) << "mediaInfo = " << setprecision(indent) << m_mediaInfo << '\n';
  if (HasOptionalField(e_nonStandardData))
    strm << setw(indent+18) << "nonStandardData = " << setprecision(indent) << m_nonStandardData << '\n';
  if (HasOptionalField(e_extensions))
    strm << setw(indent+13) << "extensions = " << setprecision(indent) << m_extensions << '\n';
  strm << setw(indent-1) << setprecision(indent-2) << "}";
}
#endif


PObject::Comparison H4609_InterGKQosMonReport::Compare(const PObject & obj) const
{
#ifndef PASN_LEANANDMEAN
  PAssert(PIsDescendant(&obj, H4609_InterGKQosMonReport), PInvalidCast);
#endif
  const H4609_InterGKQosMonReport & other = (const H4609_InterGKQosMonReport &)obj;

  Comparison result;

  if ((result = m_mediaInfo.Compare(other.m_mediaInfo)) != EqualTo)
    return result;
  if ((result = m_nonStandardData.Compare(other.m_nonStandardData)) != EqualTo)
    return result;
  if ((result = m_extensions.Compare(other.m_extensions)) != EqualTo)
    return result;

  return PASN_Sequence::Compare(other);
}


PINDEX H4609_InterGKQosMonReport::GetDataLength() const
{
  PINDEX length = 0;
  length += m_mediaInfo.GetObjectLength();
  if (HasOptionalField(e_nonStandardData))
    length += m_nonStandardData.GetObjectLength();
  if (HasOptionalField(e_extensions))
    length += m_extensions.GetObjectLength();
  return length;
}


PBoolean H4609_InterGKQosMonReport::Decode(PASN_Stream & strm)
{
  if (!PreambleDecode(strm))
    return FALSE;

  if (!m_mediaInfo.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_nonStandardData) && !m_nonStandardData.Decode(strm))
    return FALSE;
  if (HasOptionalField(e_extensions) && !m_extensions.Decode(strm))
    return FALSE;

  return UnknownExtensionsDecode(strm);
}


void H4609_InterGKQosMonReport::Encode(PASN_Stream & strm) const
{
  PreambleEncode(strm);

  m_mediaInfo.Encode(strm);
  if (HasOptionalField(e_nonStandardData))
    m_nonStandardData.Encode(strm);
  if (HasOptionalField(e_extensions))
    m_extensions.Encode(strm);

  UnknownExtensionsEncode(strm);
}


PObject * H4609_InterGKQosMonReport::Clone() const
{
#ifndef PASN_LEANANDMEAN
  PAssert(IsClass(H4609_InterGKQosMonReport::Class()), PInvalidCast);
#endif
  return new H4609_InterGKQosMonReport(*this);
}


#endif // if ! H323_DISABLE_H4609


// End of h4609.cxx
