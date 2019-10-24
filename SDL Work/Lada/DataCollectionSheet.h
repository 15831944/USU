#if !defined(AFX_DATACOLLECTIONSHEET_H__85E90365_2CDE_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_DATACOLLECTIONSHEET_H__85E90365_2CDE_11D5_B690_0080AD8FBDCC__INCLUDED_

#include "FinalStoragePage.h"	// Added by ClassView
#include "InputLocationsPage.h"	// Added by ClassView
#include "CamerasPage.h"	// Added by ClassView


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataCollectionSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionSheet
class CLADAControlModuleDoc;

class CDataCollectionSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CDataCollectionSheet)

// Construction
public:
	CDataCollectionSheet(CLADAControlModuleDoc * doc, UINT nIDCaption = IDS_PROP_SHEET_TITLE, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CDataCollectionSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CLADAControlModuleDoc * pDoc;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataCollectionSheet)
	public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetStrings();
	CCamerasPage CamerasPage;
	CInputLocationsPage InputLocationsPage;
	CFinalStoragePage FinalStoragePage;
	virtual ~CDataCollectionSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDataCollectionSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATACOLLECTIONSHEET_H__85E90365_2CDE_11D5_B690_0080AD8FBDCC__INCLUDED_)
