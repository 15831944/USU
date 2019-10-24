// InputLocationSetTest.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "InputLocationSetTest.h"
#include "Lada Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputLocationSetTest dialog
extern CString GetTimeSpan(const CTimeSpan &C,int DisplayFields = 4);

CInputLocationSetTest::CInputLocationSetTest(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CInputLocationSetTest::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CInputLocationSetTest)
	m_AvgWriteTime = 0.0;
	m_WriteFast = FALSE;
	m_WriteFreq = 0;
	m_WritesDone = 0;
	m_TotalTime = _T("");
	m_nFailed = 0;
	m_useICommand = FALSE;
	//}}AFX_DATA_INIT
}


void CInputLocationSetTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputLocationSetTest)
	DDX_Text(pDX, IDC_AVG_TIME, m_AvgWriteTime);
	DDX_Check(pDX, IDC_WRITE_FAST, m_WriteFast);
	DDX_Text(pDX, IDC_WRITE_FREQ, m_WriteFreq);
	DDX_Text(pDX, IDC_WRITES_DONE, m_WritesDone);
	DDX_Text(pDX, IDC_TOTALTIME, m_TotalTime);
	DDX_Text(pDX, IDC_NO_FAILED, m_nFailed);
	DDX_Check(pDX, IDC_I_COMMAND, m_useICommand);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputLocationSetTest, CDialog)
	//{{AFX_MSG_MAP(CInputLocationSetTest)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputLocationSetTest message handlers

void CInputLocationSetTest::OnButton1() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	// start the test...
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_nFailed = 0;
	m_IsTestStopped = FALSE;
	m_WritesDone = 0;
	
	if (m_WriteFast)
	{
		
		DWORD startTime = timeGetTime();
		while (!m_IsTestStopped)
		{
			if (pDoc->commObject)
			{
				if (m_useICommand)
				{
					double oldValue;
					char newValue[] = "32.00";
					if (!pDoc->commObject->ExecuteICommand(1, oldValue, newValue, 3 ))
						m_nFailed++;

				}
				else
				{
					if (!pDoc->commObject->SetInputLocation( 1, 32, 106 ))
						m_nFailed++;
				}

				DWORD totalTime = timeGetTime() - startTime;
				m_WritesDone++;
				m_AvgWriteTime = totalTime / m_WritesDone;
				m_TotalTime = GetTimeSpan(CTimeSpan(0,0,0,totalTime/1000),2);
				UpdateData(FALSE);
			}
			else
				OnButton2();
		}
	}
	else
	{
		
		
		DWORD totalTime = 0;
		DWORD nextStartTime = timeGetTime();
		DWORD startTime = nextStartTime;
		DWORD curTime;
		while (!m_IsTestStopped)
		{
			if (pDoc->commObject)
			{
				while ((curTime = timeGetTime()) < nextStartTime);
				nextStartTime = curTime + m_WriteFreq;
				if (m_useICommand)
				{
					double oldValue;
					char newValue[] = "32.00";
					if (!pDoc->commObject->ExecuteICommand(1, oldValue, newValue, 3 ))
						m_nFailed++;
				}
				else
				{
					if (!pDoc->commObject->SetInputLocation( 1, 32, 107 ))
						m_nFailed++;
				}
				totalTime += timeGetTime() - curTime;
				
				m_WritesDone++;
				m_AvgWriteTime = totalTime / m_WritesDone;
				m_TotalTime = GetTimeSpan(CTimeSpan(0,0,0,(nextStartTime-startTime)/1000),2);
				UpdateData(FALSE);
			}
			else
				OnButton2();
		}
	
	}
}

void CInputLocationSetTest::OnButton2() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	// stop the test... 
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	
	m_IsTestStopped = TRUE;
}

BOOL CInputLocationSetTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputLocationSetTest::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
