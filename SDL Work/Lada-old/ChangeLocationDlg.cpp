// This is Version 1.0 PLEASE DOCUMENT CHANGES
// Allows the user to access and change input locations
// ChangeLocationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ChangeLocationDlg.h"
#include "LadaStrings.h"
#include "LString.h"
#include "CommOperations.h"
#include "LADA Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE); // Returns the CString of value to dPlaces numbers after the decimal
extern LString Strings;												// The strings for both languages
extern CFont RussianArial;										// The font used
extern void SetItemFont(UINT controlID, CWnd *window);				// Sets an item to a font

/////////////////////////////////////////////////////////////////////////////
// CChangeLocationDlg dialog

// Constructor
// ptrDoc is the current document
CChangeLocationDlg::CChangeLocationDlg(CLADAControlModuleDoc *ptrDoc, int initialLocation, CWnd* pParent /*=NULL*/)
	: CDialog(CChangeLocationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeLocationDlg)
	m_wLocation = initialLocation;
	m_value = 0.0;
	m_newValue = 0.0;
	//}}AFX_DATA_INIT
	pDoc = ptrDoc;
	commObject = pDoc->commObject;
}

// Data Exchange
void CChangeLocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeLocationDlg)
	DDX_Text(pDX, IDC_EDIT1, m_wLocation);
	DDX_Text(pDX, IDC_EDIT3, m_newValue);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CChangeLocationDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeLocationDlg)
	ON_BN_CLICKED(IDC_GETVALUE, OnGetvalue)
	ON_BN_CLICKED(IDC_SETVALUE, OnSetvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeLocationDlg message handlers

// Gets a value from the CR10
void CChangeLocationDlg::OnGetvalue() 
{
	UpdateData();
	CWaitCursor wCursor;
	pDoc->GetInputLocations(&m_wLocation,1,&m_value);
	GetDlgItem(IDC_EDIT2)->SetWindowText(ValueToString(m_value,4));
	UpdateData(FALSE);
}

// Sets a value to the CR10
void CChangeLocationDlg::OnSetvalue() 
{
	UpdateData();
	CWaitCursor wCursor;
	
	commObject->SetInputLocation(m_wLocation,m_newValue);
	
	GetDlgItem(IDC_EDIT2)->SetWindowText(ValueToString(m_value,4));
	UpdateData(FALSE);

}

// Initialization
// Sets Fonts and Strings
BOOL CChangeLocationDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT2)->SetWindowText("???");
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDC_GETVALUE,this);
	SetItemFont(IDC_SETVALUE,this);

	SetStrings();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Sets the text to the current langauge
void CChangeLocationDlg::SetStrings()
{
	SetWindowText(Strings.get(IDS_K0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_K1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_K2));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_K3));
	GetDlgItem(IDC_GETVALUE)->SetWindowText(Strings.get(IDS_K4));
	GetDlgItem(IDC_SETVALUE)->SetWindowText(Strings.get(IDS_K5));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));

}

BOOL CChangeLocationDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
			Strings.ToggleLanguage();
			SetStrings();
	}
	return CDialog::PreTranslateMessage(pMsg);
}
