// RISK Tournament.h : main header file for the RISK TOURNAMENT application
//

#if !defined(AFX_RISKTOURNAMENT_H__9D3676B2_3EE6_467E_97DE_730A6EC257CE__INCLUDED_)
#define AFX_RISKTOURNAMENT_H__9D3676B2_3EE6_467E_97DE_730A6EC257CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "TypeDecs.h"
/////////////////////////////////////////////////////////////////////////////
// CRISKTournamentApp:
// See RISK Tournament.cpp for the implementation of this class
//

class CRISKTournamentApp : public CWinApp
{
public:
	CRISKTournamentApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRISKTournamentApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRISKTournamentApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKTOURNAMENT_H__9D3676B2_3EE6_467E_97DE_730A6EC257CE__INCLUDED_)
