// Instructions2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Super Duper Scavenger Hunt.h"
#include "Instructions2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstructions2Dlg dialog


CInstructions2Dlg::CInstructions2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstructions2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstructions2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInstructions2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstructions2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInstructions2Dlg, CDialog)
	//{{AFX_MSG_MAP(CInstructions2Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstructions2Dlg message handlers
