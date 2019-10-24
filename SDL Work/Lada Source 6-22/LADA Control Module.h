// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LADA Control Module.h : main header file for the LADA CONTROL MODULE application
//

#if !defined(AFX_LADACONTROLMODULE_H__B5A7CF99_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_LADACONTROLMODULE_H__B5A7CF99_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <mmsystem.h>
#include "CommOperations.h"

#define MAX_INPUT_LOCATIONS		256
#define ENGLISH_FILE_ID			1033
#define RUSSIAN_FILE_ID			25
#define ENGLISH					0
#define RUSSIAN					1
#define UNKNOWN_LANGUAGE		0
#define WM_SWITCH_LANGUAGE		(WM_USER + 1)
#define NO_TITLE				0xFFFFFFFF
#define NO_STRING				0xFFFFFFFF

#define FontSizeSmall			12
#define FontSizeMedium			18
#define FontSizeLarge			24
#define FontSizeHuge			30
#define ErrorExtension			"log"
#define	HistoryExtension		"hst"
#define InputLocationExtension	"il"
#define FinalStorageExtension	"fs"
#define FSLabelExtension		"fsl"
#define DibExtension			"dib"
#define JpgExtension			"jpg"

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleApp:
// See LADA Control Module.cpp for the implementation of this class


class CLADAControlModuleApp : public CWinApp
{
public:
	virtual afx_msg void OnFileOpen();
	CLADAControlModuleApp();
	CString GetLastFile();
	HANDLE mHandle;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADAControlModuleApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLADAControlModuleApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADACONTROLMODULE_H__B5A7CF99_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
