#if !defined(AFX_INSTRUCTIONS2DLG_H__EACAA510_53B6_11D5_A51E_444553540000__INCLUDED_)
#define AFX_INSTRUCTIONS2DLG_H__EACAA510_53B6_11D5_A51E_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Instructions2Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInstructions2Dlg dialog

class CInstructions2Dlg : public CDialog
{
// Construction
public:
	CInstructions2Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInstructions2Dlg)
	enum { IDD = IDD_INSTRUCTIONS2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstructions2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInstructions2Dlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTRUCTIONS2DLG_H__EACAA510_53B6_11D5_A51E_444553540000__INCLUDED_)
