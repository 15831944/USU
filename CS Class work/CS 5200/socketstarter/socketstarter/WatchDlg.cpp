// WatchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SocketStarter.h"
#include "WatchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString GetErrorMessage(UINT nErrorCode);

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg dialog


CWatchDlg::CWatchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWatchDlg::IDD, pParent),
      sock(NULL)
{
	//{{AFX_DATA_INIT(CWatchDlg)
	m_data2Send = _T("");
	m_status = _T("");
	//}}AFX_DATA_INIT

    m_pParent = pParent;
    m_nID = CWatchDlg::IDD;
}


void CWatchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWatchDlg)
	DDX_Control(pDX, IDC_EDIT_DATARCVD, m_ctlDataRcvd);
	DDX_Text(pDX, IDC_EDIT_DATA2SEND, m_data2Send);
	DDX_Text(pDX, IDC_EDIT_STATUS, m_status);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWatchDlg, CDialog)
	//{{AFX_MSG_MAP(CWatchDlg)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnSendData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWatchDlg message handlers

BOOL CWatchDlg::Create()
{
    return CDialog::Create(m_nID, m_pParent);
}

void CWatchDlg::OnSendData() 
{
	UpdateData(TRUE);
	if (sock)
	{
        // Convert and send the data out the socket
		CString text = UnpackString(m_data2Send);

		if (sock->Send(text.GetBuffer(0), text.GetLength()) == SOCKET_ERROR)
		{
			DisplayStatus(CString("Error occured: ") + GetErrorMessage(CAsyncSocket::GetLastError()));
		}
		else
		{
			// Echo what's sent to received window
			m_ctlDataRcvd.ReplaceSel(m_data2Send);
       		CString ending = text.Mid(text.GetLength()-2,2);
			if (ending=="\r\n")
			{
			   CString tmp("\r\n");
			   m_ctlDataRcvd.ReplaceSel(tmp);
			}
		}
        // Clear out the send field
		m_data2Send="";
        UpdateData(FALSE);
	}
}

void CWatchDlg::ShowData(const CString& text)
{
    CString tmp=PackString(text);
	CString ending = text.Mid(text.GetLength()-2,2);
	if (ending=="\r\n")
		tmp += "\r\n";
    m_ctlDataRcvd.ReplaceSel(tmp);
}

void CWatchDlg::DisplayStatus(const CString& text)
{
	m_status = text;
	UpdateData(FALSE);
}

void CWatchDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (sock)
	{
        sock->Close();
		delete sock;
		sock=NULL;
	}

	CDialog::OnCancel();
}

void CWatchDlg::PostNcDestroy() 
{
	if (sock)
	{
        sock->Close();
		delete sock;
		sock=NULL;
	}

    delete this;
}
