// Test Set System FontsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test Set System Fonts.h"
#include "Test Set System FontsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestSetSystemFontsDlg dialog

CTestSetSystemFontsDlg::CTestSetSystemFontsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSetSystemFontsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestSetSystemFontsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSetSystemFontsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSetSystemFontsDlg)
	DDX_Control(pDX, IDC_FONT_LIST, m_FontList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestSetSystemFontsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestSetSystemFontsDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSetSystemFontsDlg message handlers

BOOL CTestSetSystemFontsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_FontList.InsertColumn(0,"Font Type");
	m_FontList.InsertColumn(1,"Face Name");
	m_FontList.InsertColumn(2,"Charset");
	m_FontList.SetColumnWidth(0,LVSCW_AUTOSIZE_USEHEADER);
	m_FontList.SetColumnWidth(1,LVSCW_AUTOSIZE_USEHEADER);
	m_FontList.SetColumnWidth(2,LVSCW_AUTOSIZE_USEHEADER);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSetSystemFontsDlg::OnPaint() 
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
HCURSOR CTestSetSystemFontsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestSetSystemFontsDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	NONCLIENTMETRICS NCM;
	UINT fWinIni = 0;//SPIF_UPDATEINIFILE
	BOOL result;
	NCM.cbSize = sizeof(NONCLIENTMETRICS);
	
	//SPI_GETNONCLIENTMETRICS
	result = SystemParametersInfo(
				SPI_GETNONCLIENTMETRICS,  // system parameter to retrieve or set
				sizeof(NONCLIENTMETRICS),   // depends on action to be taken
				&NCM,  // depends on action to be taken
				fWinIni    // user profile update option
				);

	//LOGFONT lfCaptionFont; 
	//LOGFONT lfSmCaptionFont; 
	//LOGFONT lfMenuFont; 
	//LOGFONT lfStatusFont; 
	//LOGFONT lfMessageFont; 
	//TCHAR faceName[LF_FACESIZE];
	//BYTE cSet;
	int pos = 0;
	m_FontList.DeleteAllItems();
	AddInfo("CaptionFont",&NCM.lfCaptionFont, pos++);
	AddInfo("SmCaptionFont",&NCM.lfSmCaptionFont, pos++);
	AddInfo("MenuFont",&NCM.lfMenuFont, pos++);
	AddInfo("StatusFont",&NCM.lfStatusFont, pos++);
	AddInfo("MessageFont",&NCM.lfMessageFont, pos++);
}


void CTestSetSystemFontsDlg::AddInfo(char * fontType, LOGFONT * ptrFontStruct, int pos)
{
	char cBuf[10];
	wsprintf(cBuf,"%i",ptrFontStruct->lfCharSet);
	
	m_FontList.InsertItem(pos,fontType);//this could include an image number as the last parameter
	m_FontList.SetItemText(pos,1,ptrFontStruct->lfFaceName);
	m_FontList.SetItemText(pos,2,cBuf );

}

void CTestSetSystemFontsDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	NONCLIENTMETRICS NCM;
	UINT fWinIni = 0;// change this to zero if you don't want it to update user profile
	BOOL result;
	NCM.cbSize = sizeof(NONCLIENTMETRICS);
	
	//SPI_GETNONCLIENTMETRICS
	result = SystemParametersInfo(
				SPI_GETNONCLIENTMETRICS,  // system parameter to retrieve or set
				sizeof(NONCLIENTMETRICS),   // depends on action to be taken
				&NCM,  // depends on action to be taken
				fWinIni    // user profile update option
				);

	wsprintf(NCM.lfCaptionFont.lfFaceName,"Arial");
	wsprintf(NCM.lfSmCaptionFont.lfFaceName,"Arial");
	wsprintf(NCM.lfMenuFont.lfFaceName,"Arial");
	wsprintf(NCM.lfStatusFont.lfFaceName,"Arial");
	wsprintf(NCM.lfMessageFont.lfFaceName,"Arial");
	NCM.lfCaptionFont.lfCharSet = RUSSIAN_CHARSET;
	NCM.lfSmCaptionFont.lfCharSet = RUSSIAN_CHARSET;
	NCM.lfMenuFont.lfCharSet = RUSSIAN_CHARSET;
	NCM.lfStatusFont.lfCharSet = RUSSIAN_CHARSET;
	NCM.lfMessageFont.lfCharSet = RUSSIAN_CHARSET;

	fWinIni = SPIF_UPDATEINIFILE;

	result = SystemParametersInfo(
				SPI_SETNONCLIENTMETRICS,  // system parameter to retrieve or set
				sizeof(NONCLIENTMETRICS),   // depends on action to be taken
				&NCM,  // depends on action to be taken
				fWinIni    // user profile update option
				);

	//AddInfo("CaptionFont",&NCM.lfCaptionFont);
	//AddInfo("SmCaptionFont",&NCM.lfSmCaptionFont);
	//AddInfo("MenuFont",&NCM.lfMenuFont);
	//AddInfo("StatusFont",&NCM.lfStatusFont);
	//AddInfo("MessageFont",&NCM.lfMessageFont);
}

void CTestSetSystemFontsDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	static int wLang = 0;
	char * dlgTitle[] = {"Test Set System Fonts","Проверка Установки Системних Шрифт"};
	SetWindowText(dlgTitle[++wLang%2]);

}

void CTestSetSystemFontsDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	MessageBox("Test Set System Fonts","Test Set System Fonts");
}

void CTestSetSystemFontsDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
	MessageBox("Проверка Установки Системних Шрифт","Проверка Установки Системних Шрифт");
}
