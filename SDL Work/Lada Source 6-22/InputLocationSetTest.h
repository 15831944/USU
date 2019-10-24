#if !defined(AFX_INPUTLOCATIONSETTEST_H__415A0C20_5133_11D5_B692_0080AD8FBDCC__INCLUDED_)
#define AFX_INPUTLOCATIONSETTEST_H__415A0C20_5133_11D5_B692_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputLocationSetTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputLocationSetTest dialog

class CLADAControlModuleDoc;

class CInputLocationSetTest : public CDialog
{
// Construction
public:
	CLADAControlModuleDoc * pDoc;
	BOOL m_IsTestStopped;
	CInputLocationSetTest(CLADAControlModuleDoc *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputLocationSetTest)
	enum { IDD = IDD_DIALOG6 };
	double	m_AvgWriteTime;
	BOOL	m_WriteFast;
	int		m_WriteFreq;
	int		m_WritesDone;
	CString	m_TotalTime;
	int		m_nFailed;
	BOOL	m_useICommand;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputLocationSetTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputLocationSetTest)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTLOCATIONSETTEST_H__415A0C20_5133_11D5_B692_0080AD8FBDCC__INCLUDED_)
