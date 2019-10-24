// LADADIAGDlg.h : header file
//
/*
#if !defined(AFX_LADADIAGDLG_H__BBF6AD86_8A41_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_LADADIAGDLG_H__BBF6AD86_8A41_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "fstream.h"

/////////////////////////////////////////////////////////////////////////////
// CLADADIAGDlg dialog
class CLADAControlModuleDoc;
//class CCommOperations;
#include "CommOperations.h"
 
//extern enum CR10ControlType { On, Off, NoChange, Forward, Reverse };

class CLADADIAGDlg : public CDialog
{
// Construction
public:
//	ofstream fout;
	BOOL ControlCR10( CR10ControlType Lights = NoChange, CR10ControlType Fans = NoChange,
		CR10ControlType Pump1 = NoChange, CR10ControlType Pump2 = NoChange);
	bool Comm(int value,int locnumber=98);
	CCommOperations * commObject;
	CLADAControlModuleDoc * pDoc;
	void SetStrings();
	//CCommOperations* commobject;

	CLADADIAGDlg(CCommOperations * commObj, CLADAControlModuleDoc * doc = NULL,CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLADADIAGDlg)
	enum { IDD = IDD_LADADIAG_DIALOG };
	CButton	m_apump;
	BOOL	m_vair;
	CString	m_comments;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADADIAGDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLADADIAGDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFans();
	afx_msg void OnLights();
	afx_msg void OnWaterf();
	afx_msg void OnWaterb();
	afx_msg void OnApump();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADADIAGDLG_H__BBF6AD86_8A41_11D4_A864_0000E880BB29__INCLUDED_)
*/