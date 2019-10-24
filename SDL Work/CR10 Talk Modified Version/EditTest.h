#if !defined(AFX_EDITTEST_H__65B36009_570E_11D4_B01D_F4465DBDD92D__INCLUDED_)
#define AFX_EDITTEST_H__65B36009_570E_11D4_B01D_F4465DBDD92D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditTest.h : header file
//

#include "resource.h"
#include "Event.h"
#include "SelectTestObject.h"

/////////////////////////////////////////////////////////////////////////////
// EditTest dialog

class EditTest : public CDialog
{
// Construction
public:
	EditTest(Array<ExpressionItem *> *PVariables, Array<Event> *pEvents, Event *cEvent, Test &whichTest, int TestNum, CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(EditTest)
	enum { IDD = IDD_EDIT_TEST };
	CButton	m_FullExpression;
	CComboBox	m_TestNum;
	CStatic	m_TestText;
	CListCtrl	m_Test;
	CListCtrl	m_Choices;
	CListBox	m_Items;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Test * curTest;
	const Event * curEvent;
	int nChoices[5];// = {3,x,3,2,8};
	int curTestNum;
	enum MenuChoices {ControlStatement,EventExpression,BooleanOperator,Parenthesis, ActionChoice, NullChoice};

	void ShowChoices(MenuChoices m);
	void ShowCurrentTestInfo();
	void ClickList(CListCtrl &wList);
	void FillMenuBox();
	void SelectControl();

	int curFlow;
	BOOL ShowFull;
	int controlPos[20];
	BOOL IsChoiceAvailable[5];
	MenuChoices curChoice;
	Array<ExpressionItem *> *ProgVariables;
	Array<Event> *progEvents;

	// Generated message map functions
	//{{AFX_MSG(EditTest)
	afx_msg void OnInsert();
	virtual void OnOK();
	afx_msg void OnDelete();
	afx_msg void OnSelchangeTests();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeItems();
	afx_msg void OnFullExpression();
	afx_msg void OnClickTest(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownTest(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITTEST_H__65B36009_570E_11D4_B01D_F4465DBDD92D__INCLUDED_)
