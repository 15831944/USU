// SetCalibration.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "SetCalibration.h"
#include "lada control moduledoc.h"
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetCalibration dialog


SetCalibration::SetCalibration(CLADAControlModuleDoc* doc,CWnd* pParent /*=NULL*/)
	: CDialog(SetCalibration::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetCalibration)
	m_mult = 0.0;
	m_off = 0.0;
	A2 = 0.0;
	B2 = 0.0;
	B1 = 0.0;
	A1 = 0.0;
	pDoc=doc;
	//}}AFX_DATA_INIT
}


void SetCalibration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetCalibration)
	DDX_Text(pDX, IDC_EDIT38, m_mult);
	DDX_Text(pDX, IDC_EDIT37, m_off);
	DDX_Text(pDX, IDC_EDIT35, A2);
	DDX_Text(pDX, IDC_EDIT36, B2);
	DDX_Text(pDX, IDC_EDIT34, B1);
	DDX_Text(pDX, IDC_EDIT33, A1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetCalibration, CDialog)
	//{{AFX_MSG_MAP(SetCalibration)
	ON_BN_CLICKED(IDC_CALCULATE, OnCalculate)
	ON_BN_CLICKED(IDC_CHAMBERA, OnChambera)
	ON_BN_CLICKED(IDC_CHAMBERB, OnChamberb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetCalibration message handlers

void SetCalibration::OnOK() 
{
	Save();
	CDialog::OnOK();
}

BOOL SetCalibration::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Chamber=0;
//	(CButton*)(GetDlgItem(IDC_CHAMBERA))->SetCheck(TRUE);
	Display();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SetCalibration::OnCalculate() 
{
	UpdateData(TRUE);
	m_mult=(B1-B2)/(A1-A2);
	m_off=B1-(A1*m_mult);
	UpdateData(FALSE);
}

double SetCalibration::stringtodouble(CString string)
{
	double ret=0;
	double value=1;
	int length=string.GetLength();
	for (int x=0;(x<length && string[x]!='.');x++)
	{
		ret*=10;
		ret+=string[x]-'0';
	}
	if (x==length)
		return ret;
	else if (string[x]=='.')
	{
		x++;
		for (int y=x;y<length;y++)
		{
			value/=10;
			ret+=value*(string[y]-'0');
		}
	}
	return ret;
}




void SetCalibration::OnChambera() 
{
	Save();
	Chamber=0;
	Display();

	
}

void SetCalibration::OnChamberb() 
{
	Save();
	Chamber=1;
	Display();
	
}

void SetCalibration::Display()
{
	GetDlgItem(IDC_CAL1)->SetWindowText(ValueToString(pDoc->Calibrations[0][0][Chamber]));
	GetDlgItem(IDC_CAL2)->SetWindowText(ValueToString(pDoc->Calibrations[0][1][Chamber]));
	GetDlgItem(IDC_CAL3)->SetWindowText(ValueToString(pDoc->Calibrations[1][0][Chamber]));
	GetDlgItem(IDC_CAL4)->SetWindowText(ValueToString(pDoc->Calibrations[1][1][Chamber]));
	GetDlgItem(IDC_CAL5)->SetWindowText(ValueToString(pDoc->Calibrations[2][0][Chamber]));
	GetDlgItem(IDC_CAL6)->SetWindowText(ValueToString(pDoc->Calibrations[2][1][Chamber]));
	GetDlgItem(IDC_CAL7)->SetWindowText(ValueToString(pDoc->Calibrations[3][0][Chamber]));
	GetDlgItem(IDC_CAL8)->SetWindowText(ValueToString(pDoc->Calibrations[3][1][Chamber]));
	GetDlgItem(IDC_CAL9)->SetWindowText(ValueToString(pDoc->Calibrations[4][0][Chamber]));
	GetDlgItem(IDC_CAL10)->SetWindowText(ValueToString(pDoc->Calibrations[4][1][Chamber]));
	GetDlgItem(IDC_CAL11)->SetWindowText(ValueToString(pDoc->Calibrations[5][0][Chamber]));
	GetDlgItem(IDC_CAL12)->SetWindowText(ValueToString(pDoc->Calibrations[5][1][Chamber]));
	GetDlgItem(IDC_CAL13)->SetWindowText(ValueToString(pDoc->Calibrations[6][0][Chamber]));
	GetDlgItem(IDC_CAL14)->SetWindowText(ValueToString(pDoc->Calibrations[6][1][Chamber]));
	GetDlgItem(IDC_CAL15)->SetWindowText(ValueToString(pDoc->Calibrations[7][0][Chamber]));
	GetDlgItem(IDC_CAL16)->SetWindowText(ValueToString(pDoc->Calibrations[7][1][Chamber]));
	GetDlgItem(IDC_CAL17)->SetWindowText(ValueToString(pDoc->Calibrations[8][0][Chamber]));
	GetDlgItem(IDC_CAL18)->SetWindowText(ValueToString(pDoc->Calibrations[8][1][Chamber]));
	GetDlgItem(IDC_CAL19)->SetWindowText(ValueToString(pDoc->Calibrations[9][0][Chamber]));
	GetDlgItem(IDC_CAL20)->SetWindowText(ValueToString(pDoc->Calibrations[9][1][Chamber]));
	GetDlgItem(IDC_CAL21)->SetWindowText(ValueToString(pDoc->Calibrations[10][0][Chamber]));
	GetDlgItem(IDC_CAL22)->SetWindowText(ValueToString(pDoc->Calibrations[10][1][Chamber]));
	GetDlgItem(IDC_CAL23)->SetWindowText(ValueToString(pDoc->Calibrations[11][0][Chamber]));
	GetDlgItem(IDC_CAL24)->SetWindowText(ValueToString(pDoc->Calibrations[11][1][Chamber]));
	GetDlgItem(IDC_CAL25)->SetWindowText(ValueToString(pDoc->Calibrations[12][0][Chamber]));
	GetDlgItem(IDC_CAL26)->SetWindowText(ValueToString(pDoc->Calibrations[12][1][Chamber]));
	GetDlgItem(IDC_CAL27)->SetWindowText(ValueToString(pDoc->Calibrations[13][0][Chamber]));
	GetDlgItem(IDC_CAL28)->SetWindowText(ValueToString(pDoc->Calibrations[13][1][Chamber]));
	GetDlgItem(IDC_CAL29)->SetWindowText(ValueToString(pDoc->Calibrations[14][0][Chamber]));
	GetDlgItem(IDC_CAL30)->SetWindowText(ValueToString(pDoc->Calibrations[14][1][Chamber]));
	GetDlgItem(IDC_CAL31)->SetWindowText(ValueToString(pDoc->Calibrations[15][0][Chamber]));
	GetDlgItem(IDC_CAL32)->SetWindowText(ValueToString(pDoc->Calibrations[15][1][Chamber]));
	GetDlgItem(IDC_CAL33)->SetWindowText(ValueToString(pDoc->Calibrations[16][0][Chamber]));
	GetDlgItem(IDC_CAL34)->SetWindowText(ValueToString(pDoc->Calibrations[16][1][Chamber]));
	GetDlgItem(IDC_CAL35)->SetWindowText(ValueToString(pDoc->Calibrations[17][0][Chamber]));
	GetDlgItem(IDC_CAL36)->SetWindowText(ValueToString(pDoc->Calibrations[17][1][Chamber]));
	GetDlgItem(IDC_CAL37)->SetWindowText(ValueToString(pDoc->Calibrations[18][0][Chamber]));
	GetDlgItem(IDC_CAL38)->SetWindowText(ValueToString(pDoc->Calibrations[18][1][Chamber]));
	GetDlgItem(IDC_CAL39)->SetWindowText(ValueToString(pDoc->Calibrations[19][0][Chamber]));
	GetDlgItem(IDC_CAL40)->SetWindowText(ValueToString(pDoc->Calibrations[19][1][Chamber]));
	GetDlgItem(IDC_CAL41)->SetWindowText(ValueToString(pDoc->Calibrations[20][0][Chamber]));
	GetDlgItem(IDC_CAL42)->SetWindowText(ValueToString(pDoc->Calibrations[20][1][Chamber]));
	GetDlgItem(IDC_CAL43)->SetWindowText(ValueToString(pDoc->Calibrations[21][0][Chamber]));
	GetDlgItem(IDC_CAL44)->SetWindowText(ValueToString(pDoc->Calibrations[21][1][Chamber]));

}

void SetCalibration::Save()
{
	CString temp;
	GetDlgItem(IDC_CAL1)->GetWindowText(temp);
	pDoc->Calibrations[0][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL2)->GetWindowText(temp);
	pDoc->Calibrations[0][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL3)->GetWindowText(temp);
	pDoc->Calibrations[1][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL4)->GetWindowText(temp);
	pDoc->Calibrations[1][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL5)->GetWindowText(temp);
	pDoc->Calibrations[2][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL6)->GetWindowText(temp);
	pDoc->Calibrations[2][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL7)->GetWindowText(temp);
	pDoc->Calibrations[3][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL8)->GetWindowText(temp);
	pDoc->Calibrations[3][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL9)->GetWindowText(temp);
	pDoc->Calibrations[4][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL10)->GetWindowText(temp);
	pDoc->Calibrations[4][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL11)->GetWindowText(temp);
	pDoc->Calibrations[5][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL12)->GetWindowText(temp);
	pDoc->Calibrations[5][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL13)->GetWindowText(temp);
	pDoc->Calibrations[6][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL14)->GetWindowText(temp);
	pDoc->Calibrations[6][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL15)->GetWindowText(temp);
	pDoc->Calibrations[7][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL16)->GetWindowText(temp);
	pDoc->Calibrations[7][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL17)->GetWindowText(temp);
	pDoc->Calibrations[8][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL18)->GetWindowText(temp);
	pDoc->Calibrations[8][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL19)->GetWindowText(temp);
	pDoc->Calibrations[9][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL20)->GetWindowText(temp);
	pDoc->Calibrations[9][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL21)->GetWindowText(temp);
	pDoc->Calibrations[10][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL22)->GetWindowText(temp);
	pDoc->Calibrations[10][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL23)->GetWindowText(temp);
	pDoc->Calibrations[11][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL24)->GetWindowText(temp);
	pDoc->Calibrations[11][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL25)->GetWindowText(temp);
	pDoc->Calibrations[12][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL26)->GetWindowText(temp);
	pDoc->Calibrations[12][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL27)->GetWindowText(temp);
	pDoc->Calibrations[13][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL28)->GetWindowText(temp);
	pDoc->Calibrations[13][1][Chamber]=stringtodouble(temp);		
	GetDlgItem(IDC_CAL29)->GetWindowText(temp);
	pDoc->Calibrations[14][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL30)->GetWindowText(temp);
	pDoc->Calibrations[14][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL31)->GetWindowText(temp);
	pDoc->Calibrations[15][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL32)->GetWindowText(temp);
	pDoc->Calibrations[15][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL33)->GetWindowText(temp);
	pDoc->Calibrations[16][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL34)->GetWindowText(temp);
	pDoc->Calibrations[16][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL35)->GetWindowText(temp);
	pDoc->Calibrations[17][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL36)->GetWindowText(temp);
	pDoc->Calibrations[17][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL37)->GetWindowText(temp);
	pDoc->Calibrations[18][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL38)->GetWindowText(temp);
	pDoc->Calibrations[18][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL39)->GetWindowText(temp);
	pDoc->Calibrations[19][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL40)->GetWindowText(temp);
	pDoc->Calibrations[19][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL41)->GetWindowText(temp);
	pDoc->Calibrations[20][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL42)->GetWindowText(temp);
	pDoc->Calibrations[20][1][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL43)->GetWindowText(temp);
	pDoc->Calibrations[21][0][Chamber]=stringtodouble(temp);
	GetDlgItem(IDC_CAL44)->GetWindowText(temp);
	pDoc->Calibrations[21][1][Chamber]=stringtodouble(temp);

}
