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

//------------------------------------------------------------------------------
//Filename       ctrl.cpp
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    Model Controls
//------------------------------------------------------------------------------
  
#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "planetyp.h"
#include "collided.h"
#include "mytime.h"
#include "myerror.h"
#include "monotxt.h"
#include "savegame.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Ctrl
//Author		Andrew McRae
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

Ctrl::Ctrl (PSURFACE pBase,
			CTRL_TYPE type,
			int* pinput,
			SWord i1, SWord i0, SWord i2,
			FP o1, FP o0, FP o2)
{
	pModel = pBase->pModel;

	Type = type;

	pInput = pinput;

	In1 = (FP)i1;
	In0 = (FP)i0;
	In2 = (FP)i2;

	switch (Type)
	{
		case CT_ROTATION:
			Out1 = Degs2Rads (o1);
			Out0 = Degs2Rads (o0);
			Out2 = Degs2Rads (o2);
			break;

		case CT_AERODYNAMIC:
			Out1 = o1;
			Out0 = o0;
			Out2 = o2;
			break;
	}

	// upper part
	if (In0 != In2)
	{
		ControlScale2 =	(Out0 - Out2) / (In0 - In2);
		ControlOffset2 = ((In2 * Out0) - (In0 * Out2)) / (In2 - In0);
	}
	else
	{
		ControlScale2 = 0;
		ControlOffset2 = 0;
	}

	// lower part
	if (In1 != In0)
	{
		ControlScale1 =	(Out1 - Out0) / (In1 - In0);
		ControlOffset1 = ((In0 * Out1) - (In1 * Out0)) / (In0 - In1);
	}
	else
	{
		ControlScale1 = 0;
		ControlOffset1 = 0;
	}


	pDeltaClCurve = NULL;
	pDeltaCdCurve = NULL;
	pDeltaCmCurve = NULL;

	OldInput = CONTROL_RESET;

	pBaseSurface = pBase;

	List.Attach (&pBaseSurface->pCtrls, this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Ctrl
//Author		Andrew McRae
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Ctrl::~Ctrl ()
{
	List.Detach (this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewCtrl
//Author		Andrew McRae
//Date			Mon 3 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
NewCtrl::NewCtrl (PSURFACE psurf, int* input, UWord chord, FP scale_pos, FP scale_neg)
{
	pMainPlane = NULL;
	pSurface = psurf;
	pInput = input;
	Chord = chord;
	Scale_Pos = scale_pos;
	Scale_Neg = scale_neg;

	List.Attach (&pSurface->pNewCtrls, this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewCtrl
//Author		Andrew McRae
//Date			Tue 4 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
NewCtrl::NewCtrl (PMAINPLANE pmain, int* input, UWord chord, FP scale_pos, FP scale_neg)
{
	pMainPlane = pmain;
	pSurface = NULL;
	pInput = input;
	Chord = chord;
	Scale_Pos = scale_pos;
	Scale_Neg = scale_neg;

	List.Attach (&pMainPlane->pNewCtrls, this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewCtrl
//Author		Andrew McRae
//Date			Mon 3 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
NewCtrl::~NewCtrl ()
{
	List.Detach (this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process
//Author		Andrew McRae
//Date			Mon 3 Nov 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void NewCtrl::Process (FP& angle, FP& coeff, Bool Inverted)
{
	FP input = (FP)*pInput;
	if(Inverted) input *= -1;
	
	PMODEL pModel;
	if(pMainPlane != NULL)		pModel = pMainPlane->pModel;
	else if(pSurface != NULL)	pModel = pSurface->pModel;

	if(pModel->Spinning)
		switch(pModel->Type)
		{
			case AT_SPITFIRE:
				if(pInput == &(pModel->Elevator))	input = -16384 + input / 2;
				if(pInput == &(pModel->Aileron))
					if(pModel->RotVel.y > 0)
						input = -16384 + input / 4;
					else
						input =  16384 + input / 4;
				if(pInput == &(pModel->Rudder))		input = input / 4;
				break;

			case AT_HURRICANE:
				if(pInput == &(pModel->Elevator))	input = -16384 + input / 2;
				if(pInput == &(pModel->Aileron))	input = input / 4;
				if(pInput == &(pModel->Rudder))
					if(pModel->RotVel.y > 0)	input = -16384 + input / 2;
					else						input =  16384 + input / 2;
				break;

			case AT_BF109:
				if(pInput == &(pModel->Elevator))	input = -16384 + input / 2;
				if(pInput == &(pModel->Aileron))	input = input / 4;
				if(pInput == &(pModel->Rudder))		input = input / 2;
				break;

			case AT_BF110:
				if(pInput == &(pModel->Elevator))	input = -16384 + input / 2;
				if(pInput == &(pModel->Aileron))	input = input / 4;
				if(pInput == &(pModel->Rudder))		input = input / 2;
				break;

			case AT_JU87B:
				if(pInput == &(pModel->Aileron))	input = input / 4;
				if(pInput == &(pModel->Rudder))		input = input / 2;
				break;
		}
	MODLIMIT(input, 32767);

	FP maxangle;
	if(input > 0)	maxangle = Scale_Pos;
	else
					maxangle = -Scale_Neg;

	FP factor1 = input * maxangle / 32768;
	factor1 = 1 - (1 - factor1) * (1 - factor1);
	factor1 *= pModel->FControlLoss;

	if(input > 0) 
	{
		angle += factor1 * 0.6 * ((FP)Chord * 0.01);
		coeff += factor1 * 5 * ((FP)Chord * 0.01) * ((FP)Chord * 0.01);
	}
	else
	{
		angle -= factor1 * 0.6 * ((FP)Chord * 0.01);
		coeff -= factor1 * 5 * ((FP)Chord * 0.01) * ((FP)Chord * 0.01);
	}
}
