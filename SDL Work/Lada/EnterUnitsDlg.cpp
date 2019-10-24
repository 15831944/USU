// EnterUnitsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "EnterUnitsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnterUnitsDlg dialog


CEnterUnitsDlg::CEnterUnitsDlg(CString * data, CWnd* pParent /*=NULL*/)
	: CDialog(CEnterUnitsDlg::IDD, pParent)
{
	ptrReturnData = data;
	//{{AFX_DATA_INIT(CEnterUnitsDlg)
	m_data = *data;
	//}}AFX_DATA_INIT
}


void CEnterUnitsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnterUnitsDlg)
	DDX_Text(pDX, IDC_EDIT1, m_data);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEnterUnitsDlg, CDialog)
	//{{AFX_MSG_MAP(CEnterUnitsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnterUnitsDlg message handlers

void CEnterUnitsDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	*ptrReturnData = m_data;
	CDialog::OnOK();
}
