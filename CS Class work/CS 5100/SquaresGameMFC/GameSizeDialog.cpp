// GameSizeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "squaresgame.h"
#include "GameSizeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GameSizeDialog dialog


GameSizeDialog::GameSizeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(GameSizeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(GameSizeDialog)
	m_GameSize = 0;
	//}}AFX_DATA_INIT
}


void GameSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GameSizeDialog)
	DDX_Text(pDX, IDC_EDIT1, m_GameSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GameSizeDialog, CDialog)
	//{{AFX_MSG_MAP(GameSizeDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GameSizeDialog message handlers

void GameSizeDialog::OnOK() 
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
