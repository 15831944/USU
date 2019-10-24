// RiskBoardVCPpg.cpp : Implementation of the CRiskBoardVCPropPage property page class.

#include "stdafx.h"
#include "RiskBoardVC.h"
#include "RiskBoardVCPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CRiskBoardVCPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRiskBoardVCPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRiskBoardVCPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRiskBoardVCPropPage, "RISKBOARDVC.RiskBoardVCPropPage.1",
	0x8eb15bdf, 0x9d20, 0x11d5, 0xb0, 0x21, 0, 0x2, 0xe3, 0x5, 0x9e, 0xb4)


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCPropPage::CRiskBoardVCPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRiskBoardVCPropPage

BOOL CRiskBoardVCPropPage::CRiskBoardVCPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RISKBOARDVC_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCPropPage::CRiskBoardVCPropPage - Constructor

CRiskBoardVCPropPage::CRiskBoardVCPropPage() :
	COlePropertyPage(IDD, IDS_RISKBOARDVC_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRiskBoardVCPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCPropPage::DoDataExchange - Moves data between page and properties

void CRiskBoardVCPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CRiskBoardVCPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRiskBoardVCPropPage message handlers
