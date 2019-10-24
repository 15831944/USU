// MeasureWater.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "MeasureWater.h"
#include "lstring.h"
#include "ladastrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CFont RussianArial;											// The font used
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);	// Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);
extern LString Strings;
/////////////////////////////////////////////////////////////////////////////
// CMeasureWater dialog


CMeasureWater::CMeasureWater(CString text, double * volume, CWnd* pParent /*=NULL*/)
	: CDialog(CMeasureWater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeasureWater)
	m_volume = *volume;
	//}}AFX_DATA_INIT
	ptrVolume = volume;
}


void CMeasureWater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeasureWater)
	DDX_Text(pDX, IDC_EDIT1, m_volume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeasureWater, CDialog)
	//{{AFX_MSG_MAP(CMeasureWater)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureWater message handlers

void CMeasureWater::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDOK)->EnableWindow(GetDlgItem(IDC_EDIT1)->GetWindowTextLength());
		
	
}

void CMeasureWater::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	*ptrVolume = m_volume;
	CDialog::OnOK();
}

BOOL CMeasureWater::PreTranslateMessage(MSG* pMsg) 
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

BOOL CMeasureWater::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDOK,this);
	SetStrings();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeasureWater::SetStrings()
{
	SetWindowText(Strings.get(IDS_MW0));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_MW1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_MW2));
}
