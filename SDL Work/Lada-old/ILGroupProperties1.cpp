// This is Version 1.0 PLEASE DOCUMENT CHANGES
// ILGroupProperties.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ILGroupProperties.h"

#include "LADA Control ModuleDoc.h"
#include "InputLocFileInfo.h"
#include "ChooseLocationsDialog.h"
#include "LadaStrings.h"
#include "LString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
extern void SetItemFont(UINT controlID, CWnd *window);
#undef MessageBox
#define MessageBox MyMessageBox

/////////////////////////////////////////////////////////////////////////////
// CILGroupProperties dialog
extern CTimeSpan DataRetrievalFreqTable[10];
extern CTimeSpan DataSaveFreqTable[7];
extern CTimeSpan CreateFileFreqTable[3];
extern CFont RussianArial;

extern void CALLBACK EXPORT ResetTimer(
   HWND hWnd,      // handle of CWnd that called SetTimer
   UINT nMsg,      // WM_TIMER
   UINT nIDEvent,   // timer identification
   DWORD dwTime    // system time
);

CILGroupProperties::CILGroupProperties(CLADAControlModuleDoc * doc, CInputLocFileInfo * ptrILFileInfo, int wG, CWnd* pParent /*=NULL*/)
	: CDialog(CILGroupProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CILGroupProperties)
	m_SaveData = FALSE;
	m_DataRetrFreq = -1;
	m_GroupName = _T("");
	m_NewILFileFreq = -1;
	m_NIL = 0;
	m_SaveDataFreq = -1;
	//}}AFX_DATA_INIT
	wGroup = wG;
	pDoc = doc;
	m_ptrILFileInfo = ptrILFileInfo;
	m_LocList = new int[pDoc->nInputLocations];
	

}

CILGroupProperties::~CILGroupProperties()
{
	delete [] m_LocList;
}

void CILGroupProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CILGroupProperties)
	DDX_Control(pDX, IDC_NEW_ILFILE_FREQ, m_F3);
	DDX_Control(pDX, IDC_SAVE_DATA_FREQ, m_F2);
	DDX_Control(pDX, IDC_DATA_RETRIEVAL_FREQ, m_F1);
	DDX_Check(pDX, IDC_SAVE_DATA, m_SaveData);
	DDX_CBIndex(pDX, IDC_DATA_RETRIEVAL_FREQ, m_DataRetrFreq);
	DDX_Text(pDX, IDC_ILGROUPNAME, m_GroupName);
	DDX_CBIndex(pDX, IDC_NEW_ILFILE_FREQ, m_NewILFileFreq);
	DDX_Text(pDX, IDC_NIL, m_NIL);
	DDX_CBIndex(pDX, IDC_SAVE_DATA_FREQ, m_SaveDataFreq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CILGroupProperties, CDialog)
	//{{AFX_MSG_MAP(CILGroupProperties)
	ON_BN_CLICKED(IDC_SAVE_DATA, OnSaveData)
	ON_BN_CLICKED(IDC_CHOOSE_ILL_LIST, OnChooseIllList)
	ON_BN_CLICKED(IDC_TEXT19, OnAverage)
	ON_BN_CLICKED(IDC_TEXT20, OnOneInstant)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CILGroupProperties message handlers

void CILGroupProperties::OnSaveData() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_TEXT17)->EnableWindow(m_SaveData);
	m_F1.EnableWindow(m_SaveData);
	GetDlgItem(IDC_TEXT18)->EnableWindow(m_SaveData);
	m_F2.EnableWindow(m_SaveData);
//	GetDlgItem(IDC_AVERAGE)->EnableWindow(m_SaveData);
	GetDlgItem(IDC_TEXT20)->EnableWindow(m_SaveData);
	GetDlgItem(IDC_TEXT19)->EnableWindow(m_SaveData);
	m_F3.EnableWindow(m_SaveData);
}

void CILGroupProperties::OnChooseIllList() 
{
	if (pDoc->nInputLocations > 0)
	{
		UpdateData(TRUE);
			
		CChooseLocationsDlg getNamesDlg(pDoc->InputLocationNameList, m_LocList, &m_NIL, pDoc->nInputLocations);
		
		if (getNamesDlg.DoModal() == IDOK)
		{
			//m_ptrILFileInfo->SetListInfo(nLocs, Locs);
			UpdateData(FALSE);
		}
		SetStrings();
		
		
		//delete [] Locs;
	}
	else
	{
		MessageBox(IDS_PLEASE_EDIT_LIST, IDS_ERROR, MB_OK);
		ResetStrings();
	}
}

void CILGroupProperties::OnAverage() 
{
	m_SaveByAverage = TRUE;
	ShowAverageInstant();
}

void CILGroupProperties::OnOneInstant() 
{
	m_SaveByAverage = FALSE;
	ShowAverageInstant();
}

void CILGroupProperties::ShowAverageInstant()
{
	((CButton *)GetDlgItem(IDC_TEXT19))->SetCheck(m_SaveByAverage);
	((CButton *)GetDlgItem(IDC_TEXT20))->SetCheck(!m_SaveByAverage);
}

void CILGroupProperties::OnOK() 
{
	UpdateData();
	if (m_ptrILFileInfo->m_Do != m_SaveData ||
		m_ptrILFileInfo->m_RetrFreq != DataRetrievalFreqTable[m_DataRetrFreq] ||
		m_ptrILFileInfo->m_WriteDataFreq != DataSaveFreqTable[m_SaveDataFreq] )
	{
		m_ptrILFileInfo->m_Do = m_SaveData;
		m_ptrILFileInfo->m_RetrFreq = DataRetrievalFreqTable[m_DataRetrFreq];
		m_ptrILFileInfo->m_WriteDataFreq = DataSaveFreqTable[m_SaveDataFreq];
		if (pDoc->InCommMode && pDoc->m_pMainView)
		{
			lpfnTimerCallback lpfnTimer = &ResetTimer;
			CTime currentTime = CTime::GetCurrentTime();
			pDoc->m_pMainView->SetILTimer(wGroup, lpfnTimer, currentTime);

		}
	}
	
	m_ptrILFileInfo->m_SaveByAverage = m_SaveByAverage;
	m_ptrILFileInfo->m_Name = m_GroupName;
	m_ptrILFileInfo->m_nLocations = m_NIL;

	if (m_ptrILFileInfo->m_Locations)
		delete [] m_ptrILFileInfo->m_Locations;
	m_ptrILFileInfo->m_Locations = new int[m_NIL];
	memcpy(m_ptrILFileInfo->m_Locations,m_LocList, sizeof(int) * m_NIL);
	
	if (m_ptrILFileInfo->m_tempData)
		delete [] m_ptrILFileInfo->m_tempData;
	m_ptrILFileInfo->m_tempData = new double[m_NIL];
	memset(m_ptrILFileInfo->m_tempData,0,sizeof(double)*m_NIL);
	m_ptrILFileInfo->m_nItemsInTempData = 0;
	
	m_ptrILFileInfo->m_NewFileFreq = CreateFileFreqTable[m_NewILFileFreq];
			 
	CDialog::OnOK();
}

BOOL CILGroupProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
		
	m_SaveData = m_ptrILFileInfo->m_Do;
	m_SaveByAverage = m_ptrILFileInfo->m_SaveByAverage;
	m_GroupName = m_ptrILFileInfo->m_Name;
	m_NIL = m_ptrILFileInfo->m_nLocations;

	memcpy(m_LocList,m_ptrILFileInfo->m_Locations, sizeof(int) * m_ptrILFileInfo->m_nLocations);

	//m_DataRetrFreq = ;// default value
	//m_SaveDataFreq
	//m_NewILFileFreq

	m_F1.SetFont(&RussianArial);
	for (int i = 0; i < 10; i++)
	{
		m_F1.AddString(Strings.get(IDS_N_DATARETR1 + i));
		if (m_ptrILFileInfo->m_RetrFreq == DataRetrievalFreqTable[i])
			m_DataRetrFreq = i;
		
	}
	m_F2.SetFont(&RussianArial);
	for (i = 0; i < 7; i++)
	{
		m_F2.AddString(Strings.get(IDS_N_DATASAVE1 + i));
		if (m_ptrILFileInfo->m_WriteDataFreq == DataSaveFreqTable[i])
			m_SaveDataFreq = i;
	}
	m_F3.SetFont(&RussianArial);
	for(i = 0; i < 3; i++){
		m_F3.AddString(Strings.get(IDS_N_FILETIME1 + i));
		if (m_ptrILFileInfo->m_NewFileFreq == CreateFileFreqTable[i])
			m_NewILFileFreq = i;
	}

	UpdateData(FALSE);
	OnSaveData();
	ShowAverageInstant();

	SetItemFont(IDC_TEXT14,this);
	SetItemFont(IDC_TEXT15,this);
	SetItemFont(IDC_TEXT16,this);
	SetItemFont(IDC_TEXT17,this);
	SetItemFont(IDC_TEXT18,this);
	SetItemFont(IDC_TEXT19,this);
	SetItemFont(IDC_TEXT20,this);
	SetItemFont(IDC_TEXT21,this);
	SetItemFont(IDC_SAVE_DATA,this);
	SetItemFont(IDC_CHOOSE_ILL_LIST,this);
	SetItemFont(IDOK,this);
	SetItemFont(IDCANCEL,this);
	SetStrings();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CILGroupProperties::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		ResetStrings();
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CILGroupProperties::SetStrings()
{
	SetWindowText(Strings.get(IDS_O0));
	GetDlgItem(IDC_TEXT14)->SetWindowText(Strings.get(IDS_O1));
	GetDlgItem(IDC_TEXT15)->SetWindowText(Strings.get(IDS_W7));
	GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_O2));
	GetDlgItem(IDC_SAVE_DATA)->SetWindowText(Strings.get(IDS_O3));
	GetDlgItem(IDC_TEXT17)->SetWindowText(Strings.get(IDS_O4));
	GetDlgItem(IDC_TEXT18)->SetWindowText(Strings.get(IDS_O5));
	GetDlgItem(IDC_TEXT19)->SetWindowText(Strings.get(IDS_O6));
	GetDlgItem(IDC_TEXT20)->SetWindowText(Strings.get(IDS_O7));
	GetDlgItem(IDC_TEXT21)->SetWindowText(Strings.get(IDS_O8));
	GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetWindowText(Strings.get(IDS_CHOOSE));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));
	m_F1.ResetContent();
	for (int i = 0; i < 10; i++)
	{
		m_F1.AddString(Strings.get(IDS_N_DATARETR1 + i));
		if (m_ptrILFileInfo->m_RetrFreq == DataRetrievalFreqTable[i])
			m_DataRetrFreq = i;
		
	}
	m_F2.ResetContent();
	for (i = 0; i < 7; i++)
	{
		m_F2.AddString(Strings.get(IDS_N_DATASAVE1 + i));
		if (m_ptrILFileInfo->m_WriteDataFreq == DataSaveFreqTable[i])
			m_SaveDataFreq = i;
	}
	m_F3.ResetContent();
	for(i = 0; i < 3; i++)
	{
		m_F3.AddString(Strings.get(IDS_N_FILETIME1 + i));
		if (m_ptrILFileInfo->m_NewFileFreq == CreateFileFreqTable[i])
			m_NewILFileFreq = i;
	}
}

void CILGroupProperties::ResetStrings()
{
		SetStrings();
		m_F1.ResetContent();
		for (int i = 0; i < 10; i++)
		{
			m_F1.AddString(Strings.get(IDS_N_DATARETR1 + i));
			if (m_ptrILFileInfo->m_RetrFreq == DataRetrievalFreqTable[i])
				m_DataRetrFreq = i;
			
		}
		m_F2.ResetContent();
		for (i = 0; i < 7; i++)
		{
			m_F2.AddString(Strings.get(IDS_N_DATASAVE1 + i));
			if (m_ptrILFileInfo->m_WriteDataFreq == DataSaveFreqTable[i])
				m_SaveDataFreq = i;
		}
		m_F3.ResetContent();
		for(i = 0; i < 3; i++){
			m_F3.AddString(Strings.get(IDS_N_FILETIME1 + i));
			if (m_ptrILFileInfo->m_NewFileFreq == CreateFileFreqTable[i])
				m_NewILFileFreq = i;
		}
}
