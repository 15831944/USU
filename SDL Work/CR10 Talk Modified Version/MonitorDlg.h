#if !defined(AFX_MONITORDLG_H__A2E20E72_305E_11D4_98CD_00A076801ACD__INCLUDED_)
#define AFX_MONITORDLG_H__A2E20E72_305E_11D4_98CD_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorDlg.h : header file
//
#include "global defs.h"
#include "stdafx.h"
#include "CR10 Talk Main.h"




/////////////////////////////////////////////////////////////////////////////
// CMonitorDlg dialog

class CMonitorDlg : public CDialog
{
// Construction
public:
	CMonitorDlg(CMainWindow* pParent = NULL);   // standard constructor
	BOOL OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CMonitorDlg)
	enum { IDD = MONITOR_DIALOG };
	CButton	m_SaveFS;
	CStatic	m_sText2;
	CStatic	m_sText3;
	CStatic	m_lText1;
	CComboBox	m_Save_Locations_Freq;
	CEdit	m_sEdit1;
	CStatic	m_sText1;
	CButton	m_Save_Locations;
	CStatic	m_mText1;
	CListBox	m_Selected_Locations;
	CButton	m_Rename;
	CButton	m_Remove;
	CButton	m_Insert;
	CComboBox	m_Input_Locations_Freq;
	CComboBox	m_CR10_Info_Freq;
	CListBox	m_Available_Locations;
	CButton	m_Input_Locations;
	CButton	m_CR10_Info;
	int		m_LSValue;
	BOOL	m_SaveFinalStorage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void OnSelchangeFreq( CComboBox & whichFreq, int whichID );
	void OnCheck(CButton &whichButton, CComboBox &whichBox, int whichID);
	void RenameB(int whichLocation);
	void ShowInputLocations(BOOL Check);
	void ShowCR10Info(BOOL Check);
	void ShowSaveLocations(BOOL Check);

	int TFreqLevel[N_UPDATEABLE_ITEMS];
	BOOL TUpdateItems[N_UPDATEABLE_ITEMS];
	int TInputLocScreenRequests;
	int TInputLocSaveRequests;
	int TInputLocScreenList[MAX_DISPLAY_INPUT_LOCATIONS];
	CString TAvailableInputLocations[MAX_INPUT_LOCATIONS];
	CMainWindow *pParentWindow;
	// Generated message map functions
	//{{AFX_MSG(CMonitorDlg)
	afx_msg void OnCr10InfoC();
	afx_msg void OnInputLocationsC();
	afx_msg void OnSelchangeCr10InfoFreq();
	afx_msg void OnSelchangeInputLocationsFreq();
	afx_msg void OnDblclkAvailableLocationsL();
	afx_msg void OnDblclkSelectedLocationsL();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnRenameB();
	afx_msg void OnInsertB();
	afx_msg void OnRemoveB();
	afx_msg void OnSortLocations();
	afx_msg void OnFslFile();
	afx_msg void OnSaveLocationsC();
	afx_msg void OnSelchangeSaveLocationsFreq();
	afx_msg void OnSaveFs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORDLG_H__A2E20E72_305E_11D4_98CD_00A076801ACD__INCLUDED_)
