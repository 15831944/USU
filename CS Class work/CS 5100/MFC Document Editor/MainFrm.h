// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__B3690A65_EB37_4CB4_9836_CAAC5243D107__INCLUDED_)
#define AFX_MAINFRM_H__B3690A65_EB37_4CB4_9836_CAAC5243D107__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	friend class CChildFrame;

	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:
	static int CALLBACK EnumFontFamProc(
		ENUMLOGFONTEX *lpelfe,    // logical-font data
		NEWTEXTMETRICEX *lpntme,  // physical-font data
		DWORD FontType,           // type of font
		LPARAM lParam             // application-defined data
	);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	CDialogBar m_DialogBar;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileCloseWindows();
	//}}AFX_MSG
	afx_msg void OnSelchangeFontCombo();
	afx_msg void OnSelchangeSizeCombo();
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__B3690A65_EB37_4CB4_9836_CAAC5243D107__INCLUDED_)
