#if !defined(AFX_RENAMELOCATION_H__A2E20E73_305E_11D4_98CD_00A076801ACD__INCLUDED_)
#define AFX_RENAMELOCATION_H__A2E20E73_305E_11D4_98CD_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenameLocation.h : header file
//
#include "stdafx.h"
//#include "global defs.h"


/////////////////////////////////////////////////////////////////////////////
// CRenameLocation dialog

class CRenameLocation : public CDialog
{
// Construction
public:
	CRenameLocation(const char *oName, char *nName, const char *wText, const char *title, int n, BOOL ShowNumber = TRUE, CWnd* pParent = NULL);   // standard constructor
	OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CRenameLocation)
	enum { IDD = RENAME_LOCATION };
	CStatic	m_Old_Name_CStatic;
	CStatic	m_Number_CStatic;
	CStatic	m_Win_Text_CStatic;
	CEdit	m_New_Name_CEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenameLocation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char m_oldName[30];
	char *m_newName;
	int  m_number;
	char m_windowText[30];
	char m_titleText[30];
	BOOL ShowNumberBox;

	// Generated message map functions
	//{{AFX_MSG(CRenameLocation)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENAMELOCATION_H__A2E20E73_305E_11D4_98CD_00A076801ACD__INCLUDED_)
