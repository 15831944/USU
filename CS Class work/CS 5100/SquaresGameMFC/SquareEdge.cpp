// SquareEdge.cpp : implementation file
//

#include "stdafx.h"
#include "SquaresGame.h"
#include "SquareEdge.h"
#include "Square.h"
#include "SquareGame.h"
#include "ComputerPlayer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CSquaresGameApp theApp;

/////////////////////////////////////////////////////////////////////////////
// SquareEdge

SquareEdge::SquareEdge(SquareGame * pGame)
{
	ptrGame = pGame;
	set = 0;
	s1 = NULL;
	s2 = NULL;
	color = RGB(255,255,255);
	//setBorderPainted(false);
	//this.setCursor(java.awt.Cursor.getPredefinedCursor(HAND_CURSOR));
}

SquareEdge::~SquareEdge()
{
}


BEGIN_MESSAGE_MAP(SquareEdge, CButton)
	//{{AFX_MSG_MAP(SquareEdge)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SquareEdge message handlers

void SquareEdge::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	UINT uStyle = DFCS_BUTTONCHECK;//DFCS_BUTTONPUSH;

   // This code only works with buttons.
   ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

   // If drawing selected, add the pushed style to DrawFrameControl.
   //if (lpDrawItemStruct->itemState & ODS_SELECTED)
   //   uStyle |= DFCS_PUSHED;

   // Draw the button frame.
   //::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
   //   DFC_BUTTON, uStyle);
   
	HDC hDC = lpDrawItemStruct->hDC;
	HBRUSH brush = CreateSolidBrush(color);	
	HBRUSH hOldBrush = (HBRUSH) SelectObject(hDC, brush);
	Rectangle(
		lpDrawItemStruct->hDC,         // handle to DC
		lpDrawItemStruct->rcItem.left,   // x-coord of upper-left corner of rectangle
		lpDrawItemStruct->rcItem.top,    // y-coord of upper-left corner of rectangle
		lpDrawItemStruct->rcItem.right,  // x-coord of lower-right corner of rectangle
		lpDrawItemStruct->rcItem.bottom  // y-coord of lower-right corner of rectangle
	);
	SelectObject(hDC,hOldBrush);
   // Get the button's text.
   /*
   CString strText;
   GetWindowText(strText);

   // Draw the button text using the text color red.
   COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
   ::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
      &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
   ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
	*/
}

bool SquareEdge::trySide()
{
	if (set == 0)
	{
		if (s1->getSidesFilled() < 2)
		{ 
			if (s2 != NULL)
			{ 
                if (s2->getSidesFilled() < 2)
                {
					OnClicked();
					return true;
                }
                else
					return false;
			}
			else
			{
                OnClicked();
                return true;
			}
		}
		else
			return false;
	}
	else
		return false;
	
}

void SquareEdge::AddSquare(Square * s)
{
	if (s1 == NULL)
    {
        s1 = s;
    }
    else if (s2 == NULL)
    {
        s2 = s;
    }
}

void SquareEdge::CreateEdge(SquareGame *pGame)
{
	static int index = 0;
	Create(NULL,WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_OWNERDRAW,CRect(0,0,0,0),(CWnd *) pGame->getParent(), IDC_SQUARE1 + index++);
	//BS_PUSHBUTTON
	

}

void SquareEdge::notifySquares()
{
	bool squareCompleted = false;
	squareCompleted = s1->check();
	if (s2 != NULL)
	{
		squareCompleted = s2->check() || squareCompleted;
	}

	bool computerTurn = false;
	
	if (squareCompleted == false)
		// if the last move did not result in a square
		// being completly filled, then it is someone else's turn.
	{
		ptrGame->PlayerEndTurn(computerTurn);
	}
	else if (ptrGame->gameType != 1 && ptrGame->currentPlayer != 0)
	{
		// computer's turn to make a move...
		computerTurn = true;
	}

	if (computerTurn)
	{
		ptrGame->computer->MakeMove();   
	}
}
    

void SquareEdge::OnClicked() 
{
	// TODO: Add your control notification handler code here
	this->EnableWindow(FALSE);
	set = 1;
	color = ptrGame->sideColor;
	notifySquares();
	Invalidate();
}



void SquareEdge::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCursor(theApp.LoadCursor(IDC_HAND_CURSOR));//IDC_HAND));
	//CWnd * something;	
	//CButton::OnMouseMove(nFlags, point);
}

BOOL SquareEdge::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	HCURSOR myCursor = AfxGetApp()->LoadCursor( IDC_HAND_CURSOR );
	const HCURSOR hcurSave = ::SetCursor( myCursor );
	
	//MessageBeep(0);
	// ...perform lengthy op­er­ation here...
	// Restore old cursor:
	//SetCursor( hcurSave );
	return FALSE;
	//return CButton::OnSetCursor(pWnd, nHitTest, message);
}
