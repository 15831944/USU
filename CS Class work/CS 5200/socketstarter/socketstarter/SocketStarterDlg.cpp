// SocketStarterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SocketStarter.h"
#include "SocketStarterDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocketStarterDlg dialog

CSocketStarterDlg::CSocketStarterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSocketStarterDlg::IDD, pParent),
      m_pActiveStreamDlg(NULL),
      m_pPassiveStreamDlg(NULL),
      m_pDatagramDlg(NULL)
{
	//{{AFX_DATA_INIT(CSocketStarterDlg)
	m_connectionType = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketStarterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSocketStarterDlg)
	DDX_Radio(pDX, IDC_RADIO_ACTIVE, m_connectionType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSocketStarterDlg, CDialog)
	//{{AFX_MSG_MAP(CSocketStarterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocketStarterDlg message handlers

BOOL CSocketStarterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void CSocketStarterDlg::OnPaint() 
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
HCURSOR CSocketStarterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSocketStarterDlg::OnOK() 
{
	int retval=0;

	UpdateData(TRUE);

	switch(m_connectionType)
	{
	case 0: 
        {
            if (m_pActiveStreamDlg==NULL)
            {
                m_pActiveStreamDlg = new CActiveStreamDlg(this);
                m_pActiveStreamDlg->Create();
                m_pActiveStreamDlg->ShowWindow(SW_SHOW);
            }
            else
                m_pActiveStreamDlg->SetActiveWindow();
		    break;
        }
	case 1: 
        {
            if (m_pPassiveStreamDlg==NULL)
            {
                m_pPassiveStreamDlg = new CPassiveStreamDlg(this);
                m_pPassiveStreamDlg->Create();
                m_pPassiveStreamDlg->ShowWindow(SW_SHOW);
            }
		    else
                m_pPassiveStreamDlg->SetActiveWindow();
		    break;
        }
	case 2: 
        {
            if (m_pDatagramDlg==NULL)
            {
                m_pDatagramDlg = new CDatagramDlg(this);
                m_pDatagramDlg->Create();
                m_pDatagramDlg->ShowWindow(SW_SHOW);
            }
		    else
                m_pDatagramDlg->SetActiveWindow();
		    break;
        }
	}
	
}
