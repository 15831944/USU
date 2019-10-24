#if !defined(AFX_SQUARE_H__9BE4B946_0F97_4FE5_AF05_DD9827190B26__INCLUDED_)
#define AFX_SQUARE_H__9BE4B946_0F97_4FE5_AF05_DD9827190B26__INCLUDED_

#include "SquareEdge.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Square.h : header file
//

class SquareGame;

/////////////////////////////////////////////////////////////////////////////
// Square window

class Square : public CButton
{
// Construction
public:
	Square(int x, int y, SquareGame * pGame);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Square)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void Refresh();
	COLORREF color;
	void Destroy();
	bool trySquare();
	bool check();
	SquareEdge * getEmptySide();
	int getSidesFilled();
	int owner;
	bool isFilled;
	virtual ~Square();
	SquareEdge * getTopSide(){ return Top; }
	SquareEdge * getBottomSide(){ return Bottom; }
	SquareEdge * getLeftSide(){ return Left; }
	SquareEdge * getRightSide(){ return Right; }

	// Generated message map functions
protected:
	//{{AFX_MSG(Square)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void AddSides(int x, int y);
	SquareGame * ptrGame;
	SquareEdge * Right;
	SquareEdge * Left;
	SquareEdge * Bottom;
	SquareEdge * Top;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUARE_H__9BE4B946_0F97_4FE5_AF05_DD9827190B26__INCLUDED_)
