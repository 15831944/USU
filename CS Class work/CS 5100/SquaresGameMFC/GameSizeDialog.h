#if !defined(AFX_GAMESIZEDIALOG_H__11363DE2_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
#define AFX_GAMESIZEDIALOG_H__11363DE2_464A_11D6_A4E8_005004A6D7B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GameSizeDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GameSizeDialog dialog

class GameSizeDialog : public CDialog
{
// Construction
public:
	GameSizeDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GameSizeDialog)
	enum { IDD = IDD_SELECT_GAME_SIZE };
	int		m_GameSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GameSizeDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GameSizeDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GAMESIZEDIALOG_H__11363DE2_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
