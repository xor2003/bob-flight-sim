/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()

//}}AFX_INCLUDES

*/
#if !defined(AFX_HINTBOX_H__3F900B41_43D7_11D2_A5A3_0040052179B6__INCLUDED_)
#define AFX_HINTBOX_H__3F900B41_43D7_11D2_A5A3_0040052179B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HintBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHintBox dialog

class CHintBox : public CDialog
{
// Construction
public:
	CHintBox(CWnd* pParent = NULL);   // standard constructor
	HWND	parentshandle;
// Dialog Data
	//{{AFX_DATA(CHintBox)
	enum { IDD = IDDS_HINTBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHintBox)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHintBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HINTBOX_H__3F900B41_43D7_11D2_A5A3_0040052179B6__INCLUDED_)

