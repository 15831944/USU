#if !defined(AFX_EDITCONDITION_H__0044F605_46BB_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_EDITCONDITION_H__0044F605_46BB_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditCondition.h : header file
//
#include "resource.h"
#include "Event.h"

/////////////////////////////////////////////////////////////////////////////
// EditExpression dialog

class EditExpression : public CDialog
{
// Construction
public:

	EditExpression(Array<Event> *pEvents, Event *cEvent, Expression &whichExpression, CWnd *pParent, char *expDesc = NULL);   // standard constructor
	BOOL OnInitDialog();//used to initialize dialog box
// Dialog Data
	//{{AFX_DATA(EditExpression)
	enum { IDD = IDD_EDIT_CONDITION };
	CEdit	m_ExpDescWnd;
	CEdit	m_Value;
	CSpinButtonCtrl	m_Spin1;
	CEdit	m_EditNumber;
	CEdit	m_CStatement;
	CStatic	m_DirectionText;
	CComboBox	m_Variable;
	CListBox	m_Item_List;
	CString	m_ExpDescription;
	double	m_Double;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditExpression)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Expression *curExpression;
	const Event *curEvent;
	int curItem; // position of highlighted text in edit box
	Array<Event> *progEvents;
	BOOL IsEventSelected;
	Event *EventSelected;
	
	CString condText;
	int TextPos[20]; // 20 - max number of expression items
	void ShowHighlightedItem();
	void ShowExpression(CWnd * textWnd, Expression * whichExp );
	void ShowItem(CWnd * textWnd, ExpressionItem * eItem);
	
	// Generated message map functions
	//{{AFX_MSG(EditExpression)
	afx_msg void OnSelchangeItemList();
	afx_msg void OnInsert();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnEvaluate();
	virtual void OnOK();
	afx_msg void OnSelchangeVariable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCONDITION_H__0044F605_46BB_11D4_98D1_00A076801ACD__INCLUDED_)
