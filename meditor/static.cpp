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
#include "uniqueid.h"

#include "Memain.h"

#include "Static.h"
#include "GrndGrp.h"

//DEADCODE JIM 09/02/00 #include	"text.h"
#include "strings.h"
#include	"myangles.h"
#include	"bfnumber.h"
#include	"persons2.h"
#include	"mymath.h"
#include "waypoint.h"

//---------------------------------------------------------------------------
#pragma resource "*.dfm"
TStaticForm *StaticForm;
//---------------------------------------------------------------------------
__fastcall TStaticForm::TStaticForm(TComponent* Owner)
	: TForm(Owner)
{
	Font->Color = clWindow;
	Font->Color = clWindowText;
}

int __fastcall TStaticForm::FindNationality(UniqueID uid)
{
	UniqueIDBand	uidband;

	uidband = Persons2::getbandfromUID(uid);

	switch	(uidband)
	{
    case    RealAcBAND:
    case    SagBAND:
    case    BritAAASiteBAND:
    case    BritAAALargeBAND:
    case    BritBridgeBAND:
    case    BritHistoricBAND:
    case    BritMobileBAND:
    case    BritBoatBAND:
    case    PowerStationBAND:
    case    OilRefineryBAND:
    case    IndustryBAND:
    case    AircraftFactoryBAND:
    case    DocksBAND:
    case    PortBAND:
    case    NavalBaseBAND:
    case    RAF_FighterAFBAND:
    case    RAF_BomberAFBAND:
    case    RAF_CoastalAFBAND:
    case    CLRadarBAND:
    case    CHRadarBAND:
    case    SectorOpsBAND:
    case    AfHangarBAND:
    case    AfStaffBAND:
    case    AfStoresBAND:
    case    AfFieldBAND:
    case    AfNoScoreBAND:
		{
			return(IDS_ALLIES);
		}
//    case    BlueAcBAND:
    case    GermAAASiteBAND:
    case    GermMobileBAND:
    case    GermBoatBAND:
    case    LUF_FighterLF2BAND:
    case    LUF_FighterLF3BAND:
    case    LUF_BomberLF2BAND:
    case    LUF_BomberLF3BAND:
		{
			return(IDS_CENTRALPOWERS);
		}
    case    CivilianBAND:
    case    NeutMiscBAND:
    case    CityBAND:
    case    TownBAND:
    case    VillageBAND:
//    case    TakeOffPosBAND:
    case    TaxiBAND:
    case    EventBAND:
    case    RunwaySBAND:
    case    RunwayEBAND:
		{
			return(IDS_NEUTRAL);
		}
	 }
     return(IDS_NEUTRAL);
}
//---------------------------------------------------------------------------
void	__fastcall TStaticForm::OpenForm()
{
//not needed for MiG Alley, I think rdh
//DeadCode RDH 19Feb98 	char buff[50];
//DeadCode RDH 19Feb98         WayPointForm->Close();
//DeadCode RDH 19Feb98 	
//DeadCode RDH 19Feb98 		int	nat = FindNationality(MissionEditor->currtemplateitem);
//DeadCode RDH 19Feb98 		LoadString(HInstance,nat,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		NatLabel->Caption = buff;
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 		info_itemS*	I= *Persons_2.ConvertPtrUID(MissionEditor->currtemplateitem);
//DeadCode RDH 19Feb98 		int shapenameindex = GroundGroupForm->GeneralFindShapes(I->shape);
//DeadCode RDH 19Feb98 		LoadString(HInstance,shapenameindex,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		ShapeLabel->Caption = buff;
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 		int text = MissionEditor->GetBandorShapeText(MissionEditor->currtemplateitem);
//DeadCode RDH 19Feb98 		LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		BandLabel->Caption = buff;
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 		LoadString(HInstance,MissionEditor->currtemplateitem,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		if (buff[0] == 0)
//DeadCode RDH 19Feb98 		{
//DeadCode RDH 19Feb98 			int text = MissionEditor->GetBandorShapeText(MissionEditor->currtemplateitem);
//DeadCode RDH 19Feb98 			LoadString(HInstance,text,buff,sizeof(buff));
//DeadCode RDH 19Feb98 		}
//DeadCode RDH 19Feb98 
//DeadCode RDH 19Feb98 		Caption = buff;

	Show();
}

