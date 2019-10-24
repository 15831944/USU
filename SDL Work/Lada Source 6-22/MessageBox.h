// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_MESSAGEBOX_H__5CBBD1D1_BA52_11D4_98F0_00A076801ACD__INCLUDED_)
#define AFX_MESSAGEBOX_H__5CBBD1D1_BA52_11D4_98F0_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMessageBox dialog

class CMessageBox : public CDialog
{
// Construction
public:
	int defButtonNum;
	BOOL m_IsModal;
	UINT m_DefaultButton;
	BOOL Create(UINT nID, CWnd * pWnd = NULL)
        { return CDialog::Create(nID,pWnd);}
	DWORD m_Duration;
	CMessageBox(UINT MessageID, UINT MessageTitleID, DWORD DialogID, UINT iconID, UINT defaultButton, DWORD Duration = INFINITE, BOOL IsModal = TRUE, CWnd *pParent = NULL);
	CMessageBox(CString Text, CString Title = "", DWORD = 0, UINT iconID = 0, UINT defaultButton = 0, DWORD Duration = INFINITE, BOOL IsModal = TRUE, CWnd* pParent = NULL);   // standard constructor
	void DrawMessageBox();
	UINT m_MessageTitleID;
	UINT m_MessageID;
	CStatic textBox;
	int m_MBType;
	char * m_IconID;
	bool IsIcon;
	static void SetMessageFont(CFont * pFont);
	CString m_Title;
	
	CString m_Text;
	DWORD m_DlgID;
	void InitializeFontInfo();
	static int	charWidth[256];
	static bool InfoInitialized;
	static int	screenWidth;
	static int  charHeight;
	static CFont * ptrFont;
	static int buttonWidths[10][2];

// Dialog Data
	//{{AFX_DATA(CMessageBox)
	
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	afx_msg void OnButton(UINT nID);
	// Generated message map functions
	//{{AFX_MSG(CMessageBox)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MESSAGEBOX_H__5CBBD1D1_BA52_11D4_98F0_00A076801ACD__INCLUDED_)
