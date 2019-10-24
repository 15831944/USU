// DatagramDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDatagramDlg dialog
#ifndef __DATAGRAMDLG_H
#define __DATAGRAMDLG_H

class DatagramSocket;

class CDatagramDlg : public CDialog
{
// Construction
public:
	void DisplayStatus(const CString& text);
    BOOL Create();

	CDatagramDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDatagramDlg)
	enum { IDD = IDD_DIALOG_DATAGRAM };
	CString	m_remoteIP;
	CString	m_status;
	UINT	m_remotePort;
	UINT	m_localPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatagramDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
    //}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDatagramDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CWnd* m_pParent;
	int m_nID;
};

#endif
