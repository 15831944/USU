// Baby StepsView.h : interface of the CBabyStepsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BABYSTEPSVIEW_H__7A6BE5C9_3E7F_4465_AFC5_AEB5D7292606__INCLUDED_)
#define AFX_BABYSTEPSVIEW_H__7A6BE5C9_3E7F_4465_AFC5_AEB5D7292606__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBabyStepsView : public CView
{
protected: // create from serialization only
	CBabyStepsView();
	DECLARE_DYNCREATE(CBabyStepsView)

// Attributes
public:
	CBabyStepsDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBabyStepsView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawSquare(CDC * pDC, CRect rect, Square *);
	void RecalculateBoxSize(int cx, int cy);

	CPoint m_InvalidSquare;
	CRect InvalidRect;
	BOOL CalculateSquare(int mouseX, int mouseY, int &row, int &column);
	int m_margin;
	virtual ~CBabyStepsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void DrawSection( CDC * pDC, CPoint poly[], int intensity );
	CRect GetSquareRect(int x, int y);
	Square * m_ptrPopupSquare;
	CPoint m_popupSquare;
	bool m_leftButtonDown;
	bool m_RedrawAll;
	CPen penThinGray;
	int square_size;
	CBabyStepsDoc * pDoc;
	//{{AFX_MSG(CBabyStepsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPopupObstacle();
	afx_msg void OnPopupGoal();
	afx_msg void OnPopupStart();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Baby StepsView.cpp
inline CBabyStepsDoc* CBabyStepsView::GetDocument()
   { return (CBabyStepsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BABYSTEPSVIEW_H__7A6BE5C9_3E7F_4465_AFC5_AEB5D7292606__INCLUDED_)
