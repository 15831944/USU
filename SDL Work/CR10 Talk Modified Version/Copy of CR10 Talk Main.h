#ifndef CR10_TALK_H
#define CR10_TALK_H

#include "global defs.h"
#include "CR10 Comm Functions.h"
#include "FlagsDialog.h"
#include "Event.h"
#include "Array.h"

class CommFunctions;

class CMainWindow : public CDialog , public CommFunctions  {
	friend class CMonitorDlg;
public:
	CMainWindow( char * lpszResourceName );
	BOOL OnInitDialog();
	BOOL OnToolTipNotify(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	afx_msg void OnButton1(); // connect or update
	afx_msg void OnButton2(); // disconnect or cancel
	afx_msg void OnButton3(); // start or stop auto-update
	afx_msg void OnButton4(); // toggle flags
	afx_msg void OnButton5(); // get final storage
	afx_msg void OnButton6(); // move MPTR
	afx_msg void OnButton7(); // start monitor dialog box
	afx_msg void OnButton8(); // download program to CR10
	afx_msg void OnButton9(); // start events dialog
	afx_msg void OnButton10(); // monitor input locations
	afx_msg void OnClose(); // close program
	afx_msg void OnTimer(unsigned int); // auto-update
	afx_msg void OnGainFocus(UINT nID);
	afx_msg void OnLoseFocus(UINT nID);
	afx_msg void OnLocationDblClicked(UINT nID);
	BOOL PingCR10(DWORD miliseconds);
	BOOL Send(const LPSTR data, int bytesToSend);
	BOOL CheckSignature(int checkPos = 3, SigType = KCOMMAND,
		char *buffer = readBuf, int bytesToCheck = readBufPos - 2,
		unsigned char sigByte1 = (unsigned char)readBuf[readBufPos - 2], 
		unsigned char sigByte2 = (unsigned char)readBuf[readBufPos - 1]);
	BOOL Reconnect(BOOL reUpdate = FALSE);
	void SetInputLocationWindowsText();
	void SetTimeWindowText(char * time);
	void SetUserFlagsWindowsText();
	void SetPortFlagsWindowsText();
	void SetWindowNumber(int CONTROL_ID, int Number);
	void UpdateGlobalDebugInfo();
	int  MoveMPTR(int whichLocation);
	BOOL SetJCommand(BOOL DoUserFlags, BOOL DoPortFlags, 
	BOOL DoInputLocations, int InputLocList[], int InputLocRequests);
	BOOL GetFinalStorage(int LocsToRetrieve = DOWNLOAD_SIZE);
	BOOL ExecuteACommand(int *data = NULL);
	BOOL ExecuteICommand(int whichLocation, char *newValue );
	void SetButtonState(ButtonState BState);
	BOOL EndCR10Comm();
	int  DownloadProgram(CString filename = "");
	void AssociateFSLFile(CString filename = "");
	BOOL RetrieveFinalStorage(BOOL GetLastFSL = FALSE);
	void SetTimeBox(int whichTime);
	void SetInputLocationsNamesText();
	BOOL ExecuteKCommand(BOOL GetInputLocations);
	BOOL Connect();
	//virtual int OnToolHitTest(CPoint point, TOOLINFO *pTI);
	
	#ifdef DBUG
		void ShowTimeDiff();
	#endif
	FlagsDialog *m_CFlagsDialog;	
protected:
	
	BOOL AutoUpdate;
	HANDLE FSFileOut;
	HANDLE ILFileOut;
	void StopAutoUpdate();
	BOOL UpdateInfo(BOOL DoUserFlags, 
					BOOL DoPortFlags, BOOL DoInputLocations, 
					BOOL DoCR10Info, int InputLocList[], int InputLocRequests);
	void ProcessInputLocations(int InputLocList[], int InputLocRequests);
	void UpdateAll();
	void WriteInputLocations();
	Array<ExpressionItem *> ProgramVariables;
	DECLARE_MESSAGE_MAP();
private:
	void PrepareDataToWrite(int unprocessedBytes, 
		char *firstDataByte, int &nextByteToProcess, 
		char *dataToWrite, int &writePos, int &bytesToWrite, 
		int &moveDSP, int &newLocs);
	char WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow);
	CEdit *WhereFocus;
	int EditBoxUnderEdit;
	CToolTipCtrl *myToolTip;
	BOOL needPortByte;
	Array<Event> ProgramEvents;
};

#endif