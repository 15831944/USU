// client.h : main header file for the CLIENT application
//

#if !defined(AFX_CLIENT_H__4C839D46_A76F_11D5_B509_000086204AC6__INCLUDED_)
#define AFX_CLIENT_H__4C839D46_A76F_11D5_B509_000086204AC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../common/Configuration.h"

/////////////////////////////////////////////////////////////////////////////
// CClientApp:
// See client.cpp for the implementation of this class
//

class CClientApp : public CWinApp
{
protected:
	CString			server_ip;
	UINT			server_port;
	Configuration*	conf;

public:
	CClientApp();
	UINT getServerPort(void) const { return server_port; }
	const CString getServerIP(void) const { return server_ip; }

	~CClientApp()
		{  if (conf) delete conf; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENT_H__4C839D46_A76F_11D5_B509_000086204AC6__INCLUDED_)
