// ModelessD.cpp : implementation file
//

#include "stdafx.h"
#include "Drawing.h"
#include "MyButton.h"
#include "ModelessD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ModelessD dialog


ModelessD::ModelessD(CWnd* pParent /*=NULL*/)
	: CDialog(ModelessD::IDD, pParent)
{
	//{{AFX_DATA_INIT(ModelessD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pParent = pParent;
	m_nID = ModelessD::IDD;
}


void ModelessD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ModelessD)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ModelessD, CDialog)
	//{{AFX_MSG_MAP(ModelessD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ModelessD message handlers

void ModelessD::PostNcDestroy() 
{
	
	delete this;
}

void ModelessD::OnOK() 
{
	
	DestroyWindow();
}

BOOL ModelessD::Create()
{
	BOOL result = CDialog::Create(m_nID, m_pParent);
	MyButton * p = (MyButton *)m_pParent;
	char number[2];
	sprintf(number, "%d", ++(p->dialogNumber));
	SetWindowText(number);
	return result;
	
}

void ModelessD::OnCancel() 
{
	// TODO: Add extra cleanup here
	OnOK();	
}
