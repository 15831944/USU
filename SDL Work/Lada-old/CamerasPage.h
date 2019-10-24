#if !defined(AFX_CAMERASPAGE_H__4D1AD4AB_2CE3_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_CAMERASPAGE_H__4D1AD4AB_2CE3_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CamerasPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamerasPage dialog

class CCamerasPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCamerasPage)

// Construction
public:
	void SetCameraData(BOOL Update);
	BOOL IsModified;
	void SetModified(BOOL=TRUE);
	CCamerasPage();
	~CCamerasPage();

	void ApplyCameraChanges(int wChamber);         // camera page
	void SetTimeSensitiveCameraData();			   // camera page
	void EnableCameras(BOOL enable);				// camera page
	void SetStrings(BOOL updateData = TRUE);		// all
	void SetDocument(CLADAControlModuleDoc * doc);

	CDataCollectionStatusDlg(CLADAControlModuleDoc * pDoc, CWnd* pParent = NULL);   // standard constructor

	CLADAControlModuleDoc * pDoc;					// all

// Dialog Data
	//{{AFX_DATA(CCamerasPage)
	enum { IDD = IDD_PAGE_CAMERAS };
	CComboBox	m_cChamber;
	CString	m_cFreq;
	BOOL	m_IsCameraEnabled;
	int		m_wChamber;
	int		m_nCameras;
	CString	m_cameraFrequency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCamerasPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCamerasPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeWChamber();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEnableCamera();
	afx_msg void OnChangeNCameras();
	afx_msg void OnChangeFreq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERASPAGE_H__4D1AD4AB_2CE3_11D5_B690_0080AD8FBDCC__INCLUDED_)
