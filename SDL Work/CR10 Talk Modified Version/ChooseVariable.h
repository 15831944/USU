#if !defined(AFX_CHOOSEVARIABLE_H__058F2162_5CDF_11D4_98D6_00A076801ACD__INCLUDED_)
#define AFX_CHOOSEVARIABLE_H__058F2162_5CDF_11D4_98D6_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseVariable.h : header file
//

#include "Event.h"

/////////////////////////////////////////////////////////////////////////////
// CChooseVariable dialog

class CChooseVariable : public CDialog
{
// Construction
public:
	CChooseVariable(Array<ExpressionItem *> *PVars, Array<Event> *PEvents, ExpressionItem *&var, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseVariable)
	enum { IDD = IDD_CHOOSE_VARIABLE };
	CStatic	m_VarValueText;
	CEdit	m_VarValue;
	CEdit	m_ConstVar;
	CButton	m_Delete;
	CComboBox	m_Event;
	CButton	m_New;
	CListCtrl	m_EventVar;
	CListCtrl	m_ProgVar;
	CButton	m_Edit;
	double	m_ConstValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseVariable)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	enum VarTypes {ConstValue, EventExp, ProgVar, NoSelection};
	VarTypes curVarType;
	BOOL EventSelected;
	BOOL ProgVarSelected;
	int curEventNum;
	Array<ExpressionItem *> *ProgVariables;
	Array<Event> *ProgEvents;
	Event *curEvent;
	ExpressionItem **newVariable;
	void ShowCurrentEventInfo();
	void SetControls();
	void ClickList(CListCtrl &wList);
	void ShowCurrentVariableInfo();
	// Generated message map functions
	//{{AFX_MSG(CChooseVariable)
	afx_msg void OnDelete();
	afx_msg void OnEdit();
	afx_msg void OnSelchangeEvent();
	afx_msg void OnNew();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio3();
	afx_msg void OnClickEventVar(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickProgVar(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEVARIABLE_H__058F2162_5CDF_11D4_98D6_00A076801ACD__INCLUDED_)
