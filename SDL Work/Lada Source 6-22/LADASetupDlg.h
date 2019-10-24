// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LADASetupDlg.h : header file
//
#include "Stepinfo.h"

#if !defined(AFX_LADASETUPDLG_H__EA80EA26_8326_11D4_A864_0000E880BB29__INCLUDED_)
#define AFX_LADASETUPDLG_H__EA80EA26_8326_11D4_A864_0000E880BB29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "fstream.h"
#include "Camera.h"

enum CheckOutType {Setup,CheckOut,Tensiometer};

/////////////////////////////////////////////////////////////////////////////
// CLADASetupDlg dialog

class CLADAControlModuleDoc;
class CCheckout;

class CLADASetupDlg : public CDialog
{
// Construction
public:
	
	CBitmapButton CameraTestButton;
	void OnButton1();
	double Old[2];
	CCheckout * print;
	int * m_StepsPerPage;
	BOOL CheckTrue;
	void ResetStrings();
	void OnCheck(UINT nID);
	bool m_IsAutomatic;
	CPalette* ppal;					// The pointer to the pallete that is used to load a bitmap
	void SetStrings();				// Sets the text to the current language
	ofstream fout;					// Outputs information from checkout to a file
	void DoSomething();				// Does different tasks between checks on Checkout
	CLADAControlModuleDoc * pDoc;	// Pointer to the current document
	int m_numsteps;					// The number of steps used
	CheckOutType Type;				// If this is Setup else Checkout
	int checknumber;				// The last number checked
	void CheckCheck(int);			// Called after a number is checked
	void Reset(int);				// Called when Next-> or <-Back is pressed
	Stepinfo *m_step;				// The pointer to the information on the steps
	int m_stepnumber;				// The current step number
	CBitmap* m_Bitmap;				// The Pointer to the bitmap being used

	
	CLADASetupDlg(CheckOutType type=Setup,CLADAControlModuleDoc* op=NULL,CWnd* pParent = NULL);	// standard constructor
	~CLADASetupDlg();
// Dialog Data
	//{{AFX_DATA(CLADASetupDlg)
	enum { IDD = IDD_LADASETUP_DIALOG };
	CStatic	m_CPicture;	// The control for the picture
	CButton	m_CText;	// The control for the frame that displays the current substep and contains info on it
	CButton	m_CNext;	// Next-> Button control
	CButton	m_CBack;	// <-Back Button control
	CString	m_VStep;	// Step value
	CString	m_VTitle;	// Title value
	CString	m_VText;	// text value
	CString	m_VPicture;	// Picture value
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADASetupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CLADASetupDlg)
	virtual BOOL OnInitDialog();		// Initialization
	afx_msg void OnDestroy();			// ???????
	afx_msg void OnPaint();				// Paints Dialog
	afx_msg HCURSOR OnQueryDragIcon();	// When you drag the minimized window
	afx_msg void OnNext();				// When Next-> is pressed
	afx_msg void OnBack();				// When <-Back is pressed
	afx_msg void OnTestCamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADASETUPDLG_H__EA80EA26_8326_11D4_A864_0000E880BB29__INCLUDED_)
