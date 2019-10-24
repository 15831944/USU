// CCommFunctions.cpp: implementation of the CCCommFunctions class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LADA Control Module.h"
#include "CommFunctions.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Global Functions


void OutputCEError(DWORD error){
	if (error & CE_BREAK)
		OutputDebugString("\nError: The hardware detected a break condition.");
	if (error & CE_DNS)
		OutputDebugString("\nError: A parallel device is not selected.");
	if (error & CE_FRAME)
		OutputDebugString("\nError: The hardware detected a framing error.");
	if (error & CE_IOE)
		OutputDebugString("\nError: An I/O error occurred during communications with the device.");
	if (error & CE_MODE)
		OutputDebugString("\nError: The requested mode is not supported, or the hfile"
		                  "\nparameter is invalid.  If this value is specified, it is"
						  "\nthe only valid error.");	
	if (error & CE_OOP)
		OutputDebugString("\nError: Out of paper.");
	if (error & CE_OVERRUN)
		OutputDebugString("\nError: A character buffer overrun has occured.");
	if (error & CE_PTO)
		OutputDebugString("\nError: A time-out occured on a parallel device.");
	if (error & CE_RXOVER)
		OutputDebugString("\nError: Input buffer overflow.");
	if (error & CE_RXPARITY)
		OutputDebugString("\nError: Parity error.");
	if (error & CE_TXFULL)
		OutputDebugString("\nError: Output buffer full, unable to transmit character.");
}

void WriteToBuf(const BYTE *buf, int bytesToWrite){
	if (readBufPos == -1)
		return;
	else if (readBufPos + bytesToWrite > BUF_SIZE - 1)
		readBufPos = 0;
	
	if (readBufPos + bytesToWrite > BUF_SIZE - 1){
		readBufPos = -1;
		return;
	}

	int j = 0;
	for (int i = readBufPos; i < readBufPos + bytesToWrite; i++)
		readBuf[i] = buf[j++];
	
	readBufPos += bytesToWrite;
	readBuf[readBufPos] = '\0';
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommFunctions::CCommFunctions(){
	CreateCR10TalkInfo();
	
	// these are global, not member variables
	readBufPos = 0;
	readBuf = new char[BUF_SIZE];
}

CCommFunctions::~CCommFunctions(){
	//MessageBox(NULL, "Destructor for object called","Note", MB_OK);
	DestroyCR10TalkInfo();
	// these are global, not member variables
	delete readBuf;
}


BOOL CCommFunctions::CreateCR10TalkInfo()
{
	TalkInfo = new CR10TalkInfo;
	COMDEV( TalkInfo )        = 0 ;
	CONNECTED( TalkInfo )     = FALSE ;
	PORT( TalkInfo )          = defaultPort ;// 0 means port unknown
	BAUDRATE( TalkInfo )      = CBR_9600 ;
	BYTESIZE( TalkInfo )      = 8 ;
	//FLOWCTRL( TalkInfo )      = FC_RTSCTS ;
	//FLOWCTRL( TalkInfo )      = FC_XONXOFF ;
	PARITY( TalkInfo )        = NOPARITY ;
	STOPBITS( TalkInfo )      = ONESTOPBIT ;
	XONXOFF( TalkInfo )       = FALSE ;
	//USECNRECEIVE( TalkInfo )  = FALSE ;
	DISPLAYERRORS( TalkInfo ) = TRUE ;
	WRITE_OS( TalkInfo ).Offset = 0 ;
	WRITE_OS( TalkInfo ).OffsetHigh = 0 ;
	READ_OS( TalkInfo ).Offset = 0 ;
	READ_OS( TalkInfo ).OffsetHigh = 0 ;
	//TERMWND( TalkInfo ) =       hWnd ;
	// needed to initialize TERMWND for Win32

	// create I/O event used for overlapped reads / writes

	READ_OS( TalkInfo ).hEvent = CreateEvent( NULL,    // no security
                                              TRUE,    // explicit reset req
                                              FALSE,   // initial event reset
                                              NULL ) ; // no name
	if (READ_OS( TalkInfo ).hEvent == NULL)
	{
		delete TalkInfo;
		return FALSE ;
	}

	WRITE_OS( TalkInfo ).hEvent = CreateEvent( NULL,    // no security
                                               TRUE,    // explicit reset req
                                               FALSE,   // initial event reset
                                               NULL ) ; // no name
	if (NULL == WRITE_OS( TalkInfo ).hEvent)
	{
		CloseHandle( READ_OS( TalkInfo ).hEvent ) ;
		delete TalkInfo;
		return FALSE ;
	}

	// set TTYInfo handle before any further message processing.

	//SETTalkInfo( hWnd, TalkInfo ) ;
	// I don't think I need to use this MACRO.  I'm not sure
	// what it does.  It calls SetWindowLong(...) which is used
	// to change an attribute of a specified window.  
	return TRUE ;

}

//---------------------------------------------------------------------------
//  BOOL NEAR OpenConnection( HWND hWnd )
//
//  Description:
//     Opens communication port specified in the TTYINFO struct.
//     It also sets the CommState and notifies the window via
//     the fConnected flag in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - OpenComm() is not supported under Win-32.  Use CreateFile()
//       and setup for OVERLAPPED_IO.
//     - Win-32 has specific communication timeout parameters.
//     - Created the secondary thread for event notification.
//
//---------------------------------------------------------------------------


BOOL CCommFunctions::OpenConnection()
{

	char       szPort[ 15 ];
	BOOL       fRetVal ;
	//NPTTYINFO  npTTYInfo ;

	HANDLE        hCommWatchThread ;
	DWORD         dwThreadID ;
	COMMTIMEOUTS  CommTimeOuts ;

	// load the COM prefix string and append port number
	
	wsprintf( szPort, "COM%d", PORT( TalkInfo ) ) ;

	// open COMM device

	if ((COMDEV( TalkInfo ) =
		CreateFile( szPort, GENERIC_READ | GENERIC_WRITE,
                  0,                    // exclusive access
                  NULL,                 // no security attrs
                  OPEN_EXISTING,
                  //FILE_ATTRIBUTE_NORMAL |
                  FILE_FLAG_OVERLAPPED, // overlapped I/O
                  NULL )) == (HANDLE) -1 )
		return ( FALSE ) ;
	
	
	// get any early notifications

	SetCommMask( COMDEV( TalkInfo ), EV_RXCHAR ) ;

	// setup device buffers

	SetupComm( COMDEV( TalkInfo ), 4096, 4096 ) ;

	// purge any information in the buffer

	PurgeComm( COMDEV( TalkInfo ), PURGE_TXABORT | PURGE_RXABORT |
                                      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
	// set up for overlapped I/O

	CommTimeOuts.ReadIntervalTimeout = 0;//0xFFFFFFFF ;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;//1000 ;
	// CBR_9600 is approximately 1byte/ms. For our purposes, allow
	// double the expected time per character for a fudge factor.
	CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/BAUDRATE( TalkInfo ) ;
	CommTimeOuts.WriteTotalTimeoutConstant = 20 ;
	SetCommTimeouts( COMDEV( TalkInfo ), &CommTimeOuts ) ;
	
	fRetVal = SetupConnection() ;
	if (fRetVal)
	{
		CONNECTED( TalkInfo ) = TRUE ;

		// Create a secondary thread
		// to watch for an event.

		
		if (NULL == (hCommWatchThread =
                      CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
                                    0,
                                    CommWatchProc,
                                    (LPVOID) TalkInfo,
                                    0, &dwThreadID )))
		{
			CONNECTED( TalkInfo ) = FALSE ;
			CloseHandle( COMDEV( TalkInfo ) ) ;
			fRetVal = FALSE ;
		}
		else
		{
			THREADID( TalkInfo ) = dwThreadID ;
			HTHREAD( TalkInfo ) = hCommWatchThread ;
			// assert DTR
			EscapeCommFunction( COMDEV( TalkInfo ), SETDTR ) ;
		}
	}
	else
	{
		CONNECTED( TalkInfo ) = FALSE ;
		CloseHandle( COMDEV( TalkInfo ) ) ;
	}

	// restore cursor

	//SetCursor( hOldCursor ) ;

	return ( fRetVal ) ;

} // end of OpenConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR SetupConnection( HWND hWnd )
//
//  Description:
//     This routines sets up the DCB based on settings in the
//     TTY info structure and performs a SetCommState().
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Win-32 requires a slightly different processing of the DCB.
//       Changes were made for configuration of the hardware handshaking
//       lines.
//
//---------------------------------------------------------------------------

BOOL CCommFunctions::SetupConnection()
{
	BOOL       fRetVal ;
	DCB        dcb ;

    memset(&dcb, 0, sizeof( DCB ));
	dcb.DCBlength = sizeof( DCB ) ;

	GetCommState( COMDEV( TalkInfo ), &dcb ) ;
	dcb.DCBlength = sizeof( DCB ) ;
	/*
	dcb.BaudRate = BAUDRATE( TalkInfo ) ;
	dcb.fBinary = TRUE;  
	// using FALSE will not work in WIN32
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fTXContinueOnXoff = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;
	dcb.ByteSize = BYTESIZE( TalkInfo ) ;
	dcb.Parity = PARITY( TalkInfo ) ; 
	// set to NOPARITY, which is 0 or FALSE
	dcb.StopBits = STOPBITS( TalkInfo ) ;
	// set to ONESTOPBIT
	*/
	dcb.BaudRate = BAUDRATE( TalkInfo ) ;
	dcb.fBinary = TRUE;  
	// using FALSE will not work in WIN32
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fTXContinueOnXoff = TRUE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;
	dcb.XonLim = 500;
	dcb.XoffLim = 100;
	dcb.ByteSize = BYTESIZE( TalkInfo ) ;
	dcb.Parity = PARITY( TalkInfo ) ; 
	// set to NOPARITY, which is 0 or FALSE
	dcb.StopBits = STOPBITS( TalkInfo ) ;

	fRetVal = SetCommState( COMDEV( TalkInfo ), &dcb ) ;

	return ( fRetVal ) ;

} // end of SetupConnection()


//DWORD FAR PASCAL CCommFunctions::CommWatchProc( LPSTR lpdata )
//unsigned long __stdcall CommWatchProc(void *lpdata)



//---------------------------------------------------------------------------
//  BOOL NEAR WriteCommBlock( HWND hWnd, BYTE *pByte )
//
//  Description:
//     Writes a block of data to the COM port specified in the associated
//     TTY info structure.
//
//  Parameters:
//     
//     BYTE *pByte
//        pointer to data to write to port
//
//  Win-32 Porting Issues:
//     - WriteComm() has been replaced by WriteFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------

BOOL CCommFunctions::WriteCommBlock( const LPSTR lpData , DWORD dwBytesToWrite)
{
	BOOL        fWriteStat ;
	DWORD       dwBytesWritten ;
	DWORD       dwErrorFlags;
	DWORD   	dwError;
	DWORD       dwBytesSent=0;
	char        szError[ 128 ] ;

	//writesTotal++;
	fWriteStat = WriteFile( COMDEV( TalkInfo ), lpData, dwBytesToWrite,
                           &dwBytesWritten, &WRITE_OS( TalkInfo ) ) ;

	// Note that normally the code will not execute the following
	// because the driver caches write operations. Small I/O requests
	// (up to several thousand bytes) will normally be accepted
	// immediately and WriteFile will return true even though an
	// overlapped operation was specified

		if (!fWriteStat)
	{
		if(GetLastError() == ERROR_IO_PENDING)
		{
		
			// We should wait for the completion of the write operation
			// so we know if it worked or not

			// This is only one way to do this. It might be beneficial to
			// place the write operation in a separate thread
			// so that blocking on completion will not negatively
			// affect the responsiveness of the UI

			// If the write takes too long to complete, this
			// function will timeout according to the
			// CommTimeOuts.WriteTotalTimeoutMultiplier variable.
			// This code logs the timeout but does not retry
			// the write.

			while(!GetOverlappedResult( COMDEV( TalkInfo ),
			&WRITE_OS( TalkInfo ), &dwBytesWritten, TRUE ))
			{
				dwError = GetLastError();
				if(dwError == ERROR_IO_INCOMPLETE)
				{
					// normal result if not finished
					dwBytesSent += dwBytesWritten;
					continue;
				}
				else
				{
					// an error occurred, try to recover
					wsprintf( szError, "<CE-%u>", dwError ) ;
					OutputDebugString(szError);
					ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
					if (dwErrorFlags > 0)
						OutputCEError(dwErrorFlags);
			   		break;
				}
			}
			dwBytesSent += dwBytesWritten;

			if( dwBytesSent != dwBytesToWrite ){
				wsprintf(szError,"\nProbable Write Timeout: Total of %ld bytes sent", dwBytesSent);
				OutputDebugString(szError);

				ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
				if (dwErrorFlags > 0)
					OutputCEError(dwErrorFlags);
				// try the write operation again, up to 5 times
				//for (int i = 0; i < 5; i++){
				//	if (WriteCommBlock( lpData, dwBytesToWrite ))
				//		return (TRUE);
				//}
				timeOuts++;
				return (FALSE);
			}	 
			else
				wsprintf(szError,"\n%ld bytes written: char(%ld)", dwBytesSent, (int)*lpData);

			OutputDebugString(szError);

		}
		else
		{
			// some other error occurred
			ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
			if ((dwErrorFlags > 0) && DISPLAYERRORS( TalkInfo ))
			{
				wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
				OutputCEError(dwErrorFlags);
			}
			return ( FALSE );
		}
	}
	return ( TRUE ) ;

} // end of WriteCommBlock()



//---------------------------------------------------------------------------
//  BOOL NEAR CloseConnection( HWND hWnd )
//
//  Description:
//     Closes the connection to the port.  Resets the connect flag
//     in the TTYINFO struct.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to stop secondary thread.  SetCommMask() will signal the
//       WaitCommEvent() event and the thread will halt when the
//       CONNECTED() flag is clear.
//     - Use new PurgeComm() API to clear communications driver before
//       closing device.
//
//---------------------------------------------------------------------------

BOOL CCommFunctions::CloseConnection()
{
	// send an "end comm" signal to CR10
   WriteCommBlock("E\r", 2);
	// set connected flag to FALSE
   CONNECTED( TalkInfo ) = FALSE ;
   // disable event notification and wait for thread
   // to halt
   SetCommMask( COMDEV( TalkInfo ), 0 ) ;
   // block until thread has been halted
   while(THREADID(TalkInfo) != 0);
   // drop DTR
   EscapeCommFunction( COMDEV( TalkInfo ), CLRDTR ) ;
   // purge any outstanding reads/writes and close device handle
   PurgeComm( COMDEV( TalkInfo ), PURGE_TXABORT | PURGE_RXABORT |
                                  PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
   CloseHandle( COMDEV( TalkInfo ) ) ;
   return ( TRUE ) ;
} // end of CloseConnection()

//---------------------------------------------------------------------------
//  BOOL NEAR DestroyTTYInfo( HWND hWnd )
//
//  Description:
//     Destroys block associated with TTY window handle.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  Win-32 Porting Issues:
//     - Needed to clean up event objects created during initialization.
//
//---------------------------------------------------------------------------

BOOL CCommFunctions::DestroyCR10TalkInfo()
{
   // force connection closed (if not already closed)
   if (CONNECTED( TalkInfo ))
      CloseConnection();

   // clean up event objects
   CloseHandle( READ_OS( TalkInfo ).hEvent ) ;
   CloseHandle( WRITE_OS( TalkInfo ).hEvent ) ;
   //CloseHandle( POSTEVENT( TalkInfo ) ) ;

   delete TalkInfo;
   return ( TRUE ) ;
} // end of DestroyTTYInfo()

CR10TalkInfo * CCommFunctions::GetTalkInfoPtr(){
	return TalkInfo;
}

//************************************************************************
//  DWORD FAR PASCAL CommWatchProc( LPSTR lpData )
//
//  Description:
//     A secondary thread that will watch for COMM events.
//
//  Parameters:
//     LPSTR lpData
//        32-bit pointer argument
//
//  Win-32 Porting Issues:
//     - Added this thread to watch the communications device and
//       post notifications to the associated window.
//
//************************************************************************

DWORD __stdcall CCommFunctions::CommWatchProc(void *lpdata)
{

	CR10TalkInfo *TalkInfo = (CR10TalkInfo *) lpdata;

	DWORD       dwEvtMask ;
	
	OVERLAPPED  os ;
	int        nLength ;
	BYTE       abIn[ MAXBLOCK + 1] ;

	memset( &os, 0, sizeof( OVERLAPPED ) ) ;

	// create I/O event used for overlapped read

	os.hEvent = CreateEvent( NULL,    // no security
                            TRUE,    // explicit reset req
                            FALSE,   // initial event reset
                            NULL ) ; // no name
	if (os.hEvent == NULL)
	{
		AfxMessageBox( "Failed to create event for thread!", 
                  MB_ICONEXCLAMATION | MB_OK ) ;
		return ( FALSE ) ;
	}

	if (!SetCommMask( COMDEV( TalkInfo ), EV_RXCHAR ))
		return ( FALSE ) ;

	while ( CONNECTED( TalkInfo ) )
	{
		dwEvtMask = 0 ;
		WaitCommEvent( COMDEV( TalkInfo ), &dwEvtMask, NULL );
		//readNum++;
		
		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
		{
			do {
				if (nLength = ReadCommBlock( TalkInfo, (LPSTR) abIn, MAXBLOCK ))
				{
					//writeSize = nLength;
					WriteToBuf((BYTE *) abIn, nLength);
					dataReceived = TRUE;
				}		
			} while ( nLength > 0 ) ;
		}
	}
   // get rid of event handle
   CloseHandle( os.hEvent ) ;
   // clear information in structure (kind of a "we're done flag")
   THREADID( TalkInfo ) = 0 ;
   HTHREAD( TalkInfo ) = NULL ;

   return( TRUE ) ;

} // end of CommWatchProc()

//---------------------------------------------------------------------------
//  int NEAR ReadCommBlock( HWND hWnd, LPSTR lpszBlock, int nMaxLength )
//
//  Description:
//     Reads a block from the COM port and stuffs it into
//     the provided buffer.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpszBlock
//        block used for storage
//
//     int nMaxLength
//        max length of block to read
//
//  Win-32 Porting Issues:
//     - ReadComm() has been replaced by ReadFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------

int CCommFunctions::ReadCommBlock( CR10TalkInfo *TalkInfo, LPSTR lpszBlock, int nMaxLength )
{
	BOOL       fReadStat ;
	DWORD      dwErrorFlags;
	DWORD	   dwError;
	DWORD      dwLength;
	char       szError[ 128 ] ;
   
	// only try to read number of bytes in queue
	ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
	dwLength = min( (DWORD) nMaxLength, ComStat.cbInQue ) ;
	

	if (dwLength > 0)
	{
		fReadStat = ReadFile( COMDEV( TalkInfo ), lpszBlock,
		                    dwLength, &dwLength, &READ_OS( TalkInfo ) ) ;
	
		//OutputDebugString(szError);
		CString info = "\nBytes read: ";
		char number[5];
		for (UINT i = 0; i < dwLength; i++){
			wsprintf(number,"%i",(int)(unsigned char)lpszBlock[i]);
			info += "char(" + CString(number) + ") '" + lpszBlock[i] + "' ";
		}
		OutputDebugString((LPCSTR)info);

		if (!fReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				OutputDebugString("\n\rIO Pending");
				// We have to wait for read to complete.
				// This function will timeout according to the
				// CommTimeOuts.ReadTotalTimeoutConstant variable
				// Every time it times out, check for port errors

				while(!GetOverlappedResult( COMDEV( TalkInfo ),
					&READ_OS( TalkInfo ), &dwLength, TRUE ))
				{
					dwError = GetLastError();
					if(dwError == ERROR_IO_INCOMPLETE){
						// normal result if not finished
						continue;
					}
					else
					{
						// an error occurred, try to recover
						wsprintf( szError, "<CE-%u>", dwError ) ;
						//WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
						ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
						if ((dwErrorFlags > 0) && DISPLAYERRORS( TalkInfo ))
						{
							wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
							//WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
						}
						break;
					}
				}
			} // GetLastError() == ERROR_IO_PENDING
			else
			{
				// some other error occurred
				dwLength = 0 ;
				ClearCommError( COMDEV( TalkInfo ), &dwErrorFlags, &ComStat ) ;
				if ((dwErrorFlags > 0) && DISPLAYERRORS( TalkInfo ))
				{
					wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
					//WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
				}
			}		
		
		} // if (!fReadStat)

	}
	if (dwLength)
		lastReadTime = timeGetTime();
	return ( dwLength ) ;

} // end of ReadCommBlock()

