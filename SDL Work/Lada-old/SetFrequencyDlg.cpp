// SetFrequencyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "SetFrequencyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetFrequencyDlg dialog


CSetFrequencyDlg::CSetFrequencyDlg(CTimeSpan * ptrFreq, CWnd* pParent /*=NULL*/)
	: CDialog(CSetFrequencyDlg::IDD, pParent)
{
	m_TimeSpan = ptrFreq;
	//{{AFX_DATA_INIT(CSetFrequencyDlg)
	m_Hours = 0;
	m_Minutes = 0;
	//}}AFX_DATA_INIT
}


void CSetFrequencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetFrequencyDlg)
	DDX_Text(pDX, IDC_HOURS, m_Hours);
	DDX_Text(pDX, IDC_MINUTES, m_Minutes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetFrequencyDlg, CDialog)
	//{{AFX_MSG_MAP(CSetFrequencyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetFrequencyDlg message handlers

void CSetFrequencyDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if (m_Hours == 0 && m_Minutes == 0)
	{
		MessageBox("Hours or Minutes must be non-zero.");
		return;
	}
	if (m_Hours < 0 || m_Minutes < 0)
	{
		MessageBox("Hours and Minutes may not be negative.");
		return;
	}
	*m_TimeSpan = CTimeSpan(0,m_Hours,m_Minutes,0);
	CDialog::OnOK();
}

BOOL CSetFrequencyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Hours = m_TimeSpan->GetTotalHours();
	m_Minutes = m_TimeSpan->GetMinutes();
	UpdateData(FALSE);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
