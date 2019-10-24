// SquaresGame.h : main header file for the SQUARESGAME application
//

#if !defined(AFX_SQUARESGAME_H__38A3A6F8_34E4_450C_BDD9_90DADAF9AE93__INCLUDED_)
#define AFX_SQUARESGAME_H__38A3A6F8_34E4_450C_BDD9_90DADAF9AE93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSquaresGameApp:
// See SquaresGame.cpp for the implementation of this class
//

#define SQUARE_SIZE			70
#define LINE_WIDTH			10
#define GAME_PANEL_HEIGHT	31
class CSquaresGameApp : public CWinApp
{
public:
	CSquaresGameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSquaresGameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSquaresGameApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUARESGAME_H__38A3A6F8_34E4_450C_BDD9_90DADAF9AE93__INCLUDED_)
