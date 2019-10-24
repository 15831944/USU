// String Editor.h : main header file for the STRING EDITOR application
//

#if !defined(AFX_STRINGEDITOR_H__16E7BB87_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
#define AFX_STRINGEDITOR_H__16E7BB87_9EBD_11D4_98E8_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStringEditorApp:
// See String Editor.cpp for the implementation of this class
//

class CStringEditorApp : public CWinApp
{
public:
	CStringEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStringEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CStringEditorApp)
	afx_msg void OnAppAbout();
	afx_msg void OnMerge();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGEDITOR_H__16E7BB87_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
