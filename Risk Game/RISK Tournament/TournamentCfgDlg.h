#if !defined(AFX_TOURNAMENTCFGDLG_H__27D3CAB8_6201_4B0B_A660_C40141DFEA25__INCLUDED_)
#define AFX_TOURNAMENTCFGDLG_H__27D3CAB8_6201_4B0B_A660_C40141DFEA25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TournamentCfgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTournamentCfgDlg dialog
class CRISKTournamentDlg;

class CTournamentCfgDlg : public CDialog
{
// Construction
public:
	void AddPlayer(CString FileName);
	BOOL m_DlgInitialized;
	void ComputeGames();

	CRISKTournamentDlg * ptrParent;
	CTournamentCfgDlg(CWnd* pParent = NULL);   // standard constructor

	BOOL TestDLL(CString fileName, CString &PlayerName);
// Dialog Data
	//{{AFX_DATA(CTournamentCfgDlg)
	enum { IDD = IDD_CONFIGURATION_DIALOG };
	CSpinButtonCtrl	m_spin1;
	CListCtrl	m_DllList;
	int		m_nPlayers;
	int		m_nRepetitions;
	int		m_PPG;
	int		m_nGames;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTournamentCfgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTournamentCfgDlg)
	afx_msg void OnAddDll();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePlayersPerGame();
	afx_msg void OnChangeNRepetitions();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOURNAMENTCFGDLG_H__27D3CAB8_6201_4B0B_A660_C40141DFEA25__INCLUDED_)
