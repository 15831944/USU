// CommOperations.h: interface for the CCommOperations class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMOPERATIONS_H__467FACA2_6E4A_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_COMMOPERATIONS_H__467FACA2_6E4A_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommFunctions.h"
/*
#include "global defs.h"
#include "CR10 Comm Functions.h"
#include "FlagsDialog.h"
#include "Event.h"
#include "Array.h"
*/

#define DATA_STORAGE_POINTER	0
#define FILLED_FS_LOCATIONS		1
#define DATA_LOGGER_VERSION		2
#define MPTR_LOCATION			3
#define ERROR_INFO_1			4
#define ERROR_INFO_2			5
#define ERROR_INFO_3			6
#define MEMORY_SIZE				7
#define BATTERY_VOLTAGE			8
#define CHECK_SUM				9
#define WHICH_AREA				10
#define NO_DATA_ITEMS			11

//#define MAX_FS_DOWNLOAD			5000//29908
#define FS_RETRIES				3
#define DOWNLOAD_SIZE			100
#define FS_LOCS_PER_FILE		10000
#define DO_RECONNECT			1
#define TRANSMIT_SIZE			250

// PROGRAM CONSTANTS
#define MAX_DISPLAY_INPUT_LOCATIONS	15
#define MAX_INPUT_LOCATIONS		256

// UPDATEABLE ITEMS
#define INPUT_LOCATIONS			0
#define CR10_INFO				1
#define SAVE_LOCATIONS			2
#define N_UPDATEABLE_ITEMS		3

#define USERFLAGS				0
#define PORTFLAGS				1
#define CONTINUAL				0xFFFFFFFF
#define JUSTONCE				1
#define NEVER					0

enum SigType { KCOMMAND, FINALSTORAGE, DOWNLOADPROGRAM };

extern char * readBuf;
extern int readBufPos;
extern char workingDirectory[_MAX_PATH];

class CCommOperations : public CCommFunctions
{
public:
	CCommOperations( BOOL ShowMessage = TRUE );
	virtual ~CCommOperations();
	BOOL ChangeCR10Time(int hours, int minutes, int seconds, int day = 0, int year = 0);
	BOOL CheckSignature(int checkPos = 3, SigType = KCOMMAND,
		char *buffer = readBuf, int bytesToCheck = readBufPos - 2,
		unsigned char sigByte1 = (unsigned char)readBuf[readBufPos - 2], 
		unsigned char sigByte2 = (unsigned char)readBuf[readBufPos - 1]);
	BOOL Connect(BOOL ShowMessage = TRUE);
	int  DownloadProgram(CString filename = "");
	BOOL EndCR10Comm();
	BOOL ExecuteACommand(int *data = NULL);
	BOOL ExecuteICommand(int whichLocation, double &oldValue, char *newValue );
	BOOL ExecuteKCommand(BOOL GetInputLocations, int InputLocRequests);
	const char * GetCR10Time();
	BOOL GetFinalStorage(int LocsToRetrieve = DOWNLOAD_SIZE);
	BOOL IsConnected();
	int  MoveMPTR(int whichLocation);
	BOOL PingCR10(DWORD miliseconds);
	void PrepareDataToWrite(int unprocessedBytes, 
		char *firstDataByte, int &nextByteToProcess, 
		char *dataToWrite, int &writePos, int &bytesToWrite, 
		int &moveDSP, int &newLocs);
	void ProcessInputLocations(double InputLocValue[], int InputLocRequests);
	BOOL Reconnect(BOOL reUpdate = FALSE);
	BOOL RetrieveFinalStorage(BOOL GetLastFSL = FALSE);
	BOOL Send(const LPSTR data, int bytesToSend);
	BOOL SetJCommand(BOOL DoUserFlags, BOOL DoPortFlags, 
		BOOL DoInputLocations, int InputLocList[],
		int InputLocRequests);
	BOOL UpdateInfo(BOOL DoUserFlags, 
					BOOL DoPortFlags, BOOL DoInputLocations, 
					BOOL DoCR10Info, int InputLocList[], int InputLocRequests);
	char WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow);
	
	void WriteInputLocations(double InputLocValue[], int InputLocRequests);

protected:
	BOOL needPortByte;
	char timeBuf[21];
	CString DataDirectory;
	int *InputLocSaveList;
	int *InputLocSaveRequests;

	HANDLE FSFileOut;
	//void LoadInitData(BOOL LoadFromFile);
	//void WriteInitData();
	//BOOL OnToolTipNotify(UINT id, NMHDR *pTTTStruct, LRESULT *pResult);
	//afx_msg void OnButton1(); // connect or update
	//afx_msg void OnButton2(); // disconnect or cancel
	//afx_msg void OnButton3(); // start or stop auto-update
	//afx_msg void OnButton4(); // toggle flags
	//afx_msg void OnButton5(); // get final storage
	//afx_msg void OnButton6(); // move MPTR
	//afx_msg void OnButton7(); // start monitor dialog box
	//afx_msg void OnButton8(); // download program to CR10
	//afx_msg void OnButton9(); // start events dialog
	//afx_msg void OnButton10(); // monitor input locations
	//afx_msg void OnClose(); // close program
	//afx_msg void OnTimer(unsigned int); // auto-update
	//afx_msg void OnGainFocus(UINT nID);
	//afx_msg void OnLoseFocus(UINT nID);
	//afx_msg void OnLocationDblClicked(UINT nID);
	//void SetInputLocationWindowsText();
	//void SetTimeWindowText(char * time);
	//void SetUserFlagsWindowsText();
	//void SetPortFlagsWindowsText();
	//void SetWindowNumber(int CONTROL_ID, int Number);
	//void UpdateGlobalDebugInfo();
	//void SetButtonState(ButtonState BState);
	//void SetTimeBox(int whichTime);
	//void SetInputLocationsNamesText();
	//virtual int OnToolHitTest(CPoint point, TOOLINFO *pTI);
	//BOOL AutoUpdate;
	//void StopAutoUpdate();
	//void UpdateAll();
	//Array<ExpressionItem *> ProgramVariables;
	//DECLARE_MESSAGE_MAP();
	//private:
	//CEdit *WhereFocus;
	//int EditBoxUnderEdit;
	//CToolTipCtrl *myToolTip;
	//Array<Event> ProgramEvents;
};




#endif // !defined(AFX_COMMOPERATIONS_H__467FACA2_6E4A_11D4_98D9_00A076801ACD__INCLUDED_)
