#if !defined(AFX_CHOOSEITEM_H__3E1062E3_46E4_11D4_98D1_00A076801ACD__INCLUDED_)
#define AFX_CHOOSEITEM_H__3E1062E3_46E4_11D4_98D1_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseItem.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CChooseItem dialog

class CChooseItem : public CDialog
{
// Construction
public:
	CChooseItem(int *whichItem, int nItems, CString Items[], const char * DlgTitle = NULL, CWnd* pParent = NULL);   // standard constructor
	BOOL OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CChooseItem)
	enum { IDD = IDD_CHOOSE_ITEM };
	CComboBox	m_ListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseItem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int *CurSel;
	char DialogTitle[50];
	CString *PtrStrings;
	int NumberItems;
	// Generated message map functions
	//{{AFX_MSG(CChooseItem)
	virtual void OnCancel();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEITEM_H__3E1062E3_46E4_11D4_98D1_00A076801ACD__INCLUDED_)
