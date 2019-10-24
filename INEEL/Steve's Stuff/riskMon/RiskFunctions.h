// RiskFunctions.h: interface for the RiskFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RISKFUNCTIONS_H__21BCB063_59BE_11D5_8CF1_00104B945A14__INCLUDED_)
#define AFX_RISKFUNCTIONS_H__21BCB063_59BE_11D5_8CF1_00104B945A14__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <afxdb.h>
#include "StringLList.h"
#include <fstream.h>
#include <Mmsystem.h>


const int PERCENTUPDATELEVEL=20;
const int MAXNAMELENG=24;
const DWORD UPDATETIMEINC = 1000; 


struct CritCompRec  
{

	
	int			occurrences;
	float		probablility;
	double		importance;
	double		riskReduction;
	double		riskIncrease;
	char		eventName[28];
	int filler;

};

class RiskFunctions  
{
public:

	double ReadRiskLev(CDatabase & database, CString, CStringLList &bEventNames, CStringLList &, bool);

	void update(CString , CDatabase & database, bool getCritComp, CStringLList &CritComp, int WorkID =-1, int ModeID =-10);
	void GetDatabase(CDatabase &);
	//void s_ProcessUpdates(bool);
	void ReadCritBE(CDatabase & database, CString & periodTime);
	void WriteBE(CString * array, int num);
	CString * LLtoStrArray(CStringLList & lList, int &size);
	CString LLtoCharArray(CStringLList & lList);
	CStringLList GetList(CDatabase &dataBase, CString sqlString, CString colName);
	RiskFunctions();
	virtual ~RiskFunctions();
	

private:
	
	
	


};

#endif // !defined(AFX_RISKFUNCTIONS_H__21BCB063_59BE_11D5_8CF1_00104B945A14__INCLUDED_)
