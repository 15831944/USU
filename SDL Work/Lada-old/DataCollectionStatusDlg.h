#if !defined(AFX_DATACOLLECTIONSTATUSDLG_H__0DB30821_F251_11D4_9900_00A076801ACD__INCLUDED_)
#define AFX_DATACOLLECTIONSTATUSDLG_H__0DB30821_F251_11D4_9900_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataCollectionStatusDlg.h : header file
//

class CLADAControlModuleDoc;
class CFSInfo;

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionStatusDlg dialog

class CDataCollectionStatusDlg : public CDialog
{
// Construction
public:
	
	void ApplyCameraChanges(int wChamber);         // camera page
	void SetTimeSensitiveCameraData();			   // camera page
	void EnableCameras(BOOL enable);				// camera page

	void SetTimeSensitiveChamberData();				// final storage
	void EnableFinalStorage(BOOL enable = FALSE);	// final storage
	void SetChamberData(BOOL updateData = TRUE);	// final storage

	void ResetGroupTimer();							// input locations page
	void SetTimeSensitiveLocationsData();			// input locations page
	void EnableInputLocations(BOOL enable);			// input locations page
	void SetLocationsData(BOOL updateData = TRUE);	// input locations page
	
	void SetStrings(BOOL updateData = TRUE);		// all
	
	CDataCollectionStatusDlg(CLADAControlModuleDoc * pDoc, CWnd* pParent = NULL);   // standard constructor

	bool freqChanged[2];							// camera page
	int m_InitialFSFreq;							// final storage
	CFSInfo * m_ptrFSInfo;							// final storage
	CLADAControlModuleDoc * pDoc;					// all
// Dialog Data
	//{{AFX_DATA(CDataCollectionStatusDlg)
	enum { IDD = IDD_COLLECTION };
	CComboBox	m_cGroup;
	CListCtrl	m_InputLocations;
	CListBox	m_FSList;
	int		m_wChamber;
	int		m_wFSFrequency;
	int		m_NewFSFrequency;
	int		m_ArrayID;
	int		m_wGroup;
	BOOL	m_IsCameraEnabled;
	CString	m_cFreq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataCollectionStatusDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataCollectionStatusDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnProperties();
	afx_msg void OnNew();
	afx_msg void OnImportFsl();
	afx_msg void OnSelchangeWChamber();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnSelchangeNewFsFile();
	afx_msg void OnChangeArrayId();
	afx_msg void OnEnableCamera();
	afx_msg void OnChangeCFrequency();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATACOLLECTIONSTATUSDLG_H__0DB30821_F251_11D4_9900_00A076801ACD__INCLUDED_)
