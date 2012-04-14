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

// RowanDialog: // MFRaids.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "MFRaids.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// MapFiltersRaids dialog


RDialog*	MapFiltersRaids::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new MapFiltersRaids())
			);
}


MapFiltersRaids::MapFiltersRaids(CWnd* pParent /*=NULL*/)
	: RowanDialog(MapFiltersRaids::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapFiltersRaids)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MapFiltersRaids::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapFiltersRaids)
	DDX_Control(pDX, IDC_LWARROWS, m_IDC_LWARROWS);
	DDX_Control(pDX, IDC_RAFINTERCEPTS, m_IDC_RAFINTERCEPTS);
	DDX_Control(pDX, IDC_RAFPATROLS, m_IDC_RAFPATROLS);
	DDX_Control(pDX, IDC_RAFROUTELINES, m_IDC_RAFROUTELINES);
	DDX_Control(pDX, IDC_RRADIO_PLOTS, m_IDC_RRADIO_PLOTS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapFiltersRaids, CDialog)
	//{{AFX_MSG_MAP(MapFiltersRaids)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapFiltersRaids message handlers

BEGIN_EVENTSINK_MAP(MapFiltersRaids, CDialog)
    //{{AFX_EVENTSINK_MAP(MapFiltersRaids)
	ON_EVENT(MapFiltersRaids, IDC_LWARROWS, 1 /* Clicked */, OnClickedLwarrows, VTS_NONE)
	ON_EVENT(MapFiltersRaids, IDC_RAFINTERCEPTS, 1 /* Clicked */, OnClickedRafintercepts, VTS_NONE)
	ON_EVENT(MapFiltersRaids, IDC_RAFPATROLS, 1 /* Clicked */, OnClickedRafpatrols, VTS_NONE)
	ON_EVENT(MapFiltersRaids, IDC_RAFROUTELINES, 1 /* Clicked */, OnClickedRafroutelines, VTS_NONE)
	ON_EVENT(MapFiltersRaids, IDC_RRADIO_PLOTS, 1 /* Selected */, OnSelectedRradioPlots, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void MapFiltersRaids::OnClickedLwarrows() 
{
	if (Save_Data.mapfilters[FILT_LWARROWS])
		Save_Data.mapfilters%=FILT_LWARROWS;
	else
		Save_Data.mapfilters|=FILT_LWARROWS;
	m_pView->m_mapdlg.Invalidate();
	Refresh();

	
}

   
void MapFiltersRaids::OnClickedRafintercepts() 
{
	if (Save_Data.mapfilters[FILT_RAFINTERCEPTS])
		Save_Data.mapfilters%=FILT_RAFINTERCEPTS;
	else
		Save_Data.mapfilters|=FILT_RAFINTERCEPTS;
	m_pView->m_mapdlg.Invalidate();
	Refresh();

	
}

void MapFiltersRaids::OnClickedRafpatrols() 
{
	if (Save_Data.mapfilters[FILT_RAFPATROLS])
		Save_Data.mapfilters%=FILT_RAFPATROLS;
	else
		Save_Data.mapfilters|=FILT_RAFPATROLS;
	m_pView->m_mapdlg.Invalidate();
	Refresh();

	
}

void MapFiltersRaids::OnClickedRafroutelines() 
{
	if (		(Save_Data.mapfilters[FILT_RAFINTERCEPTS])
			&&	(Save_Data.mapfilters[FILT_RAFPATROLS])
			&&	(Save_Data.mapfilters[FILT_LWARROWS])
		)
	{
		Save_Data.mapfilters%=FILT_LWARROWS;
		Save_Data.mapfilters%=FILT_RAFPATROLS;
		Save_Data.mapfilters%=FILT_RAFINTERCEPTS;
	}else
	{
		Save_Data.mapfilters|=FILT_RAFPATROLS;
		Save_Data.mapfilters|=FILT_RAFINTERCEPTS;
		Save_Data.mapfilters|=FILT_LWARROWS;
	}
	m_pView->m_mapdlg.Invalidate();
	Refresh();

	
}
void MapFiltersRaids::OnOK() 
{
	CDialog::OnOK();
	
	m_pView->m_mapdlg.Invalidate();
	
}
void MapFiltersRaids::Refresh()
{
	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIO_PLOTS);
	pradio->Clear();
	pradio->AddButton(RESSTRING(AUTHENTICPLOTS));
	pradio->AddButton(RESSTRING(ICONSREP));
	pradio->AddButton(RESSTRING(ONEPLOTPERGESCHWADER));
	pradio->AddButton(RESSTRING(ONEPLOTPERGRUPPE));
	pradio->AddButton(RESSTRING(ONEPLOTPERSTAFFEL));
  	pradio->SetCurrentSelection((int)Save_Data.lwplots);


	CRButton* b;



	
	b = GETDLGITEM(IDC_LWARROWS);
	b->SetPressed(Save_Data.mapfilters[FILT_LWARROWS]);
	
	
	
	b = GETDLGITEM(IDC_RAFINTERCEPTS);
	b->SetPressed(Save_Data.mapfilters[FILT_RAFINTERCEPTS]);
	
	b = GETDLGITEM(IDC_RAFPATROLS);
	b->SetPressed(Save_Data.mapfilters[FILT_RAFPATROLS]);
	
	b = GETDLGITEM(IDC_RAFROUTELINES);
	if (		(Save_Data.mapfilters[FILT_RAFINTERCEPTS])
			&&	(Save_Data.mapfilters[FILT_RAFPATROLS])
			&&	(Save_Data.mapfilters[FILT_LWARROWS])
		)
			b->SetPressed(true);
	else
		b->SetPressed(false);
}

BOOL MapFiltersRaids::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Refresh();

	



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MapFiltersRaids::OnSelectedRradioPlots(long ButtonNum) 
{
	Save_Data.lwplots = (PlotLevels)ButtonNum;	
	m_pView->m_mapdlg.Invalidate();
	Refresh();

	
}