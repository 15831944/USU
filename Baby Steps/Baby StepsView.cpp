// Baby StepsView.cpp : implementation of the CBabyStepsView class
//

#include "stdafx.h"
#include "Baby Steps.h"

#include "Baby StepsDoc.h"
#include "Baby StepsView.h"
#include "Square.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef getSquare
	#undef getSquare
#endif

#define getSquare(x,y) pDoc->squares[x + y * pDoc->nColumns]

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsView

IMPLEMENT_DYNCREATE(CBabyStepsView, CView)

BEGIN_MESSAGE_MAP(CBabyStepsView, CView)
	//{{AFX_MSG_MAP(CBabyStepsView)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_POPUP_OBSTACLE, OnPopupObstacle)
	ON_COMMAND(ID_POPUP_GOAL, OnPopupGoal)
	ON_COMMAND(ID_POPUP_START, OnPopupStart)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsView construction/destruction

CBabyStepsView::CBabyStepsView()
{
	// TODO: add construction code here
	pDoc = NULL;
	square_size = 0;
	m_margin = 20;
	penThinGray.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
	m_RedrawAll = true;
	m_leftButtonDown = false;
}

CBabyStepsView::~CBabyStepsView()
{
}

BOOL CBabyStepsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsView drawing

void CBabyStepsView::OnDraw(CDC* pDC)
{
	CBabyStepsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (square_size > 0)
	{
		if (m_RedrawAll)
		{
			CRect bounds(m_margin - 1, m_margin - 1, pDoc->nColumns * square_size + m_margin + 2, pDoc->nRows * square_size + m_margin + 2);

			pDC->Rectangle(bounds);

			void * ptrOldPen = pDC->SelectObject(penThinGray);
			
			CPoint p1(m_margin,m_margin);
			CPoint p2(m_margin,pDoc->nColumns * square_size + m_margin);

			for (int i = 0; i <= pDoc->nColumns; i++)
			{
				pDC->MoveTo(p1);
				pDC->LineTo(p2);
				p1.Offset(square_size,0);
				p2.Offset(square_size,0);
			}
			
			p1.x = m_margin;
			p1.y = m_margin;
			p2.x = pDoc->nColumns * square_size + m_margin;
			p2.y = m_margin;
			for ( i = 0; i <= pDoc->nRows; i++)
			{
				pDC->MoveTo(p1);
				pDC->LineTo(p2);
				p1.Offset(0,square_size);
				p2.Offset(0,square_size);
			}
			pDC->SelectObject(ptrOldPen);
			
			for (int x = 0; x < pDoc->nColumns; x++)
			{
				for (int y = 0; y < pDoc->nRows; y++)
				{
					DrawSquare(pDC,GetSquareRect(x,y),&getSquare(x,y));
				}
			}

		}
		else
		{
			Square * ptrSquare = &getSquare(m_InvalidSquare.x, m_InvalidSquare.y);
			DrawSquare(pDC, InvalidRect, ptrSquare);
		}
	}
}

void CBabyStepsView::DrawSection( CDC * pDC, CPoint poly[], int intensity )
{
	int red = (GetRValue(pDoc->hotColor) - GetRValue(pDoc->coldColor)) * intensity / 100 + GetRValue(pDoc->coldColor);
	int green = (GetGValue(pDoc->hotColor) - GetGValue(pDoc->coldColor)) * intensity / 100 + GetGValue(pDoc->coldColor);
	int blue = (GetBValue(pDoc->hotColor) - GetBValue(pDoc->coldColor)) * intensity / 100 + GetBValue(pDoc->coldColor);
	COLORREF color = RGB(red,green,blue);
	CPen pen;
	pen.CreatePen(PS_SOLID,0,color);
	void * oldPen = pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush( color );
	void * oldBrush = pDC->SelectObject( &brush );
	pDC->Polygon(poly,3);
	pDC->SelectObject( oldPen );
	pDC->SelectObject( oldBrush );
}

void CBabyStepsView::DrawSquare(CDC * pDC, CRect rect, Square * ptrSquare)
{
	switch (ptrSquare->type)
	{
	case Obstacle:
		{
			CBrush ObstacleBrush;
			ObstacleBrush.CreateSolidBrush(RGB(0,0,0));
			pDC->FillRect(rect,&ObstacleBrush);
			//pDC->Rectangle(bounds);
		} break;
	case Start:
		{
			CBrush StartBrush;
			StartBrush.CreateSolidBrush(RGB(255,0,255));
			//pDC->FillRect(rect,&StartBrush);
			void * ptrOldBrush = pDC->SelectObject(&StartBrush);
			pDC->Ellipse(&rect);
			pDC->SelectObject(ptrOldBrush);
			//pDC->Rectangle(bounds);
		} break;
	case Goal:
		{
			CBrush GoalBrush;
			GoalBrush.CreateSolidBrush(RGB(255,255,0));
			//pDC->FillRect(rect,&GoalBrush);
			void * ptrOldBrush = pDC->SelectObject(&GoalBrush);
			pDC->Ellipse(&rect);
			pDC->SelectObject(ptrOldBrush);
			//pDC->Rectangle(bounds);
		} break;
	case Normal:
		{

			if (ptrSquare->top != -1)
			{
				CPoint poly[3] = { rect.TopLeft(), CPoint(rect.right,rect.top), rect.CenterPoint() };
				DrawSection( pDC, poly, ptrSquare->top );
			}
			if (ptrSquare->right != -1)
			{
				CPoint poly[3] = { CPoint(rect.right,rect.top), rect.BottomRight(), rect.CenterPoint() };
				DrawSection( pDC, poly, ptrSquare->right );
			}
			if (ptrSquare->bottom != -1)
			{
				CPoint poly[3] = { rect.BottomRight(), CPoint(rect.left,rect.bottom), rect.CenterPoint() };
				DrawSection( pDC, poly, ptrSquare->bottom );
			}
			if (ptrSquare->left != -1)
			{
				CPoint poly[3] = { CPoint(rect.left,rect.bottom), rect.TopLeft(), rect.CenterPoint() };
				DrawSection( pDC, poly, ptrSquare->left );
			}
		} break;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsView diagnostics

#ifdef _DEBUG
void CBabyStepsView::AssertValid() const
{
	CView::AssertValid();
}

void CBabyStepsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBabyStepsDoc* CBabyStepsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBabyStepsDoc)));
	return (CBabyStepsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsView message handlers

void CBabyStepsView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RecalculateBoxSize(cx, cy);
}

void CBabyStepsView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	pDoc = GetDocument();
	this->SendMessage(WM_SIZE,0,0);
	
}

void CBabyStepsView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_leftButtonDown)
	{
		int r, c;
		if (CalculateSquare(point.x, point.y, r, c) && getSquare(c,r).type == Normal)
		{
			pDoc->SetSquareType(c,r,Obstacle);
		}
	}
	//CView::OnMouseMove(nFlags, point);
}

void CBabyStepsView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	int r, c;
	m_leftButtonDown = true;
	if (CalculateSquare(point.x, point.y, r, c))
	{
		if (getSquare(c,r).type == Normal)
		{
			pDoc->SetSquareType(c,r,Obstacle);
		}
	}

	//CView::OnLButtonDown(nFlags, point);
}

void CBabyStepsView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	int r, c;
	if (CalculateSquare(point.x, point.y, r, c))
	{
		m_ptrPopupSquare = &getSquare(c,r);
		m_popupSquare = CPoint(c,r);

		CMenu popupMenu;
		popupMenu.LoadMenu(IDR_POPUP_MENU);
		CMenu* subMenu = popupMenu.GetSubMenu(0);
		ClientToScreen(&point);

		subMenu->CheckMenuItem(ID_POPUP_START, (m_ptrPopupSquare->type == Start)?MF_CHECKED:MF_UNCHECKED);
		subMenu->CheckMenuItem(ID_POPUP_GOAL, (m_ptrPopupSquare->type == Goal)?MF_CHECKED:MF_UNCHECKED);
		subMenu->CheckMenuItem(ID_POPUP_OBSTACLE, (m_ptrPopupSquare->type == Obstacle)?MF_CHECKED:MF_UNCHECKED);
		
		subMenu->EnableMenuItem(ID_POPUP_START, (m_ptrPopupSquare->type == Start || pDoc->hasStart == false)?MF_ENABLED:MF_DISABLED|MF_GRAYED);
		subMenu->EnableMenuItem(ID_POPUP_GOAL, (m_ptrPopupSquare->type == Goal || pDoc->hasGoal == false)?MF_ENABLED:MF_DISABLED|MF_GRAYED);
		
		subMenu->TrackPopupMenu(0, point.x, point.y,
			AfxGetMainWnd(), NULL);
	}

	//CFrameWnd::OnRButtonUp(nFlags, point);

	//CView::OnRButtonDown(nFlags, point);
}

BOOL CBabyStepsView::CalculateSquare(int mouseX, int mouseY, int &row, int &column)
{
	if (square_size > 0)
	{
		column = (mouseX - m_margin) / square_size;
		row = (mouseY - m_margin) / square_size;
		if (row < 0 || column < 0 || row >= pDoc->nRows || column >= pDoc->nColumns)
		{
			return FALSE;
		}
		///square_size
		return TRUE;
	}
	else
		return FALSE;
}

void CBabyStepsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (lHint == 0 || pHint == NULL)
	{
		m_RedrawAll = true;
		Invalidate();
	}
	else
	{
		m_RedrawAll = false;
		CPoint * p = (CPoint *)pHint;
		m_InvalidSquare = *p;
		InvalidRect = GetSquareRect(p->x, p->y);
		InvalidateRect(&InvalidRect,FALSE);
	}
}

void CBabyStepsView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_leftButtonDown = false;
	CView::OnLButtonUp(nFlags, point);
}

void CBabyStepsView::OnPopupObstacle() 
{
	// TODO: Add your command handler code here
	if (m_ptrPopupSquare->type == Obstacle)
	{
		pDoc->SetSquareType(m_popupSquare.x,m_popupSquare.y, Normal);
	}
	else if (m_ptrPopupSquare->type == Normal)
	{
		pDoc->SetSquareType(m_popupSquare.x,m_popupSquare.y,Obstacle);
	}
}

void CBabyStepsView::OnPopupGoal() 
{
	// TODO: Add your command handler code here
	CBabyStepsDoc* pDoc = GetDocument();
	if (m_ptrPopupSquare->type == Goal)
	{
		pDoc->ResetGoal();
	}
	else if (!pDoc->hasGoal && (m_ptrPopupSquare->type == Normal || m_ptrPopupSquare->type == Obstacle))
	{
		pDoc->SetGoal(m_popupSquare.x, m_popupSquare.y);
	}
}

void CBabyStepsView::OnPopupStart() 
{
	// TODO: Add your command handler code here
	CBabyStepsDoc* pDoc = GetDocument();
	if (m_ptrPopupSquare->type == Start)
	{
		pDoc->ResetStart();
	}
	else if (!pDoc->hasStart && (m_ptrPopupSquare->type == Normal || m_ptrPopupSquare->type == Obstacle))
	{
		pDoc->SetStart(m_popupSquare.x,m_popupSquare.y);
	}
}

void CBabyStepsView::RecalculateBoxSize(int cx, int cy)
{
	if (pDoc)
	{
		//CRect rect;
		//GetClientRect(&rect);

		//CMainFrame * ptrFrame = (CMainFrame *) GetActiveWindow();
		int cw = cx - m_margin * 2;
		int ch = cy - m_margin * 2;

		int xsize = cw / pDoc->nColumns;
		int ysize = ch / pDoc->nRows;

		square_size = min(xsize,ysize);
		if (square_size < 0)
			square_size = 0;
		m_RedrawAll = true;
		Invalidate();
	}
}

void CBabyStepsView::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CView::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	m_RedrawAll = true;
	Invalidate();	
}

void CBabyStepsView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_RedrawAll = true;
	Invalidate();
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}



CRect CBabyStepsView::GetSquareRect(int x, int y)
{
	return CRect(m_margin + x * square_size + 1, m_margin + y * square_size + 1,
			     m_margin + (x + 1) * square_size, m_margin + (y + 1) * square_size);
}
