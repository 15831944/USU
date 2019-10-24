// LADADIAGDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "LADADIAG.h"
#include "LADADIAGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLADADIAGDlg dialog

CLADADIAGDlg::CLADADIAGDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLADADIAGDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLADADIAGDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLADADIAGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLADADIAGDlg)
	DDX_Control(pDX, IDC_DIAGNOSTICLIST, m_DiagnosticList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLADADIAGDlg, CDialog)
	//{{AFX_MSG_MAP(CLADADIAGDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, OnStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADADIAGDlg message handlers

BOOL CLADADIAGDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);
	/*
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
	*/
	
	//commobject=new CCommOperations(TRUE);
	DiagnosticList.Create( IDB_BITMAP1, 16, 0, RGB(255,255,255) );
	m_DiagnosticList.SetImageList(&DiagnosticList,LVSIL_SMALL);
	m_DiagnosticList.InsertColumn(0,"Function",LVCFMT_LEFT,181,1);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLADADIAGDlg::OnPaint() 
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
HCURSOR CLADADIAGDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CLADADIAGDlg::SetStatus(int whichTest, BOOL passed)
{
	CString s;
	//s.LoadString(IDS_STRING103+whichTest);
	s = "Doggy";
	m_DiagnosticList.InsertItem(whichTest,s,passed);
	UpdateData(FALSE);
}

void CLADADIAGDlg::OnInit()
{
	m_DiagnosticList.DeleteAllItems();
	SetStatus(0,CheckVoltage());
	SetStatus(1,CheckMemory());
	SetStatus(2,CheckUploadTime());
	SetStatus(3,CheckMultiplexerPower());
	SetStatus(4,CheckVoltageChannels());
	SetStatus(5,CheckGrowthPower());
	SetStatus(6,CheckReadSensors());
	SetStatus(7,CheckSoilProbe());

}

bool CLADADIAGDlg::CheckVoltage()
{
	return true;
}


bool CLADADIAGDlg::CheckMemory()
{
	return true;
}

bool CLADADIAGDlg::CheckUploadTime()
{
	return true;
}

bool CLADADIAGDlg::CheckMultiplexerPower()
{
	MessageBox("Turn on MultiplexerPower",NULL,MB_OK);
	return true;
}

bool CLADADIAGDlg::CheckVoltageChannels()
{
	return true;
}

bool CLADADIAGDlg::CheckGrowthPower()
{
	return true;
}

bool CLADADIAGDlg::CheckReadSensors()
{
	return true;
}

bool CLADADIAGDlg::CheckSoilProbe()
{
	return false;
}

void CLADADIAGDlg::OnStart() 
{
	OnInit();	
}
