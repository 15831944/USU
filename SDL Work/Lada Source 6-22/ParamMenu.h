#if !defined(AFX_PARAMMENU_H__9746F4E5_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_)
#define AFX_PARAMMENU_H__9746F4E5_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParamMenu.h : header file
//

class CLADAControlModule;
/////////////////////////////////////////////////////////////////////////////
// CParamMenu dialog

class CParamMenu : public CDialog
{
// Construction
public:
	CLADAControlModuleDoc * pDoc;
	CParamMenu(CLADAControlModuleDoc *doc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParamMenu)
	enum { IDD = IDD_PARAM_MENU };
	CStatic	m_modeWindow;
	BOOL	m_DisplayManualDlg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamMenu)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void MakeCR10Inactive();
	void SetStrings();
	void SetControlModeWindow(ControlModeType mode);
	BOOL SetControlMode();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParamMenu)
	afx_msg void OnDisplayWindow();
	afx_msg void OnCr10Functions();
	afx_msg void OnDataCollection();
	afx_msg void OnParams();
	afx_msg void OnCalibration();
	virtual BOOL OnInitDialog();
	afx_msg void OnSwitchMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMMENU_H__9746F4E5_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_)
