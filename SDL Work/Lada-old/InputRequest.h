// This is Version 1.0 PLEASE DOCUMENT CHANGES
// InputRequest.h: interface for the CInputRequest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTREQUEST_H__5D71A380_ACDF_11D4_B01E_994A14DE542A__INCLUDED_)
#define AFX_INPUTREQUEST_H__5D71A380_ACDF_11D4_B01E_994A14DE542A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum RequestType {GraphRequest,CollectRequest,WriteRequest,FinalStorageRequest,UpdateTimeRequest};

class CInputRequest  
{
public:
	bool operator ==(const CInputRequest &right) const;
	CInputRequest(RequestType rT = GraphRequest, int wG = 0);
	virtual ~CInputRequest();
	
	RequestType Request;
	int whichGroup;
};

#endif // !defined(AFX_INPUTREQUEST_H__5D71A380_ACDF_11D4_B01E_994A14DE542A__INCLUDED_)
