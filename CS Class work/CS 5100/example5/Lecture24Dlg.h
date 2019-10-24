// Lecture24Dlg.h : header file
//

#if !defined(AFX_LECTURE24DLG_H__B88C61FE_D619_11D2_A4B8_00409505AA4A__INCLUDED_)
#define AFX_LECTURE24DLG_H__B88C61FE_D619_11D2_A4B8_00409505AA4A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CLecture24Dlg dialog

class CLecture24Dlg : public CDialog
{
// Construction
public:
	CLecture24Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLecture24Dlg)
	enum { IDD = IDD_LECTURE24_DIALOG };
	CString	m_fileName;
	CString	m_fileContents;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLecture24Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLecture24Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LECTURE24DLG_H__B88C61FE_D619_11D2_A4B8_00409505AA4A__INCLUDED_)
