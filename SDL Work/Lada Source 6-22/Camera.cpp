// Camera.cpp : implementation file
//
#include "TwainCpp.h"
#include "stdafx.h"
#include "lada control module.h"
#include "Camera.h"
#include "Dib.h"
#include "Lada Control ModuleDoc.h"
#include "LadaStrings.h"
#include "Lstring.h"
#include <fstream.h>
#include <string.h>
#include "CameraStatus.h"
#include "ProgressDialog.h"
#include "BTCImageObject.h"
#include "Historyclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamera dialog
extern LString Strings;												// The strings for both languages
extern CFont RussianArial;											// The font used
extern void SetFontText(UINT controlID, UINT stringID, CWnd *window);//Sets text to a font
extern void SetItemFont(UINT controlID, CWnd *window);				// Sets an item to a font
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);
#undef MessageBox
#define MessageBox MyMessageBox

CCamera* tdlg;
UINT SaveThread(LPVOID data)
{
	//Sleep(10000);
	DWORD waitResult = WaitForSingleObject( tdlg->cameraSuccessEvent, 90000 );
	ResetEvent( tdlg->cameraSuccessEvent ); // sets event to non-signaled state.	
	if (waitResult==WAIT_TIMEOUT)
		MessageBox(0);
	else
		tdlg->OnSave();
	return 0;
}


DWORD __stdcall UpdateCameraStatusDisplay(void *lpdata);

// LoadBMPImage	- Loads a BMP file and creates a bitmap GDI object
//		  also creates logical palette for it.// Returns	- TRUE for success
// sBMPFile	- Full path of the BMP file
// bitmap	- The bitmap object to initialize
// pPal		- Will hold the logical palette. Can be NULL

BOOL LoadBMPImage(LPCTSTR sBMPFile, CBitmap &bitmap, CPalette *pPal)
{
	CFile file;
	if( !file.Open( sBMPFile, CFile::modeRead) )
		return FALSE;
	BITMAPFILEHEADER bmfHeader;	// Read file header
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return FALSE;	// File type should be 'BM'
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))	
		return FALSE;
	// Get length of the remainder of the file and allocate memory
	DWORD nPackedDIBLen = file.GetLength() - sizeof(BITMAPFILEHEADER);
	HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, nPackedDIBLen);
	if (hDIB == 0)
		return FALSE;	// Read the remainder of the bitmap file.
	if (file.ReadHuge((LPSTR)hDIB, nPackedDIBLen) != nPackedDIBLen )
	{
		::GlobalFree(hDIB);	
		return FALSE;
	}
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB;
	// If bmiHeader.biClrUsed is zero we have to infer the number
	// of colors from the number of bits used to specify it.
	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 
						1 << bmiHeader.biBitCount;	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
			((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);
	// Create the logical palette	
	if( pPal != NULL )	
	{		// Create the palette
		if( nColors <= 256 )		
		{
			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
			LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];			
			pLP->palVersion = 0x300;
			pLP->palNumEntries = nColors;			
			for( int i=0; i < nColors; i++)			
			{
				pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
				pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
				pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
				pLP->palPalEntry[i].peFlags = 0;			
			}
			pPal->CreatePalette( pLP );
			delete[] pLP;
		}	
	}
	CClientDC dc(NULL);	
	CPalette* pOldPalette = NULL;
	if( pPal )	
	{
		pOldPalette = dc.SelectPalette( pPal, FALSE );
		dc.RealizePalette();	
	}
	HBITMAP hBmp = CreateDIBitmap( dc.m_hDC,		// handle to device context 
				&bmiHeader,	// pointer to bitmap size and format data 
				CBM_INIT,	// initialization flag 
				lpDIBBits,	// pointer to initialization data 
				&bmInfo,	// pointer to bitmap color-format data 
				DIB_RGB_COLORS);		// color-data usage 
	bitmap.Attach( hBmp );
	bitmap.SetBitmapDimension(bmiHeader.biWidth,bmiHeader.biHeight);

	if( pOldPalette )	
		dc.SelectPalette( pOldPalette, FALSE );	::GlobalFree(hDIB);
	return TRUE;
}

CCamera::CCamera(CLADAControlModuleDoc* doc, CWnd* pParent /*=NULL*/) // DOC = NULL
	: CDialog(CCamera::IDD, pParent)
{
	tdlg=this;
	ptrBitmap = NULL;
	pDoc = doc;
	//{{AFX_DATA_INIT(CCamera)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	cameraSuccessEvent = CreateEvent(NULL,TRUE,FALSE,"PICTURE_RECEIVED");
	m_ptrStatus = NULL;
	isAutoPicture = FALSE;
}

CCamera::~CCamera()
{
	//ReleaseTwain(); this is automatically called by the CTwain destructor
	delete [] m_PtrFileInfo;
	delete ptrBitmap;
}



void CCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamera)
	DDX_Control(pDX, IDC_PICTURE, m_picture);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamera, CDialog)
	//{{AFX_MSG_MAP(CCamera)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_BN_CLICKED(IDC_CAMERAA, OnCameraa)
	ON_BN_CLICKED(IDC_CAMERAB, OnCamerab)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, TestLoadPicture)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamera message handlers
void CCamera::LoadPicture(int a)
{
	if (a==0)
		MessageBox(IDS_M_NO_PICTURE_SELECTED,IDS_ERROR,MB_ICONEXCLAMATION );
	else
	{
		delete ptrBitmap;
		ptrBitmap=new CBitmap;
		
		CString command=pDoc->dataFolder+"\\"+m_PtrFileInfo[a-1];
		LoadBMPImage((LPCTSTR) command,*ptrBitmap,Palette);
		m_picture.SetBitmap((HBITMAP)*ptrBitmap);
	}
}

void CCamera::TestLoadPicture()
{
	BOOL testCancelled;
	ProgressDialog pDlg(&testCancelled, "Testing LoadPicture()","Loading a picture...");
	pDlg.Create(PROGRESS_DIALOG);
	
	CString ctemp=pDoc->dataFolder+"\\Clouds.bmp";
	CString file=pDoc->dataFolder+"\\Clouds.jpg";

	for (int i = 0; i < 20000; i++)
	{
/*		This tests the loading of pictures*/
	

		BTCImageObject conpict;
		conpict.Load(ctemp.GetBuffer(0));
		conpict.Save(file.GetBuffer(0),BTFILETYPE_JPEG);

		
		
		MSG Msg;
		PeekMessage( &Msg,         // message information
			NULL,           // handle to window
			0,//WM_MOUSEFIRST,  // first message  
			0,//WM_MOUSELAST );  // last message
			PM_REMOVE /*| PM_NOYIELD*/); //wRemoveMsg

		DispatchMessage( &Msg );  // message information);

		if (testCancelled)
			break;
		char buf[100];
		wsprintf(buf,"Loading picture %i",i);
		pDlg.SetInfo(100 * i / 20000, buf);
	}

	pDlg.Close();

}

void CCamera::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int curSel= (int) m_list.GetFirstSelectedItemPosition();	
	*pResult = 0;
	LoadPicture(curSel);
}

BOOL CCamera::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_list.SetFont(&RussianArial);
	m_list.InsertColumn(0,Strings.get(IDS_F16), LVCFMT_LEFT, 200);
	m_PtrFileInfo=NULL;
	GetFileList();
	//Bitmap=NULL;
	Palette=NULL;
	InitTwain(m_hWnd);// twain should only be initialized once...???
	if(!IsValidDriver())
	{
		MessageBox(IDS_M_UNABLE_LOAD_TWAIN,IDS_ERROR,MB_ICONWARNING|MB_OK);
		m_TwainInitialized = FALSE;
	}
	else
		m_TwainInitialized = TRUE;

	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
	SelectDefaultSource();
	SetFont(&RussianArial);
	SetItemFont(IDOK,this);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_CAMERAA,this);
	SetItemFont(IDC_CAMERAB,this);
	SetItemFont(IDC_SAVE,this);
	SetStrings();
//	Acquire(TWCPP_ANYCOUNT);
	
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCamera::GetFileList()
{
//	pDoc->dataFolder=
	m_SourceFolder = pDoc->dataFolder;
	delete [] m_PtrFileInfo;
	m_PtrFileInfo = new CString[10000];
	m_nFiles = 0;
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	CString *FileSearchInfo=new CString;
	*FileSearchInfo = m_SourceFolder + "\\*.*";//dat";
	char* dib="dib";
	char* bimp="bmp";

	hFind = FindFirstFile(*FileSearchInfo,&FindFileData);
	
	m_list.DeleteAllItems();

	if (hFind != INVALID_HANDLE_VALUE)
	{
		char ext[25];
		do
		{
			for (int extPos = strlen(FindFileData.cFileName); FindFileData.cFileName[extPos] != '.' && extPos > 0; extPos--);
			extPos++;
			strcpy(ext, &FindFileData.cFileName[extPos]);
		
			if (strcmp(ext,dib) == 0 || strcmp(ext,bimp)==0)
			{
				m_PtrFileInfo[m_nFiles] = FindFileData.cFileName;
				m_list.InsertItem(m_nFiles,FindFileData.cFileName);//this could include an image number as the last parameter
				m_nFiles++;
			}			
			
		}
		while (FindNextFile(hFind, &FindFileData));
	}
	m_list.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	CloseHandle(hFind);
	delete FileSearchInfo;

}


void CCamera::OnCameraa() 
{
	BOOL Success = TakePicture(0);
	GetDlgItem(IDC_SAVE)->EnableWindow(Success);
	if (!Success)
	{
		pDoc->m_ErrorFiles->WriteHistory(IDS_E_CAMERA, IDS_E_CAMERA_A);
	}
}

void CCamera::OnCamerab() 
{
	BOOL Success = TakePicture(1);
	GetDlgItem(IDC_SAVE)->EnableWindow(Success);
	if (!Success)
	{
		pDoc->m_ErrorFiles->WriteHistory(IDS_E_CAMERA, IDS_E_CAMERA_B);

	
	}
}

void CCamera::OnSave() 
{
	CWaitCursor wCursor;
	CString tempf;
//	CString look=now.Format("%B");
	tempf=LastPictureTaken.Format("%B %d, %y %H;%M");
	tempf="\\"+tempf+".dib";
	CString temp=pDoc->dataFolder.GetBuffer(0)+tempf;
	ofstream fout(temp.GetBuffer(0));
	fout.close();
	CString ctemp=pDoc->dataFolder+tempf;
	if (m_Dib.width==0)
	{
		MessageBox(IDS_M_FAIL_SAVE_PICTURE,IDS_PROGRAM_NAME,MB_ICONWARNING|MB_OK);
		return;
	}
	m_Dib.SaveBMP(ctemp);
	CString file;
	file=ctemp.Left(ctemp.GetLength()-4)+".jpg";
	BTCImageObject conpict;
	conpict.Load(ctemp.GetBuffer(0));
	conpict.Save(file.GetBuffer(0),BTFILETYPE_JPEG);
	ctemp.ReleaseBuffer();
	file.ReleaseBuffer();
	GetFileList();
}

void CCamera::CopyImage(HANDLE hBitmap,TW_IMAGEINFO& info)
{
	SetImage(hBitmap,info.BitsPerPixel);
}

void CCamera::SetImage(HANDLE hBitmap,int bits)
{
	CWaitCursor wCursor;
	//CWinApp *pApp = AfxGetApp();
	//POSITION pos = pApp->GetFirstDocTemplatePosition();
	//CMultiDocTemplate *pTemplate = (CMultiDocTemplate *)pApp->GetNextDocTemplate(pos);
	//CTwaintestDoc *pDoc =  (CTwaintestDoc *)pTemplate->OpenDocumentFile(NULL);
	/*if(pDoc)
	{*/
	//	CDIB dib;
	//	dib.CreateFromHandle(hBitmap,bits);
	//if(bits == 24)  pDoc->m_Dib = dib;
	//	else Create24Bit(dib,pDoc->m_Dib);
	//	pDoc->UpdateAllViews(NULL);
	//}*/
	//CString temp="Temp.bmp";
	//dib.SaveBMP(temp);
	//Bitmap=new CBitmap;

//**************************
// Test Version 1
//	CDIB dib;
//	dib.CreateFromHandle(hBitmap,bits);
//	m_Dib = dib;
//
//	CDC * dc = GetDC();
//	if (dc)
//	{
//		ptrBitmap = m_Dib.GetBitmap(*dc);
//		m_picture.SetBitmap((HBITMAP)*ptrBitmap);//*Bitmap);
//	}

//**************************
// Test Version 2  created 4/14
//	
	m_Dib.DestroyDIB();
	m_Dib.CreateFromHandle(hBitmap,bits);
	DeleteObject(hBitmap);

	CDC * dc = GetDC();
	if (dc) 
	{
		delete ptrBitmap;
	//	ptrBitmap = new CBitmap;
		ptrBitmap = m_Dib.GetBitmap(*dc);
		m_picture.SetBitmap((HBITMAP)*ptrBitmap);//*Bitmap);
	}

//**************************8
// Test Version 3

	
	//m_picture.SetBitmap(hBitmap);
	
	SetEvent(cameraSuccessEvent);
		GetDlgItem(IDC_SAVE)->EnableWindow(TRUE);
	// means the picture can now be saved...
}



void CCamera::SetDocument(CLADAControlModuleDoc *doc)
{
	pDoc = doc;
}

BOOL CCamera::PreTranslateMessage(MSG* pMsg) 
{
	ProcessMessage(*pMsg);
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		LVCOLUMN* x=new LVCOLUMN;
		char* tempst=new char[20];
		x->mask=LVCF_TEXT;
		x->pszText=tempst;
		x->cchTextMax=20;
		m_list.GetColumn(0,x);
		CString a=Strings.get(IDS_F15);
		LPTSTR temp=a.GetBuffer(0);
		x->pszText=temp;
		m_list.SetColumn(0,x);
		delete x;
		delete tempst;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam==13)
	{
		return TRUE;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CCamera::SetStrings()
{
	SetWindowText(Strings.get(IDS_F0));
	GetDlgItem(IDC_CAMERAA)->SetWindowText(Strings.get(IDS_F3));
	GetDlgItem(IDC_CAMERAB)->SetWindowText(Strings.get(IDS_F4));
	GetDlgItem(IDC_SAVE)->SetWindowText(Strings.get(IDS_SAVE));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_OK));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_F15));

}



void CCamera::OnOK() 
{
	ShowWindow(SW_HIDE);	
}

void CCamera::SendEnter()
{
	SetTimer(1,100,NULL);
}

void CCamera::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==1)
	{
		KillTimer(1);
		::BroadcastSystemMessage(BSF_POSTMESSAGE,BSM_ALLCOMPONENTS,WM_KEYDOWN,13,0);
		//::SendMessage(GetTopWindow()->GetSafeHwnd(),WM_KEYDOWN,13,0);
		//SendMessageToDescendants(WM_CLOSE);
	}
	
	
	//CDialog::OnTimer(nIDEvent);
}

void CCamera::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	//CDialog::PostNcDestroy();
}

void CCamera::OnDestroy() 
{
	
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CCamera::TakePicture(int wChamber)
{
	LastPictureTaken=CTime::GetCurrentTime();
	CWaitCursor();
	Acquire(1);//TWCPP_ANYCOUNT))
	// put this process to sleep for up to x seconds... wait to see if the event is signaled that
	// means the picture was successful.
//	if (!isAutoPicture)
//		CloseStatusWindow();
	GetDlgItem(IDC_SAVE)->EnableWindow(FALSE);
//	GetDlgItem(IDC_SAVE)->EnableWindow(waitResult != WAIT_TIMEOUT);
//	if (waitResult == WAIT_TIMEOUT)
//		return FALSE;
	return TRUE;
}

BOOL CCamera::AutoPicture(int which_camera)
{
	ResetEvent( tdlg->cameraSuccessEvent ); // sets event to non-signaled state.	
	isAutoPicture = TRUE;
	if (TakePicture(which_camera))
	{
		AfxBeginThread(SaveThread,this);
	//	OnSave();
		return TRUE;
	}
	CloseStatusWindow();
	return FALSE;
}

void CCamera::CreateStatusWindow()
{
	if (!m_ptrStatus)
	{
		IsCanceled = FALSE;
		m_ptrStatus = new CCameraStatus(&IsCanceled);
		m_ptrStatus->Create(IDD_PICTURE_STATUS);
	}
}

void CCamera::CloseStatusWindow()
{
	if (m_ptrStatus)
	{
		m_ptrStatus->KillWindow();
		m_ptrStatus = NULL;
	}
}

/*
startTime = CTime::GetCurrentTime();
		m_ptrStatus->SetTimeElapsed(0);

		
		DisplayInfo * displayInfo = new DisplayInfo;
		displayInfo->camStatusWindow = &m_ptrStatus;
		displayInfo->startTime = &startTime;
		displayInfo->hDisplay = m_ptrStatus->GetSafeHwnd();

		DWORD dwThreadID;
		hStatusThread =  CreateThread( (LPSECURITY_ATTRIBUTES) NULL,
									0,
									UpdateCameraStatusDisplay,
									(LPVOID) displayInfo,
									0, &dwThreadID );
									
struct DisplayInfo
{
public:
	CTime * startTime;
	CCameraStatus ** camStatusWindow;
	HWND hDisplay;
};
DWORD __stdcall UpdateCameraStatusDisplay(void *lpdata)
{
	CTime * ptrStartTime = ((DisplayInfo *)lpdata)->startTime;
	CCameraStatus ** ptrStatusWnd = ((DisplayInfo *)lpdata)->camStatusWindow;
	HWND hWnd = ((DisplayInfo *)lpdata)->hDisplay;
	delete lpdata;

	SYSTEMTIME SystemTime;
	GetSystemTime(&SystemTime);
	FILETIME DueTime;
	SystemTimeToFileTime(&SystemTime,&DueTime);
	
	HANDLE DisplayTimer = CreateWaitableTimer(NULL,FALSE,"UpdateCameraWindowTimer");

	if (!SetWaitableTimer(DisplayTimer,(LARGE_INTEGER*) &DueTime,1000,NULL,NULL,TRUE))
	{
		AfxMessageBox( "Failed to set timer for new thread!", 
                  MB_ICONEXCLAMATION | MB_OK ) ;
		return ( FALSE ) ;
	}
	
	

	while (*ptrStatusWnd)
	{
		WaitForSingleObject( DisplayTimer, INFINITE );
		LONG TimeElapsed = (CTime::GetCurrentTime() - (*ptrStartTime)).GetTotalSeconds();
		if (*ptrStatusWnd)
			(*ptrStatusWnd)->SetTimeElapsed(TimeElapsed);	
		
	}

	CloseHandle( DisplayTimer );
	return ( TRUE );
}
*/
