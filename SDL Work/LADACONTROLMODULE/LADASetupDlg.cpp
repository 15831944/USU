// LADASetupDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "LADASetup.h"
#include "LADASetupDlg.h"
#include "Step.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CLADASetupDlg dialog

CLADASetupDlg::CLADASetupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLADASetupDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLADASetupDlg)
	m_VCheck1 = FALSE;
	m_VCheck2 = FALSE;
	m_VCheck3 = FALSE;
	m_VCheck4 = FALSE;
	m_VCheck5 = FALSE;
	m_VCheck6 = FALSE;
	m_VCheck7 = FALSE;
	m_VCheck8 = FALSE;
	m_VCheck9 = FALSE;
	m_VStep = _T("");
	m_VTitle = _T("");
	m_VText = _T("");
	m_VPicture = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLADASetupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLADASetupDlg)
	DDX_Control(pDX, IDC_PICTURE, m_CPicture);
	DDX_Control(pDX, IDC_TEXT, m_CText);
	DDX_Control(pDX, IDC_CHECK9, m_CCheck9);
	DDX_Control(pDX, IDC_CHECK8, m_CCheck8);
	DDX_Control(pDX, IDC_CHECK7, m_CCheck7);
	DDX_Control(pDX, IDC_CHECK6, m_CCheck6);
	DDX_Control(pDX, IDC_CHECK5, m_CCheck5);
	DDX_Control(pDX, IDC_CHECK4, m_CCheck4);
	DDX_Control(pDX, IDC_CHECK3, m_CCheck3);
	DDX_Control(pDX, IDC_CHECK2, m_CCheck2);
	DDX_Control(pDX, IDC_CHECK1, m_CCheck1);
	DDX_Control(pDX, ID_NEXT, m_CNext);
	DDX_Control(pDX, ID_BACK, m_CBack);
	DDX_Check(pDX, IDC_CHECK1, m_VCheck1);
	DDX_Check(pDX, IDC_CHECK2, m_VCheck2);
	DDX_Check(pDX, IDC_CHECK3, m_VCheck3);
	DDX_Check(pDX, IDC_CHECK4, m_VCheck4);
	DDX_Check(pDX, IDC_CHECK5, m_VCheck5);
	DDX_Check(pDX, IDC_CHECK6, m_VCheck6);
	DDX_Check(pDX, IDC_CHECK7, m_VCheck7);
	DDX_Check(pDX, IDC_CHECK8, m_VCheck8);
	DDX_Check(pDX, IDC_CHECK9, m_VCheck9);
	DDX_Text(pDX, IDC_STEP, m_VStep);
	DDV_MaxChars(pDX, m_VStep, 9);
	DDX_Text(pDX, IDC_TITLE, m_VTitle);
	DDV_MaxChars(pDX, m_VTitle, 60);
	DDX_Text(pDX, IDC_TEXT, m_VText);
	DDX_Text(pDX, IDC_PICTURE, m_VPicture);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLADASetupDlg, CDialog)
	//{{AFX_MSG_MAP(CLADASetupDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_NEXT, OnNext)
	ON_BN_CLICKED(ID_BACK, OnBack)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADASetupDlg message handlers

BOOL CLADASetupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);
	CString temp[9]={"Attach Pump to Root Module","Attach electronics box to Root Module","Connect pump box cable to electronics box connector","Attach growth chamber to root module","Attach and connect sensor tree to light box","Attach light box to growth chamber","","",""};
	m_step[0]=Stepinfo(1,"Attach Parts",6,temp,"Attach Pump to Root Module");
	CString temp1[9]={"Connect ribbon cable from light box connector to electronics box connector","Connect power cable from libht box connector to control module connector","Connect communications cable from light box to control module connector","","","","",""};
	m_step[1]=Stepinfo(2,"Connect Parts to Light Box",3,temp1,"Connect Parts to Light Box");
	CString temp2[9]={"Switch on +12n,+12c,+5m supplies with one switch","Switch on fans on manual","Verify the fans","Switch the fans to computer controls","","","",""};
	m_step[2]=Stepinfo(3,"Switch on Fans",4,temp2,"Switch on Fans");
	CString temp3[9]={"Switch water pump on manual","Verify water pump","Switch water pump to computer control","","","","",""};
	m_step[3]=Stepinfo(4,"Switch on water Pump",3,temp3,"Switch on Water pump");
	CString temp4[9]={"Switch air pump on manual","Verify air pump","Switch air pump to computer control","","","","",""};
	m_step[4]=Stepinfo(5,"Switch on air pump",3,temp4,"Switch on Air Pump");
	CString temp5[9]={"Switch lights on manual","Verify lights","Switch lights to computer control","","","","","",""};
	m_step[5]=Stepinfo(6,"Switch on Lights",3,temp5,"Switch on Lights");
	CString temp6[9]={"Attach electronics box to Root Module","","","","","","",""};
	checknumber=0;
	/*m_step[6]=Stepinfo(7,"Attach electronics box to Root Module",1,temp6,"");
	CString temp7[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[7]=Stepinfo(8,"Attach electronics box to Root Module",1,temp7,"");
	CString temp8[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[8]=Stepinfo(9,"Attach electronics box to Root Module",1,temp8,"");
	CString temp9[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[9]=Stepinfo(10,"Attach electronics box to Root Module",1,temp9,"");
	CString temp10[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[10]=Stepinfo(11,"Attach electronics box to Root Module",1,temp10,"");
	CString temp11[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[11]=Stepinfo(12,"Attach electronics box to Root Module",1,temp11,"");
	CString temp12[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[12]=Stepinfo(13,"Attach electronics box to Root Module",1,temp12,"");
	CString temp13[9]={"Attach electronics box to Root Module","","","","","","",""};
	m_step[13]=Stepinfo(14,"Attach electronics box to Root Module",1,temp13,"");*/
	m_stepnumber=0;	
	Reset(0);
	/*
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	*/
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CLADASetupDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

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

void CLADASetupDlg::OnNext() 
{
	m_stepnumber++;
	if (m_stepnumber==m_numsteps)
		OnOK();
	else
		Reset(m_stepnumber);
}

void CLADASetupDlg::OnBack() 
{
	m_stepnumber--;
	if (m_stepnumber<0)
		m_stepnumber=0;
	Reset(m_stepnumber);
}

void CLADASetupDlg::Reset(int temp)
{
	m_VCheck1=FALSE;
	m_VCheck2=FALSE;
	m_VCheck3=FALSE;
	m_VCheck4=FALSE;
	m_VCheck5=FALSE;
	m_VCheck6=FALSE;
	m_VCheck7=FALSE;
	m_VCheck8=FALSE;
	m_VCheck9=FALSE;

	if (temp==0)
		m_CBack.EnableWindow(FALSE);
	else
		m_CBack.EnableWindow(TRUE);
	if (temp==m_numsteps-1)
		m_CNext.SetWindowText("Finish");
	else
		m_CNext.SetWindowText("Next->");
	m_CCheck2.ShowWindow(SW_SHOW);
	m_CCheck2.EnableWindow(FALSE);
	m_CCheck3.ShowWindow(SW_SHOW);
	m_CCheck3.EnableWindow(FALSE);
	m_CCheck4.ShowWindow(SW_SHOW);
	m_CCheck4.EnableWindow(FALSE);
	m_CCheck5.ShowWindow(SW_SHOW);
	m_CCheck5.EnableWindow(FALSE);
	m_CCheck6.ShowWindow(SW_SHOW);
	m_CCheck6.EnableWindow(FALSE);
	m_CCheck7.ShowWindow(SW_SHOW);
	m_CCheck7.EnableWindow(FALSE);
	m_CCheck8.ShowWindow(SW_SHOW);
	m_CCheck8.EnableWindow(FALSE);
	m_CCheck9.ShowWindow(SW_SHOW);
	m_CCheck9.EnableWindow(FALSE);
	
	m_VStep="Step "+CString(m_step[temp].m_step/10+'0')+CString(m_step[temp].m_step%10+'0');
	m_VTitle=m_step[temp].m_title;
	int x=m_step[temp].m_checks;
	if(x<9)
	{
		m_CCheck9.ShowWindow(SW_HIDE);
		m_CCheck9.EnableWindow(FALSE);

	}
	if(x<8)
	{
		m_CCheck8.ShowWindow(SW_HIDE);
		m_CCheck8.EnableWindow(FALSE);
	}
	if(x<7)
	{
		m_CCheck7.ShowWindow(SW_HIDE);
		m_CCheck7.EnableWindow(FALSE);
	}
	if(x<6)
	{
		m_CCheck6.ShowWindow(SW_HIDE);
		m_CCheck6.EnableWindow(FALSE);
	}
	if(x<5)
	{
		m_CCheck5.ShowWindow(SW_HIDE);
		m_CCheck5.EnableWindow(FALSE);
	}
	if(x<4)
	{
		m_CCheck4.ShowWindow(SW_HIDE);
		m_CCheck4.EnableWindow(FALSE);
	}
	if(x<3)
	{
		m_CCheck3.ShowWindow(SW_HIDE);
		m_CCheck3.EnableWindow(FALSE);
	}
	if(x<2)
	{
		m_CCheck2.ShowWindow(SW_HIDE);
		m_CCheck2.EnableWindow(FALSE);
	}
	
	m_CCheck9.SetWindowText(m_step[temp].m_Steps[8]);
	m_CCheck8.SetWindowText(m_step[temp].m_Steps[7]);
	m_CCheck7.SetWindowText(m_step[temp].m_Steps[6]);
	m_CCheck6.SetWindowText(m_step[temp].m_Steps[5]);
	m_CCheck5.SetWindowText(m_step[temp].m_Steps[4]);
	m_CCheck4.SetWindowText(m_step[temp].m_Steps[3]);
	m_CCheck3.SetWindowText(m_step[temp].m_Steps[2]);
	m_CCheck2.SetWindowText(m_step[temp].m_Steps[1]);
	m_CCheck1.SetWindowText(m_step[temp].m_Steps[0]);
	m_VText=m_step[temp].m_Text;
	
	UpdateData(FALSE);
	CheckCheck(m_stepnumber);
}

void CLADASetupDlg::OnCheck1() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>1 && m_VCheck1==TRUE)
		m_CCheck2.EnableWindow();
	checknumber = 0 + m_VCheck1;
	CheckCheck(m_stepnumber);

	
}

void CLADASetupDlg::OnCheck2() 
{
		UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>2 && m_VCheck2==TRUE)
		m_CCheck3.EnableWindow();
	checknumber = 1 + m_VCheck2;
	CheckCheck(m_stepnumber);
}

void CLADASetupDlg::OnCheck3() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>3 && m_VCheck3==TRUE)
		m_CCheck4.EnableWindow();
	checknumber = 2 + m_VCheck3;
	CheckCheck(m_stepnumber);
	
}

void CLADASetupDlg::OnCheck4() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>4 && m_VCheck4==TRUE)
		m_CCheck5.EnableWindow();
	checknumber = 3 + m_VCheck4;
	CheckCheck(m_stepnumber);
	
}

void CLADASetupDlg::OnCheck5() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>5 && m_VCheck5==TRUE)
		m_CCheck6.EnableWindow();
	checknumber = 4 + m_VCheck5;
	CheckCheck(m_stepnumber);
	
}

void CLADASetupDlg::OnCheck6() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>6 && m_VCheck6==TRUE)
		m_CCheck7.EnableWindow();
	checknumber = 5 + m_VCheck6;
	CheckCheck(m_stepnumber);
	
}

void CLADASetupDlg::OnCheck7() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>7 && m_VCheck7==TRUE)
		m_CCheck8.EnableWindow();
	checknumber = 6 + m_VCheck7;
	CheckCheck(m_stepnumber);	
}

void CLADASetupDlg::OnCheck8() 
{
	UpdateData(TRUE);
	if (m_step[m_stepnumber].m_checks>8 && m_VCheck8==TRUE)
		m_CCheck9.EnableWindow();
	checknumber = 7 + m_VCheck8;
	CheckCheck(m_stepnumber);	
}

void CLADASetupDlg::OnCheck9() 
{
	UpdateData(TRUE);
	checknumber = 8 + m_VCheck9;
	CheckCheck(m_stepnumber);	
	
}

void CLADASetupDlg::CheckCheck(int temp)
{

	UpdateData(TRUE);
	int x=m_step[temp].m_checks-(m_VCheck1+m_VCheck2+m_VCheck3+m_VCheck4+m_VCheck5+m_VCheck6+m_VCheck7+m_VCheck8+m_VCheck9);
	if (x==0)
		m_CNext.EnableWindow(TRUE);
	else
		m_CNext.EnableWindow(FALSE);
	
	m_Bitmap.DeleteObject();
	m_Bitmap.LoadBitmap(IDB_BITMAP1+9*temp+checknumber);
	m_CPicture.SetBitmap((HBITMAP)m_Bitmap);
}
