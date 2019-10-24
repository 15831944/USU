#if !defined(AFX_REPLACEGRAPHDLG_H__8E4CC6A2_1662_11D5_B01E_A31918DF8332__INCLUDED_)
#define AFX_REPLACEGRAPHDLG_H__8E4CC6A2_1662_11D5_B01E_A31918DF8332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReplaceGraphDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplaceGraphDlg dialog
class CLADAControlModuleDoc;
class CReplaceGraphDlg : public CDialog
{
// Construction
public:
	CLADAControlModuleDoc * pDoc;
	void SetStrings();
	CReplaceGraphDlg(CLADAControlModuleDoc * doc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReplaceGraphDlg)
	enum { IDD = IDD_REPLACE_GRAPH };
	CListBox	m_cGraphList;
	int		m_wGraph;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplaceGraphDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplaceGraphDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGraphList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEGRAPHDLG_H__8E4CC6A2_1662_11D5_B01E_A31918DF8332__INCLUDED_)
