//
//  DatagramSocket
//

#ifndef __DATAGRAM_SOCKET
#define __DATAGRAM_SOCKET

typedef void (CDialog::*STATUS_CALLBACK_FNC)(const CString& text);

class CWatchDlg;

class DatagramSocket : public CAsyncSocket
{
private:
	CDialog*			status_callback_obj;
										// This data member should point to a dialog
										// window that is prepared to display the
										// status of this socket object
	STATUS_CALLBACK_FNC status_callback_fnc;
										// This is a function pointer that reference
										// a display function defined for the status
										// call back window (see status_callback_obj)
	static int MaxDatagramSize;
public:
	CWatchDlg*			watch_dlg;		// This data member should points to a dialog
										// window that is prepare to display data
										// that comes in on the socket.  This window
										// must support the "ShowData" method, which
										// the CWatchDlg does.
	char * buffer;
	static void setMaxDatagramSize(int size)
	{
		MaxDatagramSize = size;
	}

	// Default constructor
    DatagramSocket();

	// Event handlers
    virtual void OnAccept(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnReceive(int nErrorCode);
    virtual void OnOutOfBandData(int nErrorCode);
    virtual void OnSend(int nErrorCode);
    virtual void OnClose(int nErrorCode);

	// Setup methods
    BOOL Setup( UINT nSocketPort = 0);	// Creates the socket using services from the
										// next layer down the communication
										// architecture.  Passing in a port of 0, will
										// cause any free port to be selected.
	void SetStatusCallbackObj(CDialog *dlg)
		{ status_callback_obj = dlg; }	// This method sets the status callback object
										// which will be used by DisplayStatus
	void SetStatusCallbackFnc(STATUS_CALLBACK_FNC fnc)
		{ status_callback_fnc = fnc; }	// This method sets the status callback function
										// which will be used by DisplayStatus

	void DisplayStatus(const CString& text);
										// This method display the given text by
										// sending it to the status callback object
										// using the status callback function

};

#endif