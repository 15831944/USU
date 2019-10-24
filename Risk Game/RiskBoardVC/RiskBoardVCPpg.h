#if !defined(AFX_RISKBOARDVCPPG_H__8EB15BED_9D20_11D5_B021_0002E3059EB4__INCLUDED_)
#define AFX_RISKBOARDVCPPG_H__8EB15BED_9D20_11D5_B021_0002E3059EB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RiskBoardVCPpg.h : Declaration of the CRiskBoardVCPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCPropPage : See RiskBoardVCPpg.cpp.cpp for implementation.

class CRiskBoardVCPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CRiskBoardVCPropPage)
	DECLARE_OLECREATE_EX(CRiskBoardVCPropPage)

// Constructor
public:
	CRiskBoardVCPropPage();

// Dialog Data
	//{{AFX_DATA(CRiskBoardVCPropPage)
	enum { IDD = IDD_PROPPAGE_RISKBOARDVC };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CRiskBoardVCPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RISKBOARDVCPPG_H__8EB15BED_9D20_11D5_B021_0002E3059EB4__INCLUDED)
