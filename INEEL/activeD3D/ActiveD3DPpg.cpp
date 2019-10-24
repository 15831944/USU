// ActiveD3DPpg.cpp : Implementation of the CActiveD3DPropPage property page class.

#include "stdafx.h"
#include "activeD3D.h"
#include "ActiveD3DPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CActiveD3DPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CActiveD3DPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CActiveD3DPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CActiveD3DPropPage, "ACTIVED3D.ActiveD3DPropPage.1",
	0x8a82c335, 0xdbea, 0x11d0, 0x8f, 0x12, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DPropPage::CActiveD3DPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CActiveD3DPropPage

BOOL CActiveD3DPropPage::CActiveD3DPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_ACTIVED3D_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DPropPage::CActiveD3DPropPage - Constructor

CActiveD3DPropPage::CActiveD3DPropPage() :
	COlePropertyPage(IDD, IDS_ACTIVED3D_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CActiveD3DPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DPropPage::DoDataExchange - Moves data between page and properties

void CActiveD3DPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CActiveD3DPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CActiveD3DPropPage message handlers
