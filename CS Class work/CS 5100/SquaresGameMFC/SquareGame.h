// SquareGame.h: interface for the SquareGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQUAREGAME_H__5ABADC84_7239_424D_8B06_4601C993F1B6__INCLUDED_)
#define AFX_SQUAREGAME_H__5ABADC84_7239_424D_8B06_4601C993F1B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Square;
class ComputerPlayer;
class CSquaresGameDlg;

class SquareGame  
{
public:
	void Refresh();
	void saveBestScores();
	int bestScores[5];
    CString bestNames[5];
	int bestScoreCount;
	void IndicateCurrentPlayer();
	int pSize;
	void DeleteSquares();
	COLORREF playerColor[2];
	COLORREF sideColor;
	CSquaresGameDlg * getParent();
	void CreateGame(CSquaresGameDlg * ptrParent);
	int gameSize;
	Square ** squares;
	bool submitBestScore(int percent, CString name);
	CString name2;
	CString name1;
	ComputerPlayer * computer;
	int currentPlayer;
	int gameType;
	void PlayerEndTurn(bool & computerTurn);
	Square * getSquare(int x, int y);
	void DoGameOver();
	void updateScoreWindow();
	int playerScore[2];
	int totalSquaresLeft;
	SquareGame();
	virtual ~SquareGame();

private:
	CSquaresGameDlg * pParent;
};

#endif // !defined(AFX_SQUAREGAME_H__5ABADC84_7239_424D_8B06_4601C993F1B6__INCLUDED_)
