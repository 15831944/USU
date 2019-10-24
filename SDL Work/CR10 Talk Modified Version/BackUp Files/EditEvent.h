#if !defined(AFX_EDITEVENT_H__2CE522F2_4631_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_EDITEVENT_H__2CE522F2_4631_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEvent.h : header file
//
#include "Array.h"
#include "Event.h"

/////////////////////////////////////////////////////////////////////////////
// EditEvent dialog

class EditEvent : public CDialog
{
// Construction
public:
	EditEvent(Array<Event> *Events, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditEvent)
	enum { IDD = IDD_EDIT_EVENT };
	CListBox	m_CtrlList;
	CListBox	m_ExpList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditEvent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Array<Event> *Events;
	Event *curEvent;
	int whichEvent;
	
	void ShowCurrentEventInfo();
	
	// Generated message map functions
	//{{AFX_MSG(EditEvent)
	afx_msg void OnSelchangeExpressionList();
	afx_msg void OnDblclkExpressionList();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnDeleteStatement();
	afx_msg void OnDeleteTest();
	afx_msg void OnSelchangeEventTitle();
	afx_msg void OnNewEvent();
	afx_msg void OnNewTest();
	virtual void OnCancel();
	afx_msg void OnHelp();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditStatement();
	afx_msg void OnEditTest();
	afx_msg void OnRenameEvent();
	afx_msg void OnNewStatement();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITEVENT_H__2CE522F2_4631_11D4_98D1_00A076801ACD__INCLUDED_)
