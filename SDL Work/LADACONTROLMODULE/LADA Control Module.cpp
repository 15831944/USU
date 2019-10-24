// LADA Control Module.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LADA Control Module.h"

#include "MainFrm.h"
#include "LADA Control ModuleDoc.h"
#include "GraphButtonForm.h"
#include "GraphWindow.h"
#include "CameradialogDlg.h"
#include "StartDialog.h"
#include "LADASetupDlg.h"
#include "LADADIAGDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleApp

BEGIN_MESSAGE_MAP(CLADAControlModuleApp, CWinApp)
	//{{AFX_MSG_MAP(CLADAControlModuleApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleApp construction

CLADAControlModuleApp::CLADAControlModuleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLADAControlModuleApp object

CLADAControlModuleApp theApp;

class CCameradialogDlg;

char workingDirectory[_MAX_PATH];

CFont smallRussianArial;
CFont largeRussianArial;
CFont RussianArial;
int   curLanguage = ENGLISH;
CCameradialogDlg *cameraDlg;

//static data members
CTimeSpan DataPlotFreqTable[] = {
	CTimeSpan(0,0,0,1),CTimeSpan(0,0,0,5),CTimeSpan(0,0,0,20),
	CTimeSpan(0,0,1,0),CTimeSpan(0,0,3,0),CTimeSpan(0,0,6,0),
	CTimeSpan(0,0,15,0)};
int BackPointsTable[] = {100,500,1000,300};
CTimeSpan DataRetrievalFreqTable[] = {
	CTimeSpan(0,0,0,1),CTimeSpan(0,0,0,2),CTimeSpan(0,0,0,3),
	CTimeSpan(0,0,0,4),CTimeSpan(0,0,0,5),CTimeSpan(0,0,0,6),
	CTimeSpan(0,0,0,10),CTimeSpan(0,0,0,15),CTimeSpan(0,0,0,30),
	CTimeSpan(0,0,1,0)};
CTimeSpan DataSaveFreqTable[] = {
	CTimeSpan(0,0,0,1),CTimeSpan(0,0,0,30),CTimeSpan(0,0,1,0),
	CTimeSpan(0,0,5,0),CTimeSpan(0,0,15,0),CTimeSpan(0,0,30,0),
	CTimeSpan(0,1,0,0)};
CTimeSpan CreateFileFreqTable[] = {
	CTimeSpan(0,1,0,0),CTimeSpan(1,0,0,0),CTimeSpan(7,0,0,0)};
int CreateFileBySizeTable[] = {
	50,100,500};

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleApp initialization

BOOL CLADAControlModuleApp::InitInstance()
{
	
	smallRussianArial.CreateFont(14,0,0,0,FW_NORMAL,0,0,0,RUSSIAN_CHARSET,0,0,0,0,"Arial");
	RussianArial.CreateFont(20,0,0,0,FW_NORMAL,0,0,0,RUSSIAN_CHARSET,0,0,0,0,"Arial");
	largeRussianArial.CreateFont(30,0,0,0,FW_BOLD,0,0,0,RUSSIAN_CHARSET,0,0,0,0,"Arial");

#ifdef _RAPID_TRANSLATION
	/* This fills RapTra start params. See "RapTra.h" for details */
	RT_STARTPARAMS StartPars;
	_tcscpy(StartPars.szStdFile, _T("LADA Control Module.tra"));
	_tcscpy(StartPars.szTraPath, _T(""));
	StartPars.bAutoSwitchCommand = TRUE;
	StartPars.nSwitchCommandID = 0x1234;
	StartPars.nSwitchMainMenuPos = 1;
	StartPars.bSwitchDlgAllowOld = TRUE;
	StartPars.nSwitchDlgHelpID = 123;
	StartPars.hRegKey = 0; //GetAppRegistryKey();
	_tcscpy(StartPars.szIniFilePath, _T("LADA Control Module.ini"));
	StartPars.nSwitchBroadcastMsg = WM_SWITCH_LANGUAGE; // Add registered message here

	/* This starts RapTra */
	RTStart(&StartPars);
	RTAddThread(GetCurrentThreadId());
#endif

	/*
	{	// BLOCK: doc template registration
		// Register the document template.  Document templates serve
		// as the connection between documents, frame windows and views.
		// Attach this form to another document or frame window by changing
		// the document or frame class in the constructor below.
		CSingleDocTemplate* pNewDocTemplate = new CSingleDocTemplate(
			IDR_GRAPHBUTTONFORM_TMPL,
			RUNTIME_CLASS(CLADAControlModuleDoc),		// document class
			RUNTIME_CLASS(CGraphWindow),		// frame class
			RUNTIME_CLASS(CGraphButtonForm));		// view class
		AddDocTemplate(pNewDocTemplate);
	}
	*/

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLADAControlModuleDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		NULL);
	AddDocTemplate(pDocTemplate);

	UINT choice = 0;
	
	CStartDialog *StartDialog;
	BOOL ContinueStart = TRUE;
	while (ContinueStart)
	{
		StartDialog = new CStartDialog(&choice);
		StartDialog->DoModal();
		delete StartDialog;
		
		switch (choice) {
		case ID_SETUP:
		{
			CLADASetupDlg *test = new CLADASetupDlg();
			test->DoModal();
			delete test;
			break;
		}
		case ID_CHECK_OUT:
		{
			CLADADIAGDlg dlg;
			dlg.DoModal();
			break;
		}
		case ID_WET_UP:
		{
			
			// If some condition is met at the end of
			// wet up, then do this : ContinueStart = FALSE;
			break;
		}
		case ID_NORMAL:
		{
			ContinueStart = FALSE;
			break;
		}
		case ID_DIAGNOSTICS:
		{
			break;
		}
		case ID_EXIT:
		default:
			return TRUE;
		}
	}
	
	cameraDlg = new CCameradialogDlg;

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// if no file is specified to be opened from the command line,
	// then look for the last file which was opened.
	// if one is found, open it.  otherwise a new document will
	// be created
	if (cmdInfo.m_strFileName.IsEmpty()){
		cmdInfo.m_strFileName = GetLastFile();
		if (!cmdInfo.m_strFileName.IsEmpty())
			cmdInfo.m_nShellCommand = CCommandLineInfo::FileOpen;
	}
	
	GetCurrentDirectory(_MAX_PATH, workingDirectory);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void SetFontText(UINT controlID, UINT stringID, CWnd *window)
{
	static CString s;
	static CWnd *wnd;
	wnd = window->GetDlgItem(controlID);
	wnd->SetFont(&smallRussianArial);
	s.LoadString(stringID);
	wnd->SetWindowText(s);
}

void SetItemFont(UINT controlID, CWnd *window)
{
	static CWnd *wnd;
	wnd = window->GetDlgItem(controlID);
	wnd->SetFont(&smallRussianArial);
}

CString CLADAControlModuleApp::GetLastFile(){
	HANDLE fileIn;
	fileIn = CreateFile("lastfile.txt", 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileIn == INVALID_HANDLE_VALUE){
		CloseHandle(fileIn);
		return CString("");
	}
	DWORD fileNameLength;
	DWORD bytesRead;
	char fileName[_MAX_PATH];

	ReadFile(fileIn,&fileNameLength,sizeof(fileNameLength),&bytesRead,NULL);
	ReadFile(fileIn,fileName,fileNameLength,&bytesRead,NULL);
	
	CloseHandle(fileIn);
	fileIn = CreateFile(fileName, 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	
	if (fileIn == INVALID_HANDLE_VALUE){
		CloseHandle(fileIn);
		return CString("");
	}
	CFile lastFile((int)fileIn);
	if (lastFile.GetLength() == 0){
		lastFile.Close();
		return CString("");
	}
	lastFile.Close();
	return CString(fileName);
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CStatic	m_Text3;
	CStatic	m_Text4;
	CStatic	m_Text2;
	CStatic	m_Text1;
	CButton	m_OKButton;
	CString	m_T1;
	CString	m_T2;
	CString	m_T3;
	CString	m_T4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_T1 = _T("");
	m_T2 = _T("");
	m_T3 = _T("");
	m_T4 = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_ABOUT_TEXT_3, m_Text3);
	DDX_Control(pDX, IDC_ABOUT_TEXT_4, m_Text4);
	DDX_Control(pDX, IDC_ABOUT_TEXT_2, m_Text2);
	DDX_Control(pDX, IDC_ABOUT_TEXT_1, m_Text1);
	DDX_Control(pDX, IDOK, m_OKButton);
	DDX_Text(pDX, IDC_ABOUT_TEXT_1, m_T1);
	DDX_Text(pDX, IDC_ABOUT_TEXT_2, m_T2);
	DDX_Text(pDX, IDC_ABOUT_TEXT_3, m_T3);
	DDX_Text(pDX, IDC_ABOUT_TEXT_4, m_T4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLADAControlModuleApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLADAControlModuleApp message handlers


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Text1.SetFont(&smallRussianArial);
	m_Text2.SetFont(&smallRussianArial);
	m_Text3.SetFont(&smallRussianArial);
	m_Text4.SetFont(&smallRussianArial);
	m_OKButton.SetFont(&smallRussianArial);
	m_T1.LoadString(IDS_ABOUT_TEXT_1);
	m_T2.LoadString(IDS_ABOUT_TEXT_2);
	m_T3.LoadString(IDS_ABOUT_TEXT_3);
	m_T4.LoadString(IDS_ABOUT_TEXT_4);
	CString s;
	s.LoadString(IDS_OK);
	static_cast<CWnd *>(&m_OKButton)->SetWindowText(s);
	SetFont(&RussianArial);
	s.LoadString(IDS_ABOUT_TITLE);
	SetWindowText(s);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CLADAControlModuleApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
#ifdef _RAPID_TRANSLATION
	RTEnd();
#endif
	delete cameraDlg;
	return CWinApp::ExitInstance();

}

void CLADAControlModuleApp::OnFileOpen()
{
	CWinApp::OnFileOpen();
}
