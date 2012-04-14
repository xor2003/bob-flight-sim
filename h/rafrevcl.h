/* STOP AFX_INCLUDES
//{{AFX_INCLUDES()
#include "rlistbox.h"
//}}AFX_INCLUDES
*/
#if !defined(AFX_RAFREVCL_H__D01BCB60_A1A3_11D3_8ADC_00A0D21BD395__INCLUDED_)
#define AFX_RAFREVCL_H__D01BCB60_A1A3_11D3_8ADC_00A0D21BD395__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RAFRevCl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RAFReviewClaims dialog

class RAFReviewClaims : public RowanDialog
{
// Construction
public:
	static RDialog* Make();

	RAFReviewClaims(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(RAFReviewClaims)
	enum { IDD = IDD_RAFREVIEWCLAIMS };
	CRListBox	m_IDC_RLISTBOXCTRL1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RAFReviewClaims)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(RAFReviewClaims)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RAFREVCL_H__D01BCB60_A1A3_11D3_8ADC_00A0D21BD395__INCLUDED_)
