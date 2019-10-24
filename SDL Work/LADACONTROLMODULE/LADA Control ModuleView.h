// LADA Control ModuleView.h : interface of the CLADAControlModuleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LADACONTROLMODULEVIEW_H__B5A7CFA1_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_LADACONTROLMODULEVIEW_H__B5A7CFA1_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLADAControlModuleDoc;

class CLADAControlModuleView : public CFormView
{
	friend class CLADAControlModuleDoc;
protected: // create from serialization only
	CLADAControlModuleView();
	DECLARE_DYNCREATE(CLADAControlModuleView)
	BOOL StartTimerThread();
public:

	DWORD t1;

	//{{AFX_DATA(CLADAControlModuleView)
	enum { IDD = IDD_LADACONTROLMODULE_FORM };
	CStatic	m_ConnStatus;
	CButton	m_Button4;
	CButton	m_Button3;
	CButton	m_Button2;
	CButton	m_Button1;
	CStatic	m_TimeWnd;
	CStatic	m_Connected;
	int		m_T1;
	int		m_T2;
	int		m_T3;
	DWORD	m_Delay;
	int		m_JTime;
	int		m_JTimeMax;
	int		m_KTime;
	int		m_KTimeMax;
	int		m_OTime;
	int		m_OTimeMax;
	int		m_RTime;
	//}}AFX_DATA

// Attributes
public:
	CBitmap *ConnectedBMP;
	CBitmap *NConnectedBMP;
	CLADAControlModuleDoc* GetDocument();
	HANDLE hTimerThread;
	
	// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLADAControlModuleView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLADAControlModuleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLADAControlModuleView)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnSetInputLocation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LADA Control ModuleView.cpp
inline CLADAControlModuleDoc* CLADAControlModuleView::GetDocument()
   { return (CLADAControlModuleDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LADACONTROLMODULEVIEW_H__B5A7CFA1_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
