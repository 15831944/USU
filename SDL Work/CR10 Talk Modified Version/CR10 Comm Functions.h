//#ifdef CR10_COMM_FUNCTIONS_H
//#define CR10_COMM_FUNCTIONS_H

#include "global defs.h"

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

class CommFunctions {
	//friend class CMainWindow;
	//friend CMainWindow::SetWindowNumber(int CONTROL_ID, int Number);
public:
	CommFunctions();
	~CommFunctions();
	static int ReadCommBlock( CR10TalkInfo *TalkInfo, LPSTR lpszBlock, int nMaxLength );
	static DWORD __stdcall CommWatchProc(void *lpdata);
protected:
	CR10TalkInfo *TalkInfo;
	BOOL CreateCR10TalkInfo();
	BOOL DestroyCR10TalkInfo(); 
	BOOL WriteCommBlock(const LPSTR, DWORD); 
	BOOL OpenConnection();
	BOOL SetupConnection();
	BOOL CloseConnection(); 
};

//#endif //#ifndef CR10_COMM_FUNCTIONS_H