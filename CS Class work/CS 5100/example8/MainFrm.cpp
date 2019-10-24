// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "junk3.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON32771, OnButton32771)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_MYNEWPANE, OnUpdateMyNewPane) //added
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_MYNEWPANE,  //added
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_paneString = "Real default string"; //added
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	CClientDC dc(this);
	SIZE size = dc.GetTextExtent(m_paneString);  //added
	int index = m_wndStatusBar.CommandToIndex(ID_MYNEWPANE);
	m_wndStatusBar.SetPaneInfo(index, ID_MYNEWPANE, SBPS_POPOUT, size.cx);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnButton32771() 
{
	// TODO: Add your command handler code here
	
	//m_paneString.Format("%d,%d", point.x, point.y);
	m_paneString = "Another string";
	int index = m_wndStatusBar.CommandToIndex(ID_MYNEWPANE);
	CClientDC dc(this);
	SIZE size = dc.GetTextExtent(m_paneString);
	m_wndStatusBar.SetPaneInfo(index, ID_MYNEWPANE, SBPS_NORMAL, size.cx);
}

void CMainFrame::OnUpdateMyNewPane(CCmdUI *pCmdUI) //added
{
	pCmdUI->Enable();
	pCmdUI->SetText(m_paneString);
}

