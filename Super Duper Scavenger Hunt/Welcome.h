#if !defined(AFX_WELCOME_H__EACAA50E_53B6_11D5_A51E_444553540000__INCLUDED_)
#define AFX_WELCOME_H__EACAA50E_53B6_11D5_A51E_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Welcome.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWelcome dialog

class CWelcome : public CDialog
{
// Construction
public:
	CWelcome(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcome)
	enum { IDD = IDD_WELCOME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWelcome)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOME_H__EACAA50E_53B6_11D5_A51E_444553540000__INCLUDED_)
