// This is Version 1.0 PLEASE DOCUMENT CHANGES
// InputLocFileInfo.cpp: implementation of the CInputLocFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "InputLocFileInfo.h"
//#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInputLocFileInfo::CInputLocFileInfo(int nLocations, int *Locations,
					  CTimeSpan retrFreq, BOOL ByAverage,
					  CTimeSpan writeFreq, 
					  CTimeSpan newFileFreq,
					  CTime LastReadTime,
					  CTime LastSaveTime, 
					  CTime LastCreateTime,
					  CString Name)
{
	if (nLocations)
	{
		if (nLocations != m_nLocations){
			if (m_tempData)
				delete [] m_tempData;
			if (m_Locations)
				delete [] m_Locations;
			m_tempData = new double[nLocations];
			m_Locations = new int[nLocations];
			memset(m_tempData, 0, sizeof(double) * m_nLocations);
		}
		if (Locations){
			for (int i = 0; i < nLocations; i++)
				m_Locations[i] = Locations[i];
		}
	}
	else
	{
		m_tempData = NULL;
		m_Locations = NULL;
	}
	m_nLocations = nLocations;

	m_Name = Name;
	
	m_RetrFreq = retrFreq; // 0 days 0 hours 1 minute 0 seconds
	m_WriteDataFreq = writeFreq;
	m_NewFileFreq = newFileFreq;
	m_SaveByAverage = ByAverage;
	//m_ILFileOut = NULL;
	m_LastReadTime = LastReadTime;
	m_LastSaveTime = LastSaveTime;
	m_LastCreateTime = LastCreateTime;
	m_NextCollectionTime = time_t(0);
	m_LastAttemptedCollectionTime = time_t(0);
	m_nItemsInTempData = 0;
	m_TimerID = 0;
	m_nAttemptedCollections = 0;
	m_nSuccessfulCollections = 0;
	m_Do = TRUE;

}

CInputLocFileInfo::~CInputLocFileInfo()
{
	if (m_tempData)
		delete [] m_tempData;
	if (m_Locations)
		delete [] m_Locations;
}

void CInputLocFileInfo::SetListInfo(int nLocations, int *Locations)
{
	if (nLocations)
	{
		if (nLocations != m_nLocations){
			if (m_tempData)
				delete [] m_tempData;
			if (m_Locations)
				delete [] m_Locations;
			m_tempData = new double[nLocations];
			m_Locations = new int[nLocations];
		}
		if (Locations)
			memcpy(m_Locations, Locations, sizeof(int) * nLocations);
		
	}
	else
	{
		m_tempData = NULL;
		m_Locations = NULL;
	}
	m_nLocations = nLocations;
	memset(m_tempData, 0, sizeof(double) * m_nLocations);
	m_nItemsInTempData = 0;
}

void CInputLocFileInfo::SetOperatingInfo(CTimeSpan retrFreq, BOOL ByAverage,
					  CTimeSpan writeFreq, 
					  CTimeSpan newFileFreq,
					  CTime LastReadTime,
					  CTime LastSaveTime, 
					  CTime LastCreateTime,
					  CString Name)
{
	m_Name = Name;
	
	m_RetrFreq = retrFreq; 
	m_WriteDataFreq = writeFreq;
	m_NewFileFreq = newFileFreq;
	m_SaveByAverage = ByAverage;
	//m_ILFileOut = NULL;
	m_LastReadTime = LastReadTime,
	m_LastSaveTime = LastSaveTime;
	m_LastCreateTime = LastCreateTime;
	m_nItemsInTempData = 0;
	
}

CInputLocFileInfo & CInputLocFileInfo::operator=(const CInputLocFileInfo & right)
{
	// assignment operator
	m_nLocations = right.m_nLocations;
	//m_ILFileOut = right.m_ILFileOut;
	m_LastReadTime = right.m_LastReadTime;
	m_LastCreateTime = right.m_LastCreateTime;
	m_LastSaveTime = right.m_LastSaveTime;
	m_NextCollectionTime = right.m_NextCollectionTime;
	m_LastAttemptedCollectionTime = right.m_LastAttemptedCollectionTime;
	if (m_Locations)
		delete [] m_Locations;
	m_Locations = new int[m_nLocations];
	memcpy(m_Locations,right.m_Locations, sizeof(int) * m_nLocations);
	m_Name = right.m_Name;
	m_NewFileFreq = right.m_NewFileFreq;
	m_RetrFreq = right.m_RetrFreq;
	m_SaveByAverage = right.m_SaveByAverage;
	if (m_tempData)
		delete [] m_tempData;
	m_tempData = new double[m_nLocations];
	memcpy(m_tempData, right.m_tempData, sizeof(double) * m_nLocations);
	m_nItemsInTempData = right.m_nItemsInTempData;
	m_WriteDataFreq = right.m_WriteDataFreq;
	m_Do = right.m_Do;
	m_TimerID = right.m_TimerID;
	m_nAttemptedCollections = right.m_nAttemptedCollections;
	m_nSuccessfulCollections = right.m_nSuccessfulCollections;
	
	/*
	if (m_HasMinMax)
	{
		if (m_Min)
			delete [] m_Min;
		if (m_Max)
			delete [] m_Max;
		m_Min = new double[m_nLocations];
		m_Max = new double[m_nLocations];
		memcpy(m_Min,right.m_Min, sizeof(double) * m_nLocations);
		memcpy(m_Max,right.m_Max, sizeof(double) * m_nLocations);
	}
	*/
	return *this;
}

void CInputLocFileInfo::WriteObject(CArchive &ar)
{
	UINT iSize;
	iSize = sizeof(BOOL);
	ar.Write(&m_Do,iSize);
	ar.Write(&m_SaveByAverage,iSize);
	
	iSize = sizeof(int);
	ar.Write(&m_nLocations,iSize);
	ar.Write(&m_nAttemptedCollections,iSize);
	ar.Write(&m_nSuccessfulCollections,iSize);
	iSize = m_nLocations * sizeof(int);
	ar.Write(m_Locations, iSize);
	iSize = sizeof(CTime);
	ar.Write(&m_LastReadTime,iSize);
	ar.Write(&m_LastSaveTime,iSize);
	ar.Write(&m_LastCreateTime,iSize);
	ar.Write(&m_LastAttemptedCollectionTime,iSize);
	iSize = sizeof(CTimeSpan);
	ar.Write(&m_NewFileFreq,iSize);
	ar.Write(&m_WriteDataFreq,iSize);
	ar.Write(&m_RetrFreq,iSize);
	ar.WriteString(m_Name);
	ar.WriteString("\n");
	ar.WriteString(m_FileName);
	ar.WriteString("\n");
	
}

void CInputLocFileInfo::ReadObject(CArchive &ar)
{
	UINT iSize;
	iSize = sizeof(BOOL);
	ar.Read(&m_Do,iSize);
	ar.Read(&m_SaveByAverage,iSize);
	iSize = sizeof(int);
	ar.Read(&m_nLocations,iSize);
	ar.Read(&m_nAttemptedCollections,iSize);
	ar.Read(&m_nSuccessfulCollections,iSize);
	iSize = m_nLocations * sizeof(int);
	m_Locations = new int[m_nLocations];
	ar.Read(m_Locations, iSize);
	iSize = sizeof(CTime);
	ar.Read(&m_LastReadTime,iSize);
	ar.Read(&m_LastSaveTime,iSize);
	ar.Read(&m_LastCreateTime,iSize);
	ar.Read(&m_LastAttemptedCollectionTime,iSize);
	iSize = sizeof(CTimeSpan);
	ar.Read(&m_NewFileFreq,iSize);
	ar.Read(&m_WriteDataFreq,iSize);
	ar.Read(&m_RetrFreq,iSize);
	ar.ReadString(m_Name);
	ar.ReadString(m_FileName);

	m_nItemsInTempData = 0; // don't save
	m_TimerID = 0;
	m_tempData = new double[m_nLocations];    // don't save
	//m_ILFileOut = NULL;     // don't save

}
