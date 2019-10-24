// DrawingView.h : interface of the CDrawingView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINGVIEW_H__D5A17BB9_064F_11D4_949F_000086520C5B__INCLUDED_)
#define AFX_DRAWINGVIEW_H__D5A17BB9_064F_11D4_949F_000086520C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MyButton.h"
class CDrawingView : public CView
{
protected: // create from serialization only
	CDrawingView();
	DECLARE_DYNCREATE(CDrawingView)

// Attributes
public:
//	CDrawingDoc* GetDocument();
	MyButton myButton;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawingView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	boolean drawIt;
// Implementation
public:
	virtual ~CDrawingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawingView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawingView.cpp
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWINGVIEW_H__D5A17BB9_064F_11D4_949F_000086520C5B__INCLUDED_)
