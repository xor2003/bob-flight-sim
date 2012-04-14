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

// RowanDialog: // LWDiary.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"
#include "LWDiary.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWDiary dialog

#ifndef	BOB_DEMO_VER
RDialog*	LWDiary::Make(SquadNum squad)
{
	LWDiary* lwdiary  = new LWDiary();

	lwdiary->grnum = squad;
	lwdiary->grnumptr = &lwdiary->grnum;

	lwdiary->currentryptr = &lwdiary->currentry;
	lwdiary->grdetailsptr = lwdiary->grdetails; 
	lwdiary->FindGeschwader();
	lwdiary->FillGruppeDetails(squad,NULL,lwdiary->grdetailsptr,*lwdiary->currentryptr);





	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
		DialList(DialBox(FIL_D_GRUPPEN_LOGBOOK,lwdiary),
						DialBox(FIL_D_GRUPPEN_LOGBOOK,new LWDiaryList(lwdiary->grnumptr, lwdiary->currentryptr, lwdiary->grdetailsptr)),
						DialBox(FIL_D_GRUPPEN_LOGBOOK,new LWDiaryDetails(lwdiary->grnumptr, lwdiary->currentryptr, lwdiary->grdetailsptr, false))
					)
			);
}
#endif

LWDiary::LWDiary(CWnd* pParent /*=NULL*/)
	: RowanDialog(LWDiary::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWDiary)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	//Keep current gruppen number in groupnum
	groupnum=0;
}

void	LWDiary::RefreshData(int effect)
{
//		for (RowanDialog* ctl=(RowanDialog*)fchild;ctl;ctl=(RowanDialog*)ctl->sibling)
			RowanDialog*	dlist=(RowanDialog*)fchild;		//ac num 
			RowanDialog*	ddet=(RowanDialog*)dlist->sibling;		//ac num 
	switch (effect)
	{
		case 0:
		case 1:
		{
			CRect parentpos;
			GetWindowRect(parentpos);
			CPoint parentoff(parentpos.left,parentpos.top);
			CRect dlistpos;
			dlist->GetWindowRect(dlistpos);
			CRect ddetpos;
			ddet->GetWindowRect(ddetpos);
			dlistpos-=parentoff;
			ddetpos-=parentoff;
			dlist->MoveWindow(ddetpos);
			ddet->MoveWindow(dlistpos);
			if (parentoff.x>0)
				dlist->RefreshData(groupnum);
			else
				ddet->RefreshData(groupnum);
			break;
		}
		case 2:
		{
			FindGeschwader();
//DeadCode JIM 13Oct00 			FillGruppeDetails(grdetails[0]);
			Refresh();
			dlist->RefreshData(groupnum);
			ddet->RefreshData(groupnum);

			break;
		}
	}

}

void LWDiary::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWDiary)
	DDX_Control(pDX, IDC_RCOMBOGROUP, m_IDC_RCOMBOGROUP);
	DDX_Control(pDX, IDC_RCOMBOGESCHWADER, m_IDC_RCOMBOGESCHWADER);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWDiary, CDialog)
	//{{AFX_MSG_MAP(LWDiary)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWDiary message handlers

void	LWDiary::FindGeschwader()
{
	geschwadertype = 0;
//DeadCode JIM 13Oct00  	int j=0, i = 0;
//DeadCode JIM 13Oct00  	while (		(Node_Data.gruppe[i].squadron != SQ_ZERO)
//DeadCode JIM 13Oct00  			&&	(j < MAX_GRUPPE)			
//DeadCode JIM 13Oct00  		  )
 	{
//DeadCode JIM 13Oct00  		if(*grnumptr == Node_Data.gruppe[i].squadron)
 		{
			int wader = GruppenPtr(Node_Data[*grnumptr])->wadernum;
 			geschwadertype = Node_Data.geschwader[wader].wadername;
//DeadCode JIM 13Oct00  			break;
 		}
//DeadCode JIM 13Oct00  	  i++;
 	 }
 

}
void	LWDiary::FillList()
{

	int j=0, i = 0;
	while (		(Node_Data.gruppe[i].squadron != SQ_ZERO)
			&&	(j < MAX_GRUPPE)			
		  )
	{
		int wader = Node_Data.gruppe[i].wadernum;
		if  (geschwadertype == 	Node_Data.geschwader[wader].wadername)
		{
			Gruppe[j] = i;
			j++;
		}
	  i++;
	 }
	maxsquads = j;

}





void LWDiary::Refresh()
{
	
	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOGROUP);
	combo->Clear()->RESCOMBO(JAGD,4)->
	SetIndex(geschwadertype);

	FillList();

	combo=GETDLGITEM(IDC_RCOMBOGESCHWADER);
	combo->Clear();
	
	int index = 0;
	for (int i = 0; i < maxsquads; i++)
	{
		Squadron* sq = &Node_Data.gruppe[Gruppe[i]];
		CString name = sq->ShortName() + "/";
		name = name + sq->SubName();
		combo->AddString(name);

		if(grnum == Node_Data.gruppe[Gruppe[i]].squadron)
			index = i;

	}

	combo->SetIndex(index);


}

BOOL LWDiary::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	FillList();

	Refresh();	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



BEGIN_EVENTSINK_MAP(LWDiary, CDialog)
    //{{AFX_EVENTSINK_MAP(LWDiary)
	ON_EVENT(LWDiary, IDC_RCOMBOGROUP, 1 /* TextChanged */, OnTextChangedRcombogroup, VTS_BSTR VTS_I2)
	ON_EVENT(LWDiary, IDC_RCOMBOGESCHWADER, 1 /* TextChanged */, OnTextChangedRcombogeschwader, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()



void LWDiary::FillGruppeDetails(SquadNum grnum,SquadronBase* currrecord,SquadronBase** grdetails,int& currentry)
{
 	SquadronBase*	grentry = Squad_Diary.FindLast(grnum);
 
 	int i = 0;
	currentry = -1;

  	while (	(i < MAX_SQDETAILS) && (grentry))
  	{
  		grdetails[i] = grentry;
		if (grentry==currrecord)
			currentry=i;
  		grentry = Squad_Diary.FindPrev(grentry);
  		i++;
  	}
 	if (currentry==-1 && i>0)
	{
 		currentry = 0;
		if (currrecord)
			INT3;
	}
 
//DeadCode JIM 23Oct00   	while (i < MAX_SQDETAILS)
//DeadCode JIM 23Oct00   	{
  		grdetails[i++] = NULL;
//DeadCode JIM 23Oct00   	}

}




void LWDiary::OnTextChangedRcombogroup(LPCTSTR text, short index) 
{
	geschwadertype = index;

	Refresh();
	RowanDialog*	dlist=(RowanDialog*)fchild;		//ac num 
	RowanDialog*	ddet=(RowanDialog*)dlist->sibling;		//ac num 

	grnum = Node_Data.gruppe[Gruppe[0]].squadron;	

	FillGruppeDetails(grnum,NULL,grdetails,currentry);
	dlist->RefreshData(0);
	ddet->RefreshData(0);

	
}




void LWDiary::OnTextChangedRcombogeschwader(LPCTSTR Caption, short index) 
{
	grnum = Node_Data.gruppe[Gruppe[index]].squadron;	
	FillGruppeDetails(grnum,NULL,grdetails,currentry);

	RowanDialog*	dlist=(RowanDialog*)fchild;		//ac num 
	RowanDialog*	ddet=(RowanDialog*)dlist->sibling;		//ac num 
	dlist->RefreshData(0);
	ddet->RefreshData(0);
	
}
