// EventListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "EventListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NAME_COLUMN		0 // DESCRIPTION becomes a tooltip for name column
#define DATE_COLUMN		1
#define DURATION_COLUMN	2
#define TYPE_COLUMN		3
#define STATUS_COLUMN	4
#define LOCATION_COLUMN	5
#define NOTE_COLUMN		6
#define N_COLUMNS		7

extern CClientApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CEventListDlg dialog


CEventListDlg::CEventListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEventListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEventListDlg)
	m_StartDate = CTime::GetCurrentTime();
	m_EndDate = CTime::GetCurrentTime();
	//}}AFX_DATA_INIT
	dlgInitialized = FALSE;
}


void CEventListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventListDlg)
	DDX_Control(pDX, IDC_LIST_VIEW, m_ListView);
	DDX_DateTimeCtrl(pDX, IDC_START_DATE, m_StartDate);
	DDX_DateTimeCtrl(pDX, IDC_END_DATE, m_EndDate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEventListDlg, CDialog)
	//{{AFX_MSG_MAP(CEventListDlg)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventListDlg message handlers

void CEventListDlg::OnQuery() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_EndDate <= m_StartDate)
	{
		MessageBox("End date cannot be less than start date.");
		return;
	}

	BOOL rResult;
	rResult=theApp.m_clientComChannel->requestEventList(m_StartDate, m_EndDate, "127.0.0.1", theApp.getServerPort());
	if (!rResult)
	{
		MessageBox("Request failed.");
		return;
	}

	DString server_ip;
	UINT server_port;
	short count;
	if(!theApp.m_clientComChannel->receiveCount(count,server_ip,server_port,3000))
	{
		MessageBox("Failed to get event count.  Server is not responding.");
	}
	else
	{
		Event event;
		//m_List.ResetContent();
		m_ListView.DeleteAllItems();
		for (short wEvent = 0; wEvent < count; wEvent++)
		{
			if(!theApp.m_clientComChannel->ReceiveEvent(event,server_ip,server_port,3000))
			{
				//... retry
				wEvent--;
			}
			else
			{
				CString t;
				//m_List.AddString(event.getName());
				m_ListView.InsertItem(wEvent,event.getName());
				// got to figure out how to set the tool tip text to add the description...
				m_ListView.SetItemText(wEvent,DATE_COLUMN,event.getDateTime().Format("%m/%d/%y %I:%M %p"));
				t.Format("%i",event.getDuration());
				m_ListView.SetItemText(wEvent,DURATION_COLUMN,t);
				m_ListView.SetItemText(wEvent,TYPE_COLUMN,Event::GetEventTypeName(event.getEventType()));
				m_ListView.SetItemText(wEvent,STATUS_COLUMN,Event::GetStatusName(event.getStatus()));
				t.Format("ID %i",event.getLocationId());
				m_ListView.SetItemText(wEvent,LOCATION_COLUMN,t);
				m_ListView.SetItemText(wEvent,NOTE_COLUMN,event.getNote());
				theApp.m_clientComChannel->SendAck(server_ip,server_port);
			}
		}

	}
	for (int c = 0; c < N_COLUMNS; c++)
		m_ListView.SetColumnWidth(c,LVSCW_AUTOSIZE_USEHEADER);
}

BOOL CEventListDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/*	
	NAME_COLUMN
	DATE_COLUMN
	DURATION_COLUMN
	TYPE_COLUMN
	STATUS_COLUMN
	LOCATION_COLUMN
	NOTE_COLUMN
	*/
	m_ListView.InsertColumn(NAME_COLUMN,"Name");
	m_ListView.InsertColumn(DATE_COLUMN,"Date");
	m_ListView.InsertColumn(DURATION_COLUMN,"Duration");
	m_ListView.InsertColumn(TYPE_COLUMN,"Type");
	m_ListView.InsertColumn(STATUS_COLUMN,"Status");
	m_ListView.InsertColumn(LOCATION_COLUMN,"Location");
	m_ListView.InsertColumn(NOTE_COLUMN,"Note");
	for (int c = 0; c < N_COLUMNS; c++)
		m_ListView.SetColumnWidth(c,LVSCW_AUTOSIZE_USEHEADER);

	m_ListView.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	// TODO: Add extra initialization here
	dlgInitialized = TRUE;
	//Rect rect1;
	//GetClientRect(&rect1);
	//OnSize(SIZE_RESTORED,rect1.Width(),rect1.Height());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEventListDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if (nType != SIZE_MINIMIZED && cx > 50 && cy > 150 && dlgInitialized)
	{
		m_ListView.SetWindowPos(NULL,0,0,cx-21,cy-119,SWP_NOMOVE|SWP_NOZORDER);	
		GetDlgItem(IDOK)->SetWindowPos(NULL,cx/2-43,cy-33,0,0,SWP_NOZORDER|SWP_NOSIZE);
	}
}
