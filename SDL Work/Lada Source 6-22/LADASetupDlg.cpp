// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LADASetupDlg.cpp : implementation file
// 1-11-01 12:30 pm added * to display bitmap

#include "stdafx.h"
#include "Lada Control Module.h"
#include "LADASetupDlg.h"
#include "Step.h"
#include "LADA Control ModuleDoc.h"
#include "Ladastrings.h"
#include "SystemDiagDlg.h"
#include "Verify.h"
#include "ParamDlg.h"
#include "LadaTest.h"
#include "fstream.h"
#include "Checkout.h"
#include "Display.h"
#include "WetupSettingsDlg.h"
#include "LString.h"
#include "Camera.h"
#include "inputlocations.h"
#include "ProgressDialog.h"
#include "manualsample.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define TURN_ON_POWER		0
#define POWER_ON			1
#define INITIALIZE_CR10X	2
#define VIEW_VOLTAGES		3
#define VIEW_MEASUREMENTS	4
#define MAIN_TEST			5
#define DISPLAY				6
#define TAKE_PICTURE		7

extern CFont RussianArial;
extern CCamera * cameraDlg;
extern void SetItemFont(UINT controlID, CWnd *window);
extern LString Strings;
extern UINT NotificationBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK, BOOL IsModal = FALSE, DWORD Duration = INFINITE);

extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK); // Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);		// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);				// Message Box
#undef MessageBox
#define MessageBox MyMessageBox
extern BOOL LoadBMPImage(LPCTSTR sBMPFile, CBitmap &bitmap, CPalette *pPal);
extern CString ValueToString(double value, int dPlaces=2, BOOL applyLanguage = FALSE);

/////////////////////////////////////////////////////////////////////////////
// CLADASetupDlg dialog
// Constructor
// setup if this is Setup or Checkout
// op is the current document
CLADASetupDlg::CLADASetupDlg(CheckOutType type, CLADAControlModuleDoc* op,CWnd* pParent /*=NULL*/)
	: CDialog(CLADASetupDlg::IDD, pParent), fout("hello.txt")
{
	//{{AFX_DATA_INIT(CLADASetupDlg)
	m_VStep = _T("");
	m_VTitle = _T("");
	m_VText = _T("");
	m_VPicture = _T("");
	pDoc = op;
	Type=type;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	print = NULL;
	m_step = NULL;
	m_IsAutomatic = false;
	ppal = NULL;
	m_Bitmap = NULL;
}


CLADASetupDlg::~CLADASetupDlg()
{
	delete [] m_StepsPerPage;
	delete print;
	delete [] m_step;
	delete ppal;
	delete m_Bitmap;
}

// Data Exchange
void CLADASetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLADASetupDlg)
	DDX_Control(pDX, IDC_PICTURE, m_CPicture);
	DDX_Control(pDX, IDC_TEXT, m_CText);
	DDX_Control(pDX, ID_NEXT, m_CNext);
	DDX_Control(pDX, ID_BACK, m_CBack);
	DDX_Text(pDX, IDC_STEP, m_VStep);
	DDV_MaxChars(pDX, m_VStep, 9);
	DDX_Text(pDX, IDC_TITLE, m_VTitle);
	DDV_MaxChars(pDX, m_VTitle, 60);
	DDX_Text(pDX, IDC_TEXT, m_VText);
	DDX_Text(pDX, IDC_PICTURE, m_VPicture);
	//}}AFX_DATA_MAP
}

// Message Maps
BEGIN_MESSAGE_MAP(CLADASetupDlg, CDialog)
	//{{AFX_MSG_MAP(CLADASetupDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(ID_BACK, OnBack)
	ON_BN_CLICKED(IDC_TEST_CAMERA, OnTestCamera)
	ON_COMMAND_RANGE(IDC_CHECK1, IDC_CHECK9, OnCheck)
	ON_WM_SYSCOMMAND()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1,OnButton1)
END_MESSAGE_MAP()

void CLADASetupDlg::OnButton1()
{
	CManualSample dlg(pDoc,FALSE,print);
	dlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLADASetupDlg message handlers

void CLADASetupDlg::OnTestCamera()
{
	if (cameraDlg)
	{
		//cameraDlg->ShowWindow(SW_SHOW);
		cameraDlg->SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
		cameraDlg->AutoPicture(0);
	}

}

// Initialization
// Sets fonts, loads first picture, and sets step info
BOOL CLADASetupDlg::OnInitDialog()
{
	checknumber=0;
	m_stepnumber=0;
	CheckTrue=FALSE;
	CDialog::OnInitDialog();
	SetFont(&RussianArial);
	for (int x=0;x<9;x++)
		SetItemFont(IDC_CHECK1+x,this);
	SetItemFont(ID_NEXT,this);
	SetItemFont(ID_BACK,this);
	SetItemFont(IDC_STEP,this);
	SetItemFont(IDC_TITLE,this);
	SetItemFont(IDC_TEXT,this);
	SetItemFont(IDC_TEXT1,this);	
	ppal=new CPalette;
	m_Bitmap=new CBitmap;
	LoadBMPImage("C:\\Lada\\LADAPics\\Setup01.bmp",*m_Bitmap,ppal);
	if (Type==Setup)
	{	
		SetWindowText(Strings.get(IDS_A1));
		m_numsteps=6;
		m_step=new Stepinfo[m_numsteps];
		m_StepsPerPage = new int[m_numsteps];
		m_StepsPerPage[0] = 7;
		m_StepsPerPage[1] = 3;
		m_StepsPerPage[2] = 5;
		m_StepsPerPage[3] = 3;
		m_StepsPerPage[4] = 3;
		m_StepsPerPage[5] = 3;
		
		for (int x=0;x<m_numsteps;x++)
		{
			CString temp[9];
			for (int y=0;y<9;y++)
				temp[y]=Strings.get(IDS_S01+10*x+y);
			m_step[x]=Stepinfo(x+1,Strings.get(IDS_S00+10*x),m_StepsPerPage[x],temp,Strings.get(IDS_S00+10*x));
		}
	}
	else if (Type==CheckOut)
	{
		CameraTestButton.AutoLoad(IDC_TEST_CAMERA,this);
		SetWindowText(Strings.get(IDS_A2));
		print=new CCheckout;
		if (MessageBox(IDS_M_AUTOMATIC_CHECK_OUT,IDS_PROGRAM_NAME,MB_YESNO|MB_ICONQUESTION)==IDYES)
			m_IsAutomatic = true;
	
		m_numsteps=1;
		m_step=new Stepinfo[1];
		m_StepsPerPage = new int[m_numsteps];
		m_StepsPerPage[0] = 7;

		for (int x=0;x<m_numsteps;x++)
		{
			CString temp[9];
			for (int y=0;y<9;y++)
				temp[y]=Strings.get(IDS_CO11+10*x+y);
			m_step[x]=Stepinfo(x+1,Strings.get(IDS_CO10+10*x),m_StepsPerPage[x],temp,Strings.get(IDS_CO10+10*x));

		}

		fout << "Parameter Designation\tIndication" << endl;
	}

	else if (Type==Tensiometer)
	{
		SetWindowText(Strings.get(IDS_TENSIOMETER));
		m_numsteps=2;
		m_step=new Stepinfo[2];
		m_StepsPerPage=new int [m_numsteps];
		m_StepsPerPage[0]=9;
		m_StepsPerPage[1]=9;
		for (int x=0;x<m_numsteps;x++)
		{
			CString temp[9];
			for (int y=0;y<9;y++)
				temp[y]=Strings.get(IDS_TENSIOMETER_STEP_1+10*x+y);
			m_step[x]=Stepinfo(x+1,Strings.get(IDS_TENSIOMETER_STEP_0+10*x),m_StepsPerPage[x],temp,Strings.get(IDS_TENSIOMETER+10*x));

		}
	}


	
	ResetStrings();
	checknumber=0;
	m_stepnumber=0;	
	Reset(0);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetStrings();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// ???????????
void CLADASetupDlg::OnDestroy()
{
//	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// Paints to the screen
void CLADASetupDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLADASetupDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// This is called when the Next-> button is pressed and proceeds to the next step
void CLADASetupDlg::OnNext() 
{
	m_stepnumber++;
	if (m_stepnumber==m_numsteps)
		OnOK();
	else
		Reset(m_stepnumber);
}

// This is called when the <-Back button is pressed and returns to the previous step
void CLADASetupDlg::OnBack() 
{
	m_stepnumber--;
	if (m_stepnumber<0)
		m_stepnumber=0;
	Reset(m_stepnumber);
}

// This is called\\ after the Next-> or <-Back button is pressed 
//  to reset the dialog and load the next step where int is the next step
void CLADASetupDlg::Reset(int Step)
{
	CheckTrue=FALSE;
	int y=m_step[Step].m_checks;
	for (int x=0;x<9;x++)
	{
		((CButton*)GetDlgItem(IDC_CHECK1+x))->SetCheck(FALSE);
		if (y<(x+1))
			((CButton*)GetDlgItem(IDC_CHECK1+x))->ShowWindow(SW_HIDE);
		else
			((CButton*)GetDlgItem(IDC_CHECK1+x))->ShowWindow(SW_SHOW);

		((CButton*)GetDlgItem(IDC_CHECK1+x))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_CHECK1+x))->SetWindowText(m_step[Step].m_Steps[x]);
		UpdateData(TRUE);
	}
	((CButton*)GetDlgItem(IDC_CHECK1))->EnableWindow(TRUE);
	if (Step==0)
		m_CBack.EnableWindow(FALSE);
	else
		m_CBack.EnableWindow(TRUE);
	if (Step==m_numsteps-1)
		m_CNext.SetWindowText(Strings.get(IDS_S4));
	else
		m_CNext.SetWindowText(Strings.get(IDS_S3));
		m_VStep=Strings.get(IDS_S1)+CString(m_step[Step].m_step/10+'0')+CString(m_step[Step].m_step%10+'0');
	m_VTitle=m_step[Step].m_title;
	m_VText=m_step[Step].m_Text;
	UpdateData(FALSE);
	GetDlgItem(IDC_CHECK1)->SetFocus();
	checknumber=0;
	CheckCheck(m_stepnumber);
}

// This is called when a check is checked and changes the explanation and picture for the next step
void CLADASetupDlg::CheckCheck(int temp)
{
	UpdateData(TRUE);
	if (!(m_step[m_stepnumber].m_checks-checknumber-1))
	{
		m_CNext.EnableWindow(TRUE);
		m_CNext.SetFocus();
		if ((m_stepnumber+1)==m_numsteps)
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_ALL_STEPS_COMPLETE));
		else
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_STEPS_COMPLETE));
	}
	else
	{
		delete m_Bitmap;
		m_Bitmap=new CBitmap;
		m_CNext.EnableWindow(FALSE);
		if (Type==Setup)
		{
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_V00+10*m_stepnumber+checknumber+CheckTrue));
			CString name=workingDirectory+"\\LadaPics\\Setup"+char('0'+m_stepnumber)+char('0'+checknumber+CheckTrue)+".bmp";
   			LoadBMPImage(name.GetBuffer(0),*m_Bitmap,ppal);
		}
		else if (Type==CheckOut)
		{
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AB0+9*m_stepnumber+checknumber+CheckTrue));
			CString name=workingDirectory+"\\LadaPics\\CheckOut"+char('0'+m_stepnumber)+char('0'+checknumber+CheckTrue)+".bmp";
   			LoadBMPImage(name.GetBuffer(0),*m_Bitmap,ppal);
		}
		else if (Type==Tensiometer)
		{
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_TENS_STEP_EXPLANATION_1+9*m_stepnumber+checknumber+CheckTrue));
			CString name=workingDirectory+"\\LadaPics\\Wetup"+char('0'+m_stepnumber)+char('0'+checknumber+CheckTrue)+".bmp";
   			LoadBMPImage(name.GetBuffer(0),*m_Bitmap,ppal);
		}

	}
	m_CPicture.SetBitmap((HBITMAP)*m_Bitmap);	
}

// During Checkout this will perform the tasks specified in each step
void CLADASetupDlg::DoSomething()
{
	if (Type==CheckOut)
	{
		if (checknumber==TURN_ON_POWER) // Starts Checkout and records the time
		{
			CTime Start=CTime::GetCurrentTime();
			CString temp;
			temp=Start.Format("%d.%m.%y");
			print->data[0][1]=temp;
			temp=Start.Format(" %H:%M");
			print->data[1][1]=temp;
			if (m_IsAutomatic)
			{
				GetDlgItem(IDC_CHECK2)->EnableWindow();
				((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
				GetDlgItem(IDC_CHECK3)->EnableWindow();
				((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(TRUE);
				checknumber=INITIALIZE_CR10X;
			}			
		}
		if (checknumber==INITIALIZE_CR10X) // Connects to the CR10
		{	
			
			pDoc->m_ControlMode = ManualControlMode;
			if (pDoc->ConnectionStatus==Connected || pDoc->Connect(FALSE, Regular, FALSE))
			{
				// don't start data retrieval mode, make sure regular program is running on CR10, don't do initialization
				BOOL Success;
				
				Success = pDoc->commObject->UpdateCR10Time();
				if (!Success)
				{
					GetDlgItem(IDC_CHECK3)->SetFocus();
					return;
				}
							
				if (!m_IsAutomatic && !Success)
					NotificationBox(IDS_M_TIME_NOT_UPDATED,IDS_PROGRAM_NAME,MB_OK,FALSE,1000);
				int loc[2]={MAVOLNEED,MAXPMPVOL};
				pDoc->GetInputLocations(loc,2,Old,8);
			
				pDoc->commObject->SetInputLocation(MAVOLNEED,10000, 109, TRUE);
				pDoc->commObject->SetInputLocation(MAXPMPVOL,10000, 110, TRUE);
				
				for (int wTry = 0; wTry < 5 && !pDoc->commObject->SetFlag(7,1); wTry++);
				if (wTry == 5)
					MessageBox("Failed to set flag 7 high to disable pump security.");

				//pDoc->commObject->SetInputLocation(IL_WATER_PUMPED,0, 113); // set water pumped to zero
			
				print->data[3][1]=ValueToString(Old[1]);
				if (m_IsAutomatic)
				{					
					((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(TRUE);		
					GetDlgItem(IDC_CHECK4)->EnableWindow();
					checknumber=VIEW_VOLTAGES;
				}
			}
			else
			{
				GetDlgItem(IDC_CHECK3)->SetFocus();
				((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(FALSE);
				GetDlgItem(IDC_CHECK4)->EnableWindow(FALSE);
			}

		}
	

		if (checknumber==VIEW_VOLTAGES) // Checks the voltages on the CR10
		{
			int listSize = 8;
			int * InputList = new int[listSize];
			for (int x=0;x<8;x++)
				InputList[x] = x+VOLTAGE_1;
			double * returnData = new double[listSize];
			CSystemDiagDlg dlg(pDoc, -1, FALSE, InputList, listSize, returnData,m_IsAutomatic,FALSE);
			dlg.DoModal();
			SetStrings();
			ResetStrings();
		
//			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AB0+10*m_stepnumber+checknumber));
			m_VStep=Strings.get(IDS_S1)+CString(m_step[m_stepnumber].m_step/10+'0')+CString(m_step[m_stepnumber].m_step%10+'0');
			m_VTitle=m_step[m_stepnumber].m_title;
			m_VText=m_step[m_stepnumber].m_Text;
			UpdateData(FALSE);
			delete [] InputList;
			delete [] returnData;
			if (m_IsAutomatic)
			{
				((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(TRUE);		
				GetDlgItem(IDC_CHECK5)->EnableWindow();
				checknumber=VIEW_MEASUREMENTS;
			}
		}
		if (checknumber==VIEW_MEASUREMENTS) // Verifies certain values from the CR10 to the user
		{			
			Verify dlga(pDoc,m_IsAutomatic,print);
			dlga.DoModal();
			SetStrings();
			ResetStrings();
		//	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AB0+10*m_stepnumber+checknumber));
			m_VStep=Strings.get(IDS_S1)+CString(m_step[m_stepnumber].m_step/10+'0')+CString(m_step[m_stepnumber].m_step%10+'0');
			m_VTitle=m_step[m_stepnumber].m_title;
			m_VText=m_step[m_stepnumber].m_Text;
			UpdateData(FALSE);
			if (m_IsAutomatic)
			{
				((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(TRUE);	
				GetDlgItem(IDC_CHECK6)->EnableWindow();
				checknumber=MAIN_TEST;
			}
		}
		
		
		if (checknumber==MAIN_TEST) // Runs the Diagnostic Tests and compares value with the user
		{			
			LadaTest dlgc(pDoc, print,m_IsAutomatic,this);
			dlgc.DoModal();
			SetStrings();
			ResetStrings();
	//		GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AB0+10*m_stepnumber+checknumber));
			m_VStep=Strings.get(IDS_S1)+CString(m_step[m_stepnumber].m_step/10+'0')+CString(m_step[m_stepnumber].m_step%10+'0');
			m_VTitle=m_step[m_stepnumber].m_title;
			m_VText=m_step[m_stepnumber].m_Text;
			UpdateData(FALSE);		
			pDoc->commObject->SetFlag(2,FALSE);
			pDoc->commObject->SetFlag(7,FALSE);
			pDoc->commObject->SetInputLocation(MAVOLNEED,Old[0], 111);
			pDoc->commObject->SetInputLocation(MAXPMPVOL,Old[1], 112);
			if (m_IsAutomatic)
			{
				((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(TRUE);		
				GetDlgItem(IDC_CHECK7)->EnableWindow();
				checknumber=DISPLAY;
			}

		}
		if (checknumber==DISPLAY)
		{
			Display ddlg(print);
			ddlg.DoModal();
			SetStrings();
			ResetStrings();
		//	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AB0+10*m_stepnumber+checknumber));
			m_VStep=Strings.get(IDS_S1)+CString(m_step[m_stepnumber].m_step/10+'0')+CString(m_step[m_stepnumber].m_step%10+'0');
			m_VTitle=m_step[m_stepnumber].m_title;
			m_VText=m_step[m_stepnumber].m_Text;
			UpdateData(FALSE);
			
			print->output(fout);
			fout.close();
			CTime now = CTime::GetCurrentTime();
			CString tempf;
			tempf=now.Format("%B %d, %y %H;%M");
			tempf="data\\Check Out "+tempf+".txt";
			CopyFile("hello.txt",tempf.GetBuffer(0),FALSE);
			//CFile::Rename("hello.txt",tempf.GetBuffer(0));
		
			if (m_IsAutomatic)
			{	
				GetDlgItem(IDC_CHECK8)->EnableWindow();
				GetDlgItem(IDC_CHECK8)->SetFocus();
			}

			GetDlgItem(IDC_TEST_CAMERA)->ShowWindow(SW_SHOW);

		}
		if (checknumber==TAKE_PICTURE)
		{	
			if (cameraDlg)
			{
				cameraDlg->ShowWindow(SW_SHOW);
				cameraDlg->AutoPicture(0);
			}
		}
	}
	else if (Type == Tensiometer)
	{
		if (checknumber == 7 ||
			checknumber == 9 ||
			checknumber == 11 ||
			checknumber == 13)
		{
			if (!pDoc->commObject)
			{
				MessageBox("No connection with CR10X.  Please restart wetup.","Error",MB_ICONWARNING);
			}
			else
			{
				pDoc->commObject->SetFlag(TENSIOMETER_CONTROL_FLAG,1);
				BOOL Cancelled;
				ProgressDialog PumpProgress(&Cancelled, "Pumping water...", "Tensiometer Priming");
				PumpProgress.Create(PROGRESS_DIALOG);
				
				double returnData[2];
				int volPumped = 0;
				do
				{
					int locations[] = {MA_PUMP_IN, PUMP_VOL};
					
					pDoc->GetInputLocations(locations,2,returnData,31);
					PumpProgress.SetInfo(100*returnData[0]/ returnData[1]);
					MSG Msg;
		
					while (PeekMessage( &Msg,         // message information
						NULL,           // handle to window
						0,//WM_MOUSEFIRST,  // first message  
						0,//WM_MOUSELAST );  // last message
						PM_REMOVE /*| PM_NOYIELD*/)) //wRemoveMsg
						DispatchMessage( &Msg );  // message information);
					if (!Cancelled && returnData[0]+0.1 < returnData[1])
						Sleep(1000);
					//pDoc->commObject->SetInputLocation(MA_PUMP_IN,volPumped+=4,111);
					
				} while (returnData[0]+0.1 < returnData[1] && !Cancelled);
				PumpProgress.Close();
				if (Cancelled)
					pDoc->commObject->SetFlag(8,0);
			}
		}

	}
	
}

// This sets the text to the current language
void CLADASetupDlg::SetStrings()
{
//	SetWindowText(Strings.get(IDS_S0));
	GetDlgItem(ID_BACK)->SetWindowText(Strings.get(IDS_S2));
//	GetDlgItem(ID_NEXT)->SetWindowText(Strings.get(IDS_S3));
	GetDlgItem(ID_HELP)->SetWindowText(Strings.get(IDS_S5));
}


BOOL CLADASetupDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
			Strings.ToggleLanguage();
			SetStrings();
			ResetStrings();
			//GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_V0+10*m_stepnumber+checknumber));
			m_VStep=Strings.get(IDS_S1)+CString(m_step[m_stepnumber].m_step/10+'0')+CString(m_step[m_stepnumber].m_step%10+'0');
			m_VTitle=m_step[m_stepnumber].m_title;
			m_VText=m_step[m_stepnumber].m_Text;
			UpdateData(FALSE);
			return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam==13)
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CLADASetupDlg::OnCheck(UINT nID)
{
	checknumber=nID-IDC_CHECK1;
	UpdateData(TRUE);
	CheckTrue=((CButton*)GetDlgItem(nID))->GetCheck();
	CheckCheck(m_stepnumber);
	if (CheckTrue)
	{	
		if (m_step[m_stepnumber].m_checks>(checknumber+1))
		{
			((CButton*)GetDlgItem(nID+1))->EnableWindow();
			GetDlgItem(nID+1)->SetFocus();
		}
		DoSomething();
	}
	
}

void CLADASetupDlg::ResetStrings()
{
	if (!(m_step[m_stepnumber].m_checks-checknumber-1))
	{
		m_CNext.EnableWindow(TRUE);
		if ((m_stepnumber+1)==m_numsteps)
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_ALL_STEPS_COMPLETE));
		else
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_STEPS_COMPLETE));
	}
	else
	{
		m_CNext.EnableWindow(FALSE);
		if (Type==Setup)
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_V00+10*m_stepnumber+checknumber+CheckTrue));
		else if (Type==CheckOut)
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_AB0+9*m_stepnumber+checknumber+CheckTrue));
		else if (Type==Tensiometer)
			GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_TENS_STEP_EXPLANATION_1+9*m_stepnumber+checknumber+CheckTrue));
		
	}
	if (m_stepnumber==m_numsteps-1)
		m_CNext.SetWindowText(Strings.get(IDS_S4));
	else
		m_CNext.SetWindowText(Strings.get(IDS_S3));
	if (Type==Setup)
	{
		SetWindowText(Strings.get(IDS_A1));
			for (int x=0;x<m_numsteps;x++)
			{
				CString temp[9];
				for (int y=0;y<9;y++)
				{
					temp[y]=Strings.get(IDS_S01+10*x+y);
					if (x==m_stepnumber)
						GetDlgItem(IDC_CHECK1+y)->SetWindowText(temp[y]);
				}
					m_step[x]=Stepinfo(x+1,Strings.get(IDS_S00+10*x),m_StepsPerPage[x],temp,Strings.get(IDS_S00+10*x));
			}
	}
	else if (Type==CheckOut)
	{
			SetWindowText(Strings.get(IDS_A2));
			for (int x=0;x<m_numsteps;x++)
			{
				CString temp[9];
				for (int y=0;y<9;y++)
				{
					temp[y]=Strings.get(IDS_CO11+10*x+y);
					if (x==m_stepnumber)
						GetDlgItem(IDC_CHECK1+y)->SetWindowText(temp[y]);
				}
				m_step[x]=Stepinfo(x+1,Strings.get(IDS_CO10+10*x),m_StepsPerPage[x],temp,Strings.get(IDS_CO10+10*x));
			}
	}
	else if (Type==Tensiometer)
	{
			SetWindowText(Strings.get(IDS_TENSIOMETER));
			for (int x=0;x<m_numsteps;x++)
			{
				CString temp[9];
				for (int y=0;y<9;y++)
				{
					temp[y]=Strings.get(IDS_TENSIOMETER_STEP_1+10*x+y);
					if (x==m_stepnumber)
						GetDlgItem(IDC_CHECK1+y)->SetWindowText(temp[y]);
				}
				m_step[x]=Stepinfo(x+1,Strings.get(IDS_TENSIOMETER_STEP_0+10*x),m_StepsPerPage[x],temp,Strings.get(IDS_TENSIOMETER_STEP_0+10*x));
			}
	}


}
