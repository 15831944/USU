// This is Version 1.0 PLEASE DOCUMENT CHANGES
// CommOperations.cpp: implementation of the CCommOperations class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LADA Control Module.h"
#include "CommOperations.h"
#include "LADA Control ModuleDoc.h"
#include "LString.h"
#include "Ladastrings.h"
#include "FSInfo.h"
#include "HistoryClass.h"
#include <fstream.h>
//#include <afxwin.h>
//#include <afx.h>
//#include "CR10 Talk Main.h"
//#include "resource.h"
#include <math.h>

//#include "MonitorDlg.h"
//#include "FlagsDialog.h"
#include "ProgressDialog.h"
#include "MessageBox.h"
//#include "RenameLocation.h"
//#include "EditEvent.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString ValueToString(double value, int dPlaces = 2, BOOL applyLanguage = FALSE);
extern double StringToValue(const char *ptrString);
extern HANDLE DataReceived;
extern LString Strings;
extern int StringToInt(const char * String, int Length = 0);
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
extern UINT NotificationBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);
extern UINT NotificationBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);
extern double StringToValue(const char *ptrString);
#undef MessageBox
#define MessageBox MyMessageBox
extern CString IntToString(int number);

#include "inputlocations.h"
BOOL PossiblyDisconnected;

#define INTERMEDIATE_STORAGE_RANGE	9223373e13
//////////////////////////////////////////////////////////////////////
//  Global functions

int round(double & value)
{
	if (value < 0.0)
		return (int) (value - 0.5);
	else
		return (int) (value + 0.5);
}

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
			wsprintf(messageString,(LPCTSTR)Strings.get(IDS_M_ERROR_FORMAT_STR),ErrorNum);
		strcat(messageString,(LPCTSTR)lpMsgBuf);
		//wsprintf(messageString,"%s%s",messageString,(LPCTSTR)lpMsgBuf);
		if (AdditionalMessage)
			strcat(messageString,AdditionalMessage);
		//wsprintf(messageString,"%s%s",messageString,AdditionalMessage);

		MessageBox( messageString, NULL, MB_OK | MB_ICONINFORMATION );
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

CCommOperations::CCommOperations( CLADAControlModuleDoc * doc, BOOL ShowMessage, BOOL WaitExtra ) // = TRUE
{
	HasCommBeenClosed = FALSE;
	pDoc = doc;
	CommSyncObject = CreateEvent(NULL,TRUE,TRUE,"CR10_COMM_SYNCRONIZATION");
	Connect(ShowMessage, WaitExtra );
}

CCommOperations::~CCommOperations()
{
	CloseHandle( CommSyncObject );
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
 //CString  AvailableInputLocations[MAX_INPUT_LOCATIONS];
 int   toggleFlags[8][2];
 //BOOL  DoToggleFlags[2];
 //int   ModifyWhichFlags;
 //CString  FlagNames[8][2];
 //int   toggleFlagsFreqLevel[8][2];
 //BOOL  SaveFinalStorage;
 //int   nPEvents;

//    USED ONLY DURING PROGRAM EXECUTION
 char  *readBuf;
 int   readBufPos;

 int   reconnects = 0;				// RECONNECTS
 DWORD programStartTime = 0;
 
 //int   FreqTable[16] = {1, 2, 5, 10, 30, 60, 120, 300, 600, 1800, 3600, 10800, 21600, 86400, 259200, 604800};
 int   FilledLocations;
 int   DSP;
 BOOL  FlagStatus[8][2];
 int   consecReconnects;
 //BOOL  GetFSUnderWay = FALSE;
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
		(SignatureType == UPLOADPROGRAM) || 
		(buffer[readBufPos - 3] == char(0x00) && 
		buffer[readBufPos - 4] == char(0x7F)) )
	{
		
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

BOOL CCommOperations::Connect(BOOL ShowMessage, BOOL WaitExtra){ // = TRUE , = FALSE;
// Open a connection and ping until you find which comport works

	if (CONNECTED(TalkInfo))
	{
		MessageBox(IDS_M_COMM_ALREADY_EXISTS);
		return TRUE;
	}
	CWaitCursor wCursor;
	bool ConnectOnAny = true;
	if ( defaultPort != 0 )
	{ 
		PORT( TalkInfo ) = defaultPort;
		char errMessage[100];
		do {
			// there is a default port.  try it first
			if (OpenConnection())
			{
				if (PingCR10(100)||PingCR10(500)||PingCR10(1000)||PingCR10(1000))
					return TRUE;
				if (WaitExtra)
				{
					for (int i = 0; i < 20; i++)
					{
						if (PingCR10(500))
							return TRUE;
					}
				}
				CloseConnection();
			}
			
			wsprintf(errMessage,(LPCSTR)Strings.get(IDS_M_RECONNECT_ON_PORT), defaultPort);
		} while (MessageBox(errMessage, NULL, MB_YESNO | MB_ICONQUESTION ) == IDYES);
		if (MessageBox(IDS_M_CONNECT_ON_ANY,IDS_PROGRAM_NAME,MB_YESNO|MB_ICONQUESTION) == IDNO)
			ConnectOnAny = false;
	}

	for (int p = 1; ConnectOnAny && p < 5; p++){
		if ( p == defaultPort )
			p++;
		if ( p == 5 )
			break;
		PORT( TalkInfo ) = p;
		if (OpenConnection()){
			if (PingCR10(500,TRUE)||PingCR10(1200)||PingCR10(2000)){
				defaultPort = p;
				return TRUE;
			}
			if (WaitExtra)
			{
				for (int i = 0; i < 20; i++)
				{
					if (PingCR10(500))
					{
						return TRUE;
						defaultPort = p;
					}
				}
			}
			CloseConnection();
		}
		else 
		{
			DWORD lError = GetLastError();
			if (lError && lError != 2) // File not found error, in this case, port not found)
				DisplayErrorMessage(lError);
		}
	}
	
	if (ShowMessage)
		MessageBox(Strings.get(IDS_M_UNABLE_TO_CONNECT), NULL, MB_ICONEXCLAMATION );
	PORT( TalkInfo ) = defaultPort;
	return FALSE;
	
}

BOOL CCommOperations::ControlCR10( CR10ControlType Lights, // = NoChange 
								   CR10ControlType Fans,   // = NoChange
								   CR10ControlType Pump1,  // = NoChange
								   CR10ControlType Pump2,  // = NoChange
								   int wChamber) // = 0
{
	int controlNumber;
	int controlLocation;
	
	if (wChamber == 0)
		controlLocation = CHAMBER_1_CONTROL;
	else
		controlLocation = CHAMBER_2_CONTROL;

	double oldValue;
	
	if (!pDoc->GetInputLocations(&controlLocation,1,&oldValue,2))
	{		
		pDoc->m_ErrorFiles->WriteHistory(IDS_E_COMMUNICATIONS, IDS_E_COMMUNICATIONS_FAILED_GET_OLD);
		return FALSE;
	}
	controlNumber = round(oldValue);
	
	if (Lights == On)
	{
		controlNumber |= 32;
		controlNumber |=128;
	}
	else if (Lights == Off)
		controlNumber |= 16;

	if (Fans == On)
		controlNumber |= 128;
	else if (Fans == Off)
		controlNumber |= 64;

	if (Pump1 == On || Pump1 == Forward)
	{
		controlNumber |= 8;
		for (int wTry = 0; wTry < 5 && !SetFlag(2,1); wTry++);
		if (wTry == 5)
			MessageBox("Failed to set flag 2 high to disable pump security.");
			
	}
	else if (Pump1 == Off)
		controlNumber |= 4;
	else if (Pump1 == Reverse)
		controlNumber |= 12;

	if (Pump2 == On || Pump2 == Forward)
	{
		controlNumber |= 2;
		for (int wTry = 0; wTry < 5 && !SetFlag(2,1); wTry++);
		if (wTry == 5)
			MessageBox("Failed to set flag 2 high to disable pump security.");
	
	}
	else if (Pump2 == Off)
		controlNumber |= 1;

	if (controlNumber)
	{
		//char message[100];
		//wsprintf(message,"Input location #%i set to %i",controlLocation,controlNumber);
		//pDoc->m_ErrorFiles->WriteHistory("Control CR10", message);
		
		SetInputLocation(controlLocation, controlNumber, 102, TRUE);
		//double old;
		//SetLocationAndVerify(controlLocation,old,controlNumber);
		
	}
	return TRUE;
}


int CCommOperations::UploadProgram(CString filename){
	//open the file
	// if no filename is provided, ask the user which file to Upload
	if (!CONNECTED( TalkInfo )){
		MessageBox (IDS_M_NO_CONNECTION_PRESENT, NULL, MB_ICONEXCLAMATION);
		return FALSE;
	}

	CString smallFileName = filename;

	if (filename == ""){
		
		CFileDialog OpenFileDialogBox(TRUE, "dl%d", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			"Data logger program (*.dld)|*.dld|All Files (*.*)|*.*||",
			NULL);
		 
		UINT success = OpenFileDialogBox.DoModal();
	
		if ( success == IDOK)
		{
			filename = OpenFileDialogBox.GetPathName();
			smallFileName = OpenFileDialogBox.GetFileName();
		}
		else
			return FALSE;
	}
	
	if (!StartCommOperation(1))
	{
		EndCommOperation();
		return FALSE;
	}

	if (!PingCR10(20)&&!PingCR10(50,TRUE)&&!PingCR10(100)&&!PingCR10(200))
	{
		EndCommOperation();
		MessageBox(IDS_M_UPLOAD_CR10_NO_RESPONSE, IDS_ERROR, MB_ICONWARNING );
		return FALSE;	
	}
	
	HANDLE fileIn = CreateFile(filename, 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileIn == INVALID_HANDLE_VALUE){
		GetLastError();
		//DisplayErrorMessage();
		EndCommOperation();
		MessageBox(IDS_M_ERROR_ACCESS_FILE, NULL, MB_ICONEXCLAMATION);
		return FALSE;
	}

	DWORD fileSize = GetFileSize(fileIn, NULL);
	
	// set up progress box
	BOOL uploadCancelled;
	char wText[100];
	wsprintf(wText,Strings.get(IDS_M_UPLOADING_FILE_NAME), smallFileName);
	ProgressDialog UploadProgress(&uploadCancelled, wText, Strings.get(IDS_M_UPLOADING_FILE));
	UploadProgress.Create(PROGRESS_DIALOG);

	//send the file
	char *fileBuff = new char[fileSize + 1];
	DWORD bytesRead;
	ReadFile(fileIn,fileBuff,fileSize,&bytesRead,NULL);
	CloseHandle( fileIn );  // handle to object);

	char SendBuff[TRANSMIT_SIZE + 10];
	
	readBufPos = 0;
	
	Send("7H\r*D2\r",7);
	
	if (!WaitOnSequence("02:<",1000,&uploadCancelled))
	{
		UploadProgress.Close();
		// 13..MODE         19:18:10.74 R  31 33 0D 0A 4D 4F 44 45 20
		char failcode[] = { 0x31, 0x33, 0x0D, 0x0A, 0x4D, 0x4F, 0x44, 0x45, 0x00 };
		for (int i = 0; i < readBufPos - 7; i++)
		{
			if (strncmp(failcode,&readBuf[i],strlen(failcode))==0)
			{
				// *D failed.  Check security code.
				EndCommOperation();
				MessageBox(IDS_M_UPLOAD_PROGRAM_D_FAILED,IDS_ERROR,MB_ICONWARNING|MB_OK);
				delete [] fileBuff;
				return FALSE;
			}
		}
		EndCommOperation();
		MessageBox(IDS_M_UPLOAD_PROGRAM_CANT_START,IDS_ERROR,MB_ICONWARNING|MB_OK);
		delete [] fileBuff;
		return FALSE;
	}
	
	/*
	7H.              19:18:10.69 T  37 48 0D
	7H....>          19:18:10.69 R  37 48 0D 0A 0D 0A 3E
	*                19:18:10.74 T  2A
	..MODE           19:18:10.74 R  0D 0A 4D 4F 44 45 20
	D                19:18:10.74 T  44
	13..MODE         19:18:10.74 R  31 33 0D 0A 4D 4F 44 45 20
	D                19:18:10.74 T  44
	13..MODE         19:18:10.74 R  31 33 0D 0A 4D 4F 44 45 20
	D                19:18:10.80 T  44
	13..MODE         19:18:10.80 R  31 33 0D 0A 4D 4F 44 45 20
	

	Send("7H\r",3);
	WaitOnChar(">",125,&uploadCancelled);
	Send("*D2",3);
	if (WaitOnChar("2",125,&uploadCancelled) != '2')
	{
		UploadProgress.Close();
		// 13..MODE         19:18:10.74 R  31 33 0D 0A 4D 4F 44 45 20
		char failcode[] = { 0x31, 0x33, 0x0D, 0x0A, 0x4D, 0x4F, 0x44, 0x45, 0x00 };
		for (int i = 0; i < readBufPos - 7; i++)
		{
			if (strncmp(failcode,&readBuf[i],strlen(failcode))==0)
			{
				// *D failed.  Check security code.
				MessageBox("*D failed.  Check security code.","Error");
				return FALSE;
			}
		}
		MessageBox("Unable to start program upload mode.","Error");
		return FALSE;
	}
	*/
	int cArray[40];
	
	for (int i = 0; i < 5; i++)
	{
		WaitForData();
		cArray[i] = readBufPos;
		if (readBufPos > 31) break;
	}
	WaitForData();
	
	BOOL opFailed = FALSE;
	
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
			MSG Msg;
		
			while (PeekMessage( &Msg,         // message information
				NULL,           // handle to window
				0,//WM_MOUSEFIRST,  // first message  
				0,//WM_MOUSELAST );  // last message
				PM_REMOVE /*| PM_NOYIELD*/)) //wRemoveMsg
				DispatchMessage( &Msg );  // message information);

			if (uploadCancelled || opFailed){
				opFailed = TRUE;	
				break;
			}
		
			sendSize = min(fileLeft, TRANSMIT_SIZE);
			
			memcpy(SendBuff,&fileBuff[fileBufPos],sendSize);

			SendBuff[sendSize] = char(0x03);
			SendBuff[sendSize + 1] = char(0x03);
			
			readBufPos = 0;
			Send(SendBuff, sendSize + 2);

			WaitForData();
			char whichChar = WaitOnChar("<>", 1000, &uploadCancelled);
			if (whichChar != '<' && whichChar != '>')
			{
				opFailed = TRUE;
				break;
			}
			/*
			for (int i = 0; i < 10; i++){
				Sleep(15);
					cArray[i] = readBufPos;
				if (readBuf[readBufPos - 1] == '<' || readBuf[readBufPos - 1] == '>')
					break;
				if (uploadCancelled) i = 10;
				
			}
			if (i == 10){
				opFailed = TRUE;	
				break;
			}
			*/

			//CheckSignature;
			BOOL SigValue = CheckSignature(0,UPLOADPROGRAM,
				&fileBuff[fileBufPos], sendSize, 
				(unsigned char) readBuf[readBufPos - 3], 
				(unsigned char) readBuf[readBufPos - 2]);
			
			if (SigValue){
				// if signature is good, then
				fileBufPos += sendSize;
				fileLeft -= sendSize;
				UploadProgress.SetInfo(100 - 100 * fileLeft / fileSize);

				if (fileLeft == 0)
					break;
				
				// continue the load operation.  
				// load the current buffer and reset signature
				SendBuff[0] = char(0x04);
				SendBuff[1] = char(0x04); 
							
			 	for (int t = 0; t < 2 && !uploadCancelled; t++){
					readBufPos = 0;
					Send(SendBuff, 2);
									
					char whichChar = WaitOnChar("<>", 12000, &uploadCancelled);
					if (whichChar == '<')
						break;
					if (whichChar == '>')
					{
						// readbufpos should be > 4
						if (readBufPos < 4)
							MessageBox("After sending 04 04 to CR10 a > was returned and readbufpos < 4","Error");
						// an error occured in the CR10 while trying to compile
						// the program which was uploaded
						for (int i = 0; readBuf[i] != 'E' && i < readBufPos; i++);
						char ErrCode[3];
						ErrCode[0] = readBuf[i+1];
						ErrCode[1] = readBuf[i+2];
						ErrCode[2] = '\0';
						char ErrMessage[100];
						wsprintf(ErrMessage,Strings.get(IDS_M_UPLOAD_FAIL_COMPILE),ErrCode);
						MessageBox(ErrMessage,Strings.get(IDS_ERROR).GetBuffer(0),MB_ICONSTOP);
						opFailed = TRUE;
						break;

					}
				} 
				if (t == 2 || uploadCancelled){
					opFailed = TRUE;	
					break;
				}
			}
			else { // signature was bad
				SendBuff[0] = char(0x02);
				SendBuff[1] = char(0x02);
				
				for (int t = 0; t < 2 && !uploadCancelled; t++){
					readBufPos = 0;
					
					Send(SendBuff, 2);
					
					char whichChar = WaitOnChar("<>", 3000, &uploadCancelled);
					if (whichChar == '<' || whichChar == '>')
						break;
				}
				if (t == 2 || uploadCancelled){
					opFailed = TRUE;	
					break;
				}
			}

		} while (fileLeft > 0 && !opFailed);

		if (!opFailed){
			UploadProgress.SetInfo(100, Strings.get(IDS_M_UPLOAD_CR10_COMPILE).GetBuffer(0));
			SendBuff[0] = char(0x05); 
			readBufPos = 0;
			SendBuff[1] = char(0x05); 
			Send(SendBuff, 2);
			WaitForData();
			char baseString[190];
			strcpy(baseString,Strings.get(IDS_M_UPLOAD_CR10_COMPILE).GetBuffer(0));
			int baseLength = strlen(baseString);
			int nStars = 0;

			for (int t = 0; t < 20; t++)
			{
				readBufPos = 0;
				Send("\r",1);
				nStars++;
				for (int i = 0; i < nStars % 4; i++)
					baseString[baseLength + i] = '.';
				baseString[baseLength + i] = '\0';
				UploadProgress.SetInfo(100, baseString);
				WaitForData(1000);
				if (readBufPos > 0)
					break;
			}
			if (t == 20 || uploadCancelled) // it didn't work...
				opFailed = TRUE;
				
		} // !opFailed
	} // !opFailed
	else
	{
		// if uploading the program failed we should have the 
		// CR10 clear its buffer, so that it can go back to regular 
		// mode...  ???
		SendBuff[0] = char(0x02);
		SendBuff[2] = char(0x02);
		SendBuff[3] = '\r';
		Send(SendBuff,3);
		WaitForData(20);

	}
	
	//UploadProgress.Close();	
	
	//CWaitCursor wCursor;

	// switch back into * mode <command mode?>
	delete [] fileBuff;
	if (!opFailed)
		LastDSP = 1;

	if (!UploadProgress.m_hWnd)
	{
		uploadCancelled = FALSE;
		UploadProgress.Create(PROGRESS_DIALOG);
	}

	CString curMessage = Strings.get(opFailed ? IDS_M_UPLOAD_FAIL_WAIT_CR10:IDS_M_UPLOAD_WAIT_CR10);

	UploadProgress.SetInfo(100, curMessage.GetBuffer(0));
	
	char ErrCode[3] = "--";
	uploadCancelled = FALSE;
	while (1)
	{
		for (int t = 0; t < 5 && !uploadCancelled; t++)
		{
			UploadProgress.SetInfo(100, (curMessage + Strings.get(IDS_M_ATTEMPT_NUMBER) + IntToString(i+1)).GetBuffer(0));
			
			readBufPos = 0;
			//Send("*0\r",3);
			Send("*0",2);
			//Send("0",1);
			// we may get err message stuff now... be patient
			char whichChar = WaitOnChar("*",12000, &uploadCancelled);
			if (whichChar == '*')
				break;
			//if (readBufPos > 4)
			//{
			//	// we are probably getting error info back
			//	for (int i = 0; (readBuf[i] != 'E' || readBuf[i+1] != ' ') && i < readBufPos; i++);
			//	if (readBuf[i+1]!=ErrCode[0] || readBuf[i+2] != ErrCode[1])
			//	{
			//		ErrCode[0] = readBuf[i+1];
			//		ErrCode[1] = readBuf[i+2];
			//		ErrCode[2] = '\0';
			//		char ErrMessage[100];
			//		wsprintf(ErrMessage,"CR10 returned error code E%s while switching modes.",ErrCode);
			//		MessageBox(ErrMessage,"Error",MB_ICONSTOP);
			//	}
			//	//opFailed = TRUE;
			//}
			
			//if we get a > returned we have not switched modes yet...
			// if we get a * back we have switched modes, exit
		
		}	
		if (t == 5) // we are still in the binary whatever mode <*0 didn't get us back)
		{
			MessageBox(IDS_M_UPLOAD_UNABLE_SWITCH,IDS_ERROR);
			MessageBox(IDS_M_CONNECT_WITH_PC208, IDS_ERROR,MB_ICONWARNING);
			//if (MessageBox(IDS_M_SWITCH_AGAIN,IDS_PROGRAM_NAME,MB_ICONQUESTION|MB_YESNO)==IDNO)
			//{
				opFailed = TRUE;
				break;
			//}
		}
		else
			break;
	}
	EndCommOperation();
	if (!opFailed)
	{
		wsprintf(wText,Strings.get(IDS_M_FILE_UPLOADED), smallFileName);
		MessageBox(wText);
		if (UpdateCR10Time())
			MessageBox(IDS_M_TIME_UPDATED,IDS_PROGRAM_NAME,MB_ICONINFORMATION);
		else
			MessageBox(IDS_M_TIME_NOT_UPDATED,IDS_PROGRAM_NAME,MB_ICONINFORMATION);
	}

	return !opFailed;
	//UploadProgress.Close();	
	//
	//static int nInUpload = 0;
		
	// we gave a command to the CR10 to switch back to command mode 0, but
	// it didn't.  This may be because its program has been corrupted.
	// upload a default program to the CR10 now...
	//nInUpload++;
	//if (nInUpload == 1) // don't allow infinite recursion...
	//{
	//	if (SwitchMode())
	//	{
	//		if (UploadProgram(filename))
	//			return TRUE;
	//	}
	//	// can't load program on... since memory has been corrupted load a 
	//	// default program on.
	//	int rStatus = UploadProgram("PC208 Default.dld");
	//	nInUpload--;
	//	return rStatus;
	//}
	//return FALSE;
	//	
	
	


}

BOOL CCommOperations::EndCR10Comm()
{
	// wait for any pending comm operations to finish
	HasCommBeenClosed = TRUE;
	StartCommOperation(2);
	EndCommOperation();

	DWORD dwErrorFlags;
	ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
		
	//DWORD LASTError = GetLastError();
	//
	//if (LASTError != 0)
	//	DisplayErrorMessage(LASTError);

	return CloseConnection();
}

BOOL CCommOperations::ExecuteACommand(int *data)
{
	if (!StartCommOperation(3))
	{
		EndCommOperation();
		return FALSE;
	}

	if (PingCR10(20) || PingCR10(500) || PingCR10(1000))
	{
		// if the CR10 responds within 20 miliseconds, or 50, or 1000...
		
		// give it 5 tries
		for (int t = 0; t < 5; t++)
		{
			readBufPos = 0;
			Send("1A\r",3);
			for (int i = 0; i < 10; i++)
			{
				WaitForData();
				if (readBufPos > 53)
					break;
			}
			if (readBufPos > 53)
				break;
			WaitForData(100);
		}
		
		if (readBufPos <= 53)
		{
			EndCommOperation();
			return FALSE;
		}
	
		// WaitForData(20);
		// UpdateGlobalDebugInfo();
		
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
				if (B >= '0' && B <= '9'&& whichData >= 0)
				{
					curNumber *= 10;
					curNumber += (B - '0');
				}
			}
			if (B == ' ' || B == '\0' || B == '.')
			{
				if (curNumber != 0)
				{
					data[whichData] = curNumber;
					if (whichData == ERROR_INFO_1 || 
						whichData == ERROR_INFO_2 )
						whichData++;
					curNumber = 0;
					whichData = -1;
				}
			}

		} while (readBuf[bufPos] != '\0');
		
		EndCommOperation();

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
	{
		EndCommOperation();
		return FALSE;
	}

	return TRUE;
}

BOOL CCommOperations::SetLocationAndVerify(int wLocation, double &oldValue, const int newValue, int nRepetitions)
{
	char buff[10];
	wsprintf(buff,"%i",newValue);
	return SetLocationAndVerify(wLocation,oldValue,buff,nRepetitions);
}

BOOL CCommOperations::SetLocationAndVerify(int wLocation, double &oldValue, const double newValue, int nRepetitions)
{
	return SetLocationAndVerify(wLocation,oldValue, ValueToString(newValue).GetBuffer(0),nRepetitions);
}

BOOL CCommOperations::SetLocationAndVerify(int wLocation, double &oldValue, char *newValue, int nRepetitions)
{
	// this one actually does it...
	// converting a string to a double???
	double correctValue = StringToValue(newValue);
	
	for (int t = 0; t < nRepetitions; t++)
	{
		if (ExecuteICommand( wLocation, oldValue, newValue, 1 ))
		{
			if (pDoc->GetInputLocations( &wLocation, 1, &oldValue,3 ))
			{
				if (fabs(oldValue - correctValue) < 0.01)
					return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CCommOperations::ExecuteICommand(int whichLocation, double &oldValue, char *newValue, int nRetries )
{
	static int nping15 = 0;
	static int nping50 = 0;
	static int nping200 = 0;
	static int nping1000 = 0;
	static int ntimes = 0;
	static int nping = 0;

	int failCode = 0;

	bool ping = false;
	double checkSum;
	int mySum;

	for (int t = 0; t < nRetries; t++)
	{
		failCode = 0;
		ntimes++;
		if (PingCR10(15))
		{
			nping15++;
			ping = true;
		}
		else if (PingCR10(50))
		{
			nping50++;
			ping = true;
		}
		else if (PingCR10(200))
		{
			nping200++;
			ping = true;
		}
		else if (PingCR10(1000))
		{
			nping1000++;
			ping = true;
		}
		
		if (ping)
		{
			nping++;

			char SendBuff[20];
			/*
			if (newValue)
				wsprintf(SendBuff,"%iI\r%s\r", whichLocation, newValue);
			else
				wsprintf(SendBuff,"%iI\r\r", whichLocation);

			readBufPos = 0;
			int SendLength = strlen(SendBuff);
			Send(SendBuff, SendLength);
			*/
			wsprintf(SendBuff,"%iI\r", whichLocation);
			Send(SendBuff, strlen(SendBuff));
			if (WaitOnChar("+-",75,NULL))
			{
				if (newValue)
					wsprintf(SendBuff,"%s\r", newValue);
				else
					wsprintf(SendBuff,"\r");
				
				Send(SendBuff, strlen(SendBuff));
				if (WaitOnChar("C",150,NULL) == 'C')// && WaitOnChar("*",125,NULL,5)=='*')
				{
					for (int cPos = readBufPos; cPos > 0 && readBuf[cPos] != 'C'; cPos--);
					if (readBufPos - cPos <= 4)
					{
						DWORD LastReadTime = timeGetTime();
						while (readBufPos - cPos <= 4 && timeGetTime() - LastReadTime < 200)
							WaitForData();
						if (readBufPos - cPos <= 4)
							return FALSE;
					} 

					mySum = 0;
						
					for (int i = 0; readBuf[i] != 'C'; i++)
					{
						if (readBuf[i] == '*')
							mySum = 0;
						else
							mySum += readBuf[i];
					}
					mySum += 'C';
					checkSum = StringToValue(&readBuf[i]);
					if (round(checkSum) == mySum)
					{
						for (; readBuf[i] != '-' && readBuf[i] != '+'; i--);
						oldValue = StringToValue(&readBuf[i]);
						return TRUE;
					}
					else // bad checksum
						failCode = 1;
				}
				else // no character C returned
					failCode = 2;
			}
			else // no initial response to input location...
				failCode = 3;	
		} 
		else  // no ping echoed
			failCode = 4;
	}
	
	CString note;
	if (failCode == 1)
		note = "checkSum = "+ValueToString(checkSum) + " mySum = " + IntToString(mySum);
	else if (failCode == 2)
		note = "no character 'C' returned";
	else if (failCode == 3)
		note = "no initial response";
	else if (failCode == 4)
		note = "no ping echoed";
	pDoc->m_ErrorFiles->WriteHistory(CString("ExecuteIComm() fail = ")+IntToString(failCode),note);
	pDoc->m_ErrorFiles->WriteHistory(CString("  "),CString("number of retries = ") + IntToString(nRetries));

	return FALSE;

}

BOOL CCommOperations::ExecuteKCommand(BOOL GetInputLocations, int InputLocRequests){
	DWORD biggestPause = 0;
	DWORD pause = 0;
	static DWORD biggestSuccessfulPause = 0;
	static DWORD biggestUnsuccessfulPause = 0;

	//PurgeComm( COMDEV( TalkInfo ) , PURGE_TXCLEAR | PURGE_RXCLEAR);
//	DWORD totalTime;
	DWORD startTime = timeGetTime();
	DWORD lastReadTime = startTime;
	int expectedSize;
	if (PingCR10(150))
	{	
		readBufPos = 0;
		int pReadBufPos = readBufPos;
			
		Send("K\r",2);
		expectedSize = 12 + needPortByte + GetInputLocations * InputLocRequests * 4;
		do 
		{
			WaitForData();
			if (readBufPos != pReadBufPos){
				lastReadTime = timeGetTime();
				pReadBufPos = readBufPos;
			}
			if (readBufPos >= expectedSize)
				break;
			pause = timeGetTime() - lastReadTime;
			if (pause > biggestPause)
			{
				biggestPause = pause;
			}
		} 
		while (pause < 200 + (unsigned) InputLocRequests * 2);

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

// GetFinalStorage:  how to understand the return values
//
//		returned (BOOL) &Value (int)	Understanding
//		0 (failure)		-1				timed out... didn't receive any bytes for too long
//		0 (failure)		0				failed after too many retries
//		0 (failure)		Positive value	CheckSignature verified that the bytes were correct,
//										but an ArrayID not matching anything in the FSFiles
//										was returned by the CR10X.
//		1 (success)		Positive value	How far to move the DSP							

BOOL CCommOperations::GetFinalStorage(int &Value, HANDLE FSFilesOut[], CLADAControlModuleDoc * pDoc, int LocsToRetrieve /*=DOWNLOAD_SIZE*/){
	//static int FSLocationsWrittenThisFile = 0;
	
	DWORD bytesWritten;
	int pReadBufPos = 0;
	int i = 0; 
	int j = 0;
	char SendBuf[80];

	//ExecuteACommand();
	// this will retrieve DSP and FilledLocations

	/*
	if (LastDSP > FilledLocations)
	{
		// if the next location for data to be retrieved has passed the
		// number of filled locations, there are two possibilities:
		// 1.  Final Storage is totally full and storage has wrapped around
		//     to the beginning.
		// 2.  The number of filled locations is still growing.  In this case we
		//	   have probably retrieved all the storage we can.
		if (nFilledLocationsAtStartOfGetFinalStorage == FilledLocations)
			LastDSP -= FilledLocations;
		else
		{
			// theoretically, this should not happen.  The number of locations
			// to collect is determined before this is ran based on the number
			// of new data.  If LastDSP is greater than the number of filled
			// locations, then GetFinalStorage() should not be called because 
			// all of the new data (at the start) should have been collected already.  
			
			return FALSE;
		}
	}
	*/

	// if ( ((DSP < LastDSP) ? (DSP + FilledLocations) : DSP) 
	//	- LastDSP < LocsToRetrieve)
	//	return FALSE;
	// If there are not enough new storage locations
	// to read FS data, return FALSE
	
	//SetWindowNumber (IDC_FS_POSITION, 0);
	
	wsprintf(SendBuf,"%iF\r",LocsToRetrieve);
	
	int ExpectedBytes = strlen(SendBuf) + LocsToRetrieve * 2 + 3;
	int nextByteToProcess;
	int moveDSP;
	int newLocs;
	int arrayIDreturned = 0;
	int firstFSLocation = ExpectedBytes - LocsToRetrieve * 2 - 2;
	int * writePos = new int[pDoc->nFSFiles];
	int * bytesToWrite = new int[pDoc->nFSFiles];
	char * dataToWrite = new char[LocsToRetrieve * 10 * pDoc->nFSFiles];

	int nBadIDs = 0;
	//SetTimeBox(2);

	for (int t = 0; t < FS_RETRIES; t++) {
		// move MPTR to LastDSP
		for (int u = 0; (MoveMPTR(LastDSP) != LastDSP) && u < 3; u++);
		if (u == 3)
		{
			//SetWindowNumber (IDC_FS_POSITION, 1);
			delete [] dataToWrite;
			delete [] writePos;
			delete [] bytesToWrite;
			Value = 0;
			return 0;
		}
		//SetTimeBox(3);

		for (int i = 0; i < pDoc->nFSFiles; i++)
		{
			writePos[i] = 0;
			bytesToWrite[i] = 0;
		}

		readBufPos = 0;
		newLocs = 0;
		moveDSP = 0;
		nextByteToProcess = firstFSLocation;

		Send(SendBuf, strlen(SendBuf));
		DWORD lastReadTime = 0;
		i = 0;
		while (readBufPos < ExpectedBytes){
			pReadBufPos = readBufPos;
			Sleep(20);//WaitForData();
			i++;
		
			if (pReadBufPos == readBufPos){
				if (lastReadTime == 0)
					lastReadTime = timeGetTime();
				else {
					if (timeGetTime() - lastReadTime > 125){
						delete [] dataToWrite;
						delete [] writePos;
						delete [] bytesToWrite;
						Value = -1;
						return FALSE;
					}
				}
			}
			else {
				lastReadTime = 0;
				if (readBufPos - nextByteToProcess >= 2 &&
					arrayIDreturned == 0)
					arrayIDreturned = PrepareDataToWrite(LocsToRetrieve, pDoc, readBufPos, readBuf, nextByteToProcess, dataToWrite, writePos, bytesToWrite, moveDSP, newLocs);
			}
			//SetTimeBox(4);
		}
		
		if (arrayIDreturned == 0)
			arrayIDreturned = PrepareDataToWrite(LocsToRetrieve, pDoc, readBufPos, readBuf, nextByteToProcess, dataToWrite, writePos, bytesToWrite, moveDSP, newLocs);
				
		if (CheckSignature(firstFSLocation, FINALSTORAGE))
		{
			if (arrayIDreturned)
			{
				if (nBadIDs < 2)
					 nBadIDs++;
				else
				{
					delete [] dataToWrite;
					delete [] writePos;
					delete [] bytesToWrite;
					Value = arrayIDreturned;
					return FALSE;
				}
			}
			else
			{
				nBadIDs = 0;
				break; // write this data now
			}
		
		}
		// if the signature was bad then the arrayIDreturned will
		// be bad too.  reset the arrayID and try getting the data again.
		arrayIDreturned = 0;
	}
	if (t == FS_RETRIES){
		delete [] dataToWrite;
		delete [] writePos;
		delete [] bytesToWrite;
		Value = 0;
		return FALSE; // returning -1 means it failed
	}
	
	//wsprintf(SendBuf,"\n**********| Final Storage Data Written: %s  |**********",s);
	//if (!WriteFile(FSFileOut, SendBuf, strlen(SendBuf), &bytesWritten, NULL))
	//	DisplayErrorMessage(GetLastError());
	
	for (int whichFS = 0; whichFS < pDoc->nFSFiles; whichFS++)
	{
		if (!WriteFile(FSFilesOut[whichFS], &dataToWrite[whichFS * (LocsToRetrieve * 10)], bytesToWrite[whichFS], &bytesWritten, NULL))
		DisplayErrorMessage(GetLastError());
	}

	LastDSP += moveDSP;
	if (LastDSP > FilledLocations)
		LastDSP -= FilledLocations;

	delete [] dataToWrite;
	delete [] writePos;
	delete [] bytesToWrite;
	
	//SetTimeBox(5);
	Value = moveDSP;
	return TRUE;
}

BOOL CCommOperations::IsConnected(){
	if (TalkInfo)
		return CONNECTED(TalkInfo);
	return FALSE;
}

/*
int CCommOperations::MoveMPTR(int whichLocation){

	if (whichLocation < 0)
		return 0;

	char SendBuf[10];

	int newLocation = 0;

	//if (whichLocation > FilledLocations)
	//	whichLocation -= FilledLocations;

	if (PingCR10(20)||PingCR10(20))
	{
		wsprintf(SendBuf, "%iG\r", whichLocation);

		readBufPos = 0;
		Send(SendBuf,strlen(SendBuf));

		//if (WaitOnChar("C", 200, NULL) != 'C')
		//	return 0;
	
		for (int i = 0; i < 10; i++) 
		{
			//UpdateGlobalDebugInfo();
			if (readBufPos > 21)
				break;
			//WaitForData(30);
			Sleep(20);
		} 
			
		for ( i = 4; readBuf[i] != 'L' && i < 40; i++);
		if (i == 40) return 0;
		
		for (; readBuf[i] != '.' && i < 40; i++){
			if (readBuf[i] >= '0' && readBuf[i] <= '9'){
				newLocation *= 10;
				newLocation += readBuf[i] - '0';
			}
			if (readBuf[i] == 'C')
				break;
		}
		if (i == 40) return 0;
		//SetWindowNumber( IDC_MPTR_LOCATION, newLocation );
		return newLocation;
	}
	return 0;
}
*/

int CCommOperations::MoveMPTR(int whichLocation){

	if (whichLocation < 0)
		return 0;

	char SendBuf[10];

	int newLocation = 0;

	//if (whichLocation > FilledLocations)
	//	whichLocation -= FilledLocations;

	wsprintf(SendBuf, "%iG\r", whichLocation);

	for (int t = 0; t < 2; t++){
		readBufPos = 0;
		Send(SendBuf,strlen(SendBuf));

		Sleep(50);
		for (int i = 0; i < 30; i++) {
			//UpdateGlobalDebugInfo();
			if (readBufPos > 21)
				break;
			Sleep(30);
		} 
		
		if (readBufPos > 21)
			break;
		
		PingCR10(20)||PingCR10(20)||PingCR10(50);
		//if (DO_RECONNECT)
		//	if (Reconnect())
		//		if (!(PingCR10(20)||PingCR10(50)||PingCR10(1000)))
		//			return 0;
		//else
		//	return 0;

	} 

	for (int i = 4; readBuf[i] != 'L' && i < 40; i++);
	if (i == 40) return 0;
	for (; readBuf[i] != '.' && i < 40; i++){
		if (readBuf[i] >= '0' && readBuf[i] <= '9'){
			newLocation *= 10;
			newLocation += readBuf[i] - '0';
		}
		if (readBuf[i] == 'C')
			break;
	}
	if (i == 40) return 0;
	//SetWindowNumber( IDC_MPTR_LOCATION, newLocation );
	return newLocation;
}

BOOL CCommOperations::PingCR10(DWORD miliseconds, BOOL DoSwitchMode)
{
	static int nConsecFail = 0;

	char CR = '\r';//ASCII_CR;
	readBufPos = 0;
	int preadBufPos;
	//EscapeCommFunction( COMDEV( TalkInfo), SETDTR );

	DWORD startTime = timeGetTime();
	
	if(!WriteCommBlock(&CR, 1))
	{
		pDoc->m_ErrorFiles->WriteHistory(IDS_E_COMMUNICATIONS, IDS_E_COMMUNICATIONS_FAILED_TO_WRITE);
		DWORD LE = GetLastError();
		if (LE == 997)
		{	// overlapped IO operation is in progress
			pDoc->m_ErrorFiles->WriteHistory(IDS_E_COMMUNICATIONS, IDS_E_COMMUNICATIONS_OVERLAPPED_IO);
		}
		//DisplayErrorMessage(LE);
		return FALSE;
	}
	else
	{
		pDoc->AssertValid();
		int i;
		do 
		{
			preadBufPos = readBufPos;
			Sleep(5);//WaitForData();
			for ( i = preadBufPos; i < readBufPos; i++)
			{
				if (i > 1 && readBuf[i] == '*' && readBuf[i-1] == 10 && readBuf[i-2] == 13)
				{
					nConsecFail = 0;
					PossiblyDisconnected = FALSE;
					return TRUE;
				}
			}
		} 
		while (timeGetTime() - startTime < miliseconds);
		char message[200];
		char readGood = (i > 1 && readBuf[i] == '*' && readBuf[i-1] == 10 && readBuf[i-2] == 13) ? 'T':'F';
				
		wsprintf(message,"Ping failed, timeout was %i ms.  readBuf good:%c", miliseconds, readGood);
		WriteToCommLog(message);
	}
	nConsecFail++;
	if (nConsecFail > 5)
	{
		// we may be disconnected
		PossiblyDisconnected = TRUE;
	}
	return FALSE;
}

int CCommOperations::PrepareDataToWrite(int LocsToRetrieve, 
										 CLADAControlModuleDoc *pDoc, 
										 int unprocessedBytes, 
										 char *firstDataByte, 
										 int &nextByteToProcess, 
										 char *dataToWrite, 
										 int writePos[], 
										 int bytesToWrite[], 
										 int &MoveDSP, 
										 int &LocationsRetrieved)
{
	static int lastArrayID = 0;
	bool haveFoundArrayID = false;

	if (lastArrayID == 0)
		haveFoundArrayID = false;

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
			{
				haveFoundArrayID = true;
				lastArrayID = number;
				wsprintf(numberOut, "\r\n%i",number);
				for (int i = 0; i < pDoc->nFSFiles; i++)
				{
					if (pDoc->m_FSOutputTable[i].m_ArrayID == lastArrayID)
						bytesToWrite[i] = writePos[i];
				}
				MoveDSP = LocationsRetrieved - 1;
			}
			break;
		case 2:	//We are writing a dummy value
			wsprintf(numberOut,"\tDUMMY");
			break;
		case 4:
		case 5:	//We are writing a low or high resolution number
			// append a \t to the beginning of the number buffer...
			for (int i = 0; numberOut[i]; i++);
			
			numberOut[i+1] = '\0';
			for (; i; i--)
			{
				numberOut[i] = numberOut[i-1];
			}
			numberOut[i] = '\t';
			break;
		}

		for (int whichFS = 0; whichFS < pDoc->nFSFiles; whichFS++)
		{
			if (pDoc->m_FSOutputTable[whichFS].m_ArrayID == lastArrayID)
			{
				strcpy(&dataToWrite[writePos[whichFS] + (LocsToRetrieve * 10) * whichFS], numberOut);
				writePos[whichFS] += strlen(numberOut);
				break;
			}
		}
		if (whichFS == pDoc->nFSFiles && haveFoundArrayID)
		{
			// no array ID was found in all the FS files for the data which was retrieved...
			return lastArrayID;
		}
	}
	return 0;
}

BOOL CCommOperations::ProcessInputLocations(char * ptrBuf, double InputLocValue[], int InputList[], int InputLocRequests){
	unsigned char iLocBytes[4];
	double sign;
	int exponent;
	double mantissa;
	double result;
	//unsigned int m;
	unsigned char mask = 1 << 7;
	bool isError = false;

	for (int i = 0; i < InputLocRequests; i++){
		for (int j = 0; j < 4; j++)
			iLocBytes[j] = ptrBuf[8 + needPortByte + i * 4 + j];
		if (iLocBytes[0] == 0 && iLocBytes[1] == 0 && 
			iLocBytes[2] == 0 && iLocBytes[3] == 0)
		{
			result = 0.0;
			isError = false;
		}
		else if ((iLocBytes[0] == 0xFF || iLocBytes[0] == 0x7F) && iLocBytes[1] == 0xFF && 
			iLocBytes[2] == 0xFF && iLocBytes[3] == 0xFF)
		{
			result = -99999.0;
			isError = true;
		}
		else {
			/*
			sign = 1 - ((iLocBytes[0] & mask) >> 1);
			exponent = (iLocBytes[0] & 0xFF) - 0x40;
			//iLocBytes[0] = 0;
			//*m <<= 8;
			m = iLocBytes[1] * 0x10000 + iLocBytes[2] * 0x100 + iLocBytes[3];
			mantissa = double(m & 0x7FFFFF) / double(0xFFFFFE) + .5; 
			//mantissa = iLocBytes[1] %= 128;
			result = sign * (mantissa * pow(2, exponent));
			*/
			sign = (iLocBytes[0] & mask) ? -1 : 1;
			exponent = (iLocBytes[0] & ~mask) - 0x40;
			mantissa = double(iLocBytes[1] * 0x10000 + iLocBytes[2] * 0x100 + iLocBytes[3]) / double(0x1000000);
			result = sign * (mantissa * pow(2, exponent));
			isError = false;
		}
		
		InputLocValue[InputList[i] - 1] = result; // to make it zero-based
		if (!isError && (result < -INTERMEDIATE_STORAGE_RANGE || result > INTERMEDIATE_STORAGE_RANGE)) 
			//  Campbell Scientific High Resolution number format has a magnitute of range
			// from .00001 to 99999
		{
			return FALSE;
		}
		//InputLocValue[InputList[i] - 1] = InputList[i];
	}
	return TRUE;
}

/*
BOOL CCommOperations::Reconnect(BOOL reUpdate){
	//SetWindowNumber( IDC_RECONNECTS, ++reconnects );	
	//consecReconnects++;

	if (CONNECTED(TalkInfo)){
		WaitForData(100);
		EndCR10Comm();// this includes CloseConnection()
		WaitForData(100);
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
*/

BOOL CCommOperations::RetrieveFinalStorage(HANDLE FSFilesOut[], CLADAControlModuleDoc * pDoc, BOOL GetLastFSL)
{
	if (!ExecuteACommand()) // this retrieves the current DSP
		return FALSE;
	if (!StartCommOperation(4))
	{
		EndCommOperation();
		return FALSE;
	}

	//nFilledLocationsAtStartOfGetFinalStorage = FilledLocations;
	//GetFSUnderWay = TRUE;
	if (LastDSP == 0)
	{
		if (FStartRetrievalFromCurrentPosOnStart)
			LastDSP = DSP; //
		else
			LastDSP = 1;
	}

	pDoc->m_FSOutputTable[0].m_LastNumberRetrieved = 0;

	int InitialToRetrieve;
	int LocsToRetrieve;

	if (DSP > LastDSP)
		LocsToRetrieve = InitialToRetrieve = DSP - LastDSP;
	else if (LastDSP > DSP)
		LocsToRetrieve = InitialToRetrieve = DSP + FilledLocations - LastDSP;
	else // LastDSP == DSP
	{
		EndCommOperation();
		return FALSE;
	}

	BOOL DoProgressBox = FALSE;
	BOOL downloadCancelled = FALSE;
	char wText[100];

	ProgressDialog *GetFSProgress = NULL;
			
	if (InitialToRetrieve > DOWNLOAD_SIZE * 2)
	{
		GetFSProgress = new ProgressDialog(&downloadCancelled, 
			"Downloading final storage locations from the CR10.", 
			"Downloading Final Storage Locations...", 
			"Stop", TRUE, NULL);
		GetFSProgress->Create(PROGRESS_DIALOG);
	}
		
	int nSuccessiveFailures = 0;
	int value;

	
	while ( (LocsToRetrieve >= DOWNLOAD_SIZE ||
			LocsToRetrieve > 0 && GetLastFSL) && 
			!downloadCancelled )
	{
		//SetTimeBox(1);
		
		int nRetrieved = 0;
	
		if (GetFinalStorage(value, FSFilesOut, pDoc))
		{
			pDoc->m_FSOutputTable[0].m_LastFailCode=1;
			nRetrieved = value;
			nSuccessiveFailures = 0;
		}
		else
		{
			if (value == -1 || value == 0) // timed out or too many repetitions
			{
				if (value == -1)
					pDoc->m_FSOutputTable[0].m_LastFailCode=3;
				else
					pDoc->m_FSOutputTable[0].m_LastFailCode=4;
				nSuccessiveFailures++;
				if (nSuccessiveFailures > 4)
				{
					downloadCancelled = TRUE;
					MessageBox( IDS_M_FS_FAILED, IDS_PROGRAM_NAME );
				}
			}
			else
			{
				// an array ID not matching anything in the FS files was returned	
				pDoc->m_FSOutputTable[0].m_LastFailCode=2;
				downloadCancelled = TRUE;
				char message[300];
				char mTitle[40];
				wsprintf(mTitle,"%s",Strings.get(IDS_PROGRAM_NAME));
				wsprintf(message,"%s",Strings.get(IDS_M_BAD_ARRAY_ID));
				wsprintf(message,message,value);
				NotificationBox(message, "Error", MB_OK, FALSE, INFINITE);
				pDoc->m_ErrorFiles->WriteHistory(IDS_E_COMMUNICATIONS, IDS_E_COMMUNICATIONS_BAD_ARRAY);
				//NotificationBox(IDS_PROGRAM_NAME, NO_TITLE, MB_OK, FALSE, 6000);
			}
		}

		MSG Msg;
		
		while(PeekMessage( &Msg,         // message information
			NULL,           // handle to window
			0,//WM_MOUSEFIRST,  // first message  
			0,//WM_MOUSELAST );  // last message
			PM_REMOVE /*| PM_NOYIELD*/)) //wRemoveMsg
			DispatchMessage( &Msg );  // message information);
		
			//SetTimeBox(6);

		if (downloadCancelled) 
			break;
			
		//LocsToRetrieve = ((DSP < LastDSP) ? (DSP + FilledLocations) : DSP) - LastDSP;
		LocsToRetrieve -= nRetrieved;
		
		if (GetFSProgress){
			wsprintf(wText,"%i final storage locations left to retrieve.", LocsToRetrieve);
			GetFSProgress->SetInfo(100 - (100 * LocsToRetrieve / InitialToRetrieve), wText);
		}
		//SetTimeBox(7);
	}

	if (GetFSProgress)
	{
		GetFSProgress->Close();
		delete GetFSProgress;
	}
	
	pDoc->m_FSOutputTable[0].m_LastNumberRetrieved = InitialToRetrieve - LocsToRetrieve;

	EndCommOperation();

	if (downloadCancelled)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL CCommOperations::Send(const LPSTR data, int bytesToSend)
{
	for (int t = 0; t < 5; t++)
	{
		if (WriteCommBlock(data, bytesToSend))
		{
			//UpdateGlobalDebugInfo();
			return TRUE;
		}
		WCBuffRepeats++;
		//if (DO_RECONNECT){
		//	Reconnect();
		//	(PingCR10(20) || PingCR10(50) || PingCR10(500) || PingCR10(1000));
		//}
	}
	//UpdateGlobalDebugInfo();
	return FALSE;

}

BOOL CCommOperations::SetJCommand(BOOL DoUserFlags, BOOL DoPortFlags, 
	BOOL DoInputLocations, int *InputLocList, int InputLocRequests)
{
	static BOOL GFS = FALSE; // get final storage variable

	if ( !IsRequestDifferent(DoInputLocations, InputLocList, InputLocRequests) 
			&& !DoPortFlags && !DoUserFlags )
		return TRUE;
	
	//DWORD sTime = timeGetTime();
	int expectedSize;

	if ( PingCR10(100) || PingCR10(500) || PingCR10(1000) )
	{
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
					//else if(ProgramCounter % FreqTable[toggleFlagsFreqLevel[i][USERFLAGS]] == 0)
					//	uFB++;
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
					//else if(ProgramCounter % FreqTable[toggleFlagsFreqLevel[i][PORTFLAGS]] == 0)
					//	pFB++;
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
		int i = 0;

		if (DoInputLocations)
		{
			for (; i < InputLocRequests; i++){
				sendBuf[8 + needPortByte + i] = char(InputLocList[i]);
				//InputLocsRequested[i] = InputLocList[i];
			}
		}
		
		sendBuf[8 + needPortByte + i] = '\0';
		
		readBufPos = 0;
		int pReadBufPos = readBufPos;
		Send(sendBuf, 9 + needPortByte + i);
		DWORD startTime = timeGetTime();
		DWORD LastReadTime = startTime;
		expectedSize = 11 + needPortByte + i;
		do 
		{
			WaitForData();
			if (readBufPos != pReadBufPos)
			{
				LastReadTime = timeGetTime();
				pReadBufPos = readBufPos;
			}
			if (readBufPos == expectedSize){
				NeedSetJCommand = FALSE;
				return TRUE;
			}
		} 
		while (timeGetTime() - LastReadTime < 250 + (unsigned) i * 2);
	}
	//DWORD tTime = timeGetTime() - sTime;
	return FALSE;

}

/*
const char * CCommOperations::GetCR10Time(CTime *returnTime)
{
	if (!StartCommOperation(5))
	{
		EndCommOperation();
		return NULL;
	}

	int yPos;
	int Year, JDay, Hour, Minute, Second;

	DWORD eTime;

	if (PingCR10(20)||PingCR10(20))
	{
		//for (int t = 0; t < 2; t++){
		readBufPos = 0;
		Send("C\r", strlen("C\r"));
		DWORD startTime = timeGetTime();
		yPos = -1;
		
		do {
			WaitForData();
			if (readBufPos > 30){
				while (readBuf[++yPos]!= 'Y' && yPos < 20);
				EndCommOperation();
				Year = StringToInt(&readBuf[yPos+1],2);
				JDay = StringToInt(&readBuf[yPos+5],4);
				Hour = StringToInt(&readBuf[yPos+12],2);
				Minute = StringToInt(&readBuf[yPos+15],2);
				Second = StringToInt(&readBuf[yPos+18],2);
				if (returnTime)
				{
					if (Year > 35)
						Year = 35;
						//CTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nDST = -1 );
					*returnTime = CTime(2000+Year,1,1,0,0,0);
					*returnTime += CTimeSpan(JDay-1,Hour,Minute,Second); 	
				}
				wsprintf(timeBuf, "%2i:%02i:%02i",Hour, Minute, Second);
				eTime = timeGetTime() - startTime;
				
				return timeBuf;
			}
			eTime = timeGetTime() - startTime;
		} while ( eTime < 120);
	
	}
	
	EndCommOperation();
	return NULL;
}
*/
const char * CCommOperations::ProcessCR10Time(CLADAControlModuleDoc * pDoc)
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

	if (pDoc)
	{
		CTime curTime = CTime::GetCurrentTime();
		
		pDoc->CR10Time = CTime(curTime.GetYear(),curTime.GetMonth(),
								curTime.GetDay(),hours,minutes,seconds / 10);
		pDoc->CR10TimeUpdated = curTime;				 	
	}
	
	// this is actually seconds * 10
	//wsprintf(timeBuf, "%2i:%02i:%02i.%1i",hours, minutes, seconds / 10, seconds % 10);
	wsprintf(timeBuf, "%2i:%02i:%02i",hours, minutes, seconds / 10);
	if (hours > 24 || minutes > 60 || seconds > 600)
	{
		int a = 0;
		// means time is bad!!!!!!!
		pDoc->m_ErrorFiles->WriteHistory("Communication Failure","Bad time returned by CR10X");
	}
	return timeBuf;
}

BOOL CCommOperations::ChangeCR10Time(int hour, int minute, int second, int day, int year) // = 0, = 0
{
	if (!StartCommOperation(6))
	{
		EndCommOperation();
		return FALSE;
	}

	if (PingCR10(20)||PingCR10(20)||PingCR10(100))
	{
		char newTimeBuff[30];
		
		if (day == -1)
			wsprintf(newTimeBuff,"%02i:%02i:%02iC\r", hour, minute, second);
		else
		{
			if (year == -1)
				year = (CTime::GetCurrentTime()).GetYear();
			year %= 100;	
			wsprintf(newTimeBuff,"%02i:%03i:%02i:%02i:%02iC\r", year, day, hour, minute, second);
		}
		for (int t = 0; t < 3; t++){
			readBufPos = 0;
			Send(newTimeBuff, strlen(newTimeBuff));
			DWORD startTime = timeGetTime();
			do {
				WaitForData(20);
				if (readBufPos > 17)
				{
					EndCommOperation();
					return TRUE;
				}
			} while (timeGetTime() - startTime < 300);
			int r = readBufPos;
			WaitForData();
			PingCR10(20)||PingCR10(20)||PingCR10(50);
		}
		pDoc->m_ErrorFiles->WriteHistory("Update Time","Failure");
		pDoc->m_ErrorFiles->WriteHistory("Command",newTimeBuff);
	}
	EndCommOperation();
	return FALSE;
}

/*
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
	
	return TRUE;
}
*/
char CCommOperations::WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow, int startPos){
	DWORD startTime = timeGetTime();
	int pReadBufPos = startPos;
	do {
		WaitForData();

		//MSG Msg;
		//if (PeekMessage( &Msg,         // message information
		//	NULL,           // handle to window
		//	0,//WM_MOUSEFIRST,  // first message  
		//	0,//WM_MOUSELAST );  // last message
		//	PM_REMOVE /*| PM_NOYIELD*/)) //wRemoveMsg
		//	DispatchMessage( &Msg );  // message information);

		for (int i = pReadBufPos; i < readBufPos; i++){
			for (int cpos = 0; c[cpos] != '\0'; cpos++){
				if (readBuf[i] == c[cpos])
					return c[cpos];
			}
		}
		pReadBufPos = readBufPos;
	
	} while (timeGetTime() - startTime < timeOut && (!stopNow || !*stopNow));
	return NULL;
}


BOOL CCommOperations::IsRequestDifferent(BOOL DoLocations, int *InputLocList, int InputLocRequests)
{
	BOOL IsDifferent = FALSE;
	
	if (!DoLocations)
	{
		IsDifferent = nLastRequest;
		nLastRequest = 0;
		return IsDifferent;
	}
	
	if (nLastRequest != InputLocRequests)
		IsDifferent = TRUE;
	else
	{
		IsDifferent = memcmp(InputLocList,LastInputRequest,InputLocRequests * sizeof(int));
	}
	if (IsDifferent){
		memcpy(LastInputRequest,InputLocList,sizeof(InputLocRequests));
		nLastRequest = InputLocRequests;
	}
	return IsDifferent;
}


BOOL CCommOperations::ToggleFlag(int wFlag, BOOL IsUser) // = TRUE
{
	memset(toggleFlags,0,sizeof(int) * 8 * 2);
	toggleFlags[wFlag-1][!IsUser] = 1;
	if (!StartCommOperation(7))
	{
		EndCommOperation();
		return FALSE;
	}
	for (int wTry = 0; wTry < 5 && !SetJCommand(IsUser,!IsUser,FALSE); wTry++);
	char message[80];
	wsprintf(message,"ToggleFlag(wFlag = %i) failed.",wFlag);
	if (wTry == 5)
		pDoc->m_ErrorFiles->WriteHistory("Comm. Error",message);
	ExecuteKCommand(FALSE,0);
	EndCommOperation();
	return wTry != 5;
}

BOOL CCommOperations::SetFlag(int wFlag, BOOL state, BOOL IsUser) // = TRUE
{
	BOOL Success;
	BOOL fState;
	if ((Success = GetFlag(wFlag,fState,IsUser)) && fState != state)
		return ToggleFlag(wFlag,IsUser);
	return Success;
}

BOOL CCommOperations::GetFlag(int wFlag, BOOL & flagState, BOOL IsUser) // = TRUE
{
	if (!StartCommOperation(8))
	{
		EndCommOperation();
		return FALSE;
	}

	for (int wTry = 0; wTry < 5 && !SetJCommand(FALSE,FALSE,FALSE);	wTry++);
	if (wTry == 5)
	{
		MessageBox("Unable to retrieve flag state.");
		return FALSE;
	}
	ExecuteKCommand(FALSE,0);
	EndCommOperation();

	unsigned char mask = 1 << 7;
	unsigned char ufbyte = readBuf[7];

	for (int i = 0; i < 8; i++){
		if (8 - i == wFlag)
		{
			flagState = (mask & ufbyte) >> 7;
			return TRUE;
		}
		ufbyte <<= 1;
	}
	return FALSE; // function should never reach this point
}

// THERE SHOULD BE GETALLFLAGS AND SETALLFLAGS functions

BOOL CCommOperations::UpdateCR10Time()
{
	struct tm* osTime;  // A pointer to a structure containing time 
                    // elements.
	CTime time = CTime::GetCurrentTime();
	osTime = time.GetLocalTm( NULL );
	
	return ChangeCR10Time(time.GetHour(), time.GetMinute(), 
		time.GetSecond() + 1, osTime->tm_yday + 1, time.GetYear());
}

BOOL CCommOperations::SwitchMode(int mode) // = 0
{
	CWaitCursor wCursor;
	int k = 0;
	char ErrCode[3] = "--";
	char SendBuff[20];

	//if (PingCR10(20)||PingCR10(50)||PingCR10(50))
	//	return TRUE;

	readBufPos = 0;
	Send("*",1);
	WaitForData();
	Send("0",1);
	// we may get err message stuff now... be patient
	char whichChar = WaitOnChar("*><",2000, NULL);
	if (whichChar == '*')
		return TRUE;

	for (int t = 0; t < 5; t++)
	{
		readBufPos = 0;
		k = 0;
		Send("\r\r\r",3);
		while (readBufPos == 0 && !PingCR10(1000) && k++ < 6);
		if (readBufPos > 0 && PingCR10(20) || PingCR10(50) || PingCR10(50))
			return TRUE;
		
		SendBuff[0] = char(0x05); 
		SendBuff[1] = char(0x05); 
		Send(SendBuff,2);
		WaitForData(50);
		Send("\r",1);
		WaitForData(50);

		Send("*0",2);
		WaitForData(50);
		Send("\r",1);

		// we may get err message stuff now... be patient
		char whichChar = WaitOnChar("*><",3000, NULL);
		if (whichChar == '*')
			return TRUE;
		Send("*1",2);
		WaitForData(50);
				
		readBufPos = 0;
		while (readBufPos == 0 && !PingCR10(1000) && k++ < 6);
		if (readBufPos > 0 && PingCR10(20) || PingCR10(50) || PingCR10(50))
			return TRUE;
		Send("EE",2);
		WaitForData(1000);
	}

	return FALSE;
}

BOOL CCommOperations::WaitOnSequence(const char *c, DWORD timeOut, BOOL *stopNow, int startPos){
	DWORD startTime = timeGetTime();
	int pReadBufPos = startPos; 
	int seqLength = strlen(c); // length of the sequence to check for

	char * lastComp;
	do {
		WaitForData();
	
		for (int i = pReadBufPos; i <= readBufPos; i++)
		{  // check all the newly received characters
			
			if (i >= seqLength) // only compare if the buffer is as long as the sequence
			{
				lastComp = &readBuf[i-seqLength];
				if (strncmp(c,&readBuf[i-seqLength],seqLength)==0) // the sequence has been found in the buffer
				{
					return TRUE;
				}
			}
		}
		pReadBufPos = readBufPos;
		
	} while (timeGetTime() - startTime < timeOut && (!stopNow || !*stopNow));
	
	return FALSE;
}

BOOL CCommOperations::SetFinalStorageFrequency(int freqSel, int wChamber)
{

/*
Frequency:			20 min		1 hr
114: A_WRITE_1_HR	61			10
113: A_WRITE_20_MN	10			21
	These control when to write to FS.
	If this number is less than 20 (or less than 60) then FS will be written to
	every twenty minutes or hour.  Only one should be set at a time.
	*/
	if (!StartCommOperation(9))
	{
		EndCommOperation();
		return FALSE;
	}

	switch (freqSel)
	{
	case 0:  // every hour
		{
			if (SetInputLocation(A_WRITE_1_HR,  10, 103, TRUE) &&
				SetInputLocation(A_WRITE_20_MN,  21, 103, TRUE) &&
				SetInputLocation(A_READ_20_MN,  21, 103, TRUE) &&
				SetInputLocation(A_READ_1_HR,  2, 103, TRUE) &&
				SetInputLocation(A_WTR_INTVL,  5, 103, TRUE))
				EndCommOperation();
				return TRUE;
		} break;
	case 1:  // every twenty minutes
		{
			if (SetInputLocation(A_WRITE_20_MN,  10, 104, TRUE) &&
				SetInputLocation(A_WRITE_1_HR,  61, 104,TRUE) &&
				SetInputLocation(A_READ_20_MN,  2, 104,TRUE) &&
				SetInputLocation(A_READ_1_HR,  61, 104,TRUE) &&
				SetInputLocation(A_WTR_INTVL,  5, 104,TRUE))
				EndCommOperation();
				return TRUE;
		} break;
	}
	EndCommOperation();
	return FALSE;
}

BOOL CCommOperations::SetSMPTestFrequency(int freqSel, int wChamber)
{
	/*
	Frequency:			20 min		1 hr				
112: A_READ_1_HR	61			2
111: A_READ_20_MN	2			21
	These control when to take a SMP reading.
	If this number is less than 20 (or less than 60) then a reading will take 
	occur every twenty minutes or hour.  Only one should be set at a time.
	*/
	
	int locations[3] = {A_READ_20_MN, A_READ_1_HR, A_WTR_INTVL};
	double newValues[3];
	switch (freqSel)
	{
	case 0:  // every hour
		{
			//if (SetLocationAndVerify(A_READ_20_MN, oldValue, 21) &&
			//	SetLocationAndVerify(A_READ_1_HR, oldValue, 2) &&
			//	SetLocationAndVerify(A_WTR_INTVL, oldValue, 5))
			//	return TRUE;
			newValues[0] = 21;
			newValues[1] = 2;
			newValues[2] = 5;
		} break;
	case 1:  // every twenty minutes
		{
			//if (SetLocationAndVerify(A_READ_20_MN, oldValue, 2) &&
			//	SetLocationAndVerify(A_READ_1_HR, oldValue, 61) &&
			//	SetLocationAndVerify(A_WTR_INTVL, oldValue, 5))
			//	return TRUE;
			newValues[0] = 2;
			newValues[1] = 61;
			newValues[2] = 5;
		} break;
	}

	
	for (int wLocation = 0; wLocation < 3; wLocation++)
	{
		for (int wTry= 0; wTry < 3; wTry++)
		{	
			if (SetInputLocation(locations[wLocation],newValues[wLocation],140))
				break;
		}
		if (wTry==3)
			return FALSE;
	}

	return TRUE;
}



BOOL CCommOperations::DetectPassword()
{
	if (PingCR10(50)||PingCR10(200)||PingCR10(500)||PingCR10(500))
	{
		for (int i = 0; i < 4; i++)
		{
			readBufPos = 0;
			Send("C\r",2);
			char wChar = WaitOnChar("*",2000,NULL);
			if (readBufPos > 7)
				return FALSE;
		}
		return TRUE; // is a password
	}
	else
	{
		NotificationBox("Unable to detect if password is enabled.  No response from CR10");
	}
	return FALSE;
}

BOOL CCommOperations::UnlockPassword()
{

	char rChar;
	readBufPos = 0;
	Send("7H\r",3);
	rChar = WaitOnChar(">",5000,NULL);
	WaitForData(20);
	if (rChar != '>')
	{
		MessageBox("Step 1 failed.");
		return FALSE;
	}
	Send("*C",2);
	rChar = WaitOnChar(":",3000,NULL);
	WaitForData(20);
	if (rChar != ':')
	{
		MessageBox("Step 2 failed.");
		return FALSE;
	}
	Send("0\r",2);
	rChar = WaitOnChar("1",3000,NULL);
	WaitForData(20);
	if (rChar != '1')
	{
		MessageBox("Step 3 failed.");
		return FALSE;
	}
	Send("*0",2);
	rChar = WaitOnChar("0",12000,NULL);
	if (rChar != '0')
	{
		MessageBox("Step 4 failed.");
		return FALSE;
	}
	return TRUE;
	
}


BOOL CCommOperations::SetControlMode(ControlModeType mode)
{
	BOOL CR10State;
	BOOL FlagState = (mode == AutomaticControlMode ? TRUE : FALSE);
	for (int i = 0; i < 3; i++)
	{
		SetFlag(3,FlagState);
		if (GetFlag(3,CR10State) && CR10State == FlagState)
		{
			
			return TRUE;
		}
	}
	
	return FALSE;
}

BOOL CCommOperations::DetermineCR10ProgramType(ControlStateType &cState)
{
	double oldValue;
	cState = NoControlState;
	int nChambers = 1;
	//, StartWetup, WetupInProgress, NoControlState};
	for (int i = 0; i < 7; i++)
	{
		int location = IL_PROGRAM_TYPE;
		if(pDoc->GetInputLocations(&location, 1, &oldValue,4))
		{
			//if (round(oldValue) == -99999)
			//{
			//	Sleep(50);
			//	continue;
			//}
			if (nChambers == 1 && round(oldValue) >= 10000 && round(oldValue) < 20000)
			{
				// 1 chamber regular
				cState = Regular;
			}
			else if (nChambers == 2 && round(oldValue) >= 20000 && round(oldValue) < 30000)
			{
				// 2 chamber regular
				cState = Regular;
			}
			else if (round(oldValue) >= 30000 && round(oldValue) < 50000)
			{
				// wetup
				cState = StartWetup;
			}
			else if (i < 6)
			{
				Sleep(50);
				continue;
			}

			return TRUE;
		}
	}
	return FALSE;
}

BOOL CCommOperations::LoadCalibrationFile(CString fName)
{
	int location=0;
	double newvalue=0;
	double old=0;
	BOOL ret=TRUE;
	char comments[80];
	ifstream fin(fName.GetBuffer(0));
	while (fin >> location >> newvalue)
	{
		//double old;
		//ret=SetLocationAndVerify(location,old,newvalue) && ret;
		ret=(SetInputLocation(location,newvalue,105, TRUE) && ret);
		fin.getline(comments,80);
	}
	fin.close();
	return ret;

}




BOOL CCommOperations::WaitForData(DWORD time)
{
	DWORD waitResult = WaitForSingleObject( DataReceived, time );
	ResetEvent( DataReceived ); // sets event to non-signaled state.
	if (waitResult == WAIT_TIMEOUT)
		return FALSE;
	return TRUE;
}




BOOL CCommOperations::SetInputLocation(int wLocation, double newValue, int wCall, BOOL verify, BOOL useDocIndex)
{
	static int nping15 = 0;
	static int nping50 = 0;
	static int nping200 = 0;
	static int nping1000 = 0;
	static int ntimes = 0;
	static int nping = 0;

	
	int failCode = 0;

	bool ping = false;
	//double checkSum;
	int mySum = 0;
	int nRetries = 20;
	int LocationToUse = wLocation;
	
	if (useDocIndex)
		LocationToUse = pDoc->InputLocationList[wLocation];
	
	for (int t = 0; t < nRetries; t++)
	{
		if (t == 19)
		{
			int a = 0;
		}
		if (nRetries == 3 || nRetries == 6 || nRetries == 9)
			Sleep(30);
		if (nRetries == 13 || nRetries == 16 || nRetries == 19)
			Sleep(50);

		if (!StartCommOperation(10))
		{
			EndCommOperation();
			return FALSE;
		}

		failCode = 0;
		ntimes++;
		if (PingCR10(15))
		{
			nping15++;
			ping = true;
		}
		else if (PingCR10(50))
		{
			nping50++;
			ping = true;
		}
		else if (PingCR10(70))
		{
			nping200++;
			ping = true;
		}
		else if (PingCR10(100))
		{
			nping1000++;
			ping = true;
		}
		else if (PingCR10(100))
		{
			nping1000++;
			ping = true;
		}
		
		if (ping)
		{
			nping++;

			char SendBuff[50];
			int sum = 0;
			wsprintf(SendBuff,"%i:%s:", LocationToUse, ValueToString(newValue,2));
			int i = 0;
			while (SendBuff[i])
				sum += SendBuff[i++];
			wsprintf(SendBuff,"%s%iU\r",SendBuff,sum);
			
			static unsigned int MaxLength = 0;
			if (strlen(SendBuff) > MaxLength)
				MaxLength = strlen(SendBuff);

			readBufPos = 0;
			Send(SendBuff, strlen(SendBuff));
			
			if (WaitOnChar("*",50,NULL))
			{
				//for (int i = 0; readBuf[i] != 'C' && readBuf[i] != '\0'; i++)
				//{
				//	if (readBuf[i] == '*')
				//		mySum = 0;
				//	else
				//		mySum += readBuf[i];
				//}
				//
				//if (readBuf[i] != 'C')
				//{
				//	
				//	
				//	int pReadBufPos = readBufPos;
				//	Sleep(20);
				//	if (pReadBufPos != readBufPos)
				//	{
				//		for (; readBuf[i] != 'C' && readBuf[i] != '\0'; i++)
				//		{
				//			if (readBuf[i] == '*')
				//				mySum = 0;
				//			else
				//				mySum += readBuf[i];
				//		}
				//		if (readBuf[i] != 'C')
				//		{
				//			EndCommOperation();
				//			Sleep(20);
				//			continue;
				//
				//		}
				//	}
				//}
				//mySum += 'C';

				//checkSum = StringToValue(&readBuf[i]);
				EndCommOperation();

				//if (round(checkSum) == mySum)
				//{
				if (verify)
				{
					double returnData;
					
					if (pDoc->GetInputLocations(&wLocation,1,&returnData,wCall,useDocIndex))
					{
						pDoc->AssertValid();
						if (fabs(returnData - newValue) < 0.01)
							return TRUE;
						else
							failCode = 4;
					}
					else
						failCode = 5;
				}
				else
					return TRUE;
				//}
				//else // bad checksum
				//	failCode = 1;
				
			}
			else // no * returned
			{
				failCode = 2;
				EndCommOperation();
				Sleep(20);
			}
			
		} 
		else  // no ping echoed
		{
			failCode = 3;
			EndCommOperation();
		}
	}

	CString note;

	switch (failCode)
	{
		//	case 1: { note = "checkSum = "+ValueToString(checkSum) + " mySum = " + IntToString(mySum); break; }
		case 2: { note = "no '*' returned within specified time interval"; break; }
		case 3: { note = "no ping echoed"; break; }
		case 4: { note = "GetInputLocations failed to return matching value"; break; }
		case 5: { note = "GetInputLocations returned FALSE"; break; }
		default: { note = "unknown cause"; break; }
	}
	char message[200];
	wsprintf(message,"SetInputLocation(wLocation = %i, wCall = %i), failcode = %i, %s", wLocation, wCall, failCode, note);
	pDoc->m_ErrorFiles->WriteHistory("Comm. Error",message);
	pDoc->m_ErrorFiles->WriteHistory(CString("  "),CString("number of retries = ") + IntToString(nRetries));
	return FALSE;

}


BOOL CCommOperations::StartCommOperation(int wFunctionIsCalling)
{
	static int prevCall;
	// waits until the object is in the signaled state.
	// it is signaled when comm is clear
	if ( HasCommBeenClosed )
		return FALSE;

	if (!pDoc->InCommMode)
	{
		char Message[80];
		wsprintf(Message,"ThreadsInCommBlock = %i, PrevCall = %i, CurrentCall = %i",pDoc->ThreadsInCommBlock, prevCall, wFunctionIsCalling);
		//MessageBox(Message,"Error",MB_ICONWARNING);
		pDoc->m_ErrorFiles->WriteHistory("StartCommOperation called while InCommMode == FALSE", Message);
		prevCall = wFunctionIsCalling;
		
		return FALSE;
	}

	DWORD waitPeriod = 1000 * 5;//60 * 3; // 3 minutes // INFINITE
	
	DWORD waitResult = WaitForSingleObject(  CommSyncObject, waitPeriod );
	ResetEvent( CommSyncObject ); // sets event to non-signaled state.
	
	// when it is set to signaled that means it is available
	if (waitResult == WAIT_TIMEOUT)
	{
		// we had to wait 3 minutes and the communication ready signal was never set
		// do some error handling routine.
		// reset comm. with CR10?
		char Message[80];
		wsprintf(Message,"ThreadsInCommBlock = %i, PrevCall = %i, CurrentCall = %i",pDoc->ThreadsInCommBlock, prevCall, wFunctionIsCalling);
		//MessageBox(Message,"Error",MB_ICONWARNING);
		pDoc->m_ErrorFiles->WriteHistory(Strings.get(IDS_E_COMMUNICATIONS_TIMEOUT), CString(Message));
		prevCall = wFunctionIsCalling;
		
		return FALSE;
		
	}
	prevCall = wFunctionIsCalling;
	pDoc->ThreadsInCommBlock++;
	return TRUE;
}

void CCommOperations::EndCommOperation()
{
	pDoc->ThreadsInCommBlock--;
	SetEvent( CommSyncObject ); // sets event to signaled state.
}


 