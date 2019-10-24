#ifndef GLOBAL_DEFS_H
#define GLOBAL_DEFS_H

#define USECOMM      // yes, we need the COMM API

#include <afx.h>
#include <windows.h>
#include <windef.h>
#include <winbase.h>

#include <commdlg.h>
#include <string.h>
#include <mmsystem.h>  // used for timeGetTime()
#include "resource.h"
/*
#include "CR10 Comm Functions.h"
#include "CR10 Talk Main.h"
#include "FlagsDialog.h"
#include "MonitorDlg.h"
#include "ProgressDlg.h"
#include "RenameLocation.h"
*/

#define MAXBLOCK        80 // THIS IS USED
#define BUF_SIZE		65537

// ascii definitions

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

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

enum SigType { KCOMMAND, FINALSTORAGE, DOWNLOADPROGRAM };
enum ButtonState {NotConnected, Connected, Running }; 

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

	
// global function prototypes
extern void LoadInitData(BOOL LoadFromFile = TRUE);
extern void WriteInitData();
extern void DisplayErrorMessage(DWORD ErrorNum);
extern void OutputCEError(DWORD error);
//template <class T> extern void SortDescending( T array[], int n );
extern void SortDescending( int array[], int n);
extern void SortAscending( int array[], int n);
//template <class T> extern T Min(const T &a, const T &b);
extern void iToString(int number, int exponent, char *s, bool isNeg = false);
extern char WaitOnChar(const char *c, DWORD timeOut, BOOL *stopNow);
extern DWORD FAR PASCAL CommWatchProc(void *lpdata);
extern void WriteToBuf(const BYTE *buf, int bytesToWrite);



//************************************************************
// GLOBAL DATA

//	  TO BE RETAINED IN A FILE
extern int   InputLocScreenList[MAX_DISPLAY_INPUT_LOCATIONS];
extern int   InputLocSaveList[MAX_INPUT_LOCATIONS];
extern BOOL  UpdateItems[N_UPDATEABLE_ITEMS];
extern int   FreqLevel[N_UPDATEABLE_ITEMS];
extern int   InputLocScreenRequests;
extern int   InputLocSaveRequests;
extern int   LastDSP;
extern BOOL  FStartRetrievalFromCurrentPosOnStart;
extern int   defaultPort;
extern CString  AvailableInputLocations[MAX_INPUT_LOCATIONS];
extern int   toggleFlags[8][2];
extern BOOL  DoToggleFlags[2];
extern int   ModifyWhichFlags;
extern CString  FlagNames[8][2];
extern int   toggleFlagsFreqLevel[8][2];
extern BOOL  SaveFinalStorage;

extern int   nPEvents;

//    USED ONLY DURING PROGRAM EXECUTION
extern char  *readBuf;
extern int   readBufPos;
extern BOOL  dataReceived;
extern int   reconnects;				// RECONNECTS
extern DWORD programStartTime;	

extern int   FreqTable[16];
extern int   FilledLocations;
extern int   DSP;
extern BOOL  FlagStatus[8][2];
extern int   consecReconnects;
extern BOOL  GetFSUnderWay;
extern DWORD LastAutoUpdateTime;
extern const char *Frequencies[16];
extern int   FlagWindowCount;
extern char  inputWindowText[15][10];
extern double InputLocValue[];
extern BOOL  NeedSetJCommand;
extern int   ProgramRunTime;
extern char workingDirectory[100];
extern int ProgramCounter;
		
// stuff used for debug info
extern int   readNum;
extern DWORD timer[8];
extern int   writeSize;
extern int   WCBuffRepeats;   // WCBUFF_REPEATS
extern int   writesTotal;		// WRITE_OPS
extern DWORD longestDelay;  // LONGEST_DELAY
extern int   timeOuts;		//TIME_OUTS
extern DWORD lastReadTime;
extern COMSTAT ComStat;

#endif







