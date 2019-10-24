// Super Duper Scavenger Hunt.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Super Duper Scavenger Hunt.h"
#include "Super Duper Scavenger HuntDlg.h"
#include "Welcome.h"
#include "Instructions1Dlg.h"
#include "Instructions2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntApp

BEGIN_MESSAGE_MAP(CSuperDuperScavengerHuntApp, CWinApp)
	//{{AFX_MSG_MAP(CSuperDuperScavengerHuntApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntApp construction

CSuperDuperScavengerHuntApp::CSuperDuperScavengerHuntApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSuperDuperScavengerHuntApp object

CSuperDuperScavengerHuntApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntApp initialization

BOOL CSuperDuperScavengerHuntApp::InitInstance()
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

	CWelcome dlg1;
	if (dlg1.DoModal()!=IDOK)
		return FALSE;

	CInstructions1Dlg dlg2;
	dlg2.DoModal();

	CInstructions2Dlg dlg3;
	dlg3.DoModal();

	CSuperDuperScavengerHuntDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
