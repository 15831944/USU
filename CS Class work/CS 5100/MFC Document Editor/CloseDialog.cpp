// CloseDialog.cpp : implementation file
//

#include "stdafx.h"
#include "MFC Document Editor.h"
#include "CloseDialog.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCloseDialog dialog


CCloseDialog::CCloseDialog(CMainFrame * ptrFrame, CWnd* pParent /*=NULL*/)
	: CDialog(CCloseDialog::IDD, pParent)
{
	ptrMainFrame = ptrFrame;
	//{{AFX_DATA_INIT(CCloseDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCloseDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCloseDialog)
	DDX_Control(pDX, IDC_LIST1, m_windowList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCloseDialog, CDialog)
	//{{AFX_MSG_MAP(CCloseDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCloseDialog message handlers

BOOL CCloseDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFrameWnd * ptrFrame = ptrMainFrame->GetActiveFrame();
	CString windowTitle;
	int index;
	
	while (ptrFrame)
	{
		ptrFrame->GetWindowText(windowTitle);
		index = m_windowList.AddString(windowTitle);
		m_windowList.SetItemData(index, (unsigned long) ptrFrame);
		ptrFrame = (CFrameWnd *) ptrFrame->GetNextWindow();
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCloseDialog::OnOK() 
{
	// TODO: Add extra validation here

   for (int i=0;i < m_windowList.GetCount();i++)
   {
	  if (m_windowList.GetSel(i) > 0)
	  {
		((CChildFrame *)m_windowList.GetItemData(i))->SendMessage(WM_CLOSE,0,0);
	  }
   }


	CDialog::OnOK();
}

void CCloseDialog::OnSelchangeList1() 
{
	GetDlgItem(IDOK)->EnableWindow(m_windowList.GetSelCount() > 0);
}
