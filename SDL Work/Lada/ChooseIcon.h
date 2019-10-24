// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog is called when the Set Default button is pressed on the Data Transfer Screen
// This allows you to toggle between Floppy and PCMCIA Card as which default you are setting

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
	void SetStrings();				// Sets the text to the current language
	BOOL * m_Floppy;				// This is returned as if the Floppy was selected
	CChooseIcon(BOOL *, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseIcon)
	enum { IDD = IDD_SELECTICON };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseIcon)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseIcon)
	virtual void OnOK();			// Called when the OK button is pressed
	virtual BOOL OnInitDialog();	// Initialization
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEICON_H__4D548041_9ACF_11D4_98E8_00A076801ACD__INCLUDED_)
