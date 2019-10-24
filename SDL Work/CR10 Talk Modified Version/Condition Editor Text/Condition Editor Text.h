// Condition Editor Text.h : main header file for the CONDITION EDITOR TEXT application
//

#if !defined(AFX_CONDITIONEDITORTEXT_H__0044F5FA_46BB_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_CONDITIONEDITORTEXT_H__0044F5FA_46BB_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CConditionEditorTextApp:
// See Condition Editor Text.cpp for the implementation of this class
//

class CConditionEditorTextApp : public CWinApp
{
public:
	CConditionEditorTextApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConditionEditorTextApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConditionEditorTextApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONDITIONEDITORTEXT_H__0044F5FA_46BB_11D4_98D1_00A076801ACD__INCLUDED_)
