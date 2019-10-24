// This is Version 1.0 PLEASE DOCUMENT CHANGES
// InputLocFileInfo.h: interface for the CInputLocFileInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTLOCFILEINFO_H__4BC5FEA3_A221_11D4_98E9_00A076801ACD__INCLUDED_)
#define AFX_INPUTLOCFILEINFO_H__4BC5FEA3_A221_11D4_98E9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInputLocFileInfo  
{
public:
	CTime m_LastAttemptedCollectionTime;
	CTime m_NextCollectionTime;
	int m_nSuccessfulCollections;
	int m_nAttemptedCollections;
	
	void ReadObject(CArchive & ar);
	void WriteObject(CArchive & ar);
	CInputLocFileInfo & operator=(const CInputLocFileInfo & right);
	void SetListInfo(int nLocations = 0, int *Locations = NULL);
	void SetOperatingInfo( CTimeSpan retrFreq = CTimeSpan(0,0,1,0), BOOL ByAverage = TRUE,
					  CTimeSpan writeFreq = CTimeSpan(0,0,15,0), 
					  CTimeSpan newFileFreq = CTimeSpan(1,0,0,0),
					  CTime LastReadTime = 0,
					  CTime LastSaveTime = 0,//CTime::GetCurrentTime(), 
					  CTime LastCreateTime = 0,//CTime::GetCurrentTime(),
					  CString name = "");

	CInputLocFileInfo(int nLocations = 0, int *Locations = NULL,
					  CTimeSpan retrFreq = CTimeSpan(0,0,1,0), BOOL ByAverage = TRUE,
					  CTimeSpan writeFreq = CTimeSpan(0,0,15,0), 
					  CTimeSpan newFileFreq = CTimeSpan(1,0,0,0),
					  CTime LastReadTime = 0,
					  CTime LastSaveTime = 0,//CTime::GetCurrentTime(), 
					  CTime LastCreateTime = 0,//CTime::GetCurrentTime(),
					  CString name = "");

	virtual ~CInputLocFileInfo();
	
	BOOL m_Do;
	BOOL m_SaveByAverage;
	int * m_Locations;
	int m_nLocations;
	int m_nItemsInTempData;// don't save
	double * m_tempData;// don't save
	//HANDLE m_ILFileOut;     // don't save
	CTime m_LastSaveTime;// the last time data was written to this file 
	CTime m_LastCreateTime;// when this file was created
	CTime m_LastReadTime;// the last time data was read
	CTimeSpan m_NewFileFreq;// how often a file should be created
	CTimeSpan m_WriteDataFreq;// how often data should be written
	CTimeSpan m_RetrFreq;// how often data should be collected
	CString m_Name;// the name of the input location group
	DWORD m_TimerIDRetrieve;
	DWORD m_TimerID;
	CString m_FileName;	// the path and file name
	
};

#endif // !defined(AFX_INPUTLOCFILEINFO_H__4BC5FEA3_A221_11D4_98E9_00A076801ACD__INCLUDED_)
