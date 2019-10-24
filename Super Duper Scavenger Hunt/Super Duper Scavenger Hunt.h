// Super Duper Scavenger Hunt.h : main header file for the SUPER DUPER SCAVENGER HUNT application
//

#if !defined(AFX_SUPERDUPERSCAVENGERHUNT_H__EACAA504_53B6_11D5_A51E_444553540000__INCLUDED_)
#define AFX_SUPERDUPERSCAVENGERHUNT_H__EACAA504_53B6_11D5_A51E_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntApp:
// See Super Duper Scavenger Hunt.cpp for the implementation of this class
//

class CSuperDuperScavengerHuntApp : public CWinApp
{
public:
	CSuperDuperScavengerHuntApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperDuperScavengerHuntApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSuperDuperScavengerHuntApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERDUPERSCAVENGERHUNT_H__EACAA504_53B6_11D5_A51E_444553540000__INCLUDED_)
