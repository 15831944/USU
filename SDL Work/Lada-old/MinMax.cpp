// This is Version 1.0 PLEASE DOCUMENT CHANGES
// MinMax.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "MinMax.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "LString.h"
#include "Ladastrings.h"

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox


/////////////////////////////////////////////////////////////////////////////
// MinMax dialog

extern CFont RussianArial;
extern void SetItemFont(UINT controlID, CWnd *window);

extern LString Strings;

/////////////////////////////////////////////////////////////////////////////
// MinMax dialog

// Constructor
// min is the current min value
// max is the current max value
MinMax::MinMax(double min, double max, CWnd* pParent /*=NULL*/)
	: CDialog(MinMax::IDD, pParent)
{
	//{{AFX_DATA_INIT(MinMax)
	m_vmax = max;
	m_vmin = min;
	m_Validate = TRUE;
	//}}AFX_DATA_INIT
}

// Data Exchange
void MinMax::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MinMax)
	DDX_Text(pDX, IDC_MAX_VALUE, m_vmax);
	DDX_Text(pDX, IDC_MIN_VALUE, m_vmin);
	DDX_Check(pDX, IDC_VALIDATE, m_Validate);
	//}}AFX_DATA_MAP
}


// Message Maps
BEGIN_MESSAGE_MAP(MinMax, CDialog)
	//{{AFX_MSG_MAP(MinMax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MinMax message handlers

// Sets fonts
BOOL MinMax::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	SetItemFont(IDC_MIN,this);
	SetItemFont(IDC_MAX,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDCANCEL,this);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Sets the text to the current language
void MinMax::SetStrings()
{
	SetWindowText(Strings.get(IDS_P0));
	GetDlgItem(IDC_MIN)->SetWindowText(Strings.get(IDS_P1));
	GetDlgItem(IDC_MAX)->SetWindowText(Strings.get(IDS_P2));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));
}

BOOL MinMax::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();	
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void MinMax::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_vmax <= m_vmin)
		MessageBox(IDS_M_MIN_MUST_BE_LESS, IDS_PROGRAM_NAME, MB_ICONINFORMATION);
	else
		CDialog::OnOK();
}
