// LADA Control ModuleDoc.cpp : implementation of the CLADAControlModuleDoc class
//

#include "stdafx.h"
#include "LADA Control Module.h"

#include "LADA Control ModuleDoc.h"
#include "ProjectSettingsDialog.h"
#include "LADA Control ModuleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char *AdditionalMessage = NULL);
extern int  curLanguage;
extern CLADAControlModuleApp theApp;
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
: backgroundBrush(RGB(200, 200, 255))
{
	InCommMode = FALSE;
	// TODO: add construction code here
	DataTimer = NULL;
	NewDataExists = FALSE;
	curWindow = -1;
	penThickBlack.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	penThinBlack.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	penThinGray.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	pens = new CPen[15];
	colors = new COLORREF[15];
	colors[0] = RGB(255,0,0);
	colors[1] = RGB(0,255,0);
	colors[2] = RGB(0,0,255);
	colors[3] = RGB(255,255,0);
	colors[4] = RGB(255,0,255);
	colors[5] = RGB(0,255,255);
	colors[6] = RGB(128,0,0);
	colors[1] = RGB(0,128,0);
	colors[7] = RGB(0,0,128);
	colors[9] = RGB(128,255,0);
	colors[10] = RGB(128,0,255);
	colors[11] = RGB(0,128,255);
	colors[12] = RGB(255,128,0);
	colors[13] = RGB(255,0,128);
	colors[14] = RGB(0,255,128);

	for (int whichPen = 0; whichPen < 15; whichPen++)
		pens[whichPen].CreatePen(PS_SOLID, 1, colors[whichPen]);
	GraphData = 0;
	PositionTime = 0;
	InputLocationNameList = 0;
	InputLocationSaveList = 0;
	tempArray = 0;
	commObject = NULL;
	InitCommSynchronization();
	DocInitialized = FALSE;

	ThreadsInFunction = 0;
	ThreadsInCommunication = 0;
	DelayTime = 0;
	ThreadsInStartBlock = 0;
}

CLADAControlModuleDoc::~CLADAControlModuleDoc()
{
// These objects are deleted by DeleteContents, which
	// is called when the document is closed
	/*
	delete [] GraphData;
	delete [] PositionTime;
	delete [] InputLocationNameList;
	delete [] InputLocationSaveList;
	delete [] tempArray;
	delete [] ItemChecked;
	delete [] DataIndex;
	*/
	
	delete [] pens;
	delete [] colors;
	delete commObject;
}

void AssociateFSLFile(char (*InputLocNameList)[2][30], CString filename = ""){
	
	filename.Replace( ".dld", ".fsl" );
	CString smallFileName = filename;

	if (filename == ""){
		CFileDialog OpenFileDialogBox(TRUE, "fsl", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			"Final Storage Label Files (*.fsl, *.csi)|*.fsl;*.csi|All Files (*.*)|*.*||",
			NULL);
		OpenFileDialogBox.m_ofn.lpstrTitle = "Choose fsl or csi file";
		UINT success = OpenFileDialogBox.DoModal();
		//this->UpdateWindow();

		if ( success == IDOK){
			filename = OpenFileDialogBox.GetPathName();
			smallFileName = OpenFileDialogBox.GetFileName();
		}
		else
			return;
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
			if (AfxMessageBox("No matching FSL file found.  Browse for FSL file to associate?",
				MB_YESNO | MB_ICONQUESTION) 
				== IDYES)
			{
				AssociateFSLFile(InputLocNameList);
			}
		}
		else
			DisplayErrorMessage(LError);
		return;
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

	for (int i = 0; i < fileSize; i++){
		curChar = fileBuff[i];
		
		if (curChar == 'O'){
			if (strncmp(&fileBuff[i],"Output_Table",12) == 0)
				break;
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
					char nameBuff[27];
					wsprintf(nameBuff,"%3i:%s", whichLoc, newName);
					//InputLocNameList[whichLoc - 1] = nameBuff;
					strcpy(InputLocNameList[whichLoc - 1][curLanguage],nameBuff);
					ignoreInput = FALSE;
					whichLoc = 0;
					CurrNumber = 0;
					wordPos = 0;
				}
				else
					break; // that means we are probably done
					// reading input locations, if there was no
					// number read on this line.
			}
		}
		else if (curChar == 'I'){
			if (strncmp(&fileBuff[i],"Input_Storage",13) == 0 ||
				strncmp(&fileBuff[i],"Input Locations", 15) == 0){
				FoundInputStorageStart = TRUE;
				i += 12;
				while (fileBuff[++i] != '\n');
				
			}
		}
	}
	delete fileBuff;
	//SetInputLocationsNamesText();
	
}

BOOL CLADAControlModuleDoc::OnNewDocument()
{
	if (!DocInitialized){
		// the only case when the document is not initialized is if no
		// document has been loaded.  this can happen in OnNewDocument is 
		// called by default, when no previous document is detected.
		// In this case the user may want to load a different document.  
		// We should ask them.
		UINT dChoice = AfxMessageBox("There is no previous configuration detected.\n"
					  "Do you wish to create a new configuration?",MB_YESNO);
		if (dChoice == IDNO)
		{
			// we need to figure out which file to open and then call serialize ourselves...
			CFileDialog OpenFileDialogBox(TRUE, ".lada", NULL, 
				OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
				"Lada Config Program (*.lada)|*.lada|",NULL);
		 
			UINT success = OpenFileDialogBox.DoModal();
		
			if ( success == IDOK){
				CString filename = OpenFileDialogBox.GetPathName();
				
				return TRUE;
			}
			return FALSE;
		}
	}

	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	InputLocationNameList = new InputListType[MAX_INPUT_LOCATIONS];
	InputLocationSaveList = new int[MAX_INPUT_LOCATIONS];
	nData = 0;
	
	for (int i = 1; i <= MAX_INPUT_LOCATIONS; i++){
		wsprintf(InputLocationNameList[i - 1][ENGLISH], "%3i:[no name]", i);
		wsprintf(InputLocationNameList[i - 1][RUSSIAN], "%3i:[ÍÀÇÂÀÍÈß ÍÅÒ]", i);
	}//YFPDFYBZ YTN

	CProjectSettingsDlg newProjectDialog(this);
	newProjectDialog.DoModal();
	
	CString fullFilePath = dataFolder + "\\" + projectOptionsFile;
	SetPathName(fullFilePath);

	ItemChecked = new BOOL[numGraphs][15];
	DataIndex = new int[numGraphs][15];
	nDataGraph = new int[numGraphs];
	for (i = 0; i < maxGraphItems; i++){
		for (int j = 0; j < numGraphs; j++){
			DataIndex[j][i] = i;
			ItemChecked[j][i] = FALSE;
		}
	}
	graphListModified = new BOOL[numGraphs];
	for (i = 0; i < numGraphs; i++){
		nDataGraph[i] = 0;
		graphListModified[i] = TRUE;
	}
	OnStartNewDocument();
	m_FloppyDefault = "A:\\";
	m_PcmciaDefault = "D:\\";
	OnSaveDocument((LPCSTR)GetPathName());

	return TRUE;
}

void CLADAControlModuleDoc::FillWithRandomData()
{
	CTime fakeTime = CTime::GetCurrentTime();
	double * Array = new double[nData];
	while (nFilledPoints < 500){
		for (int j = 0; j < nData; j++){
			Array[j] = rand() % 10 + j / 10 * (rand() % 2 + 2);
		}
		AddData(Array, fakeTime);
		fakeTime += CTimeSpan( 0, 0, 0, 1 ); 
	}
	delete [] Array;
}

void CLADAControlModuleDoc::WriteInputLocations()
{
	CTime theTime = CTime::GetCurrentTime();

	if (ILFileOut == NULL){
		char fileNameBuff[_MAX_PATH];
		CString s = theTime.Format( "%H;%M;%S, %B %d, %Y" );
		wsprintf(fileNameBuff,"%s\\Input Loc Data %s.dat", dataFolder, s);
		CTime lastFileCreationTime = theTime;
		ILFileOut = CreateFile(fileNameBuff, 
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_ARCHIVE, 
		NULL);
		if (ILFileOut == INVALID_HANDLE_VALUE){
			CloseHandle(ILFileOut);
			ILFileOut = NULL;
			DisplayErrorMessage(GetLastError());
			return;
		}
	}
	
	int d1, d2;
	double result;
	char FileOutText[20];
	char FileOutBuff[3000];
	int FileBuffPos = 0;

	CString tTime = theTime.Format("%m,%d, %H:%M, ");
	wsprintf(FileOutText,"%s",tTime);
	strcpy(&FileOutBuff[FileBuffPos], FileOutText);
	FileBuffPos += strlen(FileOutText);

	DWORD bytesWritten;
	for (int i = 0; i < nData; i++){
		result = tempSaveData[i];
		d1 = int(result);
		d2 = int((result - double(d1)) * 10000.0);
		wsprintf(FileOutText,"%i.%04i,",d1,d2);
		strcpy(&FileOutBuff[FileBuffPos], FileOutText);
		FileBuffPos += strlen(FileOutText);
	}
	
	FileOutBuff[FileBuffPos++] = '\r';
	FileOutBuff[FileBuffPos++] = '\n';
	if (!WriteFile(ILFileOut, FileOutBuff, FileBuffPos, &bytesWritten, NULL))
		DisplayErrorMessage(GetLastError());

	if (theTime - lastFileCreationTime >= newFileFreq){
		CloseHandle(ILFileOut);
		ILFileOut = NULL;
		lastFileCreationTime = theTime;
	}
}


void CLADAControlModuleDoc::AddData(double data[], CTime dataTime, BOOL UpdateViews )//=TRUE
{

	
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

	//if (UpdateViews)
	//	UpdateAllViews(NULL);
}

double CLADAControlModuleDoc::GetDataValue(int whichGraph, int whichData, int Position)
{
	return GraphData[Position * nData + DataIndex[whichGraph][whichData]];
}

const char * CLADAControlModuleDoc::GetDataName(int whichGraph, int whichData)
{
	return InputLocationNameList[DataIndex[whichGraph][whichData]][curLanguage];
}

CString CLADAControlModuleDoc::GetPositionLabel(int Position)
{
	return PositionTime[Position].Format("%H:%M:%S");
}


/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleDoc serialization

void CLADAControlModuleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		UINT iSize = MAX_INPUT_LOCATIONS * sizeof(int);
		ar.Write(InputLocationSaveList, iSize);
		iSize = MAX_INPUT_LOCATIONS * sizeof(InputListType);
		ar.Write(InputLocationNameList,iSize);
		iSize = sizeof(LONG);
		LONG timeSpan = dataRetrievalFreq.GetTotalSeconds();
		ar.Write(&timeSpan,iSize);
		timeSpan = dataPlotFreq.GetTotalSeconds();
		ar.Write(&timeSpan,iSize);
		timeSpan = dataWriteFreq.GetTotalSeconds();
		ar.Write(&timeSpan,iSize);
		timeSpan = newFileFreq.GetTotalSeconds();
		ar.Write(&timeSpan,iSize);
		iSize = sizeof(int);
		ar.Write(&nBackPoints,iSize);
		ar.Write(&newFileSize,iSize);
		ar.Write(&nData,iSize);
		ar.Write(&numGraphs,iSize);
		//ar.Write(&maxGraphItems,iSize);
		iSize = sizeof(BOOL);
		ar.Write(&saveByAverage,iSize);
		ar.Write(&saveFinalStorage,iSize);
		ar.Write(&saveByTime,iSize);
		ar.Write(&saveLocations,iSize);
		ar.Write(&numGraphs,iSize);
		ar.WriteString(dataFolder);
		ar.WriteString( "\n" );
		ar.WriteString(projectOptionsFile);	
		ar.WriteString( "\n" );
		ar.WriteString(m_FloppyDefault);
		ar.WriteString( "\n" );
		ar.WriteString(m_PcmciaDefault);
		ar.WriteString( "\n" );
		iSize = sizeof(int) * 15;
		for (int i = 0; i < numGraphs; i++){
			ar.Write( DataIndex[i], iSize );
			ar.Write( &nDataGraph[i], sizeof(int) );
			ar.Write( ItemChecked[i], iSize );
		}
		
	}
	else
	{
		// TODO: add loading code here
		InputLocationNameList = new InputListType[MAX_INPUT_LOCATIONS];
		InputLocationSaveList = new int[MAX_INPUT_LOCATIONS];
		UINT iSize = MAX_INPUT_LOCATIONS * sizeof(int);
		ar.Read(InputLocationSaveList, iSize);
		iSize = MAX_INPUT_LOCATIONS * sizeof(InputListType);
		ar.Read(InputLocationNameList,iSize);
		iSize = sizeof(LONG);
		LONG timeSpan;
		ar.Read(&timeSpan,iSize);
		dataRetrievalFreq = CTimeSpan(time_t(timeSpan));
		ar.Read(&timeSpan,iSize);
		dataPlotFreq = CTimeSpan(time_t(timeSpan));
		ar.Read(&timeSpan,iSize);
		dataWriteFreq = CTimeSpan(time_t(timeSpan));
		ar.Read(&timeSpan,iSize);
		newFileFreq = CTimeSpan(time_t(timeSpan));
		iSize = sizeof(int);
		ar.Read(&nBackPoints,iSize);
		ar.Read(&newFileSize,iSize);
		ar.Read(&nData,iSize);
		ar.Read(&numGraphs,iSize);
		//ar.Read(&maxGraphItems,iSize);
		maxGraphItems = 15;
		iSize = sizeof(BOOL);
		ar.Read(&saveByAverage,iSize);
		ar.Read(&saveFinalStorage,iSize);
		ar.Read(&saveByTime,iSize);
		ar.Read(&saveLocations,iSize);
		ar.Read(&numGraphs,iSize);
		ar.ReadString(dataFolder);
		ar.ReadString(projectOptionsFile);
		ar.ReadString(m_FloppyDefault);
		ar.ReadString(m_PcmciaDefault);
		iSize = sizeof(int) * maxGraphItems;
		DataIndex = new int[numGraphs][15];
		ItemChecked = new BOOL[numGraphs][15];
		nDataGraph = new int[numGraphs];
		
		for (int i = 0; i < numGraphs; i++){
			ar.Read( DataIndex[i], iSize );
			ar.Read( &nDataGraph[i], sizeof(int) );
			ar.Read( ItemChecked[i], iSize );
		}

		OnStartNewDocument();
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
	
	if (fileOut == INVALID_HANDLE_VALUE){
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

void CLADAControlModuleDoc::ToggleData(int whichWindow, int whichButton)
{
	ItemChecked[whichWindow][whichButton] = (
		ItemChecked[whichWindow][whichButton] ?
	FALSE :
	TRUE);
}

BOOL CLADAControlModuleDoc::IsItemChecked(int whichWindow, int whichButton)
{
	return ItemChecked[whichWindow][whichButton];
}
/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleDoc diagnostics

#ifdef _DEBUG
void CLADAControlModuleDoc::AssertValid() const
{
	CDocument::AssertValid();
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
	StopComm();
	CString filePath = GetPathName();
	if (filePath != ""){
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
	if (GraphData) {
		delete [] GraphData;
		delete [] PositionTime;
		delete [] InputLocationNameList;
		delete [] InputLocationSaveList;
		delete [] tempArray;
		delete [] newData;
		delete [] ItemChecked;
		delete [] DataIndex;
		delete [] nDataGraph;
		delete [] tempSaveData;
		delete [] graphListModified;
	}
	curWindow = -1;
	nFilledPoints = 0;
	maxGraphItems = 15;
	GraphDataPos = 0;
	GraphData = NULL;
	PositionTime = NULL;
	tempArray = NULL;
	newData = NULL;
	nItemsInTempArray = 0;
	ItemChecked = NULL;
	DataIndex = NULL;

}

BOOL CLADAControlModuleDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	//AfxMessageBox("Hello");
	// TODO: Add your specialized creation code here
	DocInitialized = TRUE;
	return TRUE;
}

void CLADAControlModuleDoc::UpdateGraphViews()
{
	for (int i = 0; i < numGraphs; i++)
	{
		((CLADAControlModuleView *)pGraphView[i])->OnUpdate(pGraphView[i],1,NULL);
		//pGraphView[i]->InvalidateRect(NULL,FALSE);
	}
}

void CLADAControlModuleDoc::InitCommSynchronization()
{
	CommSyncObject = CreateEvent(NULL,TRUE,TRUE,"COMMSYNCRONIZATION");
}

void CLADAControlModuleDoc::StartCommBlock()
{
	// waits until the object is in the signaled state.
	// it is signaled when comm is clear
	ThreadsInStartBlock++;
	DWORD waitPeriod = 1000 * 60 * 3; // 3 minutes // INFINITE
	DWORD waitResult = WaitForSingleObject(  CommSyncObject, waitPeriod );
	ResetEvent( CommSyncObject ); // sets event to non-signaled state.
	if (waitResult == WAIT_TIMEOUT)
	{
		// we had to wait 3 minutes and the communication ready signal was never set
		// do some error handling routine.
		// reset comm. with CR10?


	}
	ThreadsInStartBlock--;
}

BOOL CLADAControlModuleDoc::StopComm()
{
	
	InCommMode = FALSE;
	
	// DON'T KILL COMM STRUCTURES IN THE MIDDLE OF RETRIEVING DATA
	CWaitCursor wait;
	DWORD interval = 1000 * 15; // 15 seconds
	WaitForSingleObject(CommSyncObject, interval);
	/*
	if (DataTimer){
		HANDLE hArray[] = { &DataTimer, &CommSyncObject};
		// WAIT FOR EITHER THE TIMER TO BE SIGNALED AGAIN, OR FOR COMM TO FINISH.
		WaitForMultipleObjects(  2,             // number of handles in array
			hArray,  // object-handle array
			FALSE,            // wait option
			1000      // time-out interval
		);
	}
	*/
	if (commObject)
	{
		commObject->EndCR10Comm();
		delete commObject;
		commObject = NULL;
	}
	return TRUE;
}

void CLADAControlModuleDoc::EndCommBlock()
{
	SetEvent( CommSyncObject ); // sets event to signaled state.
}

void CLADAControlModuleDoc::OnStartNewDocument()
{

	nFilledPoints = 0;
	nFilledSaveData = 0;
	maxGraphItems = 15;
	if (nData < maxGraphItems)
			maxGraphItems = nData;

	GraphDataPos = 0;
	GraphData = new double[nData * nBackPoints];
	GraphDataBlockSize = sizeof(double) * nData;
	PositionTime = new CTime[nBackPoints];
	tempArray = new double[nData];
	tempSaveData = new double[nData];
	newData = new double[nData];
	for (int i = 0; i < nData; i++)
		newData[i] = 0.0;
	nItemsInTempArray = 0;
	graphListModified = new BOOL[numGraphs];
	for (i = 0; i < numGraphs; i++){
		graphListModified[i] = TRUE;
	}
	
	DoAutoWrap = FALSE;
		
	lastFileCreationTime = lastSaveTime = CTime::GetCurrentTime();
	ILFileOut = NULL;
	DocInitialized = TRUE;


}
