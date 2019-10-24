// This is Version 1.0 PLEASE DOCUMENT CHANGES
// DataTransfer.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "DataTransfer.h"
#include <afxext.h>

#include "LADA Control ModuleDoc.h"
#include "ChooseIcon.h"
#include "resource.h"
#include "LadaStrings.h"
#include "LString.h"
#include "ProgressDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString BrowseForFolder(LPCSTR lpszTitle, UINT nFlags = 0, LPCITEMIDLIST pidlRoot = NULL, CWnd *parentWnd = NULL); // Selects a folder
extern CFont RussianArial;																			// The font used
extern void SetItemFont(UINT controlID, CWnd *window);													// Sets item to a Font
extern void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char *AdditionalMessage = NULL);	// Displays an Error Message
extern LString Strings;																					// Contains the strings for both languages
extern UINT MyMessageBox(UINT MessageID, UINT MessageTitleID = NO_TITLE, DWORD mFlags = MB_OK);			// Message Box
extern UINT MyMessageBox(const char *text, const char *title = NULL, DWORD mFlags = MB_OK);				// Message Box
extern UINT MyMessageBox(CString text, CString title = "", DWORD mFlags = MB_OK);						// Message Box
#undef MessageBox																						// Message Box
#define MessageBox MyMessageBox																			// Message Box

#define FILENAME	0																					// Used for which column
#define FILESIZE	1																					// Used for which column
#define FILETYPE	2																					// Used for which column
#define NEWFILE		3																					// Used for which column

char * FileTypeText[] = {"Picture - DIB","Picture - JPG","Data - Archive","Data - Real Time","Data - Diagnostic","History","Other"};  // An Array that keeps file types to display

//PictureDIB, PictureJPG, FinalStorage, InputLocation, Diagnostic, Other

/////////////////////////////////////////////////////////////////////////////
// CDataTransfer dialog


// Tries a directory and creates it if it doesn't exist
// m_Directory is the directory to try
BOOL TryDirectory(CString m_Directory)  
{
	if (!SetCurrentDirectory(m_Directory)){
		// see if the specified drive exists
		
		DWORD errNum = GetLastError();
		if (errNum == 21){ // drive isn't ready
			DisplayErrorMessage(errNum,FALSE,"\nMake sure the floppy disk is inserted.");
			return FALSE;
		}
		if (!SetCurrentDirectory(m_Directory.Left(3)))
		{  // drive doesn't exist
			errNum = GetLastError();	
			DisplayErrorMessage(errNum,FALSE);
			return FALSE;
		}
		// 2 - system cannot find the file specified
		// 3 - system cannot find the path specified
		
		if (errNum == 2 || errNum == 3){
			if (MessageBox(m_Directory + Strings.get(IDS_NO_SUCH_DIRECTORY_CREATE),CString(""), MB_YESNO |MB_ICONQUESTION ) == IDYES)
			{
				if (!CreateDirectory(m_Directory,NULL))
				{
					MessageBox(m_Directory + Strings.get(IDS_COULDNT_CREATE_DIR), NULL, MB_OK);
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			DisplayErrorMessage(errNum,FALSE);
			return FALSE;
		}
	}
	return TRUE;
}

 
// The Constructor
// doc is the current documnet
CDataTransfer::CDataTransfer(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CDataTransfer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataTransfer)
	m_DestinationFolder = _T("");
	m_SourceFolder = _T("");
	m_ArchiveFiles = FALSE;
	m_PictureFiles = FALSE;
	m_RealTime = FALSE;
	m_JPG = FALSE;
	m_DIB = FALSE;
	m_HistoryFiles = FALSE;
	//}}AFX_DATA_INIT
	pDoc = doc;
	m_PtrFileInfo = NULL;
	
}


//Destructor
CDataTransfer::~CDataTransfer()
{
	delete [] m_PtrFileInfo;
}



//Standard Data Exchange for controls
void CDataTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataTransfer)
	DDX_Control(pDX, IDC_JPG, m_Jpg);
	DDX_Control(pDX, IDC_DIB, m_Dib);
	DDX_Control(pDX, IDC_TOTAL_BYTES, m_TotalBytes);
	DDX_Control(pDX, IDC_FILELIST, m_FileList);
	DDX_Control(pDX, IDC_OTHER, m_Other);
	DDX_Control(pDX, IDC_NUM_SELECTED, m_NumSelected);
	DDX_Text(pDX, IDC_DESTINATION_FOLDER, m_DestinationFolder);
	DDX_Text(pDX, IDC_SOURCE_FOLDER, m_SourceFolder);
	DDX_Check(pDX, IDC_ARCHIVE_FILES, m_ArchiveFiles);
	DDX_Check(pDX, IDC_PICTURE_FILES, m_PictureFiles);
	DDX_Check(pDX, IDC_REAL_TIME_FILES, m_RealTime);
	DDX_Check(pDX, IDC_JPG, m_JPG);
	DDX_Check(pDX, IDC_DIB, m_DIB);
	DDX_Check(pDX, IDC_HISTORY_FILES, m_HistoryFiles);
	//}}AFX_DATA_MAP
}

//Standard Message Mapping for controls
BEGIN_MESSAGE_MAP(CDataTransfer, CDialog)
	//{{AFX_MSG_MAP(CDataTransfer)
	ON_BN_CLICKED(IDC_SET_DEFAULT, OnSetDefault)
	ON_BN_CLICKED(IDC_NEW_FILES_ONLY, OnNewFilesOnly)
	ON_BN_CLICKED(IDC_ALL_FILES, OnAllFiles)
	ON_BN_CLICKED(IDC_OTHER, OnBrowseDestination)
	ON_BN_CLICKED(IDC_FLOPPY, OnFloppy)
	ON_BN_CLICKED(IDC_PCMCIA, OnPcmcia)
	ON_BN_CLICKED(IDC_ARCHIVE_FILES, OnArchiveFiles)
	ON_BN_CLICKED(IDC_PICTURE_FILES, OnPictureFiles)
	ON_BN_CLICKED(IDC_REAL_TIME_FILES, OnRealTimeFiles)
	ON_BN_CLICKED(IDC_JPG, OnJpg)
	ON_BN_CLICKED(IDC_DIB, OnDib)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_FILELIST, OnColumnclickFilelist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILELIST, OnItemchangedFilelist)
	ON_BN_CLICKED(IDC_HISTORY_FILES, OnHistoryFiles)
	ON_NOTIFY(NM_DBLCLK, IDC_FILELIST, OnDblclkFilelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTransfer message handlers

// Sets the default for the Floppy Icon and the PCMCIA Card
void CDataTransfer::OnSetDefault() 
{
	UpdateData();
	BOOL IsFloppy;
	CChooseIcon dlg(&IsFloppy);
	if (dlg.DoModal() == IDCANCEL)
	{
		SetStrings();
		LVCOLUMN* x=new LVCOLUMN;
		for (int y=0;y<4;y++)
		{
			x->mask=LVCF_TEXT;
			m_FileList.GetColumn(y,x);
			CString a=Strings.get(IDS_G19+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_FileList.SetColumn(y,x);
		}
		delete x;
		return;
	}
		SetStrings();
		LVCOLUMN* x=new LVCOLUMN;
		for (int y=0;y<4;y++)
		{
			x->mask=LVCF_TEXT;
			m_FileList.GetColumn(y,x);
			CString a=Strings.get(IDS_G19+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_FileList.SetColumn(y,x);
		}
	
	if (IsFloppy)
	{
		pDoc->m_FloppyDefault = m_DestinationFolder;	
	}
	else
	{
		pDoc->m_PcmciaDefault = m_DestinationFolder;
	}
	pDoc->SetModifiedFlag(TRUE);
}

// This copies the files selected the the destination folder and then return to the main program
void CDataTransfer::OnOK() 
{

	if (!UpdateData())
		return;
	if (m_DestinationFolder.GetLength() < 3){
		MessageBox(IDS_M_INVALID_DIR_NAME, NULL, MB_ICONINFORMATION);
		ResetStrings();
		return;
	}
	char currDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currDir);
	if (!TryDirectory(m_DestinationFolder))
	{
		ResetStrings();
		return;
	}
	CWaitCursor wCursor();
	CString filea;
	CString fileb;
	if (m_DestinationFolder[m_DestinationFolder.GetLength() - 1] != '\\')
		m_DestinationFolder += "\\";

	BOOL copyCancelled;
	ProgressDialog pDlg(&copyCancelled, NULL, Strings.get(IDS_M_COPYING_FILES));
	pDlg.Create(PROGRESS_DIALOG);
	char buf[200];
	for (int x=0;x<m_nFiles;x++)
	{
		if (m_FileList.GetItemState(x,LVIS_SELECTED)==2)
		{ 
			filea=pDoc->dataFolder +"\\" +m_FileList.GetItemText(x,0);
			fileb=m_DestinationFolder + m_FileList.GetItemText(x,0);
			wsprintf(buf,"%s %s",Strings.get(IDS_M_COPYING),filea);
			pDlg.SetInfo(100 * x / m_nFiles, buf);
			if(CopyFile(filea,fileb,FALSE))
				SetFileAttributes(filea,FILE_ATTRIBUTE_NORMAL);
			else
			{
				DisplayErrorMessage(GetLastError());
				MessageBox("File transfer cancelled.","Error",MB_ICONWARNING);
				// write to error log
				break;
			}
			MSG Msg;
			PeekMessage( &Msg,         // message information
				NULL,           // handle to window
				0,//WM_MOUSEFIRST,  // first message  
				0,//WM_MOUSELAST );  // last message
				PM_REMOVE /*| PM_NOYIELD*/); //wRemoveMsg

			DispatchMessage( &Msg );  // message information);

			if (copyCancelled)
				break;
		}
	}
	pDlg.Close();
	pDoc->LastCopyFolder = m_DestinationFolder;
	pDoc->SetModifiedFlag();
	CDialog::OnOK();
}

// This selects toggles between New Files Only and All Files
void CDataTransfer::OnNewFilesOnly() 
{
	if (m_NewOnly == FALSE)
	{
		m_NewOnly = TRUE;
		PrepareFileList();
	}
}

// This selects toggles between New Files Only and All Files
void CDataTransfer::OnAllFiles() 
{
	if (m_NewOnly == TRUE)
	{
		m_NewOnly = FALSE;
		PrepareFileList();
	}
}

// Prepare file list is called when a change is
// made which affects which files are selected.
// it will update which files are selected...
void CDataTransfer::PrepareFileList()
{
	CButton *b1 = (CButton *)GetDlgItem(IDC_NEW_FILES_ONLY);
	CButton *b2 = (CButton *)GetDlgItem(IDC_ALL_FILES);
	b1->SetCheck(m_NewOnly);
	b2->SetCheck(!m_NewOnly);
	UpdateData();

	BOOL NewFlag = TRUE;
	BOOL AddSelection = FALSE;
	//m_nSelected = 0;
	//TotalBytes = 0;
	for (int i = 0; i < m_nFiles; i++)
	{
		if (m_NewOnly)
			NewFlag = m_PtrFileInfo[i].IsNewFile;
		
		switch (m_PtrFileInfo[i].fileType)
		{
		case (PictureDIB):
			{
				AddSelection = m_PictureFiles && m_DIB && NewFlag;
				m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
			}break;
		case (PictureJPG):
			{
				AddSelection = m_PictureFiles && m_JPG && NewFlag;
				m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
			}break;
		case (FinalStorage):
			{
				AddSelection = m_ArchiveFiles && NewFlag;
				m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
			}break;
		case (InputLocation):
			{
				AddSelection = m_RealTime && NewFlag;
				m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
			}break;
		case (History):
			{
				AddSelection = m_HistoryFiles && NewFlag;
				m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
			}break;
		//case (Diagnostic):
		//	{
		//		AddSelection = m_Diagnostic && NewFlag;
		//		m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
		//	}break;
		}
		if (AddSelection){
			//m_nSelected++;
			//TotalBytes += m_PtrFileInfo[i].FileSize;
		}
	}
	DisplayFileInfo();
	
}

// This sets the list of files and information in the list box
void CDataTransfer::GetFileList()//=TRUE
{
	// this is called at the beginning to create a list of
	// all relevant files...

	if (m_PtrFileInfo)
		delete [] m_PtrFileInfo;
	m_PtrFileInfo = new CFileInfo[1000];
	m_nFiles = 0;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	CString FileSearchInfo;
	FileSearchInfo = m_SourceFolder + "\\*.*";//dat";

	hFind = FindFirstFile(FileSearchInfo,&FindFileData);
	
	m_FileList.DeleteAllItems();

	int count = 0;
	if (hFind != INVALID_HANDLE_VALUE)
	{
		char ext[4];
		char fSize[8];
		do
		{
			count++;

			for (int extPos = strlen(FindFileData.cFileName); FindFileData.cFileName[extPos] != '.' && extPos > 0; extPos--);
			extPos++;
			strcpy(ext, &FindFileData.cFileName[extPos]);
			
			// no diagnostic type is created yet...

			if (strcmp(ext,InputLocationExtension) == 0)
				m_PtrFileInfo[m_nFiles].fileType = InputLocation;
			//else if (strcmp(ext,"dgn") == 0)
			//	m_PtrFileInfo[m_nFiles].fileType = Diagnostic;
			else if (strcmp(ext,FinalStorageExtension) == 0)
				m_PtrFileInfo[m_nFiles].fileType = FinalStorage;
			else if (strcmp(ext,DibExtension) == 0)
				m_PtrFileInfo[m_nFiles].fileType = PictureDIB;
			else if (strcmp(ext,JpgExtension) == 0)
				m_PtrFileInfo[m_nFiles].fileType = PictureJPG;
			else if (strcmp(ext,HistoryExtension) == 0)
				m_PtrFileInfo[m_nFiles].fileType = History;
			else
				m_PtrFileInfo[m_nFiles].fileType = Other;

			if (m_PtrFileInfo[m_nFiles].fileType != Other)
			{
				m_PtrFileInfo[m_nFiles].IsSelected = FALSE;
				m_PtrFileInfo[m_nFiles].IsNewFile = (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE ? TRUE : FALSE);
				m_PtrFileInfo[m_nFiles].FileSize = FindFileData.nFileSizeLow;
				wsprintf(fSize,"%iKB",(FindFileData.nFileSizeLow + 999) / 1000);
		
				m_FileList.InsertItem(m_nFiles,FindFileData.cFileName);//this could include an image number as the last parameter
				m_FileList.SetItemText(m_nFiles,FILESIZE,fSize);
				m_FileList.SetItemText(m_nFiles,FILETYPE,FileTypeText[m_PtrFileInfo[m_nFiles].fileType]);
				m_FileList.SetItemText(m_nFiles,NEWFILE,m_PtrFileInfo[m_nFiles].IsNewFile ? "Yes" : "No");
				m_nFiles++;
			}
		}
		while (FindNextFile(hFind, &FindFileData));
	}
	CloseHandle(hFind);

	m_FileList.SetColumnWidth(FILENAME,LVSCW_AUTOSIZE_USEHEADER);
	m_FileList.SetColumnWidth(FILESIZE,LVSCW_AUTOSIZE_USEHEADER);
	m_FileList.SetColumnWidth(FILETYPE,LVSCW_AUTOSIZE_USEHEADER);
	m_FileList.SetColumnWidth(NEWFILE,LVSCW_AUTOSIZE_USEHEADER);
//	FileSearchInfo="1";

}
// This does all the initialization work after the dialog is loaded such as:
//		Sets the Destination folder to the last one used
//		Sets the Source folder to the data folder
//		Sets the Fonts
//		Inserts columns into the list box
BOOL CDataTransfer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_DestinationFolder = pDoc->LastCopyFolder;
	m_SourceFolder = pDoc->dataFolder;
	m_NewOnly = TRUE;
	FloppyButton.AutoLoad(IDC_FLOPPY,this);
	PCMCIAButton.AutoLoad(IDC_PCMCIA,this);
	UpdateData(FALSE);
	ShowPictureStatus();
	m_FileList.SetFont(&RussianArial);
	m_FileList.InsertColumn(FILENAME,Strings.get(IDS_G19));
	m_FileList.InsertColumn(FILESIZE,Strings.get(IDS_G20));
	m_FileList.InsertColumn(FILETYPE,Strings.get(IDS_G21));
	m_FileList.InsertColumn(NEWFILE, Strings.get(IDS_G22));
	m_nSelected = 0;
	TotalBytes = 0;
	GetFileList();
	PrepareFileList();
	SetFont(&RussianArial);
	SetItemFont(IDOK,this);
	SetItemFont(IDCANCEL,this);
	SetItemFont(IDC_TEXT1,this);
	SetItemFont(IDC_TEXT2,this);
	SetItemFont(IDC_TEXT3,this);
	SetItemFont(IDC_TEXT4,this);
	//SetItemFont(IDC_TEXT5,this);
	SetItemFont(IDC_TEXT6,this);
	SetItemFont(IDC_TEXT7,this);
	SetItemFont(IDC_OTHER,this);
	//SetItemFont(IDC_DIBTOJPG,this);
	SetItemFont(IDC_SET_DEFAULT,this);
	SetItemFont(IDC_NEW_FILES_ONLY,this);
	SetItemFont(IDC_ALL_FILES,this);
	SetItemFont(IDC_ARCHIVE_FILES,this);
	SetItemFont(IDC_PICTURE_FILES,this);
	SetItemFont(IDC_REAL_TIME_FILES,this);
	SetItemFont(IDC_HISTORY_FILES,this);
	SetItemFont(IDC_ERROR_FILES,this);
	SetItemFont(IDC_JPG,this);
	SetItemFont(IDC_DIB,this);
	SetItemFont(IDC_SOURCE_FOLDER,this);
	SetItemFont(IDC_DESTINATION_FOLDER,this);
	SetItemFont(IDC_NUM_SELECTED,this);
	SetItemFont(IDC_TOTAL_BYTES,this);
	SetStrings();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

// When the Floppy Icon is pressed it sets the folder as what is set in the floppy
void CDataTransfer::OnFloppy() 
{
	UpdateData();
	m_DestinationFolder = pDoc->m_FloppyDefault;
	UpdateData(FALSE);
}

// When the Floppy Icon is pressed it sets the folder as what is set in the floppy
void CDataTransfer::OnPcmcia() 
{
	UpdateData();
	m_DestinationFolder = pDoc->m_PcmciaDefault ;
	UpdateData(FALSE);
}

// Selects a new folder from a tree menu for the destination
void CDataTransfer::OnBrowseDestination() 
{
	CString oldFolder = m_DestinationFolder;
	m_DestinationFolder = BrowseForFolder("Select Destination Folder for Data Files");
	if (m_DestinationFolder != "")
		UpdateData(FALSE);
	else
		m_DestinationFolder = oldFolder;
}

// Selects the Archive Files
void CDataTransfer::OnArchiveFiles() 
{
	PrepareFileList();
}

// Selects the Picture Files
void CDataTransfer::OnPictureFiles() 
{
	ShowPictureStatus();
	PrepareFileList();
}

// Selects the RealTime Files
void CDataTransfer::OnRealTimeFiles() 
{
	PrepareFileList();
}

// Converts DIB Files to JPG files
/*
void CDataTransfer::OnDibtojpb() 
{
	CString file;
	CString temp;
	CFile* File;
	CFile* sFile;

	for(int x=0;x<m_nFiles;x++)
	{
		file=m_FileList.GetItemText(x,0);
		if (m_PtrFileInfo[x].fileType==PictureDIB)
		{

			File=new CFile;
			sFile=new CFile;
			temp=pDoc->dataFolder + "\\" +m_FileList.GetItemText(x,0);
			file=pDoc->dataFolder + "\\" + file.Left(file.GetLength()-4)+".jpg";
			File->SetFilePath(temp.GetBuffer(0));
			sFile->SetFilePath(file.GetBuffer(0));
			SaveImage(LoadImage(File),sFile);
			delete sFile;
			delete File;					
		}
	}
}
*/

//Enables the Dib and Jpg Button
void CDataTransfer::ShowPictureStatus()
{
	UpdateData();
	if (m_PictureFiles)
	{
		m_Dib.EnableWindow(TRUE);
		m_Jpg.EnableWindow(TRUE);
		m_JPG = TRUE;
		m_DIB = FALSE;
		UpdateData(FALSE);
	}
	else
	{
		m_Dib.EnableWindow(FALSE);
		m_Jpg.EnableWindow(FALSE);
	}
}

// Selects Jpg Files
void CDataTransfer::OnJpg() 
{
	PrepareFileList();
}

// Selects Dib Files
void CDataTransfer::OnDib() 
{
	PrepareFileList();
}

// Sort the item in reverse alphabetical order.
int CALLBACK 
CDataTransfer::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM classObject)
{
	CDataTransfer * CDptr = (CDataTransfer *)classObject;

	switch (CDptr->nColumn)
	{
	case (FILENAME):
		{
			CDptr->m_FileList;	
		}break;
	case (FILESIZE):
		{

		}break;
	case (FILETYPE):
		{
			
		}break;
	case (NEWFILE):
		{

		}break;
	}
	return 1;
}

// Tells how many files are selected and the total size
void CDataTransfer::DisplayFileInfo()
{
	m_nSelected = 0;
	TotalBytes = 0;
	for (int i = 0; i < m_nFiles; i++)
	{
		if ( m_PtrFileInfo[i].IsSelected )	
		{
			TotalBytes += m_PtrFileInfo[i].FileSize;
			m_nSelected++;
		}
	}
	char n[15];
	wsprintf(n,"%i",m_nSelected);
	m_NumSelected.SetWindowText(n);
	wsprintf(n,"%iKB",(TotalBytes + 999) / 1000);
	m_TotalBytes.SetWindowText(n);
	m_FileList.SetFocus();
	GetDlgItem(IDOK)->EnableWindow(m_nSelected);
}

// Sorts by a column when you click on it
void CDataTransfer::OnColumnclickFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	nColumn = pNMListView->iItem;
	m_FileList.SortItems(MyCompareProc, (LPARAM) this);
	*pResult = 0;
}

// Selects a file when you click on it
void CDataTransfer::OnItemchangedFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_PtrFileInfo[pNMListView->iItem].IsSelected = m_FileList.GetItemState( pNMListView->iItem, LVIS_SELECTED );
	DisplayFileInfo();
	*pResult = 0;
}

// Sets the text in the dialog to the current language
void CDataTransfer::SetStrings()
{
	SetWindowText(Strings.get(IDS_G0));
	GetDlgItem(IDC_TEXT1)->SetWindowText(Strings.get(IDS_G1));
	GetDlgItem(IDOK)->SetWindowText(Strings.get(IDS_G2));	
	GetDlgItem(IDCANCEL)->SetWindowText(Strings.get(IDS_CANCEL));
	GetDlgItem(IDC_TEXT2)->SetWindowText(Strings.get(IDS_G3));
	GetDlgItem(IDC_OTHER)->SetWindowText(Strings.get(IDS_G4));
	GetDlgItem(IDC_SET_DEFAULT)->SetWindowText(Strings.get(IDS_G5));
	GetDlgItem(IDC_TEXT3)->SetWindowText(Strings.get(IDS_G6));
	//GetDlgItem(IDC_DIBTOJPG)->SetWindowText(Strings.get(IDS_G7));
	GetDlgItem(IDC_TEXT4)->SetWindowText(Strings.get(IDS_G8));
	GetDlgItem(IDC_NEW_FILES_ONLY)->SetWindowText(Strings.get(IDS_G9));
	GetDlgItem(IDC_ALL_FILES)->SetWindowText(Strings.get(IDS_G10));
	GetDlgItem(IDC_ARCHIVE_FILES)->SetWindowText(Strings.get(IDS_G11));
	GetDlgItem(IDC_PICTURE_FILES)->SetWindowText(Strings.get(IDS_G12));
	GetDlgItem(IDC_JPG)->SetWindowText(Strings.get(IDS_G13));
	GetDlgItem(IDC_DIB)->SetWindowText(Strings.get(IDS_G14));
	GetDlgItem(IDC_REAL_TIME_FILES)->SetWindowText(Strings.get(IDS_G15));
	//GetDlgItem(IDC_TEXT5)->SetWindowText(Strings.get(IDS_G16));
	GetDlgItem(IDC_TEXT6)->SetWindowText(Strings.get(IDS_G17));
	GetDlgItem(IDC_TEXT7)->SetWindowText(Strings.get(IDS_G18));
	GetDlgItem(IDC_HISTORY_FILES)->SetWindowText(Strings.get(IDS_G23));
	GetDlgItem(IDC_ERROR_FILES)->SetWindowText(Strings.get(IDS_G24));
}
BOOL CDataTransfer::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		Strings.ToggleLanguage();
		SetStrings();
		LVCOLUMN* x=new LVCOLUMN;
		for (int y=0;y<4;y++)
		{
			x->mask=LVCF_TEXT;
			m_FileList.GetColumn(y,x);
			CString a=Strings.get(IDS_G19+y);
			LPTSTR temp=a.GetBuffer(0);
			x->pszText=temp;
			m_FileList.SetColumn(y,x);
		}
		delete [] x;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDataTransfer::ResetStrings()
{
	SetStrings();
	LVCOLUMN* x=new LVCOLUMN;
	for (int y=0;y<4;y++)
	{
		x->mask=LVCF_TEXT;
		m_FileList.GetColumn(y,x);
		CString a=Strings.get(IDS_G19+y);
		LPTSTR temp=a.GetBuffer(0);
		x->pszText=temp;
		m_FileList.SetColumn(y,x);
	}

}

void CDataTransfer::OnHistoryFiles() 
{
	// TODO: Add your control notification handler code here
	PrepareFileList();
}

void CDataTransfer::OnDblclkFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_FileList.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int nItem = m_FileList.GetNextSelectedItem(pos);
		CString fileName = pDoc->dataFolder+"\\"+m_FileList.GetItemText(nItem,0);
		ShellExecute (GetSafeHwnd(), "open", fileName, "", "", 3);
	}

	*pResult = 0;
}
