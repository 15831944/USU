/*****************************************************************************
*
*  File:          TestPackageDlg.cpp
*  Class:         TestPackageDlg
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
#include "../common/DString.h"
#include "../common/Event.h"
#include "../common/Configuration.h"
#include "../common/strdup.h"
#include "../common/ComChannel.h"
#include "../server/ServerComChannel.h"
#include "../client/ClientComChannel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CTestPackageDlg::CTestPackageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPackageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPackageDlg)
	m_test_DString = FALSE;
	m_test_Event = FALSE;
	m_test_Configuration = FALSE;
	m_test_strdup = FALSE;
	m_test_ComChannel = FALSE;
	m_test_ClientComChannel = FALSE;
	m_test_ServerComChannel = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestPackageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPackageDlg)
	DDX_Control(pDX, IDC_MESSAGE_LOG, m_ctl_log);
	DDX_Check(pDX, IDC_TEST_DSTRING, m_test_DString);
	DDX_Check(pDX, IDC_TEST_EVENT, m_test_Event);
	DDX_Check(pDX, IDC_TEST_CONFIGURATION, m_test_Configuration);
	DDX_Check(pDX, IDC_TEST_STRDUP, m_test_strdup);
	DDX_Check(pDX, IDC_TEST_COMCHANNEL, m_test_ComChannel);
	DDX_Check(pDX, IDC_TEST_CLIENT_COM_CHANNEL, m_test_ClientComChannel);
	DDX_Check(pDX, IDC_TEST_SERVER_COM_CHANNEL, m_test_ServerComChannel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestPackageDlg, CDialog)
	//{{AFX_MSG_MAP(CTestPackageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST_BUTTON, OnTestButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPackageDlg message handlers

BOOL CTestPackageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestPackageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestPackageDlg::OnPaint() 
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
HCURSOR CTestPackageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestPackageDlg::OnTestButton() 
{
	bool ok=TRUE;

	UpdateData(TRUE);

	DisplayMessage("Starting\r\n");

	try
	{
		if (m_test_DString)
		{
			DString::test1();
			DString::test2();
			DString::test3();
			DString::test4();
			DString::test5();
			DString::test6();
		}

		if (m_test_Event)
		{
			Event::test1();
			Event::test2();
			Event::test3();
			Event::test4();
			Event::test5();
			Event::test6();
		}

		if (m_test_Configuration)
		{
			Configuration::test1();
			Configuration::test2();
			Configuration::test3();
		}

		if (m_test_strdup)
		{
			strdup_test1();
		}

		if (m_test_ComChannel)
		{
			ComChannel::test1();
			ComChannel::test2();
			ComChannel::test3();
		}

		if (m_test_ServerComChannel)
		{
			ServerComChannel::test1();
			ServerComChannel::test2();
			ServerComChannel::test3();
		}

		if (m_test_ClientComChannel)
		{
			ClientComChannel::test1();
			ClientComChannel::test2();
			ClientComChannel::test3();
		}

	}
	catch(...)
	{
		ok=FALSE;
	}

	if (ok)
		DisplayMessage("Testing Complete\r\n");
	else
		DisplayMessage("An unexpected exception occurred\r\n");
}

void CTestPackageDlg::OnOK() 
{
	CDialog::OnOK();
}

void CTestPackageDlg::DisplayMessage(const CString &msg)
{
    m_ctl_log.ReplaceSel(msg);
}
