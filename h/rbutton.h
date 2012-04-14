// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CRButton wrapper class

class CRButton : public CWnd
{
protected:
	DECLARE_DYNCREATE(CRButton)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x78918646, 0xa917, 0x11d6, { 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:
	OLE_COLOR GetForeColor();
	void SetForeColor(OLE_COLOR);
	CString GetCaption();
	void SetCaption(LPCTSTR);
	BOOL GetMovesParent();
	void SetMovesParent(BOOL);
	long GetFontNum();
	void SetFontNum(long);
	BOOL GetCloseButton();
	void SetCloseButton(BOOL);
	BOOL GetTickButton();
	void SetTickButton(BOOL);
	BOOL GetShowShadow();
	void SetShowShadow(BOOL);
	unsigned long GetShadowColor();
	void SetShadowColor(unsigned long);
	CString GetString();
	void SetString(LPCTSTR);
	long GetResourceNumber();
	void SetResourceNumber(long);
	long GetNormalFileNum();
	void SetNormalFileNum(long);
	long GetPressedFileNum();
	void SetPressedFileNum(long);
	CString GetNormalFileNumString();
	void SetNormalFileNumString(LPCTSTR);
	CString GetPressedFileNumString();
	void SetPressedFileNumString(LPCTSTR);
	BOOL GetUpdateCaption();
	void SetUpdateCaption(BOOL);
	BOOL GetPressed();
	void SetPressed(BOOL);
	BOOL GetDisabled();
	void SetDisabled(BOOL);
	BOOL GetTransparency();
	void SetTransparency(BOOL);
	long GetTransparentFileNum();
	void SetTransparentFileNum(long);
	BOOL GetHelpButton();
	void SetHelpButton(BOOL);
	CString GetHintString();
	void SetHintString(LPCTSTR);
	OLE_COLOR GetBackColor();
	void SetBackColor(OLE_COLOR);

// Operations
public:
};