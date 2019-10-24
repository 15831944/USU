// HardComputer.cpp: implementation of the HardComputer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "squaresgame.h"
#include "HardComputer.h"
#include "SquareGame.h"
#include "Square.h"
#include "SquareEdge.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HardComputer::HardComputer(int x, int y, SquareGame * pGame)
{
	xBox = x;
	yBox = y;
	ptrGame = pGame;
	aSquaresLeft = xBox * yBox;
	eSquaresLeft = xBox * yBox;
	aSquares = new Square * [xBox * yBox];
	eSquares = new Square * [xBox * yBox];
	
	for (int i = 0; i < xBox; i++)
	{
		for (int j = 0; j < yBox; j++)
		{
			aSquares[i * yBox + j] = eSquares[i * yBox + j] = ptrGame->getSquare(i,j);
		}
	}
}

HardComputer::~HardComputer()
{
	delete [] aSquares;
	delete [] eSquares;
}


void HardComputer::MakeMove()
{
	// 'available' squares are those squares which are not completely filled in
	// 'empty' squares are those which have fewer than two sides filled
	
	// first, look for a square which has 3 sides filled in.
	for (int i = aSquaresLeft - 1; i >= 0; i--)
	{
		if (aSquares[i]->getSidesFilled()== 3)
		{
			aSquares[i]->getEmptySide()->OnClicked();
			return;
		}
		else if (aSquares[i]->getSidesFilled()==4)
		{
			aSquaresLeft--;
			Square * tempSquare;
			tempSquare = aSquares[i];
			aSquares[i] = aSquares[aSquaresLeft];
			aSquares[aSquaresLeft] = tempSquare;
		}
	}
	
	// now try and find a square which will not cause the other player to get a square
	int * esIndex = new int[eSquaresLeft];
	for ( i = 0; i < eSquaresLeft; i++)
	{
		esIndex[i] = i;
	}
	
	for ( i = eSquaresLeft - 1; i >= 0; i--)
	{
		// select one of the indexes at random, then check it so see if its square has a candidate side
		int rIndex = rand() % (i + 1);              
		int squareIndex = esIndex[rIndex];
		
		//System.out.println("squaresLeft="+squaresLeft+" squareIndex="+squareIndex);
		boolean squareIsGood = false;
		if (eSquares[squareIndex]->getSidesFilled() < 2)
		{
			if (eSquares[squareIndex]->trySquare())
			{
				squareIsGood = true;
			}
		}
		
		if (!squareIsGood)
		{
			eSquaresLeft--;
			Square * tempSquare;
			tempSquare = eSquares[squareIndex];
			eSquares[squareIndex] = eSquares[eSquaresLeft];
			eSquares[eSquaresLeft] = tempSquare;
		}
		else
		{
			delete [] esIndex;
			return;
		}
		esIndex[rIndex] = esIndex[i]; // so that we don't choose the same e square index again 
	}
	delete [] esIndex;
	// now just look for the first available move
	for ( i = aSquaresLeft - 1; i >= 0; i--)
	{
		if (aSquares[i]->getSidesFilled() < 4)
		{
			aSquares[i]->getEmptySide()->OnClicked();
			return;
		}
	}
	
}// end of function MakeMove
    
