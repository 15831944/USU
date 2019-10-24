// LADASetupDlg.h : header file
//
#include "Stepinfo.h"

#if !defined(AFX_LADASETUPDLG_H__EA80EA26_8326_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_LADASETUPDLG_H__EA80EA26_8326_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CLADASetupDlg dialog

const int m_numsteps=6;
class CLADASetupDlg : public CDialog
{
// Construction
public:
	int checknumber;
	void CheckCheck(int);
	void Reset(int);
	Stepinfo m_step[m_numsteps];
	int m_stepnumber;
	CBitmap m_Bitmap;

	
	CLADASetupDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLADASetupDlg)
	enum { IDD = IDD_LADASETUP_DIALOG };
	CStatic	m_CPicture;
	CButton	m_CText;
	CButton	m_CCheck9;
	CButton	m_CCheck8;
	CButton	m_CCheck7;
	CButton	m_CCheck6;
	CButton	m_CCheck5;
	CButton	m_CCheck4;
	CButton	m_CCheck3;
	CButton	m_CCheck2;
	CButton	m_CCheck1;
	CButton	m_CNext;
	CButton	m_CBack;
	BOOL	m_VCheck1;
	BOOL	m_VCheck2;
	BOOL	m_VCheck3;
	BOOL	m_VCheck4;
	BOOL	m_VCheck5;
	BOOL	m_VCheck6;
	BOOL	m_VCheck7;
	BOOL	m_VCheck8;
	BOOL	m_VCheck9;
	CString	m_VStep;
	CString	m_VTitle;
	CString	m_VText;
	CString	m_VPicture;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADASetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLADASetupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNext();
	afx_msg void OnBack();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADASETUPDLG_H__EA80EA26_8326_11D4_A864_0000E880BB29__INCLUDED_)
