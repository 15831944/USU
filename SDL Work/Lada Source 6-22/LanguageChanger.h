// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to change the language
#if !defined(AFX_LANGUAGECHANGER_H__9D5D9380_A71E_11D4_8BFB_0020781F78D7__INCLUDED_)
#define AFX_LANGUAGECHANGER_H__9D5D9380_A71E_11D4_8BFB_0020781F78D7__INCLUDED_

#include "LString.h"	// Added by ClassView
#include "Resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LanguageChanger.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LanguageChanger dialog


class LanguageChanger : public CDialog
{
// Construction
public:
	void SetStrings();
	LanguageChanger(CWnd* pParent = NULL);		// standard constructor

// Dialog Data
	//{{AFX_DATA(LanguageChanger)
	enum { IDD = IDD_LANGUAGE };
	CListBox	m_Languages;					// The control for the list box
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LanguageChanger)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LanguageChanger)
	virtual void OnOK();						//Called when Ok is press
	virtual BOOL OnInitDialog();				//Initializes dialog
	afx_msg void OnDblclkList1();				//Called when an item is doubleclicked
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANGUAGECHANGER_H__9D5D9380_A71E_11D4_8BFB_0020781F78D7__INCLUDED_)
