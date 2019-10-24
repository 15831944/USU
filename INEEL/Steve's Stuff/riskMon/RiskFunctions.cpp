// RiskFunctions.cpp: implementation of the RiskFunctions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "mfcTest.h"
#include "RiskFunctions.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
bool pause = true;

extern CString RUNNINGDIR;
extern CString ODBCName;
extern CString ProjectLoc;
extern CString Debug;
extern BOOL AccessDB;
typedef void (CALLBACK* PROJECT_OPEN)(CString);
typedef void (CALLBACK* CHGSET_FIND_NAME)(CString);
typedef int (CALLBACK* RISK_ERROR)();
typedef int (CALLBACK* CHGSET_DELETE)();
typedef void (CALLBACK* CHGSET_PUT_NAME)(CString);
typedef void (CALLBACK* CHGSET_PUT_DESCRIPTION)(CString);
typedef void (CALLBACK* CHGSET_PUT_SETTYPE)(int);
typedef void (CALLBACK* CHGSET_ADD)();
typedef void (CALLBACK* CHGSET_CLEAR_EVENT)();
typedef void (CALLBACK* EVENT_FIND_NAME)(CString);
typedef void (CALLBACK* EVENT_GET_NUMBER)(int &);
typedef void (CALLBACK* CHGSET_PUT_EVENT)(int);
typedef void (CALLBACK* CHGSET_PUT_FAILURETYPE)(char);
typedef void (CALLBACK* CHGSET_ADD_SINGLE)();
typedef void (CALLBACK* CHGSET_TOGGLEMARK)();
typedef void (CALLBACK* CHGSET_GENERATE_FAILUREDATA)();
typedef void (CALLBACK* SEQUENCE_SELECTALL)();
typedef void (CALLBACK* SEQUENCE_LOAD_SELECTED_CUTSETS)(int, int &, int &, int &, double &);
typedef void (CALLBACK* SEQUENCE_RELEASE_SELECTED_CUTSETS)();
typedef void (CALLBACK* SEQUENCE_CLEAR_SELECTIONS)();
typedef void (CALLBACK* PROJECT_CLOSE)();
typedef void (CALLBACK* CHGSET_MODIFY)();
typedef void (CALLBACK* GENERATE_ALL_SEQUENCE_CUTSETS)(bool, double, int, int, int, char [24]);
typedef void (CALLBACK* IMPORTANCE_ALL_SEQUENCES)(int);
typedef void (CALLBACK* IMPORTANCE_SORT)(int);
typedef int (CALLBACK* IMPORTANCE_COUNT_EVENTS)();
typedef void (CALLBACK* IMPORTANCE_GET_RUESULTS)(int, CritCompRec &);
typedef void (CALLBACK* IMPORTANCE_RELEASE)();




//Importance.All_Sequences(Risk.Birnbaum ---1);
//Importance.Sort(Risk.IncreaseSort ----5);
//impCount := Importance.Count_Events();---returns CARDINAL
//Importance.Get_Results(importanceList^);
//Importance.Release;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RiskFunctions::RiskFunctions()
{
	pause = true;
}

RiskFunctions::~RiskFunctions()
{

}

CStringLList RiskFunctions::GetList(CDatabase & dataBase, CString sqlString, CString colName)
{
	
	CStringLList retList;
	//CString retStr[10];
	int retStrCt=0;
	CString cur;			//holds current data to be inserted into the retStr array
	
	CRecordset recset( &dataBase );
	recset.Open(CRecordset::forwardOnly,sqlString,CRecordset::noDirtyFieldCheck);
	while( !recset.IsEOF())
		{
			
			if( ! recset.IsDeleted() )  //if it is a good record
			{	// Copy each column into a variable
				recset.GetFieldValue(colName,cur);

				// Insert values into the list
				retList.Push(cur);
				//retStr[retStrCt]=cur;
				++retStrCt;
				
			}
			// goto next record
			recset.MoveNext();
			
		}
	recset.Close();
	return retList;
	
}

CString RiskFunctions::LLtoCharArray(CStringLList & lList)
{
	CString joinedSt;
	double numInLL=lList.Count();
	CString space(" ");
	for(int i=0; i<numInLL; ++i)
	{
		CString temp;
		lList.Pop(temp);
		joinedSt += temp;
		joinedSt += space;
	}
	int stLeng = joinedSt.GetLength( ); 
	CString * str;
	str = new CString(joinedSt);
	return *str;

}

CString * RiskFunctions::LLtoStrArray(CStringLList & lList, int &size)
{
	CString* twoDArrayPtr;
	int numInLL=lList.Count();
	twoDArrayPtr = new CString[numInLL];
	for(int i=0; i<numInLL; ++i)
	{
		lList.Pop(twoDArrayPtr[i]);
	}
	
	size=i;
	return	twoDArrayPtr;

}

void RiskFunctions::WriteBE(CString * array, int numOfBE)
{
	fstream fileOut("BENames.dat", ios::out, filebuf::sh_write);
	fileOut<<numOfBE<<endl;
	for(int i=0; i<numOfBE; ++i)
	{
		fileOut<<array[i]<<endl;
	}
		
	fileOut.close();
}

void RiskFunctions::ReadCritBE(CDatabase & database, CString & periodTime)
{
	//Clear OOSResult
	database.ExecuteSQL("DELETE FROM OOSResult");
	//Clear RiskLevel table
	//database.ExecuteSQL("DELETE FROM RiskLevel");
	//ReadRiskLev(database, periodTime);
	fstream fileIn("CritBE.dat",ios::in, filebuf::sh_read);
	int numOfBE;
	
	fileIn>>numOfBE;	//get the number of names in the list
	if(numOfBE ==0)
		//only write the riskLev, no critical components
		
		return;
	char tempName[MAXNAMELENG];
	
	CString beName;
	CString temp;
	CString or(" OR ");
	CString beNameList;
	
	// Create the SQL statement to retrieve all of the ComponentID's using the BENames
	for(int i=0; i<numOfBE; ++i)
	{
		fileIn>>tempName;
		beName=tempName;
		temp.Format("CompBE.BEName='%s'",beName);
		beNameList += temp;
		if(i+1 != numOfBE)  //places an or between each tempName and not after the last one
			beNameList += or;
		
	}
	fileIn.close();
	

	
	CString sqlStatement;
	sqlStatement.Format("SELECT DISTINCT CompBE.ComponentID FROM CompBE WHERE ((%s));", beNameList);
	
	//create a linked list of the Critical ComponentID's
	CStringLList critCompLL(GetList(database,sqlStatement,"ComponentID"));

	//Write the Critical Components and RiskLevel
	CString curComp;
	int curCompNum;
	CString insCompSQLStatement;
	for(i=0; i<numOfBE; ++i)
	{
		critCompLL.Pop(curComp);
		curCompNum = atoi((LPCTSTR)curComp);
		insCompSQLStatement.Format("INSERT INTO  OOSResult Values('%d')", curCompNum);
		database.ExecuteSQL(insCompSQLStatement);
	}
}


void RiskFunctions::GetDatabase(CDatabase & database)
{
	CString DNSName(ODBCName);
	// Open the database
	database.Open(DNSName,false,false, "ODBC;");
}



void RiskFunctions::update(CString periodTime, CDatabase & database, bool getCritComp, CStringLList &CritComp ,int WorkID, int ModeID)
{
	//Get the Basic Events according to the procedures specified as running.
	CString SqlString;
	//SqlString.Format("SELECT DISTINCT CompBE.BEName FROM WorkspaceProcedures INNER JOIN (ProcComp INNER JOIN CompBE ON ProcComp.ComponentID = CompBE.ComponentID) ON WorkspaceProcedures.ProcedureID = ProcComp.ProcedureID WHERE ((((WorkspaceProcedures.StartTime)<=#%s#) AND ((WorkspaceProcedures.EndTime)>#%s#)) AND ((WorkspaceProcedures.WorkspaceID)= %d)); UNION SELECT DISTINCT CompBE.BEName FROM OOSList INNER JOIN CompBE ON OOSList.ComponentID = CompBE.ComponentID WHERE (((OOSList.StartTime)<=#%s#) AND ((OOSList.EndTime)>#%s#) AND ((OOSList.WorkspaceID)=%d));",periodTime, periodTime, WorkID,periodTime, periodTime, WorkID);
	if(AccessDB)
		SqlString.Format("SELECT DISTINCT BaseCompBE.BEName FROM BaseCompBE INNER JOIN ((WorkspaceProcedures INNER JOIN ProcComp ON WorkspaceProcedures.ProcedureID = ProcComp.ProcedureID) INNER JOIN CompBaseComponent ON ProcComp.ComponentID = CompBaseComponent.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((WorkspaceProcedures.StartTime)<=#%s#) AND ((WorkspaceProcedures.EndTime)>#%s#) AND ((WorkspaceProcedures.WorkspaceID)=%d)); UNION SELECT DISTINCT BaseCompBE.BEName FROM BaseCompBE INNER JOIN (OOSList INNER JOIN CompBaseComponent ON OOSList.ComponentID = CompBaseComponent.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((OOSList.StartTime)<=#%s#) AND ((OOSList.EndTime)>#%s#) AND ((OOSList.WorkspaceID)=%d));",periodTime, periodTime, WorkID,periodTime, periodTime, WorkID);
	else
		SqlString.Format("SELECT DISTINCT BaseCompBE.BEName FROM BaseCompBE INNER JOIN ((WorkspaceProcedures INNER JOIN ProcComp ON WorkspaceProcedures.ProcedureID = ProcComp.ProcedureID) INNER JOIN CompBaseComponent ON ProcComp.ComponentID = CompBaseComponent.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((WorkspaceProcedures.StartTime)<='%s') AND ((WorkspaceProcedures.EndTime)>'%s') AND ((WorkspaceProcedures.WorkspaceID)=%d)); UNION SELECT DISTINCT BaseCompBE.BEName FROM BaseCompBE INNER JOIN (OOSList INNER JOIN CompBaseComponent ON OOSList.ComponentID = CompBaseComponent.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((OOSList.StartTime)<='%s') AND ((OOSList.EndTime)>'%s') AND ((OOSList.WorkspaceID)=%d));",periodTime, periodTime, WorkID,periodTime, periodTime, WorkID);

	//SELECT DISTINCT BaseCompBE.BEName FROM BaseCompBE INNER JOIN ((WorkspaceProcedures INNER JOIN ProcComp ON WorkspaceProcedures.ProcedureID = ProcComp.ProcedureID) INNER JOIN CompBaseComponent ON ProcComp.ComponentID = CompBaseComponent.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((WorkspaceProcedures.StartTime)<=#6/20/01 4:05:06 AM#) AND ((WorkspaceProcedures.EndTime)>#1/7/01 4:30:00 PM#) AND ((WorkspaceProcedures.WorkspaceID)=12)); UNION SELECT DISTINCT BaseCompBE.BEName FROM BaseCompBE INNER JOIN (OOSList INNER JOIN CompBaseComponent ON OOSList.ComponentID = CompBaseComponent.ComponentID) ON BaseCompBE.BaseCompID = CompBaseComponent.BaseCompID WHERE (((OOSList.StartTime)<=#1/7/01 4:30:00 PM#) AND ((OOSList.EndTime)>#1/7/01 4:30:00 PM#) AND ((OOSList.WorkspaceID)=12));
	
	CStringLList x(GetList(database, SqlString, "BEName"));
	
	ReadRiskLev(database, periodTime, x, CritComp, getCritComp);

	
}


//calculates the risk level and gets crit be names if specified
double RiskFunctions::ReadRiskLev(CDatabase & database, CString periodTime, CStringLList &bEventNames, CStringLList &critComp, bool getCritComp)
{
	CString errorLogDir;
	errorLogDir = RUNNINGDIR + "ErrorLog.dat";
	fstream fileError(errorLogDir, ios::app, filebuf::sh_write);
	double  riskLev;
	//riskLev= rand();
	//riskLev= (riskLev/30000);
	//CString insRiskLev;
	//insRiskLev.Format("UPDATE RiskPeriods SET RiskPeriods.RiskValue = %f WHERE (((RiskPeriods.PeriodTime)= %s ));", riskLev, periodTime); 
	//database.ExecuteSQL(insRiskLev);
	
/////////////////////////////////////////////////////////////////////////////////////////////


	HINSTANCE						hDLL;               // Handle to DLL
	//Function pointers  to functions in SageRisk.dll
	PROJECT_OPEN						Project_Open;    // Function pointer
	CHGSET_FIND_NAME					ChgSet_Find_Name;
	RISK_ERROR							Risk_Error;
	CHGSET_PUT_NAME						ChgSet_Put_Name;
	CHGSET_PUT_DESCRIPTION				ChgSet_Put_Description;
	CHGSET_PUT_SETTYPE					ChgSet_Put_SetType;
	CHGSET_ADD							ChgSet_Add;
	CHGSET_CLEAR_EVENT					ChgSet_Clear_Event;
	EVENT_FIND_NAME						Event_Find_Name;
	EVENT_GET_NUMBER					Event_Get_Number;
	CHGSET_PUT_EVENT					ChgSet_Put_Event;
	CHGSET_PUT_FAILURETYPE				ChgSet_Put_FailureType;
	CHGSET_ADD_SINGLE					ChgSet_Add_Single;
	CHGSET_TOGGLEMARK					ChgSet_ToggleMark;
	CHGSET_GENERATE_FAILUREDATA			ChgSet_Generate_FailureData;
	CHGSET_DELETE						ChgSet_Delete;
	SEQUENCE_SELECTALL					Sequence_SelectAll;
	SEQUENCE_LOAD_SELECTED_CUTSETS		Sequence_Load_Selected_CutSets;
	SEQUENCE_RELEASE_SELECTED_CUTSETS	Sequence_Release_Selected_CutSets;
	SEQUENCE_CLEAR_SELECTIONS			Sequence_Clear_Selections;
	//CHGSET_TOGGLEMARK					ChgSet_ToggleMark;
	//PROJECT_CLOSE						Project_Close;
	CHGSET_MODIFY						ChgSet_Modify;
	GENERATE_ALL_SEQUENCE_CUTSETS		Generate_All_Sequence_CutSets;

	IMPORTANCE_ALL_SEQUENCES			Importance_All_Sequences;
	IMPORTANCE_SORT						Importance_Sort;
	IMPORTANCE_COUNT_EVENTS				Importance_Count_Events;
	IMPORTANCE_GET_RUESULTS				Importance_Get_Results;
	IMPORTANCE_RELEASE					Importance_Release;
	
	
	//float magicNum;
	hDLL = LoadLibrary("SageRisk.dll");
	
	
	//hDLL = AfxLoadLibrary("E:\\StevesTest\\Shell32.dll");
	//set the function pointers to point to their functions
	Project_Open = (PROJECT_OPEN)GetProcAddress(hDLL, "Project_Open");
	ChgSet_Find_Name = (CHGSET_FIND_NAME)GetProcAddress(hDLL, "ChgSet_Find_Name");
    Risk_Error = (RISK_ERROR)GetProcAddress(hDLL, "Risk_Error");
	ChgSet_Delete = (CHGSET_DELETE)GetProcAddress(hDLL, "ChgSet_Delete");
	ChgSet_Put_Description = (CHGSET_PUT_DESCRIPTION)GetProcAddress(hDLL, "ChgSet_Put_Description");
	ChgSet_Put_Name = (CHGSET_PUT_NAME)GetProcAddress(hDLL, "ChgSet_Put_Name");
	ChgSet_Put_SetType = (CHGSET_PUT_SETTYPE)GetProcAddress(hDLL, "ChgSet_Put_SetType");
	ChgSet_Add = (CHGSET_ADD)GetProcAddress(hDLL, "ChgSet_Add");
	ChgSet_Clear_Event = (CHGSET_CLEAR_EVENT)GetProcAddress(hDLL, "ChgSet_Clear_Event");
	Event_Find_Name = (EVENT_FIND_NAME)GetProcAddress(hDLL, "Event_Find_Name");
	Event_Get_Number = (EVENT_GET_NUMBER)GetProcAddress(hDLL, "Event_Get_Number");
	ChgSet_Put_Event = (CHGSET_PUT_EVENT)GetProcAddress(hDLL, "ChgSet_Put_Event");
	ChgSet_Put_FailureType = (CHGSET_PUT_FAILURETYPE)GetProcAddress(hDLL, "ChgSet_Put_FailureType");
	ChgSet_Add_Single = (CHGSET_ADD_SINGLE)GetProcAddress(hDLL, "ChgSet_Add_Single");
	ChgSet_ToggleMark = (CHGSET_TOGGLEMARK)GetProcAddress(hDLL, "ChgSet_ToggleMark");
	ChgSet_Generate_FailureData = (CHGSET_GENERATE_FAILUREDATA)GetProcAddress(hDLL, "ChgSet_Generate_FailureData");
 	Sequence_SelectAll = (SEQUENCE_SELECTALL)GetProcAddress(hDLL, "Sequence_SelectAll");
	Sequence_Load_Selected_CutSets = (SEQUENCE_LOAD_SELECTED_CUTSETS)GetProcAddress(hDLL, "Sequence_Load_Selected_CutSets");
	Sequence_Release_Selected_CutSets = (SEQUENCE_RELEASE_SELECTED_CUTSETS)GetProcAddress(hDLL, "Sequence_Release_Selected_CutSets");
	Sequence_Clear_Selections = (SEQUENCE_CLEAR_SELECTIONS)GetProcAddress(hDLL, "Sequence_Clear_Selections");
	//ChgSet_ToggleMark = (CHGSET_TOGGLEMARK)GetProcAddress(hDLL, "ChgSet_ToggleMark");
	//Project_Close = (PROJECT_CLOSE)GetProcAddress(hDLL, "Project_Close");
	ChgSet_Modify = (CHGSET_MODIFY)GetProcAddress(hDLL, "ChgSet_Modify");
	Generate_All_Sequence_CutSets = (GENERATE_ALL_SEQUENCE_CUTSETS)GetProcAddress(hDLL, "Generate_All_Sequence_CutSets");
	Importance_All_Sequences = (IMPORTANCE_ALL_SEQUENCES)GetProcAddress(hDLL, "Importance_All_Sequences");
	Importance_Sort = (IMPORTANCE_SORT)GetProcAddress(hDLL, "Importance_Sort");
	Importance_Count_Events = (IMPORTANCE_COUNT_EVENTS)GetProcAddress(hDLL, "Importance_Count_Events");
	Importance_Get_Results = (IMPORTANCE_GET_RUESULTS	)GetProcAddress(hDLL, "Importance_Get_Results");
	Importance_Release = (IMPORTANCE_RELEASE)GetProcAddress(hDLL, "Importance_Release");
	
	
	
	
	
	//CString name("E:\\RiskProjects\\Demo\\");
	//Project_Open("E:\\RiskProjects\\Demo\\");
	ChgSet_Find_Name("TestChgSet");
	int temp =Risk_Error();
	if( temp== 0)
		ChgSet_Delete();
	ChgSet_Put_Name("TestChgSet");
	ChgSet_Put_Description("Testing Risk Monitor");
	ChgSet_Put_SetType(0);
	ChgSet_Add();
	
	CString ntBEName; 
	int numOfBE = bEventNames.Count();
	int beNumber;  //temp number of the current basic event to pass into another function;
	
	for(int j=0; j<numOfBE; ++j)
	{
		ChgSet_Clear_Event();
		bEventNames.Pop(ntBEName);
		Event_Find_Name(ntBEName); //(Puts the ID number of the BeName into memory*)
		Event_Get_Number(beNumber); //(retrieves the ID number of the BE and puts it into beNumber*)
		if(beNumber != 0)//the basic event exists
		{
			ChgSet_Put_Event(beNumber);
			ChgSet_Put_FailureType('T');
			ChgSet_Add_Single();
		}
		else //the basic event does not exist, so write an error message
			fileError<<"This Basic Event does not exist in the project"<<endl<<ntBEName<<endl;
		
	}
	ChgSet_Modify();
	ChgSet_ToggleMark();
    ChgSet_Generate_FailureData();
	Generate_All_Sequence_CutSets(TRUE, 0.0000001, 2, 0, 0, "");


	
	
	
	
	Sequence_SelectAll();
	int filler1, filler2, filler3;
	Sequence_Load_Selected_CutSets(0, filler1, filler2, filler3, riskLev);
	Sequence_Release_Selected_CutSets();
	Sequence_Clear_Selections();
	
    CritCompRec *importanceList;
	int impCount;
	if(getCritComp == TRUE)
	{
		Importance_All_Sequences(1);
        Importance_Sort(5);
        impCount = Importance_Count_Events();
		//NEW(importanceList, impCount);
        importanceList = new CritCompRec[impCount+2];
		
		Importance_Get_Results(impCount, *importanceList);
        Importance_Release();
	}
        
	



	ChgSet_Find_Name("TestChgSet");
	ChgSet_ToggleMark();
	

	CString insRiskLev;
	if(periodTime != "")
	{
		if(AccessDB)
			insRiskLev.Format("UPDATE RiskPeriods SET RiskPeriods.RiskValue = %f WHERE (((RiskPeriods.PeriodTime)= #%s# ));", riskLev, periodTime);
		else
			insRiskLev.Format("UPDATE RiskPeriods SET RiskPeriods.RiskValue = %f WHERE (((RiskPeriods.PeriodTime)= '%s' ));", riskLev, periodTime);
		database.ExecuteSQL(insRiskLev);
	}
	//if a request for critical components is given
	if(getCritComp == true)
	{
		CString tempName;
		for(int i=1; i<=impCount; ++i)
		{
			tempName = (importanceList[i].eventName);
			critComp.Push(tempName, importanceList[i].importance);	
		}
	}
	return riskLev;
}


