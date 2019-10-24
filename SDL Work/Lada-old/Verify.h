// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog is used to verify certain values being read by the computer with those read 
// by the user which will be outputed to a file later.

#if !defined(AFX_VERIFY_H__2F711C00_B157_11D4_8BFB_0020781F78D7__INCLUDED_)
#define AFX_VERIFY_H__2F711C00_B157_11D4_8BFB_0020781F78D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Verify.h : header file
//
#include "checkout.h"
#include "Lada Control ModuleDoc.h"

/////////////////////////////////////////////////////////////////////////////
// Verify dialog
class CLADAControlModuleDoc;
class Verify : public CDialog
{
// Construction
public:
	void SetStrings();			// Sets the text to the current language
	CCheckout* print;			// Stores to values to later output to a file
	double get(int);			// Gets a value from the CR10
	BOOL IsAutomatic;					// Depending on which state it grabs different values
	CLADAControlModuleDoc* pDoc;// The current document
	void getvalues();			// Gets all the values and displays them
	Verify(CLADAControlModuleDoc* doc=NULL,BOOL isauto=FALSE, CCheckout* prin=NULL,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Verify)
	enum { IDD = IDD_VERIFY };
	double	m_cv1; // The first computer value
	double	m_cv2; // The second computer value
	double	m_cv3; // The third computer value
	double	m_cv4; // The fourth computer value
	double	m_cv5; // The fifth computer value
	double	m_uv1; // The first user value
	double	m_uv2; // The second user value
	double	m_uv3; // The third user value
	double	m_uv4; // The fourth user value
	double	m_uv5; // The fifth user value
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Verify)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Verify)
	virtual void OnOK(); //exits
	virtual BOOL OnInitDialog(); //Does the inital stuff
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERIFY_H__2F711C00_B157_11D4_8BFB_0020781F78D7__INCLUDED_)
