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

//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "TPaintWl.h"
#include "..\h\dosdefs.h"
#include	"monotxt2.h"
//#include "c:\program files\microsoft visual studio\vc98\include\zmouse.h"
#include "..\h\zmouse.h"

//---------------------------------------------------------------------------
static inline TPaintBoxWithWheel *ValidCtrCheck()
{
	return new TPaintBoxWithWheel(NULL);
}
//---------------------------------------------------------------------------
static	MonoText mt(0xb0000+160*8);
__fastcall TPaintBoxWithWheel::TPaintBoxWithWheel(TComponent* Owner)
	: TPaintBox(Owner)
{
	wheelmsg=0;
    mt.PrintF(70,0,"W%08x",wheelmsg);
}

static int scroll=0;

void __fastcall TPaintBoxWithWheel::WndProc(TMessage& Message)
{
	if (!wheelmsg)
    {   UINT m1,m2,m3;
    	BOOL b1;
        INT		m4;
	    HwndMSWheel( &m1,&m2,&m3,&b1,&m4);
    	wheelmsg=m1;
	    mt.PrintF(70,0,"W%08x",wheelmsg);
    }
  // tests to determine whether to continue processing
  if (Tag==0)
  {
	  scroll=(scroll+1)&127;
		mt.PrintF((scroll&7)<<3,scroll>>3,"M%06x",Message.Msg);
  }
  if (Message.Msg==wheelmsg)
	  Message.Msg=WM_MOUSEWHEEL;
  TPaintBox::WndProc(Message);
}
void __fastcall TPaintBoxWithWheel::InternalOnMouseWheel(TMessage* Message)
{
	Message->Msg=WM_MOUSEWHEEL;
 //	__asm	int	3;
}

//---------------------------------------------------------------------------
namespace Tpaintwl
{
	void __fastcall Register()
	{
		TComponentClass classes[1] = {__classid(TPaintBoxWithWheel)};
		RegisterComponents("Samples", classes, 0);
	}
}
//---------------------------------------------------------------------------
