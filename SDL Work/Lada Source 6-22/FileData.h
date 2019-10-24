// This is Version 1.0 PLEASE DOCUMENT CHANGES
// FileData.h: interface for the CFileData class.
//
//////////////////////////////////////////////////////////////////////
//This Class stores the data in an array for Camera file information
#if !defined(AFX_FILEDATA_H__EFEA7583_7446_11D4_98DA_00A076801ACD__INCLUDED_)
#define AFX_FILEDATA_H__EFEA7583_7446_11D4_98DA_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileData  
{
	friend CArchive& operator >>( CArchive& ar,  CFileData& right  );//output from a file
	friend CArchive& operator <<( CArchive& ar,  CFileData& right  );//input to a file
public:
	char* FileName;		// The name of the saved file
	CTime m_RealTime;	// Stores the time the be cut up
	CFileData();		// Basic Constructor
	virtual ~CFileData();// Destructor
	CString m_Date;		// Stores the Date
	CString m_Time;		// Stores the Time
	CString m_Camera;	// Stores which camera was used
	CString m_Size;		// Stores the size of the file
};







#endif // !defined(AFX_FILEDATA_H__EFEA7583_7446_11D4_98DA_00A076801ACD__INCLUDED_)
