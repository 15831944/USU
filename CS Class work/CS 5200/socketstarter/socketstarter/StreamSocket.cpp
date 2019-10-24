/****************************************************************************
*
*	File:			StreamSocket.cpp
*	Class:			StreamSocket
*	Project:		SocketStarter
*	Author:			Stephen Clyde
*	Last Modified:	July 17, 2000
*
*	Description:
*
*	A StreamSocket object is an asynchronization stream socket with status
*	display capabilities.
*
*	Modification history:
*
*	Aug 30, 1997	Initial Version
*	Jul 17, 2000	Comments added
*
*****************************************************************************/

#include "stdafx.h"
#include "SocketStarter.h"
#include "StreamSocket.h"
#include "ActiveStreamDlg.h"
#include "WatchDlg.h"

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::OnAccept
//
// This message handler is invoked socket gets an accept event.  If it does
// and there are no problems, it should do the accept, create a watch window
// and associate that window with this socket.
//
void StreamSocket::OnAccept(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
		{
			StreamSocket* new_socket = new StreamSocket;

			if (Accept(*new_socket) == TRUE)
		    {
				DisplayStatus("Connection established");

				new_socket->watch_dlg = new CWatchDlg;
				new_socket->watch_dlg->SetSocket(new_socket);
				new_socket->SetStatusCallbackObj(new_socket->watch_dlg);
				new_socket->SetStatusCallbackFnc((STATUS_CALLBACK_FNC) &CWatchDlg::DisplayStatus);

				// Bring the window in an Amodel fashion
				new_socket->watch_dlg->Create();
                new_socket->watch_dlg->ShowWindow(SW_SHOW);
		    }
			else
				DisplayStatus("Connection error");
			break;
		}
	case WSAENETDOWN:
		DisplayStatus("Accept failed because net is down");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::OnClose
//
// This message handler is invoked socket gets an close event.  Simply
// an status message that reflects the value of the error code.
//
void StreamSocket::OnClose(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
		DisplayStatus("Socket closed normally");
		break;
	case WSAENETDOWN:
		DisplayStatus("Socket closed - network subsystem failed");
		break;
	case WSAECONNRESET:
		DisplayStatus("Socket closed - connection reset by remote side");
		break;
	case WSAECONNABORTED:
		DisplayStatus("Socket closed - connection aborted");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::OnConnect
//
// This message handler is invoked socket gets a connect event, which occurs
// sometime after the connect method is invoked.  If there are no errors,
// setup the Watch Dialog and associate it with this socket.  If there were
// errors, display the errors
//
void StreamSocket::OnConnect(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
        {
			DisplayStatus("Connection established");

            // Disconnect the Active Dialog window and this socket
            ((CActiveStreamDlg *) status_callback_obj)->ResetSocketPtr();

			watch_dlg = new CWatchDlg;
			watch_dlg->SetSocket(this);
			SetStatusCallbackObj(watch_dlg);
		    SetStatusCallbackFnc((STATUS_CALLBACK_FNC) &CWatchDlg::DisplayStatus);

			// Bring the window in an Amodel fashion
    		watch_dlg->Create();
            watch_dlg->ShowWindow(SW_SHOW);

		    break;
        }
	case WSAEADDRINUSE:
		DisplayStatus("The specified address is already in use");
		break;
	case WSAEADDRNOTAVAIL:
		DisplayStatus("The specified address is not available from the local machine");
		break;
	case WSAEAFNOSUPPORT:
		DisplayStatus("Addresses in the specified family cannot be used with this socket");
		break;
	case WSAECONNREFUSED:
		DisplayStatus("The attempt to connect was forcefully rejected");
		break;
	case WSAEDESTADDRREQ:
		DisplayStatus("A destination address is required");
		break;
	case WSAEFAULT:
		DisplayStatus("The lpSockAddrLen argument is incorrect");
		break;
	case WSAEINVAL:
		DisplayStatus("The socket is already bound to an address");
		break;
	case WSAEISCONN:
		DisplayStatus("The socket is already connected");
		break;
	case WSAEMFILE:
		DisplayStatus("No more file descriptors are available");
		break;
	case WSAENETUNREACH:
		DisplayStatus("The network cannot be reached from this host at this time");
		break;
	case WSAENOBUFS:
		DisplayStatus("No buffer space is available. The socket cannot be connected");
		break;
	case WSAENOTCONN:
		DisplayStatus("The socket is not connected");
		break;
	case WSAENOTSOCK:
		DisplayStatus("The descriptor is a file, not a socket");
		break;
	case WSAETIMEDOUT:
		DisplayStatus("The attempt to connect timed out without establishing a connection");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::OnOutOfBandData
//
// This message handler is invoked socket gets out of band data.  Simply
// display an error, if one occurs.  We are going to ignore out of band
// data.
//
void StreamSocket::OnOutOfBandData(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
		DisplayStatus("Received out of band data");
		break;
	case WSAENETDOWN:
		DisplayStatus("The network subsystem has failed");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::OnReceive
//
// This message handler is invoked when the socket gets some data.  If no
// error occurred, it should display that data in the watch window.
// Otherwise, it should display an appropriate status message.
//
void StreamSocket::OnReceive(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
		{
			const int MAX_READ = 100;
			int count=0;
			char buffer[MAX_READ+1];

			DisplayStatus("Receiving Data");

			do
			{
				count = Receive(buffer, MAX_READ);
				CString tmp;
				if (count>0 && watch_dlg!=NULL)
					watch_dlg->ShowData(buffer, count);

			} while (count>0);
			DisplayStatus("Data Received");
			break;
		}
	case WSAENETDOWN:
		DisplayStatus("The network subsystem has failed");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::OnSend
//
// This message handler is invoked when the socket finishes sending some
// data.  It should simply display an appropriate status message.
//
void StreamSocket::OnSend(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
		DisplayStatus("Data sent");
		break;
	case WSAENETDOWN:
		DisplayStatus("The network subsystem has failed");
		break;
	}
}

/////////////////////////////////////////////////////////////////////////////
//
// SteamSocket::Setup
//
// This method creates the socket by using the services of the next layer
// down in the communication hierarchy, namely the MFC CAsyncSocket class.
//
BOOL StreamSocket::Setup( UINT nSocketPort)
{
    BOOL status = CAsyncSocket::Create(nSocketPort);
    DWORD lasterr = GetLastError();

    return status;
}

/////////////////////////////////////////////////////////////////////////////
//
// StreamSocket::DisplayStatus
//
// This method display the given text in status window of associate with this
// socket.
//
void StreamSocket::DisplayStatus(const CString& text)
{
	if (status_callback_obj!=NULL && status_callback_fnc!=NULL)
		(status_callback_obj->*status_callback_fnc)(text);
}
