/*****************************************************************************
*
*  File:          TestPackage.cpp
*  Class:         TestPackage
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*
*/

#include "stdafx.h"
#include "TestPackage.h"
#include "TestPackageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPackageApp

BEGIN_MESSAGE_MAP(CTestPackageApp, CWinApp)
	//{{AFX_MSG_MAP(CTestPackageApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPackageApp construction

CTestPackageApp::CTestPackageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestPackageApp object

CTestPackageApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestPackageApp initialization

BOOL CTestPackageApp::InitInstance()
{
	WSADATA socket_parameters;

	if (!AfxSocketInit(&socket_parameters))
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

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

	CTestPackageDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CTestPackageApp::DisplayMessage(const CString &msg)
{
	if (m_pMainWnd)
		((CTestPackageDlg*) m_pMainWnd)->DisplayMessage(msg);
}
