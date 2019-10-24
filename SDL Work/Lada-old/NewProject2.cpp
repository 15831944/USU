// This is Version 1.0 PLEASE DOCUMENT CHANGES
// NewProject2.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "NewProject2.h"
#include "InputLocFileInfo.h"
#include "ILFileDisplayInfo.h"
#include "LADA Control ModuleDoc.h"
#include "LString.h"
#include "Ladastrings.h"
#include "ChooseLocationsDialog.h"

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

extern int  AssociateFile(char (*InputLocNameList)[2][30], int maxNum, CString filename = "", int wType = 0, int ArrayID = 0);
extern CString BrowseForFolder(LPCSTR lpszTitle, UINT nFlags = 0, LPCITEMIDLIST pidlRoot = NULL, CWnd *parentWnd = NULL);
       CString GetTimeSpan(const CTimeSpan & C, int DisplayFields = 4);
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);
extern BOOL TryDirectory(CString m_Directory);

extern CFont RussianArial;

extern CTimeSpan DataRetrievalFreqTable[10];
extern CTimeSpan DataSaveFreqTable[7];
extern CTimeSpan CreateFileFreqTable[3];
extern int CreateFileBySizeTable[3];
extern LString Strings;
extern int curLanguage;

/////////////////////////////////////////////////////////////////////////////
// CNewProject2 dialog


CNewProject2::CNewProject2(CLADAControlModuleDoc * pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CNewProject2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProject2)
	m_DataFolder = _T("");
	m_curDataRetrievalSel = -1;
	m_FSGroupName = _T("");
	m_ILGroupName = _T("");
	m_curFSCreateFreq = -1;
	m_curILCreateFreq = -1;
	m_nFS = 0;
	m_nIL = 0;
	m_nILFiles = 0;
	m_curDataSaveSel = -1;
	m_SaveFinalStorage = FALSE;
	m_SaveLocations = FALSE;
	m_wILFile = 0;
	m_ArrayID = 0;
	m_wFSFile = 0;
	m_wFSFreq = -1;
	m_nFSFiles = 0;
	//}}AFX_DATA_INIT

	doc = pDoc;
	m_ILFileInfo = new CInputLocFileInfo[20];
	m_ILDisplayInfo = new CILFileDisplayInfo[20];

	m_DlgInitialized = FALSE;
}

CNewProject2::~CNewProject2()
{
	delete [] m_ILFileInfo;
	delete [] m_ILDisplayInfo;
}

void CNewProject2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProject2)
	DDX_Control(pDX, IDC_N_FSFILES, m_cnFSFiles);
	DDX_Control(pDX, IDC_SPIN2, m_Spin2);
	DDX_Control(pDX, IDC_FS_FREQUENCY, m_cFSFrequency);
	DDX_Control(pDX, IDC_WFSFILE, m_cwFSFile);
	DDX_Control(pDX, IDC_WILFILE, m_cwILFile);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_SAVE_DATA_FREQ, m_CSaveDataFreq);
	DDX_Control(pDX, IDC_ONE_INSTANT, m_Instant);
	DDX_Control(pDX, IDC_NILFILES, m_cnILFiles);
	DDX_Control(pDX, IDC_NIL, m_cNIL);
	DDX_Control(pDX, IDC_NEW_ILFILE_FREQ, m_NewILFileFreq);
	DDX_Control(pDX, IDC_NEW_FSFILE_FREQ, m_CSaveFSFreq);
	DDX_Control(pDX, IDC_ILGROUPNAME, m_cILGroupName);
	DDX_Control(pDX, IDC_DATA_RETRIEVAL_FREQ, m_CDataRetrievalFreq);
	DDX_Control(pDX, IDC_CHOOSE_ILL_LIST, m_cILList);
	DDX_Control(pDX, IDC_AVERAGE, m_Average);
	DDX_Text(pDX, IDC_DATA_FOLDER, m_DataFolder);
	DDX_CBIndex(pDX, IDC_DATA_RETRIEVAL_FREQ, m_curDataRetrievalSel);
	DDX_Text(pDX, IDC_FSGROUP_NAME, m_FSGroupName);
	DDX_Text(pDX, IDC_ILGROUPNAME, m_ILGroupName);
	DDX_CBIndex(pDX, IDC_NEW_FSFILE_FREQ, m_curFSCreateFreq);
	DDX_CBIndex(pDX, IDC_NEW_ILFILE_FREQ, m_curILCreateFreq);
	DDX_Text(pDX, IDC_NFS, m_nFS);
	DDX_Text(pDX, IDC_NIL, m_nIL);
	DDX_Text(pDX, IDC_NILFILES, m_nILFiles);
	DDX_CBIndex(pDX, IDC_SAVE_DATA_FREQ, m_curDataSaveSel);
	DDX_Check(pDX, IDC_SAVE_FINAL_STORAGE, m_SaveFinalStorage);
	DDX_Check(pDX, IDC_SAVE_LOCATIONS, m_SaveLocations);
	DDX_Text(pDX, IDC_WILFILE, m_wILFile);
	DDX_Text(pDX, IDC_ARRAY_ID, m_ArrayID);
	DDX_Text(pDX, IDC_WFSFILE, m_wFSFile);
	DDX_CBIndex(pDX, IDC_FS_FREQUENCY, m_wFSFreq);
	DDX_Text(pDX, IDC_N_FSFILES, m_nFSFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProject2, CDialog)
	//{{AFX_MSG_MAP(CNewProject2)
	ON_BN_CLICKED(IDC_FINISH, OnFinish)
	ON_BN_CLICKED(IDC_ONE_INSTANT, OnOneInstant)
	ON_BN_CLICKED(IDC_SAVE_FINAL_STORAGE, OnSaveFinalStorage)
	ON_BN_CLICKED(IDC_SAVE_LOCATIONS, OnSaveLocations)
	ON_BN_CLICKED(IDC_ASSOCIATEFSL, OnAssociatefsl)
	ON_BN_CLICKED(IDC_AVERAGE, OnAverage)
	ON_BN_CLICKED(IDC_BROWSE_DATA_FOLDER, OnBrowseDataFolder)
	ON_EN_CHANGE(IDC_NILFILES, OnChangeNilfiles)
	ON_EN_CHANGE(IDC_WILFILE, OnChangeWilfile)
	ON_BN_CLICKED(IDC_CHOOSE_ILL_LIST, OnChooseIllList)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_EN_CHANGE(IDC_WFSFILE, OnChangeWfsfile)
	ON_EN_CHANGE(IDC_N_FSFILES, OnChangeNFsfiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewProject2 message handlers

void CNewProject2::OnFinish() 
{
	// TODO: Add your control notification handler code here
	if (GetParameters())
		CDialog::OnOK();
}

void CNewProject2::OnOneInstant() 
{
	// TODO: Add your control notification handler code here
	m_ByAverage = FALSE;
	ShowAverageInstant();
}

void CNewProject2::OnSaveFinalStorage() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_TEXT6)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT8)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT4)->EnableWindow(m_SaveFinalStorage); 

	GetDlgItem(IDC_TEXT5)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT7)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT2)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_TEXT3)->EnableWindow(m_SaveFinalStorage);

	GetDlgItem(IDC_TEXT9)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_FSGROUP_NAME)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_N_FSFILES)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_SPIN2)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_FS_FREQUENCY)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_NFS)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_WFSFILE)->EnableWindow(m_SaveFinalStorage);
	m_CSaveFSFreq.EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_ASSOCIATEFSL)->EnableWindow(m_SaveFinalStorage);
	GetDlgItem(IDC_ARRAY_ID)->EnableWindow(m_SaveFinalStorage);
	if (m_SaveFinalStorage)
	{
		if (m_nFSFiles == 0){
			m_nFSFiles = 1;
			m_wFSFile = 1;
		}
		m_Spin2.SetRange(1,m_nFSFiles);

		UpdateData(FALSE);
	}
	
}

void CNewProject2::OnSaveLocations() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_TEXT13)->EnableWindow(m_SaveLocations);
	
	GetDlgItem(IDC_TEXT12)->EnableWindow(m_SaveLocations);
	
	
	m_cnILFiles.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT14)->EnableWindow(m_SaveLocations);
	m_cwILFile.EnableWindow(m_SaveLocations);
	m_Spin1.EnableWindow(m_SaveLocations);
	
	m_cILGroupName.EnableWindow(m_SaveLocations);
	m_cILList.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT16)->EnableWindow(m_SaveLocations);
	m_cNIL.EnableWindow(m_SaveLocations);
	m_CDataRetrievalFreq.EnableWindow(m_SaveLocations);
	m_Average.EnableWindow(m_SaveLocations);
	m_Instant.EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT15)->EnableWindow(m_SaveLocations);
	GetDlgItem(IDC_TEXT17)->EnableWindow(m_SaveLocations);
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

void CNewProject2::OnAssociatefsl() 
{
	UpdateData(TRUE);
	m_ptrFSFileInfo->m_ArrayID = 0; // in case OnChangeWfsfile is not able to update the
	 // array ID, the AssociateFSL function will not be called
	OnChangeWfsfile();
	if (m_ptrFSFileInfo->m_ArrayID == 0)
	{
		MessageBox(IDS_M_INVALID_ARRAY_ID);
		SetStrings();
		GetDlgItem(IDC_ARRAY_ID)->SetFocus();
		return;
	}
	CWaitCursor wCursor;

	InputListType FSLabels[256];
	
	m_nFS = m_ptrFSFileInfo->m_nDataItems = AssociateFile(FSLabels,256,CString(""),1,m_ptrFSFileInfo->m_ArrayID);

	if (m_ptrFSFileInfo->m_DataNames)
		delete [] m_ptrFSFileInfo->m_DataNames;
	m_ptrFSFileInfo->m_DataNames = new CString[m_nFS];

	for (int i = 0; i < m_ptrFSFileInfo->m_nDataItems; i++)
	{
		m_ptrFSFileInfo->m_DataNames[i] = FSLabels[i][curLanguage];		
	}
	UpdateData(FALSE);
}

void CNewProject2::OnAverage() 
{
	// TODO: Add your control notification handler code here
	m_ByAverage = TRUE;
	ShowAverageInstant();
}

void CNewProject2::OnBrowseDataFolder() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_DataFolder = BrowseForFolder("Select Save Folder for Data Files");
	if (m_DataFolder == "")
		m_DataFolder = workingDirectory;
	UpdateData(FALSE);
}

void CNewProject2::OnChangeWilfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
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

void CNewProject2::OnChangeWfsfile() 
{
	if (m_DlgInitialized && m_cwFSFile.GetWindowTextLength() > 0)
	{
		
		UpdateData(TRUE);
		
		m_ptrFSFileInfo->m_ArchiveName = m_FSGroupName;
		m_ptrFSFileInfo->m_ArrayID = m_ArrayID;
		m_ptrFSFileInfo->m_wFreqSel = m_wFSFreq;

		// nDataItems & nData names should be taken care of in the import fsl function
		
		m_ptrFSFileInfo = &m_FSOutputTable[m_wFSFile - 1];

		m_FSGroupName = m_ptrFSFileInfo->m_ArchiveName;
		m_ArrayID = m_ptrFSFileInfo->m_ArrayID;
		m_wFSFreq = m_ptrFSFileInfo->m_wFreqSel;
		m_nFS = m_ptrFSFileInfo->m_nDataItems;

		UpdateData(FALSE);
		// load names...
		//ShowFSDataNames();
	}
}

/*
void CNewProject2::OnChooseFslList() 
{
	// TODO: Add your control notification handler code here
	if (doc->nInputLocations > 0)
	{
		UpdateData(TRUE);
		int nLocs = doc->m_FSCollectionParam.m_nLocations;
		int * Locs = new int[doc->nInputLocations];
		
		if (doc->m_FSCollectionParam.m_Locations)
			memcpy(Locs,doc->m_FSCollectionParam.m_Locations, sizeof(int) * doc->m_FSCollectionParam.m_nLocations);

		CChooseLocationsDlg getNamesDlg(doc->InputLocationNameList, Locs, &nLocs, doc->nInputLocations);
		
		if (getNamesDlg.DoModal() == IDOK){
			doc->m_FSCollectionParam.SetListInfo(nLocs, Locs);
			m_nFS = nLocs;
			UpdateData(FALSE);
		}
		SetStrings();
		delete [] Locs;
	}
	else
	{
		MessageBox(IDS_M_EDIT_LIST_FIRST, IDS_ERROR, MB_OK);
		SetStrings();
	}

}
*/

void CNewProject2::OnChooseIllList() 
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
		SetStrings();
		delete [] Locs;
	}
	else
	{
		MessageBox(IDS_M_EDIT_LIST_FIRST, IDS_ERROR, MB_OK);
		SetStrings();
	}

}

BOOL CNewProject2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_DlgInitialized = TRUE;
	
	SetFont(&RussianArial);
	for (int i = 0; i < 17; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetFont(&RussianArial);

	GetDlgItem(IDC_SAVE_FINAL_STORAGE)->SetFont(&RussianArial);
	GetDlgItem(IDC_SAVE_LOCATIONS)->SetFont(&RussianArial);
	GetDlgItem(IDC_ASSOCIATEFSL)->SetFont(&RussianArial);
	GetDlgItem(IDC_BROWSE_DATA_FOLDER)->SetFont(&RussianArial);
	GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetFont(&RussianArial);
	GetDlgItem(IDC_BACK)->SetFont(&RussianArial);
	GetDlgItem(IDC_FINISH)->SetFont(&RussianArial);
	// CONTROLS W/ NO TEXT SET INITIALLY	
	GetDlgItem(IDC_NIL)->SetFont(&RussianArial);
	GetDlgItem(IDC_NILFILES)->SetFont(&RussianArial);
	GetDlgItem(IDC_NFS)->SetFont(&RussianArial);
	GetDlgItem(IDC_WILFILE)->SetFont(&RussianArial);
	GetDlgItem(IDC_DATA_FOLDER)->SetFont(&RussianArial);
	GetDlgItem(IDC_DATA_RETRIEVAL_FREQ)->SetFont(&RussianArial);
	GetDlgItem(IDC_SAVE_DATA_FREQ)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW_FSFILE_FREQ)->SetFont(&RussianArial);
	GetDlgItem(IDC_NEW_ILFILE_FREQ)->SetFont(&RussianArial);
	GetDlgItem(IDC_FSGROUP_NAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_ARRAY_ID)->SetFont(&RussianArial);
	GetDlgItem(IDC_ILGROUPNAME)->SetFont(&RussianArial);
	GetDlgItem(IDC_AVERAGE)->SetFont(&RussianArial);
	GetDlgItem(IDC_ONE_INSTANT)->SetFont(&RussianArial);
	GetDlgItem(IDC_FS_FREQUENCY)->SetFont(&RussianArial);
	GetDlgItem(IDC_N_FSFILES)->SetFont(&RussianArial);
		
	m_nFSFiles = doc->nFSFiles;
	m_nILFiles = doc->nILFiles;
	if (m_nILFiles)
		m_SaveLocations = TRUE;
	else
		m_SaveLocations = FALSE;
	
	if (m_nFSFiles)
		m_SaveFinalStorage = TRUE;
	else
		m_SaveFinalStorage = FALSE;

	m_FSGroupName = doc->m_FSCollectionParam.m_Name;
	m_nFS = doc->m_FSCollectionParam.m_nLocations;
	
	m_curFSCreateFreq = 0;
	for (i = 0; i < 3; i++)
	{
		if (CreateFileFreqTable[i] == doc->m_FSCollectionParam.m_WriteDataFreq )
		{
			m_curFSCreateFreq = i;
			break;
		}
	}

	m_DataFolder = doc->dataFolder;
	m_wILFile = 1;
	m_ptrILFileInfo = &m_ILFileInfo[m_wILFile-1];
	m_wFSFile = 1;
	m_ptrFSFileInfo = &m_FSOutputTable[m_wFSFile-1];
	m_wFSFreq = m_ptrFSFileInfo->m_wFreqSel;
	m_nFS = m_ptrFSFileInfo->m_nDataItems;
	m_ILGroupName = m_ptrILFileInfo->m_Name;
	m_nIL = m_ptrILFileInfo->m_nLocations;
	
	m_curDataRetrievalSel = 0;
	for (i = 0; i < 10; i++)
	{
		if (DataRetrievalFreqTable[i] == m_ptrILFileInfo->m_RetrFreq)
		{
			m_curDataRetrievalSel = i;
			break;
		}
	}
	m_curDataSaveSel = 0;
	for (i = 0; i < 7; i++)
	{
		if (DataSaveFreqTable[i] == m_ptrILFileInfo->m_WriteDataFreq)
		{
			m_curDataSaveSel = i;
			break;
		}
	}
	m_ByAverage = m_ptrILFileInfo->m_SaveByAverage;
	m_curILCreateFreq = 0;
	for (i = 0; i < 3; i++)
	{
		if (CreateFileFreqTable[i] == m_ptrILFileInfo->m_NewFileFreq)
		{
			m_curILCreateFreq = i;
			break;
		}
	}
	m_Spin1.SetRange(1,m_nILFiles);

	SetStrings(FALSE);

	ShowAverageInstant();
	OnSaveLocations();
	OnSaveFinalStorage();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewProject2::OnBack() 
{
	// TODO: Add your control notification handler code here
	if (GetParameters())
	{
		m_DlgInitialized = FALSE;
		EndDialog(IDABORT);
	}
}

void CNewProject2::ShowAverageInstant()
{
	m_Average.SetCheck(m_ByAverage);
	m_Instant.SetCheck(!m_ByAverage);

	if (m_ByAverage)
	{
		GetDlgItem(IDC_TEXT15)->ShowWindow(SW_SHOW);
		m_CDataRetrievalFreq.EnableWindow(TRUE);
		m_CDataRetrievalFreq.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_W16));
	}
	else // SAVE INSTANT
	{
		GetDlgItem(IDC_TEXT15)->ShowWindow(SW_HIDE);
		m_CDataRetrievalFreq.EnableWindow(FALSE);
		m_CDataRetrievalFreq.ShowWindow(SW_HIDE);
		GetDlgItem(IDC_TEXT16)->SetWindowText(Strings.get(IDS_W27));
	}
}

BOOL CNewProject2::GetParameters()
{
	UpdateData(TRUE);
	// like OnOK
	if (!TryDirectory(m_DataFolder))
		return FALSE;
	//doc->saveFinalStorage = m_SaveFinalStorage;
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
			// If the user has chosen the save data at one instant, then
			// frequency of retrive data must match frequency to write data
			if (m_ILFileInfo[i].m_SaveByAverage == FALSE)
				m_ILFileInfo[i].m_RetrFreq = m_ILFileInfo[i].m_WriteDataFreq;
			
			if (m_ILFileInfo[i].m_Name.GetLength() == 0) // a name has not been entered
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Input Location File %i has no name", i+1);
				m_cILGroupName.SetFocus();			
			}
			else if (m_ILFileInfo[i].m_nLocations == 0)
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Input Location File %i has no Input Locations", i+1);
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
				SetStrings();
				return FALSE;
			}

			doc->m_ILData[i] = m_ILFileInfo[i];
		}
	}
	else
		doc->nILFiles = 0;

	if (m_SaveFinalStorage)
	{
		doc->nFSFiles = m_nFSFiles;
		OnChangeWfsfile(); // this will save the data currently displayed...
		
		if (doc->m_FSOutputTable)
			delete [] doc->m_FSOutputTable;
		doc->m_FSOutputTable = new CFSInfo[m_nFSFiles];

		
		char ErrMessage[100];
		BOOL Error = FALSE;
		
		for (int i = 0; i < m_nFSFiles; i++)
		{
			if (m_FSOutputTable[i].m_ArchiveName.GetLength() == 0) // a name has not been entered
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Final Storage %i has no name", i+1);
				GetDlgItem(IDC_FSGROUP_NAME)->SetFocus();		
			}
			else if (m_FSOutputTable[i].m_ArrayID == 0)
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Invalid Array ID");
				GetDlgItem(IDC_ARRAY_ID)->SetFocus();
			}
			else if (m_FSOutputTable[i].m_nDataItems == 0)
			{
				Error = TRUE;
				wsprintf(ErrMessage,"Final Storage has %i no data names", i+1);
				GetDlgItem(IDC_ASSOCIATEFSL)->SetFocus();
			}
			
				
			if (Error)
			{
				MessageBox(CString(ErrMessage),Strings.get(IDS_ERROR),MB_ICONINFORMATION);
				SetStrings();
				return FALSE;
			}
			doc->m_FSOutputTable[i] = m_FSOutputTable[i];
		}
		doc->m_FSCollectionParam.m_Name = m_FSGroupName;
		doc->m_FSCollectionParam.m_WriteDataFreq = doc->m_FSCollectionParam.m_NewFileFreq = CreateFileFreqTable[m_curFSCreateFreq];
		
		//for (int i = 0; i < m_FileHeader.GetLength(); i++)
		//{
		//	if (m_FileHeader[i] == ',')
		//		m_FileHeader.SetAt(i,'\t');
		//}
		//doc->m_FSCollectionParam.m_FileName = m_FileHeader;
	}
	else
		doc->nFSFiles = 0;

	doc->dataFolder = m_DataFolder;
	return TRUE;
}

void CNewProject2::SetStrings(BOOL updateData) // = TRUE
{
	if (updateData)
		UpdateData(TRUE);
	SetWindowText(Strings.get(IDS_W0));
	
	for (int i = 0; i < 17; i++)
		GetDlgItem(IDC_TEXT1 + i)->SetWindowText(Strings.get(IDS_W1+i));

	GetDlgItem(IDC_SAVE_FINAL_STORAGE)->SetWindowText(Strings.get(IDS_W18));
	GetDlgItem(IDC_ASSOCIATEFSL)->SetWindowText(Strings.get(IDS_W19));
	GetDlgItem(IDC_BROWSE_DATA_FOLDER)->SetWindowText(Strings.get(IDS_W20));
	GetDlgItem(IDC_SAVE_LOCATIONS)->SetWindowText(Strings.get(IDS_W21));
	GetDlgItem(IDC_CHOOSE_ILL_LIST)->SetWindowText(Strings.get(IDS_W22));
	GetDlgItem(IDC_AVERAGE)->SetWindowText(Strings.get(IDS_W23));
	GetDlgItem(IDC_ONE_INSTANT)->SetWindowText(Strings.get(IDS_W24));
	GetDlgItem(IDC_BACK)->SetWindowText(Strings.get(IDS_W25));
	GetDlgItem(IDC_FINISH)->SetWindowText(Strings.get(IDS_W26));

	m_CDataRetrievalFreq.ResetContent();
	m_CSaveDataFreq.ResetContent();
	m_CSaveFSFreq.ResetContent();
	m_NewILFileFreq.ResetContent();
	m_cFSFrequency.ResetContent();

	for (i = 0; i < 10; i++)
		m_CDataRetrievalFreq.AddString(Strings.get(IDS_N_DATARETR1 + i));
	for (i = 0; i < 7; i++)
		m_CSaveDataFreq.AddString(Strings.get(IDS_N_DATASAVE1 + i));
	for(i = 0; i < 3; i++)
		m_CSaveFSFreq.AddString(Strings.get(IDS_N_FILETIME1 + i));
	for(i = 0; i < 3; i++)
		m_NewILFileFreq.AddString(Strings.get(IDS_N_FILETIME1 + i));
	for(i = 0; i < 2; i++)
		m_cFSFrequency.AddString(Strings.get(IDS_N_FSFREQ1 + i));
	UpdateData(FALSE);
}

BOOL CNewProject2::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		curLanguage = !curLanguage;
		SetStrings();
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CNewProject2::ShowFSDataNames()
{
	// this function will load information about the current m_ptrFSFileInfo into the 
	// list box and also set the number of data items in the edit box...
	//do work here...

	// there is no list box, this function will probably not be needed

}

void CNewProject2::OnChangeNilfiles() 
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

void CNewProject2::OnChangeNFsfiles() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if (m_cnFSFiles.GetWindowTextLength() > 0)
	{
		UpdateData(TRUE);
		if (m_nFSFiles > 2){
			m_nFSFiles = 2;
			UpdateData(FALSE);
		}
		m_Spin2.EnableWindow(m_nFSFiles > 1);
		if (m_nFSFiles > 0)
		{
			if (m_nFSFiles < m_wFSFile){
				m_wFSFile = m_nFSFiles;
				UpdateData(FALSE);
				OnChangeWfsfile();
			}
			m_Spin2.SetRange(1,m_nFSFiles);
		}
		else
		{
			m_SaveFinalStorage = FALSE;
			UpdateData(FALSE);
			OnSaveFinalStorage();
		}
	}
}

