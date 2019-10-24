// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "stdafx.h"
#include "MFC Document Editor.h"

#include "ChildFrm.h"
#include "MFC Document EditorView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

//extern CChildFrame ** m_Frames;
//extern int m_FrameCount;

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;
	//m_Frames[m_FrameCount++] = this;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers

void CChildFrame::OnSetFocus(CWnd* pOldWnd) 
{
	CMDIChildWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CMFCDocumentEditorView * pView = (CMFCDocumentEditorView *) GetActiveView();
	CMainFrame * pFrame = (CMainFrame *) GetMDIFrame();

	if (pView && pFrame)
	{
		CHARFORMAT cf;
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_SIZE | CFM_FACE;
		
		CComboBox * ptrCombo = (CComboBox *)pFrame->m_DialogBar.GetDlgItem(IDC_SIZE_BOX);
		cf.yHeight = ptrCombo->GetItemData(ptrCombo->GetCurSel()) * 1440 / 60;
		char text[64];
		ptrCombo->GetLBText(ptrCombo->GetCurSel(),(LPTSTR)text);
		strcpy((char *)(&cf.szFaceName[0]),text);

		pView->GetRichEditCtrl().SetSelectionCharFormat( cf );
	}
}
