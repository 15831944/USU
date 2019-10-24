// SquareGame.cpp: implementation of the SquareGame class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SquaresGame.h"
#include "SquareGame.h"
#include "GameOverDialog.h"
#include "BestScoresDialog.h"
#include "Square.h"
#include "SquaresGameDlg.h"
#include <fstream.h>
#include "EasyComputer.h"
#include "HardComputer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CFont BoldFont;
extern CFont NormalFont;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SquareGame::SquareGame()
{
	gameSize = 0;
	gameType = 1;
	totalSquaresLeft = 0;
	squares = NULL;
	pParent = NULL;
	computer = NULL;
	playerColor[0] = RGB(255,0,0);
	playerColor[1] = RGB(0,0,255);
	sideColor = RGB(0,0,0);
	pSize = 0;
	bestScoreCount = 0;
	for (int i = 0; i < 5; i++)
	{
		bestNames[i] = "";
		bestScores[i] = 0;
	}
	
	ifstream fin("bestscores.txt");
	int count;
	char quote;
	if (fin >> count)
	{
		bestScoreCount = count;
		for (i = 0; i < count; i++)
		{
			fin >> quote;
			fin.getline(bestNames[i].GetBuffer(80),80,'\"');
			fin >> bestScores[i];
		}
	}
	fin.close();
}

SquareGame::~SquareGame()
{
	DeleteSquares();
}

void SquareGame::updateScoreWindow()
{
	pParent->m_Player1Score = playerScore[0];
	pParent->m_Player2Score = playerScore[1];
	pParent->UpdateData(FALSE);
}

void SquareGame::DoGameOver()
{
	//.. the game is over... 
	int percent = 50;
	CString name;
	GameOverDialog * gDlg;
	bool isTie = false;
    if (playerScore[0] > playerScore[1])
    {
		name = name1;
        percent = playerScore[0] * 100 /(playerScore[0]+playerScore[1]);
		isTie = false;
        
    }
    else if (playerScore[1] > playerScore[0])
    {
        name = name2;
        percent = playerScore[1] * 100 /(playerScore[0]+playerScore[1]);
		isTie = false;
    }
    else
    {
		name = CString("");
        isTie = true;
    }
	gDlg = new GameOverDialog(name,percent,isTie);
    gDlg->DoModal();
	delete gDlg;

    if (isTie == false)
    {
        if (submitBestScore(percent,name))
        {
            BestScoresDialog * bDlg = new BestScoresDialog(this);
            bDlg->DoModal();
			delete bDlg;
        }
    }
}

Square * SquareGame::getSquare(int x, int y)
{
	return squares[x + y * gameSize];
}

void SquareGame::PlayerEndTurn(bool & computerTurn)
{
	//sGame.gPanel.sPanel.pLabel[currentPlayer].setForeground(new Color(150, 180, 220));
	currentPlayer = (currentPlayer + 1) % 2;
	IndicateCurrentPlayer();
	//sGame.gPanel.sPanel.pLabel[currentPlayer].setForeground(new Color(0,0,0));
	if (gameType != 1 && currentPlayer != 0)
	{
        // computer's turn to make a move...
		computerTurn = true;
	}
}

bool SquareGame::submitBestScore(int percent, CString name)
{
	for (int i = 0; i < 5; i++)
    {
        if (i >= bestScoreCount || percent > bestScores[i])
        {
          for (int j = 4; j > i; j--)
          {
            bestScores[j] = bestScores[j - 1];
            bestNames[j] = bestNames[j - 1];
          }
          bestScores[i] = percent;
          bestNames[i] = name;
          if (bestScoreCount < 5)
            bestScoreCount++;
		  saveBestScores();
          return true;
        }
    }
    return false; 
}

void SquareGame::CreateGame(CSquaresGameDlg * pDlg)
{
	pParent = pDlg;
	pParent->ShowWindow(SW_HIDE);
	DeleteSquares();

	playerScore[0] = 0;
	playerScore[1] = 0;
	updateScoreWindow();

	currentPlayer = 0;
	IndicateCurrentPlayer();

	pSize = gameSize * gameSize;
	totalSquaresLeft = pSize;
	squares = new Square *[pSize];
	int index;
	//char name[20];
	for (int i = 0; i < gameSize; i++)
	{
		for(int j = 0; j < gameSize; j++)
		{
			index = i + j * gameSize;
			squares[index] = new Square(i,j,this);
			//wsprintf(name,"%i",index);
		}
	}
	
	name1 = "Player 1";
	if (gameType == 1)
	{
		name2 = "Player 2";
	}
	else if (gameType == 2)
	{
		name2 = "Opponent";
		computer = new EasyComputer(gameSize,gameSize,this);
	}
	else if (gameType == 3)
	{
		name2 = "Opponent";
		computer = new HardComputer(gameSize,gameSize,this);
	}
	pParent->m_p1Text.SetWindowText(name1);
	pParent->m_p2Text.SetWindowText(name2);

	RECT rect;
	CPoint p(0,0);
	pParent->ClientToScreen(&p);
	pParent->GetWindowRect(&rect);
	int topHeight = p.y - rect.top;
	pParent->SetWindowPos( NULL, 0, 0, gameSize * SQUARE_SIZE + LINE_WIDTH + 7, gameSize * SQUARE_SIZE + LINE_WIDTH + GAME_PANEL_HEIGHT + topHeight + 4, SWP_NOMOVE | SWP_NOZORDER );
	pParent->ShowWindow(SW_SHOW);
}

CSquaresGameDlg * SquareGame::getParent()
{
	return pParent;
}

void SquareGame::DeleteSquares()
{
	if (computer)
	{
		delete computer;
		computer = NULL;
	}

	if (squares)
	{
		for (int k = 0; k < pSize; k++)
		{
			squares[k]->Destroy();
			delete squares[k];
		}
		delete [] squares;
	}
}

void SquareGame::IndicateCurrentPlayer()
{
	if (currentPlayer == 0)
	{
		//pParent->m_p1Text.ModifyStyleEx(0,WS_EX_WINDOWEDGE,SWP_DRAWFRAME);
		//pParent->m_p2Text.ModifyStyleEx(WS_EX_WINDOWEDGE,0,SWP_DRAWFRAME);
		pParent->m_p1Text.SetFont(&BoldFont);
		pParent->m_p2Text.SetFont(&NormalFont);
	}
	else
	{
		//pParent->m_p1Text.ModifyStyleEx(WS_EX_WINDOWEDGE,0,SWP_DRAWFRAME);
		//pParent->m_p2Text.ModifyStyleEx(0,WS_EX_WINDOWEDGE,SWP_DRAWFRAME);
		pParent->m_p2Text.SetFont(&BoldFont);
		pParent->m_p1Text.SetFont(&NormalFont);
	}
}

void SquareGame::saveBestScores()
{
	ofstream fout("bestscores.txt");
	fout << bestScoreCount << endl; 	
	for (int i = 0; i < bestScoreCount; i++)
	{
		fout << "\t" << "\"" << bestNames[i].GetBuffer(0) << "\"" ;
		fout << bestScores[i] << endl;
	}
	fout.close();
}

void SquareGame::Refresh()
{
	if (squares)
	{
		for (int k = 0; k < pSize; k++)
		{
			squares[k]->Refresh();
		}
	}
}
