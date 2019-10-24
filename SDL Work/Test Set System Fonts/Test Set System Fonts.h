// Test Set System Fonts.h : main header file for the TEST SET SYSTEM FONTS application
//

#if !defined(AFX_TESTSETSYSTEMFONTS_H__DFB03A84_853F_11D5_B021_805871C45726__INCLUDED_)
#define AFX_TESTSETSYSTEMFONTS_H__DFB03A84_853F_11D5_B021_805871C45726__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestSetSystemFontsApp:
// See Test Set System Fonts.cpp for the implementation of this class
//

class CTestSetSystemFontsApp : public CWinApp
{
public:
	CTestSetSystemFontsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSetSystemFontsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestSetSystemFontsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSETSYSTEMFONTS_H__DFB03A84_853F_11D5_B021_805871C45726__INCLUDED_)
