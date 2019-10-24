#if !defined(AFX_ADDEVENTDLG_H__5993CAA2_A8E6_11D5_B509_000086204AC6__INCLUDED_)
#define AFX_ADDEVENTDLG_H__5993CAA2_A8E6_11D5_B509_000086204AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddEventDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddEventDlg dialog

class CAddEventDlg : public CDialog
{
// Construction
public:
	CAddEventDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddEventDlg)
	enum { IDD = IDD_ADD_EVENT_DLG };
	CString	m_location;
	CString	m_description;
	short	m_duration;
	CString	m_name;
	CString	m_note;
	CTime	m_Date;
	CTime	m_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddEventDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddEventDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDEVENTDLG_H__5993CAA2_A8E6_11D5_B509_000086204AC6__INCLUDED_)
