// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog is called when the Set Default button is pressed on the Data Transfer Screen
// This allows you to toggle between Floppy and PCMCIA Card as which default you are setting
// ChooseIcon.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ChooseIcon.h"
#include "LString.h"
#include "LadaStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;												// The strings for both languages
extern CFont RussianArial;										// The font used
extern void SetItemFont(UINT controlID, CWnd *window);				// Sets an item to a font

/////////////////////////////////////////////////////////////////////////////
// CChooseIcon dialog

// Constructor
// var is returned as if the Floppy was selected
CChooseIcon::CChooseIcon(BOOL *var, CWnd* pParent /*=NULL*/)
	: CDialog(CChooseIcon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseIcon)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Floppy = var;
}

// Data Exchange
void CChooseIcon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseIcon)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CChooseIcon, CDialog)
	//{{AFX_MSG_MAP(CChooseIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseIcon message handlers

// Called when the OK button is pressed
// Sets m_Floppy to if the Floppy is selected
void CChooseIcon::OnOK() 
{
	*m_Floppy = ((CButton *)GetDlgItem(IDC_FLOPPY))->GetCheck();
	CDialog::OnOK();
}

// Initialization
// Sets the Strings and Fonts
// Selects the Floppy
BOOL CChooseIcon::OnInitDialog() 
{
	CDialog::OnInitDialog();
	((CButton *)GetDlgItem(IDC_FLOPPY))->SetCheck(TRUE);
	SetFont(&RussianArial);
	SetItemFont(IDC_FLOPPY,this);
	SetItemFont(IDC_PCMCIA,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDCANCEL,this);
	SetStrings();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
// Sets the text to the current language
void CChooseIcon::SetStrings()
{
	SetWindowText(Strings.get(IDS_Q0));
	GetDlgItem(IDC_FLOPPY)->SetWindowText(Strings.get(IDS_Q1));
	GetDlgItem(IDC_PCMCIA)->SetWindowText(Strings.get(IDS_Q2));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));
}


BOOL CChooseIcon::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
