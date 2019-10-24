// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_GRAPHPROPERTIES_H__A8875C00_79E2_11D4_B01E_E4BEFADC062A__INCLUDED_)
#define AFX_GRAPHPROPERTIES_H__A8875C00_79E2_11D4_B01E_E4BEFADC062A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphProperties.h : header file
//
class CLADAControlModuleDoc;
class CGraphCollection;
/////////////////////////////////////////////////////////////////////////////
// CGraphProperties dialog

class CGraphProperties : public CDialog
{
// Construction
public:
	void EnableGraphs(BOOL enable);
	CGraphCollection * ptrCurrentGraph;
	int m_InitialNPoints;
	int m_InitialGraphFreqSel;
	void SetStrings(BOOL Update = TRUE);
	CGraphProperties(CLADAControlModuleDoc *pDoc, CWnd* pParent = NULL);   // standard constructor
	void ShowVisibleSpan();
	void SetStatus(int whichItem);
	void GetCheckedItems();
	
// Dialog Data
	//{{AFX_DATA(CGraphProperties)
	enum { IDD = IDD_GRAPH_PROPERTIES };
	CComboBox	m_cShowGraph;
	CStatic	m_cBackColor;
	CEdit	m_Points;
	CListCtrl	m_ActiveList;
	CComboBox	m_CDataPlotFreq;
	CComboBox	m_CGraphSel;
	int		m_NPoints;
	int		m_DataPlotFreqSel;
	int		m_wGraphSel;
	CString	m_VTimeSpan;
	BOOL	m_AutoWrap;
	BOOL	m_UseMilitaryTime;
	CString	m_GraphName;
	int		m_wShowGraph;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphProperties)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_MaxPoints;
	int m_MinPoints;
	CLADAControlModuleDoc * doc;
	// Generated message map functions
	//{{AFX_MSG(CGraphProperties)
	afx_msg void OnEditList();
	afx_msg void OnSelchangeCWgraph();
	afx_msg void OnSelchangeDataPlotFreq();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusNpoints();
	virtual void OnOK();
	afx_msg void OnBackcolor();
	afx_msg void OnPaint();
	afx_msg void OnDeleteGraph();
	afx_msg void OnNewGraph();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHPROPERTIES_H__A8875C00_79E2_11D4_B01E_E4BEFADC062A__INCLUDED_)
