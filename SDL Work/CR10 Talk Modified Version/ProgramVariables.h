#if !defined(AFX_PROGRAMVARIABLES_H__0F851860_6319_11D4_B01D_9FFD8DCC6234__INCLUDED_)
#define AFX_PROGRAMVARIABLES_H__0F851860_6319_11D4_B01D_9FFD8DCC6234__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgramVariables.h : header file
//
#include "array.h"
#include "Event.h"

/////////////////////////////////////////////////////////////////////////////
// ProgramVariables dialog

class ProgramVariables : public CDialog
{
// Construction
public:
	ProgramVariables(Array<ExpressionItem *> *pVars, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ProgramVariables)
	enum { IDD = IDD_PROGRAM_VARIABLES };
	CListCtrl	m_VList;
	BOOL	m_ReadOnly;
	BOOL	m_Array;
	CString	m_VName;
	double	m_VValue;
	int		m_NElements;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProgramVariables)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Array<ExpressionItem *> *ProgVariables;
	int nVariables;

	void ShowVariableList();
	// Generated message map functions
	//{{AFX_MSG(ProgramVariables)
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnEdit();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRAMVARIABLES_H__0F851860_6319_11D4_B01D_9FFD8DCC6234__INCLUDED_)
