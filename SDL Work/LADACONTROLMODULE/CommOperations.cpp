// CommOperations.cpp: implementation of the CCommOperations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LADA Control Module.h"
#include "CommOperations.h"



//#include <afxwin.h>
//#include <afx.h>
//#include "CR10 Talk Main.h"
//#include "resource.h"
#include <math.h>

//#include "MonitorDlg.h"
//#include "FlagsDialog.h"
#include "ProgressDialog.h"
//#include "RenameLocation.h"
//#include "EditEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
//  Global functions

CString BrowseForFolder(LPCSTR lpszTitle, UINT nFlags, LPCITEMIDLIST pidlRoot, CWnd *parentWnd)
{

	CString strResult;

	//LPMALLOC lpMalloc;
	//if (::SHGetMalloc(&lpMalloc) != NOERROR)
	//	return strResult;

	char szDisplayName[_MAX_PATH];
	char szBuffer[_MAX_PATH];

	BROWSEINFO bi;

	bi.hwndOwner = parentWnd->GetSafeHwnd();
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szDisplayName;
	bi.lpszTitle = lpszTitle;
	bi.ulFlags = nFlags;
	bi.lpfn = NULL;
	bi.lParam = 0;

	LPITEMIDLIST lpItemIDList;// = new ITEMIDLIST;

	if ((lpItemIDList = ::SHBrowseForFolder(&bi)) != NULL)
	{
		if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
		{
			if (szBuffer[0] == '\0')
			{
				//AfxMessageBox(IDP_FAILED_GET_DIRECTORY,MB_ICONSTOP|MB_OK);
				return strResult;
			}
			strResult = szBuffer;
			return strResult;
		}
	}
	else
	{
		//AfxMessageBox(IDP_FAILED_GET_DIRECTORY,MB_ICONSTOP|MB_OK);
		return strResult;
	}

	return strResult;
}

void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char *AdditionalMessage = NULL){
	if (ErrorNum){
	
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			ErrorNum,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		char messageString[100];
		messageString[0] = '\0';

		if (showNum)
			wsprintf(messageString,"Error %i\n",ErrorNum);
		strcat(messageString,(LPCTSTR)lpMsgBuf);
		//wsprintf(messageString,"%s%s",messageString,(LPCTSTR)lpMsgBuf);
		if (AdditionalMessage)
			strcat(messageString,AdditionalMessage);
		//wsprintf(messageString,"%s%s",messageString,AdditionalMessage);

		AfxMessageBox( messageString,  MB_OK | MB_ICONINFORMATION );
		// Free the buffer.
		LocalFree( lpMsgBuf );
	}
}


void iToString(int number, int exponent, char *s, bool isNeg = false){// = false
	static int pos;
		
	if (number < 0){
		number *= -1;
		isNeg = true;
	}
	pos = 0;
	char lastdigit = number % 10 + '0';

	++exponent;
	if (number > 9)
		iToString(number / 10, exponent, s, isNeg);
	
	if (number < 10 && isNeg)
		s[pos++] = '-';
	if (exponent == 0){
		if (pos == 0 || (pos == 1 && isNeg))
			s[pos++] = '0';
		s[pos++] = '.';
	}
	s[pos++] = lastdigit;
	s[pos] = '\0';
}

void SortDescending( int array[], int n ){
	int temp;
	for (int pass = 0; pass < n - 1; pass++){
		for (int i = n - 2; i >= 0; i--){
			if (array[i] < array[i + 1]){
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}

void SortAscending( int array[], int n ){
	int temp;
	for (int pass = 0; pass < n - 1; pass++){
		for (int i = 0; i < n - 1; i++){
			if (array[i] > array[i + 1]){
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommOperations::CCommOperations( BOOL ShowMessage ) // = TRUE
{
	defaultPort = 0;
	//if (AfxMessageBox("Connect to CR10 now?", MB_YESNO | MB_ICONQUESTION ) == IDYES )
	Connect(ShowMessage);
	FSFileOut = NULL;
	//programStartTime = timeGetTime();
	//ProgramRunTime = 0;	
}

CCommOperations::~CCommOperations()
{

}


//************************************************************
// GLOBAL DATA

//	  TO BE RETAINED IN A FILE
 //int   InputLocScreenList[MAX_DISPLAY_INPUT_LOCATIONS];
 
 BOOL  UpdateItems[N_UPDATEABLE_ITEMS];
 //int   FreqLevel[N_UPDATEABLE_ITEMS];
 //int   InputLocScreenRequests;
 
 int   LastDSP;
 BOOL  FStartRetrievalFromCurrentPosOnStart;
 int   defaultPort;
 CString  AvailableInputLocations[MAX_INPUT_LOCATIONS];
 int   toggleFlags[8][2];
 BOOL  DoToggleFlags[2];
 int   ModifyWhichFlags;
 CString  FlagNames[8][2];
 int   toggleFlagsFreqLevel[8][2];
 BOOL  SaveFinalStorage;
 //int   nPEvents;

//    USED ONLY DURING PROGRAM EXECUTION
 char  *readBuf;
 int   readBufPos;
 BOOL  dataReceived;
 int   reconnects = 0;				// RECONNECTS
 DWORD programStartTime = 0;
 
 int   FreqTable[16] = {1, 2, 5, 10, 30, 60, 120, 300, 600, 1800, 3600, 10800, 21600, 86400, 259200, 604800};
 int   FilledLocations;
 int   DSP;
 BOOL  FlagStatus[8][2];
 int   consecReconnects;
 BOOL  GetFSUnderWay = FALSE;
 DWORD LastAutoUpdateTime = 0;
 /*
 const char *Frequencies[16] = {
	"1 Second","2 Seconds","5 Seconds","10 Seconds",
	"30 Seconds","1 Minute","2 Minutes","5 Minutes",
	"10 Minutes","30 Minutes","1 Hour","3 Hours",
	"6 Hours","1 Day","3 Days","1 Week"};
 int FlagWindowCount = 0;
 */
   //char  inputWindowText[15][10] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

 BOOL  NeedSetJCommand = TRUE;
 int   ProgramRunTime;
 int   ProgramCounter;
 
 COMSTAT ComStat;
// stuff used for debug info
 int   readNum = 0;
 DWORD timer[8];
 int   writeSize = 0;
 int   WCBuffRepeats = 0;   // WCBUFF_REPEATS
 //int   writesTotal = 0;		// WRITE_OPS
 DWORD longestDelay = 0;  // LONGEST_DELAY
 int   timeOuts = 0;		//TIME_OUTS
 DWORD lastReadTime;




BOOL CCommOperations::CheckSignature
	   (int checkPos, SigType SignatureType,
		char *buffer, int bytesToCheck,
		unsigned char sigByte1, 
		unsigned char sigByte2)
{
	if ((SignatureType == FINALSTORAGE) || 
		(SignatureType == DOWNLOADPROGRAM) || 
		(buffer[readBufPos - 3] == char(0x00) && 
		buffer[readBufPos - 4] == char(0x7F)) ){
		
		unsigned char S1 = 0xAA;
		unsigned char S0 = 0xAA;
		unsigned char T1;
		unsigned char T2;
	
		for (;checkPos < bytesToCheck; checkPos++){
			//2.
			T1 = S1;
			S1 = S0;
			//3.
			T2 = (S0 << 1) + S0 / 0x80;
			//4.
			S0 = T2 + T1 + (unsigned char)buffer[checkPos];
		}
		if (S1 == sigByte1 && S0 == sigByte2){
			//SetWindowNumber( IDC_SIGNATURE, 1);
			return TRUE;
		}
	}
	//SetWindowNumber( IDC_SIGNATURE, 0);
	return FALSE;
}

BOOL CCommOperations::Connect(BOOL ShowMessage){ // = TRUE;
// Open a connection and ping until you find which comport works

	if (CONNECTED(TalkInfo)){
		AfxMessageBox("Communication already established with CR10");
		return TRUE;
	}

	if ( defaultPort != 0){ 
		PORT(TalkInfo) = defaultPort;
		char errMessage[100];
		do {
			// there is a default port.  try it first
			if (OpenConnection()){
				if (PingCR10(500)||PingCR10(1000)||PingCR10(2000))
					return TRUE;
				CloseConnection();
			}
			
			
			wsprintf(errMessage,"Communication with CR10 on could not\n"
								"be established on COM%i.  Attempt again?", defaultPort);
		} while (AfxMessageBox(errMessage,MB_YESNO | MB_ICONQUESTION ) == IDYES);
	}
	for (int p = 1; p < 5; p++){
		if (p == defaultPort)
			p++;
		if (p == 5)
			break;
		PORT( TalkInfo ) = p;
		if (OpenConnection()){
			if (PingCR10(500)||PingCR10(1200)||PingCR10(2000)){
				defaultPort = p;
				return TRUE;
			}
			CloseConnection();
		}
		else {
			DWORD lError = GetLastError();
			if (lError && lError != 2) // File not found error, in this case, port not found)
				DisplayErrorMessage(lError);
		}
	}
	if (ShowMessage)
		AfxMessageBox("Unable to communicate with CR10", MB_ICONEXCLAMATION );
	PORT( TalkInfo ) = defaultPort;
	return FALSE;
	
}

int CCommOperations::DownloadProgram(CString filename){
	//open the file
	// if no filename is provided, ask the user which file to download
	if (!CONNECTED( TalkInfo )){
		AfxMessageBox ("No connection to CR10 present",MB_ICONEXCLAMATION);
		return FALSE;
	}

	CString smallFileName = filename;

	if (filename == ""){
		
		CFileDialog OpenFileDialogBox(TRUE, "dld", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			"Data logger program (*.dld)|*.dld|All Files (*.*)|*.*||",
			NULL);
		 
		UINT success = OpenFileDialogBox.DoModal();
		//this->UpdateWindow( );

		if ( success == IDOK){
			filename = OpenFileDialogBox.GetPathName();
			smallFileName = OpenFileDialogBox.GetFileName();
		}
		else
			return success;
	}
				 
	HANDLE fileIn = CreateFile(filename, 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileIn == INVALID_HANDLE_VALUE){
		DisplayErrorMessage(GetLastError());
		AfxMessageBox("Error accessing file",MB_ICONEXCLAMATION);
		return FALSE;
	}

	DWORD fileSize = GetFileSize(fileIn, NULL);
	
	// set up progress box
	BOOL downloadCancelled;
	char wText[100];
	wsprintf(wText,"Downloading %s to the CR10", smallFileName);
	ProgressDialog DownloadProgress(&downloadCancelled, wText, "Downloading dld file...");
	DownloadProgress.Create(PROGRESS_DIALOG);

	//send the file
	char *fileBuff = new char[fileSize + 1];
	DWORD bytesRead;
	ReadFile(fileIn,fileBuff,fileSize,&bytesRead,NULL);
	char SendBuff[TRANSMIT_SIZE + 10];
	
	readBufPos = 0;
	Send("7H\r*D2\r",7);

	
	int cArray[40];
	
	for (int i = 0; i < 5; i++){
		Sleep(15);
		cArray[i] = readBufPos;
		if (readBufPos > 31) break;
	}
	Sleep(20);
	
	BOOL opFailed = FALSE;
	//if(!WaitOnChar("<>",250, &downloadCancelled))
	//	opFailed = TRUE;	
	
	if (!opFailed)
	{
		int fileBufPos = 0;
		int sendSize;
		int fileLeft = fileSize;

		if (fileBuff[fileSize - 2] == char(0x05)){
			fileLeft -= 2;
			fileSize -= 2;
		}
		// do not send the last two characters in the file
		// if the are 5 hex, that will be done later.

		do {
			if (downloadCancelled){
				opFailed = TRUE;	
				break;
			}
			//wsprintf(SendBuff,"%s",&fileBuff[fileBufPos]);
			//strcpy(SendBuff, &fileBuff[fileBufPos]);
			sendSize = min(fileLeft, TRANSMIT_SIZE);
			
			memcpy(SendBuff,&fileBuff[fileBufPos],sendSize);

			SendBuff[sendSize] = char(0x03);
			SendBuff[sendSize + 1] = char(0x03);
			
			readBufPos = 0;
			Send(SendBuff, sendSize + 2);

		
			for (int i = 0; i < 10; i++){
				Sleep(15);
				cArray[i] = readBufPos;
				if (readBuf[readBufPos - 1] == '<' || readBuf[readBufPos - 1] == '>')
					break;
				if (downloadCancelled) i = 10;
			}
			if (i == 10){
				opFailed = TRUE;	
				break;
			}

			//CheckSignature;
			BOOL SigValue = CheckSignature(0,DOWNLOADPROGRAM,
				&fileBuff[fileBufPos], sendSize, 
				(unsigned char) readBuf[readBufPos - 3], 
				(unsigned char) readBuf[readBufPos - 2]);
			
			if (SigValue){
				// if signature is good, then
				fileBufPos += sendSize;
				fileLeft -= sendSize;
				DownloadProgress.SetInfo(100 - 100 * fileLeft / fileSize);

				if (fileLeft == 0)
					break;
				
				// continue the load operation.  
				// load the current buffer and reset signature
				SendBuff[0] = char(0x04);
				SendBuff[2] = '<';
				SendBuff[3] = '\0';
				
				for (int t = 0; t < 2 && !downloadCancelled; t++){
					readBufPos = 0;
					SendBuff[1] = char(0x04); 
					Send(SendBuff, 2);
					SendBuff[1] = '>';
					
					char whichChar = WaitOnChar(SendBuff, 8000, &downloadCancelled);
					if (whichChar == '<' || whichChar == '>')
						break;
				} 
				if (t == 2 || downloadCancelled){
					opFailed = TRUE;	
					break;
				}
			}
			else { // signature was bad
				SendBuff[0] = char(0x02);
				SendBuff[2] = '<';
				SendBuff[3] = '\0';

				for (int t = 0; t < 2 && !downloadCancelled; t++){
					readBufPos = 0;
					SendBuff[1] = char(0x02);
					Send(SendBuff, 2);
					SendBuff[1] = '>';

					char whichChar = WaitOnChar(SendBuff, 3000, &downloadCancelled);
					if (whichChar == '<' || whichChar == '>')
						break;
				}
				if (t == 2 || downloadCancelled){
					opFailed = TRUE;	
					break;
				}
			}

		} while (fileLeft > 0);

		if (!opFailed){
			DownloadProgress.SetInfo(100, "File downloaded.  CR10 compiling dld file...");
			SendBuff[0] = char(0x05); 
			readBufPos = 0;
			SendBuff[1] = char(0x05); 
			Send(SendBuff, 2);
			SendBuff[1] = '>';
			SendBuff[2] = '\0';
				
			for (int t = 0; t < 2; t++){
				char whichChar = WaitOnChar(SendBuff, 8000, &downloadCancelled);
				if (whichChar == '<' || whichChar == '>')
					break;
			} 
			if (t == 2 || downloadCancelled)
				opFailed = TRUE;	
			
		} // !opFailed
	} // !opFailed
	

	Send("*",1);
	Sleep(20);
	Send("0",1);
	WaitOnChar("*",1000, &downloadCancelled);
	DownloadProgress.Close();	
	CloseHandle( fileIn );  // handle to object);
	/*
	if (!opFailed){
		if (AfxMessageBox("Derive input location names from an FSL file?",
			MB_YESNO | MB_ICONQUESTION) 
			== IDYES)
			AssociateFSLFile(smallFileName);
	}
	*/
	return !opFailed;

}

BOOL CCommOperations::EndCR10Comm(){
		
	DWORD dwErrorFlags;
	ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
	//DWORD LASTError = GetLastError();
	//
	//if (LASTError != 0)
	//	DisplayErrorMessage(LASTError);
	return CloseConnection();
}

BOOL CCommOperations::ExecuteACommand(int *data){

	if (PingCR10(20) || PingCR10(500) || PingCR10(1000)){
		// give it 5 tries
		for (int t = 0; t < 5; t++){
			readBufPos = 0;
			Send("1A\r",3);
			for (int i = 0; i < 10; i++) {
				Sleep (10);
				if (readBufPos > 53)
					break;
			}
			if (readBufPos > 53)
					break;
			Sleep(100);
		}
		
		if (readBufPos <= 53) return FALSE;
	
		Sleep(20);

		////UpdateGlobalDebugInfo();
		
		readBuf[readBufPos] = '\0';
		char B;
		int curNumber = 0;
		int whichData = -1;
		
		BOOL deleteData = FALSE;

		if (data == NULL){
			data = new int[NO_DATA_ITEMS];
			deleteData = TRUE;
		}

		for (int i = 0; i < NO_DATA_ITEMS; i++)
			data[i] = 0;
		
		int bufPos = -1;
		do {
			bufPos++;
			B = readBuf[bufPos];
			switch (B){
			case 'R': whichData = DATA_STORAGE_POINTER; break;
			case 'F': whichData = FILLED_FS_LOCATIONS; break;
			case 'V': whichData = DATA_LOGGER_VERSION; break;
			case 'L': whichData = MPTR_LOCATION; break;
			case 'E': whichData = ERROR_INFO_1; break;
			case 'M': whichData = MEMORY_SIZE; break;
			case 'A': whichData = WHICH_AREA; break;
			case 'B': whichData = BATTERY_VOLTAGE; break;
			case 'C': whichData = CHECK_SUM; break;
			default:
				if (B >= '0' && B <= '9'&& whichData >= 0){
					curNumber *= 10;
					curNumber += (B - '0');
				}
			}
			if (B == ' ' || B == '\0' || B == '.'){
				if (curNumber != 0){
					data[whichData] = curNumber;
					if (whichData == ERROR_INFO_1 || 
						whichData == ERROR_INFO_2 )
						whichData++;
					curNumber = 0;
					whichData = -1;
				}
			}

		} while (readBuf[bufPos] != '\0');

		DSP = data[DATA_STORAGE_POINTER];
		FilledLocations = data[FILLED_FS_LOCATIONS];
		//SetWindowNumber( IDC_DSP_LOCATION, data[DATA_STORAGE_POINTER] );
		//SetWindowNumber( IDC_FS_LOCATIONS, data[FILLED_FS_LOCATIONS] );
		//SetWindowNumber( IDC_LOGGER_VER, data[DATA_LOGGER_VERSION] );
		//SetWindowNumber( IDC_MPTR_LOCATION, data[MPTR_LOCATION] );
		//SetWindowNumber( IDC_NO_EO8S, data[ERROR_INFO_1] );
		//SetWindowNumber( IDC_NO_OVERRUN, data[ERROR_INFO_2] );
		//SetWindowNumber( IDC_NO_LOW_VOLT, data[ERROR_INFO_3] );
		//SetWindowNumber( IDC_CR10_MEMORY, data[MEMORY_SIZE] );
		//SetWindowNumber( IDC_BATT_VOLTAGE, data[BATTERY_VOLTAGE] );
	
		if (deleteData) 
			delete [] data;	
	}
	else
		return FALSE;

	return TRUE;
}

BOOL CCommOperations::ExecuteICommand(int whichLocation, double &oldValue, char *newValue ){

	if (PingCR10(15)||PingCR10(50)||PingCR10(200)||PingCR10(1000)){
		char SendBuff[20];
		if (newValue)
			wsprintf(SendBuff,"%iI\r%s\r", whichLocation, newValue);
		else
			wsprintf(SendBuff,"%iI\r\r", whichLocation);

		readBufPos = 0;
		int SendLength = strlen(SendBuff);
		Send(SendBuff, SendLength);
		
		DWORD LastReadTime = timeGetTime();
		int pReadBufPos;
		do {
			pReadBufPos = readBufPos;
			Sleep(10);
			if (pReadBufPos != readBufPos)
				LastReadTime = timeGetTime();
			if (readBufPos > SendLength + 18)
			{
				
				
				
				break;
			}
		} while (timeGetTime() - LastReadTime < 125);
		
		return TRUE;
	}
	return FALSE;

}

BOOL CCommOperations::ExecuteKCommand(BOOL GetInputLocations, int InputLocRequests){
	DWORD biggestPause = 0;
	DWORD pause = 0;
	static DWORD biggestSuccessfulPause = 0;
	static DWORD biggestUnsuccessfulPause = 0;

	PurgeComm( COMDEV( TalkInfo ) , PURGE_TXCLEAR | PURGE_RXCLEAR);
	DWORD totalTime;
	DWORD startTime = timeGetTime();
	DWORD lastReadTime = startTime;
	int expectedSize;
	if (!GetFSUnderWay && (PingCR10(20) || PingCR10(50) || PingCR10(100) || PingCR10(500))){
	
		readBufPos = 0;
		int pReadBufPos = readBufPos;
			
		Send("K\r",2);
		expectedSize = 12 + needPortByte + GetInputLocations * InputLocRequests * 4;
		do {
			Sleep (10);
			if (readBufPos != pReadBufPos){
				lastReadTime = timeGetTime();
				pReadBufPos = readBufPos;
			}
			if (readBufPos == expectedSize)
				break;
			pause = timeGetTime() - lastReadTime;
			if (pause > biggestPause)
			{
				biggestPause = pause;
			}
		} while (pause < 100 + (unsigned) InputLocRequests * 10);

		if (readBufPos == expectedSize)
		{
			if (pause > biggestSuccessfulPause)
				biggestSuccessfulPause = pause;	
		}
		else
		{
			if (pause > biggestUnsuccessfulPause)
				biggestUnsuccessfulPause = pause;	
		}
		//DWORD eTime = timeGetTime() - startTime;
		//BOOL Success = CheckSignature();
		return (readBufPos == expectedSize); 
		// the signature does not even need to be checked.
		// if the number of bytes is correct, the signature is always good.
		
	}
	
	return FALSE;
}

BOOL CCommOperations::GetFinalStorage(int LocsToRetrieve /*=DOWNLOAD_SIZE*/){
	static int FSLocationsWrittenThisFile = 0;
	
	DWORD bytesWritten;
	int pReadBufPos = 0;
	int i = 0; 
	int j = 0;
	char SendBuf[80];

	// ExecuteACommand();
	// this will retrieve DSP and FilledLocations

	if ( ((DSP < LastDSP) ? (DSP + FilledLocations) : DSP) 
		- LastDSP < LocsToRetrieve)
		return FALSE;
	// If there are not enough new storage locations
	// to read FS data, return FALSE
	CTime theTime = CTime::GetCurrentTime();
	CString s = theTime.Format( "%H;%M;%S, %B %d, %Y" );

	if (FSFileOut == NULL){
		char fileNameBuff[100];
		
		wsprintf(fileNameBuff,"%sFS Data %s.dat", DataDirectory, s);

		FSFileOut = CreateFile(fileNameBuff, 
		GENERIC_WRITE, 
		FILE_SHARE_READ, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_ARCHIVE, 
		NULL);
		if (FSFileOut == INVALID_HANDLE_VALUE){
			CloseHandle(FSFileOut);
			FSFileOut = NULL;
			DisplayErrorMessage(GetLastError());
			return FALSE;
		}
	}

	//SetWindowNumber (IDC_FS_POSITION, 0);
	
	wsprintf(SendBuf,"%iF\r",LocsToRetrieve);
	int ExpectedBytes = strlen(SendBuf) + LocsToRetrieve * 2 + 3;

	int writePos;
	int nextByteToProcess;
	int moveDSP;
	int bytesToWrite;
	int newLocs;
	int firstFSLocation = ExpectedBytes - LocsToRetrieve * 2 - 2;
	char *dataToWrite = new char[LocsToRetrieve * 10];

	//SetTimeBox(2);

	for (int t = 0; t < FS_RETRIES; t++) {
		// move MPTR to LastDSP
		if (MoveMPTR(LastDSP) != LastDSP){
			//SetWindowNumber (IDC_FS_POSITION, 1);
			delete [] dataToWrite;
			return FALSE;
		}
		//SetTimeBox(3);

		writePos = 0;
		readBufPos = 0;
		bytesToWrite = 0;
		newLocs = 0;
		moveDSP = 0;
		nextByteToProcess = firstFSLocation;

		Send(SendBuf, strlen(SendBuf));
		DWORD lastReadTime = 0;
		int i = 0;
		while (readBufPos < ExpectedBytes){
			pReadBufPos = readBufPos;
			Sleep(10);
			i++;
		
			if (pReadBufPos == readBufPos){
				if (lastReadTime == 0)
					lastReadTime = timeGetTime();
				else {
					if (timeGetTime() - lastReadTime > 125){
						delete [] dataToWrite;
						return (FALSE);
					}
				}
			}
			else {
				lastReadTime = 0;
				if (readBufPos - nextByteToProcess >= 2)
					PrepareDataToWrite(readBufPos, readBuf, nextByteToProcess, dataToWrite, writePos, bytesToWrite, moveDSP, newLocs);
			}
			//SetTimeBox(4);
		
		}

		PrepareDataToWrite(readBufPos, readBuf, nextByteToProcess, dataToWrite, writePos, bytesToWrite, moveDSP, newLocs);
		
		
		if (CheckSignature(firstFSLocation, FINALSTORAGE))
			break;
	}
	if (t == FS_RETRIES){
		delete [] dataToWrite;
		return FALSE;
	}
	
	wsprintf(SendBuf,"\n**********| Final Storage Data Written: %s  |**********",s);
	if (!WriteFile(FSFileOut, SendBuf, strlen(SendBuf), &bytesWritten, NULL))
		DisplayErrorMessage(GetLastError());

	if (!WriteFile(FSFileOut, dataToWrite, bytesToWrite, &bytesWritten, NULL))
		DisplayErrorMessage(GetLastError());

	FSLocationsWrittenThisFile += moveDSP;
	LastDSP += moveDSP;

	if (LastDSP > FilledLocations)
		LastDSP -= FilledLocations;

	if (FSFileOut){
		if (FSLocationsWrittenThisFile > FS_LOCS_PER_FILE){
			FSLocationsWrittenThisFile = 0;
			// close the file; it's become too big
			CloseHandle( FSFileOut );  // handle to object);
			FSFileOut = NULL;
		}
	}
	delete [] dataToWrite;
	
	//SetTimeBox(5);

	return TRUE;
}

BOOL CCommOperations::IsConnected(){
	return CONNECTED(TalkInfo);
}

int CCommOperations::MoveMPTR(int whichLocation){

	if (whichLocation < 0)
		return 0;

	char SendBuf[10];

	int newLocation = 0;

	if (whichLocation > FilledLocations)
		whichLocation -= FilledLocations;

	wsprintf(SendBuf, "%iG\r", whichLocation);

	for (int t = 0; t < 3; t++){
		readBufPos = 0;
		Send(SendBuf,strlen(SendBuf));

		for (int i = 0; i < 10; i++) {
			Sleep(10);
			//UpdateGlobalDebugInfo();
			if (readBufPos > 21)
				break;
		} 
		Sleep(10);
		if (readBufPos > 21)
			break;
		
		if (DO_RECONNECT)
			if (Reconnect())
				if (!(PingCR10(20)||PingCR10(50)||PingCR10(1000)))
					return 0;
		else
			return 0;

	} 

	for (int i = 4; readBuf[i] != 'L' && i < 40; i++);
	if (i == 40) return 0;
	for (; readBuf[i] != '.' && i < 40; i++){
		if (readBuf[i] >= '0' && readBuf[i] <= '9'){
			newLocation *= 10;
			newLocation += readBuf[i] - '0';
		}
	}
	if (i == 40) return 0;
	//SetWindowNumber( IDC_MPTR_LOCATION, newLocation );
	return newLocation;
}

BOOL CCommOperations::PingCR10(DWORD miliseconds){
	
	char CR = '\r';//ASCII_CR;
	readBufPos = 0;
	int preadBufPos;
	//EscapeCommFunction( COMDEV( TalkInfo), SETDTR );
	dataReceived = FALSE;
	DWORD startTime = timeGetTime();
	if(!WriteCommBlock(&CR, 1)){
		// there was some error
		DWORD LE = GetLastError();
		DisplayErrorMessage(LE);
		return FALSE;
	}
	else
	{
		do {
			preadBufPos = readBufPos;
			Sleep(5);
			for (int i = preadBufPos; i < readBufPos; i++){
				if (readBuf[i] == '*')
					return TRUE;
			}
		} while (timeGetTime() - startTime < miliseconds);
	}
	//if (readBufPos != 3)
	//	AfxMessageBox("PingCR10 didn't receive 3 characters","This could cause problems",MB_ICONEXCLAMATION);
	return FALSE;
}

void CCommOperations::PrepareDataToWrite(int unprocessedBytes, char *firstDataByte, int &nextByteToProcess, char *dataToWrite, int &writePos, int &bytesToWrite, int &MoveDSP, int &LocationsRetrieved){
	
	unsigned char B, C, D, E;
	int polarity;
	int number;
	int exponent;
	int CurrentType;
	char numberOut[20];
		
	for (; nextByteToProcess < unprocessedBytes - 2; nextByteToProcess += 2){
		
		B = (unsigned char) firstDataByte[nextByteToProcess];
		C = (unsigned char) firstDataByte[nextByteToProcess + 1];
		LocationsRetrieved++;

		if ((B & 0x1C) == 0x1C){
		// second data type format
			if ((B & 0xE0) == 0xE0){
				// this byte is the start of an output array.
				number = ((B & 0x03) << 8) + C;
				CurrentType = 1;
			}
			else if ((B & 0x7F) == 0x7F){
				// B is the first byte of a two byte dummy value 
				// the second byte is always transmitted as 0
				CurrentType = 2;
			}
			else if ((B & 0x20) == 0x20){
				// B is the third byte of a 4 byte value
				// this should not be needed because I will 
				// be skipping ahead two bytes when I hit
				// the first byte in a 4 byte value
				CurrentType = 3;
			}
			else if (unprocessedBytes - nextByteToProcess >= 4){ 
				// B is the first byte of a 4 byte value
				// make sure there are enough unprocessed 
				// bytes to read this 4 byte value
				CurrentType = 4;
				
				D = (unsigned char) readBuf[nextByteToProcess + 2];
				E = (unsigned char) readBuf[nextByteToProcess + 3];
				nextByteToProcess+=2;
				LocationsRetrieved++;

				if (B & 0x40)
					polarity = -1;
				else
					polarity = 1;

				if ((B & 0x02) && (B & 0x80))
					exponent = -5;
				else if (B & 0x02)
					exponent = -4;
				else if ((B & 0x01) && (B & 0x80))
					exponent = -3;
				else if (B & 0x01)
					exponent = -2;
				else if (B & 0x80)
					exponent = -1;
				else 
					exponent = 0;
				number = polarity * (((D & 0x01) << 16) + (C << 8) + E);
			}
		}
		else {
			CurrentType = 5;
			if (B & 0x80)
				polarity = -1;
			else
				polarity = 1;
			if ((B & 0x60) == 0x60)
				exponent = -3;
			else if(B & 0x40)
				exponent = -2;
			else if(B & 0x20)
				exponent = -1;
			else
				exponent = 0;
			
			number = polarity * (((B & 0x1F) << 8) + C);
		}
			
		// store a 2 or 4 byte high-resolution value
		iToString(number, exponent, numberOut);
		
		switch (CurrentType){
		case 1: //We are writing a new line plus an output array ID
			wsprintf(numberOut, "\n%i,",number);
			bytesToWrite = writePos; 
			MoveDSP = LocationsRetrieved - 1;
			break;
		case 2:	//We are writing a dummy value
			wsprintf(numberOut,"DUMMY");
			break;
		case 4:
		case 5:	//We are writing a low or high resolution number
			wsprintf(numberOut,"%s,",numberOut);
			break;
		}
		strcpy(&dataToWrite[writePos], numberOut);
		writePos += strlen(numberOut);
	}
}

void CCommOperations::ProcessInputLocations(double InputLocValue[], int InputLocRequests){
	unsigned char iLocBytes[4];
	double sign;
	int exponent;
	double mantissa;
	double result;
	unsigned int m;
	unsigned char mask = 1 << 7;
		
	for (int i = 0; i < InputLocRequests; i++){
		for (int j = 0; j < 4; j++)
			iLocBytes[j] = readBuf[8 + needPortByte + i * 4 + j];
		if (iLocBytes[0] == 0 && iLocBytes[1] == 0 && 
			iLocBytes[2] == 0 && iLocBytes[3] == 0)
			result = 0.0;
		else if (iLocBytes[0] == 0xFF && iLocBytes[1] == 0xFF && 
			iLocBytes[2] == 0xFF && iLocBytes[3] == 0xFF)
			result = -99999.0;
		else {
			sign = 1 - ((iLocBytes[0] & mask) >> 1);
			exponent = (iLocBytes[0] & 0xFF) - 0x40;
			//iLocBytes[0] = 0;
			//*m <<= 8;
			m = iLocBytes[1] * 0x10000 + iLocBytes[2] * 0x100 + iLocBytes[3];
			mantissa = double(m & 0x7FFFFF) / double(0xFFFFFE) + .5; 
			//mantissa = iLocBytes[1] %= 128;
			result = sign * (mantissa * pow(2, exponent));
		}
		
		InputLocValue[i] = result;
	}	
}

BOOL CCommOperations::Reconnect(BOOL reUpdate){
	//SetWindowNumber( IDC_RECONNECTS, ++reconnects );	
	//consecReconnects++;
	//AfxMessageBox("Reconnect called","Message");
	if (CONNECTED(TalkInfo)){
		Sleep(100);
		EndCR10Comm();// this includes CloseConnection()
		Sleep(100);
		//SetButtonState(NotConnected);
	}
	if(OpenConnection()){
		//SetButtonState(Connected);
		//if (consecReconnects % 5 != 0){
			//Sleep(100);
			//if (reUpdate)	
			//	return UpdateInfo();
			return (PingCR10(20)||PingCR10(50)||PingCR10(50)||PingCR10(500));
		//}
	}
	//StopAutoUpdate();
	//DisplayErrorMessage(GetLastError());
	// the error message may be written to a log file.
	return FALSE;
}

BOOL CCommOperations::RetrieveFinalStorage(BOOL GetLastFSL){
	
	if (!GetFSUnderWay){
		
		if (!ExecuteACommand()) // this retrieves the current DSP
			return FALSE;

		GetFSUnderWay = TRUE;

		if (LastDSP == 0){
			if (FStartRetrievalFromCurrentPosOnStart){
				LastDSP = DSP; //
			}
			else
				LastDSP = 1;
		}

		int InitialToRetrieve = ((DSP < LastDSP) ? (DSP + FilledLocations) : DSP) - LastDSP;
		int LocsToRetrieve = InitialToRetrieve;
		BOOL DoProgressBox = FALSE;
		BOOL downloadCancelled = FALSE;
		char wText[100];
		int LocsRetrieved = 0;
		ProgressDialog *GetFSProgress = NULL;
				
		if (InitialToRetrieve > DOWNLOAD_SIZE * 2){
			GetFSProgress = new ProgressDialog(&downloadCancelled, 
				"Downloading final storage locations from the CR10.", 
				"Downloading Final Storage Locations...", 
				"Stop", TRUE, NULL);
			GetFSProgress->Create(PROGRESS_DIALOG);
		}
				
		while ( LocsToRetrieve >= DOWNLOAD_SIZE && !downloadCancelled){
			//SetTimeBox(1);
			
			BOOL GetFSSuccess = GetFinalStorage();

			MSG Msg;
		
			PeekMessage( &Msg,         // message information
				NULL,           // handle to window
				0,//WM_MOUSEFIRST,  // first message  
				0,//WM_MOUSELAST );  // last message
				PM_REMOVE /*| PM_NOYIELD*/); //wRemoveMsg
			DispatchMessage( &Msg );  // message information);
		
			//SetTimeBox(6);

			if (downloadCancelled) 
				break;
			
			LocsToRetrieve = ((DSP < LastDSP) ? (DSP + FilledLocations) : DSP) - LastDSP;
			
			if (GetFSProgress){
				wsprintf(wText,"%i final storage locations left to retrieve.", LocsToRetrieve);
				GetFSProgress->SetInfo(100 - (100 * LocsToRetrieve / InitialToRetrieve), wText);
			}
			//SetTimeBox(7);
			
		}
		if (!downloadCancelled && LocsToRetrieve && GetLastFSL)
			GetFinalStorage(LocsToRetrieve);

		GetFSUnderWay = FALSE;
		if (GetFSProgress){
			GetFSProgress->Close();
			//this->EnableWindow(TRUE);
			delete GetFSProgress;
			if (downloadCancelled){
				//StopAutoUpdate();
				return FALSE;
			}
		}
	
		return TRUE;
	}
	return FALSE;
}

BOOL CCommOperations::Send(const LPSTR data, int bytesToSend)
{
	for (int t = 0; t < 5; t++){

		if (WriteCommBlock(data, bytesToSend)){
			//UpdateGlobalDebugInfo();
			return TRUE;
		}
		WCBuffRepeats++;
		if (DO_RECONNECT){
			Reconnect();
			(PingCR10(20) || PingCR10(50) || PingCR10(500) || PingCR10(1000));
		}
	}
	//UpdateGlobalDebugInfo();
	return FALSE;

}

BOOL CCommOperations::SetJCommand(BOOL DoUserFlags, BOOL DoPortFlags, 
	BOOL DoInputLocations, int InputLocList[], int InputLocRequests)
{
	static BOOL GFS = FALSE; // get final storage variable
	DWORD sTime = timeGetTime();
	int expectedSize;

	if (!GetFSUnderWay && (PingCR10(20) || PingCR10(100) || PingCR10(500) || PingCR10(1000))){
		unsigned char uFB = 0, pFB = 0;

		// This section sets up the user flags byte.
		if (DoUserFlags){
			for (int i = 7; i >= 0; i--){
				uFB <<= 1;
				if (toggleFlags[i][USERFLAGS]){
					if (toggleFlags[i][USERFLAGS] == JUSTONCE){
						toggleFlags[i][USERFLAGS] = NEVER;
						uFB++;
					}
					else if(ProgramCounter % FreqTable[toggleFlagsFreqLevel[i][USERFLAGS]] == 0)
						uFB++;
				}
			}
		}

		// This section sets up the control ports flags byte.
		if (DoPortFlags){
			for (int i = 7; i >= 0; i--){
				pFB <<= 1;
				if (toggleFlags[i][PORTFLAGS]){
					if (toggleFlags[i][PORTFLAGS] == JUSTONCE){
						toggleFlags[i][PORTFLAGS] = NEVER;
						pFB++;
					}
					else if(ProgramCounter % FreqTable[toggleFlagsFreqLevel[i][PORTFLAGS]] == 0)
						pFB++;
				}
			}
		}

		needPortByte = (pFB != 0);
		unsigned char FSPTB = (GFS ? 128: 0) + (needPortByte ? 64 : 0);
		char sendBuf[80];

		sendBuf[0] = '3';
		sendBuf[1] = '1';
		sendBuf[2] = '4';
		sendBuf[3] = '2';
		sendBuf[4] = 'J';
		sendBuf[5] = '\r';
		sendBuf[6] = uFB;
		sendBuf[7] = FSPTB;
		sendBuf[8] = pFB;
		
		// This section sets up which input locations will be returned.
		for (int i = 0; i < InputLocRequests && DoInputLocations; i++){
			sendBuf[8 + needPortByte + i] = char(InputLocList[i]);
		}

		sendBuf[8 + needPortByte + i] = '\0';
		
		// give it 5 tries
		//Sleep(10);
		
		//for (int t = 0; t < 5; t++){
			readBufPos = 0;
			int pReadBufPos = readBufPos;
			Send(sendBuf, 9 + needPortByte + i);
			DWORD startTime = timeGetTime();
			DWORD LastReadTime = startTime;
			expectedSize = 11 + needPortByte + i;
			do {
				Sleep (10);
				if (readBufPos != pReadBufPos)
				{
					LastReadTime = timeGetTime();
					pReadBufPos = readBufPos;
				}
				if (readBufPos == expectedSize){
					NeedSetJCommand = FALSE;
					return TRUE;
				}
			} while (timeGetTime() - LastReadTime < 100 + (unsigned) i * 5);
			
		//}
		
	}
	DWORD tTime = timeGetTime() - sTime;
	return FALSE;

}

const char * CCommOperations::GetCR10Time()
{
	timeBuf[0] = '\0';
	unsigned char tbyte1 = readBuf[3];
	unsigned char tbyte2 = readBuf[4];
	unsigned char tbyte3 = readBuf[5];
	unsigned char tbyte4 = readBuf[6];
		
	// next is data bytes
	int time1 = tbyte1 * 256 + tbyte2;
	int hours = time1 / 60;
	int minutes = time1 % 60;
	int seconds = tbyte3 * 256 + tbyte4;
	// this is actually seconds * 10
	wsprintf(timeBuf, "%2i:%02i:%02i.%1i",hours, minutes, seconds / 10, seconds % 10);
	return timeBuf;
}


BOOL CCommOperations::ChangeCR10Time(int hour, int minute, int second, int day, int year) // = 0, = 0
{
	year %= 100;
	char newTimeBuff[30];
	
	if (year == 0 && day == 0)
		wsprintf(newTimeBuff,"%i:%i:%i:%i:%iC\r", year, day, hour, minute, second);
	else
		wsprintf(newTimeBuff,"%i:%i:%iC\r", hour, minute, second);
	
	for (int t = 0; t < 5; t++){
		readBufPos = 0;
		Send(newTimeBuff, strlen(newTimeBuff));
		DWORD startTime = timeGetTime();
		do {
			Sleep (10);
			if (readBufPos > 20){
				return TRUE;
			}
		} while (timeGetTime() - startTime < 100);
		Sleep(10);
		return (PingCR10(20)||PingCR10(20)||PingCR10(50));
	}
	return FALSE;
}


BOOL CCommOperations::UpdateInfo(BOOL DoUserFlags, 
							 BOOL DoPortFlags, BOOL DoInputLocations, 
							 BOOL DoCR10Info, int InputLocList[], int InputLocRequests)
{
	// ping the CR10 several times.  If there is no response,
	// then return FALSE;
	static DWORD thisTime = 0;
	static DWORD lastTime = 0;

	//**********************************************************
	//***************|  CR10 TIME  |****************************

	timeBuf[0] = '\0';
	unsigned char tbyte1 = readBuf[3];
	unsigned char tbyte2 = readBuf[4];
	unsigned char tbyte3 = readBuf[5];
	unsigned char tbyte4 = readBuf[6];
		
	// next is data bytes
	int time1 = tbyte1 * 256 + tbyte2;
	int hours = time1 / 60;
	int minutes = time1 % 60;
	int seconds = tbyte3 * 256 + tbyte4;
	// this is actually seconds * 10
	wsprintf(timeBuf, "%2i:%02i:%02i.%1i",hours, minutes, seconds / 10, seconds % 10);
	//SetTimeWindowText(timeBuf);

	unsigned char mask = 1 << 7;
	//**********************************************************
	//***************|  USER FLAGS  |****************************
	if (DoUserFlags){
		unsigned char ufbyte = readBuf[7];
		for (int i = 0; i < 8; i++){
			FlagStatus[7 - i][USERFLAGS] = (mask & ufbyte) >> 7;
			ufbyte <<= 1;
		}
		//SetUserFlagsWindowsText();
		//if (FlagWindowCount && ModifyWhichFlags == USERFLAGS)
		//	m_CFlagsDialog->UpdateFlags();
	}
	//**********************************************************
	//***************|  PORT FLAGS  |****************************
	if (DoPortFlags && needPortByte){
		unsigned char pfbyte = readBuf[8];
		for (int i = 0; i < 8; i++){
			FlagStatus[7 - i][PORTFLAGS] = (mask & pfbyte) >> 7;
			pfbyte <<= 1;
		}
		//SetPortFlagsWindowsText();
		//if (FlagWindowCount && ModifyWhichFlags == PORTFLAGS)
		//	m_CFlagsDialog->UpdateFlags();
	}
	//**********************************************************
	//***************|  INPUT LOCATIONS  |****************************

	if (DoInputLocations){
		//process input locations	
//		ProcessInputLocations(InputLocValue, InputLocSaveRequests);
		//SetInputLocationWindowsText(inputWindowText);
	}
	
	//**********************************************************
	//***************|  CR10 INFO  |****************************

	if (DoCR10Info)
		ExecuteACommand();

	//UpdateGlobalDebugInfo();
		
	consecReconnects = 0;
	/*
	thisTime = timeGetTime();
	if (lastTime != 0){
		//SetWindowNumber( IDC_LAST_DELAY, thisTime - lastTime );
		if (AutoUpdate && LastAutoUpdateTime && 
			thisTime - LastAutoUpdateTime > longestDelay){
			longestDelay = thisTime - LastAutoUpdateTime;
			//SetWindowNumber( IDC_LONGEST_DELAY, longestDelay );
		}
	}
	lastTime = thisTime;
	LastAutoUpdateTime = (AutoUpdate ? thisTime : 0);
	*/
	return TRUE;
}

char CCommOperations::WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow){
	DWORD startTime = timeGetTime();
	do {
		int pReadBufPos = readBufPos;
		Sleep(10);
		for (int i = pReadBufPos; i < readBufPos; i++){
			for (int cpos = 0; c[cpos] != '\0'; cpos++){
				if (readBuf[i] == c[cpos])
					return c[cpos];
			}
		}
	} while (timeGetTime() - startTime < timeOut && !(*stopNow));
	return NULL;
}

