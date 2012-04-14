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

// RowanDialog: // MapFltrs.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "MapFltrs.h"
#include	"savegame.h"
#include	"migview.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapFilters dialog
static const int NOBUTTON=-1;
int CMapFilters::filterbuttons[MAPFILTERSMAX+2]=
{	NOBUTTON,
	IDC_FILTER_BLUE_CIVILIAN,
	IDC_FILTER_BLUE_SUPPLY,
	IDC_FILTER_BLUE_MYARD,
	IDC_FILTER_BLUE_BRIDGE,
	IDC_FILTER_BLUE_ROADLINK,
	IDC_FILTER_BLUE_RAILLINK,
	IDC_FILTER_BLUE_TRUCK,
	IDC_FILTER_BLUE_TRAIN,
	IDC_FILTER_BLUE_ARTIE,
	IDC_FILTER_BLUE_TROOP,
	IDC_FILTER_BLUE_TANK,
	IDC_FILTER_BLUE_AIRFIELDS,
	 NOBUTTON,
	IDC_FILTER_RED_CIVILIAN,
	IDC_FILTER_RED_SUPPLY,
	IDC_FILTER_RED_MYARD,
	IDC_FILTER_RED_BRIDGE,
	IDC_FILTER_RED_ROADLINK,
	IDC_FILTER_RED_RAILLINK,
	IDC_FILTER_RED_TRUCK,
	IDC_FILTER_RED_TRAIN,
	IDC_FILTER_RED_ARTIE,
	IDC_FILTER_RED_TROOP,
	IDC_FILTER_RED_TANK,
	IDC_FILTER_RED_AIRFIELDS,

	NOBUTTON,
	IDC_FILTER_MAINWP,
	IDC_FILTER_SUBWP,
	IDC_FILTER_ROUTES,
	IDC_FILTER_FRONTLINE,
	NOBUTTON,
	0
};

//DEADCODE RDH 06/01/00 static const MapFiltersField
//DEADCODE RDH 06/01/00 	REDFILTERON(MAPFILTERSMAXBLUE,MAPFILTERSMAXRED),
//DEADCODE RDH 06/01/00 	BLUEFILTERON(MAPFILTERSMIN,MAPFILTERSMAXBLUE);
//DEADCODE RDH 06/01/00 

CMapFilters::CMapFilters(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CMapFilters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMapFilters::DoDataExchange(CDataExchange* pDX)
{

	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapFilters)
		// NOTE: the ClassWizard will add DDX and DDV calls here

	//}}AFX_DATA_MAP
	for (int filter=0;filterbuttons[filter];filter++)
		if (filterbuttons[filter]!=NOBUTTON)
			DDX_Control(pDX,filterbuttons[filter],m_filterbuttons[filter]);

}


BEGIN_MESSAGE_MAP(CMapFilters, CRToolBar)
	//{{AFX_MSG_MAP(CMapFilters)
	ON_WM_INITMENU()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapFilters message handlers

BEGIN_EVENTSINK_MAP(CMapFilters, CRToolBar)
    //{{AFX_EVENTSINK_MAP(CMapFilters)
	//}}AFX_EVENTSINK_MAP
	ON_EVENT_RANGE(CMapFilters, 1,9999, 1 /* Clicked */, OnClickedFilter, VTS_I4)
END_EVENTSINK_MAP()

void CMapFilters::OnClickedFilter(int id) 
{
//DEADCODE DAW 23/11/99 	if (id==IDC_BORDER)	
//DEADCODE DAW 23/11/99 		return;
	// TODO: Add your control notification handler code here
//DEADCODE RDH 06/01/00 		CRButton* but=(CRButton*)GetDlgItem(id);
//DEADCODE RDH 06/01/00 		bool pressed=(but->GetPressed()==1);
//DEADCODE RDH 06/01/00 	if (id==IDC_FILTER_BLUE_ALL)
//DEADCODE RDH 06/01/00 	{
//DEADCODE RDH 06/01/00 		if (pressed)
//DEADCODE RDH 06/01/00 			Save_Data.mapfilters|=BLUEFILTERON;
//DEADCODE RDH 06/01/00 		else
//DEADCODE RDH 06/01/00 			Save_Data.mapfilters-=BLUEFILTERON;
//DEADCODE RDH 06/01/00 		SetFiltersFromSaveGame();
//DEADCODE RDH 06/01/00 	}
//DEADCODE RDH 06/01/00 	else if (id==IDC_FILTER_RED_ALL)
//DEADCODE RDH 06/01/00 	{
//DEADCODE RDH 06/01/00 		if (pressed)
//DEADCODE RDH 06/01/00 			Save_Data.mapfilters|=REDFILTERON;
//DEADCODE RDH 06/01/00 		else
//DEADCODE RDH 06/01/00 			Save_Data.mapfilters-=REDFILTERON;
//DEADCODE RDH 06/01/00 		SetFiltersFromSaveGame();
//DEADCODE RDH 06/01/00 	}
//DEADCODE RDH 06/01/00 	else
//DEADCODE RDH 06/01/00 											  //JIM 21/05/99
//DEADCODE RDH 06/01/00 	{
//DEADCODE RDH 06/01/00 		for (int i=0;filterbuttons[i];i++)
//DEADCODE RDH 06/01/00 			breakif(filterbuttons[i]==id);
//DEADCODE RDH 06/01/00 		assert(filterbuttons[i]);
//DEADCODE RDH 06/01/00 
//DEADCODE RDH 06/01/00 		if (pressed)
//DEADCODE RDH 06/01/00 			Save_Data.mapfilters|=(MapFilters)i;
//DEADCODE RDH 06/01/00 		else
//DEADCODE RDH 06/01/00 			Save_Data.mapfilters%=(MapFilters)i;
//DEADCODE RDH 06/01/00 	}
//DEADCODE RDH 06/01/00 	m_pView->m_mapdlg.Invalidate();
//DEADCODE RDH 06/01/00 	//delete but;
}

void	SetFiltersFromSaveGame()
{
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	main->m_toolbar1.SetFiltersFromSaveGame();

}
void	CMapFilters::SetFiltersFromSaveGame()
{
//DeadCode DAW 11Jul00 	for (int i=0;filterbuttons[i];i++)
//DeadCode DAW 11Jul00 		if (filterbuttons[i]!=NOBUTTON)
//DeadCode DAW 11Jul00 		{
//DeadCode DAW 11Jul00 			CRButton* but=GETDLGITEM(filterbuttons[i]);
//DeadCode DAW 11Jul00 			but->SetPressed(Save_Data.mapfilters[(MapFilters)i]);
//DeadCode DAW 11Jul00 		}
}

void CMapFilters::OnInitMenu(CMenu* pMenu) 
{
	CRToolBar::OnInitMenu(pMenu);
	
	
}

int CMapFilters::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CRToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	return 0;
}
