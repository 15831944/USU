// GraphForm.h : main header file for the GRAPHFORM application
//

#if !defined(AFX_GRAPHFORM_H__9601625C_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
#define AFX_GRAPHFORM_H__9601625C_63D3_11D4_98D7_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphFormApp:
// See GraphForm.cpp for the implementation of this class
//

class CGraphFormApp : public CWinApp
{
public:
	CGraphFormApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphFormApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CGraphFormApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHFORM_H__9601625C_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
