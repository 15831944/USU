// HardComputer.h: interface for the HardComputer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HARDCOMPUTER_H__11363DE4_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
#define AFX_HARDCOMPUTER_H__11363DE4_464A_11D6_A4E8_005004A6D7B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComputerPlayer.h"

class Square;
class SquareGame;

class HardComputer : public ComputerPlayer  
{
public:
	int yBox;
	int xBox;
	SquareGame * ptrGame;
	int aSquaresLeft;
    int eSquaresLeft;
	HardComputer(int x, int y, SquareGame * pGame);
	virtual ~HardComputer();
	Square ** aSquares;
    Square ** eSquares;
	void MakeMove();
};

#endif // !defined(AFX_HARDCOMPUTER_H__11363DE4_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
