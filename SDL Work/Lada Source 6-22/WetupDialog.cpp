// This is Version 1.0 PLEASE DOCUMENT CHANGES
// ProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "WetupDialog.h"

#include "LadaStrings.h"
#include "LADA Control Module.h"
#include "LADA Control ModuleDoc.h"
#include "CommOperations.h"
#include "WetupSettingsDlg.h"
#include "Ladastrings.h"
#include "LString.h"
#include <math.h>
#include "LadaSetupDlg.h"
#include "WetupSettingsDlg.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
extern CFont RussianArial;
extern LString Strings;
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

#include "inputlocations.h"

// IDABORT means communication failed so wetup stopped.

/////////////////////////////////////////////////////////////////////////////
// WetupDialog dialog
extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);

WetupDialog::WetupDialog(BOOL *Canceled, BOOL SPercent, 
	CWnd* pParent /*=NULL*/, BOOL DParent /*=TRUE*/, CLADAControlModuleDoc * doc)
	: CDialog(WetupDialog::IDD, pParent)
{
	pDoc = doc;
	WindowClosed = Canceled;
	IsComplete = FALSE;	
	ShowPercent = SPercent;

	if (Canceled)
		*WindowClosed = FALSE;
	
	if ((DisableParent = DParent) && (pParentWnd = pParent) )
		pParent->EnableWindow(FALSE);
	//{{AFX_DATA_INIT(WetupDialog)
	//}}AFX_DATA_INIT
}


BOOL WetupDialog::OnInitDialog()
{   
	CDialog::OnInitDialog();      // TODO: Add extra initialization here

	m_FinishStatus = IDOK;

	SetFont(&RussianArial);
	SetWindowText(Strings.get(IDS_L0).GetBuffer(0));
	
	GetDlgItem(IDC_WINDOW_TEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_WINDOW_TEXT)->SetWindowText(Strings.get(IDS_L1).GetBuffer(0));
	
	GetDlgItem(IDCANCEL)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT2)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT3)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT4)->SetFont(&RussianArial);
	GetDlgItem(IDC_PAUSE)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEXTBURST)->SetFont(&RussianArial);
	GetDlgItem(IDC_TIMELEFT)->SetFont(&RussianArial);
	GetDlgItem(IDC_WATERPUMPED)->SetFont(&RussianArial);
	GetDlgItem(IDC_WATERLEFT)->SetFont(&RussianArial);

	if (!ShowPercent){
		CStatic *percentWindow = (CStatic *) GetDlgItem(IDC_PERCENT);
		percentWindow->ShowWindow(SW_HIDE);
	}
	
	SetWindowPos(&wndTop, 0,0,0,0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW );
	
	if (StartWetup())
		OnTimer(1);
	else
	{
		if (DisableParent && pParentWnd)
			pParentWnd->EnableWindow(TRUE);
		OnClose();
	}

	return TRUE;   // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE}
}

void WetupDialog::SetInfo(char *newText){

	CWnd *nText;

	//int PercentDone = m_TotalPumped * 100 / pDoc->m_WetupInfo.m_VolumeToPump;
	int PercentDone = TimeElapsed.GetTotalSeconds() * 100 / (TimeElapsed + TimeRemaining).GetTotalSeconds();

	CProgressCtrl *progBox = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	progBox->SetPos( (int)PercentDone );
	
	if (ShowPercent){
		nText = GetDlgItem(IDC_PERCENT);
		char percentCStr[4];
		wsprintf(percentCStr,"%i%%",(int)PercentDone);
		nText->SetWindowText(percentCStr);
	}

	if (newText){
		nText = GetDlgItem(IDC_WINDOW_TEXT);
		nText->SetWindowText(newText);
	}
	
	nText = GetDlgItem(IDC_WATERPUMPED);
	char pumped[15];
	wsprintf(pumped,"%i ml",(int)pDoc->m_WetupInfo.m_VolumePumped);
	nText->SetWindowText(pumped);

	nText = GetDlgItem(IDC_WATERLEFT);
	wsprintf(pumped,"%i ml",int(pDoc->m_WetupInfo.m_VolumeToPump - pDoc->m_WetupInfo.m_VolumePumped) );
	nText->SetWindowText(pumped);

	if (pDoc->m_WetupInfo.m_VolumePumped > 0)
	{
		nText = GetDlgItem(IDC_TIMELEFT);
		nText->SetWindowText(GetTimeSpan(TimeRemaining, 3));
	}

	GetDlgItem(IDC_NEXTBURST)->SetWindowText(GetTimeSpan(m_NextBurstTime - CTime::GetCurrentTime(), 3));
}

void WetupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(WetupDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(WetupDialog, CDialog)
	//{{AFX_MSG_MAP(WetupDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// WetupDialog message handlers

void WetupDialog::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (IsComplete)
	{
		OnClose();
		return;
	}
	
	if(MessageBox(IDS_M_SURE_CANCEL, IDS_PROGRAM_NAME, MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		OnClose();
	}

}

BOOL WetupDialog::StartWetup() 
{
	if (pDoc->commObject == NULL)
	{
		CWaitCursor wait;
		
		if (!pDoc->Connect(FALSE, ::StartWetup, FALSE, TRUE))
		{
			MessageBox(IDS_M_WETUP_NOT_PROCEED, IDS_PROGRAM_NAME, MB_ICONWARNING|MB_OK);
			m_FinishStatus = IDABORT;
			return FALSE;
		}
	}
	
	if (pDoc->m_WetupInfo.m_IsCR10Controlled)  // upload wetup program
	{ 
		if (!PrepareCR10())
		{
			m_FinishStatus = IDABORT;
			return FALSE;
		}
	}

	SetTimer(1,2000,NULL);     // no timer callback 
	Time = CTime::GetCurrentTime();

	TimeElapsed = CTimeSpan(0,0,0,0);

	// this section calculates when the next burst should happen
	if (!pDoc->m_WetupInfo.m_IsCR10Controlled)
		m_NextBurstTime = Time;
	else
		m_NextBurstTime = GetNextCR10BurstTime();
	CTime compTime = CTime::GetCurrentTime();
	CString myTime = compTime.Format("%H:%M:%S");
	CString nBT = m_NextBurstTime.Format("%H:%M:%S");
	BurstLength = CTimeSpan(time_t((unsigned)(pDoc->m_WetupInfo.m_BurstVolume / pDoc->m_WetupInfo.m_mlPerSecond)));
	
	IsPaused = FALSE;
	GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
	return TRUE;
}

void WetupDialog::OnTimer(UINT nIDEvent) 
{
	static bool InTimer = false;

	if (!InTimer)
	{
		InTimer = true;
		CTime now = CTime::GetCurrentTime();
		TimeElapsed += now - Time;
		Time = now;

		int volPumpedPrev = pDoc->m_WetupInfo.m_VolumePumped;
		for (int t = 0; t < 3; t++)
		{
			int locations[] = { IL_VOLUME_PUMPED, IL_CUR_VOL_PUMPED };
			double d[2];
			for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(locations,2, d, 26); wTry++);
			if (wTry == 5)
			{
				continue;
			}

			pDoc->m_WetupInfo.m_VolumePumped = (int)(d[0] + d[1]);
			if (pDoc->m_WetupInfo.m_VolumePumped >= (volPumpedPrev - 1) && // volume pumped can't go down...
				pDoc->m_WetupInfo.m_VolumePumped - volPumpedPrev <= 5) // can't pump more than 5 mililiters in a second...
				break;
		}
		if (t == 3) 
		{
			// write to error log
			// cancel wetup

		}

		//pDoc->m_WetupInfo.m_VolumeRemaining = pDoc->m_WetupInfo.m_VolumeToPump - m_TotalPumped;

		int volRemaining = pDoc->m_WetupInfo.m_VolumeToPump - pDoc->m_WetupInfo.m_VolumePumped;

		if (volRemaining <= 0)
		{
			OnComplete();
			return;
		}

		if (now > m_NextBurstTime)
		{
			if (nIntervals > 0)
				nIntervals--;
		
			if (!pDoc->m_WetupInfo.m_IsCR10Controlled)
			{
				// time to start a burst
								
				if (volRemaining < pDoc->m_WetupInfo.m_BurstVolume)
				{
					pDoc->commObject->SetInputLocation( IL_BURST_VOLUME, volRemaining, 115 );
				}
							
				
				m_NextBurstTime = now + CTimeSpan(0,0,pDoc->m_WetupInfo.m_BurstFreq,0);// this should be in minutes
			}			
			else
			{
				m_NextBurstTime = GetNextCR10BurstTime();// this should be in minutes
				// if this is CR10 controlled, then it should take care of the previous section
			}
			
			pDoc->OnSaveDocument((LPCSTR)pDoc->GetPathName());
		}
		CString nbt = m_NextBurstTime.Format("%H:%M:%S");
		TimeRemaining = (m_NextBurstTime - now) + CTimeSpan(0,0,(nIntervals - 1) * 10, 0) + BurstLength;
		
		SetInfo();
		InTimer = false;
	}

}

void WetupDialog::OnComplete()
{
	KillTimer(1);
	SetInfo();
	pDoc->m_WetupInProgress = FALSE;
	IsComplete = TRUE;
	pDoc->OnSaveDocument((LPCSTR)pDoc->GetPathName());
	SetStrings();
}

void WetupDialog::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (DisableParent && pParentWnd)
		pParentWnd->EnableWindow(TRUE);
	KillTimer(1);
	if (WindowClosed)
		*WindowClosed = TRUE;
	pDoc->commObject->SetFlag(WETUP_CONTROL_FLAG,FALSE);
	EndDialog(m_FinishStatus);
}


CTime WetupDialog::GetNextCR10BurstTime()
{
	//CTime CR10Time;
	CTime currentTime = CTime::GetCurrentTime();
	
	int location1 = 1;
	double returnD;

	for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(&location1,1,&returnD,32); wTry++);
	if (wTry == 5)
	{
		// write to error log
	}
	
	int s = (pDoc->GetCR10Time().GetMinute()%10) * 60 + pDoc->GetCR10Time().GetSecond(); 
	int k = (660 -  s) % 600;
	return currentTime + CTimeSpan(0,0,0,k);
}

void WetupDialog::OnPause() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wCursor;
	
	if (pDoc->commObject->SetFlag(WETUP_CONTROL_FLAG,IsPaused))
	{
		IsPaused = !IsPaused;
		CString pText = Strings.get(IsPaused ? IDS_RESUME : IDS_PAUSE);
		GetDlgItem(IDC_PAUSE)->SetWindowText(pText);
		if (IsPaused)
		{
			KillTimer(1);
			GetDlgItem(IDC_NEXTBURST)->SetWindowText("");
			pDoc->commObject->SetFlag(WETUP_CONTROL_FLAG,0);
			pDoc->commObject->SetFlag(2,0);
		}
		else
		{
			SetTimer(1,2000,NULL);     // no timer callback 
			pDoc->commObject->SetFlag(WETUP_CONTROL_FLAG,1);
			pDoc->commObject->SetFlag(2,1);
		}
	}

}

BOOL WetupDialog::PrepareCR10()
{
	// when you connect it should load the correct program for you, or prompt you to do it
	/*
	if (MessageBox(IDS_M_UPLOAD_PROGRAM_FIRST, IDS_PROGRAM_NAME,MB_YESNO|MB_ICONQUESTION) == IDYES)
	{
		pDoc->PauseAutomaticCommunication();
		pDoc->StartCommBlock(29);
		if (!pDoc->commObject->UploadProgram() )
		{
			pDoc->EndCommBlock();
			return FALSE;
		}
		pDoc->EndCommBlock();
		pDoc->ResumeAutomaticCommunication();
	}
	*/
	if (pDoc->m_WetupInProgress)
	{
		int locations[] = { IL_VOLUME_PUMPED, IL_CUR_VOL_PUMPED };
		double d[2];
		for (int wTry = 0; wTry < 5 && !pDoc->GetInputLocations(locations,2, d, 26); wTry++);
		if (wTry == 5)
		{
			MessageBox("Failed to retrieve water pumped in CR10X.  Wetup aborted.","Communication Failure",MB_ICONWARNING);
			return FALSE;
		}
		pDoc->m_WetupInfo.m_VolumePumped = (int)(d[0] + d[1]);

	}
	else
	{
		if (MessageBox(IDS_M_DO_TENSIOMETER,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			CLADASetupDlg dlg(Tensiometer,pDoc);
			dlg.DoModal();
		}
		// set water pumped to zero on cr10 and fiva
		for (int wTry = 0; wTry < 5 && !pDoc->commObject->SetInputLocation(IL_VOLUME_PUMPED,0,120); wTry++);
		if (wTry == 5)
		{
			MessageBox("Failed to set water level in CR10X.  Wetup aborted.","Communication Failure",MB_ICONWARNING);
			return FALSE;
		}
		for ( wTry = 0; wTry < 5 && !pDoc->commObject->SetInputLocation(IL_CUR_VOL_PUMPED,0,120); wTry++);
		if (wTry == 5)
		{
			MessageBox("Failed to set water level in CR10X.  Wetup aborted.","Communication Failure",MB_ICONWARNING);
			return FALSE;
		}

		pDoc->m_WetupInfo.m_VolumePumped = 0;
	}

	CWetupSettingsDlg wSettings(pDoc);
	wSettings.DoModal();
	nIntervals = (int)ceil(double(pDoc->m_WetupInfo.m_VolumeToPump - pDoc->m_WetupInfo.m_VolumePumped) / pDoc->m_WetupInfo.m_BurstVolume);
	if (nIntervals < 1)
		nIntervals = 1;

	if (!pDoc->commObject->SetInputLocation( IL_TOTAL_TO_PUMP, pDoc->m_WetupInfo.m_VolumeToPump - pDoc->m_WetupInfo.m_VolumePumped, 116, TRUE) ||
		!pDoc->commObject->SetInputLocation( IL_BURST_VOLUME, pDoc->m_WetupInfo.m_BurstVolume, 117, TRUE) ||
		!pDoc->commObject->SetInputLocation( IL_N_ELAPSED_INTERVALS, 0, 118, TRUE)||
		!pDoc->commObject->SetInputLocation( IL_N_INTERVALS, nIntervals, 118, TRUE))
	{
		MessageBox("Unable to set initial wetup locations in CR10.  Wetup aborted.","Error",MB_ICONSTOP);
		// write to error log
		return FALSE;
	}
	pDoc->m_WetupInProgress = TRUE;

	if (!pDoc->commObject->SetFlag(WETUP_CONTROL_FLAG,TRUE))
	{
		return FALSE;
	}
	return TRUE;
}

void WetupDialog::SetStrings()
{
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_L2).GetBuffer(0));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_L3).GetBuffer(0));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_L4).GetBuffer(0));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_L5).GetBuffer(0));
	GetDlgItem(IDC_WINDOW_TEXT)->SetWindowText(Strings.get(IsComplete?IDS_L6:IDS_L1).GetBuffer(0));
	SetWindowText(Strings.get(IDS_L0).GetBuffer(0));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IsComplete?IDS_L7:IDS_CANCEL));
	GetDlgItem(IDC_PAUSE)->SetWindowText(Strings.get(IDS_PAUSE));
}

BOOL WetupDialog::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();	
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
