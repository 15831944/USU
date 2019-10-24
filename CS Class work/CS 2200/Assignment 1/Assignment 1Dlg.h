// Assignment 1Dlg.h : header file
//

#if !defined(AFX_ASSIGNMENT1DLG_H__D80EA37A_4248_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_ASSIGNMENT1DLG_H__D80EA37A_4248_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TOSCREEN		FALSE
#define FROMSCREEN		TRUE

/////////////////////////////////////////////////////////////////////////////
// CAssignment1Dlg dialog

class CAssignment1Dlg : public CDialog
{
// Construction
public:
	CAssignment1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAssignment1Dlg)
	enum { IDD = IDD_ASSIGNMENT1_DIALOG };
	CStatic	m_ChessArea;
	CSpinButtonCtrl	m_SpinControl;
	int		m_SolutionNumber;
	int		m_RecursiveCalls;
	int		m_QueensRemoved;
	int		m_Solutions;
	int		m_TimeRequired;
	int		m_IsSafeCalls;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssignment1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAssignment1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnViewSource();
	virtual void OnCancel();
	afx_msg void OnChangeSolutionNumber();
	afx_msg void OnAboutbox();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Solve8Queens(int QueensPos[] = NULL, int CurrColumn = 0);
	BOOL IsSquareSafe(int Row, int Col,int QueenRow[]);
	void ShowSolution();
	int SolutionData[100][8];
	CBitmap m_bmpQueenP;
	CDC	m_memQueenBmpP;
	CBitmap m_bmpQueenG;
	CDC	m_memQueenBmpG;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSIGNMENT1DLG_H__D80EA37A_4248_11D4_98D1_00A076801ACD__INCLUDED_)
