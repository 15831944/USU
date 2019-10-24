// Square.cpp: implementation of the Square class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Baby Steps.h"
#include "Square.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Square::Square()
{
	type = Normal;
	top = -1;
	left = -1;
	bottom = -1;
	right = -1;
}

Square::~Square()
{

}

void Square::SetType(SquareType newType)
{
	type = newType;
}
