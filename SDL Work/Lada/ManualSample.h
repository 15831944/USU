// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog performs a Manual Sample to find the Soil Moisture levels
#if !defined(AFX_MANUALSAMPLE_H__7FB03E21_A9C1_11D4_98EA_00A076801ACD__INCLUDED_)
#define AFX_MANUALSAMPLE_H__7FB03E21_A9C1_11D4_98EA_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualSample.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CManualSample dialog
#include <fstream.h>
#include "checkout.h"
class CLADAControlModuleDoc;

class CManualSample : public CDialog
{
// Construction
public:
	void OnRefreshData1();
	double diff[8];
	void GetLastResults();
	int step1;
	int step2;
	BOOL WillOutput;					// If the information will be exported
	CCheckout* print;					// The Checkout information
	BOOL AutoStart;						// If the test will automatically start when the dialog is created
	CLADAControlModuleDoc* pDoc;		// The current document
	double Comm(int location);			// Returns the input location value from location
	void SetStrings();					// Sets the text to the current language
	double* data;						// Stores the data gathered
	CTime FinishTime;						// The time the test started
	CManualSample(CLADAControlModuleDoc* Doc,BOOL AutoStart=FALSE,CCheckout* prin = NULL,CWnd* pParent = NULL);	// Constructor
	~CManualSample();	// standard Destructor

// Dialog Data
	//{{AFX_DATA(CManualSample)
	enum { IDD = IDD_MANUALTEST2 };
	CButton	m_start2;
	CButton	m_start1;
	CListCtrl	m_cchamber2;	// The control for the Chamber A List Control
	CListCtrl	m_cchamber1;	// The control for the Chamber B List Control
	CString	m_mTime1;
	CString	m_mTime2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualSample)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CManualSample)
	virtual BOOL OnInitDialog();		// Initialization
	afx_msg void OnTimer(UINT nIDEvent);// Called when a timer goes off
	virtual void OnOK();				// Called when OK is pressed
	afx_msg void OnStart1();
	afx_msg void OnStart2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALSAMPLE_H__7FB03E21_A9C1_11D4_98EA_00A076801ACD__INCLUDED_)
