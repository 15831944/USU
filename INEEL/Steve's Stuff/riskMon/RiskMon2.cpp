// RiskMon.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "RiskMon.h"
#include "RiskFunctions.h"
#include "node.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
int * threadActive;
int * ChangesMade;
int NewWorkspaceID =-1;
int WorkspaceID= 0;
BOOL Done;
int DoAllUpdatesNow = 0;
BOOL ChangesLeft = FALSE;

int curPercent=0;
int percentDone=0;//stores the percent done when doing doAllUpdates

HANDLE Notify;


//typedefs for the sagerisk dll
typedef void (CALLBACK* PROJECT_OPEN)(CString);
typedef void (CALLBACK* PROJECT_CLOSE)();
typedef int (CALLBACK* RISK_ERROR)();
DWORD PASCAL ProcessUpdates(void * lpData);
extern "C" BOOL PASCAL EXPORT StartWorkerThread(int &tActive, int &cMade, LPSTR odbcName, LPSTR projLoc, LPSTR runningDir);
fstream Error(Debug, ios::app, filebuf::sh_write);

/////////////////////////////////////////////////////////////////////////////
// CRiskMonApp construction

CRiskMonApp::CRiskMonApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRiskMonApp object


extern "C" BOOL PASCAL EXPORT StartWorkerThread(int &tActive, int &cMade, LPSTR odbcName, LPSTR projLoc, LPSTR runningDir)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	
	//char message[200];
	//wsprintf(message,"StartWorkerThread was called with parameters: tActive = %i, cMade = %i, odbcName = %s, projLoc = %s, runningDir = %s",tActive,cMade,projLoc,runningDir);
	//MessageBox(NULL, message,"Risk Update DLL",MB_OK);
	CString myString;
	myString.Format("StartWorkerThread was called with parameters: tActive = %i, cMade = %i, odbcName = %s, projLoc = %s, runningDir = %s",tActive,cMade,odbcName,projLoc,runningDir);

	
	Error<<myString;

	ODBCName = odbcName;
	ProjectLoc = projLoc;
	RUNNINGDIR = runningDir;
	
	CString errorLogFile;
	errorLogFile = RUNNINGDIR + "ErrorLog.dat";
	DeleteFile(errorLogFile);
	DeleteFile("E:\\StevesTest\\Error.txt");	
	DWORD dwThreadID;

	
	threadActive = &tActive;
	ChangesMade = &cMade;
	
	
	Notify = CreateEvent(NULL, TRUE, FALSE, "NotifyRiskProject_s");

	
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
		return FALSE;
		
	}

	return TRUE;
	
}


BOOL  PASCAL EXPORT SetWorkspace(int &WorkID )
{
	NewWorkspaceID = WorkID;
	*ChangesMade = TRUE;
	return TRUE;
}

BOOL PASCAL EXPORT DoAllUpdates(int & percent)
{
	DoAllUpdatesNow=2;
	*ChangesMade = TRUE;
	ResetEvent(Notify);
	WaitForSingleObject(Notify, 10000);
	percent = curPercent;
	return TRUE;

}

BOOL PASCAL EXPORT ContinueAllUpdates(int & percent)
{
	ResetEvent(Notify);
	WaitForSingleObject(Notify, 10000);
	percent = percentDone;
	return TRUE;

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
	int percentCompletedLast =0;
	int numOfUpdates=0; //stores the number of updates left to be done
	int totalUpdates=0; //stores the total number of updates that were to be done  //used to calculate the %compleete 
	

	CString nextTimePeriod;//stores the next time period to be updated
	//Open table to get each TimePeriod out of
	CRecordset recset2( &database );
	
	CString runString("SELECT RiskPeriods.PeriodTime FROM RiskPeriods WHERE (((RiskPeriods.NeedUpdate)=Yes) AND WorkspaceID = ");
	CString temp;
	temp.Format("%d);", WorkspaceID);
	CString sqlString1= runString + temp;
	if(!recset2.IsOpen())
	recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
	
	CString sqlString2("UPDATE RiskPeriods SET RiskPeriods.NeedUpdate = No");
	
	
	HINSTANCE				hDLL;               // Handle to DLL
	PROJECT_OPEN			Project_Open;    // Function pointer
	PROJECT_CLOSE			Project_Close;
	RISK_ERROR				Risk_Error;
	hDLL = LoadLibrary("SageRisk.dll");
	Error<<endl<<ProjectLoc;

	Project_Open = (PROJECT_OPEN)GetProcAddress(hDLL, "Project_Open");
	Project_Close = (PROJECT_CLOSE)GetProcAddress(hDLL, "Project_Close");
	Risk_Error = (RISK_ERROR)GetProcAddress(hDLL, "Risk_Error");
	Project_Open(ProjectLoc);
	int temp2 = Risk_Error();
	Error<<endl<<temp2;
	while(*threadActive)
	{
		if	(WorkspaceID != NewWorkspaceID)
		{
			WorkspaceID = NewWorkspaceID;
			CString temp2;
			temp2.Format("%d);", WorkspaceID);
			sqlString1= runString + temp2;
			if(recset2.IsOpen())
				recset2.Close();
			if(!recset2.IsOpen())
				recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
		}
		while(*threadActive & (ChangesLeft==0))
		{
			Sleep(0);
			if(ChangesLeft || *ChangesMade)
			{
				ChangesLeft=TRUE;
				*ChangesMade=FALSE;
				if(!recset2.IsOpen())
				recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
				break;
				if	(WorkspaceID != NewWorkspaceID)
					{
						WorkspaceID = NewWorkspaceID;
						CString temp2;
						temp2.Format("%d);", WorkspaceID);
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
		
		if(DoAllUpdatesNow >1)
		{
			//timeSec=time.GetSecond();
			curPercent = 0;
			timeSec=timeGetTime();
			int percentCompletedLast =0;
			
			//get the number of updates needed to be made;
			CRecordset recset( &database );
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
			//Reset the updates to the beginning
			if(recset2.IsOpen())
				recset2.Close();
			if(!recset2.IsOpen())
				recset2.Open(CRecordset::forwardOnly,sqlString1,CRecordset::noDirtyFieldCheck);
			*ChangesMade=FALSE;
			
		}
		
			
		if((DoAllUpdatesNow)==0 && ChangesLeft==TRUE)
		{
			if(*ChangesMade) //ther has been changes made so refresh the nextTimePeriod table
			{
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
				RiskFunc.update(nextTimePeriod, database, FALSE, WorkspaceID);
				
				
			}
		}
		else
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
				RiskFunc.update(nextTimePeriod, database, FALSE, WorkspaceID);
				Sleep(0);
				
				
			}
			if(numOfUpdates ==1)
			{
				ChangesLeft=FALSE;
				if(recset2.IsOpen())
					recset2.Close();
				//done updating all so set all needUpdate to No
				database.ExecuteSQL(sqlString2);
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
	if(recset2.IsOpen())
		recset2.Close();
	database.Close();
//	Project_Close();
	
	Done = TRUE;
	SetEvent(Notify);
	return (TRUE);

}

BOOL PASCAL EXPORT CloseWorkerThread()
{
	Done = FALSE;
	*threadActive = 0;
	ResetEvent(Notify);
	WaitForSingleObject(Notify, 10000);
	Sleep(0);
	return Done;
}
BOOL PASCAL EXPORT ChangesMadeFunc()
{
	*ChangesMade = 1;
	return true;
}