// ImportFSLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ImportFSLDlg.h"
#include "LADA Control ModuleDoc.h"
#include "FSInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportFSLDlg dialog


CImportFSLDlg::CImportFSLDlg(CLADAControlModuleDoc *doc, CFSInfo * pFSInfo, CWnd* pParent /*=NULL*/)
	: CDialog(CImportFSLDlg::IDD, pParent)
{
	m_ptrFSInfo = pFSInfo;
	pDoc = doc;
	//{{AFX_DATA_INIT(CImportFSLDlg)
	m_FileName = _T("");
	m_ArrayID = -1;
	m_NumberDataPoints = 0;
	//}}AFX_DATA_INIT
	dataNames = NULL; 
	nDataPoints = NULL;
	ArrayID = NULL;
}
CImportFSLDlg::~CImportFSLDlg()
{
	delete [] dataNames; 
	delete [] nDataPoints;
	delete [] ArrayID;
}

void CImportFSLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportFSLDlg)
	DDX_Control(pDX, IDC_ARRAY_ID, m_cArrayID);
	DDX_Control(pDX, IDC_FS_LIST, m_FSList);
	DDX_Text(pDX, IDC_FILE_NAME, m_FileName);
	DDX_CBIndex(pDX, IDC_ARRAY_ID, m_ArrayID);
	DDX_Text(pDX, IDC_NUMBER, m_NumberDataPoints);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportFSLDlg, CDialog)
	//{{AFX_MSG_MAP(CImportFSLDlg)
	ON_CBN_SELCHANGE(IDC_ARRAY_ID, OnSelchangeArrayId)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportFSLDlg message handlers

void CImportFSLDlg::OnSelchangeArrayId() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	m_NumberDataPoints = nDataPoints[m_ArrayID];

	m_FSList.ResetContent();
	for (int i = 0; i < nDataPoints[m_ArrayID]; i++)
		m_FSList.AddString(dataNames[m_ArrayID * 200 + i]);
	UpdateData(FALSE);
}

extern CString IntToString(int number);
extern BOOL AssociateFSLFile(CString &fileName, CString *&dataNames, int *&ArrayID, int maxIDs, int maxPoints, int &numIDs, int *&nDataPoints);
BOOL CImportFSLDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(TRUE);
	
	CWaitCursor wCursor;

	m_ArrayID = 0;

	if (AssociateFSLFile(m_FileName, dataNames, ArrayID, 5, 200, numIDs, nDataPoints))
	{
		if (numIDs == 0)
		{
			MessageBox("No array IDs found in this file.");	
		}
		else
		{
			for (int i = 0; i < numIDs; i++)
				m_cArrayID.AddString(IntToString(ArrayID[i]));
			m_NumberDataPoints = nDataPoints[m_ArrayID];

			for (i = 0; i < nDataPoints[m_ArrayID]; i++)
				m_FSList.AddString(dataNames[m_ArrayID * 200 + i]);
		}
	}
	else
		EndDialog(IDABORT);
	
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportFSLDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();

	m_ptrFSInfo->m_ArrayID = ArrayID[m_ArrayID];
	
	m_ptrFSInfo->m_nDataItems = m_NumberDataPoints;
	if (m_ptrFSInfo->m_DataNames)
		delete [] m_ptrFSInfo->m_DataNames;
	m_ptrFSInfo->m_DataNames = new CString[m_NumberDataPoints];

	for (int i = 0; i < m_ptrFSInfo->m_nDataItems; i++)
	{
		m_ptrFSInfo->m_DataNames[i] = dataNames[m_ArrayID * 200 + i];		
	}
	 	

	CDialog::OnOK();
}
