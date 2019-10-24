// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This class stores the data used for the Control Paramters and displays them in the Parameters Dialog
// ControlParameters.cpp: implementation of the CControlParameters class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "ControlParameters.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Constructor
CControlParameters::CControlParameters()
{
	//m_CameraInterval = CTimeSpan(0,24,0,0);	
	//m_FanOnTime = 0;
	m_LightOnTime = 0;
	m_LightOffTime = 12;
	m_MaxDosage = 20;
	m_MoistureLevel = 50.0;
	m_24Hour = FALSE;
	m_SMPFreq = 0;
}

// Destructor
CControlParameters::~CControlParameters()
{

}

// Writes to a file
void CControlParameters::WriteObject(CArchive &ar)
{
	ar.Write( &m_MoistureLevel, sizeof(double) );
	//ar.Write( &m_FanOnTime, sizeof(double) );	
	ar.Write( &m_LightOnTime, sizeof(int) );	
	ar.Write( &m_LightOffTime, sizeof(int) );
	ar.Write( &m_SMPFreq, sizeof(int) );
	ar.Write( &m_24Hour, sizeof(BOOL) );
	ar.Write( &m_MaxDosage, sizeof(int) );
}

// Retrieves from a file
void CControlParameters::ReadObject(CArchive &ar)
{
	ar.Read( &m_MoistureLevel, sizeof(double) );
	//ar.Read( &m_FanOnTime, sizeof(double) );	
	ar.Read( &m_LightOnTime, sizeof(int) );	
	ar.Read( &m_LightOffTime, sizeof(int) );
	ar.Read( &m_SMPFreq, sizeof(int) );
	ar.Read( &m_24Hour, sizeof(BOOL) );
	ar.Read( &m_MaxDosage, sizeof(int) );
}
