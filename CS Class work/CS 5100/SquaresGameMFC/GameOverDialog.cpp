// GameOverDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SquaresGame.h"
#include "GameOverDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog dialog


GameOverDialog::GameOverDialog(CString name, int score, bool isTie, CWnd* pParent /*=NULL*/)
	: CDialog(GameOverDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(GameOverDialog)
	m_text1 = _T("");
	m_text2 = _T("");
	//}}AFX_DATA_INIT
	if (isTie)
	{
		m_text1 = "The game was a tie.";
		m_text2 = "";
	}
	else
	{
		m_text1.Format("%s has won!!!",name);
		m_text2.Format("%s had a score of %i%%",name,score);
	}
}


void GameOverDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GameOverDialog)
	DDX_Text(pDX, IDC_TEXT1, m_text1);
	DDX_Text(pDX, IDC_TEXT2, m_text2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GameOverDialog, CDialog)
	//{{AFX_MSG_MAP(GameOverDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog message handlers
