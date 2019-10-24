// EventListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "client.h"
#include "EventListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEventListDlg dialog


CEventListDlg::CEventListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEventListDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEventListDlg)
	m_end = _T("");
	m_list = _T("");
	m_start = _T("");
	//}}AFX_DATA_INIT
}


void CEventListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEventListDlg)
	DDX_Text(pDX, IDC_END, m_end);
	DDX_Text(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_START, m_start);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEventListDlg, CDialog)
	//{{AFX_MSG_MAP(CEventListDlg)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEventListDlg message handlers

void CEventListDlg::OnQuery() 
{
	// TODO: Add your control notification handler code here
	
}
