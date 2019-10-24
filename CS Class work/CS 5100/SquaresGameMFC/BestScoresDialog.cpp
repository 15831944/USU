// BestScoresDialog.cpp : implementation file
//

#include "stdafx.h"
#include "SquaresGame.h"
#include "BestScoresDialog.h"
#include "SquareGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BestScoresDialog dialog


BestScoresDialog::BestScoresDialog(SquareGame * pGame, CWnd* pParent /*=NULL*/)
	: CDialog(BestScoresDialog::IDD, pParent)
{
	ptrGame = pGame;
	//{{AFX_DATA_INIT(BestScoresDialog)
	//}}AFX_DATA_INIT
	for (int i = 0; i < pGame->bestScoreCount; i++)
	{
		text[i].Format("%i.\t%s\t%i%%",i+1,pGame->bestNames[i],pGame->bestScores[i]);
	}
}


void BestScoresDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BestScoresDialog)
	DDX_Text(pDX, IDC_S1, text[0]);
	DDX_Text(pDX, IDC_S2, text[1]);
	DDX_Text(pDX, IDC_S3, text[2]);
	DDX_Text(pDX, IDC_S4, text[3]);
	DDX_Text(pDX, IDC_S5, text[4]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BestScoresDialog, CDialog)
	//{{AFX_MSG_MAP(BestScoresDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BestScoresDialog message handlers

BOOL BestScoresDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
