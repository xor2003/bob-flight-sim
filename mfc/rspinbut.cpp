/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "rspinbut.h"

/////////////////////////////////////////////////////////////////////////////
// CRSpinBut

IMPLEMENT_DYNCREATE(CRSpinBut, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CRSpinBut properties

OLE_COLOR CRSpinBut::GetForeColor()
{
	OLE_COLOR result;
	GetProperty(DISPID_FORECOLOR, VT_I4, (void*)&result);
	return result;
}

void CRSpinBut::SetForeColor(OLE_COLOR propVal)
{
	SetProperty(DISPID_FORECOLOR, VT_I4, propVal);
}

long CRSpinBut::GetRepeatDelay()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void CRSpinBut::SetRepeatDelay(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

long CRSpinBut::GetIndex()
{
	long result;
	GetProperty(0x2, VT_I4, (void*)&result);
	return result;
}

void CRSpinBut::SetIndex(long propVal)
{
	SetProperty(0x2, VT_I4, propVal);
}

long CRSpinBut::GetFontNum()
{
	long result;
	GetProperty(0x3, VT_I4, (void*)&result);
	return result;
}

void CRSpinBut::SetFontNum(long propVal)
{
	SetProperty(0x3, VT_I4, propVal);
}

long CRSpinBut::GetCurrentValue()
{
	long result;
	GetProperty(0x4, VT_I4, (void*)&result);
	return result;
}

void CRSpinBut::SetCurrentValue(long propVal)
{
	SetProperty(0x4, VT_I4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CRSpinBut operations

void CRSpinBut::AddString(LPCTSTR text)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 text);
}

void CRSpinBut::DeleteString(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void CRSpinBut::Clear()
{
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CRSpinBut::SetPriceOption(long min, long max, long current)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		min, max, current);
	return result;
}

BOOL CRSpinBut::SetValueOption(long min, long max, long current)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		min, max, current);
	return result;
}

void CRSpinBut::SetPassWord(BOOL ispassword)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ispassword);
}

BOOL CRSpinBut::SetSearchValueOption(long min, long max, long current)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		min, max, current);
	return result;
}

BOOL CRSpinBut::SetPlayerNegPriceOption(long min, long max, long current)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		min, max, current);
	return result;
}