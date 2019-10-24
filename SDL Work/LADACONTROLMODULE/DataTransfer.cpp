// DataTransfer.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "DataTransfer.h"
#include <afxext.h>

#include "LADA Control ModuleDoc.h"
#include "ChooseIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString BrowseForFolder(LPCSTR lpszTitle, UINT nFlags = 0, LPCITEMIDLIST pidlRoot = NULL, CWnd *parentWnd = NULL);
extern CFont smallRussianArial;
extern void DisplayErrorMessage(DWORD ErrorNum, BOOL showNum = TRUE, char *AdditionalMessage = NULL);

#define FILENAME	0
#define FILESIZE	1
#define FILETYPE	2
#define NEWFILE		3

char * FileTypeText[] = {"Picture - DIB","Picture - JPG","Data - Archive","Data - Real Time","Data - Diagnostic","Other"};

//PictureDIB, PictureJPG, FinalStorage, InputLocation, Diagnostic, Other

/////////////////////////////////////////////////////////////////////////////
// CDataTransfer dialog


CDataTransfer::CDataTransfer(CLADAControlModuleDoc * doc, CWnd* pParent /*=NULL*/)
	: CDialog(CDataTransfer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataTransfer)
	m_DestinationFolder = _T("");
	m_SourceFolder = _T("");
	m_ArchiveFiles = FALSE;
	m_PictureFiles = FALSE;
	m_RealTime = FALSE;
	m_Diagnostic = FALSE;
	m_JPG = FALSE;
	m_DIB = FALSE;
	//}}AFX_DATA_INIT
	pDoc = doc;
	m_PtrFileInfo = NULL;
	
}

CDataTransfer::~CDataTransfer()
{
	delete [] m_PtrFileInfo;
}


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
	DDX_Check(pDX, IDC_DIAGNOSTIC, m_Diagnostic);
	DDX_Check(pDX, IDC_JPG, m_JPG);
	DDX_Check(pDX, IDC_DIB, m_DIB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataTransfer, CDialog)
	//{{AFX_MSG_MAP(CDataTransfer)
	ON_BN_CLICKED(IDC_SET_DEFAULT, OnSetDefault)
	ON_BN_CLICKED(IDC_NEW_FILES_ONLY, OnNewFilesOnly)
	ON_BN_CLICKED(IDC_ALL_FILES, OnAllFiles)
	ON_BN_CLICKED(IDC_OTHER, OnBrowseDestination)
	ON_BN_CLICKED(IDC_FLOPPY, OnFloppy)
	ON_BN_CLICKED(IDC_PCMCIA, OnPcmcia)
	ON_BN_CLICKED(IDC_ARCHIVE_FILES, OnArchiveFiles)
	ON_BN_CLICKED(IDC_DIAGNOSTIC, OnDiagnostic)
	ON_BN_CLICKED(IDC_PICTURE_FILES, OnPictureFiles)
	ON_BN_CLICKED(IDC_REAL_TIME_FILES, OnRealTimeFiles)
	ON_BN_CLICKED(IDC_DIBTOJPB, OnDibtojpb)
	ON_BN_CLICKED(IDC_JPG, OnJpg)
	ON_BN_CLICKED(IDC_DIB, OnDib)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_FILELIST, OnColumnclickFilelist)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILELIST, OnItemchangedFilelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataTransfer message handlers

void CDataTransfer::OnSetDefault() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	BOOL IsFloppy;
	CChooseIcon dlg(&IsFloppy);
	if (dlg.DoModal() == IDCANCEL)
		return;
	if (IsFloppy){
		pDoc->m_FloppyDefault = m_DestinationFolder;	
	}
	else
	{
		pDoc->m_PcmciaDefault = m_DestinationFolder;
	}
	pDoc->SetModifiedFlag(TRUE);

	//pDoc->DestinationFolder = m_DestinationFolder;

}

void CDataTransfer::OnOK() 
{
	// TODO: Add extra validation here
	if (!UpdateData())
		return;
	if (m_DestinationFolder.GetLength() < 3){
		AfxMessageBox("Invalid Directory Name",MB_ICONINFORMATION);
		return;
	}
	// copy now...

	//HANDLE dirHandle = CreateFile(m_DestinationFolder,GENERIC_READ,
	//	NULL,
		//NULL,OPEN_EXISTING,NULL,NULL);
	
	char currDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currDir);

	if (!SetCurrentDirectory(m_DestinationFolder)){
		// see if the specified drive exists
		
		DWORD errNum = GetLastError();
		if (errNum == 21){ // drive isn't ready
			DisplayErrorMessage(errNum,FALSE,"\nMake sure the floppy disk is inserted.");
			return;
		}
		if (!SetCurrentDirectory(m_DestinationFolder.Left(3)))
		{  // drive doesn't exist
			errNum = GetLastError();	
			DisplayErrorMessage(errNum,FALSE);
			return;
		}
		// 2 - system cannot find the file specified
		// 3 - system cannot find the path specified
		
		if (errNum == 2 || errNum == 3){
			if (AfxMessageBox(m_DestinationFolder + " does not exist.  Would you like to create this directory?",MB_YESNO) == IDYES)
			{

			}
			else
				return;
		}
		else
		{
			DisplayErrorMessage(errNum,FALSE);
			return;
		}
	}

	CDialog::OnOK();
}

void CDataTransfer::OnNewFilesOnly() 
{
	// TODO: Add your control notification handler code here
	if (m_NewOnly == FALSE)
	{
		m_NewOnly = TRUE;
		PrepareFileList();
	}
}

void CDataTransfer::OnAllFiles() 
{
	// TODO: Add your control notification handler code here
	if (m_NewOnly == TRUE)
	{
		m_NewOnly = FALSE;
		PrepareFileList();
	}
}

void CDataTransfer::PrepareFileList()
{
	// prepare file list is called when a change is
	// made which affects which files are selected.
	// it will update which files are selected...

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
		case (Diagnostic):
			{
				AddSelection = m_Diagnostic && NewFlag;
				m_FileList.SetItemState(i, AddSelection ? LVIS_SELECTED : 0, LVIS_SELECTED );
			}break;
		}
		if (AddSelection){
			//m_nSelected++;
			//TotalBytes += m_PtrFileInfo[i].FileSize;
		}
	}
	DisplayFileInfo();
}

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
	CString FileSearchInfo = m_SourceFolder + "\\*.*";//dat";

	hFind = FindFirstFile(FileSearchInfo,&FindFileData);
	
	m_FileList.DeleteAllItems();

	if (hFind != INVALID_HANDLE_VALUE)
	{
		char ext[4];
		char fSize[8];
		do
		{
			strcpy(ext, &FindFileData.cFileName[strlen(FindFileData.cFileName) - 3]);
			
			if (strcmp(ext,"iln") == 0)
				m_PtrFileInfo[m_nFiles].fileType = InputLocation;
			else if (strcmp(ext,"dgn") == 0)
				m_PtrFileInfo[m_nFiles].fileType = Diagnostic;
			else if (strcmp(ext,"fsn") == 0)
				m_PtrFileInfo[m_nFiles].fileType = FinalStorage;
			else if (strcmp(ext,"dib") == 0)
				m_PtrFileInfo[m_nFiles].fileType = PictureDIB;
			else if (strcmp(ext,"jpg") == 0)
				m_PtrFileInfo[m_nFiles].fileType = PictureJPG;
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
	m_FileList.SetColumnWidth(FILENAME,LVSCW_AUTOSIZE_USEHEADER);
	m_FileList.SetColumnWidth(FILESIZE,LVSCW_AUTOSIZE_USEHEADER);
	m_FileList.SetColumnWidth(FILETYPE,LVSCW_AUTOSIZE_USEHEADER);
	m_FileList.SetColumnWidth(NEWFILE,LVSCW_AUTOSIZE_USEHEADER);

}

BOOL CDataTransfer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_AddToZip = FALSE;//pDoc->AddDataToZip;
	//m_ArchiveName = "LadaData.zip";//pDoc->ZipName;
	
	m_DestinationFolder = "F:\\LADA Data";//pDoc->DestinationFolder;
	m_SourceFolder = pDoc->dataFolder;
	m_NewOnly = TRUE;
	
	FloppyButton.AutoLoad(IDC_FLOPPY,this);
	PCMCIAButton.AutoLoad(IDC_PCMCIA,this);
	UpdateData(FALSE);
	ShowPictureStatus();

	m_FileList.InsertColumn(FILENAME,"Name");
	m_FileList.InsertColumn(FILESIZE,"Size");
	m_FileList.InsertColumn(FILETYPE,"Type");
	m_FileList.InsertColumn(NEWFILE, "New");
	m_nSelected = 0;
	TotalBytes = 0;
	//m_FileList.SetCallbackMask(LVIS_SELECTED);//|LVIS_FOCUSED);
	GetFileList();
	PrepareFileList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataTransfer::OnFloppy() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_DestinationFolder = pDoc->m_FloppyDefault;
	UpdateData(FALSE);
}

void CDataTransfer::OnPcmcia() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_DestinationFolder = pDoc->m_PcmciaDefault ;
	UpdateData(FALSE);
}

void CDataTransfer::OnBrowseDestination() 
{
	// TODO: Add your control notification handler code here
	CString oldFolder = m_DestinationFolder;
	m_DestinationFolder = BrowseForFolder("Select Destination Folder for Data Files");
	if (m_DestinationFolder != "")
		UpdateData(FALSE);
	else
		m_DestinationFolder = oldFolder;
}


void CDataTransfer::OnArchiveFiles() 
{
	// TODO: Add your control notification handler code here
	PrepareFileList();
}

void CDataTransfer::OnDiagnostic() 
{
	// TODO: Add your control notification handler code here
	PrepareFileList();
}

void CDataTransfer::OnPictureFiles() 
{
	// TODO: Add your control notification handler code here
	ShowPictureStatus();
	PrepareFileList();
}

void CDataTransfer::OnRealTimeFiles() 
{
	// TODO: Add your control notification handler code here
	PrepareFileList();
}

void CDataTransfer::OnDibtojpb() 
{
	// TODO: Add your control notification handler code here
	
}

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

void CDataTransfer::OnJpg() 
{
	// TODO: Add your control notification handler code here
	PrepareFileList();
}

void CDataTransfer::OnDib() 
{
	// TODO: Add your control notification handler code here
	PrepareFileList();
}
/*
void CDataTransfer::OnItemclickFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
}
*/
// Sort the item in reverse alphabetical order.
int CALLBACK 
CDataTransfer::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM classObject)
{
   // lParamSort contains a pointer to the list view control.
   // The lParam of an item is just its index.
   //CListCtrl* pListCtrl = (CListCtrl*) lParamSort;
   //CString    strItem1 = pListCtrl->GetItemText(lParam1, 0);
   //CString    strItem2 = pListCtrl->GetItemText(lParam2, 0);
   //return strcmp(strItem2, strItem1);
	CDataTransfer * CDptr = (CDataTransfer *)classObject;
	//column = ;

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
	//m_ptrFileInfo
	return 1;
}

void CDataTransfer::DisplayFileInfo()
{
	char n[15];
	wsprintf(n,"%i",m_nSelected);
	m_NumSelected.SetWindowText(n);
	wsprintf(n,"%iKB",(TotalBytes + 999) / 1000);
	m_TotalBytes.SetWindowText(n);
	m_FileList.SetFocus();
}

void CDataTransfer::OnColumnclickFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	nColumn = pNMListView->iItem;
	m_FileList.SortItems(MyCompareProc, (LPARAM) this);
	*pResult = 0;
	*pResult = 0;
}

void CDataTransfer::OnItemchangedFilelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	m_PtrFileInfo[pNMListView->iItem].IsSelected = m_FileList.GetItemState( pNMListView->iItem, LVIS_SELECTED );
	
	/*
	BOOL AddSelection = (pNMListView->uNewState & LVIS_SELECTED ? TRUE : FALSE);
	*/
	/*
	if (pNMListView->uNewState & LVIS_SELECTED) 
	{
		m_nSelected++;
		TotalBytes += m_PtrFileInfo[pNMListView->iItem].FileSize;
	}
	else
	{
		m_nSelected--;
		TotalBytes -= m_PtrFileInfo[pNMListView->iItem].FileSize;
	}
	*/	
	DisplayFileInfo();
	*pResult = 0;
}
