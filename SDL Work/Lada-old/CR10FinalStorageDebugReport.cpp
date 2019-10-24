// CR10FinalStorageDebugReport.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "CR10FinalStorageDebugReport.h"
#include "Lada Control ModuleDoc.h"
#include "CommOperations.h"
#include "FSInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCR10FinalStorageDebugReport dialog


CCR10FinalStorageDebugReport::CCR10FinalStorageDebugReport(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CCR10FinalStorageDebugReport::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CCR10FinalStorageDebugReport)
	m_CR10Dsp = 0;
	m_LastDSP = 0;
	m_CollectFinalStorage = _T("");
	m_nAttempted = 0;
	m_nSuccessful = 0;
	m_ArrayID = 0;
	m_LastFailCode = 0;
	m_LastRetrieved = 0;
	//}}AFX_DATA_INIT
}


void CCR10FinalStorageDebugReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCR10FinalStorageDebugReport)
	DDX_Text(pDX, IDC_CR10_DSP, m_CR10Dsp);
	DDX_Text(pDX, IDC_LAST_DSP, m_LastDSP);
	DDX_Text(pDX, IDC_DO_FS, m_CollectFinalStorage);
	DDX_Text(pDX, IDC_N_ATTEMPTED, m_nAttempted);
	DDX_Text(pDX, IDC_N_SUCCESSFUL, m_nSuccessful);
	DDX_Text(pDX, IDC_ARRAY_ID, m_ArrayID);
	DDX_Text(pDX, IDC_LAST_FAIL_CODE, m_LastFailCode);
	DDX_Text(pDX, IDC_N_RETRIEVED, m_LastRetrieved);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCR10FinalStorageDebugReport, CDialog)
	//{{AFX_MSG_MAP(CCR10FinalStorageDebugReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCR10FinalStorageDebugReport message handlers
extern int LastDSP;
extern int DSP;

BOOL CCR10FinalStorageDebugReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (pDoc->commObject)
	{
		
		if (!pDoc->commObject->ExecuteACommand()) // this retrieves the current DSP
		{
			MessageBox("Failed to get CR10 DSP");
		}
		
	}

	m_LastDSP = LastDSP;
	m_CR10Dsp = DSP;
	m_ArrayID = pDoc->m_FSOutputTable[0].m_ArrayID;
	m_CollectFinalStorage = (pDoc->m_FSCollectionParam.m_Do?"TRUE":"FALSE");
	m_nAttempted = pDoc->m_FSCollectionParam.m_nAttemptedCollections;
	m_nSuccessful = pDoc->m_FSCollectionParam.m_nSuccessfulCollections;
	m_LastFailCode = pDoc->m_FSOutputTable[0].m_LastFailCode;
	m_LastRetrieved = pDoc->m_FSOutputTable[0].m_LastNumberRetrieved;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
