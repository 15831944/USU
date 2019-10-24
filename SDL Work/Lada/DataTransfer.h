// This is Version 1.0 PLEASE DOCUMENT CHANGES
//	This dialog is used to :
//		transfer certain files from the data directory to another locations,
//		convert Bitmaps to JPEGs.

#if !defined(AFX_DATATRANSFER_H__7849C0A0_9080_11D4_8303_87ACE5C34B86__INCLUDED_)
#define AFX_DATATRANSFER_H__7849C0A0_9080_11D4_8303_87ACE5C34B86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTransfer.h : header file
class CImageBuffer;
//

//fileTypes keeps track of what type a file is
enum fileTypes {PictureDIB, PictureJPG, FinalStorage, InputLocation, Diagnostic, History, Other};

//CFileInfo is used to store the information of a file
struct CFileInfo
{

	fileTypes fileType;	// Type of a file
	BOOL IsNewFile;		// If the file is new
	DWORD FileSize;		// The size of a file
	BOOL IsSelected;	// If the file is selected for transfer
};	

/////////////////////////////////////////////////////////////////////////////
// CDataTransfer dialog
class CLADAControlModuleDoc;

//#include "CustomBitmapButton.h"

class CDataTransfer : public CDialog
{
// Construction
public:
	void ResetStrings();
	void SetStrings();												// Sets the text in the dialog to the current language
	CDataTransfer(CLADAControlModuleDoc *doc, CWnd* pParent = NULL);// standard constructor
	~CDataTransfer();												// standard destructor
	void GetFileList();												// This sets the list of files and information in the list box
	void PrepareFileList();											// prepares the file list
	void ShowPictureStatus();										// Enables the Dib and Jpg Button
	void DisplayFileInfo();											// Tells how many files are selected and the total size
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM column);

	int nColumn;
	DWORD TotalBytes;				//Total Bytes ready to be copied
	int m_nFiles;					//Number of files that can be copied
	CBitmapButton FloppyButton;		//The Floppy Drive Button
	CBitmapButton PCMCIAButton;		//The Card Icon
	int m_nSelected;				//The number of files selected for copy
	BOOL m_NewOnly;					//If only new files will be transfered
	CLADAControlModuleDoc * pDoc;	//The Current document
	CFileInfo * m_PtrFileInfo;		//This contains the information of files
	CListBox *FileListWindow;		//Contains the ListBox
	
// Dialog Data
	//{{AFX_DATA(CDataTransfer)
	enum { IDD = IDD_DATA_TRANSFER };
	CButton	m_Jpg;					//The Jpg Check Box control
	CButton	m_Dib;					//The Dib Check Box control
	CStatic	m_TotalBytes;			//The Text for Total Bytes control
	CListCtrl	m_FileList;			//The List Control control
	CButton	m_Other;				//The Other Button control
	CStatic	m_NumSelected;			//The Text for Total Files selected control
	CString	m_DestinationFolder;	//The Edit Box String for the Destination Folder
	CString	m_SourceFolder;			//The String for the Source Folder
	BOOL	m_ArchiveFiles;			//The BOOL if Archived Files are selected
	BOOL	m_PictureFiles;			//The BOOL if Picture Files are selected
	BOOL	m_RealTime;				//The BOOL if Real Time Files are selected
	BOOL	m_JPG;					//The BOOL if Jpg Files are selected
	BOOL	m_DIB;					//The BOOL if Dib Files are selected
	BOOL	m_HistoryFiles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTransfer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataTransfer)
	afx_msg void OnSetDefault();	// Sets the default for the Floppy Icon and the PCMCIA Card
	virtual void OnOK();			// Sets the default for the Floppy Icon and the PCMCIA Card
	afx_msg void OnNewFilesOnly();	// This selects toggles between New Files Only and All Files
	afx_msg void OnAllFiles();		// This selects toggles between New Files Only and All Files
	virtual BOOL OnInitDialog();	// This does all the initialization work after the dialog is loaded
	afx_msg void OnBrowseDestination();// Selects a new folder from a tree menu for the destination
	afx_msg void OnFloppy();		// When the Floppy Icon is pressed it sets the folder as what is set in the floppy
	afx_msg void OnPcmcia();		// When the Card Icon is pressed it sets the folder as what is set in the floppy
	afx_msg void OnArchiveFiles();	// Selects the Archive Files
	afx_msg void OnPictureFiles();	// Selects the Picture Files
	afx_msg void OnRealTimeFiles();	// Selects the RealTime Files
	afx_msg void OnJpg();			// Selects Jpg Files
	afx_msg void OnDib();			// Selects Dib Files
	afx_msg void OnColumnclickFilelist(NMHDR* pNMHDR, LRESULT* pResult);// Sorts by a column when you click on it
	afx_msg void OnItemchangedFilelist(NMHDR* pNMHDR, LRESULT* pResult);// Selects a file when you click on it
	afx_msg void OnHistoryFiles();
	afx_msg void OnDblclkFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATRANSFER_H__7849C0A0_9080_11D4_8303_87ACE5C34B86__INCLUDED_)
