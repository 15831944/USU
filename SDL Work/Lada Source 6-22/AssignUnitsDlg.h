#if !defined(AFX_ASSIGNUNITSDLG_H__E285CD20_58A7_11D5_8306_CE4697375339__INCLUDED_)
#define AFX_ASSIGNUNITSDLG_H__E285CD20_58A7_11D5_8306_CE4697375339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AssignUnitsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAssignUnitsDlg dialog

class CAssignUnitsDlg : public CDialog
{
// Construction
public:
	CLADAControlModuleDoc * pDoc;
	CAssignUnitsDlg(CLADAControlModuleDoc *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAssignUnitsDlg)
	enum { IDD = IDD_ASSIGN_UNITS };
	CListCtrl	m_ILList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssignUnitsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAssignUnitsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkInputLocationList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUnits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSIGNUNITSDLG_H__E285CD20_58A7_11D5_8306_CE4697375339__INCLUDED_)
