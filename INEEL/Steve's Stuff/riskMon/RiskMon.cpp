// RiskMon.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "RiskMon.h"
#include "RiskFunctions.h"
#include "node.h"
#include <fstream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "ArrayListLL.h"
//#include <new.h>
//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CRiskMonApp

BEGIN_MESSAGE_MAP(CRiskMonApp, CWinApp)
	//{{AFX_MSG_MAP(CRiskMonApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CString ODBCName = "riskMon";
CString ProjectLoc = "E:\\RiskProjects\\Demo\\";
CString RUNNINGDIR = "E:\\StevesTest\\";
CString Debug = "E:\\StevesTest\\Error.txt";
DWORD dwThreadID;
int * threadActive;
int * ChangesMade;
int NewWorkspaceID =0;
int WorkspaceID= 0;
int CurModeID = -10;
int ThreadMode = -10;
BOOL PauseThread = FALSE;
BOOL IsPaused = FALSE;

BOOL Done;
int DoAllUpdatesNow = 0;
BOOL ChangesLeft = FALSE;
BOOL ProjectOpened = FALSE;  //Used so that no calls are made to a saphire project unless it has been oppened succesfully
BOOL CurrentlyCalculating = FALSE;  //used in CalcRiskFromCompList so that two copies of the function cannot be running at the same time
BOOL AccessDB = TRUE;
int curPercent=0;
int percentDone=0;//stores the percent done when doing doAllUpdates
BOOL SectionsFilled = FALSE;
HANDLE Notify;
HANDLE Pauseing;
HINSTANCE		hSageRiskDLL;               // to be Handle to SageRisk DLL
//hDLL = LoadLibrary("SageRisk.dll");
// to keep track of the update speed
DWORD totalTimeSpentUpdating;
int totalUpdatesDone;
CStringLList CritComps;  //a list of critical components calculated only at users request
CStringLList UsedCompList;  //a list of basic events to calculate the risk and get the critical components
BOOL CritCompsCalculated = FALSE;
ALNode *CurSys = NULL;  //a pointer to the last used system
ArrayListLL AllSystemsList; // stores the sections of the project containing all of the basic events


//typedef NAME24 *SYSTEMLIST;
//typedefs for the sagerisk dll
typedef void (CALLBACK* PROJECT_OPEN)(CString);
typedef void (CALLBACK* PROJECT_CLOSE)();
typedef int (CALLBACK* RISK_ERROR)();
typedef void (CALLBACK* RISK_ERROR_DESCRIPTION)(int, char[60]);
typedef int (CALLBACK* SYSTEM_COUNT_TOPS)();
typedef void (CALLBACK* SYSTEM_FIND_NAME_INDEXED)(int);
typedef void (CALLBACK* SYSTEM_GET_NAME)(char[25]);
//typedef void (CALLBACK* SYSTEM_FAULT_TREE_LOGIC	)(char[21], char[100]);
typedef int (CALLBACK* EVENT_COUNT)();
typedef void (CALLBACK* EVENT_FIND_NAME_INDEXED)(int);
typedef void (CALLBACK* EVENT_GET_NAME)(char[24]);
typedef int (CALLBACK* SYSTEM_GET_LOGIC_BE_CNT)();
//typedef void (CALLBACK* SYSTEM_GET_LOGIC_BE_NAMES)(int, long *);
typedef void (CALLBACK* SYSTEM_GET_LOGIC_BE_NAMES)(int, char (*)[25]);
typedef void (CALLBACK* SYSTEM_FIND_NAME)(char[24]);
typedef void (CALLBACK* PROJECT_UPGRADE)(char[60]);
typedef void (CALLBACK* SYSTEM_GET_DESCRIPTION)(char[61]);
typedef void (CALLBACK* EVENT_FIND_NAME)(char[25]);
typedef void (CALLBACK* EVENT_GET_DESCRIPTION)(char[61]);

DWORD PASCAL ProcessUpdates(void * lpData);
BOOL PASCAL LoadSystem(ArrayListLL &list, char sysName[25]);

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////Functions for export and use in riskmonitor program//////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
//missilaneous functions//
extern "C" BOOL PASCAL EXPORT StartWorkerThread(int &tActive, int &cMade, LPSTR odbcName, LPSTR runningDir, BOOL AdataBase);
//extern "C" BOOL PASCAL EXPORT StartWorkerThread(int &tActive, int &cMade, LPSTR odbcName, LPSTR projLoc, LPSTR runningDir);
extern "C" int PASCAL EXPORT GetAverageUpdateSpeed(int & tUpdatesDone);
extern "C" BOOL PASCAL EXPORT CloseWorkerThread();
extern "C" BOOL PASCAL EXPORT ChangesMadeFunc();
extern "C" BOOL PASCAL EXPORT SetWorkspace(int &WorkID );
extern "C" BOOL PASCAL EXPORT DoAllUpdates(int & percent);
extern "C" BOOL PASCAL EXPORT ContinueAllUpdates(int & percent);
extern "C" int PASCAL EXPORT IsProjectGood(LPSTR projLoc, LPSTR & rErrorDesc);
extern "C" void PASCAL EXPORT UpdateProject(LPSTR projLoc);
//Functions for geting the basic events of a system//
extern "C" BOOL PASCAL EXPORT GetSystemName(int index, LPSTR & name, LPSTR &sysDesc, int MappingID = 0);
extern "C" int PASCAL EXPORT SystemCount(int MappingID = 0);
extern "C" int PASCAL EXPORT GetNumOfBComps(LPSTR sysName);
extern "C" BOOL PASCAL EXPORT GetBCompName(int index, LPSTR & bCompName);
extern "C" BOOL PASCAL EXPORT GetBEName(LPSTR, int, LPSTR &, LPSTR &, int & BCompID);
extern "C" int PASCAL EXPORT GetNumOfBE(LPSTR);
//Functions for geting the critical components//
extern "C" BOOL PASCAL EXPORT LoadCritBE(LPSTR time);
extern "C" BOOL PASCAL EXPORT GetNextCritBE(LPSTR &retComp, double &riskIncrease);
//Functions for VScreen, getting the risk from a user definded components off line //
extern "C" BOOL PASCAL EXPORT AddSingleComp(int comp);
extern "C" BOOL PASCAL EXPORT ClearBEList();
extern "C" BOOL PASCAL EXPORT CalcRiskFromCompList(double &riskLev); 

PROJECT_OPEN				Project_Open;    // Function pointer
PROJECT_CLOSE				Project_Close;
RISK_ERROR					Risk_Error;
RISK_ERROR_DESCRIPTION		Risk_Error_Description;
SYSTEM_COUNT_TOPS			System_Count_Tops;
SYSTEM_GET_LOGIC_BE_CNT		System_Get_Logic_BE_Cnt;
SYSTEM_GET_LOGIC_BE_NAMES	System_Get_Logic_BE_Names;
SYSTEM_FIND_NAME			System_Find_Name;
SYSTEM_FIND_NAME_INDEXED	System_Find_Name_Indexed;
SYSTEM_GET_NAME				System_Get_Name;
PROJECT_UPGRADE				Project_Upgrade;
SYSTEM_GET_DESCRIPTION		System_Get_Description;
EVENT_FIND_NAME				Event_Find_Name;
EVENT_GET_DESCRIPTION		Event_Get_Description;
ofstream Error;

CString FormatErrorCode(DWORD Error)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		Error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	CString returnValue = CString((LPCTSTR)lpMsgBuf);
	// Free the buffer.
	LocalFree( lpMsgBuf );
	return returnValue;
}

FARPROC LoadSageDLLFunction(LPCSTR functionName)
{
	FARPROC procAddress;
	procAddress = GetProcAddress(hSageRiskDLL,functionName);
	if (procAddress == NULL)
	{
		Error << "Fatal Error:  Failed to get proc address of function " << functionName << " in SageRisk.dll" << endl;
		Error << "GetLastError returned: " << FormatErrorCode(GetLastError()) << endl;
		ProjectOpened = FALSE;
	}
	return procAddress;
}

//starts the main thread and initializes needed variables
extern "C" BOOL PASCAL EXPORT StartWorkerThread(int &tActive, int &cMade, LPSTR odbcName,LPSTR runningDir, BOOL AdataBase)
//extern "C" BOOL PASCAL EXPORT StartWorkerThread(int &tActive, int &cMade, LPSTR odbcName, LPSTR projLoc, LPSTR runningDir)
{
	
	MessageBox(NULL,"Starting Worker Tread", "ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING | MB_SYSTEMMODAL);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());	
	//char message[200];
	//wsprintf(message,"StartWorkerThread was called with parameters: tActive = %i, cMade = %i, odbcName = %s, projLoc = %s, runningDir = %s",tActive,cMade,projLoc,runningDir);
	//MessageBox(NULL, message,"Risk Update DLL",MB_OK);
	CString myString;
	myString.Format("StartWorkerThread was called with parameters: tActive = %i, cMade = %i, odbcName = %s, runningDir = %s",tActive,cMade,odbcName,runningDir);

	ODBCName = odbcName;
	//ProjectLoc = projLoc;
	RUNNINGDIR = runningDir;
	AccessDB = AdataBase;
	

	//Delete the old error log file if it exists
	CString errorLogFile;
	errorLogFile = RUNNINGDIR + "ErrorLog.dat";
	DeleteFile(errorLogFile);
	Error.open(errorLogFile.GetBuffer(0));

	//***************************************************************
	// open the DLLs for SAPHIRE support
	//*************************************************************** 
	//SageRisk DLL function call setup
	
	ProjectOpened = TRUE; //if something fails, we will set this to FALSE

	hSageRiskDLL = LoadLibrary("SAGERISK.dll");
	
	if (hSageRiskDLL == NULL)
	{
		Error<<"Failed to open SAGERISK.dll"<<endl;
		Error << "GetLastError returned: " << FormatErrorCode(GetLastError()) << endl;
		
		MessageBox(NULL, "hSageRiskDLL = NULL","ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING | MB_SYSTEMMODAL);
		ProjectOpened = FALSE;
	}
	else
	{
		Project_Open =				(PROJECT_OPEN)				LoadSageDLLFunction("Project_Open");
		Project_Close =				(PROJECT_CLOSE)				LoadSageDLLFunction("Project_Close");
		Risk_Error =				(RISK_ERROR)				LoadSageDLLFunction("Risk_Error");
		Risk_Error_Description =	(RISK_ERROR_DESCRIPTION)	LoadSageDLLFunction("Risk_Error_Description");
		System_Count_Tops =			(SYSTEM_COUNT_TOPS)			LoadSageDLLFunction("System_Count_Tops");
		System_Find_Name =			(SYSTEM_FIND_NAME)			LoadSageDLLFunction("System_Find_Name");
		System_Get_Logic_BE_Cnt =	(SYSTEM_GET_LOGIC_BE_CNT)	LoadSageDLLFunction("System_Get_Logic_BE_Cnt");
		System_Get_Logic_BE_Names = (SYSTEM_GET_LOGIC_BE_NAMES)	LoadSageDLLFunction("System_Get_Logic_BE_Names");
		System_Find_Name_Indexed =	(SYSTEM_FIND_NAME_INDEXED)	LoadSageDLLFunction("System_Find_Name_Indexed");
		System_Get_Name =			(SYSTEM_GET_NAME)			LoadSageDLLFunction("System_Get_Name");
		Project_Upgrade =			(PROJECT_UPGRADE)			LoadSageDLLFunction("Project_Upgrade");
		System_Get_Description =	(SYSTEM_GET_DESCRIPTION)	LoadSageDLLFunction("System_Get_Description");
		Event_Find_Name =			(EVENT_FIND_NAME)			LoadSageDLLFunction("Event_Find_Name");
		Event_Get_Description =		(EVENT_GET_DESCRIPTION)		LoadSageDLLFunction("Event_Get_Description");

	}
	
	if (ProjectOpened == FALSE)
	{
		// could not load the DLL or one of its functions correctly... must abort
		return FALSE;
	}
	/*
	//Open the project
	Project_Open(ProjectLoc);
	
	//Check to see if the Project was opened correctly
	int rError = Risk_Error(); 
	if (rError != 0)
	{
		char rErrorDesc[60];
		Risk_Error_Description(rError, rErrorDesc);
		//TestMessage("Yes");
		CString eMessage(rErrorDesc);
		MessageBox(NULL,eMessage,"ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING | MB_SYSTEMMODAL);
		ProjectOpened = 0;
		Error<<"Failed to open project"<<endl;
		ProjectOpened = FALSE;
		return FALSE;
	}
	else 
		ProjectOpened = TRUE;
	*/
	//******************************************************************
	//  Start thread to begin processing updates
	//******************************************************************

	threadActive = &tActive;
	ChangesMade = &cMade;
	
	
	Notify = CreateEvent(NULL, TRUE, FALSE, "NotifyRiskProject_s");
	Pauseing = CreateEvent(NULL, TRUE, FALSE, "PausingUpdates_s");
	
	if (CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
							0,
							ProcessUpdates,
							NULL,
							0, &dwThreadID ) != NULL )
	{
		return TRUE;
		
	}
	else
	{
		MessageBox(NULL,"Tread failed", "ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING | MB_SYSTEMMODAL);
		Error<<"Failed to start thread ProcessUpdates"<<endl;
		return FALSE;
		
	}
	
}


extern "C" BOOL PASCAL EXPORT SetWorkspace(int &WorkID )
{
	NewWorkspaceID = WorkID;
	*ChangesMade = TRUE;
	return TRUE;
}

extern "C" BOOL PASCAL EXPORT DoAllUpdates(int & percent)
{
	DoAllUpdatesNow=2;
	*ChangesMade = TRUE;
	ResetEvent(Notify);
	WaitForSingleObject(Notify, INFINITE);
	percent = curPercent;
	return TRUE;

}

extern "C" BOOL PASCAL EXPORT ContinueAllUpdates(int & percent)
{
	ResetEvent(Notify);
	WaitForSingleObject(Notify, INFINITE);
	percent = percentDone;
	return TRUE;

}

//tries to open a saphire project acording to the mode given
void ProjectOpen(CDatabase &database, int mode)
{
	if(mode <= 0) //said update, but no updates exist
	{
		ProjectOpened = FALSE;
		return;
	}
	//get the project location
	//CString ProjectLoc;
	CRecordset recsetProjLoc( &database );
	CString sqlGetProjLoc;
	sqlGetProjLoc.Format("SELECT Mode.SaphireProjPath FROM Mode WHERE (((Mode.ModeID)=%d));", mode);
	recsetProjLoc.Open(CRecordset::forwardOnly, sqlGetProjLoc ,CRecordset::noDirtyFieldCheck);
	CString tempPath;
	recsetProjLoc.GetFieldValue("SaphireProjPath",tempPath);
	ProjectLoc = tempPath;
	//strcpy(ProjectLoc, tempPath, 60)
	//Open the project
	Project_Open(ProjectLoc);
	
	//Check to see if the Project was opened correctly
	int rError = Risk_Error(); 
	if (rError != 0)
	{
		char rErrorDesc[60];
		Risk_Error_Description(rError, rErrorDesc);
		//TestMessage("Yes");
		CString eMessage(rErrorDesc);
		MessageBox(NULL,eMessage,"ERROR", MB_ICONEXCLAMATION | MB_ICONWARNING | MB_SYSTEMMODAL);
		ProjectOpened = 0;
		Error<<"Failed to open project"<<endl;
		ProjectOpened = FALSE;
		return;
	}
	else 
		ProjectOpened = TRUE;
}

void UpdateModes(CDatabase &db, int ModeList[10], int &size)
{
	//Load all of the modes that will need updated
	CRecordset recsetModes( &db );	
	CString sqlStringModes = "SELECT DISTINCT RiskPeriods.ModeID FROM RiskPeriods WHERE (((RiskPeriods.NeedUpdate)=True));";
	recsetModes.Open(CRecordset::forwardOnly,sqlStringModes,CRecordset::noDirtyFieldCheck);
	int i =0;
	CString ModeID;
	size = 0;
	if( recsetModes.IsEOF())
	{
		ModeList[0] = -1001;
		ChangesLeft = FALSE;
		size = 0;
		return;
	}
	while( !recsetModes.IsEOF())
	{
		
		if( ! recsetModes.IsDeleted() )  //if it is a good record
		{
			++size;
			recsetModes.GetFieldValue("ModeID",ModeID);
			ModeList[i] = atoi((LPCTSTR)ModeID); 
		}
			
		// goto next record
		recsetModes.MoveNext();
		++i;
	}
	ChangesLeft = TRUE;
}


DWORD PASCAL ProcessUpdates(void * lpData)
{
	Done = FALSE;
	RiskFunctions RiskFunc;
	CDatabase database;
	RiskFunc.GetDatabase(database);
	curPercent=0;
	percentDone=0;//stores the p
	DWORD timeSec; //stores the current seconds time to see if need to update the %complete window
	DWORD curTimeSec;
	int modesToUpdate[10] = {-1001,};
	int numOfModes=0;
	int curModeIndex=0;
	int ThreadModeID = -10;
	// to keep track of the update speed...
	DWORD startTime;
	startTime = 0;
	totalUpdatesDone = 0;
	*ChangesMade = FALSE;
	int percentCompletedLast =0;
	int numOfUpdates=0; //stores the number of updates left to be done
	int totalUpdates=0; //stores the total number of updates that were to be done  //used to calculate the %compleete 
	int i =0;
	UpdateModes(database, modesToUpdate, numOfModes);
	CString nextTimePeriod;//stores the next time period to be updated
	
	//if there is a valid mode try and open the project with the first mode
	if(modesToUpdate[0] != -1001)
		ProjectOpen(database, modesToUpdate[0]);
	else
		ChangesLeft = FALSE;
	
	
	//Open table to get each TimePeriod out of
	CRecordset recset2( &database );
	
	
	CString runString("SELECT DISTINCT RiskPeriods.PeriodTime FROM RiskPeriods WHERE ((RiskPeriods.NeedUpdate)=Yes) AND ((RiskPeriods.WorkspaceID)= ");
					 //SELECT DISTINCT RiskPeriods.PeriodTime FROM RiskPeriods WHERE (((RiskPeriods.NeedUpdate)=Yes) AND ((RiskPeriods.WorkspaceID)=5)) AND ((RiskPeriods.ModeId)=-1);

	CString temp;
	temp.Format("%d) AND ((RiskPeriods.ModeId)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
	ThreadMode = modesToUpdate[curModeIndex];
	CString sqlString1= runString + temp;
	if(!recset2.IsOpen())
	recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
	
	CString sqlString2("UPDATE RiskPeriods SET RiskPeriods.NeedUpdate = No");
	CString sqlStringModes = "SELECT DISTINCT RiskPeriods.ModeID FROM RiskPeriods WHERE (((RiskPeriods.NeedUpdate)=True));";

	
	//if the workspaceID has been change load the new workspaceID
	if (WorkspaceID != NewWorkspaceID)
	{
		WorkspaceID = NewWorkspaceID;
		CString temp2;
		temp2.Format("%d) AND ((RiskPeriods.ModeId)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
		ThreadMode = modesToUpdate[curModeIndex];
		sqlString1= runString + temp2;
		if(recset2.IsOpen())
			recset2.Close();
		if(!recset2.IsOpen())
			recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
		
	}
	
	
	//run the thread while thread is specified as active and the project was opened
	//while(*threadActive && ProjectOpened && 1>2)
	while(*threadActive)
	{
		//Thread paused if GetBeNames or other functions need to use a project
		if(PauseThread == TRUE)
		{
			IsPaused = TRUE;
			ResetEvent(Pauseing);
			WaitForSingleObject(Pauseing, INFINITE);
			//reset the project after it becomes unpaused
			UpdateModes(database, modesToUpdate, numOfModes);
			Project_Close();
			ProjectOpen(database, modesToUpdate[0]);
			curModeIndex = 0;
			CString temp2;
			temp2.Format("%d) AND ((RiskPeriods.ModeID)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
			ThreadMode = modesToUpdate[curModeIndex];
			sqlString1 = runString + temp2;
			*ChangesMade = FALSE;

		}
		IsPaused = FALSE;
		// STOP TIMER
		if (startTime)
		{
			totalTimeSpentUpdating += timeGetTime() - startTime;
			totalUpdatesDone++;	
		}

		//done with all of the updates in one mode move to the next mode
		if(ChangesLeft == FALSE && (curModeIndex < numOfModes-1))
		{
			if(numOfModes == 0)
				ProjectOpened = FALSE;
			else
			{
				++curModeIndex;
				CString temp2;
				temp2.Format("%d) AND ((RiskPeriods.ModeID)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
				ThreadMode = modesToUpdate[curModeIndex];
				sqlString1 = runString + temp2;
				ChangesLeft = TRUE;
				if(recset2.IsOpen())
					recset2.Close();
				if(!recset2.IsOpen())
					recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
				//if doing all updates one more total updates must be added for every new mode
				if(DoAllUpdatesNow == 1)
					++numOfUpdates;
			}
			
		}
		
		//if the project was not opened or there are no modes to update then wait for modes to update 
		//or a good project 
		if(ProjectOpened == FALSE || numOfModes == 0)   //the project is not oppened
		{
			while(*ChangesMade != TRUE  && PauseThread != TRUE)
			{
				Sleep(0);
			}
			if(PauseThread != TRUE) //only update if the the tread in not ment to be paused
			{
				UpdateModes(database, modesToUpdate, numOfModes);
				Project_Close();
				ProjectOpen(database, modesToUpdate[0]);
				curModeIndex = 0;
				CString temp2;
				temp2.Format("%d) AND ((RiskPeriods.ModeID)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
				ThreadMode = modesToUpdate[curModeIndex];
				sqlString1 = runString + temp2;
				*ChangesMade = FALSE;
				if (WorkspaceID != NewWorkspaceID)
				{
					WorkspaceID = NewWorkspaceID;
					CString temp2;
					temp2.Format("%d) AND ((RiskPeriods.ModeId)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
					ThreadMode = modesToUpdate[curModeIndex];
					sqlString1= runString + temp2;
					if(recset2.IsOpen())
						recset2.Close();
					if(!recset2.IsOpen())
						recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
				}
			}
		}
		if(!(*threadActive))
			break;
		

		if(ProjectOpened == TRUE && numOfModes != 0) //the project was opened successfuly and there are modes to be updated
		{
			while(((*threadActive) && (ChangesLeft==0) && (curModeIndex == (numOfModes-1))) || (WorkspaceID != 0))
			{
				Sleep(0);
				if(ChangesLeft || *ChangesMade  || PauseThread)
				{
					//reload the modes that need to be updated
					if(*ChangesMade)
					{
						UpdateModes(database, modesToUpdate, numOfModes);
						Project_Close();
						ProjectOpen(database, modesToUpdate[0]);
						curModeIndex = 0;
						CString temp2;
						temp2.Format("%d) AND ((RiskPeriods.ModeID)= %d);", WorkspaceID, modesToUpdate[curModeIndex]);
						ThreadMode = modesToUpdate[curModeIndex];
						sqlString1= runString + temp2;
						
					}
					
					
					
					ChangesLeft=TRUE;
					*ChangesMade=FALSE;
					if(!recset2.IsOpen())
					recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
					//check to see if workspaceID has changed
					if (WorkspaceID != NewWorkspaceID)
					{
						WorkspaceID = NewWorkspaceID;
						CString temp2;
						temp2.Format("%d) AND ((RiskPeriods.ModeId)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
						ThreadMode = modesToUpdate[curModeIndex];
						sqlString1= runString + temp2;
						if(recset2.IsOpen())
							recset2.Close();
						if(!recset2.IsOpen())
							recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
					}
					// START TIMER
					startTime = timeGetTime();
					break;
				}
			}
			if(!(*threadActive))
				break;
			
			if((DoAllUpdatesNow >1) && (PauseThread != TRUE))
			{
				//timeSec=time.GetSecond();
				curPercent = 0;
				timeSec=timeGetTime();
				int percentCompletedLast =0;
				
				//get all of the number of updates needed to be made;
				CRecordset recset( &database );
				CString temp2;
				temp2.Format("%d);", WorkspaceID);
				sqlString1= runString + temp2;
				
				
				if(!recset.IsOpen())
					recset.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
				while( !recset.IsEOF())
				{
					if( ! recset.IsDeleted() )  //if it is a good record
						++numOfUpdates;
					// goto next record
					recset.MoveNext();
					if(numOfUpdates<1)
						ChangesLeft=FALSE;
				}
				totalUpdates = numOfUpdates;
				if(recset.IsOpen())
					recset.Close(); //close the table results
				DoAllUpdatesNow=1;
				
				//Reset to do the updates for all the specific modes
				if(recset2.IsOpen())
					recset2.Close();
				UpdateModes(database, modesToUpdate, numOfModes);
				Project_Close();
				ProjectOpen(database, modesToUpdate[0]);
				curModeIndex = 0;
				CString temp1;
				temp1.Format("%d) AND ((RiskPeriods.ModeId)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
				ThreadMode = modesToUpdate[curModeIndex];
				sqlString1= runString + temp1;
						
				
				if(!recset2.IsOpen())
					recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
				*ChangesMade=FALSE;
				
			}
			
				
			if((DoAllUpdatesNow)==0 && ChangesLeft==TRUE && (PauseThread != TRUE))
			{
				if(*ChangesMade) //ther has been changes made so refresh the nextTimePeriod table
				{
					UpdateModes(database, modesToUpdate, numOfModes);
					curModeIndex = 0;
					CString temp;
					temp.Format("%d) AND ((RiskPeriods.ModeID)=%d);", WorkspaceID, modesToUpdate[curModeIndex]);
					ThreadMode = modesToUpdate[curModeIndex];
					sqlString1= runString + temp;
					
					
					if(recset2.IsOpen())
						recset2.Close();
					if(!recset2.IsOpen())
						recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
					
					*ChangesMade = FALSE;
					
				}
				
				
				if(recset2.IsEOF())//if there are no more updates to be made set changesMade to FALSE;
				{
					ChangesLeft=FALSE;
					if(recset2.IsOpen())
						recset2.Close();
				}

				else  //get the next TimePeriod that needs to be updated.
				{
					recset2.GetFieldValue("PeriodTime",nextTimePeriod);
					recset2.MoveNext();
					//set needUpdate of current TimePeriod to No
					CString temp;
					CString setNeedUpdateNo;  //create add on to origional sql satement to only edit one needUpdate 
					temp.Format(" WHERE (((RiskPeriods.PeriodTime)=#%s#));", nextTimePeriod);
					setNeedUpdateNo = sqlString2 + temp;
					database.ExecuteSQL(setNeedUpdateNo);
					//database.ExecuteSQL("UPDATE RiskPeriods SET RiskPeriods.NeedUpdate = No WHERE (((RiskPeriods.PeriodTime)=900));");
					//Update the table after setting the needUpdate to No
					CStringLList filler; // a filler because we don't need critical components
					RiskFunc.update(nextTimePeriod, database, FALSE, filler, WorkspaceID, ThreadModeID);
					
					
				}
			}
			else  if(((DoAllUpdatesNow)==1) && (PauseThread != TRUE))
			{
				if(recset2.IsEOF())
				{
					ChangesLeft=FALSE;
					if(recset2.IsOpen())
					recset2.Close();
				}
				else
				{
					recset2.GetFieldValue("PeriodTime",nextTimePeriod);
					recset2.MoveNext();
					CStringLList filler; // a filler because we don't need critical components
					RiskFunc.update(nextTimePeriod, database, FALSE, filler, WorkspaceID, ThreadModeID);
					
				}
				if(numOfUpdates ==1)
				{
					ChangesLeft=FALSE;
					if(recset2.IsOpen())
						recset2.Close();
					//done updating all so set all needUpdate to No
					if(curModeIndex >= numOfModes-1)
					{
						database.ExecuteSQL(sqlString2);
						//now set back to prosseccing updates normaly
						DoAllUpdatesNow = 0;
					}
				}
				
				if(numOfUpdates >0)
					--numOfUpdates;
				
			
				//update the percent compleete bar if the time gone by is more than a second off or if the 
				//percent compleete is more than "PERCENTUPDATELEVEL" complete than last time
				curTimeSec=timeGetTime();
				if(totalUpdates ==0)
				{
					curPercent = 100;
					SetEvent(Notify);
				}
				else
					curPercent=((100 * (totalUpdates-numOfUpdates) / totalUpdates));
				if(((curPercent-percentDone)>PERCENTUPDATELEVEL)||((curTimeSec - timeSec) >  UPDATETIMEINC))
				{
					//*PercentDone = curPercent;//update the percent compleete bar
					percentDone=curPercent;
					SetEvent(Notify);

					timeSec=curTimeSec;
				}
			}
		}
		if(!(*threadActive))
			break;

	}
	if(recset2.IsOpen())
		recset2.Close();
	database.Close();
	Project_Close();
	Done = TRUE;
	SetEvent(Notify);
	//Delete UsedCompList the ArrayList, it is no longer needed
	UsedCompList.Delete();
	AllSystemsList.Delete();
	return (TRUE);
}

extern "C" int PASCAL EXPORT GetAverageUpdateSpeed(int & tUpdatesDone)
{
	tUpdatesDone = totalUpdatesDone;
	if (totalUpdatesDone)
		return totalTimeSpentUpdating / totalUpdatesDone;
	else
		return -1;
}

//closes the thread
extern "C" BOOL PASCAL EXPORT CloseWorkerThread()
{
	Done = FALSE;
	if (ProjectOpened == FALSE)
		Done = TRUE;
	*threadActive = 0;
	*ChangesMade = TRUE;
	ResetEvent(Notify);
	WaitForSingleObject(Notify, INFINITE);
	Sleep(0);
	return Done;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Functions for geting the basic events of a system////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//pass in the section index and a string [25] with a '\0' last char. The string is filled with the name of the indexed section
//sysDesc is a char [61] will be filled with the system description and a '\0' at [61]
//False is Returned if index is not between 1 and SystemCount or the project was not oppened.
extern "C" BOOL PASCAL EXPORT GetSystemName(int index, LPSTR & name, LPSTR &sysDesc, int MappingID)
{		
	//getting the System name usin the FaultTree heads
	if(MappingID == 0)
	{
		//if index is not within bounds return false
		if(index == 0 || (index > SystemCount()))
			return FALSE;
		
		if(ProjectOpened == TRUE && hSageRiskDLL != NULL)
		{
			System_Find_Name_Indexed(index);
			System_Get_Description(sysDesc);
			sysDesc[61]='\0';
			char newName[25];
			//newName = name;
			System_Get_Name(newName);
			newName[25] = '\0';
			memcpy(name, newName, 25);
			return TRUE;
		}
		else
			return FALSE;
	}
	if(MappingID == 1)  //use *- as the map
	{
		return true;
	}
	if(MappingID == 2) //use ?? as the Map
	{
		return true;
	}
	if(MappingID == 3)  //use ??? as the Map
	{
		return true;
	}
	if(MappingID == 4)  //use ???? as the Map
	{
		return true;
	}
	else
		return false;
}

//returns the number of sections in the project
//return -1 if failed
extern "C" int PASCAL EXPORT SystemCount(int MappingID)
{
	//getting the System name usin the FaultTree heads
	if(MappingID == 0)
	{
		//Initialize the sageRisk DLL function calls
		if(ProjectOpened == TRUE && hSageRiskDLL != NULL)
		{
			int tops = System_Count_Tops();
			return tops;
		}

		else
			return -1;
	}
	if(MappingID == 1)  //use *- as the map
	{
		return true;	
	}
	if(MappingID == 2) //use ?? as the Map
	{
		return true;
	}
	if(MappingID == 3)  //use ??? as the Map
	{
		return true;
	}
	if(MappingID == 4)  //use ???? as the Map
	{
		return true;
	}
	else
		return false;
	
	
}

//returns the number of base componects created according to the mapping criteria given to it
extern "C" int PASCAL EXPORT GetNumOfBComps(LPSTR sysName)
{
	return AllSystemsList.GetNumOfCompBEGroups();
}

//gets the base component name according to the index and fills bCompName with that name
extern "C" BOOL PASCAL EXPORT GetBCompName(int index, LPSTR & bCompName)
{
	if(AllSystemsList.GetCompBEGroupName(index, bCompName))
		return true;
	else
		return false;
}


//Returns the indexed basic event of the system
extern "C" BOOL PASCAL EXPORT GetBEName(LPSTR sysName, int index, LPSTR & bEName, LPSTR &bEDesc, int & BCompID)
{
	CString compName = sysName;  //change to a CString for comparison
	
	//If the System has not been loaded form saphire, load it the linked list of systems
	//if(!AllSystemsList.Exists(sysName))
	
	if(!AllSystemsList.Exists(sysName))
	{
		//Load the system if it fails this function fails also
		if(!LoadSystem(AllSystemsList, sysName))
			return FALSE;
	}
	//setLook to the desired system so it returns the correct be name.
	//if it fails this function fails also
	if(!AllSystemsList.SetLook(sysName))
		return FALSE;
	
	
	if(AllSystemsList.GetBEName(index, bEName, bEDesc, BCompID))
		return TRUE;
	else
		return FALSE;
}


extern "C" int PASCAL EXPORT GetNumOfBE(LPSTR sysName)
{
	//if the system has not been loaded load it and set CurSys pointing to it
	if(!AllSystemsList.Exists(sysName))
	{
		LoadSystem(AllSystemsList, sysName);
		AllSystemsList.SetLook(sysName);
	}
	return AllSystemsList.NodeSize(sysName);
	
	
}

//loads all of basic events of a saphire project and seperates them into sections using a TreeListLL
BOOL PASCAL LoadSystem(ArrayListLL &list, char sysName[25])
{
	

	System_Find_Name(sysName);
		
   	char (*sysList)[25];
	char (*descriptions)[61];	
	char sysDesc[61];
	int NumOfBE=0;
	NumOfBE= System_Get_Logic_BE_Cnt();
	
	sysList = new char[NumOfBE][25];
	descriptions = new char[NumOfBE][61];
	
	//get the list of basic event names
	System_Get_Logic_BE_Names(NumOfBE, sysList);
	System_Find_Name(sysName);

	System_Get_Description(sysDesc);
	//Get all of the descriptions of each basic event and put it in the descriptions array
	char singleDesc[61];
	char beName[25];
	for(int i =0; i<NumOfBE; ++i)
	{
		memcpy(beName, sysList[i], 24);
		beName[25] = '\0';
		Event_Find_Name(beName);
		Event_Get_Description(singleDesc);//get the description for the one basic event
		singleDesc[61] = '\0';
		memcpy(descriptions[i], singleDesc, 61);
	}

	//push the Basic event array and the description array into the linked list of systems
	//AllSystemsList.Push(sysName, sysDesc, NumOfBE, sysList, descriptions);
	list.Push(sysName, sysDesc, NumOfBE, sysList, descriptions);
	
	//delete [] sysList;	is deleted when the Linked List is dealocated
	//delete [] descriptions; is deleted when the linked list id dealocated
	SectionsFilled = TRUE;
	return TRUE;

}





/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Functions for geting the critical components////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

//calls to calculate the risk level and load the critical basic events
//pass time in this format "20yr-mo-dy hr:mn:sc" (military hours)
extern "C" BOOL PASCAL EXPORT LoadCritBE(LPSTR time)
{
	RiskFunctions rFunc;
	CDatabase database;
	rFunc.GetDatabase(database);	
	rFunc.update(time, database, TRUE, CritComps, WorkspaceID);
	return TRUE;
}


//returns the next critical basic event that was calculated
extern "C" BOOL PASCAL EXPORT GetNextCritBE(LPSTR &retComp, double &riskIncrease)
{
	if(CritComps.Count() > 0)
	{
		CString RetStr;
		riskIncrease = CritComps.Pop(RetStr);
		memcpy(retComp, RetStr, 24);
		return TRUE;
	}
	else 
		return FALSE;

}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////Functions for VScreen, getting the risk from a user definded components off line //////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//adds a basic event to the lists to calculate a userer requested risk level by basic events
extern "C" BOOL PASCAL EXPORT AddSingleComp(int comp)
{
	RiskFunctions rFunc;
	CDatabase database;
	rFunc.GetDatabase(database);
	CString sqlCall;
	//sqlCall.Format("SELECT BaseCompBE.BEName FROM (BaseCompBE INNER JOIN CompBaseComponent ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID) INNER JOIN Component ON CompBaseComponent.ComponentID = Component.ComponentID WHERE (((Component.ComponentName)='%s'));", comp);
	sqlCall.Format("SELECT Distinct BaseCompBE.BEName FROM BaseCompBE INNER JOIN (CompBaseComponent INNER JOIN Component ON CompBaseComponent.ComponentID = Component.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((Component.ComponentID)=%d))AND ((BaseCompBE.ModeID)=%d);", comp, CurModeID);

	CRecordset recset( &database );
	if(!recset.IsOpen())
		recset.Open(CRecordset::forwardOnly,sqlCall,CRecordset::noDirtyFieldCheck);
	// the basic events of each component to the list
	CString beName;
	while( !recset.IsEOF())
	{	recset.GetFieldValue("BEName",beName);
		if( ! recset.IsDeleted() )  //if it is a good record
		{
			UsedCompList.Push(beName);	
		}
		// goto next record
		recset.MoveNext();
	}
	return TRUE;
}

//clears the basic event list for user specified risk calculations
extern "C" BOOL PASCAL EXPORT ClearBEList()
{
	CString filler; //data is not needed so use a filler as a paramiter
	int numInLL = UsedCompList.Count();
	for(int i = 0; i<numInLL; ++i)
		UsedCompList.Pop(filler);
	return TRUE;
}

//calculates the risk level with the basic events out of UsedCompList set as true
//returns false if the function is already running or the project is not opened
extern "C" BOOL PASCAL EXPORT CalcRiskFromCompList(double &riskLev)
{
	//save variables to open the thread back up after closing
	
	//LPSTR odbcName = ODBCName ;
	//LPSTR runningDir = RUNNINGDIR;
	//BOOL AdataBase = AccessDB;
		
	//CloseWorkerTread();

	if(CurrentlyCalculating && ProjectOpened)
		return FALSE;
	else
	{
		CurrentlyCalculating = TRUE;
		RiskFunctions rFunc;
		CDatabase database;
		CStringLList filler;
		rFunc.GetDatabase(database);
		riskLev=rFunc.ReadRiskLev(database, "", UsedCompList, filler, false);
		CurrentlyCalculating = FALSE;
		return TRUE;

	}
	//StartWorkerTread(1, 1, odbcName, runningDir, AdataBase);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//will rebuild a saphire project to version 7 
//WorkerThread must be suspended before this can occur
//Closes any project open, if a fuction other than the Thread was using a project, call setModeID
//before calling the other functions
extern "C" void PASCAL EXPORT UpdateProject(LPSTR projLoc)
{
	
	Project_Close();
	Project_Upgrade(projLoc);
		
}



//sets the current mode
//use before calling most functions if your mode has changed
//must pause worker thread before calling this function
extern "C" BOOL PASCAL EXPORT SetModeID(int newModeID)
{
	RiskFunctions RiskFunc;
	CDatabase database;
	RiskFunc.GetDatabase(database);
	if(IsPaused)
	{
		//
		
		//Criteria for the project and opening a different one
		//if it is the first time called after worker thread was stoped and worker thread stoped in the wrong project
		//if worker thread has been paused before but a new mode had been requested.
		if(ThreadMode != CurModeID || CurModeID != newModeID)
		{
			//as long as curModeId is correct don't load the project
			if(CurModeID != newModeID)
			{
				CurModeID = newModeID;
				CString NewProjLoc;
				CString sqlString;
				sqlString.Format("SELECT Mode.SaphireProjPath FROM Mode WHERE (((Mode.ModeID)=%d));", newModeID);
				CRecordset recset( &database );
				recset.Open(CRecordset::forwardOnly,sqlString,CRecordset::noDirtyFieldCheck);
				recset.GetFieldValue("SaphireProjPath",NewProjLoc);
				
				Project_Close();
				ProjectOpen( database, newModeID);
				if(ProjectOpened == FALSE)
					return FALSE;
			}
		}
		return TRUE;

	}
	else
		return FALSE;
}


//returns whether the opening of a project was a success and a description to rErrorDesc
//rErrorDesc must be char[60]
//must call SuspendUpdates before this and ResumeUpdates when done
extern "C" int PASCAL EXPORT IsProjectGood(LPSTR projLoc, LPSTR & rErrorDesc)
{
	//Open the project
	Project_Close();
	Project_Open(projLoc);
	
	//Check to see if the Project was opened correctly
	int rError = Risk_Error(); 
	if (rError != 0)
	{
		
		Risk_Error_Description(rError, rErrorDesc);
		return rError;
	}
	else
	{
		return 0;
	}

}


extern "C" BOOL PASCAL EXPORT SuspendUpdates( )
{
	CurModeID = 0; //resting the Current mode so that it will be set to the correct mode 
	PauseThread = TRUE;
	while(IsPaused != TRUE)
		Sleep(50);
	return TRUE;
}

extern "C" BOOL PASCAL EXPORT ResumeUpdates( )
{
	PauseThread = FALSE;
	SetEvent(Pauseing);
	return TRUE;
}
