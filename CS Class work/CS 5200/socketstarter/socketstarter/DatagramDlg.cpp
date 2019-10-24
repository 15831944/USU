// DatagramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SocketStarter.h"
#include "SocketStarterDlg.h"
#include "DatagramDlg.h"
#include "DatagramSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString GetErrorMessage(UINT errCode);
/////////////////////////////////////////////////////////////////////////////
//
// CDatagramDlg constructor
//
CDatagramDlg::CDatagramDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDatagramDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatagramDlg)
	m_remoteIP = _T("");
	m_status = _T("");
	m_remotePort = 0;
	m_localPort = 0;
	//}}AFX_DATA_INIT

    m_pParent = pParent;
    m_nID = CDatagramDlg::IDD;

}

/////////////////////////////////////////////////////////////////////////////
//
// CDatagramDlg::DoDataExchange
//
// This method is using to move data between the sceen and this objects
// data members
//
void CDatagramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatagramDlg)
	DDX_Text(pDX, IDC_EDIT_DG_REMOTEIP, m_remoteIP);
	DDV_MaxChars(pDX, m_remoteIP, 20);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_status);
	DDX_Text(pDX, IDC_EDIT_DG_REMOTEPORT, m_remotePort);
	DDX_Text(pDX, IDC_EDIT_DG_LOCALPORT, m_localPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDatagramDlg, CDialog)
	//{{AFX_MSG_MAP(CDatagramDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//
// CDatagramDlg::OnOK
//
// This message handler is invoked when the user clicks on the OK button.
// It is responsible for setup the DatagramSocket and its cooresponding watch
// window.
//
void CDatagramDlg::OnOK() 
{
    UpdateData(TRUE);

	// CS5200 Finish this method

	// Declare a local pointer to a datagram socket, since this class does not need
    // to be responsible for the datagram socket after it is set up, there is no
    // need to have the pointer be a member variable.
	DatagramSocket * ptrDSocket;    

    // Check to make sure the local port is valid (i.e. not a reverse port #)
	// if o.k. then
	if (m_localPort==0 || m_localPort>1024)
    {
		// create a new Datagram socket object and set up the call back object and
		// function
		ptrDSocket = new DatagramSocket();
		ptrDSocket->SetStatusCallbackObj(this);
		
        // create the actual socket object and bind it to the specified local
		// port. Check to see if an error occurred
		// if o.k. then 
		if (ptrDSocket->Setup(m_localPort)==TRUE)
		{
			DWORD last_err;
			last_err = GetLastError();
			if (last_err!=0 && last_err!=WSAEWOULDBLOCK)
			{
				DisplayStatus(CString("Error in establishing a connection (1): ") + GetErrorMessage(last_err));
			}
			else
			{
				//ptrDSocket->Bind(m_localPort);
				//last_err = GetLastError();
				//if (last_err!=0 && last_err!=WSAEWOULDBLOCK)
				//{
				//	DisplayStatus(CString("Error in establishing a connection (2): ") + GetErrorMessage(last_err));
				//}
				//else
				//{
					// Setup remote address as the default connection
					DisplayStatus("Establishing a connection");
					if (!ptrDSocket->Connect(m_remoteIP,m_remotePort))
					{
						DWORD last_err = CAsyncSocket::GetLastError();
						// Check to see if an error occurred
						// if not o.k. then
						// If an error occurs, say something about it in the status
						// and clean up any dynamically allocated objects.						
						DisplayStatus(CString("Error in establishing a connection (3): ") + GetErrorMessage(last_err));
					}
					else
					{
						DisplayStatus("Remote target established");
						
						// Otherwise, display a status message saying that the remote
						// target was established

						// Create a Watch Dialog window and make it responsible for the
						// datagram, i.e. move the callbacks over the that window.
						ptrDSocket->watch_dlg = new CWatchDlg;
						ptrDSocket->watch_dlg->SetSocket(ptrDSocket);
						ptrDSocket->SetStatusCallbackObj(ptrDSocket->watch_dlg);
						ptrDSocket->SetStatusCallbackFnc((STATUS_CALLBACK_FNC) &CWatchDlg::DisplayStatus);

						// Bring the window in an Amodel fashion
						ptrDSocket->watch_dlg->Create();
						ptrDSocket->watch_dlg->ShowWindow(SW_SHOW);
					}
				//}
			}
		}
		else
			DisplayStatus("Socket not created");
    }
    else
		DisplayStatus("Illegal Port");

}

BOOL CDatagramDlg::Create()
{
    return CDialog::Create(m_nID, m_pParent);
}

void CDatagramDlg::PostNcDestroy()
{
    delete this;
}


void CDatagramDlg::OnCancel() 
{
    // Clean up a pointer in starter dialog
     if (m_pParent)
         ((CSocketStarterDlg *) m_pParent) -> DatagramDlgDone();

    // Destroy the dialog box
	CDialog::OnCancel();
}

void CDatagramDlg::DisplayStatus(const CString& text)
{
	m_status=text;
	UpdateData(FALSE);
}
