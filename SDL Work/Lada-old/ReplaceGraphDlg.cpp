// ReplaceGraphDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ReplaceGraphDlg.h"
#include "LADA Control ModuleDoc.h"
#include "GraphCollection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReplaceGraphDlg dialog


CReplaceGraphDlg::CReplaceGraphDlg(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CReplaceGraphDlg::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CReplaceGraphDlg)
	m_wGraph = -1;
	//}}AFX_DATA_INIT
}


void CReplaceGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReplaceGraphDlg)
	DDX_Control(pDX, IDC_GRAPH_LIST, m_cGraphList);
	DDX_LBIndex(pDX, IDC_GRAPH_LIST, m_wGraph);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReplaceGraphDlg, CDialog)
	//{{AFX_MSG_MAP(CReplaceGraphDlg)
	ON_LBN_SELCHANGE(IDC_GRAPH_LIST, OnSelchangeGraphList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReplaceGraphDlg message handlers

BOOL CReplaceGraphDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CReplaceGraphDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	for (int i = 0; i < pDoc->nGraphCollections; i++)
		m_cGraphList.AddString(pDoc->GraphCollection[i].name);

	GetDlgItem(IDOK)->EnableWindow(m_wGraph >= 0);
	UpdateData(FALSE);
	SetStrings();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReplaceGraphDlg::SetStrings()
{

}

void CReplaceGraphDlg::OnSelchangeGraphList() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDOK)->EnableWindow(m_wGraph >= 0);
}
