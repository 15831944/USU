// PassiveStreamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPassiveStreamDlg dialog
#ifndef __PASSIVESTREAMDLG_H
#define __PASSIVESTREAMDLG_H

class CPassiveStreamDlg : public CDialog
{
// Construction
public:
	StreamSocket* stream_sock;

    void CleanUpSocket(void);
	void DisplayStatus(const CString& text);
    BOOL Create();

	CPassiveStreamDlg(CWnd* pParent = NULL);            // standard constructor

// Dialog Data
	//{{AFX_DATA(CPassiveStreamDlg)
	enum { IDD = IDD_DIALOG_PASSIVE };
	UINT	m_localPort;
	CString	m_status;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPassiveStreamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPassiveStreamDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

   	CWnd* m_pParent;
	int m_nID;
};

#endif
