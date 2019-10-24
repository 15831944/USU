#if !defined(AFX_GAMEOVERDIALOG_H__3CD20100_461D_11D6_9E3F_00A0CC413690__INCLUDED_)
#define AFX_GAMEOVERDIALOG_H__3CD20100_461D_11D6_9E3F_00A0CC413690__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameOverDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GameOverDialog dialog

class GameOverDialog : public CDialog
{
// Construction
public:
	GameOverDialog(CString name, int score, bool isTie, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GameOverDialog)
	enum { IDD = IDD_GAME_OVER };
	CString	m_text1;
	CString	m_text2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GameOverDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GameOverDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMEOVERDIALOG_H__3CD20100_461D_11D6_9E3F_00A0CC413690__INCLUDED_)
