#if !defined(AFX_EDITEVENT_H__2CE522F2_4631_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_EDITEVENT_H__2CE522F2_4631_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditEvent.h : header file
//
#include "Array.h"
#include "Event.h"

#define	NOEVENTS			0xFFFFFFFF
#define STATEMENTSELECTED	0x00000001
#define NEWSTATEMENTS		0x00000002
#define TESTSELECTED		0x00000004
#define NEWTESTS			0x00000008
#define EVENTENABLED		0x00000010
#define EVERYTHING			0xEFFFFFFF

/////////////////////////////////////////////////////////////////////////////
// EditEvent dialog

class EditEvent : public CDialog
{
// Construction
public:
	EditEvent(Array<ExpressionItem *> *PVariables, Array<Event> *Events, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditEvent)
	enum { IDD = IDD_EDIT_EVENT };
	CListCtrl	m_CtrlList;
	CListCtrl	m_ExpList;
	CButton	m_RenameEvent;
	CButton	m_NewTest;
	CButton	m_NewStatement;
	CButton	m_NewEvent;
	CButton	m_EditTest;
	CButton	m_EditStatement;
	CButton	m_DeleteTest;
	CButton	m_DeleteStatement;
	CComboBox	m_EventTitle;
	CStatic	m_EventNumber;
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
	DWORD wStatus;
	Array<ExpressionItem *> *ProgVariables; 
	int testPos[20];
	
	void ShowCurrentEventInfo();
	void SetButtonStatus(DWORD dwFlags);
	void ClickList(CListCtrl &wList, DWORD mask);

	
	// Generated message map functions
	//{{AFX_MSG(EditEvent)
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
	afx_msg void OnClickExpressionList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickControlList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnProgramVariables();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITEVENT_H__2CE522F2_4631_11D4_98D1_00A076801ACD__INCLUDED_)
