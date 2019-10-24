#if !defined(AFX_CONFDLG_H__08D671A2_E6E0_11D2_ADAA_00616E01FED8__INCLUDED_)
#define AFX_CONFDLG_H__08D671A2_E6E0_11D2_ADAA_00616E01FED8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ConfDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfDlg dialog

class CConfDlg : public CDialog
{
// Construction
public:
	CConfDlg(CWnd* pParent = NULL);   // standard constructor
	CString& getConfFile(void) { return m_conf_file; }
	void setConfFile(const CString& cf) { m_conf_file = cf; }

// Dialog Data
	//{{AFX_DATA(CConfDlg)
	enum { IDD = IDD_CONFIG_DLG };
	CString	m_conf_file;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFDLG_H__08D671A2_E6E0_11D2_ADAA_00616E01FED8__INCLUDED_)
