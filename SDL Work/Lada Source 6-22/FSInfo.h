// FSInfo.h: interface for the CFSInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FSINFO_H__7AC8A93E_F82A_4D14_AD40_E55FB6C1A10C__INCLUDED_)
#define AFX_FSINFO_H__7AC8A93E_F82A_4D14_AD40_E55FB6C1A10C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFSInfo  
{
public:
	int m_wFreqSel;
	int m_ArrayID;
	int m_nDataItems;
	int m_LastNumberRetrieved;
	int m_LastFailCode;
	void ReadObject(CArchive &ar);
	void WriteObject(CArchive &ar);
	const CFSInfo & operator=(const CFSInfo &right);
	CString * m_DataNames;
	CString m_ArchiveName;
	
	CFSInfo();
	virtual ~CFSInfo();

};

#endif // !defined(AFX_FSINFO_H__7AC8A93E_F82A_4D14_AD40_E55FB6C1A10C__INCLUDED_)
