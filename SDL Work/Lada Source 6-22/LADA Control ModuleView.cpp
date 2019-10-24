// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LADA Control ModuleView.cpp : implementation of the CLADAControlModuleView class
//

#include "stdafx.h"
#include "LADA Control Module.h"

//#include "LADA Control ModuleDoc.h"
#include "LADA Control ModuleView.h"

#include "Camera.h"
#include "LString.h"
#include "LadaStrings.h"
#include "HistoryClass.h"
#include "InputLocFileInfo.h"
#include "List.h"
#include "ViewHistoryDialog.h"
#include "WetupSettingsDlg.h"
#include "WetupDialog.h"
#include "FSInfo.h"
#include "CameraData.h"
#include "GraphCollection.h"
#include "CR10FinalStorageDebugReport.h"
#include "InputLocationReadTest.h"
#include "InputLocationSetTest.h"

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
extern UINT NotificationBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);
extern UINT NotificationBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);
extern CString IntToString(int number);
extern CCamera * cameraDlg;
extern LString Strings;
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern CFont RussianArial;
extern int curLanguage;

void CALLBACK EXPORT ResetTimer(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
)

{
	//hWnd - not important to me...
	// nIDEvent is important
	CLADAControlModuleView * pView = (CLADAControlModuleView *) CWnd::FromHandle(hWnd);
	
	CLADAControlModuleDoc * pDoc = (CLADAControlModuleDoc *) pView->GetDocument( );

	DWORD timeTo;

	int whichIL;
	
	if (nIDEvent >= FIRST_IL_TIMER && nIDEvent <= LAST_IL_TIMER){
		whichIL = nIDEvent - FIRST_IL_TIMER;
		nIDEvent = GET_IL_DATA;
	}
	if (nIDEvent >= FIRST_IL_SAVE_TIMER && nIDEvent <= LAST_IL_SAVE_TIMER){
		whichIL = nIDEvent - FIRST_IL_SAVE_TIMER;
		nIDEvent = SAVE_IL_DATA;
	}

	switch (nIDEvent){
	case UPDATE_GRAPH_TIMER:
		{
			timeTo = pDoc->dataPlotFreq.GetTotalSeconds() * 1000;
		} break;
	case GET_IL_DATA:
		{
			timeTo = pDoc->m_ILData[whichIL].m_RetrFreq.GetTotalSeconds() * 1000;
			pDoc->m_ILData[whichIL].m_NextCollectionTime = 
			nIDEvent = whichIL + FIRST_IL_TIMER;
		} break;
	case SAVE_IL_DATA:
		{
			timeTo = pDoc->m_ILData[whichIL].m_WriteDataFreq.GetTotalSeconds() * 1000;
			nIDEvent = whichIL + FIRST_IL_SAVE_TIMER;
		} break;
	case FINAL_STORAGE_TIMER:
		{
			timeTo = pDoc->m_FSCollectionParam.m_WriteDataFreq.GetTotalSeconds() * 1000;
		} break;
	case TAKE_PICTURE_1:
	case TAKE_PICTURE_2:
		{
			int wCam = nIDEvent - TAKE_PICTURE_1;
			timeTo = pDoc->m_CameraData[wCam].m_PictureFrequency.GetTotalSeconds() * 1000;
		} break;
	default:
		{
			AfxMessageBox("Error in ResetTimer:  Function called by unidentifiable timer ID.",MB_ICONWARNING);
		}
	}
	pView->KillTimer(nIDEvent);
	pView->SetTimer(nIDEvent,timeTo,NULL);
	pView->OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView

IMPLEMENT_DYNCREATE(CLADAControlModuleView, CFormView)

BEGIN_MESSAGE_MAP(CLADAControlModuleView, CFormView)
	//{{AFX_MSG_MAP(CLADAControlModuleView)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_CONNECTED, OnConnected)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	//ON_COMMAND_RANGE(IDC_FANS,IDC_APUMP,OnCR10Control)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleView construction/destruction

CLADAControlModuleView::CLADAControlModuleView()
	: CFormView(CLADAControlModuleView::IDD)
{
	//{{AFX_DATA_INIT(CLADAControlModuleView)
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	ConnectedBMP = new CBitmap;
	NConnectedBMP = new CBitmap;
	ConnectedBMP->LoadBitmap(IDB_CONNECTED);
	NConnectedBMP->LoadBitmap(IDB_NCONNECTED);
	WetupInProgressBMP = new CBitmap;
	BigRedButtonBMP = new CBitmap;
	WetupInProgressBMP->LoadBitmap(IDB_WETUP_INPROGRESS);
	BigRedButtonBMP->LoadBitmap(IDB_BIGREDBUTTON);
	wDialog = NULL;
}

CLADAControlModuleView::~CLADAControlModuleView()
{
	delete ConnectedBMP;
	delete NConnectedBMP;
	delete BigRedButtonBMP;
	delete WetupInProgressBMP;
}

void CLADAControlModuleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLADAControlModuleView)
	DDX_Control(pDX, IDC_OPMODE, m_ModeWindow);
	DDX_Control(pDX, IDC_TEXT3, m_ConnStatus);
	DDX_Control(pDX, IDC_CR10TIME, m_TimeWnd);
	DDX_Control(pDX, IDC_CONNECTED, m_Connected);
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
	pDoc = (CLADAControlModuleDoc*) GetDocument();
	
	SetTimer( UPDATE_VIEW_TIMER, 1000, NULL); 
	// this timer will keep running, even
	// when the view is not visible.
	
	pDoc->m_pMainView = this;
	
	//GetParentFrame()->RecalcLayout();
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);//Strings.get(IDS_F1));
	GetDlgItem(IDC_TEXT2)->SetFont(&RussianArial);//Strings.get(IDS_F2));
	GetDlgItem(IDC_TEXT3)->SetFont(&RussianArial);//Strings.get(IDS_F3));
	GetDlgItem(IDC_CONNECT)->SetFont(&RussianArial);//Strings.get(IDS_F4));
	GetDlgItem(IDC_CR10_TIME)->SetFont(&RussianArial);//Strings.get(IDS_F6));
	GetDlgItem(IDC_CONTROL_MODE)->SetFont(&RussianArial);//Strings.get(IDS_F1));
	GetDlgItem(IDC_MODE_TEXT)->SetFont(&RussianArial);//Strings.get(IDS_F2));
	//GetDlgItem(IDC_SWITCH_MODE)->SetFont(&RussianArial);//Strings.get(IDS_F3));
	//GetDlgItem(IDC_FANS)->SetFont(&RussianArial);//Strings.get(IDS_F4));
	//GetDlgItem(IDC_LIGHTS)->SetFont(&RussianArial);//Strings.get(IDS_F5));
	//GetDlgItem(IDC_WATERF)->SetFont(&RussianArial);//Strings.get(IDS_F6));
	//GetDlgItem(IDC_WATERB)->SetFont(&RussianArial);
	//GetDlgItem(IDC_APUMP)->SetFont(&RussianArial);//Strings.get(IDS_F6));

	//GetDlgItem(IDC_TAKE_PICTURE)->SetFont(&RussianArial);
	GetDlgItem(IDC_GRAPH_DATA)->SetFont(&RussianArial);
	GetDlgItem(IDC_GRAPH_TIME)->SetFont(&RussianArial);
	GetDlgItem(IDC_GRAPH_VALUE)->SetFont(&RussianArial);

	GetDlgItem(IDC_CR10TIME)->SetFont(&RussianArial);
	GetDlgItem(IDC_G_TIME)->SetFont(&RussianArial);
	GetDlgItem(IDC_G_VALUE)->SetFont(&RussianArial);
	
	SetStrings();
	if (pDoc->m_ControlMode == ManualControlMode)
		m_ModeWindow.SetBitmap((HBITMAP)pDoc->ManualBMP->m_hObject);
	else 
		m_ModeWindow.SetBitmap((HBITMAP)pDoc->AutomaticBMP->m_hObject);

	SetControlModeWindow(pDoc->m_ControlMode);

	// start picture taking timers
	if (pDoc->m_AreCamerasLoaded)
	{
		for (int wCam = 0; wCam < pDoc->nCameras; wCam++)
			SetCameraTimer(wCam);
	}
	
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


void CLADAControlModuleView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//CFrameWnd::OnTimer(nIDEvent);
	UINT noIDEvent = nIDEvent;

	if (pDoc->InCommMode == FALSE &&
		(nIDEvent == UPDATE_GRAPH_TIMER ||
		nIDEvent == GET_IL_DATA ||
		nIDEvent == FINAL_STORAGE_TIMER ||
		nIDEvent == UPDATE_CR10_TIME ))
	{
		// write to error log... comm timer called after InCommMode = FALSE...
		
		return;
	}
	else if (nIDEvent == DESTROY_TIMERS)
	{
		// so far, I believe this event has never actually been used., but it could be...?
		pDoc->EndDataRetrievalMode();
		return;
	}

	int whichIL = -1;
	if (nIDEvent >= FIRST_IL_TIMER && nIDEvent <= LAST_IL_TIMER){
		whichIL = nIDEvent - FIRST_IL_TIMER;
		nIDEvent = GET_IL_DATA;
	}
	if (nIDEvent >= FIRST_IL_SAVE_TIMER && nIDEvent <= LAST_IL_SAVE_TIMER){
		whichIL = nIDEvent - FIRST_IL_SAVE_TIMER;
		nIDEvent = SAVE_IL_DATA;
	}

	if (pDoc->m_IsCommPaused)
	{
		bool CriticalTimer = true;
		
		switch (nIDEvent)
		{
		case UPDATE_GRAPH_TIMER: 
			TimerRequests.insertAtFront(CInputRequest(GraphRequest)); break;
		case GET_IL_DATA:
			TimerRequests.insertAtFront(CInputRequest(CollectRequest,whichIL)); break;
		case FINAL_STORAGE_TIMER:
			TimerRequests.insertAtFront(CInputRequest(FinalStorageRequest)); break;
		case UPDATE_CR10_TIME:
			TimerRequests.insertAtFront(CInputRequest(UpdateTimeRequest)); break;		
		default:
			CriticalTimer = false;
		}

		if (CriticalTimer)
		{
			KillTimer(nIDEvent);
			return;
		}
	}

	switch (nIDEvent){
	case UPDATE_GRAPH_TIMER:
		{
			int *graphList = new int[pDoc->nInputLocations];
			int j = 0;
			//for (int n = 0; n < pDoc->nGraphCollections; n++)
			for (int n = 0; n < pDoc->nPanes; n++)
			{
				if (pDoc->PaneToCollectionIndex[n] != -1)
				{
					for (int i = 0; i < pDoc->GraphCollection[pDoc->PaneToCollectionIndex[n]].nItems; i++)
					{
						graphList[j++] = pDoc->GraphCollection[pDoc->PaneToCollectionIndex[n]].DataIndex[i];
							//pDoc->InputLocationList[];
						// it doesn't have to be direct...
					}
				}
			}
			
			
			if (j) // if there is anything to graph
			{
				EnterCriticalSection(&pDoc->CommCriticalSection);
				pDoc->RequestLocations(graphList, j); // 	SetEvent( pDoc->DataRequest );
				pDoc->AddRequest(GraphRequest);
				LeaveCriticalSection(&pDoc->CommCriticalSection);
			}
			delete [] graphList;
			pDoc->m_LastGraphUpdate = CTime::GetCurrentTime();
		} break;
	case GET_IL_DATA:
		{
			// prepare data arrays...
			
			pDoc->m_ILData[whichIL].m_nAttemptedCollections++;
			CTime currentTime = CTime::GetCurrentTime();
			pDoc->m_ILData[whichIL].m_LastAttemptedCollectionTime = currentTime;
			pDoc->m_ILData[whichIL].m_NextCollectionTime = currentTime + pDoc->m_ILData[whichIL].m_RetrFreq;
			
			EnterCriticalSection(&pDoc->CommCriticalSection);
			pDoc->RequestLocations(pDoc->m_ILData[whichIL].m_Locations, pDoc->m_ILData[whichIL].m_nLocations ); //SetEvent( pDoc->DataRequest );
			pDoc->AddRequest(CollectRequest,whichIL);
			LeaveCriticalSection(&pDoc->CommCriticalSection);

		} break;
	case SAVE_IL_DATA:
		{
			if (pDoc->m_ILData[whichIL].m_SaveByAverage == FALSE)
			{ // If save by average is false (meaning that data should be collected and
			  // saved at the same time, with no averaging) then the GET_IL_DATA timer 
			  // will never be called, so we must collect the data here.
				
				pDoc->m_ILData[whichIL].m_nAttemptedCollections++;
				CTime currentTime = CTime::GetCurrentTime();
				pDoc->m_ILData[whichIL].m_LastAttemptedCollectionTime = currentTime;
				pDoc->m_ILData[whichIL].m_NextCollectionTime = currentTime + pDoc->m_ILData[whichIL].m_WriteDataFreq;
				
				EnterCriticalSection(&pDoc->CommCriticalSection);
				pDoc->RequestLocations(pDoc->m_ILData[whichIL].m_Locations, pDoc->m_ILData[whichIL].m_nLocations );
				pDoc->AddRequest(CollectRequest,whichIL);
				LeaveCriticalSection(&pDoc->CommCriticalSection);
			}
			pDoc->AddRequest(WriteRequest,whichIL);  //SetEvent( pDoc->DataRequest );

		} break;
	case FINAL_STORAGE_TIMER:
		{
			GetFinalStorage();
		} break;
	case TAKE_PICTURE_1:
	case TAKE_PICTURE_2:
		{
			static bool IsInUse = false;
			int wChamber = nIDEvent - TAKE_PICTURE_1;

			if (!pDoc->m_AreCamerasLoaded)
			{
				KillTimer(nIDEvent);
				// write to error log
				return;
			}

			if (!IsInUse)
			{
				IsInUse = true;
				CWaitCursor wCursor;
				// wChamber can be 0 or 1
				pDoc->m_CameraData[wChamber].m_nAttempted++;
				
				if (cameraDlg->AutoPicture(wChamber)) // picture worked
				{
					pDoc->m_CameraData[wChamber].m_nSuccessful++;
					pDoc->m_CameraData[wChamber].m_LastPictureTaken = CTime::GetCurrentTime();
				}
				IsInUse = false;
			}
			else
			{
				SetCameraTimer(wChamber); // this will
				// reset the timer and delay the camera for 30 seconds
			}

		} break;
	case UPDATE_VIEW_TIMER:
		{
			if (pDoc->m_ControlState == WetupInProgress && m_WetupCanceled)
			{
				// wetup was canceled by the user while in operation
				pDoc->m_ControlState = StartWetup;
				delete wDialog;
				wDialog = NULL;
			}

			SetCommStatusWindow(pDoc->ConnectionStatus);
			
			
		} break;
	case UPDATE_CR10_TIME:
		{
		
			EnterCriticalSection(&pDoc->CommCriticalSection);
			pDoc->AddRequest(UpdateTimeRequest);
			SetEvent( pDoc->DataRequest );
			LeaveCriticalSection(&pDoc->CommCriticalSection);

		} break;
	default:
		{
			MessageBox("Error in OnTimer:  Function called by unidentifiable timer ID.","Error",MB_ICONWARNING);
		}
	}
}

void CLADAControlModuleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lHint == 0)
	{
		Invalidate();
		return;
	}
	
	Invalidate();
	

	
}

void CLADAControlModuleView::OnConnect() 
{
	// TODO: Add your control notification handler code here
	static bool InFunction = false;

	if (!InFunction)
	{
		InFunction = true;
		// start communication
		GetDlgItem(IDC_CONNECT)->EnableWindow(FALSE);
		switch(pDoc->m_ControlState)
		{
		case Regular:
			{
				CWaitCursor wait;
				if (pDoc->commObject == NULL)
				{
					pDoc->Connect(TRUE, Regular);
				}
				else 
				{
					pDoc->StopComm();
				}
			} break;
		case StartWetup:
			{
				CWaitCursor wait;
				if (pDoc->commObject == NULL)
				{
					pDoc->Connect(FALSE,StartWetup,FALSE,TRUE);
				}

				if (pDoc->commObject)
				{
					pDoc->m_ControlState = WetupInProgress;
					pDoc->m_History->WriteHistory("Wet Up","started.");
					m_WetupCanceled = FALSE;  // THIS IS HOW WE FIND OUT IF THE WETUP DIALOG WAS CLOSED...
					
					wDialog = new WetupDialog(&m_WetupCanceled, TRUE, NULL, FALSE, pDoc);   // standard constructor
					
					pDoc->m_DoWetup = TRUE;
					wDialog->Create(IDD_WETUP_DIALOG);
					if (wDialog->m_FinishStatus == IDABORT)
					{
						// couldn't talk to CR10...
						// maybe write this error in the history...
						// write to error log
						delete wDialog;
						wDialog = NULL;
						pDoc->m_ControlState = StartWetup;
						pDoc->StopComm();
					}
				}
			
			} break;
		}
		

		SetCommStatusWindow(pDoc->ConnectionStatus);
		GetDlgItem(IDC_CONNECT)->EnableWindow(TRUE);
		InFunction = false;
	}

}

void CLADAControlModuleView::SetCommStatusWindow(CR10ConnectionStatusType ConnectionStatus)
{
	static CR10ConnectionStatusType LastStatus = NoState;
	static ControlStateType LastState = NoControlState;
	static int LastLanguage = -1;

	switch (pDoc->m_ControlState)
	{
	case Regular:
		{
			if (pDoc->m_ControlState != LastState || curLanguage != LastLanguage)
			{
				LastStatus = NoState;
				GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_CONNECTION_STATUS));
			}

			if (LastStatus != ConnectionStatus)
			{
				GetDlgItem(IDC_CONNECT)->EnableWindow(TRUE);
				switch (ConnectionStatus)
				{
				case Connected:
					{
						m_Connected.SetBitmap((HBITMAP)ConnectedBMP->m_hObject);
						m_ConnStatus.SetWindowText(Strings.get(IDS_CONNECTED));
						GetDlgItem(IDC_CONNECT)->SetWindowText(Strings.get(IDS_DISCONNECT_CR10));
					} break;
				case NotConnected:
					{
						m_Connected.SetBitmap((HBITMAP)NConnectedBMP->m_hObject);
						m_ConnStatus.SetWindowText(Strings.get(IDS_NOTCONNECTED));
						GetDlgItem(IDC_CONNECT)->SetWindowText(Strings.get(IDS_CONNECT_CR10));
					} break;
				case TryingToConnect:
					{
						m_ConnStatus.SetWindowText(Strings.get(IDS_TRYINGTOCONNECT));
					} break;
				}
			}
		} break;
	case StartWetup:
		{
			m_Connected.SetBitmap((HBITMAP)BigRedButtonBMP->m_hObject);
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_WETUP_STATUS));
			GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_PRESS_START_WETUP));
			GetDlgItem(IDC_CONNECT)->SetWindowText(Strings.get(IDS_START_WETUP));
			GetDlgItem(IDC_CONNECT)->EnableWindow(TRUE);
		} break;
	case WetupInProgress:
		{
			m_Connected.SetBitmap((HBITMAP)WetupInProgressBMP->m_hObject);
			GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_WETUP_IN_PROGRESS));
			GetDlgItem(IDC_CONNECT)->EnableWindow(FALSE);
		} break;
	}
	LastState = pDoc->m_ControlState;
	LastLanguage = curLanguage;
	LastStatus = ConnectionStatus;

	//GetDlgItem(IDC_ERROR_COUNT)->SetWindowText(ValueToString((double)pDoc->m_Errors,0).GetBuffer(0));
	//GetDlgItem(IDC_READS)->SetWindowText(ValueToString((double)pDoc->m_Reads,0).GetBuffer(0));
}

void CLADAControlModuleView::SetFinalStorageTimer(lpfnTimerCallback lpfnTimer, CTime &currentTime)
{
	int timeTo;

	if (pDoc->m_FSCollectionParam.m_TimerID)
	{
		KillTimer(pDoc->m_FSCollectionParam.m_TimerID);
		pDoc->m_FSCollectionParam.m_TimerID = 0;
	}

	if (pDoc->nFSFiles)
	{
		pDoc->m_FSCollectionParam.m_TimerID = FINAL_STORAGE_TIMER;
		if (pDoc->m_FSCollectionParam.m_NextCollectionTime == 0)
		{
			pDoc->m_FSCollectionParam.m_LastReadTime = currentTime; // they all happen at the same time
			pDoc->m_FSCollectionParam.m_LastSaveTime = currentTime; // ...
			pDoc->m_FSCollectionParam.m_LastCreateTime = currentTime; // ...
			timeTo = pDoc->m_FSCollectionParam.m_NewFileFreq.GetTotalSeconds() * 1000;
			SetTimer(FINAL_STORAGE_TIMER, timeTo, NULL);
		}
		else
		{
			if (pDoc->m_FSCollectionParam.m_NextCollectionTime < currentTime + CTimeSpan(0,0,0,1))
				timeTo = 3000;
			else
				timeTo = (pDoc->m_FSCollectionParam.m_NextCollectionTime - currentTime).GetTotalSeconds() * 1000;
			if (timeTo < 3000)
				timeTo = 3000;
			
			if (CTimeSpan(0,0,0,timeTo/1000) > pDoc->m_FSCollectionParam.m_NewFileFreq)
				timeTo = pDoc->m_FSCollectionParam.m_NewFileFreq.GetTotalSeconds() * 1000;

			SetTimer(FINAL_STORAGE_TIMER, timeTo, lpfnTimer);	
			
		}
		pDoc->m_FSCollectionParam.m_NextCollectionTime = CTime::GetCurrentTime() + CTimeSpan(0,0,0,timeTo/1000);
	}
}

void CLADAControlModuleView::SetILTimer(int wIL, lpfnTimerCallback lpfnTimer, CTime &currentTime)
{
	int timeTo;
	CInputLocFileInfo * curILData = &pDoc->m_ILData[wIL];

	if (curILData->m_TimerID)
	{
		KillTimer(curILData->m_TimerID);
		if (curILData->m_SaveByAverage)
			KillTimer(curILData->m_TimerIDRetrieve);
		curILData->m_TimerID = 0;
		curILData->m_TimerIDRetrieve = 0;
	}

	if (curILData->m_Do)//pDoc->saveLocations && 
	{
		if (curILData->m_SaveByAverage) 
			// means that we can collect data inbetween when it is written to a file
		{
			curILData->m_TimerIDRetrieve = FIRST_IL_TIMER + wIL;

			if (curILData->m_NextCollectionTime != 0)
			{
				if (curILData->m_NextCollectionTime < (currentTime+CTimeSpan(0,0,0,1)))
					timeTo = 1000;
				else
					timeTo = (curILData->m_NextCollectionTime - currentTime).GetTotalSeconds() * 1000;
				
				if (timeTo < 1000)
					timeTo = 1000;

				if (CTimeSpan(0,0,0,timeTo/1000) > curILData->m_RetrFreq)
					timeTo = curILData->m_RetrFreq.GetTotalSeconds() * 1000;
				
				SetTimer(FIRST_IL_TIMER + wIL, timeTo, lpfnTimer);

			}
			else
			{
				timeTo = curILData->m_RetrFreq.GetTotalSeconds() * 1000;
				SetTimer(FIRST_IL_TIMER + wIL, timeTo, NULL);
			}
			curILData->m_NextCollectionTime = currentTime + CTimeSpan(0,0,0,timeTo / 1000);
		}
		
		curILData->m_TimerID = FIRST_IL_SAVE_TIMER + wIL;

		if (curILData->m_LastSaveTime != 0)
		{
			if (curILData->m_LastSaveTime + curILData->m_WriteDataFreq < currentTime)
				timeTo = 1000;
			else
				timeTo = (curILData->m_LastSaveTime + curILData->m_WriteDataFreq - currentTime).GetTotalSeconds() * 1000;
			if (timeTo < 1000)
				timeTo = 1000;

			if (CTimeSpan(0,0,0,timeTo/1000) > curILData->m_WriteDataFreq)
				timeTo = curILData->m_WriteDataFreq.GetTotalSeconds() * 1000;

			SetTimer(FIRST_IL_SAVE_TIMER + wIL, timeTo, lpfnTimer);
		}
		else
		{
			timeTo = curILData->m_WriteDataFreq.GetTotalSeconds() * 1000;
			SetTimer(FIRST_IL_SAVE_TIMER + wIL, curILData->m_WriteDataFreq.GetTotalSeconds() * 1000, NULL);
		}
		
		if (!curILData->m_SaveByAverage)
			curILData->m_NextCollectionTime = currentTime + CTimeSpan(0,0,0,timeTo / 1000);
	}
			
}

void CLADAControlModuleView::SetGraphTimer()
{
	KillTimer(UPDATE_GRAPH_TIMER);
	SetTimer( UPDATE_GRAPH_TIMER, pDoc->dataPlotFreq.GetTotalSeconds() * 1000, NULL);
}

void CLADAControlModuleView::SetControlModeWindow(ControlModeType mode)
{
	static ControlModeType lastMode = AutomaticControlMode;

	if (mode != lastMode)
	{
		lastMode = mode;
		//CWnd * ptrBox = GetDlgItem(IDC_CONTROL_MODE);
		//CRect rect;
		//ptrBox->GetWindowRect(&rect);
		//int ExpansionSize = 163;
		
		//ptrBox->SetWindowPos(this,0,0,
		//			rect.Width(), rect.Height() + ExpansionSize, 
		//			SWP_FRAMECHANGED | SWP_NOMOVE | 
		//			SWP_SHOWWINDOW | SWP_NOZORDER );
		//ptrBox->Invalidate();
		//GetDlgItem(IDC_TAKE_PICTURE)->GetWindowRect(&rect);
		//ScreenToClient(&rect);
		//GetDlgItem(IDC_TAKE_PICTURE)->SetWindowPos(this,rect.left,rect.top+ExpansionSize,0,0,SWP_NOSIZE | SWP_NOZORDER );
			

		switch (mode)
		{
		
		case ManualControlMode:
			{
				m_ModeWindow.SetBitmap((HBITMAP)pDoc->ManualBMP->m_hObject);
				GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_MANUAL));
			} break;
		case AutomaticControlMode:
			{
				m_ModeWindow.SetBitmap((HBITMAP)pDoc->AutomaticBMP->m_hObject);
				GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_AUTOMATIC));
			} break;

		}
	}
}

void CLADAControlModuleView::OnConnected() 
{
	// TODO: Add your control notification handler code here
	OnConnect();
}

void CLADAControlModuleView::SetStrings()
{
	static int cLang = -1;

	if (cLang != curLanguage)
	{
		GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_STATUS));//Strings.get(IDS_F2));

		//GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_D13));//Strings.get(IDS_F5));
		GetDlgItem(IDC_CR10_TIME)->SetWindowText(Strings.get(IDS_D14));//Strings.get(IDS_F6));
		GetDlgItem(IDC_CONTROL_MODE)->SetWindowText(Strings.get(IDS_D15));//Strings.get(IDS_F1));
		//GetDlgItem(IDC_SWITCH_MODE)->SetWindowText(Strings.get(IDS_D16));//Strings.get(IDS_F3));
		//GetDlgItem(IDC_TAKE_PICTURE)->SetWindowText(Strings.get(IDS_D17));
		GetDlgItem(IDC_GRAPH_DATA)->SetWindowText(Strings.get(IDS_D19));
		GetDlgItem(IDC_GRAPH_TIME)->SetWindowText(Strings.get(IDS_D20));
		GetDlgItem(IDC_GRAPH_VALUE)->SetWindowText(Strings.get(IDS_D21));
		SetCommStatusWindow(pDoc->ConnectionStatus);
		if (pDoc->m_ControlMode == AutomaticControlMode)
			GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_AUTOMATIC));
		else
			GetDlgItem(IDC_MODE_TEXT)->SetWindowText(Strings.get(IDS_MANUAL));

	}
	cLang = curLanguage;

}

void CLADAControlModuleView::ResumeTimers()
{
	CInputRequest InputRequest;
	while ( pDoc->InCommMode && TimerRequests.removeFromBack(InputRequest) )
	{
		switch (InputRequest.Request)
		{
		case GraphRequest:
			{
			OnTimer(UPDATE_GRAPH_TIMER); 
			SetGraphTimer();
			} break;
		case CollectRequest:
			{
			//nID = InputRequest.whichGroup + FIRST_IL_TIMER; 
			lpfnTimerCallback lpfnTimer = &ResetTimer;
			SetILTimer(InputRequest.whichGroup, lpfnTimer, CTime::GetCurrentTime());
			// this will call a OnTimer implicitly
			} break;
		case FinalStorageRequest:
			{
			lpfnTimerCallback lpfnTimer = &ResetTimer;
			SetFinalStorageTimer(lpfnTimer, CTime::GetCurrentTime());
			} break;
		case UpdateTimeRequest:
			{
			OnTimer(UPDATE_CR10_TIME);
			SetTimer(UPDATE_CR10_TIME, 5000, NULL);
			} break;		
		}
	}	
}

/*
void CLADAControlModuleView::OnGetFs() 
{
	// TODO: Add your control notification handler code here
	GetFinalStorage();
}
*/

BOOL CLADAControlModuleView::GetFinalStorage()
{
	// just do it... no waiting or requesting
	// this could take a long time...

	CTime theTime = CTime::GetCurrentTime();
	pDoc->m_FSCollectionParam.m_LastAttemptedCollectionTime = theTime;
	pDoc->m_FSCollectionParam.m_NextCollectionTime = theTime + pDoc->m_FSCollectionParam.m_NewFileFreq;
	CString s = theTime.Format( "%H;%M;%S, %B %d, %Y" );

	HANDLE * FSFilesOut = new HANDLE[pDoc->nFSFiles];
	char fileNameBuff[100];
			
	pDoc->m_FSCollectionParam.m_nAttemptedCollections++;

	for (int wFile = 0; wFile < pDoc->nFSFiles; wFile++)
	{
		wsprintf(fileNameBuff,"%s\\%s %s.%s", pDoc->dataFolder, pDoc->m_FSOutputTable[wFile].m_ArchiveName, s, FinalStorageExtension);

		FSFilesOut[wFile] = CreateFile(fileNameBuff, 
			GENERIC_WRITE, 
			FILE_SHARE_READ, 
			NULL, 
			CREATE_ALWAYS, 
			FILE_ATTRIBUTE_ARCHIVE, 
			NULL);
				
		if (FSFilesOut[wFile] == INVALID_HANDLE_VALUE){
			for (; wFile >= 0; wFile--)
				CloseHandle(FSFilesOut[wFile]);
			//DisplayErrorMessage(GetLastError());
			delete [] FSFilesOut;
			return FALSE;
		}
				
		CString fHeader;// = pDoc->m_FSCollectionParam.m_FileName;
				
		DWORD bytesWritten;

		for (int i = 0; i < pDoc->m_FSOutputTable[wFile].m_nDataItems; i++)
		{
			if (i)
				fHeader += '\t';
			fHeader += pDoc->m_FSOutputTable[wFile].m_DataNames[i];
			//CString(pDoc->InputLocationNameList[pDoc->m_FSCollectionParam.m_Locations[i]][ENGLISH]);
		}

		WriteFile(FSFilesOut[wFile], fHeader.GetBuffer(0), fHeader.GetLength(), &bytesWritten, NULL);
	}
	//	DisplayErrorMessage(GetLastError());
	BOOL Success;
	pDoc->PauseAutomaticCommunication();
	Success = pDoc->commObject->RetrieveFinalStorage(FSFilesOut, pDoc);
	pDoc->ResumeAutomaticCommunication();

	for ( wFile = 0; wFile < pDoc->nFSFiles; wFile++)
		CloseHandle( FSFilesOut[wFile] );
	delete [] FSFilesOut;
	
	if (Success)
	{
		pDoc->m_FSCollectionParam.m_nSuccessfulCollections++;
		pDoc->m_FSCollectionParam.m_LastSaveTime = theTime;
		pDoc->m_FSCollectionParam.m_LastCreateTime = theTime;
	}
	else
	{
		// write to error log
	}
	pDoc->OnSaveDocument(pDoc->GetPathName());

	return TRUE;
}

void CLADAControlModuleView::SetCameraTimer(int wCam)
{
	int wTimer = TAKE_PICTURE_1 + wCam;
	KillTimer(wTimer);

	unsigned int timeTo;
	CTime currentTime = CTime::GetCurrentTime();
	lpfnTimerCallback lpfnTimer = &ResetTimer;

	if (pDoc->m_CameraData[wCam].m_Do)
	{
		if (pDoc->m_CameraData[wCam].m_LastAttemptedPictureTime != 0)
		{
			if ((pDoc->m_CameraData[wCam].m_NextPictureTime +CTimeSpan(0,0,0,10)) < currentTime )
				timeTo = 10000;
			else
				timeTo = (pDoc->m_CameraData[wCam].m_NextPictureTime - currentTime).GetTotalSeconds() * 1000;
			SetTimer(wTimer, timeTo, lpfnTimer);
		}
		else
		{
			//pDoc->m_CameraData[wCam].m_LastPictureTaken = currentTime; // they all happen at the same time
			timeTo = pDoc->m_CameraData[wCam].m_PictureFrequency.GetTotalSeconds() * 1000;
			SetTimer(wTimer, timeTo, NULL);
		}
		pDoc->m_CameraData[wCam].m_NextPictureTime = currentTime + CTimeSpan(0,0,0,timeTo/1000);
	}
}

void CLADAControlModuleView::OnButton2() 
{
	// TODO: Add your control notification handler code here
	// if we give notification box ptrbox, it can then set that pointer to null,
	// and we'll know that it has been deleted already...
	//NotificationBox(IDS_PROGRAM_NAME, NO_TITLE, MB_OK, FALSE, 6000);
	//add a line to history
	//pDoc->m_History->OpenFiles();
	//pDoc->m_History->WriteHistory("Debug","OnButton2 Clicked");
	//pDoc->m_History->CloseFiles();
	//MessageBox("Modal Box");

	// create a data file...
	/*
	static int fileCount = 0;
	fileCount++;
	char fileNameBuff[200];
	wsprintf(fileNameBuff,"%s\\Sample File %i.%s", pDoc->dataFolder, fileCount, FinalStorageExtension);

	HANDLE thisFile = CreateFile(fileNameBuff, 
			GENERIC_WRITE, 
			FILE_SHARE_READ, 
			NULL, 
			CREATE_ALWAYS, 
			FILE_ATTRIBUTE_ARCHIVE, 
			NULL);
	char text[] = "Happy Data File";
	DWORD bytesWritten;
	WriteFile(thisFile, text, strlen(text), &bytesWritten, NULL);
	CloseHandle(thisFile);
	*/
	//CDataCollectionStatusDlg cDlg(pDoc);
	//cDlg.DoModal();
	CInputLocationReadTest myTest(pDoc);
	myTest.DoModal();

	//return TRUE;
}

void CLADAControlModuleView::OnButton3() 
{
	// TODO: Add your control notification handler code here
	// create modeless
	//NotificationBox("Hi","Me",MB_OK,FALSE,3000);
	CInputLocationSetTest myTest(pDoc);
	myTest.DoModal();
}

void CLADAControlModuleView::OnButton4() 
{
	// TODO: Add your control notification handler code here
	CCR10FinalStorageDebugReport cDlg(pDoc);
	cDlg.DoModal();
}


void CLADAControlModuleView::OnButton5() 
{
	// TODO: Add your control notification handler code here
	
}

void CLADAControlModuleView::OnButton6() 
{
	// TODO: Add your control notification handler code here
	
}

void CLADAControlModuleView::StartDataTimers()
{
	// which timers do I need?
	// a timer to gather final storage
	// a timer to gather input locations for file creation
	// as requested by the IL data...
	// a timer to update the graphs - synchronus with 
	// the frequency of the data plotting
	
	// when any of the timers which need input locations for their data
	// functions go off they will set an event that says .. OK ... I want
	// data.  When the data is retrieved by the other thread, it will set 
	// the data gathered event to signaled, and all the functions which are waiting
	// for data to be gathered will execute... :)
	CTime currentTime = CTime::GetCurrentTime();
				
	lpfnTimerCallback lpfnTimer = &ResetTimer;
	//void (CALLBACK EXPORT* lpfnTimer) (HWND, UINT, UINT, DWORD) = &ResetTimer;
	
	if (pDoc->m_ControlState == Regular)
	{
		SetFinalStorageTimer(lpfnTimer, currentTime);
		
		for (int i = 0; i < pDoc->nILFiles; i++)
		{
			SetILTimer(i, lpfnTimer, currentTime);
		}
	}
	OnTimer(UPDATE_GRAPH_TIMER);
}
