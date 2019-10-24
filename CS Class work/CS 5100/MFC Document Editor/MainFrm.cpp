// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFC Document Editor.h"

#include "MainFrm.h"
#include "MFC Document EditorView.h"
#include "ChildFrm.h"
#include "MFC Document EditorDoc.h"
#include "CloseDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int nFontSizes[] =
	{8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72};

//extern CChildFrame ** m_Frames;
//extern int m_FrameCount;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_CLOSE_WINDOWS, OnFileCloseWindows)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_FONT_COMBO, OnSelchangeFontCombo)
	ON_CBN_SELCHANGE(IDC_SIZE_BOX, OnSelchangeSizeCombo)
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

int CALLBACK CMainFrame::EnumFontFamProc(
  ENUMLOGFONTEX *lpelfe,    // logical-font data
  NEWTEXTMETRICEX *lpntme,  // physical-font data
  DWORD FontType,           // type of font
  LPARAM lParam             // application-defined data
)
{
	static char fontName[65];
	static int count = 0;

	if (FontType == TRUETYPE_FONTTYPE &&
		lpelfe->elfFullName[0] != '@')
	{
		if (count == 0 || strcmp((char *)(&lpelfe->elfFullName[0]),fontName) != 0)
		{
			strcpy(fontName,(const char *)(&lpelfe->elfFullName[0]));
			((CComboBox *)lParam)->AddString(CString(lpelfe->elfLogFont.lfFaceName));
		}
	}
	count++;
	return 1;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
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

	if (!m_DialogBar.Create(this,IDD_DIALOGBAR,CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_GRIPPER,IDD_DIALOGBAR))
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      // fail to create
	}

	//m_DialogBar.SetWindowPos(&wndTop, 0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	LOGFONT font;
	font.lfCharSet = DEFAULT_CHARSET;
	font.lfFaceName[0] =  '\0';
	font.lfPitchAndFamily = 0;
	
	EnumFontFamiliesEx(
		this->GetDC()->GetSafeHdc(),                          // handle to DC
		&font,              // font information
		(FONTENUMPROC) EnumFontFamProc, // callback function
		(long) m_DialogBar.GetDlgItem(IDC_FONT_COMBO),                    // additional data
		0                     // not used; must be 0
	);


	CString text;
	for (int i = 0; i < 16; i++)
	{
		text.Format("%i",nFontSizes[i]);
		int index = ((CComboBox *)m_DialogBar.GetDlgItem(IDC_SIZE_BOX))->AddString(text);
		((CComboBox *)m_DialogBar.GetDlgItem(IDC_SIZE_BOX))->SetItemData(index, nFontSizes[i]);
	}
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	((CComboBox *)m_DialogBar.GetDlgItem(IDC_SIZE_BOX))->SetCurSel(0);
	((CComboBox *)m_DialogBar.GetDlgItem(IDC_FONT_COMBO))->SetCurSel(0);
	//CComboBox::SetCurSel(
	m_DialogBar.EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_DialogBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
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
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnSelchangeFontCombo()
{
	CChildFrame *pChild = (CChildFrame *) GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child
	// window.
	CMFCDocumentEditorView * pView = (CMFCDocumentEditorView *) pChild->GetActiveView();

	if (pView)
	{
		//pView->
		//CRichEditCntrItem * pItem = pView->GetSelectedItem();
		CHARFORMAT cf;
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_FACE;
		
		CComboBox * ptrCombo = (CComboBox *)m_DialogBar.GetDlgItem(IDC_FONT_COMBO);

		char text[64];
		ptrCombo->GetLBText(ptrCombo->GetCurSel(),(LPTSTR)text);
		strcpy((char *)(&cf.szFaceName[0]),text);
		pView->GetRichEditCtrl().SetSelectionCharFormat( cf );
	}
}

void CMainFrame::OnSelchangeSizeCombo()
{
	CChildFrame *pChild = (CChildFrame *) GetActiveFrame();

	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();

	// Get the active view attached to the active MDI child
	// window.
	CMFCDocumentEditorView * pView = (CMFCDocumentEditorView *) pChild->GetActiveView();

	if (pView)
	{
		CHARFORMAT cf;
		cf.cbSize = sizeof(CHARFORMAT);
		cf.dwMask = CFM_SIZE;
		
		CComboBox * ptrCombo = (CComboBox *)m_DialogBar.GetDlgItem(IDC_SIZE_BOX);
		cf.yHeight = ptrCombo->GetItemData(ptrCombo->GetCurSel()) * 1440 / 60;
		pView->GetRichEditCtrl().SetSelectionCharFormat( cf );
	}
}

void CMainFrame::OnFileCloseWindows() 
{
	CCloseDialog cDlg(this);
	cDlg.DoModal();
}


