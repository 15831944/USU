// This is Version 1.0 PLEASE DOCUMENT CHANGES
// ManualSample.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ManualSample.h"
#include "Lstring.h"
#include "Ladastrings.h"
#include "CommOperations.h"
#include "Lada Control ModuleDoc.h"
#include "inputlocations.h"
#include "HistoryClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);	// Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Box
#undef MessageBox	
#define MessageBox MyMessageBox

extern CString ValueToString(double, int=2, BOOL applyLanguage = FALSE);// Returns the CString value of a double to int many decimal places
extern LString Strings;													// Contains all the text strings in both languages
extern CFont RussianArial;											// The font used
extern void SetItemFont(UINT controlID, CWnd *window);					// Sets and item to a font
extern CString IntToString(int number);
/////////////////////////////////////////////////////////////////////////////
// CManualSample dialog



// Constructor
// Doc is the current document
// stat becomes AutoStart
// prin contains the info for Checkout
CManualSample::CManualSample(CLADAControlModuleDoc* Doc, BOOL stat, CCheckout* prin, CWnd* pParent /*=NULL*/)
: CDialog((Doc->nGrowthChambers == 1 ? IDD_MANUALTEST1 : IDD_MANUALTEST2), pParent)
{
	step1=0;
	step2=0;
	print=NULL;
	if (prin)
	{
		print=prin;
		WillOutput=TRUE;
	}
	else 
		WillOutput=FALSE;
	pDoc=Doc;
	//{{AFX_DATA_INIT(CManualSample)
	m_mTime1 = _T("");
	m_mTime2 = _T("");
	//}}AFX_DATA_INIT
	data=new double[48];
	for (int x=0;x<48;x++)
		data[x]=0;
	AutoStart=stat;
}

// Destructor
CManualSample::~CManualSample()
{
	delete []data;
}

// Data Exchange
void CManualSample::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CManualSample)
	
	DDX_Control(pDX, IDC_START1, m_start1);
	DDX_Control(pDX, IDC_CHAMBER1, m_cchamber1);
	DDX_Text(pDX, IDC_MTIME1, m_mTime1);
	if (pDoc->nGrowthChambers == 2)
	{
		DDX_Control(pDX, IDC_CHAMBER2, m_cchamber2);
		DDX_Control(pDX, IDC_START2, m_start2);
		DDX_Text(pDX, IDC_MTIME2, m_mTime2);
	}
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CManualSample, CDialog)
	//{{AFX_MSG_MAP(CManualSample)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START1, OnStart1)
	ON_BN_CLICKED(IDC_START2, OnStart2)
	ON_BN_CLICKED(IDC_REFRESH_DATA_1, OnRefreshData1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CManualSample message handlers

// Initialization
// Sets font and strings
// Initializes List Controls
BOOL CManualSample::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	m_cchamber1.SetFont(&RussianArial);
	m_cchamber1.InsertColumn(0,Strings.get(IDS_H5));
	m_cchamber1.InsertColumn(1,Strings.get(IDS_H6));
	m_cchamber1.InsertColumn(2,Strings.get(IDS_H7));
	if (print)
		m_cchamber1.InsertColumn(3,Strings.get(IDS_H15));
	else
		m_cchamber1.InsertColumn(3,Strings.get(IDS_H8));
	GetDlgItem(IDC_START1)->EnableWindow((BOOL)pDoc->commObject);
	for (int x=0;x<8;x++)
		m_cchamber1.InsertItem(x,Strings.get(IDS_H5)+" "+IntToString(x+1));
	for (x=0;x<4;x++)
		m_cchamber1.SetColumnWidth(x,LVSCW_AUTOSIZE_USEHEADER);
	m_cchamber1.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	SetItemFont(IDC_START1,this);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_STEP1,this);
	SetItemFont(IDC_AIRTEMP,this);
	SetItemFont(IDC_REFRESH_DATA_1,this);
	SetItemFont(IDOK,this);
		
	if (pDoc->nGrowthChambers == 2)
	{
		m_cchamber2.SetFont(&RussianArial);
		m_cchamber2.InsertColumn(0,Strings.get(IDS_H5));
		m_cchamber2.InsertColumn(1,Strings.get(IDS_H6));
		m_cchamber2.InsertColumn(2,Strings.get(IDS_H7));
		m_cchamber2.InsertColumn(3,Strings.get(IDS_H8));
		GetDlgItem(IDC_START2)->EnableWindow((BOOL)pDoc->commObject);
		for (int x=0;x<8;x++)
			m_cchamber2.InsertItem(x,Strings.get(IDS_H5)+" "+ValueToString(double(x),0));
		for (x=0;x<4;x++)
			m_cchamber2.SetColumnWidth(x,LVSCW_AUTOSIZE_USEHEADER);
		m_cchamber2.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
		SetItemFont(IDC_START2,this);
		SetItemFont(IDC_TEXT2,this);
		SetItemFont(IDC_TEXT4,this);
		SetItemFont(IDC_STEP2,this);
	}
	
	/*
	if (pDoc->nGrowthChambers == 1)
	{
		// shrink the dialog box
		CRect rect;
		GetWindowRect(&rect);
		int ExpansionSize = 330;
		
		
		SetWindowPos(NULL,0,0, // this
			rect.Width() - ExpansionSize, rect.Height(), 
			SWP_FRAMECHANGED | SWP_NOMOVE | 
			SWP_SHOWWINDOW | SWP_NOZORDER );
		
		CRect okRect;
		GetDlgItem(IDOK)->GetWindowRect(&okRect);
	
		ScreenToClient(&okRect);
		GetDlgItem(IDOK)->SetWindowPos(NULL,okRect.left-ExpansionSize,okRect.top,0,0, SWP_FRAMECHANGED | 
			SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE );
	}
	*/

	SetStrings();
	
	if (WillOutput)
		OnStart1();
	else
		GetLastResults();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// Called when a timer goes off
void CManualSample::OnTimer(UINT nIDEvent) 
{
	int locations[] = { ITemp1, ITemp2, ITemp3, ITemp4, ITemp5, ITemp6, ITemp7, ITemp8,
				   IDTemp1, IDTemp2, IDTemp3, IDTemp4, IDTemp5, IDTemp6, IDTemp7, IDTemp8,
				   ISat1, ISat2, ISat3, ISat4, ISat5, ISat6, ISat7, ISat8 };
	
	if (nIDEvent==0)
	{
		if (step1==1)
		{	
			SetTimer(0,20000,NULL);
	
			for (int wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[0], 3, &data[0], 13 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (1) failed while calling GetInputLocations");
			
		
			m_cchamber1.SetItemText(0,1,ValueToString(data[0]));
			m_cchamber1.SetItemText(1,1,ValueToString(data[1]));
			m_cchamber1.SetItemText(2,1,ValueToString(data[2]));
			
		}
		else if (step1 == 2)
		{
			SetTimer(0,20000,NULL);
		
			for (int wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[6], 5, &data[6], 14 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (2) failed while calling GetInputLocations");
		
			for ( wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[16], 3, &data[16], 15 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (3) failed while calling GetInputLocations");
			

			m_cchamber1.SetItemText(6,1,ValueToString(data[6]));
			m_cchamber1.SetItemText(7,1,ValueToString(data[7]));
			
			diff[0]=data[8];
			diff[1]=data[9];
			diff[2]=data[10];
			data[8]+=data[0];
			data[9]+=data[1];
			data[10]+=data[2];
			
			m_cchamber1.SetItemText(0,2,ValueToString(data[8]));
			m_cchamber1.SetItemText(1,2,ValueToString(data[9]));
			m_cchamber1.SetItemText(2,2,ValueToString(data[10]));
			if (print)
			{
				m_cchamber1.SetItemText(0,3,ValueToString(diff[0]));
				m_cchamber1.SetItemText(1,3,ValueToString(diff[1]));
				m_cchamber1.SetItemText(2,3,ValueToString(diff[2]));
			}
			else
			{	
				m_cchamber1.SetItemText(0,3,ValueToString(data[16]));
				m_cchamber1.SetItemText(1,3,ValueToString(data[17]));
				m_cchamber1.SetItemText(2,3,ValueToString(data[18]));
			}	
		}
		if (step1==3)
		{
			SetTimer(0,20000,NULL);
			for (int wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[3], 3, &data[3], 16 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (4) failed while calling GetInputLocations");
			
		
			m_cchamber1.SetItemText(3,1,ValueToString(data[3]));
			m_cchamber1.SetItemText(4,1,ValueToString(data[4]));
			m_cchamber1.SetItemText(5,1,ValueToString(data[5]));
			
			for ( wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[14], 2, &data[14], 17 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (5) failed while calling GetInputLocations");
			
			diff[6]=data[14];
			diff[7]=data[15];
			data[14]+=data[6];
			data[15]+=data[7];
			
			for ( wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[22], 2, &data[22], 18 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (6) failed while calling GetInputLocations");
			

			m_cchamber1.SetItemText(6,2,ValueToString(data[14]));
			m_cchamber1.SetItemText(7,2,ValueToString(data[15]));
			if (print)
			{
				m_cchamber1.SetItemText(6,3,ValueToString(diff[6]));
				m_cchamber1.SetItemText(7,3,ValueToString(diff[7]));		
			}
			else
			{
				m_cchamber1.SetItemText(6,3,ValueToString(data[22]));
				m_cchamber1.SetItemText(7,3,ValueToString(data[23]));		
			}
			
		}
		if (step1==4)
		{
			for (int wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[11], 3, &data[11], 19 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (7) failed while calling GetInputLocations");
			
			diff[3]=data[11];
			diff[4]=data[12];
			diff[5]=data[13];
			data[11]+=data[3];
			data[12]+=data[4];
			data[13]+=data[5];

			for ( wTry = 0;  wTry < 5 && !pDoc->GetInputLocations( &locations[19], 3, &data[19], 20 ); wTry++);
			if (wTry==5)
				pDoc->m_ErrorFiles->WriteHistory("Error","Manual sample (8) failed while calling GetInputLocations");
			
			
			m_cchamber1.SetItemText(3,2,ValueToString(data[11]));
			m_cchamber1.SetItemText(4,2,ValueToString(data[12]));
			m_cchamber1.SetItemText(5,2,ValueToString(data[13]));
			if (print)
			{
				m_cchamber1.SetItemText(3,3,ValueToString(diff[3]));
				m_cchamber1.SetItemText(4,3,ValueToString(diff[4]));
				m_cchamber1.SetItemText(5,3,ValueToString(diff[5]));
			}
			else
			{
			m_cchamber1.SetItemText(3,3,ValueToString(data[19]));
			m_cchamber1.SetItemText(4,3,ValueToString(data[20]));
			m_cchamber1.SetItemText(5,3,ValueToString(data[21]));
			}
			m_start1.EnableWindow(FALSE);
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			GetDlgItem(IDC_REFRESH_DATA_1)->EnableWindow(TRUE);
			KillTimer(0);
			KillTimer(1);
			m_mTime1 = "0:00";
			UpdateData(FALSE);
			GetDlgItem(IDC_STEP1)->SetWindowText(Strings.get(IDS_H9+step1+1));
			if (AutoStart)
				OnOK();
			return;
		}
		step1++;
		GetDlgItem(IDC_STEP1)->SetWindowText(Strings.get(IDS_H9+step1));

	}
	CTimeSpan TimeLeft = FinishTime - CTime::GetCurrentTime();
	m_mTime1 = TimeLeft.Format("%M:%S");
	m_mTime1 = m_mTime1.Mid(1);
	UpdateData(FALSE);				// Updates Time elapsed
}

// Sets the text to the current language
void CManualSample::OnRefreshData1()
{
	GetLastResults();

}

void CManualSample::SetStrings()	
{
	SetWindowText(Strings.get(IDS_H0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_H1));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_H3));
	GetDlgItem(IDC_START1)->SetWindowText(Strings.get(IDS_H2));
	GetDlgItem(IDC_AIRTEMP)->SetWindowText(Strings.get(IDS_H16));
	GetDlgItem(IDC_REFRESH_DATA_1)->SetWindowText(Strings.get(IDS_H17));
	GetDlgItem(IDC_STEP1)->SetWindowText(Strings.get(IDS_H9+step1));


	if (pDoc->nGrowthChambers == 2)
	{
		GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_H1));
		GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_H4));
		GetDlgItem(IDC_START1)->SetWindowText(Strings.get(IDS_H2));
		GetDlgItem(IDC_STEP1)->SetWindowText(Strings.get(IDS_H9+step2));
	}

	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	

}

// Returns the value of the input location location
double CManualSample::Comm(int location)
{
	double ret;
	//pDoc->StartCommBlock(37);
	//if (!pDoc->commObject->ExecuteICommand(location,ret,NULL,3))
	//	ret = -99999.00;
	//pDoc->EndCommBlock();
	pDoc->GetInputLocations(&location,1,&ret, 21);
	return ret;
}

// Called when the OK Button is pressed
// Stores the data gathered in Print
void CManualSample::OnOK() 
{
	if (WillOutput)
	{
		for (int x=0;x<8;x++)
		{
			print->data[x+12][1]=ValueToString(diff[x],2);
			print->data[x+4][1]=ValueToString(data[x],2);
			print->data[x+20][1]=ValueToString(data[x+16],2);
		}		
	}
	CDialog::OnOK();
}

BOOL CManualSample::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		LVCOLUMN* x=new LVCOLUMN;
		char* tempst=new char[20];
		for (int y=0;y<4;y++)
		{
			x->mask=LVCF_TEXT;
			x->pszText=tempst;
			x->cchTextMax=20;
			m_cchamber1.GetColumn(y,x);
			CString a;
			if (print && y==3)
				a=Strings.get(IDS_H15);
			else
				a=Strings.get(IDS_H5+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_cchamber1.SetColumn(y,x);
			if (pDoc->nGrowthChambers == 2)
				m_cchamber2.SetColumn(y,x);
		}
		delete [] tempst;
		delete [] x;
		for (y=0;y<8;y++)
		{
			m_cchamber1.SetItemText(y,0,Strings.get(IDS_H5)+" "+ValueToString(double(y),0));
			if (pDoc->nGrowthChambers == 2)
				m_cchamber2.SetItemText(y,0,Strings.get(IDS_H5)+" "+ValueToString(double(y),0));
		}
		return TRUE;
	}	
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == 13)
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CManualSample::OnStart1() 
{
	// TODO: Add your control notification handler code here
	step1=1;
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	GetDlgItem(IDC_REFRESH_DATA_1)->EnableWindow(FALSE);
	m_start1.EnableWindow(FALSE);
	memset(data,0,sizeof(double) * 8 * 6 );
	pDoc->commObject->SetFlag(1,TRUE);
	FinishTime=CTime::GetCurrentTime() + CTimeSpan(0,0,0,70);  // 80 seconds
	int y;
	y=SetTimer(0,10000,NULL);
	y=SetTimer(1,1000,NULL);
	// no timer callback 
	int location = IInlet;  // this temperature probe is the closest to the root module
	double airTemp;
	pDoc->GetInputLocations(&location,1,&airTemp,34);
	GetDlgItem(IDC_AIR_TEMP)->SetWindowText(ValueToString(airTemp));
	GetDlgItem(IDC_STEP1)->SetWindowText(Strings.get(IDS_H9+step1));
}

void CManualSample::OnStart2() 
{
	// TODO: Add your control notification handler code here
	
}

void CManualSample::GetLastResults()
{
	int locations[] = { ITemp1, ITemp2, ITemp3, ITemp4, ITemp5, ITemp6, ITemp7, ITemp8,
				   IDTemp1, IDTemp2, IDTemp3, IDTemp4, IDTemp5, IDTemp6, IDTemp7, IDTemp8,
				   ISat1, ISat2, ISat3, ISat4, ISat5, ISat6, ISat7, ISat8 };
	pDoc->GetInputLocations(locations,24,data, 22);

	for (int i = 0; i < 8; i++)
	{
		diff[i] = data[i + 8]; 
		data[i + 8] += data[i];
	}

	int wData = 0;
	for (int column = 1; column < 4; column++)
	{
		for (int row = 0; row < 8; row++)
			m_cchamber1.SetItemText(row,column,ValueToString(data[wData++]));	
	}
	if (WillOutput)
	{
		for (int row = 0; row < 8; row++)
			m_cchamber1.SetItemText(row,3,ValueToString(diff[row]));	
	}
}
