// Test Set System FontsDlg.h : header file
//

#if !defined(AFX_TESTSETSYSTEMFONTSDLG_H__DFB03A86_853F_11D5_B021_805871C45726__INCLUDED_)
#define AFX_TESTSETSYSTEMFONTSDLG_H__DFB03A86_853F_11D5_B021_805871C45726__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestSetSystemFontsDlg dialog

class CTestSetSystemFontsDlg : public CDialog
{
// Construction
public:
	void AddInfo(char * fontType, LOGFONT * ptrFontStruct, int pos);
	CTestSetSystemFontsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestSetSystemFontsDlg)
	enum { IDD = IDD_TESTSETSYSTEMFONTS_DIALOG };
	CListCtrl	m_FontList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSetSystemFontsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSetSystemFontsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSETSYSTEMFONTSDLG_H__DFB03A86_853F_11D5_B021_805871C45726__INCLUDED_)
