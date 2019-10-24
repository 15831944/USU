// FileData.cpp: implementation of the CFileData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cameradialog.h"
#include "FileData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileData::CFileData()
{

}

CFileData::~CFileData()
{

}
CArchive& operator >>( CArchive& ar,  CFileData& right  )
{ 
	ar >> right.m_Date >> right.m_Time >> right.m_Camera >> right.m_Size;
	return ar;
		
}

CArchive& operator <<( CArchive& ar,  CFileData& right  )
{ 
	ar << right.m_Date << right.m_Time << right.m_Camera << right.m_Size;
	return ar;
		
}


