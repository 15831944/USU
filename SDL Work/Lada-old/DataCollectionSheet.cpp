// DataCollectionSheet.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "DataCollectionSheet.h"
#include "LString.h"
#include "LadaStrings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern LString Strings;
/////////////////////////////////////////////////////////////////////////////
// CDataCollectionSheet

IMPLEMENT_DYNAMIC(CDataCollectionSheet, CPropertySheet)

CDataCollectionSheet::CDataCollectionSheet(CLADAControlModuleDoc * doc, UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&FinalStoragePage);
	AddPage(&InputLocationsPage);
	AddPage(&CamerasPage);
	pDoc = doc;
	FinalStoragePage.SetDocument(pDoc);
	InputLocationsPage.SetDocument(pDoc);
	CamerasPage.SetDocument(pDoc);
}

CDataCollectionSheet::CDataCollectionSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CDataCollectionSheet::~CDataCollectionSheet()
{
}


BEGIN_MESSAGE_MAP(CDataCollectionSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDataCollectionSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataCollectionSheet message handlers

BOOL CDataCollectionSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here
	SetTitle(Strings.get(IDS_AA0).GetBuffer(0));

	CTabCtrl* tab = GetTabControl();
	TCITEM tcItem;
	tcItem.mask = TCIF_TEXT;
	
	CString text = 	Strings.get(IDS_AA2);
	tcItem.pszText = text.GetBuffer(0);
	tab->SetItem(0,&tcItem);

	text = Strings.get(IDS_AA8);
	tcItem.pszText = text.GetBuffer(0);
	tab->SetItem(1,&tcItem);

	text = Strings.get(IDS_AA26);
	tcItem.pszText = text.GetBuffer(0);
	tab->SetItem(2,&tcItem);

	return bResult;
}
