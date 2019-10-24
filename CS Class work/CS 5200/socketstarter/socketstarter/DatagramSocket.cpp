/****************************************************************************
*
*	File:			DatagramSocket.cpp
*	Class:			DatagramSocket
*	Project:		SocketStarter
*	Author:			Stephen Clyde
*	Last Modified:	July 17, 2000
*
*	Description:
*
*	A DatagramSocket object is an asynchronization datagram with status
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
#include "DatagramSocket.h"
#include "ActiveStreamDlg.h"
#include "WatchDlg.h"

int DatagramSocket::MaxDatagramSize = 0;

DatagramSocket::DatagramSocket(void) :
		CAsyncSocket(),
		status_callback_obj(NULL),
		status_callback_fnc(NULL),
		watch_dlg(NULL) 
{
	buffer = new char[MaxDatagramSize + 1];
	memset(buffer,0,MaxDatagramSize + 1);
}

/////////////////////////////////////////////////////////////////////////////
//
// DatagramSocket::OnAccept
//
// This message handler is invoked socket gets an accept event.  If it does
// and there are no problems, it should do the accept, create a watch window
// and associate that window with this socket.
//
void DatagramSocket::OnAccept(int nErrorCode)
{
	DisplayStatus("Error: OnAccept in Datagram socket was invoked");
}

/////////////////////////////////////////////////////////////////////////////
//
// DatagramSocket::OnClose
//
// This message handler is invoked socket gets an close event.  Simply
// an status message that reflects the value of the error code.
//
void DatagramSocket::OnClose(int nErrorCode)
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
// DatagramSocket::OnConnect
//
// This message handler is invoked socket gets a connect event, which occurs
// sometime after the connect method is invoked.  If there are no errors,
// setup the Watch Dialog and associate it with this socket.  If there were
// errors, display the errors
//
void DatagramSocket::OnConnect(int nErrorCode)
{
	DisplayStatus("Error: OnConnect in Datagram socket was invoked");
}

/////////////////////////////////////////////////////////////////////////////
//
// DatagramSocket::OnOutOfBandData
//
// This message handler is invoked socket gets out of band data.  Simply
// display an error, if one occurs.  We are going to ignore out of band
// data.
//
void DatagramSocket::OnOutOfBandData(int nErrorCode)
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
// DatagramSocket::OnReceive
//
// This message handler is invoked when the socket gets some data.  If no
// error occurred, it should display that data in the watch window.
// Otherwise, it should display an appropriate status message.
//
void DatagramSocket::OnReceive(int nErrorCode)
{
	switch (nErrorCode)
	{
	case 0:
		{
			int count=0;
			DisplayStatus("Receiving Data");
			do
			{
				count = Receive(buffer, MaxDatagramSize);
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
// DatagramSocket::OnSend
//
// This message handler is invoked when the socket finishes sending some
// data.  It should simply display an appropriate status message.
//
void DatagramSocket::OnSend(int nErrorCode)
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
BOOL DatagramSocket::Setup( UINT nSocketPort)
{
    BOOL status = CAsyncSocket::Create(nSocketPort, SOCK_DGRAM);
    DWORD lasterr = GetLastError();

    return status;
}

/////////////////////////////////////////////////////////////////////////////
//
// DatagramSocket::DisplayStatus
//
// This method display the given text in status window of associate with this
// socket.
//
void DatagramSocket::DisplayStatus(const CString& text)
{
	if (status_callback_obj!=NULL && status_callback_fnc!=NULL)
		(status_callback_obj->*status_callback_fnc)(text);
}
