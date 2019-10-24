#if !defined(AFX_NEWEVENT_H__44F346C2_5630_11D4_B01D_C4D4B1D9302A__INCLUDED_)
#define AFX_NEWEVENT_H__44F346C2_5630_11D4_B01D_C4D4B1D9302A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewEvent.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// NewEvent dialog

class NewEvent : public CDialog
{
// Construction
public:
	NewEvent(char *newTitle, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(NewEvent)
	enum { IDD = IDD_NEW_EVENT };
	CEdit	m_Edit1;
	CString	m_EventTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NewEvent)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	char *AddTitle;
	// Generated message map functions
	//{{AFX_MSG(NewEvent)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWEVENT_H__44F346C2_5630_11D4_B01D_C4D4B1D9302A__INCLUDED_)
