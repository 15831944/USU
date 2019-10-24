// FSInfo.cpp: implementation of the CFSInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "FSInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFSInfo::CFSInfo()
{
	m_ArchiveName = "";
	m_ArrayID = 0;
	m_DataNames = NULL;
	m_nDataItems = 0;
	m_wFreqSel = 0;
	m_LastFailCode = 0;
	m_LastNumberRetrieved = 0;
}

CFSInfo::~CFSInfo()
{
	if (m_DataNames)
		delete [] m_DataNames;
	m_DataNames = NULL;
}

void CFSInfo::ReadObject(CArchive &ar)
{
	UINT iSize;
	iSize = sizeof(int);
	ar.Read(&m_ArrayID,iSize);
	ar.Read(&m_nDataItems, iSize);
	ar.Read(&m_wFreqSel, iSize);
	ar.Read(&m_LastFailCode, iSize);
	ar.Read(&m_LastNumberRetrieved, iSize);

	ar.ReadString(m_ArchiveName);

	m_DataNames = new CString[m_nDataItems];
	for (int i = 0; i < m_nDataItems; i++)
		ar.ReadString(m_DataNames[i]);
		
}

void CFSInfo::WriteObject(CArchive &ar)
{
	UINT iSize;
	iSize = sizeof(int);
	ar.Write(&m_ArrayID,iSize);
	ar.Write(&m_nDataItems, iSize);
	ar.Write(&m_wFreqSel, iSize);
	ar.Write(&m_LastFailCode, iSize);
	ar.Write(&m_LastNumberRetrieved, iSize);

	ar.WriteString(m_ArchiveName);
	ar.WriteString("\n");

	for (int i = 0; i < m_nDataItems; i++)
	{
		ar.WriteString(m_DataNames[i]);
		ar.WriteString("\n");
	}
}

const CFSInfo & CFSInfo::operator=(const CFSInfo &right)
{
	m_ArchiveName = right.m_ArchiveName;
	m_ArrayID = right.m_ArrayID;
	m_wFreqSel = right.m_wFreqSel;
	m_nDataItems = right.m_nDataItems;

	if (m_DataNames)
		delete [] m_DataNames;
	m_DataNames = new CString[m_nDataItems];

	for (int i = 0; i < m_nDataItems; i++)
		m_DataNames[i] = right.m_DataNames[i];
	return *this;
}
