// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This is temporary dialog that allows the user to check and set flags
// Flag.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "Flag.h"
#include "LADA Control ModuleDoc.h"
#include "CommOperations.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "LString.h"
#include "LadaStrings.h"

extern LString Strings;
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

/////////////////////////////////////////////////////////////////////////////
// CFlag dialog

// Constructor
// doc is the current document
CFlag::CFlag(CLADAControlModuleDoc *doc, CWnd* pParent /*=NULL*/)
	: CDialog(CFlag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFlag)
	m_FState = FALSE;
	m_wFlag = 0;
	//}}AFX_DATA_INIT
	pDoc = doc;
}

// Data Exchange
void CFlag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFlag)
	DDX_Text(pDX, IDC_FLAG_STATE, m_FState);
	DDX_Text(pDX, IDC_W_FLAG, m_wFlag);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CFlag, CDialog)
	//{{AFX_MSG_MAP(CFlag)
	ON_EN_CHANGE(IDC_FLAG_STATE, OnChangeFlagState)
	ON_EN_CHANGE(IDC_W_FLAG, OnChangeWFlag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlag message handlers

// Called when the flag state is changed
// Sets the state
void CFlag::OnChangeFlagState() 
{
	if (GetDlgItem(IDC_FLAG_STATE)->GetWindowTextLength() > 0)
	{
		SetState();
	}
}

// Called when the flag selected is changed
// Gets the new state
void CFlag::OnChangeWFlag() 
{
	if (GetDlgItem(IDC_W_FLAG)->GetWindowTextLength() > 0)
	{
		GetState();
	}
}

// Called when the OK button is pressed
// Exits
void CFlag::OnOK() 
{
	CDialog::OnOK();
}

// Initialization
// Sets the default flag and gets its state
BOOL CFlag::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (!pDoc->commObject)
	{
		MessageBox(IDS_M_CANT_CONTROL_CR10, IDS_PROGRAM_NAME);
		EndDialog(IDABORT);
	}
	else
	{
		m_wFlag = 1;
		UpdateData(FALSE);
		GetState();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Communicates with the CR10X to get the Flag state
void CFlag::GetState()
{
	UpdateData();
	pDoc->commObject->GetFlag(m_wFlag,m_FState);
	UpdateData(FALSE);
}

// Communicates with the CR10X to set the Flag state
void CFlag::SetState()
{
	UpdateData();
	if (!pDoc->commObject->SetFlag(m_wFlag,m_FState))
		MessageBox("Failed to set flag state.");
	UpdateData(FALSE);
}

void CFlag::SetStrings()
{
	SetWindowText(Strings.get(IDS_Y0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_Y1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_Y2));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));

}
