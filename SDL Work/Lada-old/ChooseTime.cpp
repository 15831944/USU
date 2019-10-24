// ChooseTime.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ChooseTime.h"
#include "LString.h"
#include "LadaStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;

extern CFont RussianArial;
extern void SetItemFont(UINT controlID, CWnd *window);
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
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseTime message handlers

void CChooseTime::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(1);
	UpdateData(TRUE);
	*m_pDate = m_Date;
	*m_pTime = m_Time;
	CDialog::OnOK();
}

BOOL CChooseTime::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDCANCEL,this);
	
	// TODO: Add extra initialization here
	m_Date = m_Time = CTime::GetCurrentTime();
	UpdateData(FALSE);
	SetStrings();
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseTime::SetStrings()
{
	SetWindowText(Strings.get(IDS_J0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_J1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_J2));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_J3));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));

}

void CChooseTime::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
	m_Date = m_Time = CTime::GetCurrentTime();
	UpdateData(FALSE);
}

void CChooseTime::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnClose();
}

void CChooseTime::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(1);
	CDialog::OnCancel();
}

BOOL CChooseTime::PreTranslateMessage(MSG* pMsg) 
{
BOOL CCameradialogDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
			Strings.ToggleLanguage();
			SetStrings();
	}
	return CDialog::PreTranslateMessage(pMsg);
}
