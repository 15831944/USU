// InputLocationReadTest.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "InputLocationReadTest.h"
#include "Lada Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString GetTimeSpan(const CTimeSpan &C,int DisplayFields = 4);
/////////////////////////////////////////////////////////////////////////////
// CInputLocationReadTest dialog


CInputLocationReadTest::CInputLocationReadTest(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CInputLocationReadTest::IDD, pParent)
{
	pDoc = doc;
	//{{AFX_DATA_INIT(CInputLocationReadTest)
	m_AvgReadTime = 0.0;
	m_ReadFast = FALSE;
	m_ReadFreq = 0;
	m_ILsToRead = 0;
	m_ReadsDone = 0;
	m_ToBeServiced = 0;
	m_TotalTime = _T("");
	m_Servicing = 0;
	//}}AFX_DATA_INIT
}


void CInputLocationReadTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputLocationReadTest)
	DDX_Text(pDX, IDC_AVG_TIME, m_AvgReadTime);
	DDX_Check(pDX, IDC_READ_FAST, m_ReadFast);
	DDX_Text(pDX, IDC_READ_FREQ, m_ReadFreq);
	DDX_Text(pDX, IDC_NUM_READ, m_ILsToRead);
	DDX_Text(pDX, IDC_READS_DONE, m_ReadsDone);
	DDX_Text(pDX, IDC_TOBESERVICED, m_ToBeServiced);
	DDX_Text(pDX, IDC_TOTALTIME, m_TotalTime);
	DDX_Text(pDX, IDC_SERVICING, m_Servicing);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputLocationReadTest, CDialog)
	//{{AFX_MSG_MAP(CInputLocationReadTest)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_READ_FAST, OnReadFast)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputLocationReadTest message handlers

void CInputLocationReadTest::OnButton1() 
{
	// TODO: Add your control notification handler code here
	// start the test...
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	if (m_ReadFast)
	{
		int * locations = new int[this->m_ILsToRead];
		for (int i = 0; i < m_ILsToRead; i++)
			locations[i] = i+1;
		double * ptrReturn = new double[m_ILsToRead];
		m_IsTestStopped = FALSE;
		m_ReadsDone = 0;
		DWORD startTime = timeGetTime();
		while (!m_IsTestStopped)
		{
			pDoc->GetInputLocations(locations, m_ILsToRead, ptrReturn, FALSE);
			DWORD totalTime = timeGetTime() - startTime;
			m_ReadsDone++;
			m_AvgReadTime = totalTime / m_ReadsDone;
			m_TotalTime = GetTimeSpan(CTimeSpan(0,0,0,totalTime/1000),2);
			m_ToBeServiced = pDoc->ThreadsToBeServiced;
			m_Servicing = pDoc->ThreadsServicing;
			UpdateData(FALSE);
		}
		delete ptrReturn;
		delete locations;
	}
	else
	{
		int * locations = new int[this->m_ILsToRead];
		for (int i = 0; i < m_ILsToRead; i++)
			locations[i] = i+1;
		double * ptrReturn = new double[m_ILsToRead];
		m_IsTestStopped = FALSE;
		m_ReadsDone = 0;
		
		DWORD totalTime = 0;
		DWORD nextStartTime = timeGetTime();
		DWORD startTime = nextStartTime;
		DWORD curTime;
		while (!m_IsTestStopped)
		{
			while ((curTime = timeGetTime()) < nextStartTime);
			nextStartTime = curTime + m_ReadFreq;
			pDoc->GetInputLocations(locations, m_ILsToRead, ptrReturn, FALSE);
			totalTime += timeGetTime() - curTime;
			
			m_ReadsDone++;
			m_AvgReadTime = totalTime / m_ReadsDone;
			m_TotalTime = GetTimeSpan(CTimeSpan(0,0,0,(nextStartTime-startTime)/1000),2);
			m_ToBeServiced = pDoc->ThreadsToBeServiced;
			m_Servicing = pDoc->ThreadsServicing;
			UpdateData(FALSE);
		}
		delete ptrReturn;
		delete locations;

	}
}

void CInputLocationReadTest::OnButton2() 
{
	// TODO: Add your control notification handler code here
	// stop the test... 
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDOK)->EnableWindow(TRUE);
	
	m_IsTestStopped = TRUE;

}

BOOL CInputLocationReadTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputLocationReadTest::OnReadFast() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItem(IDC_TEXT1)->EnableWindow(!m_ReadFast);
	GetDlgItem(IDC_READ_FREQ)->EnableWindow(!m_ReadFast);
}

void CInputLocationReadTest::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}
