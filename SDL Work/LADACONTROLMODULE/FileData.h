// FileData.h: interface for the CFileData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDATA_H__EFEA7583_7446_11D4_98DA_00A076801ACD__INCLUDED_)
#define AFX_FILEDATA_H__EFEA7583_7446_11D4_98DA_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileData  
{
	friend CArchive& operator >>( CArchive& ar,  CFileData& right  );
	friend CArchive& operator <<( CArchive& ar,  CFileData& right  );
public:
	char* FileName;
	CTime m_RealTime;
	CFileData();
	virtual ~CFileData();
	CString m_Date;
	CString m_Time;
	CString m_Camera;
	CString m_Size;
};







#endif // !defined(AFX_FILEDATA_H__EFEA7583_7446_11D4_98DA_00A076801ACD__INCLUDED_)
