#if !defined(AFX_RSPLTBARPPG_H__0542BF55_88DF_11D1_A1F0_444553540000__INCLUDED_)
#define AFX_RSPLTBARPPG_H__0542BF55_88DF_11D1_A1F0_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// RSpltBarPpg.h : Declaration of the CRSpltBarPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRSpltBarPropPage : See RSpltBarPpg.cpp.cpp for implementation.

class CRSpltBarPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRSpltBarPropPage)
	DECLARE_OLECREATE_EX(CRSpltBarPropPage)

// Constructor
public:
	CRSpltBarPropPage();

// Dialog Data
	//{{AFX_DATA(CRSpltBarPropPage)
	enum { IDD = IDD_PROPPAGE_RSPLTBAR };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRSpltBarPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSPLTBARPPG_H__0542BF55_88DF_11D1_A1F0_444553540000__INCLUDED)
