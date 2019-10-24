// ActiveStreamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActiveStreamDlg dialog

#ifndef __ACTIVESTREAMDLG_H
#define __ACTIVESTREAMDLG_H

class CActiveStreamDlg : public CDialog
{
// Construction
public:
	void ResetSocketPtr(void);
	StreamSocket* stream_sock;

	void CleanUpSocket(void);
	void DisplayStatus(const CString& text);
    BOOL Create();

	CActiveStreamDlg(CWnd* pParent = NULL);             // standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveStreamDlg)
	enum { IDD = IDD_DIALOG_ACTIVE };
	CString	m_remoteIP;
	CString	m_status;
	UINT	m_remotePort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveStreamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CWnd* m_pParent;
	int m_nID;

	// Generated message map functions
	//{{AFX_MSG(CActiveStreamDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
#endif
