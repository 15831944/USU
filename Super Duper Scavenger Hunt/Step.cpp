// Step.cpp: implementation of the Step class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Super Duper Scavenger Hunt.h"
#include "Step.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Step::Step()
{
	CompletionInfo = "";
	Answer = "";
	Distance = "";
	Heading = "";
	IsRiddle = FALSE;
	Location = "";
	RiddleText = "";
	SecondsToNextStep = 0;
	RiddleHint = "";

}

Step::~Step()
{

}
