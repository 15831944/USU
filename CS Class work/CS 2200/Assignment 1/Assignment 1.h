// Assignment 1.h : main header file for the ASSIGNMENT 1 application
//

#if !defined(AFX_ASSIGNMENT1_H__D80EA378_4248_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_ASSIGNMENT1_H__D80EA378_4248_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAssignment1App:
// See Assignment 1.cpp for the implementation of this class
//

class CAssignment1App : public CWinApp
{
public:
	CAssignment1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssignment1App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAssignment1App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSIGNMENT1_H__D80EA378_4248_11D4_98D1_00A076801ACD__INCLUDED_)
