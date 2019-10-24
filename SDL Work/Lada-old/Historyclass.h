// This is Version 1.0 PLEASE DOCUMENT CHANGES
// HistoryClass.h: interface for the CHistoryClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISTORYCLASS_H__1166F626_8E0C_4B47_99F6_D104552ECDB6__INCLUDED_)
#define AFX_HISTORYCLASS_H__1166F626_8E0C_4B47_99F6_D104552ECDB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLADAControlModuleDoc;
class CViewHistoryDialog;

class CHistoryClass  
{
public:
	void UpdateLogWindow(CString line);
	CViewHistoryDialog ** m_ptrPtrViewDlg;
	CString * m_FileNames;
	CLADAControlModuleDoc * pDoc;
	BOOL m_AreFilesOpen;
	void CloseFiles();
	void OpenFiles();
	template <class DataType>
	void WriteData(BOOL newLine, DataType *Data, int nData);
	void WriteHistory(int sID1, int sID2, BOOL addNewLine = TRUE);
	void WriteHistory(char [], char [], BOOL addNewLine = TRUE);
	void WriteHistory(CString &category, CString &note, BOOL addNewLine = TRUE);
	int m_curFile;
	bool FindString(CString &category, CString &searchString);
	bool GetHistory(CString &category, CString searchString, CTime & info);
	bool GetHistory(CString &category, CString serachString, CString & info);
	bool GetHistory(CString &category, CString searchString, int & info);
	bool GetHistory(CString &category, CString serachString, double & info);
	CFile * m_ptrFiles;
	int m_nLanguages;
	
	CHistoryClass(CLADAControlModuleDoc *doc, int nLang = 1, CString * fileNames = NULL, CViewHistoryDialog **dlgPtr = NULL);
	virtual ~CHistoryClass();

};

#endif // !defined(AFX_HISTORYCLASS_H__1166F626_8E0C_4B47_99F6_D104552ECDB6__INCLUDED_)
