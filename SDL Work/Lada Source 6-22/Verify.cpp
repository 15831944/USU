// This is Version 1.0 PLEASE DOCUMENT CHANGES
// Verify.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "Verify.h"
#include "CommOperations.h"
#include "fstream.h"
#include "lstring.h"
#include "ladastrings.h"
#include "inputlocations.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString ValueToString(double value, int dPlaces=2, BOOL applyLanguage = FALSE);
extern LString Strings;

extern CFont RussianArial;
extern void SetItemFont(UINT controlID, CWnd *window);

int round(double value)
{
	if (value < 0.0)
		return (int) (value - 0.5);
	else
		return (int) (value + 0.5);
}
/////////////////////////////////////////////////////////////////////////////
// Verify dialog

//inital constructor
//doc is the current document
//stat is the current state
//prin is the storage for measurements

Verify::Verify(CLADAControlModuleDoc* doc,BOOL isauto, CCheckout* prin,CWnd* pParent)
	: CDialog(Verify::IDD, pParent)
{
	pDoc=doc;
	IsAutomatic=isauto;
	print=prin;

	//{{AFX_DATA_INIT(Verify)
	m_cv1 = _T("");
	m_cv2 = _T("");
	m_cv3 = _T("");
	m_cv4 = _T("");
	m_cv5 = _T("");
	m_uv1 = _T("");
	m_uv2 = _T("");
	m_uv3 = _T("");
	m_uv4 = _T("");
	m_uv5 = _T("");
	//}}AFX_DATA_INIT
}

//Standard Data Exchange
void Verify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Verify)
	DDX_Text(pDX, IDC_CV1, m_cv1);
	DDX_Text(pDX, IDC_CV2, m_cv2);
	DDX_Text(pDX, IDC_CV3, m_cv3);
	DDX_Text(pDX, IDC_CV4, m_cv4);
	DDX_Text(pDX, IDC_CV5, m_cv5);
	DDX_Text(pDX, IDC_UV1, m_uv1);
	DDX_Text(pDX, IDC_UV2, m_uv2);
	DDX_Text(pDX, IDC_UV3, m_uv3);
	DDX_Text(pDX, IDC_UV4, m_uv4);
	DDX_Text(pDX, IDC_UV5, m_uv5);
	//}}AFX_DATA_MAP
}


//Standard Message Maps
BEGIN_MESSAGE_MAP(Verify, CDialog)
	//{{AFX_MSG_MAP(Verify)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Verify message handlers

// Save the Data to print and then exits
void Verify::OnOK() 
{
	UpdateData(TRUE);
//	CString temp;
//	temp=ValueToString(m_cv1,2);
	print->data[41][1]=m_cv1;
	print->data[42][1]=m_cv2;
	print->data[43][1]=m_cv3;
	print->data[44][1]=m_cv4;
	print->data[45][1]=m_cv5;
	print->data[41][2]=m_uv1;
	print->data[42][2]=m_uv2;
	print->data[43][2]=m_uv3;
	print->data[44][2]=m_uv4;
	print->data[45][2]=m_uv5;
	CDialog::OnOK();
}

// Gets the values and sets the fonts
BOOL Verify::OnInitDialog() 
{
	getvalues();
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_TEXT4,this);
	SetItemFont(IDC_TEXT5,this);
	SetItemFont(IDC_TEXT6,this);
	SetItemFont(IDC_TEXT7,this);
	SetItemFont(IDC_TEXT8,this);
	SetItemFont(IDOK,this);
//	SetItemFont(IDCANCEL,this);
	SetStrings();	
	if (IsAutomatic)
		OnOK();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//Gets the information and displays it
void Verify::getvalues()
{
	int locations[] = {AIRTEMP,ABPRESSURE,HUMIDITY,AIROXYGEN,CARBONDIOXIDE};
	double returnData[5];
	for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(locations,5,returnData,25); wTry++);
	if (wTry == 5)
		MessageBox("Failed to retrieve data.","Error");

	m_cv1=ValueToString(returnData[0],2);
	m_cv2=ValueToString(returnData[1],2);
	m_cv3=ValueToString(returnData[2],2);
	m_cv4=ValueToString(returnData[3],1);
	m_cv5=ValueToString(returnData[4],3);
	m_uv1=m_cv1;
	m_uv2=m_cv2;
	m_uv3=m_cv3;
	m_uv4=m_cv4;
	m_uv5=m_cv5;
	UpdateData(FALSE);

}

//Gets the value from the requested location
double Verify::get(int loc)
{
	double temp;
	pDoc->GetInputLocations(&loc,1,&temp, 25);
	return temp;

}

// Sets the text to the current language
void Verify::SetStrings()
{
	SetWindowText(Strings.get(IDS_T0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_T1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_T2));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_T3));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_T4));
	GetDlgItem(IDC_TEXT5)->SetWindowText(Strings.get(IDS_T5));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_T6));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_T7));
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_T8));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
//	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));


}

BOOL Verify::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

double Verify::roundoff(double num)
{
	return ((double)(round(num*10000))/10000);
}

void Verify::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	getvalues();
}
