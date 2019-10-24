// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This is temporary dialog that allows the user to check and set flags
#if !defined(AFX_FLAG_H__15BE0861_D5CE_11D4_98FD_00A076801ACD__INCLUDED_)
#define AFX_FLAG_H__15BE0861_D5CE_11D4_98FD_00A076801ACD__INCLUDED_

#include "LADA Control ModuleDoc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Flag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFlag dialog
class CLADAControlModuleDoc;

class CFlag : public CDialog
{
// Construction
public:
	void SetStrings();
	void SetState();				// Sets a flag value
	void GetState();				// Gets a flag value
	CLADAControlModuleDoc * pDoc;	// Current document
	CFlag(CLADAControlModuleDoc * pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFlag)
	enum { IDD = IDD_FLAG };
	BOOL	m_FState;				// The state of the flag
	int		m_wFlag;				// Which flag is being checked
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFlag)
	afx_msg void OnChangeFlagState();// Called when the user changes the flag state
	afx_msg void OnChangeWFlag();	// Called when the user changes the flag selected
	virtual void OnOK();			// Called when the OK button is pressed
	virtual BOOL OnInitDialog();	// Initialization
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLAG_H__15BE0861_D5CE_11D4_98FD_00A076801ACD__INCLUDED_)
