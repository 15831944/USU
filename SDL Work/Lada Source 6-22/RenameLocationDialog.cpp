// This is Version 1.0 PLEASE DOCUMENT CHANGES
// RenameLocationDialog.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "RenameLocationDialog.h"
#include "Ladastrings.h"
#include "LString.h"
#include "LADA Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int curLanguage;
extern LString Strings;
extern CFont RussianArial;
/////////////////////////////////////////////////////////////////////////////
// CRenameLocationDialog dialog

CRenameLocationDialog::CRenameLocationDialog(int whichLocation,
								 int wTextIDS,
								 InputListType *ptrInputLoc,
								 BOOL showNumber /*=TRUE */, 
								 CWnd* pParent /*=NULL*/)
								 


	: CDialog(CRenameLocationDialog::IDD, pParent)
{
	InputLoc = ptrInputLoc;
	m_whichLocation = whichLocation;
	ShowNumberBox = showNumber;
	m_textIDS = wTextIDS;
	//InputLocNames = pDoc->InputLocationNameList;
	//strcpy(m_oldName, oName);
	//m_newName = nName;
	//m_number = n;
	//strcpy(m_windowText,wText);
	//strcpy(m_titleText,title);
	
	//{{AFX_DATA_INIT(CRenameLocationDialog)
	//}}AFX_DATA_INIT
}

CRenameLocationDialog::OnInitDialog()
{   
	CDialog::OnInitDialog();      // TODO: Add extra initialization here
	//strcpy(m_newName,m_oldName);

	GetDlgItem(IDC_WIN_TEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_OLD_NAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW_NAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_OLDNAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEWNAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_NUMBER)->SetFont(&RussianArial);
	GetDlgItem(IDOK)->SetFont(&RussianArial);
	GetDlgItem(IDCANCEL)->SetFont(&RussianArial);
	SetFont(&RussianArial);
	
	if (ShowNumberBox){
		char numBuf[8];
		wsprintf(numBuf,"%i",m_whichLocation + 1);
		m_Number_CStatic.SetWindowText(numBuf);
	}
	else
		m_Number_CStatic.ShowWindow(SW_HIDE);
	
	if (m_textIDS == NO_STRING)
		m_Win_Text_CStatic.ShowWindow(SW_HIDE);
	
	
	m_New_Name_CEdit.SetFocus();
	SetStrings();

	return FALSE;   // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE}
}

void CRenameLocationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenameLocationDialog)
	DDX_Control(pDX, IDC_OLD_NAME, m_Old_Name_CStatic);
	DDX_Control(pDX, IDC_NUMBER, m_Number_CStatic);
	DDX_Control(pDX, IDC_WIN_TEXT, m_Win_Text_CStatic);
	DDX_Control(pDX, IDC_NEW_NAME, m_New_Name_CEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRenameLocationDialog, CDialog)
	//{{AFX_MSG_MAP(CRenameLocationDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenameLocationDialog message handlers

void CRenameLocationDialog::OnOK() 
{
	m_New_Name_CEdit.GetWindowText(&InputLoc[0][curLanguage][4],24);
	CDialog::OnOK();
}

void CRenameLocationDialog::OnCancel() 
{
	CDialog::OnCancel();
}

BOOL CRenameLocationDialog::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{	
		m_New_Name_CEdit.GetWindowText(&InputLoc[0][curLanguage][4],24);
		Strings.ToggleLanguage();
		SetStrings();
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CRenameLocationDialog::SetStrings()
{
	SetWindowText(Strings.get(IDS_U0));
	GetDlgItem(IDC_OLDNAME)->SetWindowText(Strings.get(IDS_U1));
	GetDlgItem(IDC_NEWNAME)->SetWindowText(Strings.get(IDS_U2));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));

	m_Old_Name_CStatic.SetWindowText(&InputLoc[0][curLanguage][4]);
	m_New_Name_CEdit.SetWindowText(&InputLoc[0][curLanguage][4]);
	
	if (m_textIDS != NO_STRING)
		m_Win_Text_CStatic.SetWindowText(Strings.get(m_textIDS));
}
