// CalibrationDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CalibrationDlg2.h"
#include "LADA Control ModuleDoc.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg2 dialog
extern int curLanguage;
extern CString ValueToString(double value, int dPlaces = 2, int curLang = curLanguage);

CCalibrationDlg2::CCalibrationDlg2(CLADAControlModuleDoc * doc, CString sGroup, CString sName, int dLocation, int cLocation, CWnd* pParent /*=NULL*/)
	: CDialog(CCalibrationDlg2::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CCalibrationDlg2)
	m_Group = sGroup;
	m_Name = sName;
	m_Reading = 0.0;
	m_KnownValue = 0.0;
	//}}AFX_DATA_INIT
	dataLocation = dLocation;
	calibrationLocation = cLocation;
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
	CWaitCursor wCursor;

	UpdateData();
	pDoc->GetInputLocations(&dataLocation, 1, &m_Reading, 30);
	//GetDlgItem(IDC_READING)->SetWindowText(ValueToString(m_Reading,4));
	UpdateData(FALSE);

	double changeInOffset = m_KnownValue - m_Reading;
	double offsetValue;
	if (pDoc->GetInputLocations(&calibrationLocation, 1, &offsetValue, 31))
	{
		offsetValue += changeInOffset;
		if (pDoc->commObject->SetInputLocation(calibrationLocation, offsetValue, 8))
		{
			EndDialog(0);
			return;
		}
	}
	MessageBox("Calibration failed.");
	EndDialog(0);
}

BOOL CCalibrationDlg2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	pDoc->GetInputLocations(&dataLocation, 1, &m_Reading, 30);
	GetDlgItem(IDC_READING)->SetWindowText(ValueToString(m_Reading,4));
	//SetTimer(0,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//void CCalibrationDlg2::OnTimer(UINT nIDEvent) 
//{
//	// TODO: Add your message handler code here and/or call default
//	pDoc->GetInputLocations(&dataLocation, 1, &m_Reading, 30);
//	GetDlgItem(IDC_READING)->SetWindowText(ValueToString(m_Reading,4));
//	CDialog::OnTimer(nIDEvent);
//}
