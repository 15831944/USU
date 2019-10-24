// This is Version 1.0 PLEASE DOCUMENT CHANGES
// ViewHistoryDialog.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ViewHistoryDialog.h"
#include "LADA Control ModuleDoc.h"
#include "HistoryClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int curLanguage;
extern CFont RussianArial;
/////////////////////////////////////////////////////////////////////////////
// CViewHistoryDialog dialog


CViewHistoryDialog::CViewHistoryDialog(CViewHistoryDialog ** ptrDlg, CHistoryClass * pHistory, CWnd* pParent /*=NULL*/)
	: CDialog(CViewHistoryDialog::IDD, pParent)
{
	ptrHistory = pHistory;
	ptrHistoryDlg = ptrDlg;
	//{{AFX_DATA_INIT(CViewHistoryDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CViewHistoryDialog::~CViewHistoryDialog()
{
	if (ptrHistoryDlg)
		(*ptrHistoryDlg) = NULL;	
}

void CViewHistoryDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewHistoryDialog)
	DDX_Control(pDX, IDC_HISTORYLIST, m_ListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewHistoryDialog, CDialog)
	//{{AFX_MSG_MAP(CViewHistoryDialog)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewHistoryDialog message handlers


void CViewHistoryDialog::OnSize(UINT nType, int cx, int cy) 
{
	if (m_ListCtrl.m_hWnd)
		m_ListCtrl.SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER|SWP_SHOWWINDOW);
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	switch (nType)
	{
	case SIZE_MAXIMIZED://   Window has been maximized.
		{

		} break;
	case SIZE_MINIMIZED://   Window has been minimized.
		{

		} break;
	case SIZE_RESTORED://   Window has been resized, but neither SIZE_MINIMIZED nor SIZE_MAXIMIZED applies.
		{
			
		} break;
	case SIZE_MAXHIDE://   Message is sent to all pop-up windows when some other window is maximized.
		{

		} break;
	case SIZE_MAXSHOW://
		{

		} break;
	}
}

BOOL CViewHistoryDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int curFile = curLanguage;
	m_ListCtrl.SetFont(&RussianArial);
	
	SetWindowText( ptrHistory->pDoc->dataFolder + "\\" + ptrHistory->m_FileNames[curFile] );
	SetWindowPos( &wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW );
	
	CString textLine;
	ptrHistory->OpenFiles();
	ptrHistory->m_ptrFiles[curFile].SeekToBegin();
	CArchive fArchive( &ptrHistory->m_ptrFiles[curFile], CArchive::load );
	while (fArchive.ReadString(textLine))
	{
		m_ListCtrl.AddString(textLine);
	}
	fArchive.Close();
	ptrHistory->CloseFiles();
	m_ListCtrl.SetCurSel(m_ListCtrl.GetCount()-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewHistoryDialog::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	CDialog::PostNcDestroy();
	
}


void CViewHistoryDialog::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CViewHistoryDialog::OnClose() 
{
	EndDialog(IDOK);
	delete (*ptrHistoryDlg);  // pDoc->m_ptrHistoryDlg
}
