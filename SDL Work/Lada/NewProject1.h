// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_NEWPROJECT1_H__2F409E34_D04A_11D4_98FC_00A076801ACD__INCLUDED_)
#define AFX_NEWPROJECT1_H__2F409E34_D04A_11D4_98FC_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewProject1.h : header file
//
class CLADAControlModuleDoc;
#include "CameraData.h"

typedef char InputListType[2][30];

/////////////////////////////////////////////////////////////////////////////
// CNewProject1 dialog

class CNewProject1 : public CDialog
{
// Construction
public:
	void ResetCameraBox();
	void EnableCameras(BOOL enable);
	void SetStrings();
	CString m_DataFolder;
	InputListType InputLocationNameList[MAX_INPUT_LOCATIONS];
	int InputLocationList [MAX_INPUT_LOCATIONS];
	InputListType WInputLocationNameList[MAX_INPUT_LOCATIONS];
	int WInputLocationList [MAX_INPUT_LOCATIONS];

	void ShowVisibleSpan();
	CLADAControlModuleDoc * doc;
	BOOL m_DlgInitialized;
	CCameraData m_CameraData[2];
	CNewProject1(CLADAControlModuleDoc *d, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewProject1)
	enum { IDD = IDD_NEW_PROJECT1 };
	CComboBox	m_nGraphs;
	CComboBox	m_CNBackPoints;
	CListBox	m_CLocationList;
	CComboBox	m_CGraphPlotFreq;
	BOOL	m_DoWetup;
	int		m_curPlotFreqSel;
	int		m_curBackPointsSel;
	int		m_nGraphsSel;
	CString	m_ProjectName;
	CString	m_VisibleSpan;
	int		m_nWetupLocations;
	int		m_nCameras;
	double	m_CameraFreq;
	int		m_wCamera;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewProject1)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewProject1)
	afx_msg void OnDowetup();
	afx_msg void OnEditLocationList();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeGraphPlotFreq();
	afx_msg void OnSelchangeNBackPoints();
	afx_msg void OnWsettings();
	afx_msg void OnNext();
	afx_msg void OnEditWetupLocationList();
	afx_msg void OnSelchangeWCamera();
	afx_msg void OnChangeNCameras();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPROJECT1_H__2F409E34_D04A_11D4_98FC_00A076801ACD__INCLUDED_)
