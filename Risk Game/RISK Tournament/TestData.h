// TestData.h: interface for the CTestData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTDATA_H__112E9454_147A_4C6E_8504_B2AFB1D60C45__INCLUDED_)
#define AFX_TESTDATA_H__112E9454_147A_4C6E_8504_B2AFB1D60C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestData  
{
public:
	CTestData();
	virtual ~CTestData();
	int nPlayers;
	CString * DLLList;
	int PPG;
	int Repetitions;
	int * gamesPlayed;
	int * currentPlayers;
};

#endif // !defined(AFX_TESTDATA_H__112E9454_147A_4C6E_8504_B2AFB1D60C45__INCLUDED_)
