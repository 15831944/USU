#if !defined(AFX_FIND_H__9DE30AC0_CF2C_11D4_8BFB_0020781F78D7__INCLUDED_)
#define AFX_FIND_H__9DE30AC0_CF2C_11D4_8BFB_0020781F78D7__INCLUDED_

#include "String EditorDoc.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Find.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFind dialog

class CFind : public CDialog
{
// Construction
public:
	BOOL IsInside(CString a, CString b);
	CStringEditorDoc* pDoc;
	CFind(CStringEditorDoc* pDoc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFind)
	enum { IDD = IDD_CFIND };
	BOOL	m_label;
	BOOL	m_string;
	CString	m_find;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFind)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIND_H__9DE30AC0_CF2C_11D4_8BFB_0020781F78D7__INCLUDED_)
