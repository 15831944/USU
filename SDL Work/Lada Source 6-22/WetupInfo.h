// This is Version 1.0 PLEASE DOCUMENT CHANGES
// WetupInfo.h: interface for the CWetupInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WETUPINFO_H__30C4ACC2_B1E7_11D4_98EB_00A076801ACD__INCLUDED_)
#define AFX_WETUPINFO_H__30C4ACC2_B1E7_11D4_98EB_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef char InputListType[2][30];

class CGraphCollection;

class CWetupInfo  
{
public:
	BOOL * m_DoValidation;
	int nGraphCollections;
	InputListType * InputLocationNameList;
	int * InputLocationList;
	int nInputLocations;
	int m_VolumePumped;
	BOOL m_IsCR10Controlled;
	void WriteObject(CArchive &ar);
	void ReadObject(CArchive &ar);
	
	double m_mlPerSecond;
	int m_BurstFreq;
	double m_BurstVolume;
	int m_VolumeToPump;
	CGraphCollection * GraphCollection;
	int * PaneToCollectionIndex;
	CWetupInfo();
	virtual ~CWetupInfo();

};

#endif // !defined(AFX_WETUPINFO_H__30C4ACC2_B1E7_11D4_98EB_00A076801ACD__INCLUDED_)
