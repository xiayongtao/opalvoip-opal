/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


using System;
using System.Runtime.InteropServices;

public class OpalStatusTransferCall : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal OpalStatusTransferCall(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(OpalStatusTransferCall obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~OpalStatusTransferCall() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          OPALPINVOKE.delete_OpalStatusTransferCall(swigCPtr);
        }
        swigCPtr = new HandleRef(null, IntPtr.Zero);
      }
      GC.SuppressFinalize(this);
    }
  }

  public string callToken {
    set {
      OPALPINVOKE.OpalStatusTransferCall_callToken_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusTransferCall_callToken_get(swigCPtr);
      return ret;
    } 
  }

  public string protocolCallId {
    set {
      OPALPINVOKE.OpalStatusTransferCall_protocolCallId_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusTransferCall_protocolCallId_get(swigCPtr);
      return ret;
    } 
  }

  public string result {
    set {
      OPALPINVOKE.OpalStatusTransferCall_result_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusTransferCall_result_get(swigCPtr);
      return ret;
    } 
  }

  public string info {
    set {
      OPALPINVOKE.OpalStatusTransferCall_info_set(swigCPtr, value);
    } 
    get {
      string ret = OPALPINVOKE.OpalStatusTransferCall_info_get(swigCPtr);
      return ret;
    } 
  }

  public OpalStatusTransferCall() : this(OPALPINVOKE.new_OpalStatusTransferCall(), true) {
  }

}
