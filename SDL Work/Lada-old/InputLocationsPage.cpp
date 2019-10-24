// InputLocationsPage.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "InputLocationsPage.h"

#include "Lada Control ModuleDoc.h"
#include "LString.h"
#include "LadaStrings.h"
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
extern CString IntToString(int number);
extern void CALLBACK EXPORT ResetTimer(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
);
extern UINT IDS_TEMP;

/////////////////////////////////////////////////////////////////////////////
// CInputLocationsPage property page

IMPLEMENT_DYNCREATE(CInputLocationsPage, CPropertyPage)

CInputLocationsPage::CInputLocationsPage() : CPropertyPage(CInputLocationsPage::IDD)
{
	//{{AFX_DATA_INIT(CInputLocationsPage)
	m_wGroup = -1;
	//}}AFX_DATA_INIT
	IsModified = FALSE;
}

CInputLocationsPage::~CInputLocationsPage()
{
}

void CInputLocationsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputLocationsPage)
	DDX_Control(pDX, IDC_INPUT_LOCATIONS, m_InputLocations);
	DDX_Control(pDX, IDC_GROUP, m_cGroup);
	DDX_CBIndex(pDX, IDC_GROUP, m_wGroup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputLocationsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CInputLocationsPage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputLocationsPage message handlers

BOOL CInputLocationsPage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnKillActive();
}

BOOL CInputLocationsPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetStrings(FALSE);

	if (pDoc->nILFiles)
		SetTimer(1,1000,NULL);

	return CPropertyPage::OnSetActive();
}

BOOL CInputLocationsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// input locations
	GetDlgItem(IDC_TEXT8)->SetFont(&RussianArial);
	GetDlgItem(IDC_INPUT_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_PROPERTIES)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW)->SetFont(&RussianArial);
	GetDlgItem(IDC_GROUP)->SetFont(&RussianArial);
	GetDlgItem(IDC_DELETE)->SetFont(&RussianArial);
	// start initializing locations info
	m_wGroup = 0;
	m_InputLocations.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_InputLocations.InsertColumn(0,"      ");

	for (int i = 0; i < 10; i++)
		m_InputLocations.InsertItem(i, Strings.get(IDS_AA15 + i));

	if (pDoc->nILFiles == 0)
		EnableInputLocations(FALSE);
	else
	{
		for (i = 1; i <= pDoc->nILFiles; i++)
		{
			m_cGroup.AddString(pDoc->m_ILData[i-1].m_Name);
		}
		SetLocationsData(FALSE);
	}
	m_InputLocations.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	// TODO: Add extra initialization here
	SetModified(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CInputLocationsPage::OnProperties() 
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
			SetLocationsData(FALSE);
			pDoc->SetModifiedFlag();
		}
		SetStrings();	
	}

	UpdateData(FALSE);
}

void CInputLocationsPage::OnNew() 
{
	// TODO: Add your control notification handler code here
	CInputLocFileInfo fInfo;

	CILProperties gDlg(pDoc, &fInfo, pDoc->nILFiles);
	if (gDlg.DoModal() == IDOK)
	{
		m_wGroup = pDoc->nILFiles;
		if (pDoc->nILFiles == 0)
			EnableInputLocations(TRUE);
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
		SetLocationsData(FALSE);
		pDoc->SetModifiedFlag();
	}
	SetStrings();
}


void CInputLocationsPage::SetStrings(BOOL updateData)
{
	if (updateData)
		UpdateData(TRUE);

	SetWindowText(Strings.get(IDS_AA8));
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_AA8));
	GetDlgItem(IDC_PROPERTIES)->SetWindowText(Strings.get(IDS_AA_PROPERTIES));
	GetDlgItem(IDC_NEW)->SetWindowText(Strings.get(IDS_AA_NEW));
	GetDlgItem(IDC_DELETE)->SetWindowText(Strings.get(IDS_AA29));

	for (int i = 0; i < 10; i++)
		m_InputLocations.SetItemText(i, 0, Strings.get(IDS_AA15 + i));	

	UpdateData(FALSE);

	SetLocationsData();

}

void CInputLocationsPage::SetLocationsData(BOOL update)
{
	SetTimeSensitiveLocationsData();

	CString s;
	CInputLocFileInfo * currILFile = NULL;
	m_InputLocations.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	for (int wL = 0; wL < pDoc->nILFiles; wL++)
	{
		currILFile = &pDoc->m_ILData[wL];
		
		m_InputLocations.DeleteColumn(wL + 1);
		m_InputLocations.InsertColumn(wL+1,IntToString(wL+1));
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

void CInputLocationsPage::SetTimeSensitiveLocationsData()
{
	CTime currTime = CTime::GetCurrentTime();
	CString s;

	CInputLocFileInfo * currILFile = NULL;
	for (int wL = 0; wL < pDoc->nILFiles; wL++)
	{
		currILFile = &pDoc->m_ILData[wL];
		// last collection , next collection, time remaining
		if (currILFile->m_nSuccessfulCollections)
				s = currILFile->m_LastReadTime.Format("%m/%d/%y %H:%M");
			else
				s = "-";
			m_InputLocations.SetItemText(5,wL+1,s);

		if (currILFile->m_Do && pDoc->InCommMode)
		{
			s = (currILFile->m_NextCollectionTime).Format("%m/%d/%y %H:%M");
			m_InputLocations.SetItemText(6,wL+1,s);
			s = GetTimeSpan(currILFile->m_NextCollectionTime - currTime, 2);
			m_InputLocations.SetItemText(7,wL+1,s);
		}
		else
		{
			m_InputLocations.SetItemText(6,wL+1,"???");
			m_InputLocations.SetItemText(7,wL+1,"???");
		}

		// show collection frequency
		m_InputLocations.SetItemText(8,wL+1,GetTimeSpan(currILFile->m_RetrFreq, 2));
		// show write frequency
		m_InputLocations.SetItemText(9,wL+1,GetTimeSpan(currILFile->m_WriteDataFreq, 2));
	}
}



void CInputLocationsPage::EnableInputLocations(BOOL enable)
{
	GetDlgItem(IDC_GROUP)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT8)->EnableWindow(enable);
	GetDlgItem(IDC_INPUT_LOCATIONS)->EnableWindow(enable);
	GetDlgItem(IDC_PROPERTIES)->EnableWindow(enable);
	//GetDlgItem(IDC_NEW)->EnableWindow(enable); NEW SHOULD STILL BE AN OPTION
}

void CInputLocationsPage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData();

	SetTimeSensitiveLocationsData();
	
	UpdateData(FALSE);
}

BOOL CInputLocationsPage::PreTranslateMessage(MSG* pMsg) 
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

void CInputLocationsPage::ResetGroupTimer()
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

void CInputLocationsPage::SetDocument(CLADAControlModuleDoc * doc)
{
	pDoc = doc;
}

void CInputLocationsPage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	//char buf[100]; wsprintf(buf,"Input Locations - OnOK called.\nIsModified = %i",IsModified);
	//MessageBox(buf);
	CPropertyPage::OnOK();
}

void CInputLocationsPage::SetModified(BOOL Modified)
{
	IsModified = Modified;
	CPropertyPage::SetModified(Modified);
}


void CInputLocationsPage::OnDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	if (m_wGroup != -1)
	{
		CString eng = Strings.get(IDS_M_SURE_DELETE, ENGLISH) + pDoc->m_ILData[m_wGroup].m_Name+CString("\"?");
		CString russ = Strings.get(IDS_M_SURE_DELETE, RUSSIAN) + pDoc->m_ILData[m_wGroup].m_Name+CString("\"?");
		Strings.set(eng,russ,IDS_TEMP);

		if (MessageBox(IDS_TEMP,IDS_PROGRAM_NAME, MB_YESNO|MB_ICONQUESTION) == IDYES)
		{
			// turn the data collection for this group off...
			pDoc->m_ILData[m_wGroup].m_Do = FALSE;
			ResetGroupTimer();
			// decrement the number of data files
			pDoc->nILFiles--;
			m_cGroup.DeleteString( m_wGroup );
			CInputLocFileInfo *temp = pDoc->m_ILData;
			// resize the array
			if (pDoc->nILFiles)
			{
				pDoc->m_ILData = new CInputLocFileInfo[pDoc->nILFiles];
				// copy the data from the old array to the new array
				for (int wGroup = 0; wGroup < m_wGroup; wGroup++)
					pDoc->m_ILData[wGroup] = temp[wGroup];	
				for (; wGroup < pDoc->nILFiles; wGroup++)
					pDoc->m_ILData[wGroup] = temp[wGroup + 1];
				m_wGroup = 0;
				m_cGroup.SetCurSel( 0 );
			}
			else
			{
				m_wGroup = -1;
				EnableInputLocations(FALSE);
				pDoc->m_ILData = NULL;
			}
			// delete the old array
			delete [] temp;
			// update the display
			m_InputLocations.DeleteColumn(pDoc->nILFiles+1);
			SetLocationsData(FALSE);
			pDoc->SetModifiedFlag();
		}
		SetStrings();	
	}

	UpdateData(FALSE);
}
