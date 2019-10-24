#if !defined(AFX_RISKBOARDVC_H__8EB15BE4_9D20_11D5_B021_0002E3059EB4__INCLUDED_)
#define AFX_RISKBOARDVC_H__8EB15BE4_9D20_11D5_B021_0002E3059EB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RiskBoardVC.h : main header file for RISKBOARDVC.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCApp : See RiskBoardVC.cpp for implementation.

class CRiskBoardVCApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKBOARDVC_H__8EB15BE4_9D20_11D5_B021_0002E3059EB4__INCLUDED)
