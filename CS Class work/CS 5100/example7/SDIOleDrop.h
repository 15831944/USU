// SDIOleDrop.h : main header file for the SDIOLEDROP application
//

#if !defined(AFX_SDIOLEDROP_H__41A55BA6_16B3_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_SDIOLEDROP_H__41A55BA6_16B3_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropApp:
// See SDIOleDrop.cpp for the implementation of this class
//

class CSDIOleDropApp : public CWinApp
{
public:
	CSDIOleDropApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIOleDropApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSDIOleDropApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIOLEDROP_H__41A55BA6_16B3_11D4_B398_00A0CC548BE4__INCLUDED_)
