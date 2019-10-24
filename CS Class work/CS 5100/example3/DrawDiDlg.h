// DrawDiDlg.h : header file
//

#if !defined(AFX_DRAWDIDLG_H__539863B7_0724_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_DRAWDIDLG_H__539863B7_0724_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDrawDiDlg dialog

class CDrawDiDlg : public CDialog
{
// Construction
public:
	CDrawDiDlg(CWnd* pParent = NULL);	// standard constructor
	boolean draw;
	int intensity;
// Dialog Data
	//{{AFX_DATA(CDrawDiDlg)
	enum { IDD = IDD_DRAWDI_DIALOG };
	CListBox	m_choice;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawDiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDrawDiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWDIDLG_H__539863B7_0724_11D4_B398_00A0CC548BE4__INCLUDED_)
