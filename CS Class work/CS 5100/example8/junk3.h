// junk3.h : main header file for the JUNK3 application
//

#if !defined(AFX_JUNK3_H__797D85AA_BFA7_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_JUNK3_H__797D85AA_BFA7_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJunk3App:
// See junk3.cpp for the implementation of this class
//

class CJunk3App : public CWinApp
{
public:
	CJunk3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJunk3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CJunk3App)
	afx_msg void OnAppAbout();
	afx_msg void OnButton32771();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNK3_H__797D85AA_BFA7_11D4_B398_00A0CC548BE4__INCLUDED_)
