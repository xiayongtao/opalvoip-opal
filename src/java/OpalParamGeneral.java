/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.opalvoip.opal;

public class OpalParamGeneral {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected OpalParamGeneral(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(OpalParamGeneral obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        OPALJNI.delete_OpalParamGeneral(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setAudioRecordDevice(String value) {
    OPALJNI.OpalParamGeneral_audioRecordDevice_set(swigCPtr, this, value);
  }

  public String getAudioRecordDevice() {
    return OPALJNI.OpalParamGeneral_audioRecordDevice_get(swigCPtr, this);
  }

  public void setAudioPlayerDevice(String value) {
    OPALJNI.OpalParamGeneral_audioPlayerDevice_set(swigCPtr, this, value);
  }

  public String getAudioPlayerDevice() {
    return OPALJNI.OpalParamGeneral_audioPlayerDevice_get(swigCPtr, this);
  }

  public void setVideoInputDevice(String value) {
    OPALJNI.OpalParamGeneral_videoInputDevice_set(swigCPtr, this, value);
  }

  public String getVideoInputDevice() {
    return OPALJNI.OpalParamGeneral_videoInputDevice_get(swigCPtr, this);
  }

  public void setVideoOutputDevice(String value) {
    OPALJNI.OpalParamGeneral_videoOutputDevice_set(swigCPtr, this, value);
  }

  public String getVideoOutputDevice() {
    return OPALJNI.OpalParamGeneral_videoOutputDevice_get(swigCPtr, this);
  }

  public void setVideoPreviewDevice(String value) {
    OPALJNI.OpalParamGeneral_videoPreviewDevice_set(swigCPtr, this, value);
  }

  public String getVideoPreviewDevice() {
    return OPALJNI.OpalParamGeneral_videoPreviewDevice_get(swigCPtr, this);
  }

  public void setMediaOrder(String value) {
    OPALJNI.OpalParamGeneral_mediaOrder_set(swigCPtr, this, value);
  }

  public String getMediaOrder() {
    return OPALJNI.OpalParamGeneral_mediaOrder_get(swigCPtr, this);
  }

  public void setMediaMask(String value) {
    OPALJNI.OpalParamGeneral_mediaMask_set(swigCPtr, this, value);
  }

  public String getMediaMask() {
    return OPALJNI.OpalParamGeneral_mediaMask_get(swigCPtr, this);
  }

  public void setAutoRxMedia(String value) {
    OPALJNI.OpalParamGeneral_autoRxMedia_set(swigCPtr, this, value);
  }

  public String getAutoRxMedia() {
    return OPALJNI.OpalParamGeneral_autoRxMedia_get(swigCPtr, this);
  }

  public void setAutoTxMedia(String value) {
    OPALJNI.OpalParamGeneral_autoTxMedia_set(swigCPtr, this, value);
  }

  public String getAutoTxMedia() {
    return OPALJNI.OpalParamGeneral_autoTxMedia_get(swigCPtr, this);
  }

  public void setNatMethod(String value) {
    OPALJNI.OpalParamGeneral_natMethod_set(swigCPtr, this, value);
  }

  public String getNatMethod() {
    return OPALJNI.OpalParamGeneral_natMethod_get(swigCPtr, this);
  }

  public void setNatServer(String value) {
    OPALJNI.OpalParamGeneral_natServer_set(swigCPtr, this, value);
  }

  public String getNatServer() {
    return OPALJNI.OpalParamGeneral_natServer_get(swigCPtr, this);
  }

  public void setTcpPortBase(long value) {
    OPALJNI.OpalParamGeneral_tcpPortBase_set(swigCPtr, this, value);
  }

  public long getTcpPortBase() {
    return OPALJNI.OpalParamGeneral_tcpPortBase_get(swigCPtr, this);
  }

  public void setTcpPortMax(long value) {
    OPALJNI.OpalParamGeneral_tcpPortMax_set(swigCPtr, this, value);
  }

  public long getTcpPortMax() {
    return OPALJNI.OpalParamGeneral_tcpPortMax_get(swigCPtr, this);
  }

  public void setUdpPortBase(long value) {
    OPALJNI.OpalParamGeneral_udpPortBase_set(swigCPtr, this, value);
  }

  public long getUdpPortBase() {
    return OPALJNI.OpalParamGeneral_udpPortBase_get(swigCPtr, this);
  }

  public void setUdpPortMax(long value) {
    OPALJNI.OpalParamGeneral_udpPortMax_set(swigCPtr, this, value);
  }

  public long getUdpPortMax() {
    return OPALJNI.OpalParamGeneral_udpPortMax_get(swigCPtr, this);
  }

  public void setRtpPortBase(long value) {
    OPALJNI.OpalParamGeneral_rtpPortBase_set(swigCPtr, this, value);
  }

  public long getRtpPortBase() {
    return OPALJNI.OpalParamGeneral_rtpPortBase_get(swigCPtr, this);
  }

  public void setRtpPortMax(long value) {
    OPALJNI.OpalParamGeneral_rtpPortMax_set(swigCPtr, this, value);
  }

  public long getRtpPortMax() {
    return OPALJNI.OpalParamGeneral_rtpPortMax_get(swigCPtr, this);
  }

  public void setRtpTypeOfService(long value) {
    OPALJNI.OpalParamGeneral_rtpTypeOfService_set(swigCPtr, this, value);
  }

  public long getRtpTypeOfService() {
    return OPALJNI.OpalParamGeneral_rtpTypeOfService_get(swigCPtr, this);
  }

  public void setRtpMaxPayloadSize(long value) {
    OPALJNI.OpalParamGeneral_rtpMaxPayloadSize_set(swigCPtr, this, value);
  }

  public long getRtpMaxPayloadSize() {
    return OPALJNI.OpalParamGeneral_rtpMaxPayloadSize_get(swigCPtr, this);
  }

  public void setMinAudioJitter(long value) {
    OPALJNI.OpalParamGeneral_minAudioJitter_set(swigCPtr, this, value);
  }

  public long getMinAudioJitter() {
    return OPALJNI.OpalParamGeneral_minAudioJitter_get(swigCPtr, this);
  }

  public void setMaxAudioJitter(long value) {
    OPALJNI.OpalParamGeneral_maxAudioJitter_set(swigCPtr, this, value);
  }

  public long getMaxAudioJitter() {
    return OPALJNI.OpalParamGeneral_maxAudioJitter_get(swigCPtr, this);
  }

  public void setSilenceDetectMode(OpalSilenceDetectMode value) {
    OPALJNI.OpalParamGeneral_silenceDetectMode_set(swigCPtr, this, value.swigValue());
  }

  public OpalSilenceDetectMode getSilenceDetectMode() {
    return OpalSilenceDetectMode.swigToEnum(OPALJNI.OpalParamGeneral_silenceDetectMode_get(swigCPtr, this));
  }

  public void setSilenceThreshold(long value) {
    OPALJNI.OpalParamGeneral_silenceThreshold_set(swigCPtr, this, value);
  }

  public long getSilenceThreshold() {
    return OPALJNI.OpalParamGeneral_silenceThreshold_get(swigCPtr, this);
  }

  public void setSignalDeadband(long value) {
    OPALJNI.OpalParamGeneral_signalDeadband_set(swigCPtr, this, value);
  }

  public long getSignalDeadband() {
    return OPALJNI.OpalParamGeneral_signalDeadband_get(swigCPtr, this);
  }

  public void setSilenceDeadband(long value) {
    OPALJNI.OpalParamGeneral_silenceDeadband_set(swigCPtr, this, value);
  }

  public long getSilenceDeadband() {
    return OPALJNI.OpalParamGeneral_silenceDeadband_get(swigCPtr, this);
  }

  public void setSilenceAdaptPeriod(long value) {
    OPALJNI.OpalParamGeneral_silenceAdaptPeriod_set(swigCPtr, this, value);
  }

  public long getSilenceAdaptPeriod() {
    return OPALJNI.OpalParamGeneral_silenceAdaptPeriod_get(swigCPtr, this);
  }

  public void setEchoCancellation(OpalEchoCancelMode value) {
    OPALJNI.OpalParamGeneral_echoCancellation_set(swigCPtr, this, value.swigValue());
  }

  public OpalEchoCancelMode getEchoCancellation() {
    return OpalEchoCancelMode.swigToEnum(OPALJNI.OpalParamGeneral_echoCancellation_get(swigCPtr, this));
  }

  public void setAudioBuffers(long value) {
    OPALJNI.OpalParamGeneral_audioBuffers_set(swigCPtr, this, value);
  }

  public long getAudioBuffers() {
    return OPALJNI.OpalParamGeneral_audioBuffers_get(swigCPtr, this);
  }

  public void setMediaReadData(SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int value) {
    OPALJNI.OpalParamGeneral_mediaReadData_set(swigCPtr, this, SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int getMediaReadData() {
    long cPtr = OPALJNI.OpalParamGeneral_mediaReadData_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int(cPtr, false);
  }

  public void setMediaWriteData(SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int value) {
    OPALJNI.OpalParamGeneral_mediaWriteData_set(swigCPtr, this, SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int getMediaWriteData() {
    long cPtr = OPALJNI.OpalParamGeneral_mediaWriteData_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_q_const__char_p_q_const__char_p_q_const__char_p_void_p_void_int__int(cPtr, false);
  }

  public void setMediaDataHeader(OpalMediaDataType value) {
    OPALJNI.OpalParamGeneral_mediaDataHeader_set(swigCPtr, this, value.swigValue());
  }

  public OpalMediaDataType getMediaDataHeader() {
    return OpalMediaDataType.swigToEnum(OPALJNI.OpalParamGeneral_mediaDataHeader_get(swigCPtr, this));
  }

  public void setMessageAvailable(SWIGTYPE_p_f_p_q_const__OpalMessage__int value) {
    OPALJNI.OpalParamGeneral_messageAvailable_set(swigCPtr, this, SWIGTYPE_p_f_p_q_const__OpalMessage__int.getCPtr(value));
  }

  public SWIGTYPE_p_f_p_q_const__OpalMessage__int getMessageAvailable() {
    long cPtr = OPALJNI.OpalParamGeneral_messageAvailable_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_f_p_q_const__OpalMessage__int(cPtr, false);
  }

  public void setMediaOptions(String value) {
    OPALJNI.OpalParamGeneral_mediaOptions_set(swigCPtr, this, value);
  }

  public String getMediaOptions() {
    return OPALJNI.OpalParamGeneral_mediaOptions_get(swigCPtr, this);
  }

  public void setAudioBufferTime(long value) {
    OPALJNI.OpalParamGeneral_audioBufferTime_set(swigCPtr, this, value);
  }

  public long getAudioBufferTime() {
    return OPALJNI.OpalParamGeneral_audioBufferTime_get(swigCPtr, this);
  }

  public void setManualAlerting(long value) {
    OPALJNI.OpalParamGeneral_manualAlerting_set(swigCPtr, this, value);
  }

  public long getManualAlerting() {
    return OPALJNI.OpalParamGeneral_manualAlerting_get(swigCPtr, this);
  }

  public void setMediaTiming(OpalMediaTiming value) {
    OPALJNI.OpalParamGeneral_mediaTiming_set(swigCPtr, this, value.swigValue());
  }

  public OpalMediaTiming getMediaTiming() {
    return OpalMediaTiming.swigToEnum(OPALJNI.OpalParamGeneral_mediaTiming_get(swigCPtr, this));
  }

  public void setVideoSourceTiming(OpalMediaTiming value) {
    OPALJNI.OpalParamGeneral_videoSourceTiming_set(swigCPtr, this, value.swigValue());
  }

  public OpalMediaTiming getVideoSourceTiming() {
    return OpalMediaTiming.swigToEnum(OPALJNI.OpalParamGeneral_videoSourceTiming_get(swigCPtr, this));
  }

  public void setPcssMediaOverride(String value) {
    OPALJNI.OpalParamGeneral_pcssMediaOverride_set(swigCPtr, this, value);
  }

  public String getPcssMediaOverride() {
    return OPALJNI.OpalParamGeneral_pcssMediaOverride_get(swigCPtr, this);
  }

  public OpalParamGeneral() {
    this(OPALJNI.new_OpalParamGeneral(), true);
  }

}
