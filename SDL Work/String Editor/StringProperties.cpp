// StringProperties.cpp : implementation file
//

#include "stdafx.h"
#include "String Editor.h"
#include "StringProperties.h"

#include "StringInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// StringProperties dialog


StringProperties::StringProperties(CString* nlang, int lang,CStringInfo* dat, CFont* font,CWnd* pParent /*=NULL*/)
	: CDialog(StringProperties::IDD, pParent)
{
	mlang=lang;
	m_data=dat;
	propfont=font;
	clang=0;
	nlanguages=nlang;
	//{{AFX_DATA_INIT(StringProperties)
	m_vel1 = _T("");
	m_l1 = _T("");
	//}}AFX_DATA_INIT
}

StringProperties::~StringProperties()
{
//	delete []m_data;
}

void StringProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StringProperties)
	DDX_Control(pDX, IDC_L1, m_cl1);
	DDX_Control(pDX, IDC_EL1, m_cel1);
	DDX_Control(pDX, IDC_ID, m_cid);
	DDX_Text(pDX, IDC_ID, m_id);
	DDX_Text(pDX, IDC_EL1, m_vel1);
	DDX_Text(pDX, IDC_L1, m_l1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StringProperties, CDialog)
	//{{AFX_MSG_MAP(StringProperties)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_LNEXT, OnLnext)
	ON_BN_CLICKED(IDC_LPREV, OnLprev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StringProperties message handlers

void StringProperties::OnOK() 
{
	CWnd * focus=GetFocus();
	if(focus==GetDlgItem(IDC_ID))
	{
		GetDlgItem(IDC_EL1)->SetFocus();
		return;
	}
	if(focus==GetDlgItem(IDC_EL1))
	{
		clang++;
		if (clang<mlang)
		{
			m_cl1.SetWindowText(nlanguages[clang]);
			UpdateData(TRUE);
			m_data->m_Strings[clang-1]=m_vel1;
			m_vel1=m_data->m_Strings[clang];
			m_cel1.SetWindowText(m_data->m_Strings[clang]);			
			GetDlgItem(IDC_EL1)->SetFocus();
			return;
		}
	}
	if (focus==GetDlgItem(IDOK))
		clang++;
	UpdateData(TRUE);
	m_data->m_Symbol=m_id;
	m_data->m_Strings[clang-1]=m_vel1;

	
//	m_data->m_Strings[1]=m_russian;
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void StringProperties::OnClose() 
{
//	GetDlgItem(IDOK)->SetFocus();
//	OnOK();
	OnCancel();
}

BOOL StringProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_ID)->SetFocus();

	m_id = m_data->m_Symbol;
	if (m_id=="") 
		m_id="IDS_";
	m_cid.SetFont(propfont);
	m_cel1.SetFont(propfont);
	m_vel1=m_data->m_Strings[clang];
	UpdateData(FALSE);
	m_cl1.SetWindowText(nlanguages[0]);

	// TODO: Add extra initialization here

	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void StringProperties::OnLnext() 
{
	clang++;
	if (clang<mlang)
	{
		m_cl1.SetWindowText(nlanguages[clang]);
		UpdateData(TRUE);
		m_data->m_Strings[clang-1]=m_vel1;
		m_vel1=m_data->m_Strings[clang];
		m_cel1.SetWindowText(m_data->m_Strings[clang]);			
		UpdateData(FALSE);
		return;
	}
	else
		clang--;

}

void StringProperties::OnLprev() 
{
	clang--;
	if (clang>-1)
	{
		m_cl1.SetWindowText(nlanguages[clang]);
		UpdateData(TRUE);
		m_data->m_Strings[clang+1]=m_vel1;
		m_vel1=m_data->m_Strings[clang];
		m_cel1.SetWindowText(m_data->m_Strings[clang]);			
		UpdateData(FALSE);
		return;
	}
	else
		clang++;
}
