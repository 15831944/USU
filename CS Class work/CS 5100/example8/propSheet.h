#if !defined(AFX_PROPSHEET_H__538B8BE2_BFBF_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_PROPSHEET_H__538B8BE2_BFBF_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// propSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CpropSheet
#include "Page1.h"
#include "Page2.h"

class CpropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CpropSheet)

// Construction
public:
	CpropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CpropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CPage1 m_page1;
	CPage2 m_page2;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CpropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CpropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CpropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSHEET_H__538B8BE2_BFBF_11D4_B398_00A0CC548BE4__INCLUDED_)
