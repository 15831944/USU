// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog displays the information gathered in checkout
#if !defined(AFX_DISPLAY_H__0B3867BB_BD75_11D4_B962_00A0C91ACD53__INCLUDED_)
#define AFX_DISPLAY_H__0B3867BB_BD75_11D4_B962_00A0C91ACD53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Display.h : header file
//
#include "checkout.h"

/////////////////////////////////////////////////////////////////////////////
// Display dialog

class Display : public CDialog
{
// Construction
public:
	CCheckout* print;									// contains the information from checkout
	Display(CCheckout* prin=NULL,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(Display)
	enum { IDD = IDD_DISPLAY };
	CListCtrl	m_display;								// The control for the List
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Display)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Display)
	virtual BOOL OnInitDialog();						// Does all the initialization
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAY_H__0B3867BB_BD75_11D4_B962_00A0C91ACD53__INCLUDED_)
