// SetFrequencyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "SetFrequencyDlg.h"
#include "LadaStrings.h"
#include "LString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;
extern CFont RussianArial;											// The font used
extern void SetItemFont(UINT controlID, CWnd *window);					// Sets and item to a font
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
	SetStrings();
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSetFrequencyDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CSetFrequencyDlg::SetStrings()
{
	SetWindowText(Strings.get(IDS_DD0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_DD1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_DD2));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_DD3));
}
