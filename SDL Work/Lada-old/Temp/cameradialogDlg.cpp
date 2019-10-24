// cameradialogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LADA Control Module.h"
#include "cameradialogDlg.h"
#include <fstream.h>
#include "LString.h"
#include "Ladastrings.h"
#include "twain.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#undef MessageBox
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);
#define MessageBox MyMessageBox


extern LString Strings;												// The strings for both languages
extern CFont RussianArial;										// The font used
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);//Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);				// Sets an item to a font

/////////////////////////////////////////////////////////////////////////////
// CCameradialogDlg dialog
// Constructor
CCameradialogDlg::CCameradialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCameradialogDlg::IDD, pParent)
{
	m_FreqNumber = 0;
	m_FreqString = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	LPTSTR szSMDir="c:\\winnt\\";
	GetWindowsDirectory(szSMDir, sizeof(szSMDir));
	if (szSMDir [(lstrlen (szSMDir) -1)] != '\\')
	{
		lstrcat (szSMDir, "\\");
	}
	if ((OpenFile(szSMDir,&of, OF_EXIST) !=-1))
	{
		if (hDSMDLL=LoadLibrary("TWAIN_32.DLL"))
		{
			//if (hDSMDLL >= (HANDLE)VALID_HANDLE)
		//	{
				if (lpDSM_Entry = (DSMENTRYPROC)GetProcAddress(hDSMDLL,MAKEINTRESOURCE(1)))
					if (lpDSM_Entry)
						FreeLibrary(hDSMDLL);
			
		//	}
		}
	}	
}

// Destructor
CCameradialogDlg::~CCameradialogDlg()
{
	if (hDSMDLL)
		FreeLibrary(hDSMDLL);
}

// Data Exchange
void CCameradialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCameradialogDlg)
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_REPICTURE, m_rpicture);
	DDX_Control(pDX, IDC_TVALUE, m_FreqNumCon);
	DDX_Control(pDX, IDC_SAVE, m_Save);
	DDX_Control(pDX, IDC_CLEAR, m_Clear);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_RESOLUTION,m_Resolution);
	DDX_Control(pDX, IDC_FREQUENCY, m_Frequency);
	DDX_Control(pDX, IDC_FILEBOX, m_FileBox);
	DDX_Text(pDX, IDC_TVALUE, m_FreqNumber);
	DDV_MinMaxUInt(pDX, m_FreqNumber, 0, 100);
	DDX_CBString(pDX, IDC_FREQUENCY, m_FreqString);
	//}}AFX_DATA_MAP
}

// Message Maps
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
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCameradialogDlg message handlers
// Initialization
// Opens up the Source Manager
BOOL CCameradialogDlg::OnInitDialog()
{
	
	pDest=NULL;
	pOrigin=new TW_IDENTITY;
	pOrigin->Id=0;
	pOrigin->Version.MajorNum=3;
	pOrigin->Version.MinorNum=5;
	pOrigin->Version.Language=TWLG_ENGLISH_USA;
	pOrigin->Version.Country=TWCY_USA;
	lstrcpy(pOrigin->Version.Info,"Version 1.0");
	pOrigin->ProtocolMajor=TWON_PROTOCOLMAJOR;
	pOrigin->ProtocolMinor=TWON_PROTOCOLMINOR;
	lstrcpy(pOrigin->Manufacturer,"John Mulholland and Mark Salisbury");
	lstrcpy(pOrigin->ProductFamily,"Part of the LADA Family");
	lstrcpy(pOrigin->ProductName,"LADA");
	pDSM_Entry=NULL;

	rc=(*pDSM_Entry) (pOrigin,NULL,DG_CONTROL,DAT_PARENT,MSG_OPENDSM,(TW_MEMREF) this);
	
	CDialog::OnInitDialog();
	ppal=new CPalette;
	Bitmap=NULL;
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
	LoadFile(m_File);
	SetFont(&RussianArial);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_CAMERA1,this);
	SetItemFont(IDC_CAMERA2,this);
	SetItemFont(IDC_CLEAR,this);
	SetItemFont(IDC_SAVE,this);
	m_FileBox.SetFont(&RussianArial);
	m_FileBox.InsertColumn(0,Strings.get(IDS_F7),LVCFMT_LEFT,75,1);
	m_FileBox.InsertColumn(1,Strings.get(IDS_F8),LVCFMT_LEFT,75,1);
	m_FileBox.InsertColumn(2,Strings.get(IDS_F9),LVCFMT_LEFT,50,1);
	m_FileBox.InsertColumn(3,Strings.get(IDS_F10),LVCFMT_LEFT,75,1);
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	SetStrings();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

//Draws everything
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

//When a picture is doubleclicked on it displays it
void CCameradialogDlg::OnDblclkFilebox(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int curSel= (int) m_FileBox.GetFirstSelectedItemPosition();	
	*pResult = 0;
	LoadPicture(curSel);
	

}

// When the Camera 1 button is pressed it takes a picture with camera 1
void CCameradialogDlg::OnCamera1() 
{
	m_Save.EnableWindow(true);
	m_Clear.EnableWindow(true);
	
	TakePicture(1);
}

// When the Camera 2 button is pressed it takes a picture with camera 2
void CCameradialogDlg::OnCamera2() 
{
	m_Save.EnableWindow(true);
	m_Clear.EnableWindow(true);
	
	TakePicture(2);	
}

// When the Save button is pressed it saves the picture
void CCameradialogDlg::OnSave() 
{
	SavePicture();

	m_FileBox.InsertItem(0,m_File[0].m_Date,1);
	m_FileBox.SetItemText(0,1,m_File[0].m_Time);
	m_FileBox.SetItemText(0,2,m_File[0].m_Camera);
	m_FileBox.SetItemText(0,3,m_File[0].m_Size);
	
	
}

// When the Clear button is pressed it clears the box
void CCameradialogDlg::OnClear() 
{
	CClientDC dc(Black);
	CRect rect;
	Black->GetClientRect(&rect);
	dc.FillSolidRect( &rect, RGB(0,0,0) );
	
}

// This loads the list of previous files saved from FileData.cam
void CCameradialogDlg::LoadFile(Array<CFileData> &m_File)
{
	nRecords=0;
	ifstream fin("FileData.cam");					// This will create the file if it doesn't already exist
	fin.close();
	CFile fileOut( "FileData.cam", CFile::modeRead);
	
	if (fileOut.GetLength())
	{
	CArchive ar( &fileOut, CArchive::load );
	ar >> nRecords;
	if (nRecords<0)
		nRecords=0;
	m_File(nRecords);
	for (int x=0;x<nRecords;x++)
		ar >> m_File[x];
		ar.Close();
	}
	fileOut.Close();
}

// This will load the selected picture and display it
void CCameradialogDlg::LoadPicture(int a)
{
	if (a==0)
		MessageBox("No Picture Selected","ERROR",MB_ICONEXCLAMATION );
	else
	{
		if (Bitmap)
			delete Bitmap;
		Bitmap=new CBitmap;
		CString command;
		CString temp=m_File[a-1].m_Time;
		char* tempc=temp.GetBuffer(0);
		tempc[2]=';';
		command=m_File[a-1].m_Date+" "+temp+ "" + m_File[a-1].m_Camera+".dib";
		LoadBMPImage((LPCTSTR) command,*Bitmap,ppal);
		m_rpicture.SetBitmap(*Bitmap);
	}
}

// This takes a picture with the specified camera and displays it
BOOL CCameradialogDlg::TakePicture(int wCamera)
{

	Camera = wCamera;
	capCaptureSingleFrameOpen(VCWin1);
 
		if (!capCaptureSingleFrame( VCWin1 ))
		{
			MessageBox( "No camera present.", 
			"Initialization Error", 
			 MB_ICONEXCLAMATION );
			 capCaptureSingleFrameClose(VCWin1);
			return FALSE;
		}
	capCaptureSingleFrameClose(VCWin1);
	return TRUE;
}

// This saves the list of files to FileData.cam
void CCameradialogDlg::SavePictureHistory()
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

// This takes a picture and saves it without opening up the dialog
void CCameradialogDlg::TakePictureNow()
{
	ifstream fin("FileData.cam");
	fin.close();
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
	//OnCamera1();
	//OnSave();
	for (int x=0;x<10;x++)
	{
		TakePicture(1);
		Sleep(500)
	}
	if (TakePicture(1))
	{
		SavePicture();
	}
	capDriverDisconnect(VCWin1);
}

// Called when you change the Frequency by using the up down arrow
void CCameradialogDlg::OnChangeTvalue() 
{
	ChangeInterval();
}

// This is called when the time interval is changed
// It changes the interval to the current one
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

// Called when you change the Frequency select a different unit
void CCameradialogDlg::OnSelchangeFrequency() 
{
	ChangeInterval();	

}

//// When you change the Frequency enter a different number
void CCameradialogDlg::OnEditupdateFrequency() 
{
	ChangeInterval();
}

// Called when the window is destroyed and it disconnects the camera from the window
BOOL CCameradialogDlg::DestroyWindow() 
{
	capDriverDisconnect(VCWin1);
	return CDialog::DestroyWindow();
}

// Sets the text to the current language
void CCameradialogDlg::SetStrings()
{
	SetWindowText(Strings.get(IDS_F0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_F1));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_F2));
	GetDlgItem(IDC_CAMERA1)->SetWindowText(Strings.get(IDS_F3));
	GetDlgItem(IDC_CAMERA2)->SetWindowText(Strings.get(IDS_F4));
	GetDlgItem(IDC_CLEAR)->SetWindowText(Strings.get(IDS_F5));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_F6));
	GetDlgItem(IDC_SAVE)->SetWindowText(Strings.get(IDS_SAVE));
	

}

// Saves the last picture taken to a dib file
void CCameradialogDlg::SavePicture()
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
	CString FileN=(temp.m_Date+" " + TTime+temp.m_Camera+".dib");
	temp.FileName=FileN.GetBuffer(1);
	FileN.ReleaseBuffer();
	int work=capFileSaveDIB(VCWin1, temp.FileName); 

	SavePictureHistory();
}

