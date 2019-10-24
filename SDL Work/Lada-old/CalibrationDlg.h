#if !defined(AFX_CALIBRATIONDLG_H__9746F4E0_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_)
#define AFX_CALIBRATIONDLG_H__9746F4E0_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CalibrationDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCalibrationDlg dialog

#define N_LANGUAGES	2
#define MAX_GROUPS	20
#define MAX_PROBES	20
class CLADAControlModuleDoc;

class CCalibrationDlg : public CDialog
{
// Construction
public:
	void ShowGroupData();
	int nGroups;
	CString (*groupNames)[N_LANGUAGES];//= new (CString[2])[20];
	CString (*probeNames)[MAX_GROUPS][N_LANGUAGES];
	int * probesPerGroup;
	int (*offset_location)[MAX_GROUPS];
	int (*data_location)[MAX_GROUPS];
	CLADAControlModuleDoc * pDoc;
	CCalibrationDlg(CLADAControlModuleDoc * doc, CWnd* pParent = NULL);   // standard constructor
	~CCalibrationDlg();
// Dialog Data
	//{{AFX_DATA(CCalibrationDlg)
	enum { IDD = IDD_CALIBRATION };
	CComboBox	m_cwGroup;
	CListCtrl	m_Sensors;
	int		m_wGroup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalibrationDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCalibrationDlg)
	afx_msg void OnLoadFile();
	afx_msg void OnCalibrate();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeWGroup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALIBRATIONDLG_H__9746F4E0_3D9C_11D5_B691_0080AD8FBDCC__INCLUDED_)
