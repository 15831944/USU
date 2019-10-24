// This is Version 1.0 PLEASE DOCUMENT CHANGES
// FileData.cpp: implementation of the CFileData class.
//
//////////////////////////////////////////////////////////////////////
//This Class stores the data in an array for Camera file information
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

//Standard Constructor
CFileData::CFileData()
{

}

// Standard Destructor
CFileData::~CFileData()
{

}

//Reads the data from a file
CArchive& operator >>( CArchive& ar,  CFileData& right  )
{ 
	ar >> right.m_Date >> right.m_Time >> right.m_Camera >> right.m_Size;
	return ar;
		
}

//Writes the data to a file
CArchive& operator <<( CArchive& ar,  CFileData& right  )
{ 
	ar << right.m_Date << right.m_Time << right.m_Camera << right.m_Size;
	return ar;
		
}


