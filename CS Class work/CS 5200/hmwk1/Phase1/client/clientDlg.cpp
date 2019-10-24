// clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "AddEventDlg.h"
#include "EventListDlg.h"
#include "ClientComChannel.h"
#include "..\Common\Event.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CClientApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD_EVENT, OnAddEvent)
	ON_BN_CLICKED(IDC_LIST_EVENTS, OnListEvents)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
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

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnAddEvent() 
{

	// CS5700 TO DO: Add your control notification handler code here, if desired
	CAddEventDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		// CS5700 Add code here if desired
		BOOL rResult;
		rResult=theApp.m_clientComChannel->requestNewEvent(DString("127.0.0.1"),theApp.getServerPort());
		if (!rResult)
		{
			MessageBox("Request new event failed.");
			return;
		}

		long id;
		DString server_ip;
		UINT server_port;

		if(!theApp.m_clientComChannel->receiveId(id,server_ip,server_port,3000))
		{
			MessageBox("Failed to get new event id.  Server is not responding.");
		}
		else
		{
			Event newEvent;
			newEvent.setId(id);
			////	typedef enum { FACE2FACE='F', VOICE_CALL='C', VIDEO_CALL='V', ONLINE='O' } EVENT_TYPE;
			newEvent.setEventType('F');
			newEvent.setName(dlg.m_name);
			newEvent.setDescription(dlg.m_description);
			newEvent.setNote(dlg.m_note);
			newEvent.setDateTime(dlg.m_Date.GetYear(),dlg.m_Date.GetMonth(),dlg.m_Date.GetDay(),dlg.m_Time.GetHour(),dlg.m_Time.GetMinute(),0);
			newEvent.setDuration(dlg.m_duration);
			newEvent.setLocationId(353);
			newEvent.setStatus("Unscheduled");

			short result;
			result = theApp.m_clientComChannel->SendEvent(newEvent,server_ip,server_port);
			result = theApp.m_clientComChannel->ReceiveAckOrNak(server_ip,server_port,3000);
			if (result == 0)
			{
				MessageBox("Failed to receive ack or nak.  Server not responding.");
			}
			else if (result == 1)
			{
				MessageBox("Event scheduled successfully.");
			}
			else if (result == -1)
			{
				MessageBox("Failed to schedule event.");
			}
			else
			{
				MessageBox("invalid value received.");
			}
		}
	}
	else
	{
		// CS5700 Add code here if desired
	}
}

void CClientDlg::OnListEvents() 
{
	// CS5700 TO DO: Add your control notification handler code here
	
	CEventListDlg dlg;
	if (dlg.DoModal()==IDOK)
	{
		// CS5700 Add code here if desired
		

	}
	else
	{
		// CS5700 Add code here if desired
	}
}
