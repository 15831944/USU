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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphWindow message handlers

BOOL CGraphWindow::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CCreateContext * oContext = (CCreateContext*) lpcs->lpCreateParams;

	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CGraphButtonForm), CSize(100, 100), oContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CGraphDisplayView), CSize(100, 100), oContext))
	
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	return TRUE;
}
