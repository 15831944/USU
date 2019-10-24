// BitmapButtonTestDlg.h : header file
//

#if !defined(AFX_BITMAPBUTTONTESTDLG_H__A437257B_9565_11D4_B01E_E5775E14782A__INCLUDED_)
#define AFX_BITMAPBUTTONTESTDLG_H__A437257B_9565_11D4_B01E_E5775E14782A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonTestDlg dialog

class CBitmapButtonTestDlg : public CDialog
{
// Construction
public:
	CBitmapButton Button1;
	CBitmapButtonTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBitmapButtonTestDlg)
	enum { IDD = IDD_BITMAPBUTTONTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapButtonTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBitmapButtonTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPBUTTONTESTDLG_H__A437257B_9565_11D4_B01E_E5775E14782A__INCLUDED_)
