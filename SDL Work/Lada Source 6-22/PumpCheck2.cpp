// PumpCheck2.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "PumpCheck2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PumpCheck2 dialog


PumpCheck2::PumpCheck2(CWnd* pParent /*=NULL*/)
	: CDialog(PumpCheck2::IDD, pParent)
{
	//{{AFX_DATA_INIT(PumpCheck2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PumpCheck2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PumpCheck2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PumpCheck2, CDialog)
	//{{AFX_MSG_MAP(PumpCheck2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PumpCheck2 message handlers
