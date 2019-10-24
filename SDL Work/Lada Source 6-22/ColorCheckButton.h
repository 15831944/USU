// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This is the class that holds and displays each check for the graphs used
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
	CColorCheckButton();		// Constructor

// Attributes
public:
	int state;					// Checked or not
	COLORREF BColor;			// Which color
	CWnd *pParent;				// The parent
// Operations
public:
	void SetCheck(int nCheck);	// Sets the check to nCheck
	int GetCheck() const;		// Gets and returns the state of the check

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorCheckButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);	// Draws the item
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateButton(UINT Style, LPCTSTR buttonText, CRect &rect, CWnd *pParent, UINT nID, COLORREF color, BOOL s = TRUE, CFont *pFont = NULL);	// Creates the button
	virtual ~CColorCheckButton();	// Destructor
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CColorCheckButton)
	afx_msg void OnClicked();		// Called when a click occurs on the object
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORCHECKBUTTON_H__4D0D7A53_84CE_11D4_98E3_00A076801ACD__INCLUDED_)
