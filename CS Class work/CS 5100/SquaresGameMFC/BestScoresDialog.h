#if !defined(AFX_BESTSCORESDIALOG_H__3CD20101_461D_11D6_9E3F_00A0CC413690__INCLUDED_)
#define AFX_BESTSCORESDIALOG_H__3CD20101_461D_11D6_9E3F_00A0CC413690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BestScoresDialog.h : header file
//

class SquareGame;

/////////////////////////////////////////////////////////////////////////////
// BestScoresDialog dialog

class BestScoresDialog : public CDialog
{
// Construction
public:
	SquareGame * ptrGame;
	BestScoresDialog(SquareGame * ptrGame, CWnd* pParent = NULL);   // standard constructor
	CString text[5];

// Dialog Data
	//{{AFX_DATA(BestScoresDialog)
	enum { IDD = IDD_BEST_SCORES };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BestScoresDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BestScoresDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BESTSCORESDIALOG_H__3CD20101_461D_11D6_9E3F_00A0CC413690__INCLUDED_)
