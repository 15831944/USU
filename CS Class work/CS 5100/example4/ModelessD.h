#if !defined(AFX_MODELESSD_H__3C7EB0E0_0AD3_11D4_949F_000086520C5B__INCLUDED_)
#define AFX_MODELESSD_H__3C7EB0E0_0AD3_11D4_949F_000086520C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelessD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ModelessD dialog

class ModelessD : public CDialog
{
// Construction
public:
	ModelessD(CWnd* pParent = NULL);   // standard constructor
	BOOL Create();
// Dialog Data
	//{{AFX_DATA(ModelessD)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModelessD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd * m_pParent;
	int m_nID;
	// Generated message map functions
	//{{AFX_MSG(ModelessD)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESSD_H__3C7EB0E0_0AD3_11D4_949F_000086520C5B__INCLUDED_)
