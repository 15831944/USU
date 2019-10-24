// Assignment 3.h : main header file for the ASSIGNMENT 3 application
//

#if !defined(AFX_ASSIGNMENT3_H__07ED1464_4F76_11D4_B01D_C9D7E1D3C933__INCLUDED_)
#define AFX_ASSIGNMENT3_H__07ED1464_4F76_11D4_B01D_C9D7E1D3C933__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


/////////////////////////////////////////////////////////////////////////////
// CAssignment3App:
// See Assignment 3.cpp for the implementation of this class
//

class CAssignment3App : public CWinApp
{
public:
	CAssignment3App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssignment3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAssignment3App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSIGNMENT3_H__07ED1464_4F76_11D4_B01D_C9D7E1D3C933__INCLUDED_)
