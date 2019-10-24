#if !defined(AFX_SELECTTESTOBJECT_H__1C5E3AE0_5BB6_11D4_B01D_A7BF98E57D33__INCLUDED_)
#define AFX_SELECTTESTOBJECT_H__1C5E3AE0_5BB6_11D4_B01D_A7BF98E57D33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectTestObject.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelectTestObject dialog

class SelectTestObject : public CDialog
{
// Construction
public:
	SelectTestObject(CString *words, int *position, int &nItems, BOOL IsDelete = FALSE, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelectTestObject)
	enum { IDD = IDD_DIALOG3 };
	CStatic	m_NumSelected;
	CListBox	m_List1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelectTestObject)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_IsDelete;
	int *m_NItems;
	int *m_Object;
	CString *m_TArray;
	int m_curSel;
	// Generated message map functions
	//{{AFX_MSG(SelectTestObject)
	afx_msg void OnSelchangeList1();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTTESTOBJECT_H__1C5E3AE0_5BB6_11D4_B01D_A7BF98E57D33__INCLUDED_)
