/*
 * h224.h
 *
 * H.224 PDU implementation for the OpenH323 Project.
 *
 * Copyright (c) 2006 Network for Educational Technology, ETH Zurich.
 * Written by Hannes Friederich.
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
 * Contributor(s): ______________________________________.
 *
 * $Revision$
 * $Author$
 * $Date$
 */

#ifndef __OPAL_H224_H
#define __OPAL_H224_H

#ifdef P_USE_PRAGMA
#pragma interface
#endif

#ifndef _PTLIB_H
#include <ptlib.h>
#endif

#include <opal/buildopts.h>

#include <opal/mediatype.h>
#include <h224/q922.h>

#define H224_HEADER_SIZE 6

#define H224_BROADCAST 0x0000

///////////////////////////////////////////////////////////////////////////////
//
//  declare a media type for H.224
//

class OpalH224MediaType : OpalRTPAVPMediaType 
{
  public:
    OpalH224MediaType();

#if OPAL_SIP
    SDPMediaDescription * CreateSDPMediaDescription(const OpalTransportAddress & localAddress);
#endif
};

///////////////////////////////////////////////////////////////////////////////

class H224_Frame : public Q922_Frame
{
  PCLASSINFO(H224_Frame, Q922_Frame);
	
public:
	
  H224_Frame(PINDEX clientDataSize = 254);
  ~H224_Frame();
	
  PBoolean IsHighPriority() const { return (GetLowOrderAddressOctet() == 0x71); }
  void SetHighPriority(PBoolean flag);
	
  WORD GetDestinationTerminalAddress() const;
  void SetDestinationTerminalAddress(WORD destination);
	
  WORD GetSourceTerminalAddress() const;
  void SetSourceTerminalAddress(WORD source);
	
  // Only standard client IDs are supported at the moment
  BYTE GetClientID() const;
  void SetClientID(BYTE clientID);
	
  PBoolean GetBS() const;
  void SetBS(PBoolean bs);
	
  PBoolean GetES() const;
  void SetES(PBoolean es);
	
  PBoolean GetC1() const;
  void SetC1(PBoolean c1);
	
  PBoolean GetC0() const;
  void SetC0(PBoolean c0);
	
  BYTE GetSegmentNumber() const;
  void SetSegmentNumber(BYTE segmentNumber);
	
  BYTE *GetClientDataPtr() const { return (GetInformationFieldPtr() + H224_HEADER_SIZE); }
	
  PINDEX GetClientDataSize() const { return (GetInformationFieldSize() - H224_HEADER_SIZE); }
  void SetClientDataSize(PINDEX size) { SetInformationFieldSize(size + H224_HEADER_SIZE); }
	
  PBoolean Decode(const BYTE *data, PINDEX size);
};

#endif // __OPAL_H224_H

