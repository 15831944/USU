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

#include <VFW.H>
#include <afxwin.h>
#include <windows.h>

typedef HWND (VFWAPI * lpFunc1)(LPCSTR, DWORD, int, int, int, int, HWND, int);

class CCameradialogDlg : public CDialog
{
// Construction
public:
	bool firstpicture;
	int nID;
	HINSTANCE hLibrary;
	CString* Path;
	void ChangeInterval();
	CTimeSpan m_Interval;
	void TakePictureNow();
	Array<CFileData> m_File;
	CCameradialogDlg(CWnd* pParent = NULL);	// standard constructor
	~CCameradialogDlg();
	lpFunc1 CreateCaptureWindow;
// Dialog Data
	//{{AFX_DATA(CCameradialogDlg)
	enum { IDD = IDD_CAMERADIALOG_DIALOG };
	CEdit	m_FreqNumCon;
	CButton	m_Save;
	CButton	m_Clear;
	CSpinButtonCtrl	m_Spin1;
	CComboBox	m_Resolution;
	CComboBox	m_Frequency;
	CListCtrl	m_FileBox;
//	CTime	m_Date;
	CWnd *Black;
	HWND VCWin1;
	int nRecords;
	int Camera;
	UINT	m_FreqNumber;
	CString	m_FreqString;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameradialogDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCameradialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkFilebox(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCamera1();
	afx_msg void OnCamera2();
	afx_msg void OnSave();
	afx_msg void OnClear();
	afx_msg void LoadFile(Array<CFileData>&);
	afx_msg void Clear();
	afx_msg void TakePicture();
	afx_msg void LoadPicture(int);
	afx_msg void Save();
	afx_msg void OnChangeTvalue();
	afx_msg void OnSelchangeFrequency();
	afx_msg void OnEditupdateFrequency();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERADIALOGDLG_H__A818942C_73A2_11D4_98DA_00A076801ACD__INCLUDED_)
