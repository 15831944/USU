// SquaresGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SquaresGame.h"
#include "SquaresGameDlg.h"
#include "SquareGame.h"
#include "NewGameDialog.h"
#include "BestScoresDialog.h"
#include "GameSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameDlg dialog

CSquaresGameDlg::CSquaresGameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSquaresGameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSquaresGameDlg)
	m_Player1Score = 0;
	m_Player2Score = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSquaresGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSquaresGameDlg)
	DDX_Control(pDX, IDC_PLAYER2, m_p2Text);
	DDX_Control(pDX, IDC_PLAYER1, m_p1Text);
	DDX_Text(pDX, IDC_PLAYER1_SCORE, m_Player1Score);
	DDX_Text(pDX, IDC_PLAYER2_SCORE, m_Player2Score);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSquaresGameDlg, CDialog)
	//{{AFX_MSG_MAP(CSquaresGameDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_FILE_NEWGAME, OnFileNewgame)
	ON_COMMAND(ID_FILE_BESTGAMES, OnFileBestgames)
	ON_COMMAND(ID_OPTIONS_GAMESIZE, OnOptionsGamesize)
	ON_COMMAND(ID_OPTIONS_PLAYER1COLOR, OnOptionsPlayer1color)
	ON_COMMAND(ID_OPTIONS_PLAYER2COLOR, OnOptionsPlayer2color)
	ON_COMMAND(ID_OPTIONS_SIDECOLOR, OnOptionsSidecolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameDlg message handlers

BOOL CSquaresGameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	game.CreateGame(this);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSquaresGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSquaresGameDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSquaresGameDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CSquaresGameDlg::OnFileExit() 
{
	// TODO: Add your command handler code here
	EndDialog(IDABORT);
}

void CSquaresGameDlg::OnFileNewgame() 
{
	// TODO: Add your command handler code here
	NewGameDialog nDlg;
	if (nDlg.DoModal() == IDOK)
	{
		game.gameSize = nDlg.m_GameSize;
		game.gameType = nDlg.m_GameType;
		game.CreateGame(this);
	}
}

void CSquaresGameDlg::OnFileBestgames() 
{
	// TODO: Add your command handler code here
	BestScoresDialog bDlg(&game);
	bDlg.DoModal();
}

void CSquaresGameDlg::OnOptionsGamesize() 
{
	// TODO: Add your command handler code here
	GameSizeDialog gDlg;
	if (gDlg.DoModal() == IDOK)
	{
		game.gameSize = gDlg.m_GameSize;
		game.CreateGame(this);
	}
}

void CSquaresGameDlg::OnOptionsPlayer1color() 
{
	// TODO: Add your command handler code here
	CColorDialog cDlg;
	cDlg.m_cc.rgbResult = game.playerColor[0];
	cDlg.m_cc.Flags |= CC_RGBINIT;
	if (cDlg.DoModal() == IDOK)
	{
		game.playerColor[0] = cDlg.GetColor();
		game.Refresh();
	}
}

void CSquaresGameDlg::OnOptionsPlayer2color() 
{
	// TODO: Add your command handler code here
	CColorDialog cDlg;
	cDlg.m_cc.rgbResult = game.playerColor[1];
	cDlg.m_cc.Flags |= CC_RGBINIT;
	if (cDlg.DoModal() == IDOK)
	{
		game.playerColor[1] = cDlg.GetColor();
		game.Refresh();
	}
}

void CSquaresGameDlg::OnOptionsSidecolor() 
{
	// TODO: Add your command handler code here
	CColorDialog cDlg;
	cDlg.m_cc.rgbResult = game.sideColor;
	cDlg.m_cc.Flags |= CC_RGBINIT;
	if (cDlg.DoModal() == IDOK)
	{
		game.sideColor = cDlg.GetColor();
		game.Refresh();
	}
}
