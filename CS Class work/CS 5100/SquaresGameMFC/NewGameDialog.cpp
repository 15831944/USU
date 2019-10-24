// NewGameDialog.cpp : implementation file
//

#include "stdafx.h"
#include "squaresgame.h"
#include "NewGameDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NewGameDialog dialog


NewGameDialog::NewGameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(NewGameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(NewGameDialog)
	m_GameSize = 0;
	//}}AFX_DATA_INIT
}


void NewGameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NewGameDialog)
	DDX_Text(pDX, IDC_EDIT1, m_GameSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NewGameDialog, CDialog)
	//{{AFX_MSG_MAP(NewGameDialog)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewGameDialog message handlers

BOOL NewGameDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);
	m_GameSize = 3;
	m_GameType = 1;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void NewGameDialog::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	if (m_GameSize < 3 || m_GameSize > 10)
	{
		MessageBox("Game Size must between a number between 3 and 10.","Error",MB_ICONINFORMATION);
	}
	else
	{
		CDialog::OnOK();
	}
}

void NewGameDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void NewGameDialog::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_GameType = 1;
}

void NewGameDialog::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_GameType = 2;
}

void NewGameDialog::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	m_GameType = 3;
}
