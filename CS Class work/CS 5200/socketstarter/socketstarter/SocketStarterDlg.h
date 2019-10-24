// SocketStarterDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSocketStarterDlg dialog
#include "ActiveStreamDlg.h"
#include "PassiveStreamDlg.h"
#include "DatagramDlg.h"

class CSocketStarterDlg : public CDialog
{
// Construction
public:
    void ActiveStreamDlgDone(void) { m_pActiveStreamDlg = NULL; }
    void PassiveStreamDlgDone(void) { m_pPassiveStreamDlg = NULL; }
    void DatagramDlgDone(void) { m_pDatagramDlg = NULL; }

	CSocketStarterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSocketStarterDlg)
	enum { IDD = IDD_SOCKETSTARTER_DIALOG };
	int		m_connectionType;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketStarterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    CActiveStreamDlg*   m_pActiveStreamDlg;
    CPassiveStreamDlg*  m_pPassiveStreamDlg;
    CDatagramDlg*       m_pDatagramDlg;

	// Generated message map functions
	//{{AFX_MSG(CSocketStarterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
