#if !defined(AFX_FLAGSDIALOG_H__76C17CB4_3C79_11D4_98CE_00A076801ACD__INCLUDED_)
#define AFX_FLAGSDIALOG_H__76C17CB4_3C79_11D4_98CE_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FlagsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FlagsDialog dialog

class FlagsDialog : public CDialog
{
// Construction
public:
	FlagsDialog(CWnd* pParent = NULL);   // standard constructor
	BOOL OnInitDialog();
	BOOL Create(UINT nID, CWnd * pWnd = NULL)
        { return CDialog::Create(nID,pWnd);}
	CButton m_WhichFlags;
	void UpdateFlags();
	
// Dialog Data
	//{{AFX_DATA(FlagsDialog)
	enum { IDD = FLAGS_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FlagsDialog)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	char TFlagNames[8][30];
	char TPortNames[8][30];

	void DisplayAllFlagInfo();
	void ShowWhichFlags();
	void ShowToggleOn();
	void ShowFlagName(int whichFlag);
	void ShowFlagStatus(int whichFlag);
	void ShowToggleState(int whichFlag);
	void ChangeToggleStatus(int Status, int whichFlag);
	// Generated message map functions
	//{{AFX_MSG(FlagsDialog)
	afx_msg void OnCtoggleon();
	afx_msg void OnSelchangeFlagfreq1();
	afx_msg void OnSelchangeFlagfreq2();
	afx_msg void OnSelchangeFlagfreq3();
	afx_msg void OnSelchangeFlagfreq4();
	afx_msg void OnSelchangeFlagfreq5();
	afx_msg void OnSelchangeFlagfreq6();
	afx_msg void OnSelchangeFlagfreq7();
	afx_msg void OnSelchangeFlagfreq8();
	afx_msg void OnR1();
	afx_msg void OnR2();
	afx_msg void OnR3();
	afx_msg void OnR4();
	afx_msg void OnR5();
	afx_msg void OnR6();
	afx_msg void OnR7();
	afx_msg void OnR8();
	afx_msg void OnRe1();
	afx_msg void OnRe2();
	afx_msg void OnRe3();
	afx_msg void OnRe4();
	afx_msg void OnRe5();
	afx_msg void OnRe6();
	afx_msg void OnRe7();
	afx_msg void OnRe8();
	afx_msg void OnRportflags();
	afx_msg void OnRuserflags();
	virtual void OnOK();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLAGSDIALOG_H__76C17CB4_3C79_11D4_98CE_00A076801ACD__INCLUDED_)
