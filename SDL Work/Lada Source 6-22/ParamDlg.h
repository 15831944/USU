// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to change the parameters for the document
// ParamDlg.h : header file
//

#if !defined(AFX_PARAMDLG_H__57466686_A1AE_11D4_8BFB_0020781F78D7__INCLUDED_)
#define AFX_PARAMDLG_H__57466686_A1AE_11D4_8BFB_0020781F78D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CParamDlg dialog
class CLADAControlModuleDoc;
class CControlParameters;

class CParamDlg : public CDialog
{
// Construction
public:
	void UpdateLightSettings(BOOL In24HourMode);
	BOOL m_24Hour;
	BOOL CloseCurrentChamber();
	BOOL SetControlMode();
	void SetControlModeWindow(ControlModeType mode);
	void SetLocations();
	CControlParameters * curControlParameters;
	int m_LightOffLocation;
	int m_LightOnLocation;
	int m_MoistureLocation;
	void MakeCR10ParametersInactive();
	//BOOL IsInitialization;
	bool m_CanUpdateCR10;		// If the CR10 can be updated
	void SetStrings(BOOL = TRUE);			// Sets the text to the current language
	void SaveValues();			// This saves the values to the document
	void MakeCR10Inactive();	// This function disables the dialog
	BOOL UpdateCR10Parameters();// This function writes the parameter values to the CR10
	BOOL GetCR10Parameters();	// This function retrieves the parameters stored in the CR10
	BOOL m_ShowWetup;			// If Wetup is shown
	CLADAControlModuleDoc* pDoc;// The current document
	CParamDlg(CLADAControlModuleDoc* doc=NULL, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CParamDlg)
	enum { IDD = IDD_PARAM_DIALOG };
	CComboBox	m_cSMPFreq;
	CComboBox	m_cwChamber;
	int		m_wChamber;			// Chamber A=0 Chamber B=1;
	double	m_CR10Moisture;		// The CR10 Moisture level value
	double	m_Moisture;			// The Moisture Light Value
	int		m_CR10LightOff;
	int		m_CR10LightOn;
	int		m_LightOff;
	int		m_LightOn;
	int		m_wSMPFreq;
	int		m_CR10MaxDosage;
	int		m_MaxDosage;
	CString	m_MoistureReading;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParamDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParamDlg)
	virtual BOOL OnInitDialog();			// Initialization
	virtual void OnOK();					// Called when OK is pressed
	afx_msg void OnSelchangeSelectChamber();// Called when the Selected Chamber is changed
	afx_msg void OnUpdate();				// Called when the Update button is pressed
	afx_msg void OnLights1();
	afx_msg void OnLights2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARAMDLG_H__57466686_A1AE_11D4_8BFB_0020781F78D7__INCLUDED_)
