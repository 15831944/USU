// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_CUSTOMBITMAPBUTTON_H__117A1793_993F_11D4_98E8_00A076801ACD__INCLUDED_)
#define AFX_CUSTOMBITMAPBUTTON_H__117A1793_993F_11D4_98E8_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomBitmapButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomBitmapButton window

class CCustomBitmapButton : public CButton
{
// Construction
public:
	CCustomBitmapButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomBitmapButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCustomBitmapButton();
	BOOL LoadBitmaps(LPCTSTR lpszBitmapResource,
		LPCTSTR lpszBitmapResourceSel, LPCTSTR lpszBitmapResourceFocus,
		LPCTSTR lpszBitmapResourceDisabled);
	virtual void SizeToContent();
	virtual BOOL AutoLoad(UINT nID, CWnd* pParent);
	void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID);
	void SetStyle(DWORD style);
	// Generated message map functions
protected:
	DWORD m_Style;
	//{{AFX_MSG(CCustomBitmapButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	CBitmap m_bitmap;
	CBitmap m_bitmapSel;
	CBitmap m_bitmapFocus;
	CBitmap m_bitmapDisabled;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMBITMAPBUTTON_H__117A1793_993F_11D4_98E8_00A076801ACD__INCLUDED_)
