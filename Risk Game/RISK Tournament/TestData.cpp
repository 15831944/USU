// TestData.cpp: implementation of the CTestData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RISK Tournament.h"
#include "TestData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestData::CTestData()
{
	nPlayers = 0;
	DLLList = NULL;
	PPG = 0;
	Repetitions = 0;
	gamesPlayed = 0;
	currentPlayers = NULL;
}

CTestData::~CTestData()
{

}
