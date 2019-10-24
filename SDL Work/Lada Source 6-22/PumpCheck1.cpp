// PumpCheck1.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "PumpCheck1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PumpCheck1 dialog


PumpCheck1::PumpCheck1(CWnd* pParent /*=NULL*/)
	: CDialog(PumpCheck1::IDD, pParent)
{
	//{{AFX_DATA_INIT(PumpCheck1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PumpCheck1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PumpCheck1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PumpCheck1, CDialog)
	//{{AFX_MSG_MAP(PumpCheck1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PumpCheck1 message handlers
