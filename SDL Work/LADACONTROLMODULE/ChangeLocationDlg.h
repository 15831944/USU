#if !defined(AFX_CHANGELOCATIONDLG_H__01853161_8BB3_11D4_B01E_84C08E9E972A__INCLUDED_)
#define AFX_CHANGELOCATIONDLG_H__01853161_8BB3_11D4_B01E_84C08E9E972A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeLocationDlg.h : header file
//
class CCommOperations;
class CLADAControlModuleDoc;
/////////////////////////////////////////////////////////////////////////////
// CChangeLocationDlg dialog

class CChangeLocationDlg : public CDialog
{
// Construction
public:
	CChangeLocationDlg(CLADAControlModuleDoc *ptrDoc, CWnd* pParent = NULL);   // standard constructor

	CLADAControlModuleDoc *pDoc;
	CCommOperations *commObject;
// Dialog Data
	//{{AFX_DATA(CChangeLocationDlg)
	enum { IDD = IDD_EDITLOCATION };
	int		m_wLocation;
	double	m_value;
	double	m_newValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeLocationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeLocationDlg)
	afx_msg void OnGetvalue();
	afx_msg void OnSetvalue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGELOCATIONDLG_H__01853161_8BB3_11D4_B01E_84C08E9E972A__INCLUDED_)
