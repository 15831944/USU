// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////
#include "GraphInfo.h"

#if !defined(AFX_LEFTVIEW_H__96016266_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
#define AFX_LEFTVIEW_H__96016266_63D3_11D4_98D7_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGraphFormDoc;

class CLeftView : public CView
{
protected: // create from serialization only
	CLeftView(/*GraphInfo &gInfo*/);
	DECLARE_DYNCREATE(CLeftView)
	
	CGraphFormDoc* pDoc;
	int nData;
	double (*gData)[5000];
	CPen *pens;
	COLORREF *colors;
	CBrush backgroundBrush;
	CPen penThickBlack;
	CPen penThinBlack;
	CPen penThinGray;
	int *nPoints;
	int *sPoint;
	
	int *StartTime;
	int *EndTime;
	double PixelLabelDistance;
// Attributes
public:
	//CGraphFormDoc* GetDocument();
	//GraphInfo *graphInfo;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
#ifndef _DEBUG  // debug version in LeftView.cpp
inline CGraphFormDoc* CLeftView::GetDocument()
   { return (CGraphFormDoc*)m_pDocument; }
#endif
*/

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__96016266_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
