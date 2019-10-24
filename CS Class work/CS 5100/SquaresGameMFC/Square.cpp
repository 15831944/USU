// Square.cpp : implementation file
//

#include "stdafx.h"
#include "SquaresGame.h"
#include "Square.h"

#include "SquareEdge.h"
#include "SquareGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Square

Square::Square(int x, int y, SquareGame * pGame)
{
	static int index = 0;
	ptrGame = pGame;
	isFilled = false;
	owner = -1;
	AddSides(x,y);
	int top = y * SQUARE_SIZE + LINE_WIDTH + GAME_PANEL_HEIGHT;
	int left = x * SQUARE_SIZE + LINE_WIDTH;
	int bottom = top + SQUARE_SIZE - LINE_WIDTH + 1;
	int right = left + SQUARE_SIZE - LINE_WIDTH + 1;
	
	CRect rect(left,top,right,bottom);
	Create(NULL,WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_OWNERDRAW,rect,(CWnd *) pGame->getParent(), IDC_SQUARE1 + index++);
    
	//this->EnableWindow(FALSE);
	color = RGB(255,255,255);
    
}

void Square::AddSides(int x, int y)
{
	if (x == 0)
    {
        // create a left side
        Left = new SquareEdge(ptrGame);
        Left->CreateEdge(ptrGame);
		Left->MoveWindow(x * SQUARE_SIZE, y * SQUARE_SIZE + LINE_WIDTH + GAME_PANEL_HEIGHT, LINE_WIDTH + 1, SQUARE_SIZE - LINE_WIDTH + 1, TRUE);
    }
    else
    {
        Left = ptrGame->getSquare(x - 1, y)->getRightSide();
    }
    Left->AddSquare(this);
	
    if (y == 0)
    {
        // create a top side
        Top = new SquareEdge(ptrGame);
        Top->CreateEdge(ptrGame);
        Top->MoveWindow(x * SQUARE_SIZE + LINE_WIDTH, y * SQUARE_SIZE + GAME_PANEL_HEIGHT, SQUARE_SIZE - LINE_WIDTH + 1, LINE_WIDTH + 1);
    }
    else
    {
        Top = ptrGame->getSquare(x, y - 1)->getBottomSide();
    }
    Top->AddSquare(this);

    Right = new SquareEdge(ptrGame);
    Right->CreateEdge(ptrGame);
    Right->AddSquare(this);
    Right->MoveWindow((x+1) * SQUARE_SIZE, y * SQUARE_SIZE + LINE_WIDTH + GAME_PANEL_HEIGHT, LINE_WIDTH + 1, SQUARE_SIZE - LINE_WIDTH + 1);

    Bottom = new SquareEdge(ptrGame);
    Bottom->CreateEdge(ptrGame);
	Bottom->AddSquare(this);
    Bottom->MoveWindow(x * SQUARE_SIZE + LINE_WIDTH, (y+1) * SQUARE_SIZE + GAME_PANEL_HEIGHT, SQUARE_SIZE - LINE_WIDTH + 1, LINE_WIDTH + 1);
}

Square::~Square()
{
	if (Top)
	{
		if (Top->s2 && Top->s2 != this)
			Top->s2->Bottom = NULL;
		if (Top->s1 && Top->s1 != this)
			Top->s1->Bottom = NULL;
		delete Top;
		Top = NULL;
	}
	if (Bottom)
	{
		if (Bottom->s2 && Bottom->s2 != this)
			Bottom->s2->Top = NULL;
		if (Bottom->s1 && Bottom->s1 != this)
			Bottom->s1->Top = NULL;
		delete Bottom;
		Bottom = NULL;
	}
	if (Left)
	{
		if (Left->s2 && Left->s2 != this)
			Left->s2->Right = NULL;
		if (Left->s1 && Left->s1 != this)
			Left->s1->Right = NULL;
		delete Left;
		Left = NULL;
	}
	if (Right)
	{
		if (Right->s2 && Right->s2 != this)
			Right->s2->Left = NULL;
		if (Right->s1 && Right->s1 != this)
			Right->s1->Left = NULL;
		delete Right;
		Right = NULL;
	}
}


BEGIN_MESSAGE_MAP(Square, CButton)
	//{{AFX_MSG_MAP(Square)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Square message handlers

bool Square::check()
{
	if (getSidesFilled() == 4 && isFilled == false)
	{
		ptrGame->totalSquaresLeft--;
		isFilled = true;
		owner = ptrGame->currentPlayer;
		color = ptrGame->playerColor[ptrGame->currentPlayer];
		ptrGame->playerScore[ptrGame->currentPlayer]++;
		ptrGame->updateScoreWindow();
		Invalidate(TRUE);
		if (ptrGame->totalSquaresLeft == 0)
		{
			ptrGame->DoGameOver();
		}
		return true;
	}
	return false;
}

int Square::getSidesFilled()
{
	return Left->set + Right->set + Top->set + Bottom->set;
}

SquareEdge * Square::getEmptySide()
{
	if (Top->set == 0)
		return Top;
	else if (Left->set == 0)
		return Left;
	else if (Bottom->set == 0)
		return Bottom;
	else if (Right->set == 0)
		return Right;
	else
		return NULL;
	
}

bool Square::trySquare()
{
	if (Left->trySide())
	{
        return true;
	}
	if (Right->trySide())
	{
        return true;
	}
	if (Top->trySide())
	{
        return true;
	}
	if (Bottom->trySide())
	{
        return true;
	}
	return false;
}

void Square::Destroy()
{
	DestroyWindow();
}

void Square::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
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
	//CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void Square::Refresh()
{
	if (isFilled)
	{
		color = ptrGame->playerColor[owner];
	}

	Invalidate();
	if (Top->set)
	{
		Top->color = ptrGame->sideColor;
		Top->Invalidate();
	}
	
	if (Left->set)
	{
		Left->color = ptrGame->sideColor;
		Left->Invalidate();
	}
	if (Right->set)
	{
		Right->color = ptrGame->sideColor;
		Right->Invalidate();
	}
	if (Bottom->set)
	{
		Bottom->color = ptrGame->sideColor;
		Bottom->Invalidate();
	}
}
