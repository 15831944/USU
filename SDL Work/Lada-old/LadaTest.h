// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This program allows the user to test various functions of the Control Module and compare 
// the time on with how long the computer told it to be on.
#if !defined(AFX_LADATEST_H__1B8084E1_B6C1_4722_B419_16E764AA183E__INCLUDED_)
#define AFX_LADATEST_H__1B8084E1_B6C1_4722_B419_16E764AA183E__INCLUDED_

#include "CommOperations.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream.h>
#include "checkout.h"
//
/////////////////////////////////////////////////////////////////////////////
// LadaTest dialog
class CLADAControlModuleDoc;
class LadaTest : public CDialog
{
// Construction
public:
	int Doing;
	CTime WillEnd;
	int step;
	CTimeSpan Left;
	BOOL IsAutomatic;
	void SetStrings();			// Sets the text to the current language
	double pump;				// amount of water pumped
	CCheckout* print;			// Holds all the information gathered during checkout
	double get(int);			// Gets the desired input location
	CTime Start;				// The time the this part of the test started
	CLADAControlModuleDoc* pDoc;// The current document
	LadaTest(CLADAControlModuleDoc* doc,CCheckout* prin=NULL,BOOL isauto=FALSE,CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(LadaTest)
	enum { IDD = IDD_TEST };
	CEdit	m_ccomments;		// The control for the comments edit box
	CString	m_cv1;
	CString	m_cv10;
	CString	m_cv11;
	CString	m_cv12;
	CString	m_cv13;
	CString	m_cv14;
	CString	m_cv2;
	CString	m_cv3;
	CString	m_cv4;
	CString	m_cv5;
	CString	m_cv6;
	CString	m_cv7;
	CString	m_cv8;
	CString	m_cv9;
	CString	m_uv1;
	CString	m_uv10;
	CString	m_uv11;
	CString	m_uv12;
	CString	m_uv13;
	CString	m_uv14;
	CString	m_uv2;
	CString	m_uv3;
	CString	m_uv4;
	CString	m_uv5;
	CString	m_uv6;
	CString	m_uv7;
	CString	m_uv8;
	CString	m_uv9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LadaTest)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LadaTest)
	virtual BOOL OnInitDialog();			// Does the initial setup
	afx_msg void OnTimer(UINT nIDEvent);	// Is called when a timer goes off
	virtual void OnOK();					// Called when Ok is pressed
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADATEST_H__1B8084E1_B6C1_4722_B419_16E764AA183E__INCLUDED_)
