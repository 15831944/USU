// This is Version 1.0 PLEASE DOCUMENT CHANGES
// GraphWindow.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "GraphWindow.h"

#include "GraphButtonForm.h"
#include "GraphDisplayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphWindow

IMPLEMENT_DYNCREATE(CGraphWindow, CFrameWnd)

CGraphWindow::CGraphWindow()
{
}

CGraphWindow::~CGraphWindow()
{
}


BEGIN_MESSAGE_MAP(CGraphWindow, CFrameWnd)
	//{{AFX_MSG_MAP(CGraphWindow)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	//ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphWindow message handlers

BOOL CGraphWindow::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CCreateContext * oContext = (CCreateContext*) lpcs->lpCreateParams;

	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CGraphButtonForm), CSize(240, 100), oContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGraphDisplayView), CSize(240, 100), oContext))
	
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	return TRUE;
}

/*
BOOL CGraphWindow::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
   // need to handle both ANSI and UNICODE versions of the message
   TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
   //TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;   
   CString strTipText;
   UINT nID = pNMHDR->idFrom;
   if (pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND))// ||
      //pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))   
   {
      // idFrom is actually the HWND of the tool
      nID = ::GetDlgCtrlID((HWND)nID);   
   }
   if (nID != 0) // will be zero on a separator
      strTipText.Format("Control ID = %d", nID);
   if (pNMHDR->code == TTN_NEEDTEXTA)
      lstrcpyn(pTTTA->szText, strTipText, sizeof(pTTTA->szText));   
   //else
    //  _mbstowcsz(pTTTW->szText, strTipText, sizeof(pTTTW->szText));
   *pResult = 0;   
   return TRUE;    // message was handled
}
*/