// PassiveStreamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SocketStarter.h"
#include "SocketStarterDlg.h"
#include "PassiveStreamDlg.h"
#include "StreamSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassiveStreamDlg dialog


CPassiveStreamDlg::CPassiveStreamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPassiveStreamDlg::IDD, pParent),
	  stream_sock(NULL)
{
	//{{AFX_DATA_INIT(CPassiveStreamDlg)
	m_localPort = 1100;
	m_status = _T("");
	//}}AFX_DATA_INIT

    m_pParent = pParent;
    m_nID = CPassiveStreamDlg::IDD;
}

void CPassiveStreamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassiveStreamDlg)
	DDX_Text(pDX, IDC_EDIT_PASSIVEPORT, m_localPort);
	DDX_Text(pDX, IDC_ACCEPT_STATUS, m_status);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassiveStreamDlg, CDialog)
	//{{AFX_MSG_MAP(CPassiveStreamDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassiveStreamDlg message handlers

//
//	CPassiveStreamDlg::OnOk
//
//	This function first closes down any existing socket and then
//  create a stream socket for a passive connection.  It sets up
//  the listen queue and returns, giving control back to the user.
//  If an connection comes in, the StreamSocket::OnAccept event
//  handler gets called, which in turn brings up the CWatchDlg
//  window.
//
void CPassiveStreamDlg::OnOK() 
{
    UpdateData(TRUE);

	// Close down exist socket
    CleanUpSocket();

	if (m_localPort==0 || m_localPort>1024)
    {
		// create a new stream socket and bind the request port
        stream_sock = new StreamSocket;
        if (stream_sock->Setup(m_localPort) == TRUE)
        {
			// Setup listen queue
            if (stream_sock->Listen() == TRUE)
			{
				DisplayStatus("Waiting for a connection");
				stream_sock->SetStatusCallbackObj(this);
				stream_sock->SetStatusCallbackFnc((STATUS_CALLBACK_FNC) &CPassiveStreamDlg::DisplayStatus);
                GetDlgItem(IDOK)->EnableWindow(FALSE);
			}
			else
            {
				DisplayStatus("Listen queue failure");
                CleanUpSocket();
            }
        }
        else
		{
			DisplayStatus("Socket not created");
			delete stream_sock;
		}
    }
    else
		DisplayStatus("Illegal Port");
}

BOOL CPassiveStreamDlg::Create()
{
    return CDialog::Create(m_nID, m_pParent);
}

void CPassiveStreamDlg::PostNcDestroy()
{
    delete this;
}

void CPassiveStreamDlg::OnCancel() 
{
    // Clean up the socket
	CleanUpSocket();

    // Clean up a pointer in starter dialog
    if (m_pParent)
        ((CSocketStarterDlg *) m_pParent) -> PassiveStreamDlgDone();

    // Destroy the dialog box
	DestroyWindow();
}

void CPassiveStreamDlg::DisplayStatus(const CString& text)
{
	m_status=text;
	UpdateData(FALSE);
}

void CPassiveStreamDlg::CleanUpSocket(void)
{
   	if (stream_sock)
	{
        stream_sock->Close();
		delete stream_sock;
		stream_sock=NULL;
	}
}
