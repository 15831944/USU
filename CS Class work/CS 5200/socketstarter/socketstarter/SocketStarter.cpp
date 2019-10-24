// SocketStarter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SocketStarter.h"
#include "SocketStarterDlg.h"
#include "DatagramSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// String conversion functions

CString PackString(const CString& rawdata)
{
	CString	result("");

	for (int i=0; i<rawdata.GetLength(); i++)
	{
		if (rawdata[i]>=32)
			result += rawdata[i];
		else
		{
			CString tmp;
			tmp.Format("\\%02d",(unsigned char) rawdata[i]);
			result += tmp;
		}
	}

	return result;
}

CString UnpackString(const CString& data)
{
	CString result("");
	int lng = data.GetLength();

	const char *str_ptr = data;
	const char *end_ptr = str_ptr+lng;
	char *tmp_ptr;
	while (str_ptr < end_ptr)
	{
		if (*str_ptr=='\\')
		{
			long tmp = strtol(str_ptr+1, &tmp_ptr, 0);
			char tmp_char = (char) tmp & 0xff;
			result += tmp_char;
			str_ptr = tmp_ptr;
		}
		else
		{
			result += *str_ptr;
			str_ptr++;
		}
	}

	return result;
}

CString GetErrorMessage(UINT nErrorCode)
{
	CString message;
	switch (nErrorCode)
	{
	case 0:
		message = CString("no error occured");
		break;
	case WSANOTINITIALISED:
		message = CString("A successful AfxSocketInit must occur before using this API.");
		break;
	case WSAEINPROGRESS:
		message = CString("A blocking Windows Sockets call is in progress.");
		break;
	case WSAEAFNOSUPPORT:
		message = CString("Addresses in the specified family cannot be used with this socket.");
		break;
	case WSAEWOULDBLOCK:
		message = CString("The socket is marked as nonblocking and the connection cannot be completed immediately.");
		break;
	case WSAENETDOWN:
		message = CString("Network subsystem failed");
		break;
	case WSAECONNRESET:
		message = CString("Connection reset by remote side");
		break;
	case WSAECONNABORTED:
		message = CString("Connection aborted");
		break;
	case WSAEADDRINUSE:
		message = CString("The specified address is already in use");
		break;
	case WSAEADDRNOTAVAIL:
		message = CString("The specified address is not available from the local machine");
		break;
	case WSAECONNREFUSED:
		message = CString("The attempt to connect was forcefully rejected");
		break;
	case WSAEDESTADDRREQ:
		message = CString("A destination address is required");
		break;
	case WSAEFAULT:
		message = CString("The lpSockAddrLen argument is incorrect");
		break;
	case WSAEINVAL:
		message = CString("The socket is already bound to an address");
		break;
	case WSAEISCONN:
		message = CString("The socket is already connected");
		break;
	case WSAEMFILE:
		message = CString("No more file descriptors are available");
		break;
	case WSAENETUNREACH:
		message = CString("The network cannot be reached from this host at this time");
		break;
	case WSAENOBUFS:
		message = CString("No buffer space is available. The socket cannot be connected");
		break;
	case WSAENOTCONN:
		message = CString("The socket is not connected");
		break;
	case WSAENOTSOCK:
		message = CString("The descriptor is a file, not a socket");
		break;
	case WSAETIMEDOUT:
		message = CString("The attempt to connect timed out without establishing a connection");
		break;
	default:
		message.Format("Unknown error has occured.  Code = %i",nErrorCode);
	}
	return message;
}

/////////////////////////////////////////////////////////////////////////////
// CSocketStarterApp

BEGIN_MESSAGE_MAP(CSocketStarterApp, CWinApp)
	//{{AFX_MSG_MAP(CSocketStarterApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocketStarterApp construction

CSocketStarterApp::CSocketStarterApp(void)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSocketStarterApp object

CSocketStarterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSocketStarterApp initialization

BOOL CSocketStarterApp::InitInstance()
{
	WSADATA socket_configuration_data;

	if (!AfxSocketInit(&socket_configuration_data))
	{
//		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	DatagramSocket::setMaxDatagramSize(socket_configuration_data.iMaxUdpDg);

	CSocketStarterDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

