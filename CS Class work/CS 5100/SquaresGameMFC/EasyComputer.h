// EasyComputer.h: interface for the EasyComputer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EASYCOMPUTER_H__11363DE3_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
#define AFX_EASYCOMPUTER_H__11363DE3_464A_11D6_A4E8_005004A6D7B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComputerPlayer.h"

class SquareGame; 
class Square;

class EasyComputer : public ComputerPlayer  
{
public:
	SquareGame * ptrGame;
	int yBox;
	int xBox;
	int squaresLeft;
	Square ** asquares;
	EasyComputer(int x, int y, SquareGame *);
	void MakeMove();
	virtual ~EasyComputer();

};

#endif // !defined(AFX_EASYCOMPUTER_H__11363DE3_464A_11D6_A4E8_005004A6D7B4__INCLUDED_)
