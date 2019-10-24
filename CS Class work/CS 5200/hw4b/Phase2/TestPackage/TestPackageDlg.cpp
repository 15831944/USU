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
#include "../common/Location.h"
#include "../common/Configuration.h"
#include "../common/strdup.h"
#include "../common/ComChannel.h"
#include "../common/Building.h"
#include "../common/TimeOfDay.h"
#include "../common/TimeBlock.h"
#include "../common/ReservedTime.h"
#include "../common/MeetingPreference.h"
#include "../common/CalendarDate.h"
#include "../common/Calendar.h"
#include "../common/User.h"
#include "../common/PersistentObjectSet.h"
#include "../common/SockAddr.h"
#include "../common/LogicalClock.h"
#include "../common/Message.h"
#include "../common/RequestReply.h"
#include "../common/Request.h"
#include "../common/Reply.h"
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
	m_test_Building = FALSE;
	m_test_TimeOfDay = FALSE;
	m_test_Calendar = FALSE;
	m_test_CalendarDate = FALSE;
	m_test_TimeBlock = FALSE;
	m_test_User = FALSE;
	m_test_Location = FALSE;
	m_test_ReservedTime = FALSE;
	m_test_PersistentObjectSet = FALSE;
	m_test_LogicalClock = FALSE;
	m_test_SocketAddress = FALSE;
	m_test_Message = FALSE;
	m_test_MeetingPreference = FALSE;
	m_test_Reply = FALSE;
	m_test_Request = FALSE;
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
	DDX_Check(pDX, IDC_TEST_BUILDING, m_test_Building);
	DDX_Check(pDX, IDC_TEST_TIMEOFDAY, m_test_TimeOfDay);
	DDX_Check(pDX, IDC_TEST_CALENDAR, m_test_Calendar);
	DDX_Check(pDX, IDC_TEST_CALENDARDATE, m_test_CalendarDate);
	DDX_Check(pDX, IDC_TEST_TIMEBLOCK, m_test_TimeBlock);
	DDX_Check(pDX, IDC_TEST_USER, m_test_User);
	DDX_Check(pDX, IDC_TEST_LOCATION, m_test_Location);
	DDX_Check(pDX, IDC_TEST_RESERVEDTIME, m_test_ReservedTime);
	DDX_Check(pDX, IDC_TEST_PERSISTENTOBJECTSET, m_test_PersistentObjectSet);
	DDX_Check(pDX, IDC_TEST_LOGICALCLOCK, m_test_LogicalClock);
	DDX_Check(pDX, IDC_TEST_SOCKADDR, m_test_SocketAddress);
	DDX_Check(pDX, IDC_TEST_MESSAGE, m_test_Message);
	DDX_Check(pDX, IDC_TEST_MEETINGPREFERENCE, m_test_MeetingPreference);
	DDX_Check(pDX, IDC_TEST_REPLY, m_test_Reply);
	DDX_Check(pDX, IDC_TEST_REQUEST, m_test_Request);
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
		if (m_test_strdup) strdup_test1();
		if (m_test_DString) DString::run_tests();
		if (m_test_TimeOfDay) TimeOfDay::run_tests();
		if (m_test_CalendarDate) CalendarDate::run_tests();
		if (m_test_TimeBlock) TimeBlock::run_tests();
		if (m_test_ReservedTime) ReservedTime::run_tests();
		if (m_test_MeetingPreference) MeetingPreference::run_tests();
		if (m_test_Calendar) Calendar::run_tests();
		if (m_test_Building) Building::run_tests();
		if (m_test_Event) Event::run_tests();
		if (m_test_Location) Location::run_tests();
		if (m_test_User) User::run_tests();
		if (m_test_PersistentObjectSet) PersistentObjectSet_run_tests();
		if (m_test_SocketAddress) SocketAddress::run_tests();
		if (m_test_ComChannel) ComChannel::run_tests();
		if (m_test_ServerComChannel) ServerComChannel::run_tests();
		if (m_test_ClientComChannel) ClientComChannel::run_tests();
		if (m_test_Configuration) Configuration::run_tests();
		if (m_test_LogicalClock) LogicalClock::run_tests();
		if (m_test_Message) Message::run_tests();
		if (m_test_Request)
		{
			LoginRequest::run_tests();
			TerminateRequest::run_tests();
		}
		if (m_test_Reply)
		{
			ObjectReply::run_tests();
			CountReply::run_tests();
			AckReply::run_tests();
			ErrorReply::run_tests();
			NewIdReply::run_tests();
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
