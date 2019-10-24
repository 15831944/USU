// This is Version 1.0 PLEASE DOCUMENT CHANGES
// HistoryClass.cpp: implementation of the CHistoryClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lada control module.h"
#include "HistoryClass.h"
#include "LADA Control ModuleDoc.h"
#include "ViewHistoryDialog.h"
#include "LString.h"
#include "ViewHistoryDialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern LString Strings;
extern int curLanguage;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CHistoryClass::UpdateLogWindow(CString line)
{
	if (m_ptrPtrViewDlg && (*m_ptrPtrViewDlg))
	{
		(*m_ptrPtrViewDlg)->m_ListCtrl.AddString( line );
	}
}

CHistoryClass::CHistoryClass(CLADAControlModuleDoc *doc, 
							 int nLang, CString * fileNames, 
							 CViewHistoryDialog **dlgPtr)
{
	m_ptrPtrViewDlg = dlgPtr;
	pDoc = doc;
	m_nLanguages = nLang;
	m_ptrFiles = new CFile[m_nLanguages];
	m_AreFilesOpen = FALSE;
	m_curFile = 0;
	m_FileNames = new CString[m_nLanguages];
	for (int i = 0; i < m_nLanguages; i++)
		m_FileNames[i] = fileNames[i];
}

CHistoryClass::~CHistoryClass()
{
	if (m_AreFilesOpen)
		CloseFiles();
	delete [] m_FileNames;
	m_FileNames = NULL;
	delete [] m_ptrFiles;
	m_ptrFiles = NULL;
}

bool CHistoryClass::GetHistory(CString &category, CString searchString, int &info)
{
	if (FindString(category,searchString))
	{
		// find the colon in the string, then return the data after the colon...
		return true;
	}
	return false;
}

bool CHistoryClass::GetHistory(CString &category, CString searchString, double &info)
{
	if (FindString(category,searchString))
	{
		// find the colon in the string, then return the data after the colon...
		return true;
	}
	return false;
}

bool CHistoryClass::GetHistory(CString &category, CString searchString, CTime &info)
{
	if (FindString(category,searchString))
	{
		// find the colon in the string, then return the data after the colon...
		return true;
	}
	return false;
}

bool CHistoryClass::GetHistory(CString &category, CString searchString, CString &info)
{
	if (FindString(category,searchString))
	{
		// find the colon in the string, then return the data after the colon...
		return true;
	}
	return false;
}

bool CHistoryClass::FindString(CString &category, CString &searchString)
{
	CString textLine;
	CString midString;
	//searchString += ":";

	CArchive fArchive( &m_ptrFiles[m_curFile], CArchive::load );

	while (fArchive.ReadString(textLine))
	{
		textLine = textLine.Mid(22);
		if (textLine[0] == '\t')
			continue;
		
		if ( textLine.Find((LPCTSTR) searchString ))
		{
			searchString = textLine;
			fArchive.Close();
			return true;
		}
	}
	fArchive.Close();
	return false;
}

void CHistoryClass::WriteHistory(int sID1, int sID2, BOOL addNewLine)
{
	if (m_AreFilesOpen)
	{
		CTime currentTime = CTime::GetCurrentTime();
		CString timeStamp = currentTime.Format("%m/%d/%Y  %H:%M:%S  ");
		int prevCurLanguage = curLanguage;
		for (int curLanguage = 0; curLanguage < m_nLanguages; curLanguage++)
		{
			m_ptrFiles[curLanguage].SeekToEnd();
			CArchive fArchive( &m_ptrFiles[curLanguage], CArchive::store );
			CString line = timeStamp + Strings.get(sID1) + CString("- ") + Strings.get(sID2);
			fArchive.WriteString( line );
			if (addNewLine)
				fArchive.WriteString( "\r\n" );
			if ( prevCurLanguage == curLanguage )
				UpdateLogWindow( line );
		}
		curLanguage = prevCurLanguage;
	}
	else
		MessageBox(NULL,"WriteHistory called when m_AreFilesOpen == FALSE","Program Error",MB_ICONWARNING);
		
}

void CHistoryClass::WriteHistory(char s1[], char s2[], BOOL addNewLine)
{
	WriteHistory(CString(s1), CString(s2), addNewLine);
}

void CHistoryClass::WriteHistory(CString &category, CString &note, BOOL addNewLine)
{
	if (m_AreFilesOpen)
	{
		CTime currentTime = CTime::GetCurrentTime();
		CString timeStamp = currentTime.Format("%m/%d/%Y  %H:%M:%S  ");
		int prevCurLanguage = curLanguage;
		for (int curLanguage = 0; curLanguage < m_nLanguages; curLanguage++)
		{
			m_ptrFiles[curLanguage].SeekToEnd();
			CArchive fArchive( &m_ptrFiles[curLanguage], CArchive::store );
			CString line = timeStamp + category + CString("- ") + note;
			fArchive.WriteString( line );
			if (addNewLine)
				fArchive.WriteString( "\r\n" );
			if ( prevCurLanguage == curLanguage )
				UpdateLogWindow( line );
		}
		curLanguage = prevCurLanguage;
	}
	else
		MessageBox(NULL,"WriteHistory called when m_AreFilesOpen == FALSE","Program Error",MB_ICONWARNING);

}

template <class DataType>
void CHistoryClass::WriteData(BOOL newLine, DataType *Data, int nData)
{

}

void CHistoryClass::OpenFiles()
{
	CString fName;
	if (!m_AreFilesOpen)
	{
		for (int i = 0; i < m_nLanguages; i++){
			m_ptrFiles[i].Open(pDoc->dataFolder + "\\" + m_FileNames[i], CFile::modeNoTruncate|CFile::modeReadWrite);
			//UINT ihv = INVALID_HANDLE_VALUE;
			if (m_ptrFiles[i].m_hFile == (UINT)INVALID_HANDLE_VALUE)
			{
				if (!m_ptrFiles[i].Open(pDoc->dataFolder + "\\" + m_FileNames[i],CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite))
				{
					MessageBox(NULL,"History file could not be created.","Error",MB_ICONWARNING);
				}
			}	
		}
		m_AreFilesOpen = TRUE;
	}
	else
		MessageBox(NULL,"OpenFiles() called when m_AreFilesOpen == TRUE","Program Error",MB_ICONWARNING);

	
}

void CHistoryClass::CloseFiles()
{
	if (m_AreFilesOpen)
	{
		for (int i = 0; i < m_nLanguages; i++)
			m_ptrFiles[i].Close();
		m_AreFilesOpen = FALSE;
	}
	else
		MessageBox(NULL,"OpenFiles() called when m_AreFilesOpen == FALSE","Program Error",MB_ICONWARNING);

}