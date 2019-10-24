#if !defined(AFX_ACTIVED3DPPG_H__8A82C344_DBEA_11D0_8F12_444553540000__INCLUDED_)
#define AFX_ACTIVED3DPPG_H__8A82C344_DBEA_11D0_8F12_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ActiveD3DPpg.h : Declaration of the CActiveD3DPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CActiveD3DPropPage : See ActiveD3DPpg.cpp.cpp for implementation.

class CActiveD3DPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CActiveD3DPropPage)
	DECLARE_OLECREATE_EX(CActiveD3DPropPage)

// Constructor
public:
	CActiveD3DPropPage();

// Dialog Data
	//{{AFX_DATA(CActiveD3DPropPage)
	enum { IDD = IDD_PROPPAGE_ACTIVED3D };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CActiveD3DPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVED3DPPG_H__8A82C344_DBEA_11D0_8F12_444553540000__INCLUDED)
