// AddEventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "AddEventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddEventDlg dialog


CAddEventDlg::CAddEventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddEventDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddEventDlg)
	m_location = _T("Old Main 119");
	m_description = _T("Weekly meeting held by ACM club members.");
	m_duration = 60;
	m_name = _T("ACM Meeting");
	m_note = _T("This meeting will be a workshop on DLLs presented by Mark Salisbury.");
	m_Date = CTime(2001,9,27,0,0,0);
	m_Time = CTime(2001,9,27,20,0,0);
	//}}AFX_DATA_INIT
}


void CAddEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddEventDlg)
	DDX_Text(pDX, IDC_LOCATION, m_location);
	DDX_Text(pDX, IDC_DESC, m_description);
	DDX_Text(pDX, IDC_DURATION, m_duration);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_NOTE, m_note);
	DDX_DateTimeCtrl(pDX, IDC_DATE_PICKER, m_Date);
	DDX_DateTimeCtrl(pDX, IDC_TIME_PICKER, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddEventDlg, CDialog)
	//{{AFX_MSG_MAP(CAddEventDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddEventDlg message handlers

void CAddEventDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}
