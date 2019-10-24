#if !defined(AFX_MANUALCONTROL_H__2C182400_072D_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_MANUALCONTROL_H__2C182400_072D_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ManualControl.h : header file
//
#include "LADA Control ModuleDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CManualControl dialog

class CManualControl : public CDialog
{
// Construction
public:
	BOOL ControlCR10( CR10ControlType Lights = NoChange, CR10ControlType Fans = NoChange,
		CR10ControlType Pump1 = NoChange, CR10ControlType Pump2 = NoChange);
	void OnCR10Control(UINT nID);
	CLADAControlModuleDoc * pDoc;
	CManualControl(CLADAControlModuleDoc * doc, CWnd* pParent = NULL);   // standard constructor
	~CManualControl();
	BOOL Create(UINT nID, CWnd * pWnd = NULL)
        { return CDialog::Create(nID,pWnd);}

// Dialog Data
	//{{AFX_DATA(CManualControl)
	enum { IDD = IDD_MANUAL_CONTROL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CManualControl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void RefreshControls();
	void SetChamberRadio();
	int curChamber;
	void SetStrings();

	// Generated message map functions
	//{{AFX_MSG(CManualControl)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnChamberA();
	afx_msg void OnChamberB();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MANUALCONTROL_H__2C182400_072D_11D5_B690_0080AD8FBDCC__INCLUDED_)
