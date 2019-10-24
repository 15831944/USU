// This is Version 1.0 PLEASE DOCUMENT CHANGES
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

enum SigType { KCOMMAND, FINALSTORAGE, UPLOADPROGRAM };
enum CR10ControlType { On, Off, NoChange, Forward, Reverse };
enum ControlModeType {ManualControlMode, AutomaticControlMode, NoMode};

enum ControlStateType {Regular, SelectWetupSettings, StartWetup, WetupInProgress, NoControlState};

extern char * readBuf;
extern int readBufPos;
extern CString workingDirectory;

class CLADAControlModuleDoc;
class CLADAControlModuleView;
class CCommOperations : public CCommFunctions
{
	friend BOOL GetData(CLADAControlModuleDoc *pDoc, CCommOperations *commObject, CLADAControlModuleView *pView);
public:
	void StartCommOperation(int wFunctionIsCalling = 0);
	void EndCommOperation();
	BOOL SetInputLocation( int wLocation, double newValue, BOOL verify = FALSE, BOOL useDocIndex = FALSE);
	BOOL SetSMPTestFrequency(int freqSel, int wChamber);
	BOOL WaitForData(DWORD time = 10);
	BOOL LoadCalibrationFile(CString fName="");
	CCommOperations( CLADAControlModuleDoc * doc, BOOL ShowMessage = TRUE , BOOL WaitExtra = FALSE );
	CLADAControlModuleDoc * pDoc;
	BOOL DetermineCR10ProgramType(ControlStateType &cState);
	BOOL SetControlMode(ControlModeType mode);
	BOOL UnlockPassword();
	BOOL DetectPassword();
	BOOL SetLocationAndVerify(int wLocation, double &oldValue, const int newValue, int nRepetitions = 3);
	BOOL SetLocationAndVerify(int wLocation, double &oldValue, const double newValue, int nRepetitions = 3);
	BOOL SetLocationAndVerify(int wLocation, double &oldValue, char *newValue, int nRepetitions = 3);
	BOOL SetFinalStorageFrequency(int freqSel, int wChamber);
	
	int nFilledLocationsAtStartOfGetFinalStorage;
	BOOL SwitchMode(int mode = 0);
	BOOL UpdateCR10Time();
	bool ForceSetJCommand;
	BOOL ControlCR10( CR10ControlType Lights = NoChange, CR10ControlType Fans = NoChange,
		CR10ControlType Pump1 = NoChange, CR10ControlType Pump2 = NoChange, int chamber = 0);

	BOOL SetFlag(int wFlag, BOOL state, BOOL IsUser = TRUE);
	void ToggleFlag(int wFlag, BOOL IsUser = TRUE);
	BOOL GetFlag(int wFlag, BOOL IsUser = TRUE);

	BOOL IsRequestDifferent(BOOL DoLocations, int *InputLocList, int InputLocRequests);
	//int InputLocsRequested[256];

	virtual ~CCommOperations();
	BOOL ChangeCR10Time(int hours, int minutes, int seconds, int day = -1, int year = -1);
	BOOL Connect(BOOL ShowMessage = TRUE, BOOL WaitExtra = FALSE);
	int  UploadProgram(CString filename = "");
	BOOL EndCR10Comm();
	BOOL ExecuteACommand(int *data = NULL);
	BOOL ExecuteICommand(int whichLocation, double &oldValue, char *newValue, int nRetries );// = 1);
	BOOL ExecuteKCommand(BOOL GetInputLocations, int InputLocRequests);
	const char * GetCR10Time(CTime *returnTime = NULL);
	BOOL GetFinalStorage(int &value, HANDLE FSFilesOut[], CLADAControlModuleDoc * pDoc, int LocsToRetrieve = DOWNLOAD_SIZE);
	BOOL IsConnected();
	
	BOOL ProcessInputLocations(char * ptrBuf, double InputLocValue[], int InputList[], int InputLocRequests);
	const char * ProcessCR10Time(CLADAControlModuleDoc * pDoc = NULL);
	//BOOL Reconnect(BOOL reUpdate = FALSE);
	BOOL RetrieveFinalStorage(HANDLE FSFilesOut[], CLADAControlModuleDoc * pDoc, BOOL GetLastFSL = FALSE);
	BOOL Send(const LPSTR data, int bytesToSend);
	BOOL SetJCommand(BOOL DoUserFlags, BOOL DoPortFlags, 
		BOOL DoInputLocations, int *InputLocList = NULL,
		int InputLocRequests = 0);
	//BOOL UpdateInfo(BOOL DoUserFlags, 
	//				BOOL DoPortFlags, BOOL DoInputLocations, 
	//				BOOL DoCR10Info, int InputLocList[], int InputLocRequests);
	

	char timeBuf[21];

	BOOL CheckSignature(int checkPos = 3, SigType = KCOMMAND,
		char *buffer = readBuf, int bytesToCheck = readBufPos - 2,
		unsigned char sigByte1 = (unsigned char)readBuf[readBufPos - 2], 
		unsigned char sigByte2 = (unsigned char)readBuf[readBufPos - 1]);
private:
	int  MoveMPTR(int whichLocation);
	BOOL PingCR10(DWORD miliseconds, BOOL DoSwitchMode = FALSE);
	int  PrepareDataToWrite(int LocsToRetrieve, CLADAControlModuleDoc *pDoc, int unprocessedBytes, 
		char *firstDataByte, int &nextByteToProcess, 
		char *dataToWrite, int writePos[], int bytesToWrite[], 
		int &moveDSP, int &newLocs);
	char WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow, int startPos = 0);
	BOOL WaitOnSequence(const char *c, DWORD timeOut, BOOL *stopNow, int startPos = 0);

protected:
	BOOL needPortByte;

	int LastInputRequest[MAX_INPUT_LOCATIONS];
	int nLastRequest;
	
	HANDLE						CommSyncObject;

};




#endif // !defined(AFX_COMMOPERATIONS_H__467FACA2_6E4A_11D4_98D9_00A076801ACD__INCLUDED_)