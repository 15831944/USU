// CameraStatus.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CameraStatus.h"
#include "LadaStrings.h"
#include "LString.h"
#include "Windows.h"

extern LString Strings;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameraStatus dialog


CCameraStatus::CCameraStatus(BOOL *Canceled, CWnd* pParent /*=NULL*/)
	: CDialog(CCameraStatus::IDD, pParent)
{
	m_Initialized = FALSE;
	IsCanceled = Canceled;
	*IsCanceled = FALSE;
	//{{AFX_DATA_INIT(CCameraStatus)
	m_TimeElapsed = _T("");
	//}}AFX_DATA_INIT
	curMessageID = -1;
}


void CCameraStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameraStatus)
	DDX_Text(pDX, IDC_TIME_ELAPSED, m_TimeElapsed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCameraStatus, CDialog)
	//{{AFX_MSG_MAP(CCameraStatus)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameraStatus message handlers

void CCameraStatus::OnCancel() 
{
	// TODO: Add extra cleanup here
	*IsCanceled = TRUE;
	CDialog::OnCancel();
}

BOOL CCameraStatus::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CCameraStatus::EnableCancelButton(BOOL Enable)
{
	GetDlgItem(IDCANCEL)->EnableWindow(Enable);
}

BOOL CCameraStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_Initialized = TRUE;
	// TODO: Add extra initialization here
	StartTime = CTime::GetCurrentTime();
	SetStrings();
	SetTimer(1,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCameraStatus::SetMessage(unsigned int messageID)
{
	if (m_Initialized == TRUE)
	{
		curMessageID = messageID;
		SetStrings();
	}
}

void CCameraStatus::SetStrings()
{
	if (m_Initialized)
	{
		if (curMessageID > -1)
			GetDlgItem(IDC_MESSAGE_TEXT)->SetWindowText(Strings.get(curMessageID));
		GetDlgItem(IDC_TIME_ELAPSED_TEXT)->SetWindowText(Strings.get(IDS_ELAPSED_TIME));
		// the time window is a member variable
		UpdateData(FALSE);
	}
}

void CCameraStatus::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	///CDialog::PostNcDestroy();
}

void CCameraStatus::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_Initialized)
	{
		m_TimeElapsed = (CTime::GetCurrentTime() - StartTime).Format("%M:%S");
		SetStrings();
	}
	else
		KillTimer(nIDEvent);
	//CDialog::OnTimer(nIDEvent);
}

void CCameraStatus::KillWindow()
{
	DestroyWindow();
	m_Initialized = FALSE;
}

void CCameraStatus::SetStartTime(CTime & time)
{
	StartTime = time;
}
