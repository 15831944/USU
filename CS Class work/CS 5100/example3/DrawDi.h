// DrawDi.h : main header file for the DRAWDI application
//

#if !defined(AFX_DRAWDI_H__539863B5_0724_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_DRAWDI_H__539863B5_0724_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawDiApp:
// See DrawDi.cpp for the implementation of this class
//

class CDrawDiApp : public CWinApp
{
public:
	CDrawDiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawDiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDrawDiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDI_H__539863B5_0724_11D4_B398_00A0CC548BE4__INCLUDED_)
