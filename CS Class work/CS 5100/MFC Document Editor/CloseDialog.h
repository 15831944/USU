#if !defined(AFX_CLOSEDIALOG_H__87E46A47_ED65_49C2_BB32_0AA4D86DE633__INCLUDED_)
#define AFX_CLOSEDIALOG_H__87E46A47_ED65_49C2_BB32_0AA4D86DE633__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CloseDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCloseDialog dialog

class CMainFrame;

class CCloseDialog : public CDialog
{
// Construction
public:
	CCloseDialog(CMainFrame *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCloseDialog)
	enum { IDD = IDD_CLOSE_WINDOWS };
	CListBox	m_windowList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMainFrame * ptrMainFrame;

	// Generated message map functions
	//{{AFX_MSG(CCloseDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEDIALOG_H__87E46A47_ED65_49C2_BB32_0AA4D86DE633__INCLUDED_)
