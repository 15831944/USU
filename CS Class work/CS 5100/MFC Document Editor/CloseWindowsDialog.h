#if !defined(AFX_CLOSEWINDOWSDIALOG_H__1B57EADE_FC1A_4640_8B73_1427ADBE3649__INCLUDED_)
#define AFX_CLOSEWINDOWSDIALOG_H__1B57EADE_FC1A_4640_8B73_1427ADBE3649__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CloseWindowsDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCloseWindowsDialog dialog

class CCloseWindowsDialog : public CDialog
{
// Construction
public:
	CCloseWindowsDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCloseWindowsDialog)
	enum { IDD = IDD_CLOSE_WINDOWS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseWindowsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCloseWindowsDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEWINDOWSDIALOG_H__1B57EADE_FC1A_4640_8B73_1427ADBE3649__INCLUDED_)
