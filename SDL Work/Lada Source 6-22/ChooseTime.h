#if !defined(AFX_CHOOSETIME_H__A3F27220_7522_11D4_B01E_D7AFDCC2832D__INCLUDED_)
#define AFX_CHOOSETIME_H__A3F27220_7522_11D4_B01E_D7AFDCC2832D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChooseTime dialog


class CChooseTime : public CDialog
{
// Construction
public:
	void SetStrings();
	CChooseTime(CTime *pDate, CTime *pTime, CWnd* pParent = NULL);   // standard constructor
	CTime *m_pDate;
	CTime *m_pTime;
// Dialog Data
	//{{AFX_DATA(CChooseTime)
	enum { IDD = IDD_CHOOSE_TIME };
	CTime	m_Date;
	CTime	m_Time;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseTime)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChooseTime)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSETIME_H__A3F27220_7522_11D4_B01E_D7AFDCC2832D__INCLUDED_)
