// cameradialogDlg.h : header file
//

#if !defined(AFX_CAMERADIALOGDLG_H__A818942C_73A2_11D4_98DA_00A076801ACD__INCLUDED_)
#define AFX_CAMERADIALOGDLG_H__A818942C_73A2_11D4_98DA_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCameradialogDlg dialog
#include "Array.h"
#include <fstream.h>
#include "FileData.h"
#include "twain.h"
#include <VFW.H>
#include <afxwin.h>
#include <windows.h>
//#include <sti.h>

typedef HWND (VFWAPI * lpFunc1)(LPCSTR, DWORD, int, int, int, int, HWND, int);

class CCameradialogDlg : public CDialog
{
// Construction
public:
	pTW_IDENTITY pOrigin;			// Still trying to figure out what this one does
	pTW_IDENTITY pDest;				// Still trying to figure out what this one does
	TW_MEMREF pData;				// Still trying to figure out what this one does
	TW_UINT16 rc;					// Still trying to figure out what this one does
	DSMENTRYPROC lpDSM_Entry;		// Still trying to figure out what this one does
	HINSTANCE hDSMDLL;				// Still trying to figure out what this one does
	CPalette* ppal;					// The palette pointer that is used to display bitmaps
	CBitmap* Bitmap;				// The place to store bitmaps
	void SavePicture();				// Saves the last picture taken to a dib file
	void SetStrings();				// Sets the text to the current language
	void LoadFile(Array<CFileData>&);// Loads all the last pictures taken
	void LoadPicture(int);			// Loads a picture
	BOOL TakePicture(int);			// Takes a picture	
	void SavePictureHistory();		// Saves the list of pictures taken
	int nID;						// Used to Create window
	DSMENTRYPROC pDSM_Entry;		// Still trying to figure out what this one does
	HANDLE hDSMLib;					// Still trying to figure out what this one does
	char szSMDIR;					// Still trying to figure out what this one does
	OFSTRUCT of;					// Still trying to figure out what this one does				
	void ChangeInterval();			// Changes the interval of picture taking
	CTimeSpan m_Interval;			// The current picture taking interval
	void TakePictureNow();			// Takes a picture without bringing up the dialog
	Array<CFileData> m_File;		// The array of when pictures were taken
	CCameradialogDlg(CWnd* pParent = NULL);	// standard constructor
	~CCameradialogDlg();			// standard destructor
	lpFunc1 CreateCaptureWindow;	// The structure that creates a capture window
// Dialog Data
	//{{AFX_DATA(CCameradialogDlg)
	enum { IDD = IDD_CAMERADIALOG_DIALOG };
	CStatic	m_picture;				// The control that holds the last picture taken
	CStatic	m_rpicture;				// The control that holds the last picture loaded
	CEdit	m_FreqNumCon;			// The control that holds the frequency number
	CButton	m_Save;					// The control for the save button
	CButton	m_Clear;				// The control for the clear button
	CSpinButtonCtrl	m_Spin1;		// The control for the up down arrows for frequency number
	CComboBox	m_Resolution;		// The control for the resolution button
	CComboBox	m_Frequency;		// The control for the frequency unit (hours, days..)
	CListCtrl	m_FileBox;			// The control for the filebox that displays when pictures were taken
	CWnd *Black;					// The window that stores the picture
	HWND VCWin1;					// The handle to the window that stores the picture
	int nRecords;					// The number of photo times stored
	int Camera;						// Which Camera
	UINT	m_FreqNumber;			// The Frequency Number
	CString	m_FreqString;			// The unit of Frequency
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameradialogDlg)
	public:
	virtual BOOL DestroyWindow();	// Destroys the Window
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCameradialogDlg)
	virtual BOOL OnInitDialog();	//Initialized the Dialog
	afx_msg void OnPaint();			// Paints
	afx_msg HCURSOR OnQueryDragIcon();// When you drag the Icon
	afx_msg void OnDblclkFilebox(NMHDR* pNMHDR, LRESULT* pResult);// When you doubleclick on one of the previous picture descriptions
	afx_msg void OnCamera1();		// When you click on the Camera 1 button
	afx_msg void OnCamera2();		// When you click on the Camera 2 button
	afx_msg void OnSave();			// When you click on the Save button
	afx_msg void OnClear();			// When you click on the Clear button
	afx_msg void OnChangeTvalue();	// When you change the Frequency by using the up down arrow
	afx_msg void OnSelchangeFrequency();// When you change the Frequency select a different unit
	afx_msg void OnEditupdateFrequency();// When you change the Frequency enter a different number
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERADIALOGDLG_H__A818942C_73A2_11D4_98DA_00A076801ACD__INCLUDED_)
