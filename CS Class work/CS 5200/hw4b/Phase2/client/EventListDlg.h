#if !defined(AFX_EVENTLISTDLG_H__5993CAA3_A8E6_11D5_B509_000086204AC6__INCLUDED_)
#define AFX_EVENTLISTDLG_H__5993CAA3_A8E6_11D5_B509_000086204AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEventListDlg dialog

class CEventListDlg : public CDialog
{
// Construction
public:
	CEventListDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEventListDlg)
	enum { IDD = IDD_EVENT_LIST };
	CString	m_end;
	CString	m_list;
	CString	m_start;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventListDlg)
	afx_msg void OnQuery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTLISTDLG_H__5993CAA3_A8E6_11D5_B509_000086204AC6__INCLUDED_)
