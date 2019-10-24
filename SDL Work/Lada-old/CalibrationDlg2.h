#if !defined(AFX_CALIBRATIONDLG2_H__9746F4E1_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_)
#define AFX_CALIBRATIONDLG2_H__9746F4E1_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalibrationDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg2 dialog

class CCalibrationDlg2 : public CDialog
{
// Construction
public:
	CCalibrationDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCalibrationDlg2)
	enum { IDD = IDD_CALIBRATE2 };
	CString	m_Group;
	CString	m_Name;
	double	m_Reading;
	double	m_KnownValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibrationDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalibrationDlg2)
	afx_msg void OnReCalibrate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATIONDLG2_H__9746F4E1_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_)
