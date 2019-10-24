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

class CProjectSettingsDlg : public CDialog
{
// Construction
public:
	CProjectSettingsDlg(CLADAControlModuleDoc *doc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProjectSettingsDlg)
	enum { IDD = IDD_NEW_PROJECT };
	CStatic	m_SaveLocText;
	CComboBox	m_nGraphs;
	CButton	m_Time;
	CButton	m_Size;
	CButton	m_Instant;
	CButton	m_Average;
	CComboBox	m_CSizeTime;
	CComboBox	m_CSaveDataFreq;
	CComboBox	m_CNBackPoints;
	CListBox	m_CLocationList;
	CComboBox	m_CGraphPlotFreq;
	CComboBox	m_CDataRetrievalFreq;
	CString	m_DataFolder;
	BOOL	m_SaveFinalStorage;
	CString	m_SaveProjectFileName;
	CString	m_VisibleSpan;
	int		m_curBackPointsSel;
	int		m_curDataRetrievalSel;
	int		m_curDataSaveSel;
	int		m_curPlotFreqSel;
	int		m_curSizeTimeSel;
	BOOL	m_SaveLocations;
	int		m_nGraphsSel;
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
	BOOL m_ByTime;
	// Generated message map functions
	//{{AFX_MSG(CProjectSettingsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseDataFolder();
	afx_msg void OnBySize();
	afx_msg void OnByTime();
	afx_msg void OnEditLocationList();
	afx_msg void OnSelchangeGraphPlotFreq();
	afx_msg void OnSelchangeNBackPoints();
	afx_msg void OnAverage();
	afx_msg void OnOneInstant();
	virtual void OnOK();
	afx_msg void OnSaveLocations();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROJECTSETTINGSDIALOG_H__B5A7CFC9_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
