// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to select certain input locations for graphs and files
#if !defined(AFX_CHOOSELOCATIONSDIALOG_H__B5A7CFCA_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_CHOOSELOCATIONSDIALOG_H__B5A7CFCA_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseLocationsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseLocationsDialog dialog

class CLADAControlModuleDoc;

typedef char InputListType[2][30];

class CChooseLocationsDlg : public CDialog
{
// Construction
public:
	int * ptrSelectedItems;
	void SetStrings();
	CChooseLocationsDlg(InputListType *iNames, int *iLocSaveList, int *nSaveList, int Available = MAX_INPUT_LOCATIONS, CWnd* pParent = NULL);
	CChooseLocationsDlg(CLADAControlModuleDoc * doc, CWnd* pParent = NULL);
	~CChooseLocationsDlg();
	enum DialogType {SaveMonitorDlg, DisplayLocationsDlg};
// Dialog Data
	//{{AFX_DATA(CChooseLocationsDlg)
	enum { IDD = MONITOR_DIALOG };
	CButton	m_Button9;
	CButton	m_Button8;
	CButton	m_Button5;
	CButton	m_Button3;
	CButton	m_Button2;
	CButton	m_Button4;
	CButton	m_Button7;
	CButton	m_Button6;
	CButton	m_Button1;
	CEdit	m_CNLocs;
	CComboBox	m_WhichGraph;
	CListBox	m_SLocations;
	CListBox	m_ALocations;
	int		m_nLocations;
	int		m_WhichGraphSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseLocationsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char (*InputLocNames)[2][30];
	int * SInputLocList;
	int * nILSaveList;
	DialogType dType;
	CLADAControlModuleDoc *pDoc;
	int cGraphSel;
	int MaxSelectedLocations;
	int AvailableStrings;
	
	void RenameLocation(int whichLocation);
	void ShowGraphChoices();
	//void SetFontText(UINT controlID, UINT stringID);
	// Generated message map functions
	//{{AFX_MSG(CChooseLocationsDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSortLocations();
	afx_msg void OnRenameLocation();
	afx_msg void OnRemove();
	afx_msg void OnInsert();
	afx_msg void OnFslFile();
	afx_msg void OnDblclkSLocations();
	afx_msg void OnDblclkALocations();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelectAlli();
	afx_msg void OnSelectAlls();
	afx_msg void OnSelchangeSLocations();
	afx_msg void OnSelchangeALocations();
	afx_msg void OnSelchangeWhichGraph();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSELOCATIONSDIALOG_H__B5A7CFCA_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
