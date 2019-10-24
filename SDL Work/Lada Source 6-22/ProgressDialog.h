// This is Version 1.0 PLEASE DOCUMENT CHANGES
// Displays the progress of an operation
#if !defined(AFX_PROGRESSDIALOG_H__76C17CB2_3C79_11D4_98CE_00A076801ACD__INCLUDED_)
#define AFX_PROGRESSDIALOG_H__76C17CB2_3C79_11D4_98CE_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgressDialog.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// ProgressDialog dialog

class ProgressDialog : public CDialog
{
// Construction
public:
	ProgressDialog(BOOL *Canceled, const char *iText,const char *TitleBar,
		const char *CancelText = NULL,BOOL SPercent = TRUE,
		CWnd* pParent = NULL, BOOL DParent = TRUE);				// Standard constructor
	BOOL OnInitDialog();										// Does all the initialization stuff
	void SetInfo(int percentCompletion, char *newText = NULL);	// Sets the info and updates the bar
	BOOL Create(UINT nID, CWnd * pWnd = NULL)					// 
        { return CDialog::Create(nID,pWnd);}
	void Close();												// 

// Dialog Data
	//{{AFX_DATA(ProgressDialog)
	enum { IDD = PROGRESS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgressDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL *WindowClosed;				// If Cancel was pressed
	char InitText[100];					// The initial text
	char TitleBarText[70];				// the
	char CancelButtonText[30];
	BOOL ShowPercent;
	CWnd *pParentWnd;
	BOOL DisableParent;
	// Generated message map functions
	//{{AFX_MSG(ProgressDialog)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDIALOG_H__76C17CB2_3C79_11D4_98CE_00A076801ACD__INCLUDED_)
