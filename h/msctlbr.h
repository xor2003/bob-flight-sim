/*
//{{AFX_INCLUDES()
#include "rbutton.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_MSCTLBR_H__9EF0A801_2D49_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_MSCTLBR_H__9EF0A801_2D49_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MscTlbr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMiscToolbar dialog
struct	LWDirectivesResults;
struct	RAFDirectivesResults;
class CMiscToolbar : public CRToolBar
{	friend class	CMIGView;
// Construction
public:
	CMiscToolbar(CWnd* pParent = NULL);   // standard constructor
	enum	{THUMBNAIL, ZOOMLEVEL, DIRECTIVESTOGGLE,MAPFILTERS, FILES, DIRECTIVERESULTS, DIRECTIVES, ENDOFLIST,LISTLEN, CONTROL};

	void ChildDialClosed(int dialnum,RDialog*,int rv);
	void	OpenSaveOnly(bool quitafter);

	void OpenDirectivetoggle(LWDirectivesResults* dirres); 
	void OpenRAFDirectivetoggle(RAFDirectivesResults* dirres); 
	void OpenDirectiveResultsToggle(LWDirectivesResults* dirres); 
	void OpenEmptyDirectiveResults();
	void OpenRAFDirectiveResultsToggle(RAFDirectivesResults* dirres); 

// Dialog Data
	//{{AFX_DATA(CMiscToolbar)
	enum { IDD = IDDT_MISCTOOLBAR };
	CRButton	m_IDC_ZOOMIN;
	CRButton	m_IDC_ZOOMOUT;
	CRButton	m_IDC_REPLAY;
	CRButton	m_IDC_READYROOM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMiscToolbar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CRButton	m_dialids[LISTLEN];
protected:
	static int dialids[LISTLEN];
	// Generated message map functions
	//{{AFX_MSG(CMiscToolbar)
	afx_msg void OnClickedReplay();
	afx_msg void OnClickedReadyRoom();
	afx_msg void OnClickedZoomin();
	afx_msg void OnClickedZoomout();
	afx_msg void OnClickedThumbnail();
	afx_msg void OnClickedFiles();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClickedMapfilters();
	afx_msg void OnClickedDirectivetoggle();
	afx_msg void OnClickedTogglezoom();
	afx_msg void OnClickedZoomlevel();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSCTLBR_H__9EF0A801_2D49_11D2_A5A3_0040052179B6__INCLUDED_)
