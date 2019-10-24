#if !defined(AFX_NEWSTRINGTABLEDLG_H__16E7BB9A_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
#define AFX_NEWSTRINGTABLEDLG_H__16E7BB9A_9EBD_11D4_98E8_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewStringTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewStringTableDlg dialog
class CStringEditorDoc;

class CNewStringTableDlg : public CDialog
{
// Construction
public:
	~CNewStringTableDlg();
	LOGFONT m_LogFont;
	CString * m_ptrNames;
	BOOL IsInitialized;
	CStringEditorDoc * pDoc;
	CNewStringTableDlg(CStringEditorDoc *pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewStringTableDlg)
	enum { IDD = IDD_NEWSTRINGTABLE };
	CSpinButtonCtrl	m_Spin;
	CEdit	m_CNLanguages;
	CEdit	m_CLNumber;
	CString	m_FontName;
	CString	m_langName;
	int		m_langNumber;
	int		m_nLanguages;
	int		m_fSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewStringTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewStringTableDlg)
	afx_msg void OnChangefont();
	afx_msg void OnChangeNlanguages();
	afx_msg void OnChangeLnumber();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeLname();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWSTRINGTABLEDLG_H__16E7BB9A_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
