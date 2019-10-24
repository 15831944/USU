// CloseWindowsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MFC Document Editor.h"
#include "CloseWindowsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowsDialog dialog


CCloseWindowsDialog::CCloseWindowsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCloseWindowsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCloseWindowsDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCloseWindowsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCloseWindowsDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCloseWindowsDialog, CDialog)
	//{{AFX_MSG_MAP(CCloseWindowsDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowsDialog message handlers
