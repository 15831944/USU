// LADA Control ModuleView.cpp : implementation of the CLADAControlModuleView class
//

#include "stdafx.h"
#include "LADA Control Module.h"

#include "LADA Control ModuleDoc.h"
#include "LADA Control ModuleView.h"
#include "ChooseTime.h"
#include "CameradialogDlg.h"
#include "WaitTimerInfo.h"

#include "ChangeLocationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void  SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern CCameradialogDlg * cameraDlg;
extern DWORD __stdcall CommWaitTimer(void *lpdata);
/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView

IMPLEMENT_DYNCREATE(CLADAControlModuleView, CFormView)

BEGIN_MESSAGE_MAP(CLADAControlModuleView, CFormView)
	//{{AFX_MSG_MAP(CLADAControlModuleView)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON12, OnSetInputLocation)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView construction/destruction

CLADAControlModuleView::CLADAControlModuleView()
	: CFormView(CLADAControlModuleView::IDD)
{
	//{{AFX_DATA_INIT(CLADAControlModuleView)
	m_T1 = 0;
	m_T2 = 0;
	m_T3 = 0;
	m_Delay = 0;
	m_JTime = 0;
	m_JTimeMax = 0;
	m_KTime = 0;
	m_KTimeMax = 0;
	m_OTime = 0;
	m_OTimeMax = 0;
	m_RTime = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	ConnectedBMP = new CBitmap;
	NConnectedBMP = new CBitmap;
	ConnectedBMP->LoadBitmap(IDB_CONNECTED);
	NConnectedBMP->LoadBitmap(IDB_NCONNECTED);
	hTimerThread = NULL;

}

CLADAControlModuleView::~CLADAControlModuleView()
{
	delete ConnectedBMP;
	delete NConnectedBMP;

}

void CLADAControlModuleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLADAControlModuleView)
	DDX_Control(pDX, IDC_TEXT3, m_ConnStatus);
	DDX_Control(pDX, IDC_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_CR10TIME, m_TimeWnd);
	DDX_Control(pDX, IDC_CONNECTED, m_Connected);
	DDX_Text(pDX, IDC_TW1, m_T1);
	DDX_Text(pDX, IDC_TW2, m_T2);
	DDX_Text(pDX, IDC_TW3, m_T3);
	DDX_Text(pDX, IDC_EDITDELAY, m_Delay);
	DDV_MinMaxDWord(pDX, m_Delay, 0, 2000);
	DDX_Text(pDX, IDC_JTIME, m_JTime);
	DDX_Text(pDX, IDC_JTIMEMAX, m_JTimeMax);
	DDX_Text(pDX, IDC_KTIME, m_KTime);
	DDX_Text(pDX, IDC_KTIMEMAX, m_KTimeMax);
	DDX_Text(pDX, IDC_OTIME, m_OTime);
	DDX_Text(pDX, IDC_OTIMEMAX, m_OTimeMax);
	DDX_Text(pDX, IDC_RETR_TIME, m_RTime);
	//}}AFX_DATA_MAP
}

BOOL CLADAControlModuleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CLADAControlModuleView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//GetParentFrame()->RecalcLayout();
	for (int i = 0; i < 6; i++)
		SetFontText(IDC_TEXT1 + i, IDS_LTEXT1 + i, this);
	for (i = 0; i < 4; i++)
		SetFontText(IDC_BUTTON1 + i, IDS_LBUTTON1 + i, this);
	m_Button3.EnableWindow(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView printing

BOOL CLADAControlModuleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLADAControlModuleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLADAControlModuleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLADAControlModuleView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView diagnostics

#ifdef _DEBUG
void CLADAControlModuleView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLADAControlModuleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLADAControlModuleDoc* CLADAControlModuleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLADAControlModuleDoc)));
	return (CLADAControlModuleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView message handlers

void CLADAControlModuleView::OnButton1() 
{
	// TODO: Add your control notification handler code here
	// start communication
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument( );
	if (pDoc->commObject == NULL){
		CWaitCursor wait;
		pDoc->commObject = new CCommOperations(FALSE);
		if (pDoc->commObject->IsConnected() && StartTimerThread()){
			m_Connected.SetBitmap((HBITMAP)ConnectedBMP->m_hObject);
			m_ConnStatus.SetWindowText("Connected");
			m_Button2.EnableWindow(FALSE);
			m_Button3.EnableWindow(TRUE);
		}
		else{
			delete pDoc->commObject;
			pDoc->commObject = NULL;
		}
	}
}

BOOL CLADAControlModuleView::StartTimerThread()
{
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument( );
	
	if (pDoc->commObject)
	{
		pDoc->InCommMode = TRUE;
		CWaitTimerInfo * waitInfo = new CWaitTimerInfo;
		waitInfo->commObject = pDoc->commObject;
		waitInfo->pDoc = pDoc;
		waitInfo->pView = this;
		waitInfo->InCommMode = &pDoc->InCommMode;

		DWORD dwThreadID;

		if (NULL == (hTimerThread =
				  CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
								0,
								CommWaitTimer,
								(LPVOID) waitInfo,
								0, &dwThreadID )))
		{
			return FALSE;
		}
		else
		{
			SetTimer( 1, 200, NULL );
			//THREADID( TalkInfo ) = dwThreadID ;
			//HTHREAD( TalkInfo ) = hCommWatchThread ;
			// assert DTR
			//EscapeCommFunction( COMDEV( TalkInfo ), SETDTR ) ;
			return TRUE;
		}	
	}
	return FALSE;
}

void CLADAControlModuleView::OnButton2() 
{
	// TODO: Add your control notification handler code here
	// Upload program
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument();
	if (pDoc->commObject == NULL){
		AfxMessageBox("Unable to upload program.\nNo connection with CR10 present.");
		return;
	}
	pDoc->StartCommBlock();
	pDoc->commObject->DownloadProgram();
	pDoc->EndCommBlock();
	
}

void CLADAControlModuleView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//CFrameWnd::OnTimer(nIDEvent);
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument( );

	if (pDoc->NewDataExists){
		pDoc->UpdateGraphViews();
		pDoc->NewDataExists = FALSE;
	}
//#ifdef _DEBUG
	
	UpdateData();
	pDoc->DelayTime = m_Delay;
	m_T1 = pDoc->ThreadsInFunction;
	m_T2 = pDoc->ThreadsInCommunication;
	m_T3 = pDoc->ThreadsInStartBlock;
	m_RTime = (int)pDoc->RTime;
	UpdateData(FALSE);

//#endif

}

void CLADAControlModuleView::OnButton3() 
{
	// TODO: Add your control notification handler code here
	// Break Communication
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument( );
	KillTimer(1);
	if (pDoc->StopComm())
	{
		m_Connected.SetBitmap((HBITMAP)NConnectedBMP->m_hObject);
		m_ConnStatus.SetWindowText("Not Connected");
		m_Button2.EnableWindow(TRUE);
		m_Button3.EnableWindow(FALSE);
	}
}

void CLADAControlModuleView::OnButton4() 
{
	// TODO: Add your control notification handler code here
	// change cr10 time
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument( );
	
	if (pDoc->commObject == NULL){
		AfxMessageBox("Unable to change time.\nNo connection with CR10 present.");
		return;
	}
	
	CTime date;
	CTime time;
	CChooseTime timeDlg(&date, &time);
	if (timeDlg.DoModal() == IDOK)
	{
		struct tm* osTime;  // A pointer to a structure containing time 
                    // elements.
		osTime = date.GetLocalTm( NULL );
		pDoc->StartCommBlock();
		pDoc->commObject->ChangeCR10Time(time.GetHour(), time.GetMinute(), 
			time.GetSecond(), osTime->tm_yday + 1, date.GetYear());
		pDoc->EndCommBlock();
	}

}

void CLADAControlModuleView::OnButton5() 
{
	// TODO: Add your control notification handler code here
	cameraDlg->TakePictureNow();
}

void CLADAControlModuleView::OnSetInputLocation() 
{
	// TODO: Add your control notification handler code here
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) GetDocument( );
	
	CChangeLocationDlg myDlg( pDoc );
	myDlg.DoModal();
	
}
