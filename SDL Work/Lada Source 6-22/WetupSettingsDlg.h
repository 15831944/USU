// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_WETUPSETTINGSDLG_H__30C4ACC1_B1E7_11D4_98EB_00A076801ACD__INCLUDED_)
#define AFX_WETUPSETTINGSDLG_H__30C4ACC1_B1E7_11D4_98EB_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WetupSettingsDlg.h : header file
//
class CLADAControlModuleDoc;
/////////////////////////////////////////////////////////////////////////////
// CWetupSettingsDlg dialog

class CWetupSettingsDlg : public CDialog
{
// Construction
public:
	void SetStrings();
	BOOL IsAutomatic;
	CLADAControlModuleDoc * pDoc;

	BOOL UpdateEstimates(BOOL UpdateTime = TRUE);
	CWetupSettingsDlg(CLADAControlModuleDoc * pDoc=NULL,BOOL AUTO=FALSE,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWetupSettingsDlg)
	enum { IDD = IDD_WETUPSETTINGS };
	CEdit	m_cHours;
	CEdit	m_cMinutes;
	CEdit	m_cVToPump;
	CEdit	m_cVPBurst;
	CEdit	m_cFreqBurst;
	int		m_FBurst;
	CString	m_eWetupTime;
	CString	m_eBurstLength;
	int		m_vToPump;
	UINT	m_Hours;
	UINT	m_Minutes;
	double	m_VBurst;
	int		m_VolumePumped;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWetupSettingsDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWetupSettingsDlg)
	afx_msg void OnChangeVtopump();
	afx_msg void OnChangeVpburst();
	afx_msg void OnChangeFburst();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnChangeTime();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WETUPSETTINGSDLG_H__30C4ACC1_B1E7_11D4_98EB_00A076801ACD__INCLUDED_)
