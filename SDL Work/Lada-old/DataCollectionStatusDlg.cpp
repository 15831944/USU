// DataCollectionStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "DataCollectionStatusDlg.h"
#include "Lada Control ModuleDoc.h"
#include "LString.h"
#include "LadaStrings.h"
#include "FSInfo.h"
#include "CameraData.h"
#include "ILProperties.h"


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

extern double StringToValue(const char * ptrString);
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern CFont RussianArial;
extern LString Strings;
extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);
extern int curLanguage;
extern CTimeSpan CreateFileFreqTable[3];
extern CString IntToString(int number);
extern void CALLBACK EXPORT ResetTimer(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
);

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionStatusDlg dialog


CDataCollectionStatusDlg::CDataCollectionStatusDlg(CLADAControlModuleDoc *doc, CWnd* pParent /*=NULL*/)
	: CDialog(CDataCollectionStatusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataCollectionStatusDlg)
	m_wChamber = -1;
	m_wFSFrequency = -1;
	m_NewFSFrequency = -1;
	m_ArrayID = 0;
	m_wGroup = -1;
	m_IsCameraEnabled = FALSE;
	m_cFreq = _T("");
	//}}AFX_DATA_INIT
	pDoc = doc;
	freqChanged[0] = false;
	freqChanged[1] = false;
}


void CDataCollectionStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataCollectionStatusDlg)
	DDX_Control(pDX, IDC_GROUP, m_cGroup);
	DDX_Control(pDX, IDC_INPUT_LOCATIONS, m_InputLocations);
	DDX_Control(pDX, IDC_FS_LIST, m_FSList);
	DDX_CBIndex(pDX, IDC_W_CHAMBER, m_wChamber);
	DDX_CBIndex(pDX, IDC_FS_FREQUENCY, m_wFSFrequency);
	DDX_CBIndex(pDX, IDC_NEW_FS_FILE, m_NewFSFrequency);
	DDX_Text(pDX, IDC_ARRAY_ID, m_ArrayID);
	DDX_CBIndex(pDX, IDC_GROUP, m_wGroup);
	DDX_Check(pDX, IDC_ENABLE_CAMERA, m_IsCameraEnabled);
	DDX_Text(pDX, IDC_C_FREQUENCY, m_cFreq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataCollectionStatusDlg, CDialog)
	//{{AFX_MSG_MAP(CDataCollectionStatusDlg)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_IMPORT_FSL, OnImportFsl)
	ON_CBN_SELCHANGE(IDC_W_CHAMBER, OnSelchangeWChamber)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_NEW_FS_FILE, OnSelchangeNewFsFile)
	ON_EN_CHANGE(IDC_ARRAY_ID, OnChangeArrayId)
	ON_BN_CLICKED(IDC_ENABLE_CAMERA, OnEnableCamera)
	ON_EN_CHANGE(IDC_C_FREQUENCY, OnChangeCFrequency)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionStatusDlg message handlers

BOOL CDataCollectionStatusDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_W_CHAMBER)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_LAST)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_NEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW_FS_FILE)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_REMAINING)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_FREQUENCY)->SetFont(&RussianArial);
	GetDlgItem(IDC_IMPORT_FSL)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_LAST)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_NEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_C_FREQUENCY)->SetFont(&RussianArial);
	GetDlgItem(IDC_INPUT_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_PROPERTIES)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW)->SetFont(&RussianArial);
	GetDlgItem(IDOK)->SetFont(&RussianArial);
	GetDlgItem(IDC_ARRAY_ID)->SetFont(&RussianArial);
	GetDlgItem(IDC_GROUP)->SetFont(&RussianArial);
	GetDlgItem(IDC_ENABLE_CAMERA)->SetFont(&RussianArial);

	for (int i = 0; i < 14; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetFont(&RussianArial);

	// start initializing chamber stuff
	for (i = 0; i < 2; i++)
		((CComboBox*)GetDlgItem(IDC_W_CHAMBER))->AddString(CString((char)('1'+ i)));
	m_wChamber = 0;
	
	if (pDoc->nFSFiles == 0)
		EnableFinalStorage(FALSE);
	else
	{
		m_ptrFSInfo = &pDoc->m_FSOutputTable[m_wChamber];

		// newFsFrequency has to do with how often all FS files are created
		m_NewFSFrequency = 0;
		m_InitialFSFreq = -1;
		for (i = 0; i < 3; i++)
		{
			if (CreateFileFreqTable[i] == pDoc->m_FSCollectionParam.m_NewFileFreq )
			{
				m_InitialFSFreq = i;
				m_NewFSFrequency = i;
				break;
			}
		}
		SetChamberData(FALSE);
	}

	// start initializing camera info
	EnableCameras(m_wChamber < pDoc->nCameras);
	if (m_wChamber < pDoc->nCameras)
		SetTimeSensitiveCameraData();

	// start initializing locations info
	m_wGroup = 0;
	m_InputLocations.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_InputLocations.InsertColumn(0,"      ");

	for (i = 0; i < 10; i++)
		m_InputLocations.InsertItem(i, Strings.get(IDS_AA15 + i));

	if (pDoc->nILFiles == 0)
		EnableInputLocations(FALSE);
	else
	{
		for (i = 1; i <= pDoc->nILFiles; i++)
		{
			m_InputLocations.InsertColumn(i,IntToString(i));
			m_cGroup.AddString(pDoc->m_ILData[i-1].m_Name);
		}
		SetLocationsData(FALSE);
	}
	m_InputLocations.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	SetStrings(FALSE);

	if (pDoc->nFSFiles || pDoc->nILFiles || pDoc->nCameras)
		SetTimer(1,1000,NULL);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataCollectionStatusDlg::OnOK() 
{
	// TODO: Add extra validation here
	KillTimer(1);
	if (freqChanged[m_wChamber])
	{
		ApplyCameraChanges(m_wChamber);
		freqChanged[m_wChamber] = false;
	}
	UpdateData();
	CDialog::OnOK();
}

void CDataCollectionStatusDlg::OnProperties() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CInputLocFileInfo fInfo;

	if (m_wGroup != -1)
	{
		fInfo = pDoc->m_ILData[m_wGroup];
		CILProperties gDlg(pDoc, &fInfo, m_wGroup);
		if (gDlg.DoModal() == IDOK)
		{
			pDoc->m_ILData[m_wGroup] = fInfo;
			CWaitCursor wCursor;
			if (gDlg.doResetTimer)
				ResetGroupTimer();
			
			m_cGroup.DeleteString( m_wGroup );
			m_cGroup.InsertString( m_wGroup, pDoc->m_ILData[m_wGroup].m_Name );
			m_cGroup.SetCurSel( m_wGroup );
			pDoc->SetModifiedFlag();
		}
		SetStrings();	
	}

	UpdateData(FALSE);
}

void CDataCollectionStatusDlg::OnNew() 
{
	// TODO: Add your control notification handler code here
	CInputLocFileInfo fInfo;

	CILProperties gDlg(pDoc, &fInfo, pDoc->nILFiles);
	if (gDlg.DoModal() == IDOK)
	{
		m_wGroup = pDoc->nILFiles;
		pDoc->nILFiles++;
		//pDoc->saveLocations = TRUE;
		CInputLocFileInfo * tempPtr = new CInputLocFileInfo[pDoc->nILFiles];
		for (int i = 0; i < pDoc->nILFiles - 1; i++)
		{
			tempPtr[i] = pDoc->m_ILData[i];
		}
		tempPtr[i] = fInfo; // copies what was in the temporary object to the permaneant
		delete [] pDoc->m_ILData;
		pDoc->m_ILData = tempPtr; // reassigns m_ILData to the new location in memory
		CWaitCursor wCursor;
		if (gDlg.doResetTimer)
			ResetGroupTimer();
		m_cGroup.DeleteString( m_wGroup );
		m_cGroup.AddString( pDoc->m_ILData[m_wGroup].m_Name );
		m_cGroup.SetCurSel( m_wGroup );
		pDoc->SetModifiedFlag();
	}
	SetStrings();
}

void CDataCollectionStatusDlg::OnImportFsl() 
{
	// TODO: Add your control notification handler code here
	
}

void CDataCollectionStatusDlg::SetStrings(BOOL updateData)
{
	if (updateData)
		UpdateData(TRUE);

	SetWindowText(Strings.get(IDS_AA0));
	for (int i = 0; i < 14; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetWindowText(Strings.get(IDS_AA1 + i));
	GetDlgItem(IDC_IMPORT_FSL)->SetWindowText(Strings.get(IDS_AA_IMPORT_FSL));
	GetDlgItem(IDC_PROPERTIES)->SetWindowText(Strings.get(IDS_AA_PROPERTIES));
	GetDlgItem(IDC_NEW)->SetWindowText(Strings.get(IDS_AA_NEW));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));

	for(i = 0; i < 3; i++)
		((CComboBox*)GetDlgItem(IDC_NEW_FS_FILE))->AddString(Strings.get(IDS_N_FILETIME1 + i));

	for(i = 0; i < 2; i++)
		((CComboBox*)GetDlgItem(IDC_FS_FREQUENCY))->AddString(Strings.get(IDS_N_FSFREQ1 + i));
	
	for (i = 0; i < 10; i++)
		m_InputLocations.SetItemText(i, 0, Strings.get(IDS_AA15 + i));	

	UpdateData(FALSE);

	SetLocationsData();

}

void CDataCollectionStatusDlg::SetChamberData(BOOL updateData)
{
	if (updateData)
		UpdateData(TRUE);

	// info that is specific to each chamber
	m_wFSFrequency = m_ptrFSInfo->m_wFreqSel;

	m_FSList.ResetContent();
	for (int i = 0; i < m_ptrFSInfo->m_nDataItems; i++)
		m_FSList.AddString(m_ptrFSInfo->m_DataNames[i]);
	
	
	SetTimeSensitiveChamberData();
	m_ArrayID = m_ptrFSInfo->m_ArrayID;

	UpdateData(FALSE);
}

void CDataCollectionStatusDlg::SetTimeSensitiveChamberData()
{
	CTime currTime = CTime::GetCurrentTime();
	CString s;
	if (pDoc->m_FSCollectionParam.m_LastCreateTime != 0)
	{
		if (pDoc->m_FSCollectionParam.m_nSuccessfulCollections)
			GetDlgItem(IDC_FS_LAST)->SetWindowText(pDoc->m_FSCollectionParam.m_LastCreateTime.Format("%m/%d/%y %H:%M"));

		s = (pDoc->m_FSCollectionParam.m_LastCreateTime + pDoc->m_FSCollectionParam.m_NewFileFreq).Format("%m/%d/%y %H:%M");
		GetDlgItem(IDC_FS_NEXT)->SetWindowText(s);
		s = GetTimeSpan((pDoc->m_FSCollectionParam.m_LastCreateTime + pDoc->m_FSCollectionParam.m_NewFileFreq) - currTime, 2);
		GetDlgItem(IDC_FS_REMAINING)->SetWindowText(s);
	}

}

void CDataCollectionStatusDlg::SetLocationsData(BOOL update)
{
	SetTimeSensitiveLocationsData();

	CString s;
	CInputLocFileInfo * currILFile = NULL;
	for (int wL = 0; wL < pDoc->nILFiles; wL++)
	{
		currILFile = &pDoc->m_ILData[wL];
		// show name
		m_InputLocations.SetItemText(0,wL+1,currILFile->m_Name);
		// show number of data 
		m_InputLocations.SetItemText(1,wL+1,IntToString(currILFile->m_nLocations));
		// show range of data...
		s = IntToString(currILFile->m_Locations[0] + 1) + " - " + IntToString(currILFile->m_Locations[currILFile->m_nLocations - 1] + 1);
		m_InputLocations.SetItemText(2,wL+1,s);
		// save data?
		m_InputLocations.SetItemText(3,wL+1,( currILFile->m_Do ? Strings.get(IDS_YES):Strings.get(IDS_NO)));
		// save average?
		m_InputLocations.SetItemText(4,wL+1,( currILFile->m_SaveByAverage ? Strings.get(IDS_YES):Strings.get(IDS_NO)));

		m_InputLocations.SetColumnWidth(wL+1,LVSCW_AUTOSIZE_USEHEADER);
	}

}

void CDataCollectionStatusDlg::SetTimeSensitiveLocationsData()
{
	CTime currTime = CTime::GetCurrentTime();
	CString s;

	CInputLocFileInfo * currILFile = NULL;
	for (int wL = 0; wL < pDoc->nILFiles; wL++)
	{
		currILFile = &pDoc->m_ILData[wL];
		// last collection , next collection, time remaining
		if (currILFile->m_LastReadTime != 0)
		{
			if (currILFile->m_nSuccessfulCollections)
				s = currILFile->m_LastReadTime.Format("%m/%d/%y %H:%M");
			else
				s = "-";
			m_InputLocations.SetItemText(5,wL+1,s);
			s = (currILFile->m_LastReadTime + currILFile->m_RetrFreq).Format("%m/%d/%y %H:%M");
			m_InputLocations.SetItemText(6,wL+1,s);

			s = GetTimeSpan((currILFile->m_LastReadTime + currILFile->m_RetrFreq) - currTime, 2);
			m_InputLocations.SetItemText(7,wL+1,s);
		}
		// show collection frequency
		m_InputLocations.SetItemText(8,wL+1,GetTimeSpan(currILFile->m_RetrFreq, 2));
		// show write frequency
		m_InputLocations.SetItemText(9,wL+1,GetTimeSpan(currILFile->m_WriteDataFreq, 2));
	}
	
}

void CDataCollectionStatusDlg::EnableFinalStorage(BOOL enable)
{
	GetDlgItem(IDC_FS_LAST)->EnableWindow(enable);
	GetDlgItem(IDC_FS_NEXT)->EnableWindow(enable);
	GetDlgItem(IDC_FS_REMAINING)->EnableWindow(enable);
	GetDlgItem(IDC_NEW_FS_FILE)->EnableWindow(enable);
	//GetDlgItem(IDC_W_CHAMBER)->EnableWindow(enable);
	GetDlgItem(IDC_FS_FREQUENCY)->EnableWindow(enable);
	GetDlgItem(IDC_FS_FREQUENCY)->EnableWindow(enable);
	GetDlgItem(IDC_IMPORT_FSL)->EnableWindow(enable);
	GetDlgItem(IDC_FS_LIST)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT7)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT13)->EnableWindow(enable);
	//GetDlgItem(IDC_TEXT1)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT6)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT5)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT4)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT3)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT2)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT14)->EnableWindow(enable);
	GetDlgItem(IDC_ARRAY_ID)->EnableWindow(enable);
	m_FSList.ShowWindow( enable ? SW_SHOW : SW_HIDE );
}

void CDataCollectionStatusDlg::EnableInputLocations(BOOL enable)
{
	GetDlgItem(IDC_GROUP)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT8)->EnableWindow(enable);
	GetDlgItem(IDC_INPUT_LOCATIONS)->EnableWindow(enable);
	GetDlgItem(IDC_PROPERTIES)->EnableWindow(enable);
	//GetDlgItem(IDC_NEW)->EnableWindow(enable); NEW SHOULD STILL BE AN OPTION
}

void CDataCollectionStatusDlg::OnSelchangeWChamber() 
{
	// TODO: Add your control notification handler code here
	if (freqChanged[m_wChamber])
	{
		ApplyCameraChanges(m_wChamber);
		freqChanged[m_wChamber] = false;
	}

	UpdateData(TRUE);
	
	EnableFinalStorage(m_wChamber < pDoc->nFSFiles);
	if (m_wChamber < pDoc->nFSFiles)
		SetChamberData();
	
	// show information about cameras...
	
	EnableCameras(m_wChamber < pDoc->nCameras);
	if (m_wChamber < pDoc->nCameras)
		SetTimeSensitiveCameraData();
	UpdateData(FALSE);
}

void CDataCollectionStatusDlg::EnableCameras(BOOL enable)
{
	// THIS IS ALSO CALLED EVERY TIME THE CURRENT CHAMBER IS CHANGED
	if (enable)
	{
		m_IsCameraEnabled = pDoc->m_CameraData[m_wChamber].m_Do;
		GetDlgItem(IDC_ENABLE_CAMERA)->SetWindowText(Strings.get(IDS_AA25) + IntToString(m_wChamber + 1));
	}
	GetDlgItem(IDC_ENABLE_CAMERA)->EnableWindow(enable);
	
	GetDlgItem(IDC_TEXT9)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT10)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT11)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT12)->EnableWindow(enable);
	GetDlgItem(IDC_C_LAST)->EnableWindow(enable);
	GetDlgItem(IDC_C_NEXT)->EnableWindow(enable);
	GetDlgItem(IDC_C_FREQUENCY)->EnableWindow(enable);
}

void CDataCollectionStatusDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData();
	if (pDoc->nFSFiles)
		SetTimer(FINAL_STORAGE_TIMER,1000,NULL);
	if (pDoc->nILFiles)
		SetTimer(INPUT_LOCATION_TIMER,1000,NULL);
	if (pDoc->nCameras)
		SetTimer(CAMERA_TIMER,1000,NULL);
	switch (nIDEvent)
	{
	case FINAL_STORAGE_TIMER:
		SetTimeSensitiveChamberData();
		break;
	case INPUT_LOCATION_TIMER:
		SetTimeSensitiveLocationsData();
		break;
	case CAMERA_TIMER:
		SetTimeSensitiveCameraData();
		break;
	}
	UpdateData(FALSE);
}

void CDataCollectionStatusDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnClose();
}


void CDataCollectionStatusDlg::OnSelchangeNewFsFile() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	pDoc->m_FSCollectionParam.m_NewFileFreq = CreateFileFreqTable[m_NewFSFrequency];
	lpfnTimerCallback lpfnTimer = &ResetTimer;
	pDoc->m_pMainView->SetFinalStorageTimer(lpfnTimer, CTime::GetCurrentTime());
	SetChamberData(FALSE);
}

void CDataCollectionStatusDlg::OnChangeArrayId() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (GetDlgItem(IDC_ARRAY_ID)->GetWindowTextLength() > 0)
	{
		UpdateData(TRUE);
		m_ptrFSInfo->m_ArrayID = m_ArrayID;

	}
}

BOOL CDataCollectionStatusDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDataCollectionStatusDlg::ResetGroupTimer()
{
	if (pDoc->InCommMode && pDoc->m_pMainView)
	{
		lpfnTimerCallback lpfnTimer = &ResetTimer;
		CTime currentTime = CTime::GetCurrentTime();
		pDoc->m_pMainView->SetILTimer(m_wGroup, lpfnTimer, currentTime);
		// this function will set or reset the timer depending on the value of
		// m_Do
	}
}

void CDataCollectionStatusDlg::SetTimeSensitiveCameraData()
{
	CString s;
	if (m_wChamber < pDoc->nCameras)
	{
		if ( (pDoc->m_CameraData[m_wChamber].m_LastPictureTaken != 0) && pDoc->m_CameraData[m_wChamber].m_nSuccessful)
			GetDlgItem(IDC_C_LAST)->SetWindowText(pDoc->m_CameraData[m_wChamber].m_LastPictureTaken.Format("%m/%d/%y %H:%M"));
		s = (pDoc->m_CameraData[m_wChamber].m_LastPictureTaken + pDoc->m_CameraData[m_wChamber].m_PictureFrequency).Format("%m/%d/%y %H:%M");
		GetDlgItem(IDC_C_NEXT)->SetWindowText(s);
		m_cFreq = ValueToString(pDoc->m_CameraData[m_wChamber].m_PictureFrequency.GetTotalMinutes() / 60.0);
	}
}

void CDataCollectionStatusDlg::ApplyCameraChanges(int wChamber)
{
	// reset the camera timer
	pDoc->m_pMainView->SetCameraTimer(wChamber);
	
}

void CDataCollectionStatusDlg::OnEnableCamera() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (pDoc->m_CameraData[m_wChamber].m_Do != m_IsCameraEnabled)
	{
		pDoc->SetModifiedFlag();
		if (m_IsCameraEnabled)
		{
			if (pDoc->m_CamerasEnabled == 0) // we have just turned the first camera on
			{
				if (MessageBox(IDS_M_LOAD_CAMERA_DRIVER_NOW,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
				{
					pDoc->LoadCameras();
					if (pDoc->m_LastCameraLoadFailed)
					{
						MessageBox(IDS_M_FAILED_LOAD_CAMERA,IDS_PROGRAM_NAME,MB_ICONWARNING);
						pDoc->UnloadCameras();
						m_IsCameraEnabled = FALSE;
						UpdateData(FALSE);
						return;
					}
					else
						MessageBox(IDS_M_SUCCEEDED_LOAD_CAMERA,IDS_PROGRAM_NAME,MB_ICONINFORMATION);
				}
				else
				{
					m_IsCameraEnabled = FALSE;
					UpdateData(FALSE);
					return;
				}
			}
			pDoc->m_CamerasEnabled++; 
		}
		else
		{
			if (pDoc->m_CamerasEnabled == 1) // we have just turned the last camera off
			{
				if (MessageBox(IDS_M_UNLOAD_CAMERA_DRIVER_NOW,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
					pDoc->UnloadCameras();
				else
				{
					m_IsCameraEnabled = TRUE;
					UpdateData(FALSE);
					return;
				}
				
			}
			pDoc->m_CamerasEnabled--;
#ifdef _DEBUG			
			if (pDoc->m_CamerasEnabled < 0)
				MessageBox("m_CamerasEnabled should not be less than 0","Program Error");
#endif

		}

		pDoc->m_CameraData[m_wChamber].m_Do = m_IsCameraEnabled;
	}
}

void CDataCollectionStatusDlg::OnChangeCFrequency() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int l;
	if (l = GetDlgItem(IDC_C_FREQUENCY)->GetWindowTextLength()) 
	{
		CString buf;
		GetDlgItem(IDC_C_FREQUENCY)->GetWindowText(buf);
		if (buf[l-1] != '.')
		{
	
			UpdateData();
			double v = StringToValue(buf.GetBuffer(0));
			CTimeSpan newFreq = CTimeSpan(0,int(v),int((double(v)-double(int(v))) * 60.0), 0);
			pDoc->m_CameraData[m_wChamber].m_PictureFrequency = newFreq;
			freqChanged[m_wChamber] = true;
		}
	}
}
