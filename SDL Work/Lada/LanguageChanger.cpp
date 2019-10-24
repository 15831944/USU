// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LanguageChanger.cpp : implementation file
//

#include "stdafx.h"
#include "LanguageChanger.h"
#include "LString.h"
#include "LadaStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LanguageChanger dialog
extern int curLanguage;  // The current language
extern LString Strings;	 // All the string data
extern CFont RussianArial;											// The font used
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);//Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);				// Sets an item to a font

// Constructor
LanguageChanger::LanguageChanger(CWnd* pParent /*=NULL*/)
	: CDialog(LanguageChanger::IDD, pParent)
{
	
}

// Data Exchange
void LanguageChanger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LanguageChanger)
	DDX_Control(pDX, IDC_LIST1, m_Languages);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(LanguageChanger, CDialog)
	//{{AFX_MSG_MAP(LanguageChanger)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LanguageChanger message handlers

// Sets the current language equal to the one selected and exits
void LanguageChanger::OnOK() 
{
	if (m_Languages.GetCurSel()>=0)
		curLanguage=m_Languages.GetCurSel();
	CDialog::OnOK();
}

// Inserts all the languages in the listbox
BOOL LanguageChanger::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	SetItemFont(IDOK,this);
	SetItemFont(IDCANCEL,this);
	m_Languages.SetFont(&RussianArial);
	
	for (int x=0;x<Strings.nLanguages;x++)
		m_Languages.AddString(Strings.get(IDS_Z1+x));
	SetStrings();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Sets the current language equal to the one selected and exits
void LanguageChanger::OnDblclkList1() 
{
	OnOK();	
}

void LanguageChanger::SetStrings()
{
	SetWindowText(Strings.get(IDS_Z0));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));
}

BOOL LanguageChanger::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
			Strings.ToggleLanguage();
			SetStrings();
			m_Languages.ResetContent();
			for (int x=0;x<Strings.nLanguages;x++)
				m_Languages.AddString(Strings.get(IDS_Z1+x));

	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
