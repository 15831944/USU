#if !defined(AFX_SETFREQUENCYDLG_H__D43EA460_3EDC_11D5_B691_0080AD8FBDCC__INCLUDED_)
#define AFX_SETFREQUENCYDLG_H__D43EA460_3EDC_11D5_B691_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetFrequencyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetFrequencyDlg dialog

class CSetFrequencyDlg : public CDialog
{
// Construction
public:
	void SetStrings();
	CTimeSpan * m_TimeSpan;
	CSetFrequencyDlg(CTimeSpan * ptrFreq, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetFrequencyDlg)
	enum { IDD = IDD_SET_FREQUENCY };
	int		m_Hours;
	int		m_Minutes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetFrequencyDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetFrequencyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETFREQUENCYDLG_H__D43EA460_3EDC_11D5_B691_0080AD8FBDCC__INCLUDED_)
