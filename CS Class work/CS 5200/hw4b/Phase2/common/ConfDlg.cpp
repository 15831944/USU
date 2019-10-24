// ConfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "../server/server.h"
#include "../common/ConfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfDlg dialog


CConfDlg::CConfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfDlg)
	m_conf_file = _T("");
	//}}AFX_DATA_INIT
}


void CConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfDlg)
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_conf_file);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfDlg, CDialog)
	//{{AFX_MSG_MAP(CConfDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfDlg message handlers
