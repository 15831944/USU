// ScheduleX.h : main header file for the SCHEDULEX application
//

#if !defined(AFX_SCHEDULEX_H__D058DDF5_0971_11D3_9C61_00A0CC3A1AD6__INCLUDED_)
#define AFX_SCHEDULEX_H__D058DDF5_0971_11D3_9C61_00A0CC3A1AD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScheduleXApp:
// See ScheduleX.cpp for the implementation of this class
//

class CScheduleXApp : public CWinApp
{
public:
	CScheduleXApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleXApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScheduleXApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULEX_H__D058DDF5_0971_11D3_9C61_00A0CC3A1AD6__INCLUDED_)
