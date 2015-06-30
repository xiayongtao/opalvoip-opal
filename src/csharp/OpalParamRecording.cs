//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.5
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------


public class OpalParamRecording : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalParamRecording(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(OpalParamRecording obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalParamRecording() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalParamRecording(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public string callToken {
    set {
      OPALPINVOKE.OpalParamRecording_callToken_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_callToken_get(swigCPtr);
      return ret;
    } 
  }

  public string file {
    set {
      OPALPINVOKE.OpalParamRecording_file_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_file_get(swigCPtr);
      return ret;
    } 
  }

  public uint channels {
    set {
      OPALPINVOKE.OpalParamRecording_channels_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_channels_get(swigCPtr);
      return ret;
    } 
  }

  public string audioFormat {
    set {
      OPALPINVOKE.OpalParamRecording_audioFormat_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_audioFormat_get(swigCPtr);
      return ret;
    } 
  }

  public string videoFormat {
    set {
      OPALPINVOKE.OpalParamRecording_videoFormat_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalParamRecording_videoFormat_get(swigCPtr);
      return ret;
    } 
  }

  public uint videoWidth {
    set {
      OPALPINVOKE.OpalParamRecording_videoWidth_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_videoWidth_get(swigCPtr);
      return ret;
    } 
  }

  public uint videoHeight {
    set {
      OPALPINVOKE.OpalParamRecording_videoHeight_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_videoHeight_get(swigCPtr);
      return ret;
    } 
  }

  public uint videoRate {
    set {
      OPALPINVOKE.OpalParamRecording_videoRate_set(swigCPtr, value);
    } 
    get {
      uint ret = OPALPINVOKE.OpalParamRecording_videoRate_get(swigCPtr);
      return ret;
    } 
  }

  public OpalVideoRecordMixMode videoMixing {
    set {
      OPALPINVOKE.OpalParamRecording_videoMixing_set(swigCPtr, (int)value);
    } 
    get {
      OpalVideoRecordMixMode ret = (OpalVideoRecordMixMode)OPALPINVOKE.OpalParamRecording_videoMixing_get(swigCPtr);
      return ret;
    } 
  }

  public OpalParamRecording() : this(OPALPINVOKE.new_OpalParamRecording(), true) {
  }

}
