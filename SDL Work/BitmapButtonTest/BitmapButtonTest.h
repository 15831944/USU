// BitmapButtonTest.h : main header file for the BITMAPBUTTONTEST application
//

#if !defined(AFX_BITMAPBUTTONTEST_H__A4372579_9565_11D4_B01E_E5775E14782A__INCLUDED_)
#define AFX_BITMAPBUTTONTEST_H__A4372579_9565_11D4_B01E_E5775E14782A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBitmapButtonTestApp:
// See BitmapButtonTest.cpp for the implementation of this class
//

class CBitmapButtonTestApp : public CWinApp
{
public:
	CBitmapButtonTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitmapButtonTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBitmapButtonTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPBUTTONTEST_H__A4372579_9565_11D4_B01E_E5775E14782A__INCLUDED_)
