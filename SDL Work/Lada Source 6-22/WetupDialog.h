// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_PROGRESSDIALOG_H__76C17CB2_3C79_11D4_98CE_00A076801ACD__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__76C17CB2_3C79_11D4_98CE_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WetupDialog.h : header file
//

class CLADAControlModuleDoc;
/////////////////////////////////////////////////////////////////////////////
// WetupDialog dialog

class WetupDialog : public CDialog
{
// Construction
public:
	BOOL IsComplete;
	int nIntervals;
	CTimeSpan BurstLength;
	CTimeSpan TimeRemaining;
	CTime m_FinishTime;
	CTime m_NextBurstTime;
	void SetStrings();
	BOOL PrepareCR10();
	BOOL IsPaused;
	CTime GetNextCR10BurstTime();
	UINT m_FinishStatus;

	CTimeSpan TimeElapsed;
	void OnComplete();
	double m_BurstVolume;
	CLADAControlModuleDoc * pDoc;
	
	WetupDialog(BOOL *Canceled = NULL, 
		BOOL SPercent = TRUE, CWnd* pParent = NULL, 
		BOOL DParent = TRUE, CLADAControlModuleDoc * doc = NULL);   // standard constructor
	BOOL OnInitDialog();
	void SetInfo(char *newText = NULL);
	BOOL Create(UINT nID, CWnd * pWnd = NULL)
        { return CDialog::Create(nID,pWnd);}
	BOOL StartWetup();
//	void OnTimer(UINT nIDEvent);
	int GetState();

// Dialog Data
	//{{AFX_DATA(WetupDialog)
	enum { IDD = IDD_WETUP_DIALOG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(WetupDialog)
	public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	BOOL *WindowClosed;
		
	BOOL ShowPercent;
	CWnd *pParentWnd;
	BOOL DisableParent;

	CTime Time;

	// Generated message map functions
	//{{AFX_MSG(WetupDialog)
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnPause();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__76C17CB2_3C79_11D4_98CE_00A076801ACD__INCLUDED_)
