// ProjectSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "ProjectSettingsDialog.h"
#include "ChooseLocationsDialog.h"
#include "LADA Control ModuleDoc.h"
#include "InputLocFileInfo.h"
#include "ILFileDisplayInfo.h"
#include "LString.h"
#include "Ladastrings.h"
#include "WetupSettingsDlg.h"


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

extern int  AssociateFile(char (*InputLocNameList)[2][30], int maxNum, CString filename = "", int wType = 0);
extern CString BrowseForFolder(LPCSTR lpszTitle, UINT nFlags = 0, LPCITEMIDLIST pidlRoot = NULL, CWnd *parentWnd = NULL);
       CString GetTimeSpan(const CTimeSpan & C);
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern BOOL TryDirectory(CString m_Directory);

extern CFont RussianArial;

extern CTimeSpan DataPlotFreqTable[7];
extern int BackPointsTable[4];
extern CTimeSpan DataRetrievalFreqTable[10];
extern CTimeSpan DataSaveFreqTable[7];
extern CTimeSpan CreateFileFreqTable[3];
extern int CreateFileBySizeTable[3];
extern LString Strings;


int PromptBox(CString BoxTitle, CString BoxPrompt, 
			  int *returnInt = NULL, CString *returnCString = NULL, 
			  CString intPrompt = "", CString cPrompt = "", 
			  int suggestion = 0, CString csuggestion = "")
{
	// create a generic CDialog box.

	return 5;
}

/////////////////////////////////////////////////////////////////////////////
// CProjectSettingsDlg dialog


CProjectSettingsDlg::CProjectSettingsDlg(CLADAControlModuleDoc *d, CWnd* pParent /*=NULL*/)
	: CDialog(CProjectSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProjectSettingsDlg)
	m_DataFolder = _T("");
	m_SaveFinalStorage = FALSE;
	m_ProjectName = _T("");
	m_VisibleSpan = _T("");
	m_curBackPointsSel = -1;
	m_curDataRetrievalSel = -1;
	m_curDataSaveSel = -1;
	m_curPlotFreqSel = -1;
	m_SaveLocations = FALSE;
	m_nGraphsSel = -1;
	m_FSGroupName = _T("");
	m_ILGroupName = _T("");
	m_curFSCreateFreq = -1;
	m_curILCreateFreq = -1;
	m_nFS = 0;
	m_nIL = 0;
	m_nILFiles = 0;
	m_wILFile = 0;
	m_DoWetup = FALSE;
	m_FileHeader = _T("");
	//}}AFX_DATA_INIT
	m_DlgInitialized = FALSE;
	m_ILFileInfo = new CInputLocFileInfo[20];
	m_ILDisplayInfo = new CILFileDisplayInfo[20];
	doc = d;
	
	//InputListType InputLocationNameList[MAX_INPUT_LOCATIONS];
	
	for (int i = 0; i < MAX_INPUT_LOCATIONS; i++){
		wsprintf(InputLocationNameList[i][ENGLISH], "%3i:[no name]", i+1);
		wsprintf(InputLocationNameList[i][RUSSIAN], "%3i:[ÍÀÇÂÀÍÈß ÍÅÒ]", i+1);
	}//YFPDFYBZ YTN
	doc->nInputLocations = 0;

	if (MessageBox(IDS_M_EXISTS_CS_FILE, NO_TITLE, MB_YESNO|MB_ICONQUESTION) == IDYES)
		AssociateFile(InputLocationNameList);
	

	CChooseLocationsDlg getNamesDlg(InputLocationNameList, InputLocationList, &doc->nInputLocations);
	getNamesDlg.DoModal();

}

CProjectSettingsDlg::~CProjectSettingsDlg()
{
	delete [] m_ILFileInfo;
	delete [] m_ILDisplayInfo;
}

void CProjectSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectSettingsDlg)
	DDX_Control(pDX, IDC_NEW_FSFILE_FREQ, m_CSaveFSFreq);
	DDX_Control(pDX, IDC_NEW_ILFILE_FREQ, m_NewILFileFreq);
	DDX_Control(pDX, IDC_NIL, m_cNIL);
	DDX_Control(pDX, IDC_CHOOSE_ILL_LIST, m_cILList);
	DDX_Control(pDX, IDC_ILGROUPNAME, m_cILGroupName);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_NILFILES, m_cnILFiles);
	DDX_Control(pDX, IDC_WILFILE, m_cwILFile);
	DDX_Control(pDX, IDC_N_GRAPHS, m_nGraphs);
	DDX_Control(pDX, IDC_ONE_INSTANT, m_Instant);
	DDX_Control(pDX, IDC_AVERAGE, m_Average);
	DDX_Control(pDX, IDC_SAVE_DATA_FREQ, m_CSaveDataFreq);
	DDX_Control(pDX, IDC_N_BACK_POINTS, m_CNBackPoints);
	DDX_Control(pDX, IDC_LOCATION_LIST, m_CLocationList);
	DDX_Control(pDX, IDC_GRAPH_PLOT_FREQ, m_CGraphPlotFreq);
	DDX_Control(pDX, IDC_DATA_RETRIEVAL_FREQ, m_CDataRetrievalFreq);
	DDX_Text(pDX, IDC_DATA_FOLDER, m_DataFolder);
	DDV_MaxChars(pDX, m_DataFolder, 255);
	DDX_Check(pDX, IDC_SAVE_FINAL_STORAGE, m_SaveFinalStorage);
	DDX_Text(pDX, IDC_SAVE_PROJECT, m_ProjectName);
	DDV_MaxChars(pDX, m_ProjectName, 30);
	DDX_Text(pDX, IDC_VISIBLE_SPAN, m_VisibleSpan);
	DDX_CBIndex(pDX, IDC_N_BACK_POINTS, m_curBackPointsSel);
	DDX_CBIndex(pDX, IDC_DATA_RETRIEVAL_FREQ, m_curDataRetrievalSel);
	DDX_CBIndex(pDX, IDC_SAVE_DATA_FREQ, m_curDataSaveSel);
	DDX_CBIndex(pDX, IDC_GRAPH_PLOT_FREQ, m_curPlotFreqSel);
	DDX_Check(pDX, IDC_SAVE_LOCATIONS, m_SaveLocations);
	DDX_CBIndex(pDX, IDC_N_GRAPHS, m_nGraphsSel);
	DDX_Text(pDX, IDC_FSGROUP_NAME, m_FSGroupName);
	DDX_Text(pDX, IDC_ILGROUPNAME, m_ILGroupName);
	DDX_CBIndex(pDX, IDC_NEW_FSFILE_FREQ, m_curFSCreateFreq);
	DDX_CBIndex(pDX, IDC_NEW_ILFILE_FREQ, m_curILCreateFreq);
	DDX_Text(pDX, IDC_NFS, m_nFS);
	DDX_Text(pDX, IDC_NIL, m_nIL);
	DDX_Text(pDX, IDC_NILFILES, m_nILFiles);
	DDV_MinMaxInt(pDX, m_nILFiles, 0, 20);
	DDX_Text(pDX, IDC_WILFILE, m_wILFile);
	DDX_Check(pDX, IDC_DOWETUP, m_DoWetup);
	DDX_Text(pDX, IDC_ARRAY_ID, m_FileHeader);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CProjectSettingsDlg)
	ON_BN_CLICKED(IDC_BROWSE_DATA_FOLDER, OnBrowseDataFolder)
	ON_BN_CLICKED(IDC_EDIT_LOCATION_LIST, OnEditLocationList)
	ON_CBN_SELCHANGE(IDC_GRAPH_PLOT_FREQ, OnSelchangeGraphPlotFreq)
	ON_CBN_SELCHANGE(IDC_N_BACK_POINTS, OnSelchangeNBackPoints)
	ON_BN_CLICKED(IDC_AVERAGE, OnAverage)
	ON_BN_CLICKED(IDC_ONE_INSTANT, OnOneInstant)
	ON_BN_CLICKED(IDC_SAVE_LOCATIONS, OnSaveLocations)
	ON_EN_CHANGE(IDC_WILFILE, OnChangeWilfile)
	ON_EN_CHANGE(IDC_NILFILES, OnChangeNilfiles)
	ON_BN_CLICKED(IDC_SAVE_FINAL_STORAGE, OnSaveFinalStorage)
	ON_BN_CLICKED(IDC_CHOOSE_FSL_LIST, OnChooseFslList)
	ON_BN_CLICKED(IDC_CHOOSE_ILL_LIST, OnChooseIllList)
	ON_BN_CLICKED(IDC_ASSOCIATEFSL, OnAssociatefsl)
	ON_BN_CLICKED(IDC_WSETTINGS, OnWsettings)
	ON_BN_CLICKED(IDC_DOWETUP, OnDowetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectSettingsDlg message handlers
extern int curLanguage;

BOOL CProjectSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	m_DlgInitialized = TRUE;
	// m_ByAverage - value set in on average
	

	m_curPlotFreqSel = 3;
	m_curBackPointsSel = 1;
	m_curDataRetrievalSel = 0;
	m_curDataSaveSel = 3;
	m_DataFolder = workingDirectory;
	m_nGraphsSel = 2;
	m_SaveLocations = FALSE;
	m_SaveFinalStorage = FALSE;
	m_curFSCreateFreq = 1;
	m_curILCreateFreq = 1;
	m_nFS = 0;
	m_nIL = 0;
	m_nILFiles = 0;
	m_wILFile = 0;
	m_Spin1.SetRange(0,0);

	m_ptrILFileInfo = &m_ILFileInfo[0];

	SetFont(&RussianArial);
	CString s;
	s.LoadString(IDS_PTITLE);
	SetWindowText(s);


	for (int i = 0; i < 21; i++)
		SetFontText(IDC_TEXT1 + i, IDS_PTEXT1 + i, this);
	
	SetFontText(IDC_EDIT_LOCATION_LIST, IDS_EDIT_LOCATION_LIST,this);
	SetFontText(IDC_SAVE_FINAL_STORAGE, IDS_SAVE_FINAL_STORAGE,this);
	SetFontText(IDC_SAVE_LOCATIONS, IDS_SAVE_LOCATIONS,this);
	SetFontText(IDC_CHOOSE_FSL_LIST, IDS_CHOOSE_FSL_LIST,this);
	SetFontText(IDC_CHOOSE_ILL_LIST, IDS_CHOOSE_ILL_LIST,this);
	SetFontText(IDC_AVERAGE, IDS_AVERAGE,this);
	SetFontText(IDC_ONE_INSTANT, IDS_ONE_INSTANT,this);
	SetFontText(IDC_BROWSE_DATA_FOLDER, IDS_BROWSE_DATA_FOLDER,this);

	m_cNIL.SetFont(&RussianArial);
	m_cnILFiles.SetFont(&RussianArial);
	GetDlgItem(IDC_NFS)->SetFont(&RussianArial);
	m_cwILFile.SetFont(&RussianArial);

	if (doc->InputLocationList){
		delete [] doc->InputLocationList;
		doc->InputLocationList = NULL;
	}
	if (doc->InputLocationNameList)
	{
		delete [] doc->InputLocationNameList;
		doc->InputLocationNameList = NULL;
	}
	
	if (doc->nInputLocations)
	{
		doc->InputLocationList = new int[doc->nInputLocations];
		doc->InputLocationNameList = new InputListType[doc->nInputLocations];
		for (int i = 0; i < doc->nInputLocations; i++)
		{
			memcpy(doc->InputLocationNameList[i], InputLocationNameList[InputLocationList[i]],sizeof(InputListType));
		}
		memcpy(doc->InputLocationList, InputLocationList, sizeof(int) * doc->nInputLocations);
	}

	m_CLocationList.ResetContent();
	for ( i = 0; i < doc->nInputLocations; i++)
	{
		m_CLocationList.AddString(doc->InputLocationNameList[i][curLanguage]);
	}
	m_CDataRetrievalFreq.SetFont(&RussianArial);
	for (i = 0; i < 10; i++)
	{
		s.LoadString(IDS_N_DATARETR1 + i);
		m_CDataRetrievalFreq.AddString(s);
	}
	m_CGraphPlotFreq.SetFont(&RussianArial);
	for (i = 0; i < 7; i++)
	{
		s.LoadString(IDS_N_DATAPLOT1 + i);
		m_CGraphPlotFreq.AddString(s);
	}
	m_CNBackPoints.SetFont(&RussianArial);
	for (i = 0; i < 4; i++)
	{
		s.LoadString(IDS_N_BACKPOINT1 + i);
		m_CNBackPoints.AddString(s);
	}
	m_CSaveDataFreq.SetFont(&RussianArial);
	for (i = 0; i < 7; i++)
	{
		s.LoadString(IDS_N_DATASAVE1 + i);
		m_CSaveDataFreq.AddString(s);
	}
	m_CSaveFSFreq.SetFont(&RussianArial);
	for(i = 0; i < 4; i++){
		s.LoadString(IDS_N_FILETIME1 + i);
		m_CSaveFSFreq.AddString(s);
	}

	m_nGraphs.SetFont(&RussianArial);
	for (i = 0; i < 4; i++)
	{
		m_nGraphs.AddString(CString(char(i+'1')));
	}

	m_NewILFileFreq.SetFont(&RussianArial);
	for(i = 0; i < 4; i++){
		s.LoadString(IDS_N_FILETIME1 + i);
		m_NewILFileFreq.AddString(s);
	}
	

	m_ProjectName = "LADA Experiment";
	UpdateData(FALSE);
	OnAverage();
	OnSaveLocations();
	OnSaveFinalStorage();
	ShowVisibleSpan();
	ShowAverageInstant();
	Reset();
	OnDowetup();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProjectSettingsDlg::ShowVisibleSpan()
{
	UpdateData(TRUE);
	CTimeSpan visibleSpan = CTimeSpan(time_t(DataPlotFreqTable[m_curPlotFreqSel].GetTotalSeconds() * BackPointsTable[m_curBackPointsSel]));
	m_VisibleSpan = GetTimeSpan(visibleSpan);
	UpdateData(FALSE);
}

CString GetTimeSpan(const CTimeSpan & C)
{
	CString Time;
	int t;
	if (t = C.GetDays()){
		if (t > 1)
			Time = C.Format("%H days ");
		else
			Time = "1 day ";
	}
	if (t = C.GetHours()){
		if (t > 1)
			Time += C.Format("%H hours ");
		else
			Time += "1 hour ";
	}
	if (t = C.GetMinutes()){
		if (t > 1)
			Time += C.Format("%M minutes ");
		else
			Time += "1 minute ";
	}
	if (t = C.GetSeconds()){
		if (t > 1)
			Time += C.Format("%S seconds");
		else
			Time += "1 second";
	}
	return Time;

}

void CProjectSettingsDlg::OnBrowseDataFolder() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_DataFolder = BrowseForFolder("Select Save Folder for Data Files");
	if (m_DataFolder == "")
		m_DataFolder = workingDirectory;
	UpdateData(FALSE);
}

void CProjectSettingsDlg::OnAverage() 
{
	// TODO: Add your control notification handler code here
	m_ByAverage = TRUE;
	ShowAverageInstant();
}

void CProjectSettingsDlg::OnOneInstant() 
{
	// TODO: Add your control notification handler code here
	m_ByAverage = FALSE;
	ShowAverageInstant();
}

void CProjectSettingsDlg::OnEditLocationList() 
{
	// TODO: Add your control notification handler code here
	CChooseLocationsDlg getNamesDlg(InputLocationNameList, InputLocationList, &doc->nInputLocations);
	getNamesDlg.DoModal();
	m_CLocationList.ResetContent();
	
	if (doc->InputLocationList){
		delete [] doc->InputLocationList;
		doc->InputLocationList = NULL;
	}
	if (doc->InputLocationNameList)
	{
		delete [] doc->InputLocationNameList;
		doc->InputLocationNameList = NULL;
	}
	
	if (doc->nInputLocations)
	{
		doc->InputLocationList = new int[doc->nInputLocations];
		doc->InputLocationNameList = new InputListType[doc->nInputLocations];
		for (int i = 0; i < doc->nInputLocations; i++)
		{
			memcpy(doc->InputLocationNameList[i], InputLocationNameList[InputLocationList[i]],sizeof(InputListType));
		}
		memcpy(doc->InputLocationList, InputLocationList, sizeof(int) * doc->nInputLocations);
	}
	
	for (int i = 0; i < doc->nInputLocations; i++)
	{
		m_CLocationList.AddString(doc->InputLocationNameList[i][curLanguage]);
	}
}

void CProjectSettingsDlg::OnSelchangeGraphPlotFreq() 
{
	// TODO: Add your control notification handler code here
	ShowVisibleSpan();
}

void CProjectSettingsDlg::OnSelchangeNBackPoints() 
{
	// TODO: Add your control notification handler code here
	if (m_curBackPointsSel == 4){
		// choose custom number of back points

	}
	ShowVisibleSpan();
}


void CProjectSettingsDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	// what's taken care of already?
	// InputLocationList
	// InputLocationNameList
	// nInputLocations
	UpdateData(TRUE);

	if (!TryDirectory(m_DataFolder))
		return;

	if (doc->nInputLocations == 0){
		MessageBox(IDS_M_MUST_SELECT_ONE_LOCATION, NO_TITLE, MB_ICONINFORMATION);
		return;	
	}

	doc->saveFinalStorage = m_SaveFinalStorage;
	//doc->saveLocations = m_SaveLocations;
	
	if (m_SaveLocations)
	{
		doc->nILFiles = m_nILFiles;
		OnChangeWilfile(); // this will save the data currently displayed...
		
		if (doc->m_ILData)
			delete [] doc->m_ILData;
		doc->m_ILData = new CInputLocFileInfo[m_nILFiles];

		char ErrMessage[100];
		BOOL Error = FALSE;
		for (int i = 0; i < m_nILFiles; i++)
		{
			if (m_ILFileInfo[i].m_Name.GetLength() == 0) // a name has not been entered
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Input Location File %i has no name", m_wILFile);
				m_cILGroupName.SetFocus();			
			}
			else if (m_ILFileInfo[i].m_nLocations == 0)
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Input Location File %i has no Input Locations", m_wILFile);
				GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetFocus();
			}
			else if (m_ILFileInfo[i].m_WriteDataFreq < m_ILFileInfo[i].m_RetrFreq )
			{
				Error = TRUE;
				strcpy(ErrMessage,"Data cannot be written more frequently than it is saved.");
				m_CSaveDataFreq.SetFocus();
			}
			else if (m_ILFileInfo[i].m_NewFileFreq < m_ILFileInfo[i].m_WriteDataFreq )
			{
				Error = TRUE;
				strcpy(ErrMessage,"Data cannot be written more frequently than it is saved.");
			}
			
			if (Error)
			{
				m_wILFile = i + 1;
				UpdateData(FALSE);
				OnChangeWilfile();
				MessageBox(CString(ErrMessage),Strings.get(IDS_ERROR),MB_ICONINFORMATION);
				return;
			}

			doc->m_ILData[i] = m_ILFileInfo[i];
		}
	}
	else
		doc->nILFiles = 0;

	if (m_SaveFinalStorage)
	{
		char ErrMessage[100];
		BOOL Error = FALSE;
		if (m_FSGroupName.GetLength() == 0) // a name has not been entered
		{
			Error = TRUE;
			wsprintf(ErrMessage,"Final Storage has no name");
			GetDlgItem(IDC_FSGROUP_NAME)->SetFocus();		
		}
		else if (doc->m_FSInfo.m_nLocations == 0)
		{
			Error = TRUE;
			wsprintf(ErrMessage,"Final Storage has no named Input Locations");
			GetDlgItem(IDC_CHOOSE_FSL_LIST)->SetFocus();
		}
			
		if (Error)
		{
			MessageBox(CString(ErrMessage),Strings.get(IDS_ERROR),MB_ICONINFORMATION);
			return;
		}

		doc->m_FSInfo.m_Name = m_FSGroupName;
		doc->m_FSInfo.m_WriteDataFreq = doc->m_FSInfo.m_NewFileFreq = CreateFileFreqTable[m_curFSCreateFreq];
		
		for (int i = 0; i < m_FileHeader.GetLength(); i++)
		{
			if (m_FileHeader[i] == ',')
				m_FileHeader.SetAt(i,'\t');
		}
		doc->m_FSInfo.m_FileName = m_FileHeader;

	}
	doc->m_DoWetup = m_DoWetup;
	
	doc->dataPlotFreq = DataPlotFreqTable[m_curPlotFreqSel];
	doc->nBackPoints = BackPointsTable[m_curBackPointsSel];
	doc->dataFolder = m_DataFolder;
	doc->projectName = m_ProjectName;
	doc->numGraphs = 3;//m_nGraphsSel + 1;

	CDialog::OnOK();
}


void CProjectSettingsDlg::OnChangeWilfile() 
{
		// TODO: Add your control notification handler code here
	if (m_DlgInitialized && m_cwILFile.GetWindowTextLength() > 0)
	{
		int pILFile = m_wILFile;
		UpdateData(TRUE);
		m_ILDisplayInfo[pILFile - 1].m_curDataRetrievalSel = m_curDataRetrievalSel;
		m_ILDisplayInfo[pILFile - 1].m_curDataSaveSel = m_curDataSaveSel;
		m_ILDisplayInfo[pILFile - 1].m_curILCreateFreq = m_curILCreateFreq;
		
		m_ptrILFileInfo->m_RetrFreq = DataRetrievalFreqTable[m_curDataRetrievalSel];
		m_ptrILFileInfo->m_WriteDataFreq = DataSaveFreqTable[m_curDataSaveSel];
		m_ptrILFileInfo->m_NewFileFreq = CreateFileFreqTable[m_curILCreateFreq];
		m_ptrILFileInfo->m_SaveByAverage = m_ByAverage;
		m_ptrILFileInfo->m_Name = m_ILGroupName;
		
		m_ptrILFileInfo = &m_ILFileInfo[m_wILFile - 1];
		m_curDataRetrievalSel = m_ILDisplayInfo[m_wILFile - 1].m_curDataRetrievalSel;
		m_curDataSaveSel = m_ILDisplayInfo[m_wILFile - 1].m_curDataSaveSel;
		m_curILCreateFreq = m_ILDisplayInfo[m_wILFile - 1].m_curILCreateFreq;
		m_ByAverage = m_ptrILFileInfo->m_SaveByAverage;
		m_ILGroupName = m_ptrILFileInfo->m_Name;

		UpdateData(FALSE);
		ShowAverageInstant();
		// take care of locations now...
	}
}


void CProjectSettingsDlg::OnSaveLocations() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_TEXT9)->EnableWindow(m_SaveLocations);
	m_cnILFiles.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT14)->EnableWindow(m_SaveLocations);
	m_cwILFile.EnableWindow(m_SaveLocations);
	m_Spin1.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT15)->EnableWindow(m_SaveLocations);
	m_cILGroupName.EnableWindow(m_SaveLocations);
	m_cILList.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT16)->EnableWindow(m_SaveLocations);
	m_cNIL.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT17)->EnableWindow(m_SaveLocations);
	m_CDataRetrievalFreq.EnableWindow(m_SaveLocations);
	m_Average.EnableWindow(m_SaveLocations);
	m_Instant.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT18)->EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT19)->EnableWindow(m_SaveLocations);
	m_CSaveDataFreq.EnableWindow(m_SaveLocations);
	m_NewILFileFreq.EnableWindow(m_SaveLocations);
	if (m_SaveLocations)
	{
		if (m_nILFiles == 0){
			m_nILFiles = 1;
			m_wILFile = 1;
		}
		m_Spin1.SetRange(1,m_nILFiles);

		UpdateData(FALSE);
	}
}

void CProjectSettingsDlg::OnSaveFinalStorage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	GetDlgItem(IDC_TEXT10)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT11)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_FSGROUP_NAME)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_CHOOSE_FSL_LIST)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT12)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_NFS)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT13)->EnableWindow(m_SaveFinalStorage);
	m_CSaveFSFreq.EnableWindow(m_SaveFinalStorage);
	
}


void CProjectSettingsDlg::OnChangeNilfiles() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_cnILFiles.GetWindowTextLength() > 0)
	{
		UpdateData(TRUE);
		if (m_nILFiles > 20){
			m_nILFiles = 20;
			UpdateData(FALSE);
		}
		m_Spin1.EnableWindow(m_nILFiles > 1);
		if (m_nILFiles > 0)
		{
			if (m_nILFiles < m_wILFile){
				m_wILFile = m_nILFiles;
				UpdateData(FALSE);
				OnChangeWilfile();
			}
			m_Spin1.SetRange(1,m_nILFiles);
		}
		else
		{
			m_SaveLocations = FALSE;
			UpdateData(FALSE);
			OnSaveLocations();
		}
	}
}


void CProjectSettingsDlg::OnChooseFslList() 
{
	// TODO: Add your control notification handler code here
	if (doc->nInputLocations > 0)
	{
		UpdateData(TRUE);
		int nLocs = doc->m_FSInfo.m_nLocations;
		int * Locs = new int[doc->nInputLocations];
		
		if (doc->m_FSInfo.m_Locations)
			memcpy(Locs,doc->m_FSInfo.m_Locations, sizeof(int) * doc->m_FSInfo.m_nLocations);

		CChooseLocationsDlg getNamesDlg(doc->InputLocationNameList, Locs, &nLocs, doc->nInputLocations);
		
		if (getNamesDlg.DoModal() == IDOK){
			doc->m_FSInfo.SetListInfo(nLocs, Locs);
			m_nFS = nLocs;
			UpdateData(FALSE);
		}
		delete [] Locs;
	}
	else
		MessageBox(IDS_M_EDIT_LIST_FIRST, IDS_ERROR, MB_OK);
}

void CProjectSettingsDlg::OnChooseIllList() 
{
	// TODO: Add your control notification handler code here
	if (doc->nInputLocations > 0)
	{
		UpdateData(TRUE);
		int nLocs = m_ptrILFileInfo->m_nLocations;
		int * Locs = new int[doc->nInputLocations];
		
		memcpy(Locs, m_ptrILFileInfo->m_Locations, sizeof(int) * m_ptrILFileInfo->m_nLocations);
		
		CChooseLocationsDlg getNamesDlg(doc->InputLocationNameList, Locs, &nLocs, doc->nInputLocations);
		
		if (getNamesDlg.DoModal() == IDOK){
			m_ptrILFileInfo->SetListInfo(nLocs, Locs);
			m_nIL = nLocs;
			UpdateData(FALSE);
		}
		delete [] Locs;
	}
	else
		MessageBox(IDS_M_EDIT_LIST_FIRST, IDS_ERROR, MB_OK);
}

void CProjectSettingsDlg::ShowAverageInstant()
{
	m_Average.SetCheck(m_ByAverage);
	m_Instant.SetCheck(!m_ByAverage);
}

void CProjectSettingsDlg::Reset()
{
	SetWindowText(Strings.get(IDS_C0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_C1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_C2));
	GetDlgItem(IDC_EDIT_LOCATION_LIST)->SetWindowText(Strings.get(IDS_C3));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_C4));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_C5));
	GetDlgItem(IDC_TEXT5)->SetWindowText(Strings.get(IDS_C6));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_C7));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_C8));
	GetDlgItem(IDC_TEXT8)->SetWindowText(Strings.get(IDS_C9));
	GetDlgItem(IDC_SAVE_FINAL_STORAGE)->SetWindowText(Strings.get(IDS_C10));
	GetDlgItem(IDC_SAVE_LOCATIONS)->SetWindowText(Strings.get(IDS_C11));
	GetDlgItem(IDC_TEXT9)->SetWindowText(Strings.get(IDS_C12));
	GetDlgItem(IDC_TEXT10)->SetWindowText(Strings.get(IDS_C13));
	GetDlgItem(IDC_TEXT11)->SetWindowText(Strings.get(IDS_C14));
	GetDlgItem(IDC_CHOOSE_FSL_LIST)->SetWindowText(Strings.get(IDS_CHOOSE));
	GetDlgItem(IDC_TEXT12)->SetWindowText(Strings.get(IDS_NUMBER));
	GetDlgItem(IDC_TEXT13)->SetWindowText(Strings.get(IDS_C15));
	GetDlgItem(IDC_TEXT20)->SetWindowText(Strings.get(IDS_C16));
	GetDlgItem(IDC_BROWSE_DATA_FOLDER)->SetWindowText(Strings.get(IDS_BROWSE));
	GetDlgItem(IDC_TEXT21)->SetWindowText(Strings.get(IDS_C17));
	GetDlgItem(IDC_TEXT14)->SetWindowText(Strings.get(IDS_C18));
	GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetWindowText(Strings.get(IDS_CHOOSE));
	GetDlgItem(IDC_TEXT15)->SetWindowText(Strings.get(IDS_C19));
	GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_NUMBER));
	GetDlgItem(IDC_TEXT17)->SetWindowText(Strings.get(IDS_C20));
	GetDlgItem(IDC_TEXT18)->SetWindowText(Strings.get(IDS_C21));
	GetDlgItem(IDC_AVERAGE)->SetWindowText(Strings.get(IDS_C22));
	GetDlgItem(IDC_ONE_INSTANT)->SetWindowText(Strings.get(IDS_C23));
	GetDlgItem(IDC_TEXT19)->SetWindowText(Strings.get(IDS_C24));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
}

void CProjectSettingsDlg::OnAssociatefsl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (doc->nInputLocations == 0){
		MessageBox(IDS_M_SELECT_LOCATIONS_FIRST);
		return;
	}

	InputListType FSLabels[256];
	unsigned int lFSLabel;
	bool matchFound = false;

	int nLocs = 0;
	int * Locs = new int[doc->nInputLocations];
		
	int maxLoc = AssociateFile(FSLabels,CString(""),1);
	for (int i = 0; i < maxLoc; i++)
	{
		lFSLabel = strlen(FSLabels[i][curLanguage]);
		matchFound = false;
		for (int j = 0; j < doc->nInputLocations && !matchFound; j++)
		{
			if (strlen(&doc->InputLocationNameList[j][curLanguage][4]) == lFSLabel &&
				strcmp(&doc->InputLocationNameList[j][curLanguage][4], FSLabels[i][curLanguage]) == 0)
			{
				matchFound = true;
				Locs[i] = j;
			}
		}
		if (!matchFound)
		{
			char message[100];
			wsprintf(message,"%i",FSLabels[i][curLanguage]);
			MessageBox(Strings.get(IDS_M_UNSUCCESSFUL_FILE_IMPORT) + CString(message), CString(""), MB_ICONWARNING);
			i = 0; 
			break;
			/*
			wsprintf(message,"No match was found for final storage label %s.\n  Do you wish to create a new input location?",FSLabels[i][curLanguage]);
			DWORD result = MessageBox(message,NULL,MB_YESNOCANCEL);
			if (result == IDYES)
			{

			}
			else if (result == IDNO)
			{
				//wsprintf(message,"No match was found for final storage label %s.\n  Do you wish to create a new input location?",FSLabels[i][curLanguage]);
				result = MessageBox("Would you like to select an input location?",NULL,MB_YESNOCANCEL);
				if (result == IDYES)
				{

				}
				else
				{

				}
			}
			else if (result == IDCANCEL)
			{

			}*/
		}
	}

	doc->m_FSInfo.SetListInfo(i, Locs);
	m_nFS = i;
	UpdateData(FALSE);
	
	delete [] Locs;

	UpdateData(FALSE);
}

void CProjectSettingsDlg::OnWsettings() 
{
	// TODO: Add your control notification handler code here
	CWetupSettingsDlg wDlg(doc);
	wDlg.DoModal();
}

void CProjectSettingsDlg::OnDowetup() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDC_WSETTINGS)->EnableWindow(m_DoWetup);
}
