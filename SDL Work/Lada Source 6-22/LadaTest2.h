#if !defined(AFX_LADATEST2_H__58D33E40_595C_11D5_8306_829BE732EF3B__INCLUDED_)
#define AFX_LADATEST2_H__58D33E40_595C_11D5_8306_829BE732EF3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LadaTest2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LadaTest2 dialog
class CLADAControlModuleDoc ;
class CCheckout;
class LadaTest2 : public CDialog
{
// Construction
public:
	BOOL IsAutomatic;
	CCheckout * print;
	void CollectData(BOOL UpdateUser);
	CLADAControlModuleDoc * pDoc;
	void SetStrings();
	LadaTest2(CLADAControlModuleDoc *, CCheckout *, BOOL IsAuto, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LadaTest2)
	enum { IDD = IDD_LADATEST2 };
	CString	m_u5;
	CString	m_u6;
	CString	m_u7;
	CString	m_u8;
	CString	m_u9;
	CString	m_u10;
	CString	m_u11;
	CString	m_u12;
	CString	m_cv6;
	CString	m_cv7;
	CString	m_cv8;
	CString	m_cv9;
	CString	m_cv11;
	CString	m_cv12;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LadaTest2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LadaTest2)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADATEST2_H__58D33E40_595C_11D5_8306_829BE732EF3B__INCLUDED_)
