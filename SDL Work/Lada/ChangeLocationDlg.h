// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_CHANGELOCATIONDLG_H__01853161_8BB3_11D4_B01E_84C08E9E972A__INCLUDED_)
#define AFX_CHANGELOCATIONDLG_H__01853161_8BB3_11D4_B01E_84C08E9E972A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeLocationDlg.h : header file
//
class CCommOperations;
class CLADAControlModuleDoc;
// Allows the user to access and change input locations
/////////////////////////////////////////////////////////////////////////////
// CChangeLocationDlg dialog

class CChangeLocationDlg : public CDialog
{
// Construction
public:
	void SetStrings();
	CChangeLocationDlg(CLADAControlModuleDoc *ptrDoc, int initialLocation = 0, CWnd* pParent = NULL);   // standard constructor

	CLADAControlModuleDoc *pDoc;	// The current document
	CCommOperations *commObject;	// The current Communication Object with the CR10
// Dialog Data
	//{{AFX_DATA(CChangeLocationDlg)
	enum { IDD = IDD_EDITLOCATION };
	int		m_wLocation;			// Which location is being accesed
	double	m_value;				// The value retrieved from the CR10
	double	m_newValue;				// The value entered by the user
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeLocationDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeLocationDlg)
	afx_msg void OnGetvalue();
	afx_msg void OnSetvalue();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGELOCATIONDLG_H__01853161_8BB3_11D4_B01E_84C08E9E972A__INCLUDED_)
