// SDIFileDrop.h : main header file for the SDIFILEDROP application
//

#if !defined(AFX_SDIFILEDROP_H__F9DC416A_121D_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_SDIFILEDROP_H__F9DC416A_121D_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropApp:
// See SDIFileDrop.cpp for the implementation of this class
//

class CSDIFileDropApp : public CWinApp
{
public:
	CSDIFileDropApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIFileDropApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSDIFileDropApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIFILEDROP_H__F9DC416A_121D_11D4_B398_00A0CC548BE4__INCLUDED_)
