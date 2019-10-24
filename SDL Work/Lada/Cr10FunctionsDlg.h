#if !defined(AFX_CR10FUNCTIONSDLG_H__BFE71580_F6F5_11D4_99BE_8728CD0B604D__INCLUDED_)
#define AFX_CR10FUNCTIONSDLG_H__BFE71580_F6F5_11D4_99BE_8728CD0B604D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Cr10FunctionsDlg.h : header file
//

class CLADAControlModuleDoc;
/////////////////////////////////////////////////////////////////////////////
// CCr10FunctionsDlg dialog

class CCr10FunctionsDlg : public CDialog
{
// Construction
public:
	CLADAControlModuleDoc * pDoc;
	void SetStrings();
	CCr10FunctionsDlg(CLADAControlModuleDoc *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCr10FunctionsDlg)
	enum { IDD = IDD_CR10_FUNCTIONS };
	CString	m_CR10Time;
	CString	m_FIVATime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCr10FunctionsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCr10FunctionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetFinalStorage();
	afx_msg void OnSetFlags();
	afx_msg void OnSetlocation();
	afx_msg void OnUpdateTime();
	afx_msg void OnUploadprogram();
	afx_msg void OnUnlockPassword();
	afx_msg void OnResetFinalStorage();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CR10FUNCTIONSDLG_H__BFE71580_F6F5_11D4_99BE_8728CD0B604D__INCLUDED_)
