// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Baby Steps.h"

#include "MainFrm.h"
#include "Baby StepsDoc.h"

#include "Buttons.h"

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
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

/*
void CMainFrame::CreateToolBar()
{
	
	if (!m_wndToolBar.CreateEx(this))
	{
		TRACE0("Failed to create toolbar\n");
		return;      // fail to create
	}
	
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(16, 20); 
	// (min button width, max button width) in pixels
	//m_wndToolBar.SetFont(&SmallRussianArial);

	//m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	// (using this style allows buttons to have a drop down menu)
	
	CImageList img;
	img.Create(IDB_HOT_TOOLBAR, 16, 0, RGB(255, 0, 255)); //IDB_BITMAP1
	// (the resource ID, the size of each image (in pixels), 
	// the number of images the list can grow by,
	// mask color - transparent color ??)
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	// imlements 'hot buttons' (CImageList *object)
	img.Detach();
	// detaches an image list object from a CImageList object
	// (probably so the object 'img' can be used again 
	// in the next line of code
	img.Create(IDB_NORMAL_TOOLBAR, 16, 0, RGB(255, 0, 255));
	// same as preceding
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	// sets the cold image list for the cold toolbar buttons
	img.Detach();

	img.Create(IDB_DISABLED_TOOLBAR, 16, 0, RGB(255, 0, 255));
	// same as preceding
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&img);
	// sets the cold image list for the cold toolbar buttons
	img.Detach();

	// TODO: Remove this if you don't want tool tips
	//m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
	//	CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT);
	// CWnd member function (styles to remove, styles to add, flags
	// to be passed to SetWindowPos.  If ommitted, SetWindowPos is
	// not called.  
	m_wndToolBar.SetButtons(NULL, BUTTONS);
	// points to an array of command IDs.  It can be NULL to allocate
	// empty buttons.  SetButtonInfo can then be used to set button
	// attributes.
	
	// set up each toolbar button
	for (int i = 0; i < BUTTONS; i++)
		m_wndToolBar.SetButtonInfo(	i, // Index of the button or separator
									RES_BUT_ID[ButtonOrder[i]], //command ID
									RES_BUT_STYLE[ButtonOrder[i]], //new button style
									ButtonOrder[i] // New index for the button’s image within the bitmap.
								  );

	//for ( i = 0; i < BUTTONS; i++){
	//	m_wndToolBar.SetButtonText(	i, Strings.get(RES_BUT_IDS[ButtonOrder[i]]));
	//}
	//SetToolbarText();

	//this->LoadResStrings();
	
	CRect rectToolBar;
	// set up toolbar button sizes
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	// gets size of a button (index of button, rect object) 
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(16,15));
	// sets button sizes (size of button, size of image) in pixels
	
}
*/

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	/*
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	*/
	
	if (!m_DialogBar.Create(this,IDD_DIALOGBAR,CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_GRIPPER,IDD_DIALOGBAR))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}
	SaveButton.AutoLoad(IDC_SAVE,&m_DialogBar);
	PlayButton.AutoLoad(IDC_PLAY,&m_DialogBar);
	PauseButton.AutoLoad(IDC_PAUSE,&m_DialogBar);
	//CreateToolBar();
	/*
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	*/

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);

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


void CMainFrame::OnPlay() 
{
	// TODO: Add your command handler code here
	CBabyStepsDoc * pDoc = (CBabyStepsDoc * )GetActiveDocument();
	if (!pDoc->hasStart)
	{
		MessageBox("You must create a start state first.","Error",MB_ICONINFORMATION);
		return;
	}
	if (!pDoc->hasGoal)
	{
		MessageBox("You must create a goal state first.","Error",MB_ICONINFORMATION);
		return;
	}

	pDoc->state = Running;
	//UpdateToolBar();
	//MessageBox("OnStart()");
	UpdateDialogBar();
	pDoc->RunAlgorithm();
}

void CMainFrame::OnPause() 
{
	// TODO: Add your command handler code here
	CBabyStepsDoc * pDoc = (CBabyStepsDoc * )GetActiveDocument();
	pDoc->state = Editting;
	//UpdateToolBar();
	//MessageBox("OnPause()");
	UpdateDialogBar();
	//pDoc->DoMessages();
}

void CMainFrame::OnStop() 
{
	// TODO: Add your command handler code here
	CBabyStepsDoc * pDoc = (CBabyStepsDoc * )GetActiveDocument();
	pDoc->state = Editting;
	//UpdateToolBar();
	//MessageBox("OnStop()");
	UpdateDialogBar();
}
/*
void CMainFrame::UpdateToolBar()
{
	CBabyStepsDoc * pDoc = (CBabyStepsDoc * )GetActiveDocument();
	//m_wndToolBar.GetToolBarCtrl().EnableButton();//m_wndToolBar.CommandToIndex()
	if (pDoc)
	{
		//m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_NEW, pDoc->state == Editting);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_OPEN, pDoc->state == Editting);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_SAVE, pDoc->state == Editting);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_PLAY, pDoc->state == Editting);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_PAUSE, pDoc->state == Running);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_STOP, pDoc->state == Running);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_START_STATE, pDoc->state == Editting);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_GOAL_STATE, pDoc->state == Editting);
		m_wndToolBar.GetToolBarCtrl().EnableButton(ID_OBSTACLE, pDoc->state == Editting);
		//m_wndToolBar.GetToolBarCtrl().SetButtonState(ID_OBSTACLE, pDoc->state == Editting);
		//m_wndToolBar.GetToolBarCtrl().EnableButton(2, pDoc->state == Editting);
		//m_wndToolBar.GetToolBarCtrl().EnableButton(3, pDoc->state == Running);
		m_wndToolBar.GetToolBarCtrl().SetState(ID_FILE_NEW, TBBS_DISABLED);
	}
}

*/


void CMainFrame::UpdateDialogBar()
{
		//m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_NEW, pDoc->state == Editting);
	CBabyStepsDoc * pDoc = (CBabyStepsDoc * )GetActiveDocument();
	if (pDoc)
	{
		m_DialogBar.GetDlgItem(IDC_NEW)->EnableWindow(pDoc->state == Editting);
		m_DialogBar.GetDlgItem(IDC_OPEN)->EnableWindow(pDoc->state == Editting);
		m_DialogBar.GetDlgItem(IDC_SAVE)->EnableWindow(pDoc->state == Editting);
		m_DialogBar.GetDlgItem(IDC_PLAY)->EnableWindow(pDoc->state == Editting);
		m_DialogBar.GetDlgItem(IDC_PAUSE)->EnableWindow(pDoc->state == Running);
		m_DialogBar.GetDlgItem(IDC_STOP)->EnableWindow(pDoc->state == Running);
	}
}
