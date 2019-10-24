// SquaresGame.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SquaresGame.h"
#include "SquaresGameDlg.h"
#include "NewGameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameApp

BEGIN_MESSAGE_MAP(CSquaresGameApp, CWinApp)
	//{{AFX_MSG_MAP(CSquaresGameApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameApp construction

CSquaresGameApp::CSquaresGameApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSquaresGameApp object

CSquaresGameApp theApp;
CFont BoldFont;
CFont NormalFont;

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameApp initialization

BOOL CSquaresGameApp::InitInstance()
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

	BoldFont.CreateFont(16,0,0,0,FW_BOLD,0,0,0,DEFAULT_CHARSET,0,0,0,0,"MS Sans Serif");
	NormalFont.CreateFont(16,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,0,0,"MS Sans Serif");

	NewGameDialog nDlg;
	if (nDlg.DoModal() == IDOK)
	{
		CSquaresGameDlg dlg;
		dlg.game.gameSize = nDlg.m_GameSize;
		dlg.game.gameType = nDlg.m_GameType;
		m_pMainWnd = &dlg;
		dlg.DoModal();		
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
