#if !defined(AFX_MYBUTTON_H__348F2AC3_0721_11D4_949F_000086520C5B__INCLUDED_)
#define AFX_MYBUTTON_H__348F2AC3_0721_11D4_949F_000086520C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyButton window

class MyButton : public CButton
{
// Construction
public:
	MyButton();

// Attributes
public:
int dialogNumber;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyButton)
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBUTTON_H__348F2AC3_0721_11D4_949F_000086520C5B__INCLUDED_)
