// Super Duper Scavenger HuntDlg.h : header file
//

#if !defined(AFX_SUPERDUPERSCAVENGERHUNTDLG_H__EACAA506_53B6_11D5_A51E_444553540000__INCLUDED_)
#define AFX_SUPERDUPERSCAVENGERHUNTDLG_H__EACAA506_53B6_11D5_A51E_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSuperDuperScavengerHuntDlg dialog
#include "Step.h"

class CSuperDuperScavengerHuntDlg : public CDialog
{
// Construction
public:
	BOOL TimeIsUp;
	void AdvanceToNextStep();
	void EndQuest();
	int nStepsTimeOut;
	int nStepsWrong;
	CTime stepFinishTime;
	void DisplayStep();
	Step Steps[10];
	int curStep;
	int totalSteps;
	CSuperDuperScavengerHuntDlg(CWnd* pParent = NULL);	// standard constructor
	~CSuperDuperScavengerHuntDlg();
// Dialog Data
	//{{AFX_DATA(CSuperDuperScavengerHuntDlg)
	enum { IDD = IDD_SUPERDUPERSCAVENGERHUNT_DIALOG };
	CString	m_Answer;
	CString	m_RiddleText;
	CString	m_TimeLeft;
	CString	m_AnswerText;
	CString	m_Location;
	CString	m_Heading;
	CString	m_Distance;
	CString	m_Caption;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperDuperScavengerHuntDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSuperDuperScavengerHuntDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERDUPERSCAVENGERHUNTDLG_H__EACAA506_53B6_11D5_A51E_444553540000__INCLUDED_)
