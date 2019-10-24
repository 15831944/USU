// CommFunctions.h: interface for the CCommFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMFUNCTIONS_H__8CF1B572_6EC8_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_COMMFUNCTIONS_H__8CF1B572_6EC8_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "global defs.h"

#define USECOMM      // yes, we need the COMM API
//#include <afx.h>
//#include <windows.h>
//#include <windef.h>
//#include <winbase.h>

//#include <commdlg.h>
//#include <string.h>

#define MAXBLOCK        80 // THIS IS USED
#define BUF_SIZE		65537

extern int     readBufPos;
extern char    *readBuf;
extern int     defaultPort;
extern COMSTAT ComStat;
extern int     timeOuts;
extern BOOL    dataReceived;
extern DWORD   lastReadTime;

typedef struct tagCR10TalkInfo
{
   HANDLE  idComDev ;
   BYTE    bPort;
   BOOL    fConnected, fXonXoff, fDisplayErrors;
   BYTE    bByteSize, bFlowCtrl, bParity, bStopBits ;
   DWORD   dwBaudRate ;
   HANDLE      hPostEvent, hWatchThread, hWatchEvent ;
   HWND        hTermWnd ;
   DWORD       dwThreadID ;
   OVERLAPPED  osWrite, osRead ;
} CR10TalkInfo;

// macros ( for easier readability )

#define COMDEV( x ) (x -> idComDev)
#define PORT( x )   (x -> bPort)
#define CONNECTED( x ) (x -> fConnected)
#define XONXOFF( x ) (x -> fXonXoff)
#define BYTESIZE( x ) (x -> bByteSize)
#define FLOWCTRL( x ) (x -> bFlowCtrl)
#define PARITY( x ) (x -> bParity)
#define STOPBITS( x ) (x -> bStopBits)
#define BAUDRATE( x ) (x -> dwBaudRate)
#define DISPLAYERRORS( x ) (x -> fDisplayErrors)
#define POSTEVENT( x ) (x -> hPostEvent)
#define TERMWND( x ) (x -> hTermWnd)
#define HTHREAD( x ) (x -> hWatchThread)
#define THREADID( x ) (x -> dwThreadID)
#define WRITE_OS( x ) (x -> osWrite)
#define READ_OS( x ) (x -> osRead)

class CCommFunctions  
{
public:
	CCommFunctions();
	virtual ~CCommFunctions();
	static int ReadCommBlock( CR10TalkInfo *TalkInfo, LPSTR lpszBlock, int nMaxLength );
	static DWORD __stdcall CommWatchProc(void *lpdata);
	CR10TalkInfo * GetTalkInfoPtr();
protected:
	CR10TalkInfo *TalkInfo;
	BOOL CreateCR10TalkInfo();
	BOOL DestroyCR10TalkInfo(); 
	BOOL WriteCommBlock(const LPSTR, DWORD); 
	BOOL OpenConnection();
	BOOL SetupConnection();
	BOOL CloseConnection(); 
};

#endif // !defined(AFX_COMMFUNCTIONS_H__8CF1B572_6EC8_11D4_98D9_00A076801ACD__INCLUDED_)
