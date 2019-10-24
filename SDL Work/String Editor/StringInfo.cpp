// StringInfo.cpp: implementation of the CStringInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "String Editor.h"
#include "StringInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStringInfo::CStringInfo()
{
	m_Symbol = "";
	m_ID = 0; 
//	m_Strings = NULL;

}

CStringInfo::CStringInfo(int nLang, CString Symbol, int ID, CString * Strings)
{
	m_Symbol = Symbol;
	m_ID = ID;
//	m_Strings = new CString[nLang];
	if (Strings)
	{
		for (int i = 0; i < nLang; i++)
			m_Strings[i] = Strings[i];
	}
}

CStringInfo::~CStringInfo()
{
//	delete []m_Strings;
}

void CStringInfo::SetString(int nLang, CString Symbol, int ID, CString *Strings)
{
	m_Symbol = "";//Symbol;
	m_ID = ID;
//	if (m_Strings)
//		delete [] m_Strings;
//	m_Strings = new CString[nLang];
	if (Strings)
	{
		for (int i = 0; i < nLang; i++)
			m_Strings[i] = Strings[i];
	}
}
