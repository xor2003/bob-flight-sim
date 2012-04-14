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
//Filename       persons4.cpp
//System
//Author         Jim Taylor
//Date           Fri 20 Jun 1997
//Description    Version of persons for mission editor
//				 This version makes the complex info_ objects permanent
//------------------------------------------------------------------------------
//#include <vcl\vcl.h>
//#include	"memain.h"


  //	#include	<stdio.h>

//DEADCODE JIM 09/02/00 	#include	"text.h"
	#include	"dosdefs.h"
	#include	"myerror.h"
//#define	TEXTREF_Included
	#include	"worldinc.h"
 	#include	"myangles.h"
	#include	"uniqueid.h"
	#include	"mymath.h"
	#include	"bfnumber.h"
	#include	"makebf.h"
	#include	"persons2.h"
//	#include	"sqinfo.h"
	#include	"files.g"
//#define	TEXTREF_Included
//	#include	"text.h"
//	#include	"error.h"
	#include	"mymath.h"
	#include	"worldinc.h"
//	#include	"node.h"
	#include	"bfnumber.h"
//	#include	"bfcommon.h"
	#include	"bfnumber.h"	//intensional double include

//DeadCode JIM 28Mar96 extern	PlaneType&	camel;										//RDH 23Feb96
//Old_Code PD 27Aug96  	MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);
//	extern	ULong	GR_FriendlyScoutType00;
//	extern	ULong	GR_GlobalSkillMin;
//	extern	ULong	GR_GlobalSkillMax;
//	extern	ULong	GR_CWP,GR_CPP;

//##int	Expr::lowestaddr=0x77777777;
//##int	Expr::highestaddr=0;
//##int	Expr::numelts=0;
//##int	Expr::indent=0;
//int	info_debug::lowestaddr=0x77777777;
//int	info_debug::highestaddr=0;
//int	info_debug::numelts=0;

Bool	operator == (TokenCode a,TokenCode b)	{return Bool(int(a)==int(b));}
//Nationality		defaultside=NAT_GREEN;

#define EvalOrDefault(field,type,expr,default)				\
		{													\
			int v1;											\
			if ((v1=I.expr.Evaluate())==ENABLE_COMPLEX_VAL)	\
				field=default;								\
			else			   								\
				field=type(v1);								\
		}

;//ME ItemBase *items[(int)IllegalBAND+1];

BfieldDesc*		Persons2::bfdesc=NULL;
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������
//
//	THESE make_ routines make the actual items in the world
//
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������

//������������������������������������������������������������������������������


//DeadCode MS 28Oct100 void	Persons2::FixupRouteOwner(UniqueID	owner,UniqueID route)
//DeadCode MS 28Oct100 {
//DeadCode MS 28Oct100 	while (route)
//DeadCode MS 28Oct100 	{
//DeadCode MS 28Oct100 		info_waypoint* W=*ConvertPtrUID(route);
//DeadCode MS 28Oct100 
//DeadCode MS 28Oct100 		if (W->Status.size!=WAYPOINTSIZE)
//DeadCode MS 28Oct100 			W->owner=owner;
//DeadCode MS 28Oct100 		W->position.EvalW(W->World);
//DeadCode MS 28Oct100 		if (W->target.Evaluate()!=ENABLE_COMPLEX_VAL)
//DeadCode MS 28Oct100 		{
//DeadCode MS 28Oct100 			Coords3D	t;
//DeadCode MS 28Oct100 			UIDExpr	u;
//DeadCode MS 28Oct100 			u.val=W->target.Evaluate();
//DeadCode MS 28Oct100 			u.EvalW(t);
//DeadCode MS 28Oct100 			W->World.X+=t.X;//ME +MissionEditor->zoomiconsize;
//DeadCode MS 28Oct100 			W->World.Y+=t.Y;
//DeadCode MS 28Oct100 			W->World.Z+=t.Z;//ME -MissionEditor->zoomiconsize;
//DeadCode MS 28Oct100 		}
//DeadCode MS 28Oct100 		W->owner=owner;
//DeadCode MS 28Oct100 		route=W->nextwp;
//DeadCode MS 28Oct100 	}
//DeadCode MS 28Oct100 }

//������������������������������������������������������������������������������
//Procedure		make_airgrp
//Author		Jim Taylor
//Date			Mon 16 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::make_airgrp(info_airgrp& I)
{
	if (!justscanning)
	{
		info_airgrp*	J=new info_airgrp;
		*J=I;
		int v1,v2,v3;
		if ((v3=J->nat.Evaluate())==ENABLE_COMPLEX_VAL)
			v3=NAT_RED;//defaultside;
		if ((v1=J->uid.Evaluate())==ENABLE_COMPLEX_VAL)
			if ((v2=J->band.Evaluate())==ENABLE_COMPLEX_VAL)
//DEADCODE DAW 24/11/99 				if (v3==(int)NAT_RED)
//DEADCODE DAW 24/11/99 					J->uniqueID.count=assignuid(RedAcBAND);
//DEADCODE DAW 24/11/99 				else
				J->uniqueID.count=assignuid(RealAcBAND);
			else
				J->uniqueID.count=assignuid((UniqueIDBand)v2);
		else
			if (&ConvertPtrUID(UniqueID(v1)))
            {
            	PleaseWarnUser("This battlfield has been damaged because of the above error. Do not save it!","Aircraft with named UID already loaded.");
				J->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
            }
			else
				J->uniqueID.count=UniqueID(v1);
#ifndef	__BCPLUSPLUS__
		if (J->wpref==UID_NULL)
			J->wpref=UniqueID(GR_lastroutefirstwaypoint);
#endif
		if ((v3=J->wpnum.Evaluate())!=ENABLE_COMPLEX_VAL)
			while (--v3>=0)
			{
				info_waypointPtr w=ConvertPtrUID(J->wpref);
				J->wpref=w->nextwp;
			}
//DeadCode MS 26Sep00 #ifndef NDEBUG
//DeadCode MS 26Sep00 			{	//Homebase never filled in...
//DeadCode MS 26Sep00  				info_waypointPtr w=ConvertPtrUID(J->wpref);
//DeadCode MS 26Sep00 				if (w->applygroup!=ENABLE_COMPLEX_VAL)
//DeadCode MS 26Sep00 					assert(	w->target.Evaluate()==J->homebase.Evaluate());
//DeadCode MS 26Sep00 			}
//DeadCode MS 26Sep00 #endif
		//NOTE: 
			//Coming back from the 3d, the information represented here
			//is not up to date.
			//We need to have recorded the new position, waypoint and strength
			//of each aircraft.
			//This note is repeated in mapcode.cpp
			//
#ifndef NDEBUG
		assert (loadedSAGcount<MAX_LOADEDSAG,": Too many sags loaded!");
		loadedSAG[loadedSAGcount++]=J->uniqueID.count;
#endif
		J->bfieldindex=currbfindex;
//		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
//		J->uniqueID.deaded=FALSE;
		J->position.EvalW(J->World);
  //		J->shape=ShapeNum(J->shape.Evaluate());
//		FixupRouteOwner(J->uniqueID.count,J->wpref);
  //		FixupRouteOwner(J->uniqueID.count,J->wpref);
//camp tmp		if (J->inform.Evaluate()==ENABLE_COMPLEX_VAL)
//			MissionEditor->ActiveCampaign.PlayerAcuid = J->uniqueID.count;
		logUID(J);
	}
	else
	{
		int	v3;
		if ((v3=I.nat.Evaluate())==ENABLE_COMPLEX_VAL)
			v3=NAT_RED;//defaultside;
        if (bfdesc)
			if (I.inwing.Evaluate()==ENABLE_COMPLEX_VAL)
				if (v3==NAT_RED)
;//ME 					bfdesc->RAC+=12;
				else
;//ME 					bfdesc->BAC+=12;
			else
				if (v3==NAT_RED)
;//ME 					bfdesc->RAC+=I.inform.Evaluate();
				else
;//ME 					bfdesc->BAC+=I.inform.Evaluate();
	}
}

//������������������������������������������������������������������������������
//Procedure		make_waypoint
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs		if I.useexistingWP then evaluate that to get UID to link in!
//				no other vars will be filled in.
//
//Returns
//
//------------------------------------------------------------------------------
UniqueID	Persons4::make_waypoint(info_waypoint& I)
{
	if (!justscanning)
	{
		info_waypoint*	J=new info_waypoint;
		*J=I;
		int v=I.uid.Evaluate();
		if (v<=0)
			v=assignuid(WayPointBAND);
		J->uniqueID.count=UniqueID(v);
		J->bfieldindex=currbfindex;
		J->uniqueID.changed=FALSE;
		J->World.Y=ENABLE_COMPLEX_VAL;									//RDH 10/03/00
		logUID(J);
		if (J->prevwp && J->prevwp!=IllegalSepID)
		{
			info_waypoint* W=*ConvertPtrUID(J->prevwp);
			W->nextwp=UniqueID(v);
		}
		else
		{
			J->prevwp=UID_Null;
#ifndef	__BCPLUSPLUS__
			GR_lastroutefirstwaypoint=v;
#endif
		}
		J->World.Y=ENABLE_COMPLEX_VAL;
		J->nextwp=UID_Null;
		return UniqueID(v);
	}
	return UID_Null;

}

void	Persons4::AddRoute(UniqueID	firstwp)
{	//This is called after the whole route has been read in...
}
//������������������������������������������������������������������������������
//Procedure		make_gndgrp
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::make_gndgrp(info_grndgrp& I)
{
	if (!justscanning)
	{
		info_grndgrp*	J=new info_grndgrp;
		*J=I;
		bool	gotGRoverride=false;
		int v1,v2,v3;
		if ((v3=J->nat.Evaluate())==ENABLE_COMPLEX_VAL)
			v3=NAT_RED;//defaultside;
		if ((v1=J->uid.Evaluate())==ENABLE_COMPLEX_VAL)
			if ((v2=J->band.Evaluate())==ENABLE_COMPLEX_VAL)
					J->uniqueID.count=assignuid(BritBoatBAND);	//JIM 22Feb100
			else
				J->uniqueID.count=assignuid((UniqueIDBand)v2);
		else
			if (&ConvertPtrUID(UniqueID(v1)))
            {
            	PleaseWarnUser("This battlfield has been damaged because of the above error. Do not save it!","Mobile with named UID already loaded.");
				J->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
            }
			else
			{
				J->uniqueID.count=UniqueID(v1);
#ifndef	__BCPLUSPLUS__
				if (v1==+GR_ItemInfoOverride)
					gotGRoverride=true;
#endif
			}
		J->bfieldindex=currbfindex;
//		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
//		J->uniqueID.deaded=FALSE;
		J->position.EvalW(J->World);
#ifndef	__BCPLUSPLUS__
		if (gotGRoverride)
		{
//DeadCode JIM 22Oct00 			J->World.X=GR_ItemXOverride;
//DeadCode JIM 22Oct00 			J->World.Z=GR_ItemZOverride;
			for (int wpcount=GR_ItemWpOverride;wpcount;wpcount--)
				if (info_waypointPtr(Persons2::ConvertPtrUID(J->wpref))->nextwp)
					J->wpref=info_waypointPtr(Persons2::ConvertPtrUID(J->wpref))->nextwp;
		}
#endif
//		J->shape=ShapeNum(J->shape.Evaluate());
		J->Item::shape=ShapeNum(J->shape.Evaluate());				  //JIM 16/04/99

		logUID(J);
//		FixupRouteOwner(J->uniqueID.count,J->wpref);
  //		FixupRouteOwner(J->uniqueID.count,J->wpref);
	}                                               
	else
		if (justscanning==SCANNAMES)
		{
			int	v3;
			if ((v3=I.nat.Evaluate())==ENABLE_COMPLEX_VAL)
				v3=NAT_RED;//defaultside;
            if (bfdesc)
				if (v3==NAT_RED)
;//ME 					bfdesc->RGR+=I.inform.Evaluate();
				else
;//ME 					bfdesc->BGR+=I.inform.Evaluate();
		}
}
//������������������������������������������������������������������������������
//Procedure		make_itemS
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	Makes object J, a copy of temp object I
//				Fills in item UID and coords
//				Adds item to UID table.
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
int		Persons4::make_itemgroupcount(EventVal& E)
{
	return 32767;	//E.Evaluate();
}

void	Persons4::make_itemS(info_itemS& I,bool enabled)
{
//  if ((int)I.uid.Evaluate() != (int)UID_Varneville)				//this is in wrong band so don't load!
//  {
	if (!justscanning)
	{
		info_itemS* J=new info_itemS;
		*J=I;
		int v1,v2;
																	//	if ((v3=J->nat.Evaluate())==ENABLE_COMPLEX_VAL)
																	  //		v3=defaultside;
		if ((v1=J->uid.Evaluate())==ENABLE_COMPLEX_VAL)
			if ((v2=J->band.Evaluate())==ENABLE_COMPLEX_VAL)
				J->uniqueID.count=assignuid(CivilianBAND);
			else
				J->uniqueID.count=assignuid((UniqueIDBand)v2);
		else
			if (&ConvertPtrUID(UniqueID(v1)))
            {
				J->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
            	PleaseWarnUser("This battlfield has been damaged because of the above error. Do not save it!","Aircraft with named UID already loaded.");
            }
			else
				J->uniqueID.count=UniqueID(v1);
		J->bfieldindex=currbfindex;
//DeadCode RDH 11Feb98 		J->uniqueID.sector=loadingmainworld;
		J->uniqueID.changed=FALSE;
//		J->uniqueID.deaded=FALSE;
		J->position.EvalW(J->World);
		J->Item::shape=ShapeNum(J->shape.Evaluate());
		logUID(J);
	}
//DEADCODE JIM 16/11/99 	else
//DEADCODE JIM 16/11/99 		if (bfdesc && justscanning==SCANNAMES)
//DEADCODE JIM 16/11/99 ;//ME 			bfdesc->ST++;
//  }
//  else
//  {
//
//
//  }
}

//������������������������������������������������������������������������������
//Procedure		make_events
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	Don't need to fill this routine.
//				The event chain is automatically part of the called routine
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::make_events(info_event*&	I,ItemBasePtr P)
{
	if (justscanning==SELECTSQUAD)
	{
		if (--selectedsquad==0)
		{
			*keptevent=*I;
		}
	}
}


//������������������������������������������������������������������������������
//Procedure		make_setval
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::make_setval(EventVar& es)
{
	if (justscanning)
    	if (bfdesc)
;//ME 			bfdesc->defrefs[bfdesc->useddefrefs++]=es;
        else;    
	else
		SetLoc(es.index,es.Evaluate());
}

//������������������������������������������������������������������������������
//Procedure		used_globref
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::used_globref(int index)
{
	if (bfdesc&&justscanning)
	{
;//ME 		for (int i=0;i<bfdesc->useddefrefs;i++)
;//ME 			if (bfdesc->defrefs[i].index==index)
;//ME 				return;
;//ME 		for (int i=0;i<bfdesc->usedreqrefs;i++)
;//ME 			if (bfdesc->reqrefs[i]==index)
;//ME 				return;
;//ME 
;//ME 
;//ME 		bfdesc->reqrefs[bfdesc->usedreqrefs++]=index;
	}
}

//������������������������������������������������������������������������������
//Procedure		make_string
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description
//
//Inputs		t is one of:
//						T_comment
//						T_name
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::SquadAddDesc(string bfieldptr,int len,TokenCode t)

{}

void	Persons4::make_string(string src,int len,TokenCode t)
{
	if (!bfdesc)
    	return;
	if (justscanning==SCANNAMES)
	{
 		char*	trg;//ME =bfdesc->title;
//DEADCODE JIM 16/11/99 		if (t==T_comment)
//DEADCODE JIM 16/11/99 ;//ME 			if ((UWord&)bfdesc->description[0])
//DEADCODE JIM 16/11/99 ;//ME 			{
//DEADCODE JIM 16/11/99 ;//ME 				trg=bfdesc->news;
//DEADCODE JIM 16/11/99 ;//ME 				if (len>=DESCRIPT_LEN)
//DEADCODE JIM 16/11/99 ;//ME 					len=DESCRIPT_LEN-1;
//DEADCODE JIM 16/11/99 ;//ME 
//DEADCODE JIM 16/11/99 ;//ME 			}
//DEADCODE JIM 16/11/99 ;//ME 			else
//DEADCODE JIM 16/11/99 ;//ME 			{
//DEADCODE JIM 16/11/99 ;//ME 				trg=bfdesc->description;
//DEADCODE JIM 16/11/99 ;//ME 				if (len>=DESCRIPT_LEN)
//DEADCODE JIM 16/11/99 ;//ME 					len=DESCRIPT_LEN-1;
//DEADCODE JIM 16/11/99 ;//ME 			}
//DEADCODE JIM 16/11/99 ;//ME 		else
		if (t==T_family)
		{
;//ME 			trg=bfdesc->family;
			if (len>=TITLE_LEN)
				len=TITLE_LEN-1;
		}
		else
			if (len>=TITLE_LEN)
				len=TITLE_LEN-1;
//		trg[1]=1;
;//ME 		strncpy(trg,src,len);
  //		trg[len]=0;
	}
	else
	if (justscanning==SCANSQUADS)
		SquadAddDesc(src,len,t);

	if (t==T_family && src[0]<='9')
		if (justscanning)
		{
			int	dummy;
//camp tmp			sscanf(src,
//					"%i %i "
//					"%hi %hi "
//					"%c %c "
//					"%hi %hi %hi "
//					"%hi %hi %hi "
//					"%hi %hi "
//					"%hi %hi "
//					"%hi %hi %hi"
//					,
//					&MissionEditor->ActiveCampaign.nextdate,&dummy,
//					&dummy,&dummy,
//					&MissionEditor->ActiveCampaign.nextnat,&dummy,
//					&dummy,&dummy,&dummy,
//						&MissionEditor->ActiveCampaign.nextera,
//						&MissionEditor->ActiveCampaign.nextregion,
//						&dummy,
//					&dummy,&dummy,
//					&dummy,&dummy,
//					&dummy,&dummy,&dummy
//					);
//			MissionEditor->ActiveCampaign.nextnat&=31;
		}
		else
		{	//load mission control record
//camp tmp			MissionData *M=MissionEditor->ActiveCampaign.mission+MissionEditor->currmission;
//			int	dummy;
//			sscanf(src,
//					"%i %i "
//					"%hi %hi "
//					"%c %c "
//					"%hi %hi %hi "
//					"%hi %hi %hi "
//					"%hi %hi "
//					"%hi %hi "
//					"%hi %hi %hi"
//					,
//					&M->missiondate,&M->timeofday,
//					&M->numofsquadronac,&M->numofflightac,
//					&M->PlayerNationality,&M->formationtypeindex,
//					&M->weathernum,&M->windspeed,&M->winddirection,
//					&dummy,&M->region,&M->PlayerAcType,
//					&(UWord&)M->PlayerHomeBase,&(UWord&)M->EnemyHomeBase,
//					&(UWord&)M->MainObjective,&(UWord&)M->SubObjective,
//					&(UWord&)M->WP1,&(UWord&)M->WP2,&(UWord&)M->WP3
//					);
//			M->PlayerNationality&=31;M->formationtypeindex&=31;
		}
}

Bool	Persons4::make_agname(string src,int len,info_airgrp& A)
{
	if (!justscanning)
		if (len==4)
		{
//DEADCODE JIM 14/02/00 			int	v=(src[1]&15)*100+(src[2]&15)*10+(src[3]&15);
//DEADCODE JIM 14/02/00 			if (src[0]=='E')
//DEADCODE JIM 14/02/00 				A.squadron=-v;
//DEADCODE JIM 14/02/00 			else
//DEADCODE JIM 14/02/00 				A.squadron=v;
//DEADCODE JIM 14/02/00 			return TRUE;
		}
	return FALSE;
}

Bool	Persons4::make_eventname(string src,int len,info_event& E)
{
	if (justscanning==NAMESQUAD)
		if (selectedsquad--==0)
		{
;//ME 			strncpy(keptstr,src,len);
			keptstr[len]=0;
		}
	if (!justscanning)
		if (len==4)
		{
			int	v=(src[1]&15)*100+(src[2]&15)*10+(src[3]&15);
			if (src[0]=='F')
				if (E.FrFighterSq)
					E.FrBomberSq=v;
				else
					E.FrFighterSq=v;
			else
			if (src[0]=='E')
				if (E.EnFighterSq)
					E.EnBomberSq=-v;
				else
					E.EnFighterSq=-v;
		}
//	if (justscanning==SELECTSQUAD)
		return TRUE;
//	else
  //	{	//need to generate squad number info here somehow!
	//	return FALSE;
//	}
}




//������������������������������������������������������������������������������
//Procedure		logUID
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	puts item in uid lookup
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons4::logUID(ItemBasePtr	selecteditem)
{
    tabulateUID(selecteditem);
}
void	Persons2::tabulateUID(ItemBasePtr	selecteditem)

{
//	UidNode			*swapnode, **foundnode, *thenode, *nextnode, **rightmostnode;
	UniqueID		theuid;
  //	Bool			finished = FALSE;
  //	ItemBasePtr		*attackerptr;
  //	UILogType	 	request;

	theuid = selecteditem->uniqueID.count;
	if (theuid==0x100)
		NOP;
	assert(pItem[theuid]==NULL,"UID already used!");

	assert(pItem[theuid]==0,"Reused!");
	pItem[theuid] = selecteditem;

}

void	Persons2::delUID(UniqueID u)
{
	pItem[u]=NULL;
}

//������������������������������������������������������������������������������
//
//	Runtime/endgame routines to getting info on items
//
//������������������������������������������������������������������������������
//������������������������������������������������������������������������������

//������������������������������������������������������������������������������
//Procedure		ItemStatus
//Author		Jim Taylor
//Date			Mon 30 Sep 1996
//
//Description	get and put statuses of items. Use in State3d destructor.
//
//Inputs		
//
//Returns
//
//------------------------------------------------------------------------------
ITEM_STATUS	Persons2::ItemStatus(UniqueID u,ITEM_STATUS s)
{

 	ItemBasePtr	i=ConvertPtrUID(u);
 	if (i)
 	{
 		ITEM_STATUS	rv=i->Status;
 		i->Status.deadtime=(int)s.deadtime;
 		i->Status.deadscale=(int)s.deadscale;
 		return (rv);
 	}
	else
	{
		ITEM_STATUS	rv(FALSE);
		return rv;
	}
}

ITEM_STATUS	Persons2::ItemStatus(UniqueID u)
{
 	ItemBasePtr	i=ConvertPtrUID(u);
 	if (i)
 		return (i->Status);
 	else
	{
		ITEM_STATUS	rv(FALSE);
		return rv;
	}
}

//ITEM_STATUS	Persons2::ConvoyStatus(UniqueID uid,UniqueID& nextwp,UniqueID& nextwptarg,SLong& livelength)
//{
// 	FormationItemPtr	f=*ConvertPtrUID(uid);
// 	if (f)
// 	{
// 		livelength=0;
//DeadCode JIM 20Jun97 		WayPointPtr w=f->waypoint;
//DeadCode JIM 20Jun97
//DeadCode JIM 20Jun97 		nextwp=w->uniqueID.count;
//DeadCode JIM 20Jun97 		ItemBasePtr	i=w->target;
//DeadCode JIM 20Jun97 		if (i)
//DeadCode JIM 20Jun97 			nextwptarg=i->uniqueID.count;
//DeadCode JIM 20Jun97 		else
//DeadCode JIM 20Jun97 			nextwptarg=IllegalSepID;
//DeadCode JIM 20Jun97 		while (f)
//DeadCode JIM 20Jun97 		{
//DeadCode JIM 20Jun97 			if (f->Status.deadtime==0)
//DeadCode JIM 20Jun97 			  	livelength++;
//DeadCode JIM 20Jun97 			f=f->follower;
//DeadCode JIM 20Jun97 		}
//DeadCode JIM 20Jun97 		if (i)
//DeadCode JIM 20Jun97 			return (i->Status);
//DeadCode JIM 20Jun97 		else
//DeadCode JIM 20Jun97 			return (w->Status);
//DeadCode JIM 20Jun97 	}
//DeadCode JIM 20Jun97 	else
//	{
//		ITEM_STATUS	rv(FALSE);
//		return rv;
//	}
//}

void Persons4::InitGamePiece()
{
;//ME 	FILE* f=fopen("..\\h\\uidtops.g","rt");
;//ME 	int i;
;//ME 		fscanf(f,"%x %x",&i,&i);
;//ME 	int c=-1;
;//ME 	do
;//ME 	{
;//ME 		int i,j=0;
;//ME 		fscanf(f,"%x %x",&i,&j);
;//ME 		switch (i)
;//ME 		{	//patch bands where we can have full spread.
;//ME //			case	RedGroundMobileBAND:
;//ME   //			case	BlueAcBAND:
;//ME 	//		case	RedCivilianBAND:
;//ME 	  //			uidbandmax[c]=i;
;//ME 		}
;//ME 		c++;
;//ME 		i=fgetc(f);
;//ME 		uidbandmax[c]=j;
;//ME 	}	while (c<2||uidbandmax[c]!=0);
;//ME
;//ME
}

void	Persons4::InitSubPiece()
{
}

void Persons4::EndSubPiece()
{
}
void Persons4::FinishSetPiece()
{
}

//typedef void (*ha)(AirStrucPtr,FormationIndex,UByte* colours);
//ha	Persons2::Colour_Rule_List[]
//		={  NULL };

Bool	Persons4::anyoutstanding()	{return FALSE;}

//##void	Expr::printit(int indent,char name,int value)
//##{
//##}



 //
 //
 //
 //


//
//
//
//
