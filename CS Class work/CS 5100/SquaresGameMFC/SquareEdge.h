#if !defined(AFX_SQUAREEDGE_H__D7346A94_5D5C_4020_9B67_6C97ECBBBA88__INCLUDED_)
#define AFX_SQUAREEDGE_H__D7346A94_5D5C_4020_9B67_6C97ECBBBA88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SquareEdge.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SquareEdge window

class SquareGame;
class Square;
class EasyComputer;
class HardComputer;

class SquareEdge : public CButton
{
	friend class Square;
	friend class EasyComputer;
	friend class HardComputer;
// Construction
public:
	SquareEdge(SquareGame *);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SquareEdge)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF color;
	SquareGame * ptrGame;
	void notifySquares();
	void CreateEdge(SquareGame * pGame);
	void AddSquare(Square *);
	Square * s2;
	Square * s1;
	bool trySide();
	int set;
	virtual ~SquareEdge();

	// Generated message map functions
protected:
	//{{AFX_MSG(SquareEdge)
	afx_msg void OnClicked();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQUAREEDGE_H__D7346A94_5D5C_4020_9B67_6C97ECBBBA88__INCLUDED_)
