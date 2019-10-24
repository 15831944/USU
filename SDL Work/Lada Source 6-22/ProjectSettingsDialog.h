// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_PROJECTSETTINGSDIALOG_H__B5A7CFC9_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_PROJECTSETTINGSDIALOG_H__B5A7CFC9_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProjectSettingsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProjectSettingsDialog dialog

class CLADAControlModuleDoc;
class CInputLocFileInfo;
class CILFileDisplayInfo;

typedef char InputListType[2][30];

class CProjectSettingsDlg : public CDialog
{
// Construction
public:
	void Reset();
	void ShowAverageInstant();
	CILFileDisplayInfo * m_ILDisplayInfo;
	InputListType InputLocationNameList[MAX_INPUT_LOCATIONS];
	int InputLocationList [MAX_INPUT_LOCATIONS];

	BOOL m_DlgInitialized;
	CInputLocFileInfo * m_ptrILFileInfo;
	CInputLocFileInfo * m_ILFileInfo;
	CProjectSettingsDlg(CLADAControlModuleDoc *doc, CWnd* pParent = NULL);   // standard constructor
	~CProjectSettingsDlg();
// Dialog Data
	//{{AFX_DATA(CProjectSettingsDlg)
	enum { IDD = IDD_NEW_PROJECT };
	CComboBox	m_CSaveFSFreq;
	CComboBox	m_NewILFileFreq;
	CEdit	m_cNIL;
	CButton	m_cILList;
	CEdit	m_cILGroupName;
	CSpinButtonCtrl	m_Spin1;
	CEdit	m_cnILFiles;
	CEdit	m_cwILFile;
	CComboBox	m_nGraphs;
	CButton	m_Instant;
	CButton	m_Average;
	CComboBox	m_CSaveDataFreq;
	CComboBox	m_CNBackPoints;
	CListBox	m_CLocationList;
	CComboBox	m_CGraphPlotFreq;
	CComboBox	m_CDataRetrievalFreq;
	CString	m_DataFolder;
	BOOL	m_SaveFinalStorage;
	CString	m_ProjectName;
	CString	m_VisibleSpan;
	int		m_curBackPointsSel;
	int		m_curDataRetrievalSel;
	int		m_curDataSaveSel;
	int		m_curPlotFreqSel;
	BOOL	m_SaveLocations;
	int		m_nGraphsSel;
	CString	m_FSGroupName;
	CString	m_ILGroupName;
	int		m_curFSCreateFreq;
	int		m_curILCreateFreq;
	int		m_nFS;
	int		m_nIL;
	int		m_nILFiles;
	int		m_wILFile;
	BOOL	m_DoWetup;
	CString	m_FileHeader;
	//}}AFX_DATA

	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProjectSettingsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CLADAControlModuleDoc *doc;
	void ShowVisibleSpan();
		
	BOOL m_ByAverage;
	// Generated message map functions
	//{{AFX_MSG(CProjectSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseDataFolder();
	afx_msg void OnEditLocationList();
	afx_msg void OnSelchangeGraphPlotFreq();
	afx_msg void OnSelchangeNBackPoints();
	afx_msg void OnAverage();
	afx_msg void OnOneInstant();
	virtual void OnOK();
	afx_msg void OnSaveLocations();
	afx_msg void OnChangeWilfile();
	afx_msg void OnChangeNilfiles();
	afx_msg void OnSaveFinalStorage();
	afx_msg void OnChooseFslList();
	afx_msg void OnChooseIllList();
	afx_msg void OnAssociatefsl();
	afx_msg void OnWsettings();
	afx_msg void OnDowetup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTSETTINGSDIALOG_H__B5A7CFC9_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
