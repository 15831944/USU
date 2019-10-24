// SquaresGameDlg.h : header file
//

#if !defined(AFX_SQUARESGAMEDLG_H__44B78163_8BA3_4D9A_B882_FDD165441D9C__INCLUDED_)
#define AFX_SQUARESGAMEDLG_H__44B78163_8BA3_4D9A_B882_FDD165441D9C__INCLUDED_

#include "SquareGame.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameDlg dialog

class SquareEdge;

class CSquaresGameDlg : public CDialog
{
// Construction
public:
	SquareGame game;
	CSquaresGameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSquaresGameDlg)
	enum { IDD = IDD_SQUARESGAME_DIALOG };
	CStatic	m_p2Text;
	CStatic	m_p1Text;
	int		m_Player1Score;
	int		m_Player2Score;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquaresGameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSquaresGameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileExit();
	afx_msg void OnFileNewgame();
	afx_msg void OnFileBestgames();
	afx_msg void OnOptionsGamesize();
	afx_msg void OnOptionsPlayer1color();
	afx_msg void OnOptionsPlayer2color();
	afx_msg void OnOptionsSidecolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUARESGAMEDLG_H__44B78163_8BA3_4D9A_B882_FDD165441D9C__INCLUDED_)
