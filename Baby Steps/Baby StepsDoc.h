// Baby StepsDoc.h : interface of the CBabyStepsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BABYSTEPSDOC_H__95D1354D_0C38_4B5E_991A_A269556B35ED__INCLUDED_)
#define AFX_BABYSTEPSDOC_H__95D1354D_0C38_4B5E_991A_A269556B35ED__INCLUDED_

#include "Baby Steps.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Square;

class CBabyStepsDoc : public CDocument
{
protected: // create from serialization only
	CBabyStepsDoc();
	DECLARE_DYNCREATE(CBabyStepsDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBabyStepsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	void RunAlgorithm();
	COLORREF coldColor;
	COLORREF hotColor;
	void UpdateAllSquares();
	void UpdateSquare(int x, int y);
	void ResetStart();
	void SetStart(int x, int y);
	void ResetGoal();
	void SetGoal(int x, int y);
	CPoint startPoint;
	CPoint goalPoint;
	bool hasGoal;
	bool hasStart;
	void SetSquareType(int x, int y, SquareType newType);
	DocStateType state;
	int nColumns;
	int nRows;
	Square * squares;
	virtual ~CBabyStepsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void DoMessages();
// Generated message map functions
protected:
	
	//{{AFX_MSG(CBabyStepsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BABYSTEPSDOC_H__95D1354D_0C38_4B5E_991A_A269556B35ED__INCLUDED_)
