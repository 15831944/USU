// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_NEWPROJECT2_H__2F409E31_D04A_11D4_98FC_00A076801ACD__INCLUDED_)
#define AFX_NEWPROJECT2_H__2F409E31_D04A_11D4_98FC_00A076801ACD__INCLUDED_

#include "FSInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProject2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewProject2 dialog
class CLADAControlModuleDoc;
class CInputLocFileInfo;
class CILFileDisplayInfo;

typedef char InputListType[2][30];

class CNewProject2 : public CDialog
{
// Construction
public:
	void ShowFSDataNames();
	CFSInfo * m_ptrFSFileInfo;
	CFSInfo m_FSOutputTable[2];
	void SetStrings(BOOL updateData = TRUE);
	BOOL GetParameters();
	CNewProject2(CLADAControlModuleDoc * pDoc, CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewProject2();

	BOOL m_DlgInitialized;
	BOOL m_ByAverage;
	CInputLocFileInfo * m_ptrILFileInfo;
	CLADAControlModuleDoc * doc;
	CILFileDisplayInfo * m_ILDisplayInfo;
	CInputLocFileInfo * m_ILFileInfo;
	
	void ShowAverageInstant();

// Dialog Data
	//{{AFX_DATA(CNewProject2)
	enum { IDD = IDD_NEW_PROJECT2 };
	CEdit	m_cnFSFiles;
	CSpinButtonCtrl	m_Spin2;
	CComboBox	m_cFSFrequency;
	CEdit	m_cwFSFile;
	CEdit	m_cwILFile;
	CSpinButtonCtrl	m_Spin1;
	CComboBox	m_CSaveDataFreq;
	CButton	m_Instant;
	CEdit	m_cnILFiles;
	CEdit	m_cNIL;
	CComboBox	m_NewILFileFreq;
	CComboBox	m_CSaveFSFreq;
	CEdit	m_cILGroupName;
	CComboBox	m_CDataRetrievalFreq;
	CButton	m_cILList;
	CButton	m_Average;
	CString	m_DataFolder;
	int		m_curDataRetrievalSel;
	CString	m_FSGroupName;
	CString	m_ILGroupName;
	int		m_curFSCreateFreq;
	int		m_curILCreateFreq;
	int		m_nFS;
	int		m_nIL;
	int		m_nILFiles;
	int		m_curDataSaveSel;
	BOOL	m_SaveFinalStorage;
	BOOL	m_SaveLocations;
	int		m_wILFile;
	int		m_ArrayID;
	int		m_wFSFile;
	int		m_wFSFreq;
	int		m_nFSFiles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProject2)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProject2)
	afx_msg void OnFinish();
	afx_msg void OnOneInstant();
	afx_msg void OnSaveFinalStorage();
	afx_msg void OnSaveLocations();
	afx_msg void OnAssociatefsl();
	afx_msg void OnAverage();
	afx_msg void OnBrowseDataFolder();
	afx_msg void OnChangeNilfiles();
	afx_msg void OnChangeWilfile();
	afx_msg void OnChooseIllList();
	virtual BOOL OnInitDialog();
	afx_msg void OnBack();
	afx_msg void OnChangeWfsfile();
	afx_msg void OnChangeNFsfiles();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECT2_H__2F409E31_D04A_11D4_98FC_00A076801ACD__INCLUDED_)
