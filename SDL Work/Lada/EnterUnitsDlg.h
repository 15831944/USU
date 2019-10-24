#if !defined(AFX_ENTERUNITSDLG_H__E285CD21_58A7_11D5_8306_CE4697375339__INCLUDED_)
#define AFX_ENTERUNITSDLG_H__E285CD21_58A7_11D5_8306_CE4697375339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EnterUnitsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterUnitsDlg dialog

class CEnterUnitsDlg : public CDialog
{
// Construction
public:
	CString * ptrReturnData;
	CEnterUnitsDlg(CString *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterUnitsDlg)
	enum { IDD = IDD_ENTER_UNITS };
	CString	m_data;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterUnitsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterUnitsDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTERUNITSDLG_H__E285CD21_58A7_11D5_8306_CE4697375339__INCLUDED_)
