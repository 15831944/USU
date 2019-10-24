// ActiveStreamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SocketStarter.h"
#include "SocketStarterDlg.h"
#include "ActiveStreamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CActiveStreamDlg dialog


CActiveStreamDlg::CActiveStreamDlg(CWnd* pParent /*=NULL*/) :
	CDialog(CActiveStreamDlg::IDD, pParent),
    stream_sock(NULL)
{
	//{{AFX_DATA_INIT(CActiveStreamDlg)
	m_remoteIP = _T("");
	m_status = _T("");
	m_remotePort = 0;
	//}}AFX_DATA_INIT

    m_pParent = pParent;
    m_nID = CActiveStreamDlg::IDD;
}


void CActiveStreamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CActiveStreamDlg)
	DDX_Text(pDX, IDC_EDIT_ACTIVEIP, m_remoteIP);
	DDV_MaxChars(pDX, m_remoteIP, 20);
	DDX_Text(pDX, IDC_EDIT1, m_status);
	DDX_Text(pDX, IDC_EDIT_ACTIVEPORT, m_remotePort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CActiveStreamDlg, CDialog)
	//{{AFX_MSG_MAP(CActiveStreamDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CActiveStreamDlg message handlers

void CActiveStreamDlg::OnOK() 
{
    UpdateData(TRUE);

	// Close down exist socket
	CleanUpSocket();

	// create a new stream socket 
    stream_sock = new StreamSocket;
    if (stream_sock->Setup()==TRUE)
    {
        // Set up call backs
        stream_sock->SetStatusCallbackObj(this);
	    stream_sock->SetStatusCallbackFnc((STATUS_CALLBACK_FNC) &CActiveStreamDlg::DisplayStatus);

	    // Setup listen queue
	    DisplayStatus("Establishing a connection");
        stream_sock->Connect(m_remoteIP, m_remotePort);
        DWORD last_err = GetLastError();
        if (last_err!=0 && last_err!=WSAEWOULDBLOCK)
        {
            DisplayStatus("Error in establishing a connection");
            CleanUpSocket();
        }
    }
    else
    {
        DisplayStatus("Error in setting up socket");
        delete stream_sock;
    }
}

BOOL CActiveStreamDlg::Create()
{
    return CDialog::Create(m_nID, m_pParent);
}

void CActiveStreamDlg::PostNcDestroy()
{
    delete this;
}

void CActiveStreamDlg::DisplayStatus(const CString& text)
{
	m_status=text;
	UpdateData(FALSE);
}

void CActiveStreamDlg::OnCancel() 
{
    // Clean up the socket
	CleanUpSocket();

    // Clean up a pointer in starter dialog
    if (m_pParent)
        ((CSocketStarterDlg *) m_pParent) -> ActiveStreamDlgDone();

    // Destroy the dialog box
	DestroyWindow();
}

void CActiveStreamDlg::CleanUpSocket(void)
{
	if (stream_sock)
	{
        stream_sock->Close();
		delete stream_sock;
		stream_sock=NULL;
	}

}

void CActiveStreamDlg::ResetSocketPtr(void)
{
    // This function is called by the Stream Socket class after it moves
    // a pointer to the socket over to the CWatchDlg class.  The socket
    // will be closed by CWatchDlg

    stream_sock=NULL;
}
