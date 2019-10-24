#if !defined(AFX_CHOOSEICON_H__4D548041_9ACF_11D4_98E8_00A076801ACD__INCLUDED_)
#define AFX_CHOOSEICON_H__4D548041_9ACF_11D4_98E8_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseIcon.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseIcon dialog

class CChooseIcon : public CDialog
{
// Construction
public:
	BOOL * m_Floppy;
	CChooseIcon(BOOL *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseIcon)
	enum { IDD = IDD_SELECTICON };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseIcon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseIcon)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEICON_H__4D548041_9ACF_11D4_98E8_00A076801ACD__INCLUDED_)
