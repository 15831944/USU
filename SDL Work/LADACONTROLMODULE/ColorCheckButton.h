#if !defined(AFX_COLORCHECKBUTTON_H__4D0D7A53_84CE_11D4_98E3_00A076801ACD__INCLUDED_)
#define AFX_COLORCHECKBUTTON_H__4D0D7A53_84CE_11D4_98E3_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorCheckButton.h : header file
//

#ifndef __AFXEXT_H__
#ifdef _RAPID_TRANSLATION
#undef CString
#include<afxext.h>
#define CString __X_CString
#else
#include<afxext.h>
#endif
#endif

#define		SPACE_1		2
#define		SPACE_2		1
/////////////////////////////////////////////////////////////////////////////
// CColorCheckButton window

class CColorCheckButton : public CButton
{
// Construction
public:
	CColorCheckButton();

// Attributes
public:
	int state;
	COLORREF BColor;
	CWnd *pParent;
// Operations
public:
	void SetCheck(int nCheck);
	int GetCheck() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorCheckButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateButton(LPCTSTR buttonText, CRect &rect, CWnd *pParent, UINT nID, COLORREF color, BOOL s = TRUE, CFont *pFont = NULL);
	virtual ~CColorCheckButton();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CColorCheckButton)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHECKBUTTON_H__4D0D7A53_84CE_11D4_98E3_00A076801ACD__INCLUDED_)
