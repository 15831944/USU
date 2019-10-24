// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LADA Control ModuleDoc.cpp : implementation of the CLADAControlModuleDoc class
//

#include "stdafx.h"
#include "LADA Control Module.h"

#include "LADA Control ModuleDoc.h"
//#include "ProjectSettingsDialog.h"
#include "NewProject1.h"
#include "NewProject2.h"
#include "LADA Control ModuleView.h"
#include "List.h"
#include "GraphDisplayView.h"
#include "GraphButtonForm.h"
#include "camera.h"

#include "LADASetupDlg.h"
#include "Lstring.h"
#include "LadaStrings.h"
#include "HistoryClass.h"
#include "LADASetupDlg.h"
#include "ViewHistoryDialog.h"
#include "StartDialog.h"
#include "MainFrm.h"
#include "CameraData.h"
#include "ParamDlg.h"
#include "CheckOutDlg1.h"
#include "GraphCollection.h"
#include "InputLocations.h"
#include "fstream.h"
#include "WaitTimerInfo.h"

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
extern UINT NotificationBox(CString text, CString title = "", DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);

extern void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char *AdditionalMessage = NULL);
extern int  curLanguage;
extern CLADAControlModuleApp theApp;
extern LString Strings;
extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern int LastDSP;
CFrameWnd * p_MainFrame = NULL;
extern CCamera* cameraDlg;
extern UINT IDS_TEMP;
extern BOOL PossiblyDisconnected;
extern CString IntToString(int number);
extern int ThreadsInCommWaitTimer;
extern DWORD __stdcall CommWaitTimer(void *lpdata);

#define SPECIAL_CODE	0x5F9EFAB0

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleDoc

IMPLEMENT_DYNCREATE(CLADAControlModuleDoc, CDocument)

BEGIN_MESSAGE_MAP(CLADAControlModuleDoc, CDocument)
	//{{AFX_MSG_MAP(CLADAControlModuleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()


CLADAControlModuleDoc::CLADAControlModuleDoc()
{
	hDataRetrievalThread = NULL;
	DataRequest = NULL;
	InitializeCriticalSection(&CommCriticalSection);
	WantToGetInputLocation = FALSE;
	ThreadsToBeServiced = 0;
	ThreadsServicing = 0;
	InputLocationToIndex = NULL;
		paneModified = NULL;
		PaneToCollectionIndex = NULL;
		GraphData = NULL;
		PositionTime = NULL;
		InputLocationNameList = NULL;
		InputLocationList = NULL;
		tempArray = NULL;
		newData = NULL;
		GraphCollection = NULL;
		m_GetLocationList = NULL;
		m_GetLocationListIndex = NULL;
		m_ILData = NULL;
		m_FSOutputTable = NULL;
		m_CameraData = NULL;
		m_HasMinMax = NULL;
		m_DoValidation = NULL;
		m_minValues = NULL;
		m_maxValues = NULL;
		m_History = NULL;
		m_ErrorFiles = NULL;
		m_HistoryNames = NULL;
		m_ErrorNames = NULL;
		m_ControlParameters = NULL;
		m_ptrHistoryDlg = NULL;
		m_ptrErrorDlg = NULL;

	m_AreCamerasLoaded = FALSE;
	openDocumentFailed = FALSE;
	m_LastCameraLoadFailed = FALSE;
	m_CamerasEnabled = 0;
	ApplicationIsOpen = TRUE;
	ManualBMP = new CBitmap;
	AutomaticBMP = new CBitmap;
	ManualBMP->LoadBitmap(IDB_MANMODE);
	AutomaticBMP->LoadBitmap(IDB_AUTOMODE);

	nGrowthChambers = 1;
	CR10Time = time_t(0);
	CR10TimeUpdated = time_t(0);
	m_IsCR10Initialized = FALSE;
	BackGraphCollections = 0;
	BackGraphCollection = NULL;
	BacknInputLocations = 0;
	BackInputLocationList = NULL;
	BackInputLocationNameList = NULL;
	BackM_DoValidation = NULL;

	PaneToCollectionIndex = NULL;
	GraphCollection = NULL;

	LoadBackGraphParameters = FALSE;
	// debug variable
	D_CatchEndCommBlock = FALSE;

	nILFiles = 0;
	nFSFiles = 0;
	nCameras = 0;

	dataFolder = workingDirectory + "\\Data";
	projectName = "LADA Experiment";

	ThreadsInCommBlock = 0;
	ConnectionStatus = NotConnected;
	InCommMode = FALSE;
	// TODO: add construction code here
	m_LastGroup = 0;
	//NewDataExists = FALSE;
	curWindow = -1;
	penThickBlack.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	penThinBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	penThinGray.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	
	m_nActiveRequests = 0;
	UpdateTimeRequests = 0;
	GraphData = 0;
	PositionTime = 0;
	InputLocationNameList = NULL;
	InputLocationList = NULL;
	tempArray = 0;
	commObject = NULL;
	m_History = NULL;
	m_ptrHistoryDlg = NULL;
	m_ptrErrorDlg = NULL;
	m_ptrManualDlg = NULL;
	m_pMainView = NULL;
	
	DocInitialized = FALSE;
	m_FrameWnd = NULL;
	m_ILData = NULL;
	m_FSOutputTable = NULL;
	m_CameraData = NULL;
	m_ControlState = NoControlState;

	m_Errors = 0;
	m_Reads = 0;
}

CLADAControlModuleDoc::~CLADAControlModuleDoc()
{
// These objects are deleted by DeleteContents, which
	// is called when the document is closed
	/*
	delete [] GraphData;
	delete [] PositionTime;
	delete [] InputLocationNameList;
	delete [] InputLocationList;
	delete [] tempArray;
	*/
	DeleteCriticalSection(&CommCriticalSection);
	int temp=0;
	delete AutomaticBMP;
	delete ManualBMP;
	if (commObject)
		delete commObject;
	commObject = NULL;
	ConnectionStatus = NotConnected;
}

int AssociateFile(char (*InputLocNameList)[2][30], int maxNum, CString filename = "", int wType = 0, int ArrayID = 0){
	
	char defExt[4];
	char dlgString[80];

	if (wType == 0)
	{
		strcpy(defExt,"csi");
		wsprintf(dlgString,"Campbell Scientific Files (*.%s)|*.%s|All Files (*.*)|*.*||",defExt,defExt);
	}
	else
	{
		strcpy(defExt,"fsl");
		wsprintf(dlgString,"Final Storage Label Files (*.%s)|*.%s|All Files (*.*)|*.*||",defExt,defExt);
	}

	char dotExt[5];
	wsprintf(dotExt,".%s",defExt);
	filename.Replace( ".dld", dotExt );
	CString smallFileName = filename;

	if (filename == ""){
		CFileDialog OpenFileDialogBox(TRUE, defExt, NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			dlgString,
			NULL);
		OpenFileDialogBox.m_ofn.lpstrTitle = (wType == 0 ? "Choose csi file":"Choose fsl file");
		UINT success = OpenFileDialogBox.DoModal();
		//this->UpdateWindow();

		if ( success == IDOK){
			filename = OpenFileDialogBox.GetPathName();
			smallFileName = OpenFileDialogBox.GetFileName();
		}
		else
			return 0;
	}
			 
	HANDLE fileIn = CreateFile(filename, 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileIn == INVALID_HANDLE_VALUE){
		DWORD LError = GetLastError();
		CloseHandle( fileIn ); 
		if (LError == ERROR_FILE_NOT_FOUND){
			if (MessageBox(IDS_M_NO_FILE_MATCH_FOUND, NO_TITLE,	MB_YESNO | MB_ICONQUESTION) 
				== IDYES)
			{
				AssociateFile(InputLocNameList, maxNum, CString(""),wType);
			}
		}
		else
			DisplayErrorMessage(LError);
		return 0;
	}

	// reset all input location names.
	//char nameBuff[30];
	//for (int i = 1; i <= MAX_INPUT_LOCATIONS; i++){
	//	wsprintf(nameBuff, "%3i: [no name]", i);
	//	InputLocNameList[i - 1] = nameBuff;
	//}

	int fileSize = (signed int) GetFileSize(fileIn, NULL);
	char *fileBuff = new char[fileSize + 1];
	DWORD bytesRead;
	ReadFile(fileIn,fileBuff,fileSize,&bytesRead,NULL);
	CloseHandle( fileIn ); 

	BOOL FoundInputStorageStart = FALSE;
	BOOL ignoreInput = FALSE;
	int CurrNumber = 0;
	int whichLoc = 0;
	char curChar;
	char newName[25];
	int wordPos = 0;
	int maxLoc = 0;
	int LocationN = 0;

	for (int i = 0; i < fileSize; i++){
		curChar = fileBuff[i];
		
		if ((wType == 0 && FoundInputStorageStart) || // means we are looking for input locations, should be csi file
			(wType == 1 && FoundInputStorageStart)) // means we are looking for final storage names
			
		{
			if (curChar == 'O'){
				if (strncmp(&fileBuff[i],"Output_Table",12) == 0)
					break;
			}
			else if (curChar == 'P')
			{
				if (strncmp(&fileBuff[i-1],"-Program Security-",18) == 0)
					break;
			}
		}

		if (FoundInputStorageStart){
			if (!ignoreInput){
				if (curChar >= '0' && curChar <= '9' && whichLoc == 0){
					CurrNumber *= 10;
					CurrNumber += curChar - '0';
				}
				else if (curChar == ' ' && CurrNumber != 0 && whichLoc == 0){
					whichLoc = CurrNumber;
				}
				else if (curChar == ' ' && wordPos > 0)
					ignoreInput = TRUE;
				else if (whichLoc != 0) {
					newName[wordPos++] = curChar;
					newName[wordPos] = '\0';
				}
			} 
			else if (curChar == '\n' || curChar == '\r'){
				if (whichLoc > 0){
					if (LocationN < maxNum)
					{
						if (wType == 0)
						{
							char nameBuff[27];
							wsprintf(nameBuff,"%3i:%s", whichLoc, newName);
							//InputLocNameList[whichLoc - 1] = nameBuff;
							strcpy(InputLocNameList[LocationN][curLanguage],nameBuff);
						}
						else
							strcpy(InputLocNameList[LocationN][curLanguage],newName);

						ignoreInput = FALSE;
						if (whichLoc > maxLoc)
							maxLoc = whichLoc;
						LocationN++;
						whichLoc = 0;
						CurrNumber = 0;
						wordPos = 0;
					}
					else
					{
						delete [] fileBuff;
						return LocationN;
					}
				}
				else
					break; // that means we are probably done
					// reading input locations, if there was no
					// number read on this line.
			}
		}
		else if (curChar == 'I' && wType == 0)
		{
			if (strncmp(&fileBuff[i],"Input_Storage",13) == 0 ||
				strncmp(&fileBuff[i-1],"-Input Locations-", 17) == 0){
				FoundInputStorageStart = TRUE;
				i += 12;
				while (fileBuff[++i] != '\n');
				
			}
		}
		else if (curChar == 'O' && wType == 1)
		{
			if (strncmp(&fileBuff[i],"Output_Table",12) == 0)
			{	
				while (--i && fileBuff[i] != '\r' && fileBuff[i] != '\n');
				i++;
				int value = 0;
				for (; fileBuff[i] >= '0' && fileBuff[i] <= '9'; i++)
				{
					value *= 10;
					value += fileBuff[i] - '0';
				}
				if (value == ArrayID)
					FoundInputStorageStart = TRUE;
				
				i += 11;
					while (fileBuff[++i] != '\n');
			}
		}
	}
	delete [] fileBuff;
	//SetInputLocationsNamesText();
	return LocationN;
}

BOOL AssociateFSLFile(CString & filename, CString *&dataNames, int *&ArrayID, int maxIDs, int maxPoints, int &numIDs, int *&nDataPoints)
{
	// CString *dataNames	- array to hold names of data points found
	// int *ArrayID			- array to hold array IDs of output tables found
	// int maxIDs			- max number of output tables to find
	// int maxPoints		- max number of data points to find per table
	// int &numIDs			- the actual number of output tables found
	// int *nDataPoints		- the number of data points per table found

	dataNames = new CString[maxIDs * maxPoints];
	ArrayID = new int[maxIDs];
	numIDs = 0;
	nDataPoints = new int[maxIDs];
	memset(nDataPoints,0,sizeof(int)*maxIDs);

	char dlgString[80];

	wsprintf(dlgString,"Final Storage Label Files (*.%s)|*.%s|All Files (*.*)|*.*||",FSLabelExtension,FSLabelExtension);
	char dotExt[5];
	wsprintf(dotExt,".%s",FSLabelExtension);

	CString smallFileName;

	CFileDialog OpenFileDialogBox(TRUE, FSLabelExtension, NULL, 
		OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
		dlgString,
		NULL);
	OpenFileDialogBox.m_ofn.lpstrTitle = "Choose fsl file";
	UINT success = OpenFileDialogBox.DoModal();
	if ( success == IDOK )
	{
		filename = OpenFileDialogBox.GetPathName();
		smallFileName = OpenFileDialogBox.GetFileName();
	}
	else
		return FALSE;
	
			 
	HANDLE fileIn = CreateFile(filename, 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileIn == INVALID_HANDLE_VALUE)
	{
		DWORD LError = GetLastError();
		CloseHandle( fileIn ); 
		return FALSE;
	}

	int fileSize = (signed int) GetFileSize(fileIn, NULL);
	char *fileBuff = new char[fileSize + 1];
	DWORD bytesRead;
	ReadFile(fileIn,fileBuff,fileSize,&bytesRead,NULL);
	CloseHandle( fileIn ); 

	BOOL FoundInputStorageStart = FALSE;
	BOOL ignoreInput = FALSE;
	int CurrNumber = 0;
	int whichLoc = 0;
	char curChar;
	char newName[25];
	int wordPos = 0;
	int maxLoc = 0;
	int LocationN = 0;

	for (int i = 0; i < fileSize; i++){
		curChar = fileBuff[i];
		
		if (FoundInputStorageStart) // means we are looking for final storage names
		{
			if (curChar == 'E')
			{
				if (strncmp(&fileBuff[i-1],"Estimated",9) == 0)
					break;
			}
		}

		if (FoundInputStorageStart){
			if (!ignoreInput){
				if (curChar >= '0' && curChar <= '9' && whichLoc == 0){
					CurrNumber *= 10;
					CurrNumber += curChar - '0';
				}
				else if (curChar == ' ' && CurrNumber != 0 && whichLoc == 0){
					whichLoc = CurrNumber;
				}
				else if (curChar == ' ' && wordPos > 0)
					ignoreInput = TRUE;
				else if (whichLoc != 0) 
				{
					newName[wordPos++] = curChar;
					newName[wordPos] = '\0';
				}
			} 
			else if (curChar == '\n' || curChar == '\r')
			{
				if (whichLoc > 0)
				{
					if (nDataPoints[numIDs] < maxPoints)
					{
						dataNames[maxPoints * (numIDs-1) + nDataPoints[numIDs-1]] = newName;
						nDataPoints[numIDs-1]++;
						ignoreInput = FALSE;
						whichLoc = 0;
						CurrNumber = 0;
						wordPos = 0;
					}
					
				}
			}
		}
		if (curChar == 'O')
		{
			if (strncmp(&fileBuff[i],"Output_Table",12) == 0 && numIDs < maxIDs)
			{	
				FoundInputStorageStart = TRUE;
				while (--i && fileBuff[i] != '\r' && fileBuff[i] != '\n');
				i++;
				int value = 0;
				for (; fileBuff[i] >= '0' && fileBuff[i] <= '9'; i++)
				{
					value *= 10;
					value += fileBuff[i] - '0';
				}
				ArrayID[numIDs] = value;
				numIDs++;
				i += 11;
					while (fileBuff[++i] != '\n');
			}
			else if (numIDs == maxIDs)
			{
				break;
			}
		}
	}
	delete [] fileBuff;
	//SetInputLocationsNamesText();
	return TRUE;
}

BOOL CLADAControlModuleDoc::OnNewDocument()
{
	if (!DocInitialized){
		// the only case when the document is not initialized is if no
		// document has been loaded.  this can happen in OnNewDocument is 
		// called by default, when no previous document is detected.
		// In this case the user may want to load a different document.  
		// We should ask them.
		UINT dChoice = MessageBox(IDS_NO_CONFIGURATION_FOUND, NO_TITLE, MB_YESNO|MB_ICONQUESTION);
		
		if (dChoice == IDNO)
		{
			// we need to figure out which file to open and then call serialize ourselves...
			CFileDialog OpenFileDialogBox(TRUE, ".lada", NULL, 
				OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
				"Lada Config Program (*.lada)|*.lada|",NULL);
		 
			UINT success = OpenFileDialogBox.DoModal();
		
			if ( success == IDOK){
				CString filename = OpenFileDialogBox.GetPathName();
				// LOAD THIS FILE
				return OnOpenDocument(filename);
			}
			return FALSE;
		}
		if (!CDocument::OnNewDocument())
			return FALSE;
		if (!GetNewProjectSettings())
			return FALSE;
	}
	else
	{
		const CString fileName = GetPathName();
		
		if (commObject)
			StopComm();
		if (fileName != ""){
			SetLastFile(fileName);
			if (IsModified())
				OnSaveDocument(fileName);
		}
		m_pMainView->OnTimer(DESTROY_TIMERS);

		if (!CDocument::OnNewDocument())
			return FALSE;
		if (!GetNewProjectSettings())
		{
			// revert to previous document
			//return TRUE;
			return OnOpenDocument(fileName);
			//but for now just close program
			//return FALSE;
		}
	}

	nGrowthChambers = 1;
	m_ControlParameters = new CControlParameters[nGrowthChambers];
	m_ControlMode = ManualControlMode;
	maxGraphItems = 15;
	projectOptionsFile = projectName + ".lada";
	CString fullFilePath = dataFolder + "\\" + projectOptionsFile;
	LastCopyFolder = dataFolder;
	SetPathName(fullFilePath);
	
	nHistoryFiles = Strings.nLanguages;
	m_HistoryNames = new CString[nHistoryFiles];
	for (int i = 0; i < nHistoryFiles; i++)
	{
		m_HistoryNames[i] = projectName + " History(" + Strings.LNames[i] + ")." + HistoryExtension;
	}
	m_ErrorNames = new CString[nHistoryFiles];
	for ( i = 0; i < nHistoryFiles; i++)
	{
		m_ErrorNames[i] = projectName + " Error Log(" + Strings.LNames[i] + ")." + ErrorExtension;
	}
	
	nGraphCollections = 3;
	GraphCollection = new CGraphCollection[nGraphCollections];
	
	PaneToCollectionIndex = new int[nPanes];
	for ( i = 0; i < nPanes; i++)
		PaneToCollectionIndex[i] = -1;

	DoAutoWrap = FALSE;
	m_UseMilitaryTime = TRUE;
	backgroundBrushColor = RGB(0,0,0);//RGB(200, 200, 255);

	m_HasMinMax = new BOOL[nInputLocations];
	memset(m_HasMinMax,0,sizeof(BOOL)*nInputLocations);
	m_DoValidation = new BOOL[nInputLocations];
	memset(m_DoValidation,0,sizeof(BOOL)*nInputLocations);
	m_maxValues = new double[nInputLocations];
	memset(m_maxValues,0,sizeof(double)*nInputLocations);
	m_minValues = new double[nInputLocations];
	memset(m_minValues,0,sizeof(double)*nInputLocations);

	OnStartNewDocument();
	m_FloppyDefault = "A:\\";
	m_PcmciaDefault = "D:\\";
	
	m_History->OpenFiles();
	m_History->WriteHistory("Project Settings","project file created.");
	m_History->CloseFiles();

	OnSaveDocument(fullFilePath);
	ExecuteInitialCommand();
	if (ApplicationIsOpen == FALSE)
	{
		if (commObject)
		StopComm();
		if (fullFilePath != ""){
			SetLastFile(fullFilePath);
			if (IsModified())
				OnSaveDocument(fullFilePath);
		}
		return FALSE;
	}
	return TRUE;
}

void CLADAControlModuleDoc::FillWithRandomData()
{
	CTime fakeTime = CTime::GetCurrentTime();
	double * Array = new double[nInputLocations];
	while (nFilledPoints < 500){
		for (int j = 0; j < nInputLocations; j++){
			Array[j] = rand() % 10 + j / 10 * (rand() % 2 + 2);
		}
		AddData(Array, fakeTime);
		fakeTime += CTimeSpan( 0, 0, 0, 1 ); 
	}
	delete [] Array;
}

void CLADAControlModuleDoc::WriteInputLocations(CInputLocFileInfo * ptrInfo)
{
	CTime theTime = CTime::GetCurrentTime();
	// decide if we should create a new file or open an existing file...
	bool CreateNew = false;
	
	if (ptrInfo->m_LastCreateTime == 0)
	{
		// file has never been created...
		ptrInfo->m_LastCreateTime = theTime;
		CreateNew = true;
	}
	else if ((theTime - ptrInfo->m_LastCreateTime).GetTotalSeconds() >= 
		ptrInfo->m_NewFileFreq.GetTotalSeconds() )
	{
		ptrInfo->m_LastCreateTime += ptrInfo->m_NewFileFreq;
		if ((theTime - ptrInfo->m_LastCreateTime).GetTotalSeconds() > ptrInfo->m_NewFileFreq.GetTotalSeconds() / 60)
			ptrInfo->m_LastCreateTime = theTime;
		CreateNew = true;
	}

	HANDLE hFile;
	if (CreateNew || ptrInfo->m_FileName == "")
	{
		char fileNameBuff[100];
		CString s = theTime.Format( "%H;%M;%S, %B %d, %Y" );
		wsprintf(fileNameBuff,"%s\\%s %s.%s", dataFolder, ptrInfo->m_Name, s, InputLocationExtension);
		ptrInfo->m_FileName = fileNameBuff;
		hFile = CreateFile(fileNameBuff, 
			GENERIC_WRITE, 
			FILE_SHARE_READ, 
			NULL, 
			CREATE_ALWAYS, 
			FILE_ATTRIBUTE_ARCHIVE, 
			NULL);
		CreateNew = true;
	}
	else 
	{
		hFile = CreateFile(ptrInfo->m_FileName.GetBuffer(1), 
			GENERIC_WRITE, 
			FILE_SHARE_READ, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_ARCHIVE, 
			NULL);
	}

	if (hFile == INVALID_HANDLE_VALUE){
		CloseHandle(hFile);
		DisplayErrorMessage(GetLastError());
		return;
	}
	
	CFile file((int)hFile);
	CArchive ar(&file,CArchive::store);
	CString d;

	if (CreateNew)
	{
		// add header
		// Input Locations, 1,2,3,4,5,6,7,8,9
		ar.WriteString("  Time  \t");
		for (int i = 0; i < ptrInfo->m_nLocations; i++)
		{
			// To write the input location number to file:
			//d = ValueToString(ptrInfo->m_Locations[i] + 1, 0);
			// To write the input location name to file
			d = CString(InputLocationNameList[ptrInfo->m_Locations[i]][ENGLISH]);
			if (i == ptrInfo->m_nLocations - 1)
				ar.WriteString(d + "\r\n");
			else
				ar.WriteString(d + "\t");
		}
	}
	else
	{
		file.SeekToEnd();
	}

	CString s = theTime.Format( "%H:%M:%S\t" );
	ar.WriteString(s);
	
	for (int i = 0; i < ptrInfo->m_nLocations; i++)
	{
		if (ptrInfo->m_SaveByAverage)
			d = ValueToString(ptrInfo->m_tempData[i] / ptrInfo->m_nItemsInTempData);
		else
			d = ValueToString(ptrInfo->m_tempData[i]);

		if (i == ptrInfo->m_nLocations - 1)
			ar.WriteString(d + "\r\n");
		else
			ar.WriteString(d + "\t");
	}
	ar.Close();
	file.Close();
	// set number of data items to zero and clear out storage array
	ptrInfo->m_nItemsInTempData = 0;
	memset(ptrInfo->m_tempData, 0, sizeof(double) * ptrInfo->m_nLocations);
}

void CLADAControlModuleDoc::AddData(double data[], CTime dataTime, BOOL UpdateViews )//=TRUE
{

	/*
	nFilledSaveData++;
	if (dataTime - lastSaveTime >= dataWriteFreq ) 
	{
		lastSaveTime = CTime::GetCurrentTime();
		
		for (int i = 0; i < nData; i++)
			tempSaveData[i] = (tempSaveData[i] + data[i]) / nFilledSaveData;
				
		WriteInputLocations();

		nFilledSaveData = 0;
		for (i = 0; i < nData; i++)
			tempSaveData[i] = 0.0;
		
	} 
	else 
	{
		for (int i = 0; i < nData; i++)
			tempSaveData[i] = tempSaveData[i] + data[i];
	}

	if (nFilledPoints == 0 || dataTime - PositionTime[(GraphDataPos > 0 ? GraphDataPos - 1 : nFilledPoints - 1)]
		>= dataPlotFreq ) 
	{

		PositionTime[GraphDataPos] = dataTime;
		
		if (nItemsInTempArray != 0){
			nItemsInTempArray++;
			for (int i = 0; i < nData; i++)
				data[i] = (tempArray[i] + data[i]) / nItemsInTempArray;
			nItemsInTempArray = 0;		
		}
		memcpy(&GraphData[GraphDataPos * nData], data, GraphDataBlockSize);
		
		GraphDataPos++;
		
		if (GraphDataPos >= nBackPoints)
			GraphDataPos = 0;
		
		if (nFilledPoints < nBackPoints){
			nFilledPoints++;
		}
		
	} 
	else 
	{
		nItemsInTempArray++;
		if (nItemsInTempArray == 1){
			for (int i = 0; i < nData; i++)
				tempArray[i] = data[i];	
		}
		else
		{
			for (int i = 0; i < nData; i++)
				tempArray[i] = tempArray[i] + data[i];
		}
				

	}
	*/

	//if (UpdateViews)
	//	UpdateAllViews(NULL);
}

double CLADAControlModuleDoc::GetDataValue(int whichGraph, int whichData, int Position)
{
	return GraphData[Position * nInputLocations + GraphCollection[whichGraph].DataIndex[whichData]];
}

const char * CLADAControlModuleDoc::GetDataName(int whichGraph, int whichData)
{
	if (whichData < GraphCollection[whichGraph].nItems)
		return InputLocationNameList[GraphCollection[whichGraph].DataIndex[whichData]][curLanguage];
	else
		return "";
}

CString CLADAControlModuleDoc::GetPositionLabel(int Position)
{
	if (m_UseMilitaryTime)
		return PositionTime[Position].Format("%H:%M:%S");
	else
		return PositionTime[Position].Format("%I:%M:%S");
}

BOOL CLADAControlModuleDoc::IsPositionLabel(int pos)
{
	return (PositionTime[pos] != CTime(time_t(0)));
}


/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleDoc serialization

void CLADAControlModuleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		if (LoadBackGraphParameters)
			SaveWetupGraphParameters();
		UINT iSize;
		iSize = sizeof(int);
		ar.Write(&nPanes,iSize);
		ar.Write(&nGraphCollections,iSize);
		ar.Write(&nGrowthChambers,iSize);
		ar.Write(&curLanguage,iSize);
		ar.Write(&nHistoryFiles,iSize);
		ar.Write(&nInputLocations,iSize);
		ar.Write(&defaultPort,iSize);
		iSize = nInputLocations * sizeof(int);
		ar.Write(InputLocationList, iSize);
		iSize = nInputLocations * sizeof(InputListType);
		ar.Write(InputLocationNameList,iSize);
		iSize = sizeof(LONG);
		LONG timeSpan;
		// timeSpan = dataRetrievalFreq.GetTotalSeconds();
		//ar.Write(&timeSpan,iSize);
		timeSpan = dataPlotFreq.GetTotalSeconds();
		ar.Write(&timeSpan,iSize);
		//timeSpan = dataWriteFreq.GetTotalSeconds();
		//ar.Write(&timeSpan,iSize);
		//timeSpan = newFileFreq.GetTotalSeconds();
		//ar.Write(&timeSpan,iSize);
		iSize = sizeof(int);
		ar.Write(&nBackPoints,iSize);
		ar.Write(&nILFiles,iSize);
		ar.Write(&nFSFiles,iSize);
		ar.Write(&nCameras,iSize);
		ar.Write(&nInputLocations,iSize);
		ar.Write(&nGraphCollections,iSize);
		ar.Write(&nPanes,iSize);
		ar.Write(&m_CamerasEnabled,iSize);
		
		iSize = sizeof(BOOL);
		ar.Write(&DoAutoWrap,iSize);
		ar.Write(&m_DoWetup,iSize);
		ar.Write(&m_IsWetupComplete,iSize);
		ar.Write(&m_UseMilitaryTime,iSize);
		ar.Write(&m_IsCR10Initialized,iSize);
		ar.Write(&m_LastCameraLoadFailed,iSize);

		ar.Write(&backgroundBrushColor,sizeof(COLORREF));
		ar.WriteString(dataFolder);
		ar.WriteString( "\n" );
		ar.WriteString(projectName);	
		ar.WriteString( "\n" );
		ar.WriteString(projectOptionsFile);	
		ar.WriteString( "\n" );
		ar.WriteString(m_FloppyDefault);
		ar.WriteString( "\n" );
		ar.WriteString(m_PcmciaDefault);
		ar.WriteString( "\n" );
		ar.WriteString(LastCopyFolder);
		ar.WriteString( "\n" );
		for (int i = 0; i < nHistoryFiles; i++){
			ar.WriteString( m_HistoryNames[i] );
			ar.WriteString( "\n" );
			ar.WriteString( m_ErrorNames[i] );
			ar.WriteString( "\n" );
		}

		for (i = 0; i < nGraphCollections; i++)
			GraphCollection[i].WriteObject(ar);

		ar.Write(PaneToCollectionIndex,sizeof(int)*nPanes);

		//if (saveLocations)
		//{
		for (i = 0; i < nILFiles; i++)
			m_ILData[i].WriteObject(ar);
		//}

		if (nFSFiles)
		{
			SaveDataStoragePointer();
			m_FSCollectionParam.WriteObject(ar);

			for (i = 0; i < nFSFiles; i++)
				m_FSOutputTable[i].WriteObject(ar);
		}

		for (i = 0; i < nCameras; i++)
			m_CameraData[i].WriteObject(ar);

		m_WetupInfo.WriteObject(ar);

		for (i = 0; i < nGrowthChambers; i++)
			m_ControlParameters[i].WriteObject(ar);

		ar.Write(m_HasMinMax,sizeof(BOOL) * nInputLocations);
		ar.Write(m_DoValidation,sizeof(BOOL) * nInputLocations);
		ar.Write(m_minValues,sizeof(double) * nInputLocations);
		ar.Write(m_maxValues,sizeof(double) * nInputLocations);

		ar.Write(&m_ControlMode,sizeof(ControlModeType));

		unsigned int checkValue = SPECIAL_CODE;
		ar.Write(&checkValue, sizeof(unsigned int));

		if (LoadBackGraphParameters)
			LoadWetupGraphParameters();
	}
	else
	{
		SetPathName(ar.GetFile()->GetFilePath());
		maxGraphItems = 15;
		// TODO: add loading code here
		
		UINT iSize;
		iSize = sizeof(int);
		ar.Read(&nPanes,iSize);
		ar.Read(&nGraphCollections,iSize);
		ar.Read(&nGrowthChambers,iSize);
		ar.Read(&curLanguage,iSize);
		ar.Read(&nHistoryFiles,iSize);
		ar.Read(&nInputLocations,iSize);
		ar.Read(&defaultPort,iSize);
		InputLocationNameList = new InputListType[nInputLocations];
		InputLocationList = new int[nInputLocations];
		iSize = nInputLocations * sizeof(int);
		ar.Read(InputLocationList, iSize);
		iSize = nInputLocations * sizeof(InputListType);
		ar.Read(InputLocationNameList,iSize);
		iSize = sizeof(LONG);
		LONG timeSpan;
		//ar.Read(&timeSpan,iSize);
		//dataRetrievalFreq = CTimeSpan(time_t(timeSpan));
		ar.Read(&timeSpan,iSize);
		dataPlotFreq = CTimeSpan(time_t(timeSpan));
		//ar.Read(&timeSpan,iSize);
		//dataWriteFreq = CTimeSpan(time_t(timeSpan));
		//ar.Read(&timeSpan,iSize);
		//newFileFreq = CTimeSpan(time_t(timeSpan));
		iSize = sizeof(int);
		ar.Read(&nBackPoints,iSize);
		ar.Read(&nILFiles,iSize);
		ar.Read(&nFSFiles,iSize);
		ar.Read(&nCameras,iSize);
		ar.Read(&nInputLocations,iSize);
		ar.Read(&nGraphCollections,iSize);
		ar.Read(&nPanes,iSize);
		ar.Read(&m_CamerasEnabled,iSize);

		iSize = sizeof(BOOL);
		ar.Read(&DoAutoWrap,iSize);
		ar.Read(&m_DoWetup,iSize);
		ar.Read(&m_IsWetupComplete,iSize);
		ar.Read(&m_UseMilitaryTime,iSize);
		ar.Read(&m_IsCR10Initialized,iSize);
		ar.Read(&m_LastCameraLoadFailed,iSize);

		ar.Read(&backgroundBrushColor,sizeof(COLORREF));
		ar.ReadString(dataFolder);
		ar.ReadString(projectName);
		ar.ReadString(projectOptionsFile);
		ar.ReadString(m_FloppyDefault);
		ar.ReadString(m_PcmciaDefault);
		ar.ReadString(LastCopyFolder);
		m_HistoryNames = new CString[nHistoryFiles];
		m_ErrorNames = new CString[nHistoryFiles];
		for (int i = 0; i < nHistoryFiles; i++)
		{
			ar.ReadString( m_HistoryNames[i] );
			ar.ReadString( m_ErrorNames[i] );
		}
		
		if (nGraphCollections)
		{
			GraphCollection = new CGraphCollection[nGraphCollections];
			for (i = 0; i < nGraphCollections; i++)
				GraphCollection[i].ReadObject(ar);
		}
		
		PaneToCollectionIndex = new int[nPanes];
		ar.Read(PaneToCollectionIndex,sizeof(int)*nPanes);

		if (nILFiles){
			m_ILData = new CInputLocFileInfo[nILFiles];
			for (i = 0; i < nILFiles; i++)
				m_ILData[i].ReadObject(ar);
		}

		if (nFSFiles)
		{
			LoadDataStoragePointer();
			m_FSCollectionParam.ReadObject(ar);
			m_FSOutputTable = new CFSInfo[nFSFiles];

			for (i = 0; i < nFSFiles; i++)
				m_FSOutputTable[i].ReadObject(ar);
		}

		if (nCameras)
		{
			m_CameraData = new CCameraData[nCameras];
			for (i = 0; i < nCameras; i++)
				m_CameraData[i].ReadObject(ar);
		}


		m_WetupInfo.ReadObject(ar);

		m_ControlParameters = new CControlParameters[nGrowthChambers];
		for (i = 0; i < nGrowthChambers; i++)
			m_ControlParameters[i].ReadObject(ar);

		m_HasMinMax = new BOOL[nInputLocations];
		m_DoValidation = new BOOL[nInputLocations];
		m_minValues = new double[nInputLocations];
		m_maxValues = new double[nInputLocations];
		ar.Read(m_HasMinMax,sizeof(BOOL) * nInputLocations);
		ar.Read(m_DoValidation,sizeof(BOOL) * nInputLocations);
		ar.Read(m_minValues,sizeof(double) * nInputLocations);
		ar.Read(m_maxValues,sizeof(double) * nInputLocations);

		ar.Read(&m_ControlMode,sizeof(ControlModeType));
		
		unsigned int checkValue = 0;
		ar.Read(&checkValue, sizeof(unsigned int));
		unsigned int specialCode = SPECIAL_CODE;
		if (checkValue != SPECIAL_CODE)
		{
			curLanguage = 0;
			MessageBox(IDS_M_CORRUPTED_OR_INVALID_DATA_FILE,IDS_ERROR,MB_ICONSTOP);
			ApplicationIsOpen = FALSE;
			openDocumentFailed = TRUE;
		}
	}
}

void CLADAControlModuleDoc::SetLastFile(CString fileName)
{
	HANDLE fileOut;
	CString fileLocation = CString(workingDirectory) + CString("\\lastfile.txt");
	fileOut = CreateFile(fileLocation, 
		GENERIC_WRITE, 
		0, 
		NULL, 
		OPEN_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileOut == INVALID_HANDLE_VALUE)
	{
		CloseHandle(fileOut);
		return;
	}
	DWORD bytesRead;
	LPTSTR fileBuff = fileName.GetBuffer( 1 );
	DWORD fileNameLength = strlen(fileBuff) + 1;		
	WriteFile(fileOut,&fileNameLength,sizeof(fileNameLength),&bytesRead,NULL);
	WriteFile(fileOut,fileBuff,fileNameLength,&bytesRead,NULL);
	CloseHandle(fileOut);
	fileName.ReleaseBuffer();

}

void CLADAControlModuleDoc::DeleteLastFile()
{
	CString fileLocation = CString(workingDirectory) + CString("\\lastfile.txt");
	if (!DeleteFile(fileLocation))
	{
		DWORD error = GetLastError();
		if (error)
			DisplayErrorMessage(error,TRUE);
	}
}

void CLADAControlModuleDoc::ToggleData(int whichIndex, int whichButton)
{
	GraphCollection[whichIndex].isItemChecked[whichButton] = !GraphCollection[whichIndex].isItemChecked[whichButton];
}

BOOL CLADAControlModuleDoc::IsItemChecked(int whichIndex, int whichButton)
{
	return GraphCollection[whichIndex].isItemChecked[whichButton];
}
/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleDoc diagnostics

#ifdef _DEBUG
void CLADAControlModuleDoc::AssertValid() const
{
	//CDocument::AssertValid();
}

void CLADAControlModuleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleDoc commands

void CLADAControlModuleDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	// communication should stop here
	if (commObject)
		StopComm();
	
	if (m_CamerasEnabled)
	{
		UnloadCameras();
	}

	CString filePath = GetPathName();
	
	if (openDocumentFailed)
	{
		DeleteLastFile();
	}
	else if (filePath != "")
	{
		SetLastFile(filePath);
		if (IsModified())
			OnSaveDocument(filePath);
	}
	CDocument::OnCloseDocument();
}

void CLADAControlModuleDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	// delete those things which will be re-initialized
	//if (GraphData) {
		delete [] paneModified;
		delete [] PaneToCollectionIndex;
		delete [] GraphData;
		delete [] PositionTime;
		delete [] InputLocationNameList;
		delete [] InputLocationList;
		delete [] tempArray;
		delete [] newData;
		delete [] InputLocationToIndex;
		delete [] GraphCollection;
		delete [] m_GetLocationList;
		delete [] m_GetLocationListIndex;
		delete [] m_ILData;
		delete [] m_FSOutputTable;
		delete [] m_CameraData;
		delete [] m_HasMinMax;
		delete [] m_DoValidation;
		delete [] m_minValues;
		delete [] m_maxValues;
		delete m_History;
		delete m_ErrorFiles;
		delete [] m_HistoryNames;
		delete [] m_ErrorNames;
		delete [] m_ControlParameters;
		delete m_ptrHistoryDlg;
		delete m_ptrErrorDlg;
		InputLocationToIndex = NULL;
		paneModified = NULL;
		PaneToCollectionIndex = NULL;
		GraphData = NULL;
		PositionTime = NULL;
		InputLocationNameList = NULL;
		InputLocationList = NULL;
		tempArray = NULL;
		newData = NULL;
		GraphCollection = NULL;
		m_GetLocationList = NULL;
		m_GetLocationListIndex = NULL;
		m_ILData = NULL;
		m_FSOutputTable = NULL;
		m_CameraData = NULL;
		m_HasMinMax = NULL;
		m_DoValidation = NULL;
		m_minValues = NULL;
		m_maxValues = NULL;
		m_History = NULL;
		m_ErrorFiles = NULL;
		m_HistoryNames = NULL;
		m_ErrorNames = NULL;
		m_ControlParameters = NULL;
		m_ptrHistoryDlg = NULL;
		m_ptrErrorDlg = NULL;
	//}
	backgroundBrush.DeleteObject();
	curWindow = -1;
	nFilledPoints = 0;
	maxGraphItems = 15;
	GraphDataPos = 0;
	GraphData = NULL;
	PositionTime = NULL;
	tempArray = NULL;
	newData = NULL;
	m_nGetLocList = 0;


}

BOOL CLADAControlModuleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	OnStartNewDocument();
	ExecuteInitialCommand();

	if (ApplicationIsOpen == FALSE)
	{
		if (commObject)
		StopComm();
		CString filePath = GetPathName();
		
		if (filePath != "" && !openDocumentFailed)
		{
			SetLastFile(filePath);
			if (IsModified())
				OnSaveDocument(filePath);
		}
		//SaveModified();
		return FALSE;

	}

	// TODO: Add your specialized creation code here
	DocInitialized = TRUE;
	return TRUE;
}

void CLADAControlModuleDoc::UpdateGraphViews()
{
	for (int i = 0; i < nPanes; i++)
	{
		((CGraphDisplayView *)pGraphView[i])->OnUpdate(pGraphView[i],1,NULL);
		((CGraphButtonForm *)pGraphButtonView[i])->OnUpdate(pGraphButtonView[i],0,NULL);
		//pGraphView[i]->InvalidateRect(NULL,FALSE);
	}
}

BOOL CLADAControlModuleDoc::StopComm()
{
	//if (!InCommMode)
	//	MessageBox(NULL,"Error:  StopComm() called while InCommMode == FALSE","Error",MB_OK);
	InCommMode = FALSE; // just in case m_pMainView is NULL
	EndDataRetrievalMode();
	
	// DON'T KILL COMM STRUCTURES IN THE MIDDLE OF RETRIEVING DATA
	

	if (commObject)
	{
		commObject->EndCR10Comm();
		delete commObject;
		commObject = NULL;
	}
	ConnectionStatus = NotConnected;
	if (m_pMainView)
		m_pMainView->SetCommStatusWindow(ConnectionStatus);

	return TRUE;
}



void CLADAControlModuleDoc::OnStartNewDocument()
{
	GraphData = new double[nInputLocations * nBackPoints];
	GraphDataBlockSize = sizeof(double) * nInputLocations;
	PositionTime = new CTime[nBackPoints];
	tempArray = new double[nInputLocations];
	newData = new double[MAX_INPUT_LOCATIONS]; // nInputLocations
	InputLocationToIndex = new int[MAX_INPUT_LOCATIONS];
	for (int i = 0; i < MAX_INPUT_LOCATIONS; i++)
		InputLocationToIndex[i] = -1;
	for ( i = 0; i < nInputLocations; i++)
		InputLocationToIndex[InputLocationList[i]] = i;

	ClearGraphData();
		
	paneModified = new BOOL[nPanes];
	for ( i = 0; i < nPanes; i++)
		paneModified[i] = TRUE;

	backgroundBrush.CreateSolidBrush(backgroundBrushColor);

	m_History = new CHistoryClass(this, nHistoryFiles, m_HistoryNames, &m_ptrHistoryDlg);
	m_ErrorFiles = new CHistoryClass(this, nHistoryFiles, m_ErrorNames, &m_ptrErrorDlg);
	//lastFileCreationTime = lastSaveTime = CTime::GetCurrentTime();
	//ILFileOut = NULL;
	DocInitialized = TRUE;

	m_nGetLocList = 0;
	m_GetLocationList = new int[nInputLocations];
	m_GetLocationListIndex = new int[nInputLocations];

	ResetGetLocList();
	
	if (m_CamerasEnabled)
	{
		LoadCameras();
	}

}

void CLADAControlModuleDoc::RequestLocations(int *locList, int nLoc)// index zero based location list, not cr10 actual list
{
	for (int i = 0; i < nLoc; i++)
	{
		for (int j = 0; j < nInputLocations; j++)
		{
			if (m_GetLocationList[j] == 0)
			{
				m_GetLocationList[j] = InputLocationList[locList[i]] + 1;
				m_GetLocationListIndex[j] = locList[i];
				m_nGetLocList++;
				break;
			}
			else if (locList[i] + 1 == m_GetLocationList[j])
			{
				// location was already found in the list
				break;
			}
		}
	}
	SetEvent( DataRequest );
}

void CLADAControlModuleDoc::ResetGetLocList()
{
	memset(m_GetLocationList,0,nInputLocations*sizeof(int));
	m_nGetLocList = 0;
}

void CLADAControlModuleDoc::AddRequest(RequestType r, int whichGroup)
{
	switch (r)
	{
	case GraphRequest:
	case CollectRequest:
		{
			if (!GetLocationRequests.ValueFound(CInputRequest(r,whichGroup)))
			{
				GetLocationRequests.insertAtFront(CInputRequest(r,whichGroup));
				m_nActiveRequests++;
			}
		}
		break;
	case WriteRequest:
		{
			if (!WriteLocationRequests.ValueFound(CInputRequest(r,whichGroup)))
			{
				WriteLocationRequests.insertAtFront(CInputRequest(r,whichGroup));
				m_nActiveRequests++;
			}
		}
		break;
	}
	
}


void CLADAControlModuleDoc::CompleteRequests()
{
	CInputRequest InputRequest;
	CTime theTime = CTime::GetCurrentTime();
	while ( GetLocationRequests.removeFromBack(InputRequest) )
	{
		m_nActiveRequests--;

		if (InputRequest.Request == GraphRequest)
		{
			AddGraphData(theTime);
			UpdateGraphViews();
			//UpdateAllViews(NULL);
		}
		else if (InputRequest.Request == CollectRequest)
		{
			CInputLocFileInfo * ptrInfo = &m_ILData[InputRequest.whichGroup];
			ptrInfo->m_LastReadTime = theTime;
			m_ILData[InputRequest.whichGroup].m_nSuccessfulCollections++;
			
			for (int i = 0; i < ptrInfo->m_nLocations; i++)
			{
				//if (newData[ptrInfo->m_Locations[i]] < -0.001 || newData[ptrInfo->m_Locations[i]] > 1000.0)
				//{
				//	MessageBeep(-1);
				//	MessageBox("Invalid data retrieved.  Press enter to stop program.");
				//	int breakpoint = 1452;
				//}

				if (ptrInfo->m_SaveByAverage)
					ptrInfo->m_tempData[i] += newData[ptrInfo->m_Locations[i]];
				else
					ptrInfo->m_tempData[i] = newData[ptrInfo->m_Locations[i]];
					
			}
			if (ptrInfo->m_SaveByAverage)
				ptrInfo->m_nItemsInTempData++;
			else
				ptrInfo->m_nItemsInTempData = 1;
				
		}

	}
	
	List<CInputRequest> unfulfilledWriteRequests;

	while ( WriteLocationRequests.removeFromBack(InputRequest) )
	{
		CInputLocFileInfo * ptrInfo = &m_ILData[InputRequest.whichGroup];
		if (ptrInfo->m_nItemsInTempData)
		{
			ptrInfo->m_LastSaveTime = theTime;
			WriteInputLocations(ptrInfo);
			m_nActiveRequests--;
		}
		else
		{
			// there is not data for this request available
			// if there is no request to gather this data, then add it,
			// in any case put the request to get this data back...

			// this could happen if two requests are added at the same
			// time, to read and write some input locations, while 
			// data collection is in progress.
			// If this happens the write request will be caught here 
			// before the read request is completed (during the next 
			// cycle).
			unfulfilledWriteRequests.insertAtFront(InputRequest);
			// The next line that checks to see if the value is found should always
			// find it, but in case it doesn't it will insert it...
			if (!GetLocationRequests.ValueFound(CInputRequest(CollectRequest, InputRequest.whichGroup)))
			{
				AddRequest(CollectRequest, InputRequest.whichGroup);
				// display some error message?
				// write to error log
			}
		}
	}

	while ( unfulfilledWriteRequests.removeFromBack(InputRequest) )
	{
		WriteLocationRequests.insertAtFront(InputRequest);	
	}

}

void CLADAControlModuleDoc::AddGraphData(CTime dataTime)
{
	// I don't think this function is used anymore
	PositionTime[GraphDataPos] = dataTime;
		
	memcpy(&GraphData[GraphDataPos * nInputLocations], newData, GraphDataBlockSize);
		
	GraphDataPos++;
		
	if (GraphDataPos >= nBackPoints)
		GraphDataPos = 0;
		
	if (nFilledPoints < nBackPoints)
		nFilledPoints++;
	
}

void CLADAControlModuleDoc::ExecuteInitialCommand()
{
	if (ApplicationIsOpen == FALSE)
		return;

	static BOOL FirstExecution = TRUE;
	static BOOL canceled;
	
	UINT choice = 0;
	
	CStartDialog *StartDialog;
	BOOL ContinueStart = TRUE;
	ApplicationIsOpen = TRUE;

	if (!FirstExecution)
		CleanUp();
	
	while (ContinueStart)
	{
		StartDialog = new CStartDialog(&choice);
		StartDialog->DoModal();
		delete StartDialog;
		
		//if (choice == ID_NORMAL && m_DoWetup == TRUE)
		//choice = ID_WET_UP;

		switch (choice) {
		case ID_SETUP:
			{
				m_History->OpenFiles();
				m_History->WriteHistory("Setup","started.");
				m_History->CloseFiles();

				CLADASetupDlg *test = new CLADASetupDlg();
				if (test->DoModal()==IDOK)
				{
					delete test;
					m_History->OpenFiles();
					m_History->WriteHistory("Setup","completed.");
					m_History->CloseFiles();
					if (MessageBox(IDS_PROCEED_TO_CHECKOUT, IDS_PROGRAM_NAME, MB_YESNO | MB_ICONQUESTION )==IDNO)
						break;
				}
				else
				{
					delete test;
					break;
				}
				
			};
		case ID_CHECK_OUT:
			{
				m_History->OpenFiles();
				m_History->WriteHistory("Check Out","started.");
				m_History->CloseFiles();

				//CCheckOutDlg dlg(CheckOut, this);
				CLADASetupDlg dlg(FALSE,this);
				if (dlg.DoModal()==IDOK)
				{				
					m_History->OpenFiles();
					m_History->WriteHistory("Check Out","completed.");
					m_History->CloseFiles();

					if (m_DoWetup && !m_IsWetupComplete)
					{
						if (MessageBox(IDS_PROCEED_TO_WETUP, IDS_PROGRAM_NAME, MB_YESNO | MB_ICONQUESTION )==IDNO)
							break;
					}
					else
						break;
				}
				else
					break;
			};
		case ID_WET_UP:
			{
				BOOL StartWetup = FALSE;
				
				if (m_DoWetup)
				{
					if ( m_IsWetupComplete == TRUE)
					{
						if (MessageBox(IDS_M_REPEAT_WETUP, IDS_PROGRAM_NAME, MB_YESNO | MB_ICONQUESTION )==IDYES)
							StartWetup = TRUE;
					}
					else
						StartWetup = TRUE;
				}
				else
				{
					// wetup is not part of the project
					MessageBox(IDS_M_WETUP_NOT_IN_PROJECT, IDS_ERROR, MB_ICONWARNING);
				}

				if (StartWetup)
				{
					m_ControlState = SelectWetupSettings;
					ContinueStart = FALSE;
					LoadWetupGraphParameters();

					if (MessageBox(IDS_M_DO_TENSIOMETER,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
					{
						CCheckOutDlg dlg(Tensiometer, this);
						dlg.DoModal();
					}
				}
				
				break;
			}
		case ID_NORMAL:
			{
				m_ControlState = Regular;
				ContinueStart = FALSE;
				break;
			}
		case ID_DIAGNOSTICS: // should be help
			{
				break;
			}
		case ID_EXIT:
			{
				ApplicationIsOpen = FALSE;//false;
				ContinueStart = FALSE;
				return;
			}
		}
	}
	
	StopComm();

	//SetCommStatusWindow(pDoc->ConnectionStatus);
	if (m_pMainView)
	{
		m_pMainView->SetStrings();
		m_pMainView->SetControlModeWindow( m_ControlMode );
		m_pMainView->SetCommStatusWindow( ConnectionStatus );
	}

	//if (m_FrameWnd)
	//{
	//	m_FrameWnd->EnableButton(4, m_ControlState==Regular);
	//}
	// this function doesn't work

	if (!FirstExecution)
	{
		CWinApp * pApp = AfxGetApp( );
		
		if (pApp->m_pMainWnd)
			((CFrameWnd *)pApp->m_pMainWnd)->ActivateFrame();
		
		for (int i = 0; i < nPanes; i++)
		{
			paneModified[i] = TRUE;
		}
		UpdateGraphViews();
	}
	FirstExecution = FALSE;
}

void CLADAControlModuleDoc::PauseAutomaticCommunication()
{
	m_IsCommPaused = TRUE;
}

void CLADAControlModuleDoc::ResumeAutomaticCommunication()
{
	m_IsCommPaused = FALSE;
	SetEvent(CommWakeUpEvent);
	m_pMainView->ResumeTimers();
}



BOOL CLADAControlModuleDoc::GetNewProjectSettings()
{
	//CProjectSettingsDlg newProjectDialog(this);
	//	if (newProjectDialog.DoModal() != IDOK)
	//		return FALSE;
	CNewProject1 p1Dlg(this);
	CNewProject2 p2Dlg(this);
	UINT sValue;
	do 
	{
		if (p1Dlg.DoModal() != IDOK)
			return FALSE;
	
		sValue = p2Dlg.DoModal();
		
		if (sValue == IDCANCEL) // IT SHOULD return IDABORT if <-Back
			return FALSE;

	} while (sValue != IDOK);
	return TRUE;

}

void CLADAControlModuleDoc::LoadWetupGraphParameters()
{
	LoadBackGraphParameters = TRUE;
	// save current graph info into temp variables

	BackGraphCollections = nGraphCollections;
	BackGraphCollection = GraphCollection;
	BackInputLocationList = InputLocationList;
	BackInputLocationNameList = InputLocationNameList;
	BacknInputLocations = nInputLocations;
	BackPaneToCollectionIndex = PaneToCollectionIndex;
	BackM_DoValidation = m_DoValidation;

	GraphCollection = m_WetupInfo.GraphCollection;
	nGraphCollections = m_WetupInfo.nGraphCollections;
	nInputLocations = m_WetupInfo.nInputLocations;
	InputLocationList = m_WetupInfo.InputLocationList;
	InputLocationNameList = m_WetupInfo.InputLocationNameList;
	PaneToCollectionIndex = m_WetupInfo.PaneToCollectionIndex;
	m_DoValidation = m_WetupInfo.m_DoValidation;
}

void CLADAControlModuleDoc::SaveWetupGraphParameters()
{
	LoadBackGraphParameters = FALSE;
	
	// load graph settings back into wetup variables
	
	//m_WetupInfo.nInputLocations = nInputLocations;
	//m_WetupInfo.InputLocationList = InputLocationList;
	//m_WetupInfo.InputLocationNameList = InputLocationNameList;
	//m_WetupInfo.GraphCollection = GraphCollection;
	//m_WetupInfo.PaneToCollectionIndex = PaneToCollectionIndex;
	//m_WetupInfo.
	GraphCollection = BackGraphCollection;
	nGraphCollections = BackGraphCollections;
	nInputLocations = BacknInputLocations;
	InputLocationList = BackInputLocationList;
	InputLocationNameList = BackInputLocationNameList;
	PaneToCollectionIndex = BackPaneToCollectionIndex;
	m_DoValidation = BackM_DoValidation;

	BackGraphCollection = NULL;
	BackInputLocationList = NULL;
	BackInputLocationNameList = NULL;
	BackPaneToCollectionIndex = NULL;
	BackM_DoValidation = NULL;
	BacknInputLocations = 0;
	BackGraphCollections = 0;
}

void CLADAControlModuleDoc::CleanUp()
{
	// since this function could be called while the program is running (by clicking
	// on the close button) we need to disable or discontinue any communication or 
	// active timers.
	if (InCommMode)
	{
		// write to error log...
		// InCommMode == TRUE in CLADAControlModuleDoc::CleanUp()
		StopComm();
	}

	// if wetup was chosen, save the wetup parameters and load back the regular 
	// graph data parameters
	if (LoadBackGraphParameters)
	{
		SaveWetupGraphParameters();
	}
	
	// Clear graph data
	ClearGraphData();

	// Save input location files...
	// only save if there is new information
	CTime theTime = CTime::GetCurrentTime();
	for (int whichGroup = 0; whichGroup < nILFiles; whichGroup++)
	{
		if (m_ILData[whichGroup].m_Do == TRUE &&
			m_ILData[whichGroup].m_nItemsInTempData )
		{
			CInputLocFileInfo * ptrInfo = &m_ILData[whichGroup];
			ptrInfo->m_LastSaveTime = theTime;
			WriteInputLocations(ptrInfo);
		}
	}
}

void CLADAControlModuleDoc::ClearGraphData()
{
	nFilledPoints = 0;
	GraphDataPos = 0;
	memset(PositionTime,0,sizeof(CTime)*nBackPoints);
	memset(newData,0,sizeof(double) * MAX_INPUT_LOCATIONS);
}

BOOL CLADAControlModuleDoc::PerformInitialization(CString &notice)
{
	CWaitCursor wCursor();
	// set final storage write time and frequency and SMP test time and frequency...
	BOOL Success;

	for (int wChamber = 0; wChamber < nFSFiles; wChamber++)
	{
		Success = commObject->SetFinalStorageFrequency(m_FSOutputTable[wChamber].m_wFreqSel,wChamber);
		if (!Success)
		{
			// write to history file, intialization was started and failed
			notice += Strings.get(IDS_M_SET_FS_FAILED) + Strings.get(IDS_CHAMBER_A + wChamber) + "\n";
			return FALSE;
		}
		notice = notice + 
			Strings.get(IDS_M_FINAL_STORAGE_INITIALIZED) + 
			Strings.get(IDS_CHAMBER_A + wChamber) + " " + 
			Strings.get(IDS_N_FSFREQ1+m_FSOutputTable[wChamber].m_wFreqSel) + "\n";
	}

	/*
	CParamDlg pDlg(this);
	if (pDlg.DoModal() == IDOK)
	{
		// parameters updated ...
	}
	else
	{
		// parameters were not updated or comm w/ cr10 failed...
	}
	*/
	return TRUE;
}

BOOL CLADAControlModuleDoc::Connect(BOOL StartTimers, ControlStateType desiredState, BOOL DoInitialization, BOOL FailOnWrongProgram )
{
	if (commObject == NULL)
		commObject = new CCommOperations(this, TRUE);
#ifdef _DEBUG
	else
		MessageBox("Connect in doc called while commObject initialized.","Error",MB_ICONSTOP);
#endif
	
	if (!commObject->IsConnected())
	{
		// If it fails to connect in the constructor, then abort
		StopComm();
		return FALSE;
	}

	ConnectionStatus = Connected;
	if (m_pMainView)
		m_pMainView->SetCommStatusWindow(ConnectionStatus);

	if (!StartDataRetrievalMode(FALSE))
	{
		// start communication thread, but not regular data timers
		StopComm();
		return FALSE;
	}

	// DETECT PASSWORD NOW...
	if (commObject->DetectPassword())
	{
		NotificationBox(IDS_M_PASSWORD_DETECTED, IDS_PROGRAM_NAME);
		// write to error log
		StopComm();
		return FALSE;
	}
	
	Sleep(200);
	// make sure the CR10 is running the correct program
	if ( FailOnWrongProgram && !EnsureCorrectCR10Program(desiredState) )
	{
		if (MessageBox(IDS_M_UNABLE_ENSURE_CORRECT_PROGRAM,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			StopComm();
			return FALSE;
		}
	}

	// make sure the CR10 is in the correct mode, manual or automatic...
	BOOL setModeSuccess = commObject->SetControlMode( m_ControlMode );
	
	if (m_pMainView)
		m_pMainView->SetControlModeWindow( m_ControlMode );

	if (!setModeSuccess)
	{
		MessageBox(IDS_M_UNABLE_SET_CONTROL_MODE,IDS_ERROR,MB_ICONWARNING);
		// write to error log
		return FALSE;
	}

	if (m_pMainView && StartTimers)
	{
		m_pMainView->StartDataTimers();
	}

	//if (DoInitialization && !m_IsCR10Initialized && m_ControlState == Regular)
	//if (DoInitialization && m_ControlState == Regular)
	//{
		//if (MessageBox(IDS_M_INITIALIZE_CR10_NOW,IDS_PROGRAM_NAME,MB_YESNO| MB_ICONQUESTION ) == IDYES)
		//{
		// since Gail doesn't want any initialization to go on, make sure that the
		// CR10X code default values are the ones we use when creating a new project...
		//if (PerformInitialization())
		//{
		//	m_IsCR10Initialized = TRUE;
		//}
	//}
	
	return TRUE;
	
}

BOOL CLADAControlModuleDoc::EnsureCorrectCR10Program(ControlStateType desiredState)
{
	ControlStateType actualState;
	
	if (commObject && commObject->DetermineCR10ProgramType(actualState))
	{
		if (actualState != desiredState)
		{
			CString file = workingDirectory;
			if (workingDirectory[workingDirectory.GetLength() - 1] != '\\')
				file += "\\";
			CString fileName;

			UINT actualProgram;

			if (desiredState == Regular)
				fileName = CString(Strings.get(IDS_REGULAR_PROGRAM_NAME));
			else if (desiredState == StartWetup)
				fileName = CString(Strings.get(IDS_WETUP_PROGRAM_NAME));
			else
			{
				fileName = Strings.get(IDS_M_AN_UNKNOWN_PROGRAM);
				file = "";
			}

			if (actualState == Regular)
				actualProgram = IDS_M_REGULAR_PROGRAM;
			else if (actualState == StartWetup)
				actualProgram = IDS_M_WETUP_PROGRAM;
			else
				actualProgram = IDS_M_AN_UNKNOWN_PROGRAM; 

			// message :
			// CR10X is running { a program for regular operations mode,
			// a program for wetup operation, an unknown program } and should be running
			// { a program for regular operations mode, a program for wetup operation, an 
			// unknown program }.
			// Would you like to load { a program for regular operations mode, a 
			// program for wetup operation, an unknown program } now?
			

			CString message = Strings.get(IDS_M_CR10_IS_RUNNING) + Strings.get(actualProgram)
				+ Strings.get(IDS_M_SHOULD_BE_RUNNING) + ":\n" + fileName + "\n"
				+ Strings.get(IDS_M_WOULD_YOU_LOAD) + " " + fileName + " " + Strings.get(IDS_M_NOW);

			if (MessageBox(message,Strings.get(IDS_PROGRAM_NAME),MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				if (file != "")
					file += fileName;
				if(!commObject->UploadProgram(file))
				{
					CString eng = Strings.get(IDS_M_MISSING_FILE1,ENGLISH) + fileName + Strings.get(IDS_M_MISSING_FILE2,ENGLISH) + workingDirectory;
					CString russ = Strings.get(IDS_M_MISSING_FILE1,RUSSIAN) + fileName + Strings.get(IDS_M_MISSING_FILE2,RUSSIAN) + workingDirectory;
					Strings.set(eng,russ,IDS_TEMP);

					MessageBox(IDS_TEMP, IDS_PROGRAM_NAME, MB_OK);
					return FALSE;
				}
				else
				{
					CString message;
					m_IsCR10Initialized = FALSE;
					if (m_ControlState == Regular && PerformInitialization(message))
					{
						message += "Final storage and SMP test frequency set\n";
						m_IsCR10Initialized = TRUE;
					}
					else
					{
						message += "Final storage and SMP test frequency not set\n";
					}
					
					for (int i = 0; i < nGrowthChambers; i++)
					{
						if (SetControlParameters(i, m_ControlParameters[i].m_MoistureLevel, m_ControlParameters[i].m_24Hour, m_ControlParameters[i].m_LightOnTime, m_ControlParameters[i].m_LightOffTime, m_ControlParameters[i].m_SMPFreq ))
							message += "Setting parameters for chamber 1 successful\n";
						else
							message += "Setting parameters for chamber 1 failed\n";
					}
					// write to history [message]

					if (commObject->DetermineCR10ProgramType(actualState))
					{
						if (actualState != desiredState)
						{
							// write to error log,
							// program x was loaded successfuly, desired mode is[], actual mode is []
							return FALSE;
							//message = Strings.get(IDS_M_FAILED_LOAD_CORRECT_P) + Strings.get(IDS_M_WOULD_YOU_LOAD) + fileName + Strings.get(IDS_M_NOW);
						}
						else
							return TRUE;
					}
					else
					{
						// write to error log
						return FALSE;
					}
				}
				
			}
			else
			{
				return FALSE;
			}

		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		
		//NotificationBox(IDS_M_UNABLE_TO_DETERMINE_P_TYPE, IDS_PROGRAM_NAME);
		// write to error log
		return FALSE;
	}
	
	
}

BOOL CLADAControlModuleDoc::SetControlParameters(int whichChamber, double MoistLevel, BOOL In24Hour, int LightOn, int LightOff, int SMPFreq )
{
	int m_MoistureLocation, m_LightOnLocation, m_LightOffLocation;

	if (whichChamber == 0) // chamber A
	{
		m_MoistureLocation = MOISTURE_CONTROL_A;
		m_LightOnLocation = LIGHT_ON_TIME_A;
		m_LightOffLocation = LIGHT_OFF_TIME_A;
	}
	else
	{
		m_MoistureLocation = MOISTURE_CONTROL_B;
		m_LightOnLocation = LIGHT_ON_TIME_B;
		m_LightOffLocation = LIGHT_OFF_TIME_B;
	}

	double oldValue;

	if (In24Hour)
	{
		LightOff = 25;
		commObject->ControlCR10(On);
	}


	if (commObject->SetLocationAndVerify(m_MoistureLocation,oldValue,ValueToString(MoistLevel).GetBuffer(0)) &&
		commObject->SetLocationAndVerify(m_LightOnLocation,oldValue,IntToString(LightOn).GetBuffer(0)) &&
		commObject->SetLocationAndVerify(m_LightOffLocation,oldValue,IntToString(LightOff).GetBuffer(0)) &&
		commObject->SetSMPTestFrequency(SMPFreq,whichChamber))
	{
		m_ControlParameters[whichChamber].m_MoistureLevel = MoistLevel;
		m_ControlParameters[whichChamber].m_LightOnTime = LightOn;
		m_ControlParameters[whichChamber].m_SMPFreq = SMPFreq;
		m_ControlParameters[whichChamber].m_24Hour = (BOOL)(LightOff > 24);
		if (!In24Hour) // don't set light off time to 25 if in 24 hour mode, retain the real value as if we were not in this mode
			m_ControlParameters[whichChamber].m_LightOffTime = LightOff;
		SetModifiedFlag();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CLADAControlModuleDoc::LoadCameras()
{
	if (cameraDlg == NULL)
	{
		if (m_LastCameraLoadFailed == TRUE)
		{
			// ask the user if they want to load cameras... last time it failed.
			if(MessageBox(IDS_M_LAST_LOAD_FAILED,IDS_PROGRAM_NAME,MB_YESNO|MB_ICONQUESTION)==IDNO)
				return FALSE;
		}
		m_LastCameraLoadFailed = TRUE;
		OnSaveDocument((LPCSTR)GetPathName());
		cameraDlg = new CCamera(this);
		cameraDlg->Create(IDD_CAMERA);
		m_LastCameraLoadFailed = !cameraDlg->m_TwainInitialized;
		OnSaveDocument((LPCSTR)GetPathName());
		if (m_LastCameraLoadFailed)
		{
			// WRITE TO ERROR LOG
			UnloadCameras();
			return FALSE;
		}
		m_AreCamerasLoaded = TRUE;
		return TRUE;
	}
	return FALSE;
}

BOOL CLADAControlModuleDoc::UnloadCameras()
{
	if (cameraDlg != NULL)
	{
		cameraDlg->ReleaseTwain();
		cameraDlg->DestroyWindow();
		cameraDlg = NULL;
	}
	m_AreCamerasLoaded = FALSE;
	return TRUE;
}

void CLADAControlModuleDoc::SaveDataStoragePointer()
{
	CString path = dataFolder + "\\Data Storage Pointer.txt";
	ofstream fout(path);
	fout << LastDSP;
	fout.close();
}

void CLADAControlModuleDoc::LoadDataStoragePointer()
{
	CString path = dataFolder + "\\Data Storage Pointer.txt";
	ifstream fin(path);
	if (!(fin >> LastDSP))
	{
		LastDSP = 1;
	}
	fin.close();
}

BOOL CLADAControlModuleDoc::GetInputLocations(int *ptrFirstLocation, int nLocations, double *ptrReturnData, BOOL useDocIndex)
{
	
	if (!commObject || !InCommMode || !DataRequest)
	{
		MessageBox("Get input location failed.  commObject == NULL or InCommMode == NULL or DataRequest == NULL","Program error",MB_ICONSTOP);
		// if any of these are true it probably means this function is being called before 
		// communication support for this function is 100% initialized...
		return FALSE;
	}

	if (m_IsCommPaused)
	{
		sleepingRequests++;
		WaitForSingleObject(CommWakeUpEvent,INFINITE);
		sleepingRequests--;
		if (sleepingRequests==0)
			ResetEvent(CommWakeUpEvent);
	}

	// START CRITICAL SECTION...
	EnterCriticalSection(&CommCriticalSection);
	if (useDocIndex)
		RequestLocations(ptrFirstLocation,nLocations);
	else
	{
		int locations[MAX_INPUT_LOCATIONS];
		for (int i = 0; i < nLocations; i++)
		{
			locations[i] = InputLocationToIndex[ptrFirstLocation[i]-1];
		}
		RequestLocations(locations,nLocations);
	}
	HANDLE ToBeServicedHandle = ToBeServicedData;
	ThreadsToBeServiced++;
	m_nActiveRequests++;
	WantToGetInputLocation = TRUE;
	// END CRITICAL SECTION...
	LeaveCriticalSection(&CommCriticalSection);
	
	DWORD WaitResult;
	MSG Msg;
	do 
	{
		WaitResult = WaitForSingleObject( ToBeServicedHandle, 20 );
					
		while (WaitResult == WAIT_TIMEOUT && 
			PeekMessage( &Msg,         // message information
			NULL,           // handle to window
			0,//WM_MOUSEFIRST,  // first message  
			0,//WM_MOUSELAST );  // last message
			PM_REMOVE /*| PM_NOYIELD*/)) //wRemoveMsg
			DispatchMessage( &Msg );  // message information);
		DWORD d = WAIT_FAILED;
		if (WaitResult == WAIT_FAILED)
		{
			// write to error log
			MessageBox("WaitForSingleObject in GetInputLocations returned WAIT_FAILED","Error",MB_ICONSTOP);
		}
	}
	while (WaitResult == WAIT_TIMEOUT);

	ThreadsServicing--;
	m_nActiveRequests--;

	if (ThreadsServicing <= 0)
		ResetEvent( ServicingData );
#ifdef _DEBUG
	if (ThreadsServicing < 0)
		MessageBox("ThreadsServicing < 0 in GetInputLocations","Program Error",MB_ICONSTOP);
#endif

	Sleep(0);
	
	if (WaitResult == WAIT_TIMEOUT)
		return FALSE;
	else
	{
		for (int i = 0; i < nLocations; i++)
		{
			if (useDocIndex)
				ptrReturnData[i] = newData[InputLocationList[ptrFirstLocation[i]]];
			else
				ptrReturnData[i] = newData[ptrFirstLocation[i]-1];
		
		}
		return TRUE;
	}
	
	return TRUE;
}

BOOL CLADAControlModuleDoc::StartDataRetrievalMode(BOOL StartTimers)
{
	if (commObject && commObject->IsConnected())
	{
		InCommMode = TRUE;
		m_IsCommPaused = FALSE;
		CommWakeUpEvent = CreateEvent(NULL,TRUE,FALSE,"RESUME_COMM");
		sleepingRequests = 0;

		CWaitTimerInfo * waitInfo = new CWaitTimerInfo;
		waitInfo->commObject = commObject;
		waitInfo->pDoc = this;
		//waitInfo->pView = this;
		waitInfo->InCommMode = &InCommMode;
				
		for (int i = 0; ThreadsInCommWaitTimer && i < 5; i++)
		{
			Sleep(50);
		}
		if (i == 5 && ThreadsInCommWaitTimer)
		{
			MessageBox("Could not create thread for data collection.\nOnly one data thread can exist at a time","Error",MB_OK);
			return FALSE;
		}

		DWORD dwThreadID;
		if (NULL == (hDataRetrievalThread =
				  CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
								0,
								CommWaitTimer,
								(LPVOID) waitInfo,
								0, &dwThreadID )))
		{
			return FALSE;
		}
		else
		{
			if (StartTimers)
			{
				if (m_pMainView)
					m_pMainView->StartDataTimers();
				else
					MessageBox("StartDataTimers == TRUE called in StartDataRetrievalMode with m_pMainView == NULL","Error",MB_ICONSTOP);


			}
						
			return TRUE;
		}	
	}
	return FALSE;
}

void CLADAControlModuleDoc::EndDataRetrievalMode()
{
	DWORD nID = 0;
	if (m_pMainView)
	{
		m_pMainView->KillTimer(UPDATE_GRAPH_TIMER);
		m_pMainView->KillTimer(UPDATE_CR10_TIME);
		
		for (int i = 0; i < nILFiles; i++)
		{
			if (m_ILData[i].m_TimerID)
			{
				m_pMainView->KillTimer(m_ILData[i].m_TimerID);
				m_pMainView->KillTimer(m_ILData[i].m_TimerIDRetrieve);
			}
		}
		if (m_FSCollectionParam.m_TimerID)
			m_pMainView->KillTimer(m_FSCollectionParam.m_TimerID);
	}	
	
	// wait for the current operation to finish...
	InCommMode = FALSE;	
	CloseHandle(CommWakeUpEvent);
	SetEvent( DataRequest );
	for (int i = 0; ThreadsInCommWaitTimer && i < 10; i++)
	{
		Sleep(50);
	}
	if (i == 5 && ThreadsInCommWaitTimer)
	{
		// write to error log... thread for collection would not exit...		
	}
	return;
}