// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This class stores the data used for the Control Paramters and displays them in the Parameters Dialog
// ControlParameters.h: interface for the CControlParameters class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLPARAMETERS_H__50910840_B7B6_11D4_B01E_C8918D557734__INCLUDED_)
#define AFX_CONTROLPARAMETERS_H__50910840_B7B6_11D4_B01E_C8918D557734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CControlParameters  
{
public:
	int m_SMPFreq;
	BOOL m_24Hour;
	int m_LightOffTime;
	int m_LightOnTime;			// The time the Lights are on during a 24 hour period
	//int m_FanOnTime;				// The time the Fans are on during a 24 hour period
	void ReadObject(CArchive &ar);	// Retrieves from a file 
	void WriteObject(CArchive &ar);	// Writes to a file
	double m_MoistureLevel;			// The desired Moisture level
	//CTimeSpan m_CameraInterval;		// The period between digital photos
	CControlParameters();			// Constructor
	virtual ~CControlParameters();	// Destructor

};

#endif // !defined(AFX_CONTROLPARAMETERS_H__50910840_B7B6_11D4_B01E_C8918D557734__INCLUDED_)
