#if !defined(AFX_NEWGAMEDIALOG_H__11363DE1_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
#define AFX_NEWGAMEDIALOG_H__11363DE1_464A_11D6_A4E8_005004A6D7B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewGameDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewGameDialog dialog

class NewGameDialog : public CDialog
{
// Construction
public:
	int m_GameType;
	NewGameDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NewGameDialog)
	enum { IDD = IDD_NEW_GAME };
	int		m_GameSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewGameDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NewGameDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWGAMEDIALOG_H__11363DE1_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
