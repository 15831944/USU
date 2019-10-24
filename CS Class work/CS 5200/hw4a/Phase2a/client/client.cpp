// client.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "../common/confDlg.h"
#include "../common/DString.h"
#include "../common/Configuration.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	//{{AFX_MSG_MAP(CClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientApp construction

CClientApp::CClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CClientApp object

CClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CClientApp initialization

BOOL CClientApp::InitInstance()
{
	DString conf_file("c:\\DCS\\client.ini");

	CConfDlg conf_dlg;
	conf_dlg.setConfFile(conf_file);
	if (conf_dlg.DoModal()==IDOK)
		conf_file = conf_dlg.getConfFile();

	conf = new Configuration(conf_file);

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

	server_port = conf->getProfileUShort("Communications","Server_Port",12000);
	char buffer[MAX_CONFIG_VALUE_LENGTH+1];
	server_ip = "127.0.0.1";
	if (conf->getProfileString("Communications","Server_IP",buffer, MAX_CONFIG_VALUE_LENGTH))
		server_ip = buffer;

	CClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
