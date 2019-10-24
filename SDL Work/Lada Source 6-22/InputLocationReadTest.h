#if !defined(AFX_INPUTLOCATIONREADTEST_H__85B21B82_3AED_11D5_B691_0080AD8FBDCC__INCLUDED_)
#define AFX_INPUTLOCATIONREADTEST_H__85B21B82_3AED_11D5_B691_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputLocationReadTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputLocationReadTest dialog
class CLADAControlModuleDoc;
class CInputLocationReadTest : public CDialog
{
// Construction
public:
	BOOL m_IsTestStopped;
	CLADAControlModuleDoc * pDoc;
	CInputLocationReadTest(CLADAControlModuleDoc *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputLocationReadTest)
	enum { IDD = IDD_DIALOG5 };
	double	m_AvgReadTime;
	BOOL	m_ReadFast;
	int		m_ReadFreq;
	int		m_ILsToRead;
	int		m_ReadsDone;
	int		m_ToBeServiced;
	CString	m_TotalTime;
	int		m_Servicing;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputLocationReadTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputLocationReadTest)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnReadFast();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTLOCATIONREADTEST_H__85B21B82_3AED_11D5_B691_0080AD8FBDCC__INCLUDED_)
