#if !defined(AFX_GRAPHPROPERTIES_H__A8875C00_79E2_11D4_B01E_E4BEFADC062A__INCLUDED_)
#define AFX_GRAPHPROPERTIES_H__A8875C00_79E2_11D4_B01E_E4BEFADC062A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphProperties.h : header file
//
class CLADAControlModuleDoc;

/////////////////////////////////////////////////////////////////////////////
// CGraphProperties dialog

class CGraphProperties : public CDialog
{
// Construction
public:
	CGraphProperties(CLADAControlModuleDoc *pDoc, CWnd* pParent = NULL);   // standard constructor
	void ShowVisibleSpan();
	void SetStatus(int whichItem);
	void GetCheckedItems();
	
// Dialog Data
	//{{AFX_DATA(CGraphProperties)
	enum { IDD = IDD_GRAPH_PROPERTIES };
	CEdit	m_Points;
	CListCtrl	m_ActiveList;
	CComboBox	m_CDataPlotFreq;
	CComboBox	m_CGraphSel;
	int		m_NPoints;
	BOOL	m_ShowGraph;
	int		m_DataPlotFreqSel;
	int		m_wGraphSel;
	CString	m_VTimeSpan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphProperties)
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
	afx_msg void OnShowGraph();
	afx_msg void OnSelchangeCWgraph();
	afx_msg void OnSelchangeDataPlotFreq();
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusNpoints();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHPROPERTIES_H__A8875C00_79E2_11D4_B01E_E4BEFADC062A__INCLUDED_)
