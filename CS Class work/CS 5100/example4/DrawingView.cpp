// DrawingView.cpp : implementation of the CDrawingView class
//

#include "stdafx.h"
#include "Drawing.h"

#include "DrawingView.h"
#include "DrawingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawingView

IMPLEMENT_DYNCREATE(CDrawingView, CView)

BEGIN_MESSAGE_MAP(CDrawingView, CView)
	//{{AFX_MSG_MAP(CDrawingView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawingView construction/destruction

CDrawingView::CDrawingView()
{
	drawIt = false;
}

CDrawingView::~CDrawingView()
{
}

BOOL CDrawingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawingView drawing

void CDrawingView::OnDraw(CDC* pDC)
{
	if (!drawIt) return;
	CPen pen(PS_SOLID, 3, RGB(0, 0, 255));
	CPen * oldPen = pDC->SelectObject(&pen);
	pDC->MoveTo(20, 20);
	pDC->LineTo(120, 120);
	CBrush redBrush(5, RGB(255, 0, 0));
	CBrush * oldBrush = pDC->SelectObject(&redBrush);
	pDC->Rectangle(120, 120, 220, 170);
	CBrush greenBrush(RGB(0, 255, 0));
	pDC->SelectObject(&greenBrush);
	pDC->Pie(CRect(250, 250, 350, 350), CPoint(320, 270), CPoint(250, 250));
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawingView diagnostics

#ifdef _DEBUG
void CDrawingView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawingView message handlers

void CDrawingView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	drawIt = !drawIt;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);

}

int CDrawingView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	myButton.Create("myButton", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON, 	
		CRect(300, 100, 400, 140), this, IDC_MYBUTTON);
	return 0;
}
