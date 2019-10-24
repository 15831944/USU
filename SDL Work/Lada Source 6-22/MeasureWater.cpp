// MeasureWater.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "MeasureWater.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeasureWater dialog


CMeasureWater::CMeasureWater(CString text, double * volume, CWnd* pParent /*=NULL*/)
	: CDialog(CMeasureWater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeasureWater)
	m_volume = *volume;
	//}}AFX_DATA_INIT
	ptrVolume = volume;
}


void CMeasureWater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeasureWater)
	DDX_Text(pDX, IDC_EDIT1, m_volume);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeasureWater, CDialog)
	//{{AFX_MSG_MAP(CMeasureWater)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureWater message handlers

void CMeasureWater::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	GetDlgItem(IDOK)->EnableWindow(GetDlgItem(IDC_EDIT1)->GetWindowTextLength());
		
	
}

void CMeasureWater::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	*ptrVolume = m_volume;
	CDialog::OnOK();
}
