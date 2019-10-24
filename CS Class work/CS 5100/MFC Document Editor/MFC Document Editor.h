// MFC Document Editor.h : main header file for the MFC DOCUMENT EDITOR application
//

#if !defined(AFX_MFCDOCUMENTEDITOR_H__D0AAD2F6_F86F_4E9D_B2E8_C245F0A386B0__INCLUDED_)
#define AFX_MFCDOCUMENTEDITOR_H__D0AAD2F6_F86F_4E9D_B2E8_C245F0A386B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorApp:
// See MFC Document Editor.cpp for the implementation of this class
//

class CMFCDocumentEditorApp : public CWinApp
{
public:
	CMFCDocumentEditorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDocumentEditorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMFCDocumentEditorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDOCUMENTEDITOR_H__D0AAD2F6_F86F_4E9D_B2E8_C245F0A386B0__INCLUDED_)
