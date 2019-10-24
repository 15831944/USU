// This is Version 1.0 PLEASE DOCUMENT CHANGES
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LADA Control Module.h"

#include "MainFrm.h"
#include "LADA Control ModuleView.h"

#include "GraphWindow.h"
#include "LADA Control ModuleDoc.h"
#include "ChooseLocationsDialog.h"
#include "ToolBar.h"
#include "GraphProperties.h"
#include "DataTransfer.h"
#include "SystemDiagDlg.h"
#include "ParamMenu.h"
#include "ManualSample.h"
#include "LanguageChanger.h"
#include "ViewHistoryDialog.h"
#include "Camera.h"
#include "Htmlhelp.h"


#include "LString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

extern int curLanguage;
extern CCamera * cameraDlg;
int GetCurrentLanguage();
extern LString Strings;
extern CFont SmallRussianArial;
extern CFont RussianArial;
extern CFont LargeRussianArial;
extern CString workingDirectory;


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_CHANGE_LANGUAGE, OnChangeLanguage)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	// Global help commands
//	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
//	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
//	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
//	ON_COMMAND(ID_DEFAULT_HELP, CFrameWnd::OnHelpFinder)
	//ON_BN_CLICKED(IDC_AUTOWRAP, OnAutoWrap)
	//ON_BN_CLICKED(IDC_EDITLIST, OnEditGraphList)
	ON_COMMAND_RANGE(IDC_DATA_TRANSFER, IDC_EXIT, OnToolBarButton)
	ON_MESSAGE(WM_SWITCH_LANGUAGE, OnSwitchLanguage)
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

	nGraphs = 3; // default
}

CMainFrame::~CMainFrame()
{
	delete m_wndSplitter2;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();
	//	pDoc->m_FrameWnd = this;

	//myFont = new CFont();
	//myFont->CreateFont(20,0,0,0,FW_NORMAL,0,0,0,RUSSIAN_CHARSET,0,0,0,0,"Arial");

		// this function first creates a toolbar, then a dialog bar, then a rebar, to which
	// it adds the toolbar and dialog bar.
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CreateToolBar();

	//if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
	//	CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	//{
	//	TRACE0("Failed to create dialogbar\n");
	//	return -1;		// fail to create
	//}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar))// ||
		//!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}
	m_wndReBar.GetReBarCtrl().MaximizeBand(0);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	m_wndSplitter.SetColumnInfo( 0, 600, 400 );//ideal, min

	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CLADAControlModuleView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	m_wndSplitter2 = new CSplitterWnd;
	// add the second splitter pane - which is a nested splitter with 2 rows
	if (!m_wndSplitter2->CreateStatic(
		&m_wndSplitter,     // our parent window is the first splitter
		nGraphs, 1,               // the new splitter is 3 rows, 1 column
		WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
		m_wndSplitter.IdFromRowCol(0, 0)
			// new splitter is in the first row, first column of first splitter
	   ))
	{
		TRACE0("Failed to create nested splitter\n");
		return FALSE;
	}

	pContext->m_pNewViewClass = NULL;
	CRect rect;

	GetClientRect(rect);
	if (!m_wndSplitter2->CreateView(0, 0,
		RUNTIME_CLASS(CGraphWindow), CSize(rect.right * 3 / 4, rect.bottom / 3), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}
	//pContext->m_pCurrentDoc = document2Ptr = new CGraphDoc("filename2", currentDoc, 15);
	if (!m_wndSplitter2->CreateView(1, 0,
		RUNTIME_CLASS(CGraphWindow), CSize(rect.right * 3 / 4, rect.bottom / 3), pContext))
	{
		TRACE0("Failed to create third pane\n");
		return FALSE;
	}
	//pContext->m_pCurrentDoc = document3Ptr = new CGraphDoc("filename3", currentDoc, 30);
	if (!m_wndSplitter2->CreateView(2, 0,
		RUNTIME_CLASS(CGraphWindow), CSize(rect.right * 3 / 4, rect.bottom / 3), pContext))
	{
		TRACE0("Failed to create fourth pane\n");
		return FALSE;
	}
	
	m_wndSplitter.RecalcLayout();
	
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//cs.hMenu = NULL;
	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;
	// here I could choose to disable the menu by typing
	if (cs.hMenu)
	{
		DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	//CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	//RecalcLayout();
	//RebuildSplitter();
	
	if (curLanguage != m_curDisplayLanguage)
	{
		SetToolbarText();
		m_curDisplayLanguage = curLanguage;
	}
	
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();
	//if (pDoc)
	//	EnableButton(4, pDoc->m_ControlState == Regular);

	//nCmdShow = SW_SHOWMAXIMIZED;
	CFrameWnd::ActivateFrame(nCmdShow);
	//ShowWindow(nCmdShow);
	
}

BOOL CMainFrame::RebuildSplitter()
{
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();
	int nPanes = pDoc->nPanes;

	if (nGraphs != nPanes){
		
		if (m_wndSplitter2){ // if there is a splitter window
			static_cast<CDocument *>(pDoc)->m_bAutoDelete = FALSE;
			m_wndSplitter2->DestroyWindow();
			static_cast<CDocument *>(pDoc)->m_bAutoDelete = TRUE;
		}
		
		CCreateContext context;
		context.m_pNewViewClass= NULL;
		context.m_pCurrentDoc=pDoc;
		context.m_pNewDocTemplate=NULL;
		context.m_pLastView=NULL;
		context.m_pCurrentFrame=NULL;

		if (nPanes > 1) // if there will be a splitter window
		{
			if (m_wndSplitter2)
				delete m_wndSplitter2;
			m_wndSplitter2 = new CSplitterWnd;	
			
			if (!m_wndSplitter2->CreateStatic(
				&m_wndSplitter,     // our parent window is the first splitter
				nPanes, 1,               // the new splitter is 3 rows, 1 column
				WS_CHILD | WS_VISIBLE | WS_BORDER,  // style, WS_BORDER is needed
				m_wndSplitter.IdFromRowCol(0, 0)// new splitter is in the first row, first column of first splitter
			))
			{
				TRACE0("Failed to create nested splitter\n");
				return FALSE;
			}
			
			CRect rect;
			GetClientRect(rect);
			int newHeight = rect.bottom / 3;
			
			for (int i = 0; i < nPanes; i++)
			{
				if (!m_wndSplitter2->CreateView(i, 0,
					RUNTIME_CLASS(CGraphWindow), CSize(100, newHeight), &context))
				{
					TRACE0("Failed to create pane\n");
					return FALSE;
				}
				CView * pNewView= (CView *)m_wndSplitter2->GetPane(i,0);
   				pNewView->OnInitialUpdate();
			}
		}
		else
		{
			m_wndSplitter2 = NULL;
			
			//CWnd *newView = CreateView(&context);
			//newView->SetActiveWindow();
			//newView->ShowWindow(SW_NORMAL);

			m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CGraphWindow),CSize(100,100), &context);
			CFrameWnd * pNewFrame = (CFrameWnd *) m_wndSplitter.GetPane(0,0);
 			//pNewFrame->OnInitialUpdate();
		}
		
		//SetActiveView((CView*)m_pwndSplitter->GetPane(0,0));

		m_wndSplitter.RecalcLayout(); 
		if (nPanes > 1)
			m_wndSplitter2->RecalcLayout(); 

		nGraphs = nPanes;
		return TRUE;
	} 
	else
		return TRUE;
	return FALSE;
		
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnToolBarButton(UINT nID){ //
/*IDC_DATA_TRANSFER, 
								IDC_GRAPH, 
								IDC_CAMERAS, 
								IDC_SYSTEM_CHECK, 
								IDC_CHANGE_LANGUAGE,
								IDC_MAN_SAMPLE,
								IDC_SYSTEM_CONTROLS,
								IDC_HELP_BUTTON
								*/

	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();

	switch (nID){
	case IDC_CHANGE_LANGUAGE: {

		LanguageChanger lDlg;
		lDlg.DoModal();
		SetStrings();

	//	Invalidate();
	} break;
	case IDC_CAMERAS: {

		if (cameraDlg)
		{
			cameraDlg->ShowWindow(SW_SHOW);
			SetStrings();
		}
		else
		{
			MessageBox("This function is not available because no cameras are loaded.  Try enabling one or more cameras through the Data Collection dialog.","LADA Software System",MB_ICONINFORMATION);
		}

	} break;
	case IDC_GRAPH: {
		CGraphProperties gDialog(pDoc);
		gDialog.DoModal();
		SetStrings();
		pDoc->UpdateAllViews(NULL);
	} break;
	case IDC_DATA_TRANSFER: {
		CDataTransfer dDlg(pDoc);
		dDlg.DoModal();
		SetStrings();

	} break;
	case IDC_SYSTEM_CHECK: {
		if (pDoc->m_ControlState == Regular)
		{
			CSystemDiagDlg sDlg(pDoc, pDoc->m_LastGroup);
			sDlg.DoModal();
		}
		else
			MessageBox(IDS_M_SYSTEM_ONLY_AVAIL,IDS_PROGRAM_NAME,MB_ICONINFORMATION);
		SetStrings();

	} break;
	case IDC_MAN_SAMPLE: {
		if (pDoc->commObject)
		{
			CManualSample cDlg(pDoc);
			cDlg.DoModal();
			SetStrings();
		}
		else
			MessageBox(IDS_M_MUST_CONNECT,IDS_PROGRAM_NAME,MB_ICONINFORMATION);
	} break;
	case IDC_SYSTEM_CONTROLS: {
		CParamMenu cDlg(pDoc);
		cDlg.DoModal();
		SetStrings();
	} break;
	case IDC_HELP_BUTTON: {
		//HtmlHelp(NULL, workingDirectory + "\\LADA.chm::ExampleB.htm", HH_DISPLAY_TOPIC, NULL);
		if (curLanguage == ENGLISH)
		{
			HtmlHelp(NULL, workingDirectory + "\\LADA Help.chm", HH_DISPLAY_TOPIC, NULL);
		}
		else
		{
			HtmlHelp(NULL, workingDirectory + "\\LADA Help Ru.chm", HH_DISPLAY_TOPIC, NULL);
		}
	} break;
	case IDC_HISTORY: {
		if (pDoc->m_ptrHistoryDlg == NULL)
		{
			pDoc->m_ptrHistoryDlg = new CViewHistoryDialog(&pDoc->m_ptrHistoryDlg, pDoc->m_History);   // standard constructor
			pDoc->m_ptrHistoryDlg->Create(IDD_VIEWHISTORY);
		}
	} break;
	case IDC_ERRORS: {
		if (pDoc->m_ptrErrorDlg == NULL)
		{
			pDoc->m_ptrErrorDlg = new CViewHistoryDialog(&pDoc->m_ptrErrorDlg, pDoc->m_ErrorFiles);   // standard constructor
			pDoc->m_ptrErrorDlg->Create(IDD_VIEWHISTORY);	
		}
	} break;
	case IDC_EXIT: {
		OnClose();
	} break;

	}
}

LRESULT CMainFrame::OnSwitchLanguage(WPARAM wPARAM, LPARAM lPARAM)
{
	LRESULT result = 0;

	CString str;
	for ( int i = 0; i < BUTTONS; i++){
		str.LoadString(RES_BUT_IDS[ButtonOrder[i]]);
		m_wndToolBar.SetButtonText(	i, str );
	}
	CRect rectToolBar;
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(60,29));

	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();
	pDoc->UpdateAllViews(NULL);
	
	return result;
}

int GetCurrentLanguage()
{
#ifdef _RAPID_TRANSLATION
	if (curLanguage == -1)
	{
		RT_LANGUAGEPARAMS lParams;
		RTGetLanguageParams(&lParams);
		
		switch (lParams.nLanguageID){
		case ENGLISH_FILE_ID:
			{curLanguage = ENGLISH;}
		case RUSSIAN_FILE_ID:
			{curLanguage = RUSSIAN;}
		default:
			{curLanguage = UNKNOWN_LANGUAGE;}
		}
	}
#endif _RAPID_TRANSLATION
	return curLanguage;
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();
	pDoc->ExecuteInitialCommand();
	if (!pDoc->ApplicationIsOpen)
	{
		if (pDoc->SaveModified())
			CFrameWnd::OnClose();
	}
}	

void CMainFrame::SetToolbarText()
{
	m_curDisplayLanguage = curLanguage;
	for (int i = 0; i < BUTTONS; i++){
		m_wndToolBar.SetButtonText(	i, Strings.get(RES_BUT_IDS[ButtonOrder[i]]));
	}

	m_wndToolBar.Invalidate();	
	//CDocument::UpdateAllViews(NULL);
}

void CMainFrame::SetStrings()
{
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetActiveDocument();
	SetToolbarText();
	pDoc->m_pMainView->SetStrings();
	for (int i = 0; i < pDoc->nPanes; i++)
		pDoc->paneModified[i] = TRUE;
	pDoc->UpdateGraphViews();

}

void CMainFrame::CreateToolBar()
{
	if (!m_wndToolBar.CreateEx(this) /*||!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)*/)
	{
		TRACE0("Failed to create toolbar\n");
		return;      // fail to create
	}
	
	m_wndToolBar.GetToolBarCtrl().SetButtonWidth(60, 70); 
	// (min button width, max button width) in pixels
	m_wndToolBar.SetFont(&SmallRussianArial);

	//m_wndToolBar.GetToolBarCtrl().SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	// (using this style allows buttons to have a drop down menu)
	
	CImageList img;
	img.Create(IDB_HOTTOOLBAR, 50, 0, RGB(255, 0, 255)); //IDB_BITMAP1
	// (the resource ID, the size of each image (in pixels), 
	// the number of images the list can grow by,
	// mask color - transparent color ??)
	m_wndToolBar.GetToolBarCtrl().SetHotImageList(&img);
	// imlements 'hot buttons' (CImageList *object)
	img.Detach();
	// detaches an image list object from a CImageList object
	// (probably so the object 'img' can be used again 
	// in the next line of code
	img.Create(IDB_COLDTOOLBAR, 50, 0, RGB(255, 0, 255));
	// same as preceding
	m_wndToolBar.GetToolBarCtrl().SetImageList(&img);
	// sets the cold image list for the cold toolbar buttons
	img.Detach();

	// TODO: Remove this if you don't want tool tips
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

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
	SetToolbarText();

	//this->LoadResStrings();
	
	CRect rectToolBar;
	// set up toolbar button sizes
	m_wndToolBar.GetItemRect(0, &rectToolBar);
	// gets size of a button (index of button, rect object) 
	m_wndToolBar.SetSizes(rectToolBar.Size(), CSize(50,29));
	// sets button sizes (size of button, size of image) in pixels
	
}

BOOL CMainFrame::Create(LPCTSTR lpszClassName,
	LPCTSTR lpszWindowName,
	DWORD dwStyle,
	const RECT& rect,
	CWnd* pParentWnd,
	LPCTSTR lpszMenuName,
	DWORD dwExStyle,
	CCreateContext* pContext)
{
	return CFrameWnd::Create(lpszClassName,
		lpszWindowName,
		dwStyle,
		rect,
		pParentWnd,
		NULL,
		dwExStyle,
		pContext);
}

/*
BOOL CMainFrame::Create(  UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
*/

void CMainFrame::OnChangeLanguage() 
{
	// TODO: Add your command handler code here
	curLanguage = !curLanguage;
	SetStrings();
}



void CMainFrame::EnableButton(int nID, BOOL Enable)
{
	m_wndToolBar.GetToolBarCtrl().EnableButton(nID,Enable);
}

