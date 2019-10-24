#include <afxwin.h>
#include <windows.h>
#include <VFW.H>

class CVideoCaptureWindow : public CFrameWnd {
public:
	CVideoCaptureWindow();
private:
};

CVideoCaptureWindow::CVideoCaptureWindow(){

	int nID = 0;

	HINSTANCE hLibrary;  
    hLibrary = LoadLibrary("AVICAP32.DLL"); // Load the DLL now
	typedef HWND (VFWAPI * lpFunc1)(LPCSTR, DWORD, int, int, int, int, HWND, int);
	
	lpFunc1 CreateCaptureWindow = NULL;
	
    if (hLibrary != NULL)    {
        CreateCaptureWindow = (lpFunc1) GetProcAddress(hLibrary, "capCreateCaptureWindowA");
        if (CreateCaptureWindow == NULL) {             
			MessageBox( "System file not present (AVICAP32.DLL).", 
          "Initialization Error", 
          MB_ICONEXCLAMATION );
		}
	}
	
	Create ( NULL, "Video Capture Window", WS_OVERLAPPEDWINDOW, CRect(100, 100, 400, 400));
	
	HWND VCWin1;
	
	HWND hParentWnd = *this;	
	
	char message[] = "No driver was found ( )";
	
	VCWin1 = CreateCaptureWindow ( "My Own Capture Window", 
		WS_CHILD | WS_VISIBLE , 0, 0, 300, 300, hParentWnd, nID);
			
	if (!capDriverConnect(  VCWin1, nID )){
		message[21] = nID + '0';
		MessageBox( message, "Initialization Error", MB_ICONEXCLAMATION );
	}

//	}
	if (!capGrabFrame( VCWin1 )){
		MessageBox( "No camera present.", 
        "Initialization Error", 
        MB_ICONEXCLAMATION );
		
	}
}

class CVideoApp : public CWinApp {
public:
	BOOL InitInstance(){
		m_pMainWnd = new CVideoCaptureWindow();
		m_pMainWnd->ShowWindow( m_nCmdShow );
		m_pMainWnd->UpdateWindow();
		return TRUE;
	}
} VideoWindow1;