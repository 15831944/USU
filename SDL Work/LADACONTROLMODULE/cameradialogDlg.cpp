// cameradialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "cameradialogDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCameradialogDlg dialog

CCameradialogDlg::CCameradialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameradialogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCameradialogDlg)
//	m_Date = 0;
	Path=0;
	m_FreqNumber = 0;
	m_FreqString = _T("");
	firstpicture=false;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	CreateCaptureWindow = NULL;
	
	hLibrary = LoadLibrary("AVICAP32.DLL");

	if (hLibrary != NULL)    
	{
		CreateCaptureWindow = (lpFunc1) GetProcAddress(hLibrary, "capCreateCaptureWindowA");
	    if (CreateCaptureWindow == NULL) 
		{             
			MessageBox( "System file not present (AVICAP32.DLL).", 
			"Initialization Error", 
			MB_ICONEXCLAMATION );
		}
	}
	
}

CCameradialogDlg::~CCameradialogDlg()
{
	if (hLibrary)
		FreeLibrary(hLibrary);
}

void CCameradialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameradialogDlg)
	DDX_Control(pDX, IDC_TVALUE, m_FreqNumCon);
	DDX_Control(pDX, IDC_SAVE, m_Save);
	DDX_Control(pDX, IDC_CLEAR, m_Clear);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_RESOLUTION,m_Resolution);
	DDX_Control(pDX, IDC_FREQUENCY, m_Frequency);
	DDX_Control(pDX, IDC_FILEBOX, m_FileBox);
//	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Date);
	DDX_Text(pDX, IDC_TVALUE, m_FreqNumber);
	DDV_MinMaxUInt(pDX, m_FreqNumber, 0, 100);
	DDX_CBString(pDX, IDC_FREQUENCY, m_FreqString);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCameradialogDlg, CDialog)
	//{{AFX_MSG_MAP(CCameradialogDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_FILEBOX, OnDblclkFilebox)
	ON_BN_CLICKED(IDC_CAMERA1, OnCamera1)
	ON_BN_CLICKED(IDC_CAMERA2, OnCamera2)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_EN_CHANGE(IDC_TVALUE, OnChangeTvalue)
	ON_CBN_SELCHANGE(IDC_FREQUENCY, OnSelchangeFrequency)
	ON_CBN_EDITUPDATE(IDC_FREQUENCY, OnEditupdateFrequency)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameradialogDlg message handlers

BOOL CCameradialogDlg::OnInitDialog()
{

	CDialog::OnInitDialog();


	HWND hParentWnd = *this;
	char message[] = "No driver was found ( )";
	CRect Rect;
	Black=GetDlgItem(IDC_PICTURE);
	Black->GetClientRect(Rect);
	VCWin1 = CreateCaptureWindow ( "My Own Capture Window", 
		WS_CHILD | WS_VISIBLE , 0, 0, Rect.right, Rect.bottom, Black->GetSafeHwnd(), nID);
	if (!capDriverConnect( VCWin1, 0 ))
	{
		message[21] =  '0';
		MessageBox( message, 
		"Initialization Error", 
		MB_ICONEXCLAMATION );
	}	
	
//	capDlgVideoFormat(  VCWin1  );

//	MessageBox("Hello");
	LoadFile(m_File);
	
	m_FileBox.InsertColumn(0,"Date",LVCFMT_LEFT,75,1);
	m_FileBox.InsertColumn(1,"Time",LVCFMT_LEFT,75,1);
	m_FileBox.InsertColumn(2,"Camera",LVCFMT_LEFT,50,1);
	m_FileBox.InsertColumn(3,"Size",LVCFMT_LEFT,75,1);
	for (int x=0;x<nRecords;x++)
	{
		m_FileBox.InsertItem(x,m_File[x].m_Date,1);
		m_FileBox.SetItemText(x,1,m_File[x].m_Time);
		m_FileBox.SetItemText(x,2,m_File[x].m_Camera);
		m_FileBox.SetItemText(x,3,m_File[x].m_Size);
	}
	m_Frequency.AddString("Weeks");
	m_Frequency.AddString("Days");
	m_Frequency.AddString("Hours");
	m_Frequency.AddString("Minutes");
	m_Spin1.SetBuddy(&m_FreqNumCon);
	m_Resolution.AddString("640 X 480");

	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCameradialogDlg::OnPaint() 
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
HCURSOR CCameradialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCameradialogDlg::OnDblclkFilebox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int curSel= (int) m_FileBox.GetFirstSelectedItemPosition();	
	*pResult = 0;
	LoadPicture(curSel);
	

}

void CCameradialogDlg::OnCamera1() 
{
	Camera=1;
	TakePicture();
}

void CCameradialogDlg::OnCamera2() 
{
	Camera=2;
	TakePicture();	
}



void CCameradialogDlg::OnSave() 
{
	CFileData temp;
	temp.m_RealTime=CTime::GetCurrentTime();
	temp.m_Date=temp.m_RealTime.Format("%B %d, %y");
	temp.m_Time=temp.m_RealTime.Format("%H:%M");
	CString TTime=temp.m_RealTime.Format("%H;%M");
	if(Camera==1)
		temp.m_Camera="1";
	else
		temp.m_Camera="2";
	temp.m_Size="30 kb";
	m_File.Insert(temp,0);
	nRecords++;
	Save();
	CString FileN=(temp.m_Date+" " + TTime+temp.m_Camera+".dib");
	temp.FileName=FileN.GetBuffer(1);
	FileN.ReleaseBuffer();
	int work=capFileSaveDIB(VCWin1, temp.FileName); 
	m_FileBox.InsertItem(0,temp.m_Date,1);
	m_FileBox.SetItemText(0,1,temp.m_Time);
	m_FileBox.SetItemText(0,2,temp.m_Camera);
	m_FileBox.SetItemText(0,3,temp.m_Size);
	
	
}


void CCameradialogDlg::OnClear() 
{
	Clear();
	MessageBox("Picture Cleared","CLEARED" );
	
}

void CCameradialogDlg::LoadFile(Array<CFileData> &m_File)
{
	nRecords=0;
	HANDLE Temp=CreateFile("FileData.cam",STANDARD_RIGHTS_ALL,FILE_SHARE_READ,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);
	if (Temp!=INVALID_HANDLE_VALUE)
		CloseHandle(Temp);
	CFile fileOut( "FileData.cam", CFile::modeRead);
	if (fileOut.GetLength())
	{
	CArchive ar( &fileOut, CArchive::load );
	ar >> nRecords;
	m_File(nRecords);
	for (int x=0;x<nRecords;x++)
		ar >> m_File[x];
		ar.Close();
	}
	fileOut.Close();
}


void CCameradialogDlg::LoadPicture(int a)
{
	if (a==0)
		MessageBox("No Picture Selected","ERROR",MB_ICONEXCLAMATION );
	else
		MessageBox( m_File[a-1].m_Date+" "+m_File[a-1].m_Time+ " " + m_File[a-1].m_Camera,
			"Picture Loaded");


//	capFileOpen()
}

void CCameradialogDlg::TakePicture()
{

	m_Save.EnableWindow(true);
	m_Clear.EnableWindow(true);
	
	
//		}
//	BOOL capCaptureSingleFrameOpen(VCWin1);
 
		if (!capGrabFrame( VCWin1 ))
		{
			MessageBox( "No camera present.", 
			"Initialization Error", 
			 MB_ICONEXCLAMATION );
		}

//	}

}

void CCameradialogDlg::Save()
{
	CFile fileOut( "FileData.cam", CFile::modeWrite);
	CArchive ar( &fileOut, CArchive::store);
	ar << nRecords;
	for (int x=0;x<nRecords;x++)
		ar << m_File[x];
	ar.Close();
	fileOut.Close();
	LoadFile(m_File);
}

void CCameradialogDlg::Clear()
{
	CClientDC dc(Black);
	CRect rect;
	Black->GetClientRect(&rect);
	dc.FillSolidRect( &rect, RGB(0,0,0) );

}


void CCameradialogDlg::TakePictureNow()
{
	//HWND hParentWnd = *this;
	//char message[] = "No driver was found ( )";
	//CRect Rect;
	//Black=GetDlgItem(IDC_PICTURE);
	//Black->GetClientRect(Rect);
	int nID = 0;
	VCWin1 = CreateCaptureWindow ( NULL, 
		NULL, 0, 0, 0, 0, NULL, nID);
	if (!capDriverConnect( VCWin1, 0 ))
	{
		//message[21] =  '0';
		MessageBox( "Failed to connect capture driver", 
		"Initialization Error", 
		MB_ICONEXCLAMATION );
	}
	OnCamera1();
	OnSave();
	OnCamera2();
	OnSave();
	capDriverDisconnect(VCWin1);
}

void CCameradialogDlg::OnChangeTvalue() 
{
	ChangeInterval();
}


void CCameradialogDlg::ChangeInterval()
{
	
	UpdateData(TRUE);
	int curSel = m_Frequency.GetCurSel();
	if (curSel==0)
	{
		CTimeSpan temp(7*m_FreqNumber,0,0,0);
		m_Interval=temp;
	}
	else if (curSel==1)
	{
		CTimeSpan temp(m_FreqNumber,0,0,0);
		m_Interval=temp;
	}
	else if (curSel==2)
	{
		CTimeSpan temp(0,m_FreqNumber,0,0);
		m_Interval=temp;
	}
	else
	{
		CTimeSpan temp(0,0,m_FreqNumber,0);
		m_Interval=temp;
	}
	int d,h,m,x;
	d=m_Interval.GetDays();
	h=m_Interval.GetHours();
	m=m_Interval.GetMinutes();
	x=m_Interval.GetTotalMinutes();


}

void CCameradialogDlg::OnSelchangeFrequency() 
{
	ChangeInterval();	

}

void CCameradialogDlg::OnEditupdateFrequency() 
{
	ChangeInterval();
}

BOOL CCameradialogDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	capDriverDisconnect(VCWin1);
	return CDialog::DestroyWindow();
}
