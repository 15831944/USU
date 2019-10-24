// ChooseTime.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ChooseTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseTime dialog


CChooseTime::CChooseTime(CTime *pDate, CTime *pTime, CWnd* pParent /*=NULL*/)
	: CDialog(CChooseTime::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseTime)
	m_Date = 0;
	m_Time = 0;
	//}}AFX_DATA_INIT
	m_pDate = pDate;
	m_pTime = pTime;
}


void CChooseTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseTime)
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_Time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseTime, CDialog)
	//{{AFX_MSG_MAP(CChooseTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseTime message handlers

void CChooseTime::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	*m_pDate = m_Date;
	*m_pTime = m_Time;

	CDialog::OnOK();
}

BOOL CChooseTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Date = m_Time = CTime::GetCurrentTime();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
