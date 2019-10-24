// Lecture24.h : main header file for the LECTURE24 application
//

#if !defined(AFX_LECTURE24_H__B88C61FC_D619_11D2_A4B8_00409505AA4A__INCLUDED_)
#define AFX_LECTURE24_H__B88C61FC_D619_11D2_A4B8_00409505AA4A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLecture24App:
// See Lecture24.cpp for the implementation of this class
//

class CLecture24App : public CWinApp
{
public:
	CLecture24App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLecture24App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLecture24App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LECTURE24_H__B88C61FC_D619_11D2_A4B8_00409505AA4A__INCLUDED_)
