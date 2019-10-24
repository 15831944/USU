#if !defined(AFX_CHECKOUTDLG1_H__47FA2860_04EB_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_CHECKOUTDLG1_H__47FA2860_04EB_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CheckOutDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCheckOutDlg dialog
typedef int (* stepFunctionType)(void);
class CLADAControlModuleDoc;
class CCheckout;
enum CheckOutType {CheckOut,Tensiometer};

#define MAX_STEPS	18
class CCheckOutDlg : public CDialog
{
// Construction
public:
	BOOL m_HasStepTitle;
	int m_BaseAddressStepTitle;
	CString PictureDirectory;
	void LoadPicture();
	UINT m_BaseAddressStepDescription;
	UINT m_BaseAddressStepString;
	static CheckOutType m_DlgType;
	void RestoreStrings();
	CString fillerRussian;
	CString fillerEnglish;
	CTime StartTime;
	CString fillerString;
	static CString CompletedFileName;
	CPalette * m_Palette;
	CBitmap * m_Bitmap;
	static BOOL m_IsAutomatic;
	static CLADAControlModuleDoc * pDoc;
	static CCheckout * print;
	static int Step1();
	static int Step2();
	static int Step3();
	static int Step4();
	static int Step5();
	static int Step6();
	static int Step7();
	static int Step8();
	static int Step9();
	static int Step10();
	static int Step11();
	static int Step12();
	static int Step13();
	static int Step14();
	static int Step15();
	static int Step16();
	static int Step17();
	static int Step18();
	int m_wPage;
	void SetStepText();
	void SetStrings();

	int m_TotalSteps;
	void PreparePage();
	int m_curStep;
	CCheckOutDlg(CheckOutType, CLADAControlModuleDoc * pDoc, CWnd* pParent = NULL);   // standard constructor
	virtual ~CCheckOutDlg();
	void OnCheckBox(UINT nID);
	stepFunctionType m_Function[MAX_STEPS];
	CString PictureName[MAX_STEPS];

// Dialog Data
	//{{AFX_DATA(CCheckOutDlg)
	enum { IDD = IDD_CHECK_OUT };
	CStatic	m_CPicture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckOutDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCheckOutDlg)
	afx_msg void OnNext();
	afx_msg void OnBack();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKOUTDLG1_H__47FA2860_04EB_11D5_B690_0080AD8FBDCC__INCLUDED_)
