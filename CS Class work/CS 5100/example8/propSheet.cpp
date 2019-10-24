// propSheet.cpp : implementation file
//

#include "stdafx.h"
#include "junk3.h"
#include "propSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CpropSheet

IMPLEMENT_DYNAMIC(CpropSheet, CPropertySheet)

CpropSheet::CpropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_page1);
	AddPage(&m_page2);
}

CpropSheet::CpropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_page1);
	AddPage(&m_page2);
}

CpropSheet::~CpropSheet()
{
}


BEGIN_MESSAGE_MAP(CpropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CpropSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CpropSheet message handlers
