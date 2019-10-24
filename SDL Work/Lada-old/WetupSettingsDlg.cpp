// This is Version 1.0 PLEASE DOCUMENT CHANGES
// WetupSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "WetupSettingsDlg.h"
#include "LADA Control ModuleDoc.h"
#include <math.h>
#include "LString.h"
#include "LadaStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;
extern CFont RussianArial;
extern int curLanguage;
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);

/////////////////////////////////////////////////////////////////////////////
// CWetupSettingsDlg dialog


CWetupSettingsDlg::CWetupSettingsDlg(CLADAControlModuleDoc *doc,BOOL Auto, CWnd* pParent /*=NULL*/)
	: CDialog(CWetupSettingsDlg::IDD, pParent)
{
	IsAutomatic=Auto;
	pDoc = doc;
	//{{AFX_DATA_INIT(CWetupSettingsDlg)
	m_FBurst = pDoc->m_WetupInfo.m_BurstFreq;
	m_eWetupTime = _T("");
	m_eBurstLength = _T("");
	m_vToPump = pDoc->m_WetupInfo.m_VolumeToPump;
	m_Hours = 0;
	m_Minutes = 0;
	m_VBurst = pDoc->m_WetupInfo.m_BurstVolume;
	m_VolumePumped = pDoc->m_WetupInfo.m_VolumePumped;
	//}}AFX_DATA_INIT
}


void CWetupSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWetupSettingsDlg)
	DDX_Control(pDX, IDC_HOURS, m_cHours);
	DDX_Control(pDX, IDC_MINUTES, m_cMinutes);
	DDX_Control(pDX, IDC_VTOPUMP, m_cVToPump);
	DDX_Control(pDX, IDC_VPBURST, m_cVPBurst);
	DDX_Control(pDX, IDC_FBURST, m_cFreqBurst);
	DDX_Text(pDX, IDC_FBURST, m_FBurst);
	DDV_MinMaxInt(pDX, m_FBurst, 1, 120);
	DDX_Text(pDX, IDC_EWETUPTIME, m_eWetupTime);
	DDX_Text(pDX, IDC_EBURSTLENGTH, m_eBurstLength);
	DDX_Text(pDX, IDC_VTOPUMP, m_vToPump);
	DDX_Text(pDX, IDC_HOURS, m_Hours);
	DDX_Text(pDX, IDC_MINUTES, m_Minutes);
	DDX_Text(pDX, IDC_VPBURST, m_VBurst);
	DDX_Text(pDX, IDC_TOTAL_PUMPED, m_VolumePumped);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWetupSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CWetupSettingsDlg)
	ON_EN_CHANGE(IDC_VTOPUMP, OnChangeVtopump)
	ON_EN_CHANGE(IDC_VPBURST, OnChangeVpburst)
	ON_EN_CHANGE(IDC_FBURST, OnChangeFburst)
	ON_EN_CHANGE(IDC_HOURS, OnChangeTime)
	ON_EN_CHANGE(IDC_MINUTES, OnChangeTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWetupSettingsDlg message handlers

void CWetupSettingsDlg::OnChangeVtopump() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateEstimates();
}

void CWetupSettingsDlg::OnChangeVpburst() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateEstimates();
}

void CWetupSettingsDlg::OnChangeFburst() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateEstimates();
}

BOOL CWetupSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//UpdateData(FALSE);
	SetFont(&RussianArial);
	for (int i = 0; i < 12; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetFont(&RussianArial);
	GetDlgItem(IDC_VTOPUMP)->SetFont(&RussianArial);
	GetDlgItem(IDC_FBURST)->SetFont(&RussianArial);
	GetDlgItem(IDC_VPBURST)->SetFont(&RussianArial);
	GetDlgItem(IDC_HOURS)->SetFont(&RussianArial);
	GetDlgItem(IDC_MINUTES)->SetFont(&RussianArial);
	GetDlgItem(IDC_EWETUPTIME)->SetFont(&RussianArial);
	GetDlgItem(IDC_EBURSTLENGTH)->SetFont(&RussianArial);
	GetDlgItem(IDOK)->SetFont(&RussianArial);

	SetStrings();
	
	if (IsAutomatic)
		OnOK();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWetupSettingsDlg::UpdateEstimates(BOOL UpdateTime) // = TRUE
{
	if (m_cVToPump.GetWindowTextLength() && m_cFreqBurst.GetWindowTextLength() && m_cVPBurst.GetWindowTextLength())
	{
		UpdateData(TRUE);
		DWORD nSeconds;
		
		int volToPumpNow = m_vToPump - pDoc->m_WetupInfo.m_VolumePumped;

		if (m_VBurst > 0){
			int nBursts = (int)ceil((volToPumpNow - 1) / m_VBurst);
		
			m_eWetupTime = GetTimeSpan(CTimeSpan(time_t(nBursts * m_FBurst * 60)), 3);
			
			if (UpdateTime)
			{
				nSeconds = (unsigned long)(volToPumpNow * m_FBurst * 60 / m_VBurst);
				
				m_Hours = CTimeSpan(time_t(nSeconds)).GetHours();
				m_Minutes = CTimeSpan(time_t(nSeconds)).GetMinutes();
			}			
		}		
		nSeconds = (unsigned)(m_VBurst / pDoc->m_WetupInfo.m_mlPerSecond);
		m_eBurstLength = GetTimeSpan(CTimeSpan(time_t(nSeconds)), 2);
		UpdateData(FALSE);
		return TRUE;
	}
	else
		return FALSE;
	
}

void CWetupSettingsDlg::OnOK() 
{
	// TODO: Add extra validation here
	if (!UpdateEstimates())
		return;
	if (m_Minutes < 0 || m_Minutes > 59)
	{
		MessageBox("Minutes should be between 0 and 59","Error");
		return;
	}
	
	if (m_Hours < 0 || m_Hours > 72)
	{
		MessageBox("Hours should be between 0 and 72","Error");
		return;
	}

	if (m_VBurst / pDoc->m_WetupInfo.m_mlPerSecond > m_FBurst * 60)
	{
		MessageBox("Estimated burst length must be less than burst frequency.","Error");
		return;
	}

	if (m_vToPump < m_VolumePumped)
	{
		MessageBox("Volume to pump cannot be less than volume pumped.","Error");
		return;	
	}

	pDoc->m_WetupInfo.m_BurstFreq = m_FBurst;
	pDoc->m_WetupInfo.m_BurstVolume = m_VBurst;
	pDoc->m_WetupInfo.m_VolumeToPump = m_vToPump;
	
	CDialog::OnOK();
}

void CWetupSettingsDlg::OnChangeTime() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_cHours.GetWindowTextLength() && m_cMinutes.GetWindowTextLength() && m_cVToPump.GetWindowTextLength())
	{
		UpdateData();
		m_VBurst = (double) m_vToPump * m_FBurst / (m_Hours * 60 + m_Minutes);
		UpdateData(FALSE);
		UpdateEstimates(FALSE);
	}
}


void CWetupSettingsDlg::SetStrings()
{
	SetWindowText(Strings.get(IDS_X0));
	for (int i = 0; i < 12; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetWindowText(Strings.get(IDS_X1+i));
	UpdateEstimates();
	
}

BOOL CWetupSettingsDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		curLanguage = !curLanguage;
		SetStrings();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
