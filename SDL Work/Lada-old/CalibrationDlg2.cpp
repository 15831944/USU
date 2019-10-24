// CalibrationDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CalibrationDlg2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg2 dialog


CCalibrationDlg2::CCalibrationDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCalibrationDlg2)
	m_Group = _T("");
	m_Name = _T("");
	m_Reading = 0.0;
	m_KnownValue = 0.0;
	//}}AFX_DATA_INIT
}


void CCalibrationDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalibrationDlg2)
	DDX_Text(pDX, IDC_GROUP, m_Group);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDX_Text(pDX, IDC_READING, m_Reading);
	DDX_Text(pDX, IDC_VALUE, m_KnownValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCalibrationDlg2, CDialog)
	//{{AFX_MSG_MAP(CCalibrationDlg2)
	ON_BN_CLICKED(IDC_RE_CALIBRATE, OnReCalibrate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg2 message handlers

void CCalibrationDlg2::OnReCalibrate() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CCalibrationDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
