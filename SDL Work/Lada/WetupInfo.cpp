// This is Version 1.0 PLEASE DOCUMENT CHANGES
// WetupInfo.cpp: implementation of the CWetupInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "WetupInfo.h"
#include "GraphCollection.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWetupInfo::CWetupInfo()
{
	m_BurstFreq = 10;// burst every ten minutes
	m_VolumePumped = 0;
	m_VolumeToPump = 1000;
	m_BurstVolume = 10.0; // 10 mililiters every burst
	m_mlPerSecond = 50.0 / 190.0; // last time I checked, it took 190 sec to pump 50 ml

	m_DoValidation = NULL;
	m_IsCR10Controlled = TRUE;
	nInputLocations = 0;
	InputLocationNameList = NULL;
	InputLocationList = NULL;
	nGraphCollections = 3;
	GraphCollection = new CGraphCollection[3];
	PaneToCollectionIndex = new int[3];
	for (int i = 0; i < 3; i++)
		PaneToCollectionIndex[i] = -1;
	
}

CWetupInfo::~CWetupInfo()
{
	
	delete [] GraphCollection;
	delete [] InputLocationNameList;
	delete [] InputLocationList;
	delete [] PaneToCollectionIndex;
	delete [] m_DoValidation;

	InputLocationNameList = NULL;
	InputLocationList = NULL;
	PaneToCollectionIndex = NULL;
}

void CWetupInfo::WriteObject(CArchive &ar)
{

	UINT iSize;
	iSize = sizeof(int);
	ar.Write(&nGraphCollections,iSize);
	ar.Write(&m_BurstFreq,iSize);
	ar.Write(&m_VolumeToPump,iSize);
	ar.Write(&m_VolumePumped,iSize);

	ar.Write(&nInputLocations,iSize);
	iSize = sizeof(BOOL);
	ar.Write(&m_IsCR10Controlled,iSize);
	iSize = sizeof(double);
	ar.Write(&m_mlPerSecond,iSize);
	ar.Write(&m_BurstVolume,iSize);
	iSize = sizeof(CTimeSpan);

	for (int i = 0; i < nGraphCollections; i++)
		GraphCollection[i].WriteObject(ar);

	if (nInputLocations)
	{
		ar.Write( InputLocationList, sizeof(int)*nInputLocations);
		ar.Write( InputLocationNameList, sizeof(InputListType) * nInputLocations);
	}

	ar.Write( PaneToCollectionIndex, sizeof(int) * 3);
}

void CWetupInfo::ReadObject(CArchive &ar)
{
	UINT iSize;
	iSize = sizeof(int);
	ar.Read(&nGraphCollections,iSize);
	ar.Read(&m_BurstFreq,iSize);
	ar.Read(&m_VolumeToPump,iSize);
	ar.Read(&m_VolumePumped,iSize);

	ar.Read(&nInputLocations,iSize);
	iSize = sizeof(BOOL);
	ar.Read(&m_IsCR10Controlled,iSize);
	iSize = sizeof(double);
	ar.Read(&m_mlPerSecond,iSize);
	ar.Read(&m_BurstVolume,iSize);
	iSize = sizeof(CTimeSpan);
	
	delete [] GraphCollection;
	GraphCollection = new CGraphCollection[nGraphCollections];
	for (int i = 0; i < nGraphCollections; i++)
		GraphCollection[i].ReadObject(ar);

	if (nInputLocations)
	{
		InputLocationList = new int[nInputLocations];
		InputLocationNameList = new InputListType[nInputLocations];

		ar.Read( InputLocationList, sizeof(int)*nInputLocations);
		ar.Read( InputLocationNameList, sizeof(InputListType) * nInputLocations);
	}

	delete [] PaneToCollectionIndex;
	PaneToCollectionIndex = new int[3];
	ar.Read( PaneToCollectionIndex, sizeof(int) * 3);

	m_DoValidation = new BOOL[nInputLocations];
	memset(m_DoValidation,0,sizeof(BOOL)*nInputLocations);
}