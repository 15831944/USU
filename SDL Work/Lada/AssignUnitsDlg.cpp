// AssignUnitsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "AssignUnitsDlg.h"
#include "LADA Control ModuleDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAssignUnitsDlg dialog


CAssignUnitsDlg::CAssignUnitsDlg(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CAssignUnitsDlg::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CAssignUnitsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAssignUnitsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAssignUnitsDlg)
	DDX_Control(pDX, IDC_INPUT_LOCATION_LIST, m_ILList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAssignUnitsDlg, CDialog)
	//{{AFX_MSG_MAP(CAssignUnitsDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_INPUT_LOCATION_LIST, OnDblclkInputLocationList)
	ON_BN_CLICKED(IDC_UNITS, OnUnits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAssignUnitsDlg message handlers

BOOL CAssignUnitsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_ILList.
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAssignUnitsDlg::OnDblclkInputLocationList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CAssignUnitsDlg::OnUnits() 
{
	// TODO: Add your control notification handler code here
	
}
