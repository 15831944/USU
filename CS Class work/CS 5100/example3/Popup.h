#if !defined(AFX_POPUP_H__539863BF_0724_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_POPUP_H__539863BF_0724_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Popup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Popup dialog

class Popup : public CDialog
{
// Construction
public:
	Popup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Popup)
	enum { IDD = IDD_DIALOG1 };
	CScrollBar	m_intensity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Popup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Popup)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POPUP_H__539863BF_0724_11D4_B398_00A0CC548BE4__INCLUDED_)
