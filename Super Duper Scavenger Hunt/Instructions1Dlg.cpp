// Instructions1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Super Duper Scavenger Hunt.h"
#include "Instructions1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstructions1Dlg dialog


CInstructions1Dlg::CInstructions1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInstructions1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInstructions1Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInstructions1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstructions1Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInstructions1Dlg, CDialog)
	//{{AFX_MSG_MAP(CInstructions1Dlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstructions1Dlg message handlers
