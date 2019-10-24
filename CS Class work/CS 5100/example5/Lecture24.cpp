// Lecture24.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Lecture24.h"
#include "Lecture24Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLecture24App

BEGIN_MESSAGE_MAP(CLecture24App, CWinApp)
	//{{AFX_MSG_MAP(CLecture24App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLecture24App construction

CLecture24App::CLecture24App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLecture24App object

CLecture24App theApp;

/////////////////////////////////////////////////////////////////////////////
// CLecture24App initialization

BOOL CLecture24App::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CLecture24Dlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_fileName = "<Type the file name here.>";
	dlg.m_fileContents = "";
	int nResponse = dlg.DoModal();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
