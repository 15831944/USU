// This is Version 1.0 PLEASE DOCUMENT CHANGES
// InputRequest.cpp: implementation of the CInputRequest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InputRequest.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInputRequest::CInputRequest(RequestType rT, int wG) // = 0
{
	Request = rT;
	whichGroup = wG;
}

CInputRequest::~CInputRequest()
{

}

bool CInputRequest::operator ==(const CInputRequest &right) const
{
	return (Request == right.Request && whichGroup == right.whichGroup);
}
