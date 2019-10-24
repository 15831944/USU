// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to display the values of certain input locations and check to see if they 
//		are within certain bounds.
// SystemDiagDlg.h : header file
//

#if !defined(AFX_SYSTEMDIAGDLG_H__C5B6915A_D38F_4409_8ED5_9CB7214D24BF__INCLUDED_)
#define AFX_SYSTEMDIAGDLG_H__C5B6915A_D38F_4409_8ED5_9CB7214D24BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSystemDiagDlg dialog
class CLADAControlModuleDoc;
class CInputLocFileInfo;

class CSystemDiagDlg : public CDialog
{
// Construction
public:
	void ValidateAll();
	void SetCheckedItems();
	void GetCheckedItems();
	BOOL m_ShowBottomControls;
	void ResetGroupTimer();
	void ResetStrings();
	BOOL IsAutomatic;
	void SetStrings();					// Sets the text to the current language
	void SetGroupInfo();				// Sets the new list information 
	double * m_ptrReturnData;			// Returns the data collected
	int m_nIList;						// The number of input locations in the group
	int * m_InputList;					// The list of input locations in the group
	int * m_InputLocationIndex;
	BOOL m_ShowTopControls;			// Are changes allowed?
	void load();						// loads a group and displays the information
	double* values;						// The list of values of the input locations
	void GetValues();					// Gets the values that are requested
	CInputLocFileInfo* fileinfo;		// The information that stores each group
	CLADAControlModuleDoc * pDoc;		// The current document
	CSystemDiagDlg(CLADAControlModuleDoc *doc, int group,  BOOL allowChangeGroup = TRUE,
		int * ILs = NULL, int nGroup = 0, double *ptrReturnData = NULL, BOOL isauto = FALSE,
		BOOL showSave = TRUE,  CWnd* pParent = NULL);	// standard constructor
	~CSystemDiagDlg();					// Destructor
// Dialog Data
	//{{AFX_DATA(CSystemDiagDlg)
	enum { IDD = IDD_SYSTEMDIAG_DIALOG };
	CComboBox	m_cGroup;
	CListCtrl	m_cdiag;
	int		m_wGroup;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSystemDiagDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSystemDiagDlg)
	virtual BOOL OnInitDialog();									// Initialization
	afx_msg void OnSave();											// Saves your info to a file
	afx_msg void OnSelect();										// Does Something
	virtual void OnOK();											// Exits
	afx_msg void OnDblclkDiaglist(NMHDR* pNMHDR, LRESULT* pResult);	// Allows you to set the bounds for an input location
	afx_msg void OnProperties();									// Allows you to change the properties of a group	
	afx_msg void OnSelchangeGroup();								// Select a different group
	afx_msg void OnCreatenewgroup();								// Allows you to create a new group to be displayed
	afx_msg void OnLoadValidation();
	afx_msg void OnValidateAll();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMDIAGDLG_H__C5B6915A_D38F_4409_8ED5_9CB7214D24BF__INCLUDED_)
