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
	m_location = _T("");
	m_id = 0;
	m_date = _T("");
	m_description = _T("");
	m_duration = 0;
	m_name = _T("");
	m_note = _T("");
	//}}AFX_DATA_INIT
}


void CAddEventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddEventDlg)
	DDX_Text(pDX, IDC_LOCATION, m_location);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Text(pDX, IDC_DATE, m_date);
	DDX_Text(pDX, IDC_DESC, m_description);
	DDX_Text(pDX, IDC_DURATION, m_duration);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_NOTE, m_note);
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
	UpdateData(TRUE);
	DString tmp;

	if (m_name=="")
		tmp += "The name cannot be blank. Please enter a meaning name for the event you want to add.\r\n";
	if (m_location=="")
		tmp += "The location cannot be blank. Please enter the location of the event.\r\n";

	if (tmp!="")
		AfxMessageBox(tmp);
	else
		CDialog::OnOK();
}

/////////////////////////////////////////////////////////////////////////////
//
// CAddEventDlg getEvent
//
// This method loads an event object using data from the screen.
//
BOOL CAddEventDlg::getEvent(Event& e)
{
	BOOL result=TRUE;

	result = result && e.setId(m_id);
	result = result && e.setName(m_name);
	result = result && e.setLocationId(0);
	result = result && e.setDateTime(m_date);
	result = result && e.setDescription(m_description);
	result = result && e.setDuration(m_duration);
	result = result && e.setNote(m_note);

	return result;
}