// ProjectSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "ProjectSettingsDialog.h"
#include "ChooseLocationsDialog.h"
#include "LADA Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void AssociateFSLFile(char (*InputLocNameList)[2][30], CString filename = "");
extern CString BrowseForFolder(LPCSTR lpszTitle, UINT nFlags = 0, LPCITEMIDLIST pidlRoot = NULL, CWnd *parentWnd = NULL);
       CString GetTimeSpan(const CTimeSpan & C);
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern CFont smallRussianArial;

extern CTimeSpan DataPlotFreqTable[7];
extern int BackPointsTable[4];
extern CTimeSpan DataRetrievalFreqTable[10];
extern CTimeSpan DataSaveFreqTable[7];
extern CTimeSpan CreateFileFreqTable[3];
extern int CreateFileBySizeTable[3];


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
	m_SaveProjectFileName = _T("");
	m_VisibleSpan = _T("");
	m_curBackPointsSel = -1;
	m_curDataRetrievalSel = -1;
	m_curDataSaveSel = -1;
	m_curPlotFreqSel = -1;
	m_curSizeTimeSel = -1;
	m_SaveLocations = FALSE;
	m_nGraphsSel = -1;
	//}}AFX_DATA_INIT
	
	doc = d;
	if (AfxMessageBox("Is there a Campbell Scientific .csi or .fsl file\n which contains the input location names?",MB_YESNO|MB_ICONINFORMATION) == IDYES)
		AssociateFSLFile(doc->InputLocationNameList);
	
	CChooseLocationsDlg getNamesDlg(doc->InputLocationNameList, doc->InputLocationSaveList, &doc->nData);
	getNamesDlg.DoModal();

}


void CProjectSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProjectSettingsDlg)
	DDX_Control(pDX, IDC_TEXT10, m_SaveLocText);
	DDX_Control(pDX, IDC_N_GRAPHS, m_nGraphs);
	DDX_Control(pDX, IDC_BY_TIME, m_Time);
	DDX_Control(pDX, IDC_BY_SIZE, m_Size);
	DDX_Control(pDX, IDC_ONE_INSTANT, m_Instant);
	DDX_Control(pDX, IDC_AVERAGE, m_Average);
	DDX_Control(pDX, IDC_SIZE_TIME, m_CSizeTime);
	DDX_Control(pDX, IDC_SAVE_DATA_FREQ, m_CSaveDataFreq);
	DDX_Control(pDX, IDC_N_BACK_POINTS, m_CNBackPoints);
	DDX_Control(pDX, IDC_LOCATION_LIST, m_CLocationList);
	DDX_Control(pDX, IDC_GRAPH_PLOT_FREQ, m_CGraphPlotFreq);
	DDX_Control(pDX, IDC_DATA_RETRIEVAL_FREQ, m_CDataRetrievalFreq);
	DDX_Text(pDX, IDC_DATA_FOLDER, m_DataFolder);
	DDV_MaxChars(pDX, m_DataFolder, 255);
	DDX_Check(pDX, IDC_SAVE_FINAL_STORAGE, m_SaveFinalStorage);
	DDX_Text(pDX, IDC_SAVE_PROJECT, m_SaveProjectFileName);
	DDV_MaxChars(pDX, m_SaveProjectFileName, 30);
	DDX_Text(pDX, IDC_VISIBLE_SPAN, m_VisibleSpan);
	DDX_CBIndex(pDX, IDC_N_BACK_POINTS, m_curBackPointsSel);
	DDX_CBIndex(pDX, IDC_DATA_RETRIEVAL_FREQ, m_curDataRetrievalSel);
	DDX_CBIndex(pDX, IDC_SAVE_DATA_FREQ, m_curDataSaveSel);
	DDX_CBIndex(pDX, IDC_GRAPH_PLOT_FREQ, m_curPlotFreqSel);
	DDX_CBIndex(pDX, IDC_SIZE_TIME, m_curSizeTimeSel);
	DDX_Check(pDX, IDC_SAVE_LOCATIONS, m_SaveLocations);
	DDX_CBIndex(pDX, IDC_N_GRAPHS, m_nGraphsSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProjectSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CProjectSettingsDlg)
	ON_BN_CLICKED(IDC_BROWSE_DATA_FOLDER, OnBrowseDataFolder)
	ON_BN_CLICKED(IDC_BY_SIZE, OnBySize)
	ON_BN_CLICKED(IDC_BY_TIME, OnByTime)
	ON_BN_CLICKED(IDC_EDIT_LOCATION_LIST, OnEditLocationList)
	ON_CBN_SELCHANGE(IDC_GRAPH_PLOT_FREQ, OnSelchangeGraphPlotFreq)
	ON_CBN_SELCHANGE(IDC_N_BACK_POINTS, OnSelchangeNBackPoints)
	ON_BN_CLICKED(IDC_AVERAGE, OnAverage)
	ON_BN_CLICKED(IDC_ONE_INSTANT, OnOneInstant)
	ON_BN_CLICKED(IDC_SAVE_LOCATIONS, OnSaveLocations)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProjectSettingsDlg message handlers
extern int curLanguage;

BOOL CProjectSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	SetFont(&smallRussianArial);
	CString s;
	s.LoadString(IDS_PTITLE);
	SetWindowText(s);

	for (int i = 0; i < 14; i++)
		SetFontText(IDC_TEXT1 + i, IDS_PTEXT1 + i, this);
	for ( i = 0; i < 8; i++)
		SetFontText(IDC_EDIT_LOCATION_LIST + i, IDS_PBUTTON1 + i, this);

	m_CLocationList.ResetContent();
	for ( i = 0; i < doc->nData; i++)
	{
		m_CLocationList.AddString(doc->InputLocationNameList[i][curLanguage]);
	}
	m_DataFolder = workingDirectory;
	
	
	m_curPlotFreqSel = 3;
	m_curBackPointsSel = 1;
	m_curDataRetrievalSel = 0;
	m_curDataSaveSel = 3;
	m_curSizeTimeSel = 1;
	m_nGraphsSel = 2;
	m_SaveLocations = TRUE;
	OnByTime();
	OnAverage();
	m_CGraphPlotFreq.SetFont(&smallRussianArial);
	for (i = 0; i < 7; i++)
	{
		s.LoadString(IDS_N_DATAPLOT1 + i);
		m_CGraphPlotFreq.AddString(s);
	}
	m_CNBackPoints.SetFont(&smallRussianArial);
	for (i = 0; i < 4; i++)
	{
		s.LoadString(IDS_N_BACKPOINT1 + i);
		m_CNBackPoints.AddString(s);
	}
	m_CDataRetrievalFreq.SetFont(&smallRussianArial);
	for (i = 0; i < 10; i++)
	{
		s.LoadString(IDS_N_DATARETR1 + i);
		m_CDataRetrievalFreq.AddString(s);
	}
	m_CSaveDataFreq.SetFont(&smallRussianArial);
	for (i = 0; i < 7; i++)
	{
		s.LoadString(IDS_N_DATASAVE1 + i);
		m_CSaveDataFreq.AddString(s);
	}
	m_nGraphs.SetFont(&smallRussianArial);
	for (i = 0; i < 4; i++)
	{
		m_nGraphs.AddString(CString(char(i+'1')));
	}
	m_SaveProjectFileName = "LADA Module Config.lada";
	UpdateData(FALSE);
	OnSaveLocations();
	ShowVisibleSpan();
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
	m_DataFolder = BrowseForFolder("Select Save Folder for Data Files");
	if (m_DataFolder == "")
		m_DataFolder = workingDirectory;
	UpdateData(FALSE);
}


void CProjectSettingsDlg::OnBySize() 
{
	// TODO: Add your control notification handler code here
	m_Size.SetCheck(1);
	m_Time.SetCheck(0);
	m_CSizeTime.ResetContent();
	CString s;
	for (int i = 0; i < 3; i++){
		s.LoadString(IDS_N_FILESIZE1 +i);
		m_CSizeTime.AddString(s);
	}
	m_CSizeTime.SetCurSel(1);
	m_ByTime = FALSE;
}

void CProjectSettingsDlg::OnByTime() 
{
	// TODO: Add your control notification handler code here
	m_Size.SetCheck(0);
	m_Time.SetCheck(1);
	m_CSizeTime.ResetContent();
	CString s;
	for (int i = 0; i < 3; i++){
		s.LoadString(IDS_N_FILETIME1 +i);
		m_CSizeTime.AddString(s);
	}
	m_CSizeTime.SetCurSel(1);
	m_ByTime = TRUE;
}

void CProjectSettingsDlg::OnAverage() 
{
	// TODO: Add your control notification handler code here
	m_Average.SetCheck(1);
	m_Instant.SetCheck(0);
	m_ByAverage = TRUE;
}

void CProjectSettingsDlg::OnOneInstant() 
{
	// TODO: Add your control notification handler code here
	m_Average.SetCheck(0);
	m_Instant.SetCheck(1);
	m_ByAverage = FALSE;
}

void CProjectSettingsDlg::OnEditLocationList() 
{
	// TODO: Add your control notification handler code here
	CChooseLocationsDlg getNamesDlg(doc->InputLocationNameList, doc->InputLocationSaveList, &doc->nData);
	getNamesDlg.DoModal();
	m_CLocationList.ResetContent();
	for (int i = 0; i < doc->nData; i++)
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
	// InputLocationSaveList
	// InputLocationNameList
	// nData
	UpdateData(TRUE);
	if (doc->nData == 0){
		AfxMessageBox("At least one input location must be selected.  Please correct the error.",MB_ICONINFORMATION);
		return;	
	}
	doc->dataRetrievalFreq = DataRetrievalFreqTable[m_curDataRetrievalSel];
	doc->dataPlotFreq = DataPlotFreqTable[m_curPlotFreqSel];
	doc->dataWriteFreq = DataSaveFreqTable[m_curDataSaveSel];
	if (doc->dataPlotFreq < doc->dataRetrievalFreq)
	{
		AfxMessageBox("Data cannot be plotted more frequently than in is retrieved from CR10.  Please correct the error.",MB_ICONINFORMATION);
		return;	
	}
	if (doc->dataWriteFreq < doc->dataRetrievalFreq)
	{
		AfxMessageBox("Data cannot be saved more frequently than in is retrieved from CR10.  Please correct the error.",MB_ICONINFORMATION);
		return;
	}
	doc->nBackPoints = BackPointsTable[m_curBackPointsSel];
	doc->saveByAverage = m_ByAverage;
	doc->saveFinalStorage = m_SaveFinalStorage;
	doc->saveByTime = m_ByTime;
	doc->newFileSize = CreateFileBySizeTable[m_curSizeTimeSel];
	doc->newFileFreq = CreateFileFreqTable[m_curSizeTimeSel];
	doc->dataFolder = m_DataFolder;
	doc->projectOptionsFile = m_SaveProjectFileName;
	doc->saveLocations = m_SaveLocations;
	doc->numGraphs = 3;//m_nGraphsSel + 1;
	CDialog::OnOK();
}

void CProjectSettingsDlg::OnSaveLocations() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_CSaveDataFreq.EnableWindow(m_SaveLocations);
	m_Average.EnableWindow(m_SaveLocations);
	m_Instant.EnableWindow(m_SaveLocations);
	m_SaveLocText.EnableWindow(m_SaveLocations);
}
