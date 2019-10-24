// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_GRAPHDISPLAYVIEW_H__B5A7CFCC_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_GRAPHDISPLAYVIEW_H__B5A7CFCC_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphDisplayView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphDisplayView view

class CLADAControlModuleDoc;

class CGraphDisplayView : public CView
{
	friend class CLADAControlModuleDoc;
protected:
	void PlotData(int whichGraphItem);
	int CreateValueLabels(BOOL drawLabels);
	CGraphDisplayView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGraphDisplayView)

	DWORD Hint;
	CLADAControlModuleDoc * pDoc;
	int whichWindow;
	CDC* pDC;
	
	int firstPoint;
	int lastPoint;
	int nBackPoints;

	int PixelLabelDistanceY;
	int PixelLabelDistanceX;

	CRect rect;     	
	bool IsDefinedMinMax;
	double minValue;
	double maxValue;
	int nDataPoints;

	double UnitsPerPixel;
	double BottomValue;
	double PixelsPerPoint;
	int PixelLeftPos;
	int PixelBottomPos;

public:

// Operations
public:
	int whichGraph;
	bool m_IsDataSelected;
	CToolTipCtrl m_ToolTip;
	void PlotDataPoints();
	BOOL DrawGraphForm();
	void GetMinMax();
	void PlaceHoroLabel(int PixelLabelPos);
	void PlaceVertLabel(int PixelLabelPos, BOOL draw, int &maxLength);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphDisplayView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphDisplayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGraphDisplayView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHDISPLAYVIEW_H__B5A7CFCC_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
