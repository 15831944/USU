#if !defined(AFX_ACTIVED3D_H__8A82C33A_DBEA_11D0_8F12_444553540000__INCLUDED_)
#define AFX_ACTIVED3D_H__8A82C33A_DBEA_11D0_8F12_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// activeD3D.h : main header file for ACTIVED3D.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CActiveD3DApp : See activeD3D.cpp for implementation.

class CActiveD3DApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVED3D_H__8A82C33A_DBEA_11D0_8F12_444553540000__INCLUDED)
