// ChooseIcon.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ChooseIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChooseIcon dialog


CChooseIcon::CChooseIcon(BOOL *var, CWnd* pParent /*=NULL*/)
	: CDialog(CChooseIcon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseIcon)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Floppy = var;
}


void CChooseIcon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseIcon)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseIcon, CDialog)
	//{{AFX_MSG_MAP(CChooseIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseIcon message handlers

void CChooseIcon::OnOK() 
{
	// TODO: Add extra validation here
	*m_Floppy = ((CButton *)GetDlgItem(IDC_FLOPPY))->GetCheck();
	CDialog::OnOK();
}

BOOL CChooseIcon::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
