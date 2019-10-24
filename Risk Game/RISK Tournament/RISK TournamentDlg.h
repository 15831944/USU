// RISK TournamentDlg.h : header file
//

#if !defined(AFX_RISKTOURNAMENTDLG_H__36D978D7_0E03_4611_AAEE_61668DC4B6B1__INCLUDED_)
#define AFX_RISKTOURNAMENTDLG_H__36D978D7_0E03_4611_AAEE_61668DC4B6B1__INCLUDED_

#include "TournamentCfgDlg.h"	// Added by ClassView
#include "TestData.h"
#include "GameProcessorThread.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRISKTournamentDlg dialog

class CRISKTournamentDlg : public CDialog
{
// Construction
public:
	void EndProcessing();
	CGameProcessorThread m_WorkerThread;
	CTestData m_progData;
	CTime m_StartTime;
	int m_nGamesPlayed;
	void EnableConfiguration(BOOL Enable);
	BOOL AddPlayer(CString FileName);
	void SaveData(); 
	void ComputeGames();
	void LoadData();
	BOOL TestDLL(CString fileName, CString &PlayerName);
	BOOL m_IsRunning;
	//CTournamentCfgDlg m_cfgDlg;
	CRISKTournamentDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL IsDLLPathInUse(CString fileName);
	
// Dialog Data
	//{{AFX_DATA(CRISKTournamentDlg)
	enum { IDD = IDD_RISKTOURNAMENT_DIALOG };
	CProgressCtrl	m_Progress1;
	CSpinButtonCtrl	m_spin1;
	CListCtrl	m_DllList;
	int		m_nPlayers;
	int		m_nGames;
	int		m_nRepetitions;
	int		m_PPG;
	CString	m_CurrentGame;
	CString	m_GamesPlayed;
	CString	m_TimeRemaining;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRISKTournamentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRISKTournamentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartStop();
	afx_msg void OnAddDll();
	afx_msg void OnRemoveDll();
	afx_msg void OnChangeNRepetitions();
	afx_msg void OnChangePlayersPerGame();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKTOURNAMENTDLG_H__36D978D7_0E03_4611_AAEE_61668DC4B6B1__INCLUDED_)
