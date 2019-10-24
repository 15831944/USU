// Square.h: interface for the Square class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SQUARE_H__7604A655_61BE_44BB_99A3_2DB41A675CC4__INCLUDED_)
#define AFX_SQUARE_H__7604A655_61BE_44BB_99A3_2DB41A675CC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Square  
{
public:
	void SetType(SquareType newType);
	SquareType type;
	int right;
	int left;
	int bottom;
	int top;
	Square();
	virtual ~Square();

};

#endif // !defined(AFX_SQUARE_H__7604A655_61BE_44BB_99A3_2DB41A675CC4__INCLUDED_)
