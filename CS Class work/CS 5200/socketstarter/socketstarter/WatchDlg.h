// WatchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg dialog
#ifndef __WATCHDLG_H
#define __WATCHDLG_H

class CWatchDlg : public CDialog
{
// Construction
public:

	void DisplayStatus(const CString& text);
	void SetSocket(CAsyncSocket* s) { sock = s; }
	void ShowData(const CString& text);
	void ShowData(const char* buffer, int lng)
		{ if (buffer!=NULL && lng>0) ShowData(CString(buffer,lng)); }
    BOOL Create(void);

	CWatchDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWatchDlg)
	enum { IDD = IDD_DIALOG_WATCH };
	CEdit	m_ctlDataRcvd;
	CString	m_data2Send;
	CString	m_status;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWatchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd* m_pParent;
	int m_nID;

	// Generated message map functions
	//{{AFX_MSG(CWatchDlg)
	afx_msg void OnSendData();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CAsyncSocket* sock;
};

#endif
