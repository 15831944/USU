// this program will simply connect with the CR10,
// monitor its data locations and user flags.
//  started May 8, 2000

#include <afxwin.h>
#include <afx.h>
#include "CR10 Talk Main.h"
#include "resource.h"
#include <math.h>

#include "MonitorDlg.h"
#include "FlagsDialog.h"
#include "ProgressDialog.h"
#include "RenameLocation.h"
#include "EditEvent.h"

//************************************************************
// GLOBAL DATA

//	  TO BE RETAINED IN A FILE
 int   InputLocScreenList[MAX_DISPLAY_INPUT_LOCATIONS];
 int   InputLocSaveList[MAX_INPUT_LOCATIONS];
 BOOL  UpdateItems[N_UPDATEABLE_ITEMS];
 int   FreqLevel[N_UPDATEABLE_ITEMS];
 int   InputLocScreenRequests;
 int   InputLocSaveRequests;
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
 int   nPEvents;

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
 const char *Frequencies[16] = {
	"1 Second","2 Seconds","5 Seconds","10 Seconds",
	"30 Seconds","1 Minute","2 Minutes","5 Minutes",
	"10 Minutes","30 Minutes","1 Hour","3 Hours",
	"6 Hours","1 Day","3 Days","1 Week"};
 int FlagWindowCount = 0;
 char  inputWindowText[15][10] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 double InputLocValue[MAX_INPUT_LOCATIONS];
 BOOL  NeedSetJCommand = TRUE;
 int   ProgramRunTime;
 int   ProgramCounter;
 char  workingDirectory[100];


// stuff used for debug info
 int   readNum = 0;
 DWORD timer[8];
 int   writeSize = 0;
 int   WCBuffRepeats = 0;   // WCBUFF_REPEATS
 int   writesTotal = 0;		// WRITE_OPS
 DWORD longestDelay = 0;  // LONGEST_DELAY
 int   timeOuts = 0;		//TIME_OUTS
 DWORD lastReadTime;
 COMSTAT ComStat;


CMainWindow::CMainWindow(char *lpszResourceName)
: CDialog(lpszResourceName), CommFunctions(),
ProgramEvents(nPEvents)
{
	AutoUpdate = FALSE;
	FSFileOut = NULL;
	ILFileOut = NULL;
	m_CFlagsDialog = NULL;
	WhereFocus = NULL;
	EditBoxUnderEdit = 0;

	if (MessageBox("Connect to CR10 now?","CR10 Talk", MB_YESNO | MB_ICONQUESTION ) == IDYES )
		Connect();

	programStartTime = timeGetTime();
	ProgramRunTime = 0;

}

BOOL CMainWindow::Connect(){
	// Open a connection and ping until you find which comport works
	
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
		} while (MessageBox(errMessage,"Communication Error",MB_YESNO | MB_ICONQUESTION ) == IDYES);
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
	MessageBox("Unable to communicate with CR10","Communication Error", MB_ICONEXCLAMATION );
	PORT( TalkInfo ) = defaultPort;
	return FALSE;
}

BOOL CMainWindow::OnInitDialog()
{   
	CDialog::OnInitDialog();      // TODO: Add extra initialization here
	if ( CONNECTED(TalkInfo) ){
		SetButtonState(Connected);
		UpdateAll();
	}
	else {
		SetButtonState(NotConnected);
	}
	SetInputLocationsNamesText();

	SetWindowNumber(IDC_DLASTDSP, LastDSP);

	EnableToolTips(TRUE);

	//myToolTip = new CToolTipCtrl;
	//myToolTip->Create(this);
	//CRect rect;
	//for (int i = 0; i < MAX_DISPLAY_INPUT_LOCATIONS; i++){
	//int i = 0;
	//GetDlgItem(IDC_LOC_1 + i)->GetWindowRect(rect);
	//BOOL AddSuccess = myToolTip->AddTool(this, "tOOL Tip"/*LPSTR_TEXTCALLBACK*/, &rect, IDC_LOC_1 + i);
	//}
	//myToolTip.SetToolInfo(...);
	//myToolTip->Activate(TRUE);
	//CString text;
	//myToolTip->GetText( text, this, IDC_LOC_1 );

	return TRUE;   // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE}
}

void CMainWindow::SetInputLocationsNamesText(){
	for (int i = 0; i < MAX_DISPLAY_INPUT_LOCATIONS; i++){
		if (i < InputLocScreenRequests){
			GetDlgItem(IDC_LOC_1 + i)->SetWindowText(AvailableInputLocations[InputLocScreenList[i]-1]);
			GetDlgItem(IDC_LOC_1 + i)->EnableWindow(TRUE);
			GetDlgItem(IDC_LOCATION1 + i)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_LOCATION1 + i)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_LOC_1 + i)->SetWindowText("");
			GetDlgItem(IDC_LOC_1 + i)->EnableWindow(FALSE);
			GetDlgItem(IDC_LOCATION1 + i)->ShowWindow(SW_HIDE);
			GetDlgItem(IDC_LOCATION1 + i)->EnableWindow(FALSE);
		}
	}

}

void CMainWindow::SetButtonState(ButtonState BState){
	CButton *pButton1, *pButton2, *pButton4, *pButton5, *pButton8;
	pButton1 = ( CButton * ) GetDlgItem( IDC_BUTTON1 );
	pButton2 = ( CButton * ) GetDlgItem( IDC_BUTTON2 );
	pButton4 = ( CButton * ) GetDlgItem( IDC_BUTTON4 );
	pButton5 = ( CButton * ) GetDlgItem( IDC_BUTTON5 );
	pButton8 = ( CButton * ) GetDlgItem( IDC_BUTTON8 );
	
	switch (BState){
	case NotConnected:
		pButton1->SetWindowText("Connect");
		pButton2->SetWindowText("Start");
		pButton2->EnableWindow(FALSE);
		pButton4->EnableWindow(FALSE);
		pButton5->EnableWindow(FALSE);
		pButton8->EnableWindow(FALSE);
		break;
	case Connected:
		pButton2->SetWindowText("Start");
		break;
	case Running:
		pButton2->SetWindowText("Stop");
		break;
	}

	if (BState == Connected || BState == Running){
		pButton1->SetWindowText("Disconnect");
		pButton2->EnableWindow(TRUE);
		pButton4->EnableWindow(TRUE);
		pButton5->EnableWindow(TRUE);
		pButton8->EnableWindow(TRUE);
	}
}



afx_msg void CMainWindow::OnButton1(){
// connect or update
	if (!CONNECTED(TalkInfo)) {
		// we are not connected yet: CONNECT
		if (!Connect())
			MessageBox( "Connection failed.", "CR10 Talk",MB_ICONEXCLAMATION );
		else {
			// change button text and update window
			SetButtonState(Connected);
		}
	}
	else  // we are already connected: DISCONNECT
	{	
		StopAutoUpdate();
		CloseConnection();
		SetButtonState(NotConnected);
	}	
}

afx_msg void CMainWindow::OnButton2(){
	// disconnect or cancel
	if (WhereFocus){
		GetDlgItem(IDC_BUTTON3)->SetFocus();
	}
	else
	{
		if (AutoUpdate) 
			// time to stop AutoUpdate
			StopAutoUpdate();
		else {
			// time to start AutoUpdate
			if (!SetTimer( 1, 1000, NULL ))
				MessageBox("Error setting timer","Program error",MB_ICONEXCLAMATION);
			else
			{
				AutoUpdate = TRUE;
				SetButtonState(Running);
			}
		}
	}
}

afx_msg void CMainWindow::OnButton3(){
	// close program
	SendMessage( WM_CLOSE );
}

void CMainWindow::StopAutoUpdate(){

	if (AutoUpdate) {
		// time to stop AutoUpdate
		AutoUpdate = FALSE;
		LastAutoUpdateTime = 0;
		KillTimer( 1 );
		SetButtonState(Connected);
	}
}

afx_msg void CMainWindow::OnButton4(){
	// toggle flags
	//show or hide some windows
	if (FlagWindowCount == 0){
		m_CFlagsDialog = new FlagsDialog;
		//m_CFlagsDialog->DoModal();
		m_CFlagsDialog->Create(FLAGS_DIALOG);
	}
}

afx_msg void CMainWindow::OnButton5(){
	// get final storage
	// if auto-update is in progress, then stop auto-update.
	RetrieveFinalStorage();
}

afx_msg void CMainWindow::OnButton6(){
	// move LastDSP
	CEdit *NewMPTRLocation = (CEdit *) GetDlgItem( IDC_EDIT_MPTR );
	char numBuf[6];
	NewMPTRLocation->GetWindowText(numBuf, 6);
	int LocationNumber = 0;

	for (int i = 0; numBuf[i] != '\0'; i++){
		if (numBuf[i] >= '0' && numBuf[i] <= '9'){
			LocationNumber *= 10;
			LocationNumber += numBuf[i] - '0';
		}
	}

	/*
	if (CONNECTED(TalkInfo)) {
		MoveMPTR(LocationNumber);
	}
	*/
	LastDSP = LocationNumber;
}

afx_msg void CMainWindow::OnButton7(){
//  Choose items to monitor dialog...
	CMonitorDlg mDialog(this);
	mDialog.DoModal();
	SetInputLocationsNamesText();
}

afx_msg void CMainWindow::OnButton8(){
	// download program to CR10
	int dsuccess = DownloadProgram();

	if (dsuccess == TRUE)
		MessageBox("Program successfully downloaded to CR10","CR 10 Talk");
	else if (dsuccess == FALSE)
		MessageBox("Error in downloading program to CR10","CR 10 Talk",MB_ICONEXCLAMATION);
}

afx_msg void CMainWindow::OnButton9(){
	// Event Settings...
	EditEvent eventDlg(&ProgramVariables, &ProgramEvents, this);
	eventDlg.DoModal();
}

afx_msg void CMainWindow::OnButton10(){
	// Event Settings...
	if (CONNECTED(TalkInfo))
		UpdateAll();
}

afx_msg void CMainWindow::OnClose() 
{
	// If it's still connected to the CR10, disconnect here.
	if (CONNECTED(TalkInfo)){
		if (SaveFinalStorage)
			RetrieveFinalStorage();
		CloseConnection();
	}
	CDialog::OnClose();
	if (FSFileOut)
		CloseHandle( FSFileOut );  
	WriteInitData();
	ProgramEvents(0);
	DisplayErrorMessage(GetLastError());
}

afx_msg void CMainWindow::OnTimer(unsigned int number)
{
	static int OnTimerCount = 0;
	
	OnTimerCount++;

	if (OnTimerCount == 1){
		
		ProgramRunTime = (timeGetTime() - programStartTime) / 1000;
		SetWindowNumber(IDC_RUNTIME_COUNTER, ProgramRunTime - ProgramCounter);
		if (ProgramRunTime - ProgramCounter > 5)
			ProgramCounter = ProgramRunTime - 1;
		
		BOOL gotInputLocations = FALSE;

		SetTimeBox(1);
		for (;ProgramCounter < ProgramRunTime; ProgramCounter++){
			
			if (UpdateItems[SAVE_LOCATIONS] && (ProgramCounter % FreqTable[FreqLevel[SAVE_LOCATIONS]] == 0)){
				gotInputLocations = TRUE;
				for (int LocPos = 0; LocPos - InputLocSaveRequests > 0; LocPos += 62){
					int LocsToGet = min(62,InputLocSaveRequests - LocPos);
					SetJCommand(FALSE, FALSE, TRUE, &InputLocSaveList[LocPos], LocsToGet);
					ExecuteKCommand(TRUE);
					ProcessInputLocations(&InputLocSaveList[LocPos], LocsToGet);
				}
				//write Inputlocvalues to file
				WriteInputLocations();
			}
			
			BOOL DoInputLocations = UpdateItems[INPUT_LOCATIONS] && 
				(ProgramCounter % FreqTable[FreqLevel[INPUT_LOCATIONS]] == 0) &&
				!gotInputLocations;
		
			SetJCommand(DoToggleFlags[USERFLAGS],
				DoToggleFlags[PORTFLAGS], DoInputLocations,
				InputLocScreenList, InputLocScreenRequests);
			SetTimeBox(2);
			ExecuteKCommand(DoInputLocations);
			SetTimeBox(3);
			if (ProgramCounter == ProgramRunTime - 1){
				if (!UpdateInfo(DoToggleFlags[USERFLAGS],
				DoToggleFlags[PORTFLAGS], DoInputLocations,
				UpdateItems[CR10_INFO] && (ProgramCounter % FreqTable[FreqLevel[CR10_INFO]] == 0),
				InputLocScreenList, InputLocScreenRequests))
				{
					SetTimeBox(4);
					MessageBox( "Error updating info (5)","Error",MB_ICONEXCLAMATION );
					StopAutoUpdate();
				}	
				else {
					SetTimeBox(4);
					SetInputLocationWindowsText();
					if (SaveFinalStorage){
						RetrieveFinalStorage();	
						WriteInitData();
					}
				}
				SetTimeBox(5);
			}
		}// end for loop
	}// end if OnTimerCount == 1
	OnTimerCount--;
}

void CMainWindow::WriteInputLocations(){
	
	CTime theTime = CTime::GetCurrentTime();
	CString s = theTime.Format( "%H;%M;%S, %B %d, %Y" );

	if (ILFileOut == NULL){
		char fileNameBuff[50];
		
		CString path = "C:\\";
		wsprintf(fileNameBuff,"%sInput Loc Data %s.dat", path, s);

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
	char FileOutText[10];
	char FileOutBuff[3000];
	int FileBuffPos = 0;
	DWORD bytesWritten;
	for (int i = 0; i < InputLocSaveRequests; i++){
		result = InputLocValue[InputLocSaveList[i] - 1];
		d1 = int(result);
		d2 = int((result - double(d1)) * 10000.0);
		wsprintf(FileOutText,"%i.%04i,",d1,d2);
		strcpy(&FileOutBuff[FileBuffPos], FileOutText);
		FileBuffPos += strlen(FileOutText);
	}
	
	FileOutBuff[FileBuffPos++] = '\n';
	if (!WriteFile(ILFileOut, FileOutBuff, FileBuffPos, &bytesWritten, NULL))
		DisplayErrorMessage(GetLastError());

}

void CMainWindow::UpdateAll(){
	
	SetJCommand(DoToggleFlags[USERFLAGS],
		DoToggleFlags[PORTFLAGS], UpdateItems[INPUT_LOCATIONS],
		InputLocScreenList, InputLocScreenRequests);
	ExecuteKCommand(TRUE);
	if (!UpdateInfo(DoToggleFlags[USERFLAGS],
		DoToggleFlags[PORTFLAGS],
		UpdateItems[INPUT_LOCATIONS],
		UpdateItems[CR10_INFO],
		InputLocScreenList, InputLocScreenRequests))
		MessageBox("Error updating info","Error",MB_ICONEXCLAMATION);
	else
		SetInputLocationWindowsText();
}

void CMainWindow::OnGainFocus(UINT nID){

	WhereFocus = (CEdit *) GetDlgItem(nID);
	EditBoxUnderEdit = nID - IDC_LOCATION1 + 1;
	WhereFocus->SetReadOnly(FALSE);
	WhereFocus->PostMessage(EM_SETSEL,	0, -1);
}

void CMainWindow::OnLoseFocus(UINT nID){
	
	if (WhereFocus->GetModify()){
		char TextBuff[20];
		WhereFocus->GetLine(0, TextBuff);
		ExecuteICommand(InputLocScreenList[EditBoxUnderEdit - 1], TextBuff);
	}
	WhereFocus->SetReadOnly(TRUE);
	WhereFocus->SetSel(-1,-1);
	WhereFocus = NULL;
	EditBoxUnderEdit = 0;
}

void CMainWindow::OnLocationDblClicked(UINT nID){
	int whichLocation = InputLocScreenList[nID - IDC_LOC_1];
	CString OldName = AvailableInputLocations[whichLocation - 1].Mid(4);
	char newName[30];
	strcpy(newName, OldName);
	CRenameLocation cNewName(OldName, newName,
	"Input Location", "Rename Input Location Dialog", whichLocation, TRUE, this );
	
	//CRenameLocation cNewName(OldName, &AvailableInputLocations[whichLocation - 1][4],
	//	"Input Location", "Rename Input Location Dialog", whichLocation, TRUE, this );
	
	cNewName.DoModal();
	AvailableInputLocations[whichLocation - 1].Replace(OldName, newName);
	GetDlgItem(nID)->SetWindowText(AvailableInputLocations[whichLocation - 1]);
}

BOOL CMainWindow::ExecuteICommand(int whichLocation, char *newValue ){

	if (PingCR10(15)||PingCR10(50)||PingCR10(200)||PingCR10(1000)){
		char SendBuff[20];
		wsprintf(SendBuff,"%iI\r%s\r", whichLocation, newValue);
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
			if (readBufPos > SendLength + 18) break;
		} while (timeGetTime() - LastReadTime < 125);
		
		return TRUE;
	}
	return FALSE;

}

BOOL CMainWindow::RetrieveFinalStorage(BOOL GetLastFSL){
	
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
				"Stop", TRUE, this);
			GetFSProgress->Create(PROGRESS_DIALOG);
		}
				
		while ( LocsToRetrieve >= DOWNLOAD_SIZE && !downloadCancelled){
			SetTimeBox(1);
			
			BOOL GetFSSuccess = GetFinalStorage();

			MSG Msg;
		
			PeekMessage( &Msg,         // message information
				NULL,           // handle to window
				0,//WM_MOUSEFIRST,  // first message  
				0,//WM_MOUSELAST );  // last message
				PM_REMOVE /*| PM_NOYIELD*/); //wRemoveMsg
			DispatchMessage( &Msg );  // message information);
		
			SetTimeBox(6);

			if (downloadCancelled) 
				break;
			
			LocsToRetrieve = ((DSP < LastDSP) ? (DSP + FilledLocations) : DSP) - LastDSP;
			
			if (GetFSProgress){
				wsprintf(wText,"%i final storage locations left to retrieve.", LocsToRetrieve);
				GetFSProgress->SetInfo(100 - (100 * LocsToRetrieve / InitialToRetrieve), wText);
			}
			SetTimeBox(7);
			
		}
		if (!downloadCancelled && LocsToRetrieve && GetLastFSL)
			GetFinalStorage(LocsToRetrieve);

		GetFSUnderWay = FALSE;
		if (GetFSProgress){
			GetFSProgress->Close();
			this->EnableWindow(TRUE);
			delete GetFSProgress;
			if (downloadCancelled){
				StopAutoUpdate();
				return FALSE;
			}
		}
	
		return TRUE;
	}
	return FALSE;
}

BOOL CMainWindow::Send(const LPSTR data, int bytesToSend)
{
	for (int t = 0; t < 5; t++){

		if (WriteCommBlock(data, bytesToSend)){
			UpdateGlobalDebugInfo();
			return TRUE;
		}
		WCBuffRepeats++;
		if (DO_RECONNECT){
			Reconnect();
			(PingCR10(20) || PingCR10(50) || PingCR10(500) || PingCR10(1000));
		}
	}
	UpdateGlobalDebugInfo();
	return FALSE;

}

void CMainWindow::UpdateGlobalDebugInfo(){
	
	SetWindowNumber( IDC_TIME_OUTS, timeOuts );
	SetWindowNumber( IDC_WRITE_RETRIES, WCBuffRepeats );

	SetWindowNumber( IDC_READ_BUF, readBufPos );
	SetWindowNumber( IDC_RUN_TIME, ( timeGetTime() - programStartTime ) / ( 60000 ));
	SetWindowNumber( IDC_LAST_READ_TIME, int(timeGetTime() - lastReadTime));
}

BOOL CMainWindow::PingCR10(DWORD miliseconds){
	
	char CR = ASCII_CR;
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
	//	MessageBox("PingCR10 didn't receive 3 characters","This could cause problems",MB_ICONEXCLAMATION);
	return FALSE;
}

void CMainWindow::SetInputLocationWindowsText(){
	CStatic *pLoc;
	int d1, d2;

	double result;

	for (int i = 0; i < InputLocScreenRequests; i++){
		if (i + 1 != EditBoxUnderEdit){
			result = InputLocValue[InputLocScreenList[i] - 1];
			d1 = int(result);
			d2 = int((result - double(d1)) * 10000.0);
			wsprintf(inputWindowText[i],"%i.%04i",d1,d2);
			pLoc = ( CStatic * ) GetDlgItem( IDC_LOCATION1 + i );
			pLoc->SetWindowText( inputWindowText[i] );
		}
	}
}

void CMainWindow::SetTimeWindowText( char *cTime ){
	CStatic *pTime;
	pTime = ( CStatic * ) GetDlgItem( IDC_TIME );
	pTime->SetWindowText( cTime );
}

void CMainWindow::SetTimeBox(int whichTime){
	timer[whichTime] = timeGetTime();
	
	if (whichTime == 7)
		SetWindowNumber(IDC_TIMER7, timer[7] - timer[1]);
	else if (whichTime > 1){
		CStatic *pText = (CStatic *) GetDlgItem(IDC_T_1 + whichTime - 1);
		CStatic *pLoc = (CStatic *) GetDlgItem(IDC_TIMER1 + whichTime - 1);
		char TextBuff[20];
		if (whichTime > 2){
			wsprintf(TextBuff,"Timer %i set...",whichTime);
			pText->SetWindowText(TextBuff);
			pLoc->SetWindowText("?");
			
		}
	
		pText = (CStatic *) GetDlgItem(IDC_T_1 + whichTime - 2);
		wsprintf(TextBuff,"Timer %i - Timer %i",whichTime, whichTime - 1);
		pText->SetWindowText(TextBuff);
		SetWindowNumber(IDC_TIMER1 + whichTime - 2, timer[whichTime] - timer[whichTime - 1]);
	}
	
}

void CMainWindow::SetUserFlagsWindowsText(){
	CStatic *pLoc;
	char windowText[2];

	for (int i = 0; i < 8; i++){
		pLoc = ( CStatic * ) GetDlgItem( IDC_U_FLAG1 + i );
		wsprintf(windowText,"%i", FlagStatus[i][USERFLAGS]);
		pLoc->SetWindowText( windowText );
	}
}

void CMainWindow::SetPortFlagsWindowsText(){
	CStatic *pLoc;
	char windowText[2];

	for (int i = 0; i < 8; i++){
		pLoc = ( CStatic * ) GetDlgItem( IDC_P_FLAG1 + i );
		wsprintf(windowText,"%i",FlagStatus[i][PORTFLAGS]);
		pLoc->SetWindowText( windowText );
	}
}

void CMainWindow::SetWindowNumber(int CONTROL_ID, int Number){
	CStatic *pLoc;
	char windowText[13];
	pLoc = ( CStatic * ) GetDlgItem( CONTROL_ID );
	wsprintf(windowText, "%i", Number);
	pLoc->SetWindowText( windowText );
}

BOOL CMainWindow::SetJCommand(BOOL DoUserFlags, BOOL DoPortFlags, 
	BOOL DoInputLocations, int InputLocList[], int InputLocRequests)
{
	static BOOL GFS = FALSE; // get final storage variable

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
	for (int t = 0; t < 5; t++){
		readBufPos = 0;
		Send(sendBuf, 9 + needPortByte + i);
		DWORD startTime = timeGetTime();
		do {
			Sleep (10);
			if (readBufPos == 11 + needPortByte + i){
				NeedSetJCommand = FALSE;
				return TRUE;
			}
		} while (timeGetTime() - startTime < 100);
		Sleep(100);
	}
	
}
return FALSE;

}

BOOL CMainWindow::ExecuteKCommand(BOOL GetInputLocations){
	
	if (!GetFSUnderWay && (PingCR10(20) || PingCR10(100) || PingCR10(500) || PingCR10(1000))){
	
		for (int t = 0; t < 5; t++){
			readBufPos = 0;
			Send("K\r",2);
			DWORD startTime = timeGetTime();
			do {
				Sleep (10);
				if (readBufPos == 12 + needPortByte + GetInputLocations * InputLocScreenRequests * 4 )
					break;
			} while (timeGetTime() - startTime < 100);
			if (readBufPos == 12 + needPortByte + GetInputLocations * InputLocScreenRequests * 4)
				return TRUE;
			Sleep(100);
		}
	}
	return FALSE;
}


BOOL CMainWindow::UpdateInfo(BOOL DoUserFlags, 
							 BOOL DoPortFlags, BOOL DoInputLocations, 
							 BOOL DoCR10Info, int InputLocList[], int InputLocRequests)
{
	// ping the CR10 several times.  If there is no response,
	// then return FALSE;
	static DWORD thisTime = 0;
	static DWORD lastTime = 0;


	//**********************************************************
	//***************|  CR10 TIME  |****************************

	
	char timeBuf[21];
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
	SetTimeWindowText(timeBuf);

	unsigned char mask = 1 << 7;
	//**********************************************************
	//***************|  USER FLAGS  |****************************
	if (DoUserFlags){
		unsigned char ufbyte = readBuf[7];
		for (int i = 0; i < 8; i++){
			FlagStatus[7 - i][USERFLAGS] = (mask & ufbyte) >> 7;
			ufbyte <<= 1;
		}
		SetUserFlagsWindowsText();
		if (FlagWindowCount && ModifyWhichFlags == USERFLAGS)
			m_CFlagsDialog->UpdateFlags();
	}
	//**********************************************************
	//***************|  PORT FLAGS  |****************************
	if (DoPortFlags && needPortByte){
		unsigned char pfbyte = readBuf[8];
		for (int i = 0; i < 8; i++){
			FlagStatus[7 - i][PORTFLAGS] = (mask & pfbyte) >> 7;
			pfbyte <<= 1;
		}
		SetPortFlagsWindowsText();
		if (FlagWindowCount && ModifyWhichFlags == PORTFLAGS)
			m_CFlagsDialog->UpdateFlags();
	}
	//**********************************************************
	//***************|  INPUT LOCATIONS  |****************************

	if (DoInputLocations){
		//process input locations	
		ProcessInputLocations(InputLocScreenList, InputLocScreenRequests);
		//SetInputLocationWindowsText(inputWindowText);
	}
	
	//**********************************************************
	//***************|  CR10 INFO  |****************************

	if (DoCR10Info)
		ExecuteACommand();

	UpdateGlobalDebugInfo();
		
	consecReconnects = 0;
	thisTime = timeGetTime();
	if (lastTime != 0){
		SetWindowNumber( IDC_LAST_DELAY, thisTime - lastTime );
		if (AutoUpdate && LastAutoUpdateTime && 
			thisTime - LastAutoUpdateTime > longestDelay){
			longestDelay = thisTime - LastAutoUpdateTime;
			SetWindowNumber( IDC_LONGEST_DELAY, longestDelay );
		}
	}
	lastTime = thisTime;
	LastAutoUpdateTime = (AutoUpdate ? thisTime : 0);
	
	return TRUE;
}

void CMainWindow::ProcessInputLocations(int InputLocList[], int InputLocRequests){
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
		
		InputLocValue[InputLocList[i] - 1] = result;
	}	
}

BOOL CMainWindow::Reconnect(BOOL reUpdate){
	SetWindowNumber( IDC_RECONNECTS, ++reconnects );	
	consecReconnects++;
	
	MessageBox("Reconnect called","Message");

	if (CONNECTED(TalkInfo)){
		CloseConnection();
		Sleep(200);
		SetButtonState(NotConnected);
	}

	if(OpenConnection()){
		SetButtonState(Connected);
		if (consecReconnects % 5 != 0){
			
			Sleep(100);
			//if (reUpdate)	
			//	return UpdateInfo();
	
			return TRUE;
		}
	}
	
	StopAutoUpdate();
	
	DisplayErrorMessage(GetLastError());

	return FALSE;
}

BOOL CMainWindow::CheckSignature
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
			SetWindowNumber( IDC_SIGNATURE, 1);
			return TRUE;
		}
	}
	SetWindowNumber( IDC_SIGNATURE, 0);
	return FALSE;
}

int CMainWindow::MoveMPTR(int whichLocation){

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
			UpdateGlobalDebugInfo();
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
	SetWindowNumber( IDC_MPTR_LOCATION, newLocation );
	return newLocation;
}

BOOL CMainWindow::GetFinalStorage(int LocsToRetrieve /*=DOWNLOAD_SIZE*/){
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
		char fileNameBuff[50];
		
		CString path = "C:\\";
		wsprintf(fileNameBuff,"%sFS Data %s.dat", path, s);

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

	SetWindowNumber (IDC_FS_POSITION, 0);
	
	wsprintf(SendBuf,"%iF\r",LocsToRetrieve);
	int ExpectedBytes = strlen(SendBuf) + LocsToRetrieve * 2 + 3;

	int writePos;
	int nextByteToProcess;
	int moveDSP;
	int bytesToWrite;
	int newLocs;
	int firstFSLocation = ExpectedBytes - LocsToRetrieve * 2 - 2;
	char *dataToWrite = new char[LocsToRetrieve * 10];

	SetTimeBox(2);

	for (int t = 0; t < FS_RETRIES; t++) {
		// move MPTR to LastDSP
		if (MoveMPTR(LastDSP) != LastDSP){
			SetWindowNumber (IDC_FS_POSITION, 1);
			delete [] dataToWrite;
			return FALSE;
		}
		SetTimeBox(3);

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
			SetTimeBox(4);
		
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

	SetWindowNumber( IDC_LOCS_RETRIEVE, (ExpectedBytes - i - 2) / 2 );
	SetWindowNumber(IDC_DMPTR, MoveMPTR(0)); 
	SetWindowNumber(IDC_DLASTDSP, LastDSP);
	
	SetWindowNumber (IDC_FS_POSITION, 4);

	if (FSFileOut){
		if (FSLocationsWrittenThisFile > FS_LOCS_PER_FILE){
			FSLocationsWrittenThisFile = 0;
			// close the file; it's become too big
			CloseHandle( FSFileOut );  // handle to object);
			FSFileOut = NULL;
		}
	}
	delete [] dataToWrite;
	
	SetTimeBox(5);

	return TRUE;
}

void CMainWindow::PrepareDataToWrite(int unprocessedBytes, char *firstDataByte, int &nextByteToProcess, char *dataToWrite, int &writePos, int &bytesToWrite, int &MoveDSP, int &LocationsRetrieved){
	
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

void CMainWindow::AssociateFSLFile(CString filename){
	
	filename.Replace( ".dld", ".fsl" );
	CString smallFileName = filename;

	if (filename == ""){
		CFileDialog OpenFileDialogBox(TRUE, "fsl", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			"Final Storage Label Files (*.fsl)|*.fsl|All Files (*.*)|*.*||",
			this);
		 
		UINT success = OpenFileDialogBox.DoModal();
		this->UpdateWindow();

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
			if (MessageBox("No matching FSL file found.  Browse for FSL file to associate?",
				"File not found", MB_YESNO | MB_ICONQUESTION) 
				== IDYES)
			{
				AssociateFSLFile();
			}
		}
		else
			DisplayErrorMessage(LError);
		return;
	}

	// reset all input location names.
	char nameBuff[30];
	for (int i = 1; i <= MAX_INPUT_LOCATIONS; i++){
		wsprintf(nameBuff, "%3i: [no name]", i);
		AvailableInputLocations[i - 1] = nameBuff;
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

	for (i = 0; i < fileSize; i++){
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
					char nameBuff[31];
					wsprintf(nameBuff,"%3i: %s", whichLoc, newName);
					AvailableInputLocations[whichLoc - 1] = nameBuff;
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
	SetInputLocationsNamesText();
	
}


int CMainWindow::DownloadProgram(CString filename){
	//open the file
	// if no filename is provided, ask the user which file to download
	if (!CONNECTED( TalkInfo )){
		MessageBox ("No connection to CR10 present","Error",MB_ICONEXCLAMATION);
		return FALSE;
	}

	CString smallFileName = filename;

	if (filename == ""){
		
		CFileDialog OpenFileDialogBox(TRUE, "dld", NULL, 
			OFN_HIDEREADONLY | OFN_PATHMUSTEXIST ,
			"Data logger program (*.dld)|*.dld|All Files (*.*)|*.*||",
			this);
		 
		UINT success = OpenFileDialogBox.DoModal();
		this->UpdateWindow( );

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
		MessageBox("Error accessing file","Error",MB_ICONEXCLAMATION);
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
	if (!opFailed){
		if (MessageBox("Derive input location names from an FSL file?",
			"File not found", MB_YESNO | MB_ICONQUESTION) 
			== IDYES)
			AssociateFSLFile(smallFileName);
	}

	return !opFailed;

}

BOOL CMainWindow::EndCR10Comm(){
		
	DWORD dwErrorFlags;
	ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
	DWORD LASTError = GetLastError();
	
	if (LASTError != 0)
		DisplayErrorMessage(LASTError);
	if (dwErrorFlags > 0)
		OutputCEError(dwErrorFlags);
	WriteCommBlock("E\r",2);
	EscapeCommFunction( COMDEV( TalkInfo), CLRDTR );
	Sleep(3000);
	return TRUE;
}

BOOL CMainWindow::ExecuteACommand(int *data){

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

		UpdateGlobalDebugInfo();
		
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
		SetWindowNumber( IDC_DSP_LOCATION, data[DATA_STORAGE_POINTER] );
		SetWindowNumber( IDC_FS_LOCATIONS, data[FILLED_FS_LOCATIONS] );
		SetWindowNumber( IDC_LOGGER_VER, data[DATA_LOGGER_VERSION] );
		SetWindowNumber( IDC_MPTR_LOCATION, data[MPTR_LOCATION] );
		SetWindowNumber( IDC_NO_EO8S, data[ERROR_INFO_1] );
		SetWindowNumber( IDC_NO_OVERRUN, data[ERROR_INFO_2] );
		SetWindowNumber( IDC_NO_LOW_VOLT, data[ERROR_INFO_3] );
		SetWindowNumber( IDC_CR10_MEMORY, data[MEMORY_SIZE] );
		SetWindowNumber( IDC_BATT_VOLTAGE, data[BATTERY_VOLTAGE] );
	
		if (deleteData) 
			delete [] data;	
	}
	else
		return FALSE;

	return TRUE;
}

char CMainWindow::WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow){
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

BOOL CMainWindow::OnToolTipNotify(UINT id, NMHDR *pTTTStruct, LRESULT *pResult){
	
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pTTTStruct;
	UINT nID = pTTTStruct->idFrom;

	if (pTTT->uFlags & TTF_IDISHWND)
		nID = ::GetDlgCtrlID((HWND) nID);
	
	if (nID >= IDC_LOC_1 && nID <= IDC_LOC_15){
		strcpy(pTTT->szText, AvailableInputLocations[InputLocScreenList[nID - IDC_LOC_1] - 1]);
	}
	//if (pTT->uFlags && 
	//strcpy(pTTT->szText,"This is a tool tip.");
	return TRUE;

}
/*
int CMainWindow::OnToolHitTest(CPoint point, TOOLINFO *pTI){

	return 1;
}
*/
BEGIN_MESSAGE_MAP( CMainWindow, CDialog )
	ON_COMMAND( IDC_BUTTON1, OnButton1 )
	ON_COMMAND( IDC_BUTTON2, OnButton2 )
	ON_COMMAND( IDC_BUTTON3, OnButton3 )
	ON_COMMAND( IDC_BUTTON4, OnButton4 )
	ON_COMMAND( IDC_BUTTON5, OnButton5 )
	ON_COMMAND( IDC_BUTTON6, OnButton6 )
	ON_COMMAND( IDC_BUTTON7, OnButton7 )
	ON_COMMAND( IDC_BUTTON8, OnButton8 )
	ON_COMMAND( IDC_BUTTON9, OnButton9 )
	ON_COMMAND( IDC_BUTTON10, OnButton10 )
	//ON_NOTIFY( NM_CLICK, IDC_EDIT_MPTR, OnMptrEnter )
	//ON_CONTROL_RANGE( BN_CLICKED, IDC_LOCATION1, IDC_LOCATION15, OnLocationClicked )
	//ON_CONTROL_RANGE( BN_KILLFOCUS, IDC_LOCATION1, IDC_LOCATION15, OnLocationClicked )
	//ON_COMMAND_RANGE( IDC_LOCATION1, IDC_LOCATION15, OnLocationClicked )
	//ON_CONTROL( BN_KILLFOCUS, IDC_TEMP_EDIT, OnTempEdit )
	//ON_NOTIFY( NM_KILLFOCUS, IDC_LOCATION1, OnMptrEnter )
	//ON_NOTIFY( NM_RETURN, IDC_LOCATION1, OnMptrEnter )
	//ON_NOTIFY( NM_CLICK, IDC_LOCATION1, OnMptrEnter )
	//ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	//ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_CONTROL_RANGE( EN_KILLFOCUS, IDC_LOCATION1, IDC_LOCATION15, OnLoseFocus )
	ON_CONTROL_RANGE( EN_SETFOCUS, IDC_LOCATION1, IDC_LOCATION15, OnGainFocus )
	ON_CONTROL_RANGE( BN_CLICKED, IDC_LOC_1, IDC_LOC_15, OnLocationDblClicked )
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,OnToolTipNotify) 
	//ON_NOTIFY_EX_RANGE(TTN_NEEDTEXT,0,0XFFFF, OnToolTipNotify)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	
END_MESSAGE_MAP()

class CCR10TalkApp : public CWinApp {
public:
	BOOL InitInstance()
	{
		afxMemDF |= checkAlwaysMemDF;
		HANDLE mHandle = CreateMutex(NULL,TRUE,"CR10TALK");
		if ( GetLastError() == ERROR_ALREADY_EXISTS ){
			MessageBox(NULL,"CR10 Talk is already running.\nOnly one instance of CR10 Talk\nmay run at a time.","Error",MB_ICONEXCLAMATION);
		}
		else {
			GetCurrentDirectory(100, workingDirectory);
			
			LoadInitData((MessageBox(NULL, "Load init data from file?","CR10 Talk",MB_YESNO | MB_ICONQUESTION ) == IDYES));
	
			CMainWindow CR10TalkDialog("CR10_TALK_DIALOG");
			CR10TalkDialog.DoModal();
			ReleaseMutex(mHandle);
		}

		return FALSE;
	}
	
} InstApplication;

