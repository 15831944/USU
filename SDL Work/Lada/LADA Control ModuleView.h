// This is Version 1.0 PLEASE DOCUMENT CHANGES
// LADA Control ModuleView.h : interface of the CLADAControlModuleView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LADACONTROLMODULEVIEW_H__B5A7CFA1_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_LADACONTROLMODULEVIEW_H__B5A7CFA1_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLADAControlModuleDoc;
class WetupDialog;

typedef void (CALLBACK EXPORT* lpfnTimerCallback) (HWND, UINT, UINT, DWORD);

#include "CommOperations.h"
#include "List.h"
#include "InputRequest.h"

enum CR10ConnectionStatusType { Connected, NotConnected, TryingToConnect, NoState };

class CLADAControlModuleView : public CFormView
{
	friend class CLADAControlModuleDoc;
	friend void CALLBACK EXPORT ResetTimer(
		HWND hWnd,      // handle of CWnd that called SetTimer
		UINT nMsg,      // WM_TIMER
		UINT nIDEvent,   // timer identification
		DWORD dwTime    // system time
	);
	friend class CGraphDisplayView;
protected: // create from serialization only
	CLADAControlModuleView();
	DECLARE_DYNCREATE(CLADAControlModuleView)
public:
	BOOL ControlCR10(	CR10ControlType Lights = NoChange, 
						CR10ControlType Fans = NoChange,
						CR10ControlType Pump1 = NoChange,
						CR10ControlType Pump2 = NoChange	);
	/*
	void CALLBACK EXPORT ResetTimer(
		HWND hWnd,      // handle of CWnd that called SetTimer
		UINT nMsg,      // WM_TIMER
		UINT nIDEvent,   // timer identification
		DWORD dwTime    // system time
	);
	*/
	List<CInputRequest> TimerRequests;
	WetupDialog * wDialog;
	DWORD t1;

	//{{AFX_DATA(CLADAControlModuleView)
	enum { IDD = IDD_LADACONTROLMODULE_FORM };
	CStatic	m_ModeWindow;
	CStatic	m_ConnStatus;
	CStatic	m_TimeWnd;
	CStatic	m_Connected;
	//}}AFX_DATA

// Attributes
public:
	CBitmap *ConnectedBMP;
	CBitmap *NConnectedBMP;
	CBitmap *BigRedButtonBMP;
	CBitmap *WetupInProgressBMP;
	CLADAControlModuleDoc* GetDocument();
	
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
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void StartDataTimers();
	void SetCameraTimer(int whichTimer);
	BOOL GetFinalStorage(BOOL ISWETUP=FALSE);
	void ResumeTimers();
	void SetStrings();
	BOOL m_WetupCanceled;
	void OnCR10Control(UINT nID);
	void SetControlModeWindow(ControlModeType mode);
	void SetGraphTimer();
	void SetILTimer(int wIL, lpfnTimerCallback lpfnTimer, CTime &currentTime);
	void SetFinalStorageTimer(lpfnTimerCallback lpfnTimer, CTime &currentTime);
	void SetCommStatusWindow(CR10ConnectionStatusType ConnectionStatus);
	CLADAControlModuleDoc * pDoc;
	
	virtual ~CLADAControlModuleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CLADAControlModuleView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConnect();
	afx_msg void OnTakePicture();
	afx_msg void OnConnected();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
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
