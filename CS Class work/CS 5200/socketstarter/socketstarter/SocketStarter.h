// SocketStarter.h : main header file for the SOCKETSTARTER application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "WatchDlg.h"
#include "afxsock.h"
#include "StreamSocket.h"

extern CString UnpackString(const CString& data);
extern CString PackString(const CString& rawdata);


/////////////////////////////////////////////////////////////////////////////
// CSocketStarterApp:
// See SocketStarter.cpp for the implementation of this class
//

class CSocketStarterApp : public CWinApp
{
public:
	CSocketStarterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSocketStarterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSocketStarterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
