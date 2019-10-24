// LadaTest2.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "LadaTest2.h"
#include "inputlocations.h"
#include "lada control moduledoc.h"
#include "resource.h"
#include "ladastrings.h"
#include "Lstring.h"
#include "checkout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFont RussianArial;								// The font used
extern void SetItemFont(UINT controlID, CWnd *window);		// Sets an item to a font
extern LString Strings;
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
/////////////////////////////////////////////////////////////////////////////
// LadaTest2 dialog

void LadaTest2::CollectData(BOOL UpdateUser)
{
	double hold[8];
	int locations[8] = {IBallTemp,IRefTemp,ILeaf1,ILeaf2,ILeaf3,IInlet,ILeafSurface,IHumOut};
	for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(locations,8,hold,33); wTry++);
	if (wTry == 5)
		MessageBox("Failed to collect data.");
	
	GetDlgItem(IDC_CV5)->SetWindowText(ValueToString(hold[0]));
	GetDlgItem(IDC_CV6)->SetWindowText(ValueToString(hold[1]));
	GetDlgItem(IDC_CV7)->SetWindowText(ValueToString(hold[2]));
	GetDlgItem(IDC_CV8)->SetWindowText(ValueToString(hold[3]));
	GetDlgItem(IDC_CV9)->SetWindowText(ValueToString(hold[4]));
	GetDlgItem(IDC_CV10)->SetWindowText(ValueToString(hold[5]));
	GetDlgItem(IDC_CV11)->SetWindowText(ValueToString(hold[6]));
	GetDlgItem(IDC_CV12)->SetWindowText(ValueToString(hold[7]));
	if (UpdateUser)
	{
		GetDlgItem(IDC_UV5)->SetWindowText(ValueToString(hold[0]));
		GetDlgItem(IDC_UV6)->SetWindowText(ValueToString(hold[1]));
		GetDlgItem(IDC_UV7)->SetWindowText(ValueToString(hold[2]));
		GetDlgItem(IDC_UV8)->SetWindowText(ValueToString(hold[3]));
		GetDlgItem(IDC_UV9)->SetWindowText(ValueToString(hold[4]));
		GetDlgItem(IDC_UV10)->SetWindowText(ValueToString(hold[5]));
		GetDlgItem(IDC_UV11)->SetWindowText(ValueToString(hold[6]));
		GetDlgItem(IDC_UV12)->SetWindowText(ValueToString(hold[7]));
	}
}
LadaTest2::LadaTest2(CLADAControlModuleDoc * doc, CCheckout * prin, BOOL IsAuto, CWnd* pParent /*=NULL*/)
	: CDialog(LadaTest2::IDD, pParent)
{
	IsAutomatic = IsAuto;
	pDoc = doc;
	print = prin;
	//{{AFX_DATA_INIT(LadaTest2)
	m_u5 = _T("");
	m_u6 = _T("");
	m_u7 = _T("");
	m_u8 = _T("");
	m_u9 = _T("");
	m_u10 = _T("");
	m_u11 = _T("");
	m_u12 = _T("");
	m_cv6 = _T("");
	m_cv7 = _T("");
	m_cv8 = _T("");
	m_cv9 = _T("");
	m_cv11 = _T("");
	m_cv12 = _T("");
	//}}AFX_DATA_INIT
}

void LadaTest2::SetStrings()
{
	GetDlgItem(IDC_TEXT5)->SetWindowText(Strings.get(IDS_R7));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_R8));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_R9));
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_R10));
	GetDlgItem(IDC_TEXT9)->SetWindowText(Strings.get(IDS_R12));
	GetDlgItem(IDC_TEXT10)->SetWindowText(Strings.get(IDS_R12));
	GetDlgItem(IDC_TEXT11)->SetWindowText(Strings.get(IDS_R13));
	GetDlgItem(IDC_TEXT12)->SetWindowText(Strings.get(IDS_R14));
}

void LadaTest2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LadaTest2)
	DDX_Text(pDX, IDC_UV5, m_u5);
	DDX_Text(pDX, IDC_UV6, m_u6);
	DDX_Text(pDX, IDC_UV7, m_u7);
	DDX_Text(pDX, IDC_UV8, m_u8);
	DDX_Text(pDX, IDC_UV9, m_u9);
	DDX_Text(pDX, IDC_UV10, m_u10);
	DDX_Text(pDX, IDC_UV11, m_u11);
	DDX_Text(pDX, IDC_UV12, m_u12);
	DDX_Text(pDX, IDC_CV6, m_cv6);
	DDX_Text(pDX, IDC_CV7, m_cv7);
	DDX_Text(pDX, IDC_CV8, m_cv8);
	DDX_Text(pDX, IDC_CV9, m_cv9);
	DDX_Text(pDX, IDC_CV11, m_cv11);
	DDX_Text(pDX, IDC_CV12, m_cv12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LadaTest2, CDialog)
	//{{AFX_MSG_MAP(LadaTest2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LadaTest2 message handlers

BOOL LadaTest2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetItemFont(IDC_TEXT5,this);
	SetItemFont(IDC_TEXT6,this);
	SetItemFont(IDC_TEXT7,this);
	SetItemFont(IDC_TEXT8,this);
	SetItemFont(IDC_TEXT9,this);
	SetItemFont(IDC_TEXT10,this);
	SetItemFont(IDC_TEXT11,this);
	SetItemFont(IDC_TEXT12,this);

	// TODO: Add extra initialization here
	SetStrings();
	CollectData(TRUE);
	if (IsAutomatic)
		OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void LadaTest2::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	print->data[30][1]=m_cv6;
	print->data[31][1]=m_cv7;
	print->data[32][1]=m_cv8;
	print->data[33][1]=m_cv9;
	print->data[30][2]=m_u6;
	print->data[31][2]=m_u7;
	print->data[32][2]=m_u8;
	print->data[33][2]=m_u9;
	print->data[34][2]=m_u11;
	print->data[35][2]=m_u12;
	print->data[34][1]=m_cv11;
	print->data[35][1]=m_cv12;
	CDialog::OnOK();
}

void LadaTest2::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CollectData(FALSE);
}
