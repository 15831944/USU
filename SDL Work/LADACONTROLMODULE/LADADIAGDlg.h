// LADADIAGDlg.h : header file
//

#if !defined(AFX_LADADIAGDLG_H__BBF6AD86_8A41_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_LADADIAGDLG_H__BBF6AD86_8A41_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CLADADIAGDlg dialog

class CLADADIAGDlg : public CDialog
{
// Construction
public:
	//CCommOperations* commobject;
	CImageList DiagnosticList;
	bool CheckVoltage();
	bool CheckMemory();
	bool CheckUploadTime();
	bool CheckMultiplexerPower();
	bool CheckVoltageChannels();
	bool CheckGrowthPower();
	bool CheckReadSensors();
	bool CheckSoilProbe();
	void OnInit();
	void SetStatus(int,BOOL);
	CLADADIAGDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLADADIAGDlg)
	enum { IDD = IDD_LADADIAG_DIALOG };
	CListCtrl	m_DiagnosticList;
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
	afx_msg void OnStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADADIAGDLG_H__BBF6AD86_8A41_11D4_A864_0000E880BB29__INCLUDED_)
