// StringInfo.h: interface for the CStringInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGINFO_H__7AB2DA60_A134_11D4_82B9_00105A19E3B9__INCLUDED_)
#define AFX_STRINGINFO_H__7AB2DA60_A134_11D4_82B9_00105A19E3B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringInfo  
{
public:
	int internal;
	void SetString(int nLang, CString Symbol = "", int ID = 0, CString * Strings = NULL);
	CString m_Strings[2];
	int m_ID;
	CString m_Symbol;
	CStringInfo();
	CStringInfo(int nLang, CString Symbol = "", int ID = 0, CString * Strings = NULL);
	virtual ~CStringInfo();

};

#endif // !defined(AFX_STRINGINFO_H__7AB2DA60_A134_11D4_82B9_00105A19E3B9__INCLUDED_)
