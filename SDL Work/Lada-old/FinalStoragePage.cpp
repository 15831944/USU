// FinalStoragePage.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "FinalStoragePage.h"

#include "Lada Control ModuleDoc.h"
#include "LString.h"
#include "LadaStrings.h"
#include "FSInfo.h"
#include "ImportFSLDlg.h"

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

extern CString IntToString(int number);
extern double StringToValue(const char * ptrString);
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern CFont RussianArial;
extern LString Strings;
extern CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);
extern int curLanguage;
extern CTimeSpan CreateFileFreqTable[3];

/////////////////////////////////////////////////////////////////////////////
// CFinalStoragePage property page

IMPLEMENT_DYNCREATE(CFinalStoragePage, CPropertyPage)

CFinalStoragePage::CFinalStoragePage() : CPropertyPage(CFinalStoragePage::IDD)
{
	//{{AFX_DATA_INIT(CFinalStoragePage)
	m_CR10WriteFSFreq = -1;
	m_SaveFSFreq = -1;
	m_wChamber = -1;
	m_nDataPoints = 0;
	//}}AFX_DATA_INIT
	IsModified = FALSE;
	m_ptrFSInfo = NULL;
}

CFinalStoragePage::~CFinalStoragePage()
{
}

void CFinalStoragePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFinalStoragePage)
	DDX_Control(pDX, IDC_FS_LIST, m_FSList);
	DDX_CBIndex(pDX, IDC_FS_FREQUENCY, m_CR10WriteFSFreq);
	DDX_CBIndex(pDX, IDC_NEW_FS_FILE, m_SaveFSFreq);
	DDX_CBIndex(pDX, IDC_W_CHAMBER, m_wChamber);
	DDX_Text(pDX, IDC_DATA_POINTS, m_nDataPoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFinalStoragePage, CPropertyPage)
	//{{AFX_MSG_MAP(CFinalStoragePage)
	ON_CBN_SELCHANGE(IDC_W_CHAMBER, OnSelchangeWChamber)
	ON_CBN_SELCHANGE(IDC_NEW_FS_FILE, OnSelchangeNewFsFile)
	ON_BN_CLICKED(IDC_IMPORT_FSL, OnImportFsl)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_FS_FREQUENCY, OnSelchangeFsFrequency)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFinalStoragePage message handlers

BOOL CFinalStoragePage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetStrings(FALSE);

	if (pDoc->nFSFiles)
		SetTimer(1,1000,NULL);
	return CPropertyPage::OnSetActive();
}

BOOL CFinalStoragePage::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(FINAL_STORAGE_TIMER);
	return CPropertyPage::OnKillActive();
}

BOOL CFinalStoragePage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// final storage
	GetDlgItem(IDC_TEXT1)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT2)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT3)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT4)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT5)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT6)->SetFont(&RussianArial);
	//GetDlgItem(IDC_TEXT7)->SetFont(&RussianArial);
	GetDlgItem(IDC_TEXT13)->SetFont(&RussianArial);
	GetDlgItem(IDC_DATA_POINTS_TXT)->SetFont(&RussianArial);

	GetDlgItem(IDC_FS_LAST)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_NEXT)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW_FS_FILE)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_REMAINING)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_FREQUENCY)->SetFont(&RussianArial);
	GetDlgItem(IDC_IMPORT_FSL)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_DATA_POINTS)->SetFont(&RussianArial);

	m_wChamber = 0;

	if (pDoc->nFSFiles == 0)
		EnableFinalStorage(FALSE);
	else
	{
		m_ptrFSInfo = &pDoc->m_FSOutputTable[m_wChamber];

		// newFsFrequency has to do with how often all FS files are created
		m_InitialSaveFreq = m_SaveFSFreq = 0;
		for (int i = 0; i < 3; i++)
		{
			if (CreateFileFreqTable[i] == pDoc->m_FSCollectionParam.m_NewFileFreq )
			{
				m_InitialSaveFreq = m_SaveFSFreq = i;
				break;
			}
		}
		SetChamberData(FALSE);
		SetTimer(FINAL_STORAGE_TIMER,1000,NULL);
	}

	if (pDoc->nFSFiles < 2)
	{
		GetDlgItem(IDC_TEXT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_W_CHAMBER)->EnableWindow(FALSE);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			((CComboBox*)GetDlgItem(IDC_W_CHAMBER))->AddString(IntToString(i+1));
		}
	}
	// TODO: Add extra initialization here
	SetModified(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFinalStoragePage::OnImportFsl() 
{
	// TODO: Add your control notification handler code here
	CImportFSLDlg fDlg(pDoc, m_ptrFSInfo);

	if (fDlg.DoModal()==IDOK)
	{
		SetModified();
		OnOK();
		SetChamberData();
	}
}

void CFinalStoragePage::SetStrings(BOOL updateData)
{
	if (updateData)
		UpdateData(TRUE);

	SetWindowText(Strings.get(IDS_AA2));
	
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AA1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_AA2));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_AA3));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_AA4));
	GetDlgItem(IDC_TEXT5)->SetWindowText(Strings.get(IDS_AA5));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_AA6));
	//GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_AA7));
	GetDlgItem(IDC_TEXT13)->SetWindowText(Strings.get(IDS_AA13));
	GetDlgItem(IDC_DATA_POINTS_TXT)->SetWindowText(Strings.get(IDS_AA27));

	GetDlgItem(IDC_IMPORT_FSL)->SetWindowText(Strings.get(IDS_AA_IMPORT_FSL));

	for(int i = 0; i < 3; i++)
		((CComboBox*)GetDlgItem(IDC_NEW_FS_FILE))->AddString(Strings.get(IDS_N_FILETIME1 + i));

	for(i = 0; i < 2; i++)
		((CComboBox*)GetDlgItem(IDC_FS_FREQUENCY))->AddString(Strings.get(IDS_N_FSFREQ1 + i));
	
	UpdateData(FALSE);
}

void CFinalStoragePage::SetChamberData(BOOL updateData)
{
	if (updateData)
		UpdateData(TRUE);

	// info that is specific to each chamber
	m_InitialCR10Freq = m_CR10WriteFSFreq = m_ptrFSInfo->m_wFreqSel;

	m_FSList.ResetContent();
	for (int i = 0; i < m_ptrFSInfo->m_nDataItems; i++)
		m_FSList.AddString(m_ptrFSInfo->m_DataNames[i]);
	
	
	SetTimeSensitiveChamberData();
	m_nDataPoints = m_ptrFSInfo->m_nDataItems;

	UpdateData(FALSE);
}

void CFinalStoragePage::SetTimeSensitiveChamberData()
{
	CTime currTime = CTime::GetCurrentTime();
	CString s;
	if (pDoc->m_FSCollectionParam.m_nSuccessfulCollections)
			GetDlgItem(IDC_FS_LAST)->SetWindowText(pDoc->m_FSCollectionParam.m_LastCreateTime.Format("%m/%d/%y %H:%M"));

	if ( pDoc->m_FSCollectionParam.m_NextCollectionTime != 0 && pDoc->InCommMode )
	{
		s = pDoc->m_FSCollectionParam.m_NextCollectionTime.Format("%m/%d/%y %H:%M");
		GetDlgItem(IDC_FS_NEXT)->SetWindowText(s);
		s = GetTimeSpan(pDoc->m_FSCollectionParam.m_NextCollectionTime - currTime, 2);
		GetDlgItem(IDC_FS_REMAINING)->SetWindowText(s);
	}
	else
	{
		GetDlgItem(IDC_FS_NEXT)->SetWindowText("???");
		GetDlgItem(IDC_FS_REMAINING)->SetWindowText("???");
	}

}

void CFinalStoragePage::EnableFinalStorage(BOOL enable)
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
//	GetDlgItem(IDC_TEXT7)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT13)->EnableWindow(enable);
	//GetDlgItem(IDC_TEXT1)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT6)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT5)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT4)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT3)->EnableWindow(enable);
	GetDlgItem(IDC_TEXT2)->EnableWindow(enable);
	//GetDlgItem(IDC_TEXT14)->EnableWindow(enable);
//	GetDlgItem(IDC_ARRAY_ID)->EnableWindow(enable);
	GetDlgItem(IDC_DATA_POINTS_TXT)->EnableWindow(enable);
	GetDlgItem(IDC_DATA_POINTS)->EnableWindow(enable);
	
	m_FSList.ShowWindow( enable ? SW_SHOW : SW_HIDE );
}

void CFinalStoragePage::OnSelchangeWChamber() 
{
	// TODO: Add your control notification handler code here
	OnOK();
	m_ptrFSInfo = &pDoc->m_FSOutputTable[m_wChamber];
#ifdef _DEBUG
	ASSERT(m_ptrFSInfo!=NULL);
#endif
	SetChamberData(FALSE);
}


void CFinalStoragePage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	SetTimeSensitiveChamberData();
}

void CFinalStoragePage::OnSelchangeNewFsFile() 
{
	// TODO: Add your control notification handler code here
	SetModified();
}

BOOL CFinalStoragePage::PreTranslateMessage(MSG* pMsg) 
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

void CFinalStoragePage::SetDocument(CLADAControlModuleDoc *doc)
{
	pDoc = doc;
}


void CFinalStoragePage::OnOK() 
{
	// TODO: Add your specialized code here and/or call the base class
	//char buf[100]; wsprintf(buf,"Final Storage - OnOK called.\nIsModified = %i",IsModified);
	//MessageBox(buf);
	UpdateData(TRUE);

	if (IsModified)
	{
		if (m_InitialSaveFreq != m_SaveFSFreq) 
			// final storage collection frequency has changed
		{
			pDoc->m_FSCollectionParam.m_NewFileFreq = CreateFileFreqTable[m_SaveFSFreq];
			lpfnTimerCallback lpfnTimer = &ResetTimer;
			pDoc->m_pMainView->SetFinalStorageTimer(lpfnTimer, CTime::GetCurrentTime());
			SetChamberData(FALSE);

		}

		if (m_CR10WriteFSFreq != m_InitialCR10Freq)
		{


		}
		//if (GetDlgItem(IDC_ARRAY_ID)->GetWindowTextLength() < 1)
		//{
		//	MessageBox("Array ID is invalid");
		//	GetDlgItem(IDC_ARRAY_ID)->SetFocus();
		//	return;
		//}
		//m_ptrFSInfo->m_ArrayID = m_ArrayID;

		SetModified(FALSE);


	}
	CPropertyPage::OnOK();
}

void CFinalStoragePage::SetModified(BOOL Modified)
{
	IsModified = Modified;
	CPropertyPage::SetModified(Modified);
}

void CFinalStoragePage::OnSelchangeFsFrequency() 
{
	// TODO: Add your control notification handler code here
	SetModified();
	OnOK();
}
