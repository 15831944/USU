// EasyComputer.cpp: implementation of the EasyComputer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "squaresgame.h"
#include "EasyComputer.h"
#include "Square.h"
#include "SquareEdge.h"
#include "SquareGame.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EasyComputer::EasyComputer(int x, int y, SquareGame * pGame)
{
	xBox = x;
	yBox = y;
	ptrGame = pGame;
	asquares = new Square * [xBox * yBox];
	squaresLeft = xBox * yBox;
	for (int i = 0; i < xBox; i++)
    {
		for (int j = 0; j < yBox; j++)
		{
			asquares[i*yBox+j] = ptrGame->getSquare(i,j);
		}
    }
}

EasyComputer::~EasyComputer()
{
	delete [] asquares;	
}

void EasyComputer::MakeMove()
{
	while (squaresLeft > 0)
	{
		int squareIndex = rand() % squaresLeft;
		
		//System.out.println("squaresLeft="+squaresLeft+" squareIndex="+squareIndex+" sidesFilled="+asquares[squareIndex].getSidesFilled());
		
		if (asquares[squareIndex]->getSidesFilled() < 4)
		{
            if (asquares[squareIndex]->getTopSide()->set == 0)
            {
				asquares[squareIndex]->getTopSide()->OnClicked();
				return;
            }
            else if (asquares[squareIndex]->getBottomSide()->set == 0)
            {
				asquares[squareIndex]->getBottomSide()->OnClicked();
				return;
            }
            else if (asquares[squareIndex]->getLeftSide()->set == 0)
            {
				asquares[squareIndex]->getLeftSide()->OnClicked();
				return;
            }
            else if (asquares[squareIndex]->getRightSide()->set == 0)
            {
				asquares[squareIndex]->getRightSide()->OnClicked();
				return;
            }
            else
            {
				//System.out.println("Error: getSidesFilled() < 4 and all sides are set");
            }
		}
		else
		{
            squaresLeft--;
            Square * tempSquare;
            tempSquare = asquares[squareIndex];
            asquares[squareIndex] = asquares[squaresLeft];
            asquares[squaresLeft] = tempSquare;
		}
	}
	//System.out.println("no blank squares found");
}
   
