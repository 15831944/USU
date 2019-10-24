// ILProperties.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ILProperties.h"

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

extern int curLanguage;
extern LString Strings;
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
extern void SetItemFont(UINT controlID, CWnd *window);
#undef MessageBox
#define MessageBox MyMessageBox


/////////////////////////////////////////////////////////////////////////////
// CILProperties dialog

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

CILProperties::CILProperties(CLADAControlModuleDoc * doc, CInputLocFileInfo * ptrILFileInfo, int wG, CWnd* pParent /*=NULL*/)
	: CDialog(CILProperties::IDD, pParent)
{
	//{{AFX_DATA_INIT(CILProperties)
	m_DataRetrFreq = -1;
	m_GroupName = _T("");
	m_NewILFileFreq = -1;
	m_SaveData = FALSE;
	m_SaveDataFreq = -1;
	m_NIL = 0;
	//}}AFX_DATA_INIT
	wGroup = wG;
	pDoc = doc;
	m_ptrILFileInfo = ptrILFileInfo;
	m_LocList = new int[pDoc->nInputLocations];
	doResetTimer = false;
}

CILProperties::~CILProperties()
{
	delete [] m_LocList;
}

void CILProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CILProperties)
	DDX_Control(pDX, IDC_ONE_INSTANT, m_Instant);
	DDX_Control(pDX, IDC_AVERAGE, m_Average);
	DDX_Control(pDX, IDC_SAVE_DATA_FREQ, m_F2);
	DDX_Control(pDX, IDC_NEW_ILFILE_FREQ, m_F3);
	DDX_Control(pDX, IDC_DATA_RETRIEVAL_FREQ, m_F1);
	DDX_CBIndex(pDX, IDC_DATA_RETRIEVAL_FREQ, m_DataRetrFreq);
	DDX_Text(pDX, IDC_ILGROUPNAME, m_GroupName);
	DDX_CBIndex(pDX, IDC_NEW_ILFILE_FREQ, m_NewILFileFreq);
	DDX_Check(pDX, IDC_SAVE_DATA, m_SaveData);
	DDX_CBIndex(pDX, IDC_SAVE_DATA_FREQ, m_SaveDataFreq);
	DDX_Text(pDX, IDC_NIL, m_NIL);
	//}}AFX_DATA_MAP
	
}


BEGIN_MESSAGE_MAP(CILProperties, CDialog)
	//{{AFX_MSG_MAP(CILProperties)
	ON_BN_CLICKED(IDC_AVERAGE, OnAverage)
	ON_BN_CLICKED(IDC_ONE_INSTANT, OnOneInstant)
	ON_BN_CLICKED(IDC_CHOOSE_ILL_LIST, OnChooseIllList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CILProperties message handlers

void CILProperties::OnAverage() 
{
	// TODO: Add your control notification handler code here
	m_ByAverage = TRUE;
	ShowAverageInstant();	
}

void CILProperties::OnOneInstant() 
{
	// TODO: Add your control notification handler code here
	m_ByAverage = FALSE;
	ShowAverageInstant();
}

void CILProperties::OnChooseIllList() 
{
	// TODO: Add your control notification handler code here
	if (pDoc->nInputLocations > 0)
	{
		UpdateData(TRUE);
			
		CChooseLocationsDlg getNamesDlg(pDoc->InputLocationNameList, m_LocList, &m_NIL, pDoc->nInputLocations);
		
		if (getNamesDlg.DoModal() == IDOK)
		{
			UpdateData(FALSE);
		}
		SetStrings();
		
		
		//delete [] Locs;
	}
	else
	{
		MessageBox(IDS_PLEASE_EDIT_LIST, IDS_ERROR, MB_OK);
		SetStrings();
	}

}

BOOL CILProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetFont(&RussianArial);

	m_SaveData = m_ptrILFileInfo->m_Do;
	m_ByAverage = m_ptrILFileInfo->m_SaveByAverage;
	m_GroupName = m_ptrILFileInfo->m_Name;
	m_NIL = m_ptrILFileInfo->m_nLocations;

	memcpy(m_LocList, m_ptrILFileInfo->m_Locations, sizeof(int) * m_ptrILFileInfo->m_nLocations);

	//m_DataRetrFreq = ;// default value
	//m_SaveDataFreq
	//m_NewILFileFreq

	m_F1.SetFont(&RussianArial);
	m_F2.SetFont(&RussianArial);
	m_F3.SetFont(&RussianArial);
	for (int i = 0; i < 6; i++)
		GetDlgItem(IDC_TEXT12 + i)->SetFont(&RussianArial);
	
	GetDlgItem(IDC_SAVE_DATA)->SetFont(&RussianArial);
	GetDlgItem(IDOK)->SetFont(&RussianArial);
	GetDlgItem(IDCANCEL)->SetFont(&RussianArial);
	GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_NIL)->SetFont(&RussianArial);
	GetDlgItem(IDC_AVERAGE)->SetFont(&RussianArial);
	GetDlgItem(IDC_ONE_INSTANT)->SetFont(&RussianArial);
	GetDlgItem(IDC_ILGROUPNAME)->SetFont(&RussianArial);

	for ( i = 0; i < 10; i++)
	{
		m_F1.AddString(Strings.get(IDS_N_DATARETR1 + i));
		if (m_ptrILFileInfo->m_RetrFreq == DataRetrievalFreqTable[i])
			m_DataRetrFreq = i;
		
	}
	for (i = 0; i < 7; i++)
	{
		m_F2.AddString(Strings.get(IDS_N_DATASAVE1 + i));
		if (m_ptrILFileInfo->m_WriteDataFreq == DataSaveFreqTable[i])
			m_SaveDataFreq = i;
	}
	for(i = 0; i < 3; i++){
		m_F3.AddString(Strings.get(IDS_N_FILETIME1 + i));
		if (m_ptrILFileInfo->m_NewFileFreq == CreateFileFreqTable[i])
			m_NewILFileFreq = i;
	}

	UpdateData(FALSE);

	ShowAverageInstant();

	SetStrings(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CILProperties::ShowAverageInstant()
{
	m_Average.SetCheck(m_ByAverage);
	m_Instant.SetCheck(!m_ByAverage);

	if (m_ByAverage)
	{
		GetDlgItem(IDC_TEXT15)->ShowWindow(SW_SHOW);
		m_F1.EnableWindow(TRUE);
		m_F1.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_W16));
	}
	else // SAVE INSTANT
	{
		GetDlgItem(IDC_TEXT15)->ShowWindow(SW_HIDE);
		m_F1.EnableWindow(FALSE);
		m_F1.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_W27));
	}
}

void CILProperties::SetStrings(BOOL updateData) // = TRUE
{
	if (updateData)
		UpdateData(TRUE);
	//SetWindowText(Strings.get(IDS_W0));
	
	for (int i = 0; i < 6; i++)
		GetDlgItem(IDC_TEXT12 + i)->SetWindowText(Strings.get(IDS_W12+i));

	GetDlgItem(IDC_SAVE_DATA)->SetWindowText(Strings.get(IDS_O3));

	GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetWindowText(Strings.get(IDS_W22));
	GetDlgItem(IDC_AVERAGE)->SetWindowText(Strings.get(IDS_W23));
	GetDlgItem(IDC_ONE_INSTANT)->SetWindowText(Strings.get(IDS_W24));

	m_F1.ResetContent();
	m_F2.ResetContent();
	m_F3.ResetContent();
	for (i = 0; i < 10; i++)
		m_F1.AddString(Strings.get(IDS_N_DATARETR1 + i));
	for (i = 0; i < 7; i++)
		m_F2.AddString(Strings.get(IDS_N_DATASAVE1 + i));
	for(i = 0; i < 3; i++)
		m_F3.AddString(Strings.get(IDS_N_FILETIME1 + i));
		
	UpdateData(FALSE);
}

BOOL CILProperties::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CILProperties::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if (m_NIL == 0)
	{
		MessageBox("You must select at least one input location into this group.");
		return;
	}

	m_ptrILFileInfo->m_SaveByAverage = m_ByAverage;
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

	if (m_ptrILFileInfo->m_Do != m_SaveData ||
		m_ptrILFileInfo->m_RetrFreq != DataRetrievalFreqTable[m_DataRetrFreq] ||
		m_ptrILFileInfo->m_WriteDataFreq != DataSaveFreqTable[m_SaveDataFreq] )
	{
		doResetTimer = true;
		m_ptrILFileInfo->m_Do = m_SaveData;
		m_ptrILFileInfo->m_RetrFreq = DataRetrievalFreqTable[m_DataRetrFreq];
		m_ptrILFileInfo->m_WriteDataFreq = DataSaveFreqTable[m_SaveDataFreq];
	}
		 
	CDialog::OnOK();
}
