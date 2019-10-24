// HelpDialog.cpp : implementation file
//

#include <AfxWin.h>
#include <AfxExt.h>
#include "resource.h"
#include "HelpDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// HelpDialog dialog


HelpDialog::HelpDialog(CWnd* pParent /*=NULL*/)
	: CDialog(HelpDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(HelpDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void HelpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(HelpDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HelpDialog, CDialog)
	//{{AFX_MSG_MAP(HelpDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HelpDialog message handlers

BOOL HelpDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetWindowText("The Cube Demo");

	text1.Create( 10, 8, "Cutting-Edge Direct3D", this, "MS SansSerif", 14 );
	text2.Create( 10, 28, "Programming", this, "MS SansSerif", 14 );
	
	text1.SetTextColor( GetSysColor( COLOR_WINDOWTEXT ) );
	text1.SetBkColor( GetSysColor( COLOR_3DFACE ) );
	text2.SetTextColor( GetSysColor( COLOR_WINDOWTEXT ) );
	text2.SetBkColor( GetSysColor( COLOR_3DFACE ) );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
