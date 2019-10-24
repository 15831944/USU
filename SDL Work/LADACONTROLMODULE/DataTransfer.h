#if !defined(AFX_DATATRANSFER_H__7849C0A0_9080_11D4_8303_87ACE5C34B86__INCLUDED_)
#define AFX_DATATRANSFER_H__7849C0A0_9080_11D4_8303_87ACE5C34B86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataTransfer.h : header file
//
enum fileTypes {PictureDIB, PictureJPG, FinalStorage, InputLocation, Diagnostic, Other};

struct CFileInfo
{
	//char cFileName[MAX_PATH];
	//DWORD attributes;
	fileTypes fileType;
	BOOL IsNewFile;
	DWORD FileSize;
	BOOL IsSelected;
};	

/////////////////////////////////////////////////////////////////////////////
// CDataTransfer dialog
class CLADAControlModuleDoc;

//#include "CustomBitmapButton.h"

class CDataTransfer : public CDialog
{
// Construction
public:
	CDataTransfer(CLADAControlModuleDoc *doc, CWnd* pParent = NULL); // standard constructor
	~CDataTransfer();
	void GetFileList();
	void PrepareFileList();
	void ShowPictureStatus();
	void DisplayFileInfo();
	static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM column);

	int nColumn;
	DWORD TotalBytes;
	int m_nFiles;
	CBitmapButton FloppyButton;
	CBitmapButton PCMCIAButton;
	int m_nSelected;
	BOOL m_NewOnly;
	CLADAControlModuleDoc * pDoc;
	CFileInfo * m_PtrFileInfo;
	CListBox *FileListWindow;
	
// Dialog Data
	//{{AFX_DATA(CDataTransfer)
	enum { IDD = IDD_DATA_TRANSFER };
	CButton	m_Jpg;
	CButton	m_Dib;
	CStatic	m_TotalBytes;
	CListCtrl	m_FileList;
	CButton	m_Other;
	CStatic	m_NumSelected;
	CString	m_DestinationFolder;
	CString	m_SourceFolder;
	BOOL	m_ArchiveFiles;
	BOOL	m_PictureFiles;
	BOOL	m_RealTime;
	BOOL	m_Diagnostic;
	BOOL	m_JPG;
	BOOL	m_DIB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataTransfer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataTransfer)
	afx_msg void OnSetDefault();
	virtual void OnOK();
	afx_msg void OnNewFilesOnly();
	afx_msg void OnAllFiles();
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseDestination();
	afx_msg void OnFloppy();
	afx_msg void OnPcmcia();
	afx_msg void OnArchiveFiles();
	afx_msg void OnDiagnostic();
	afx_msg void OnPictureFiles();
	afx_msg void OnRealTimeFiles();
	afx_msg void OnDibtojpb();
	afx_msg void OnJpg();
	afx_msg void OnDib();
	afx_msg void OnColumnclickFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedFilelist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATATRANSFER_H__7849C0A0_9080_11D4_8303_87ACE5C34B86__INCLUDED_)
