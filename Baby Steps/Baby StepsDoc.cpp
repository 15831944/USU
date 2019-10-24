// Baby StepsDoc.cpp : implementation of the CBabyStepsDoc class
//

#include "stdafx.h"
#include "Baby Steps.h"

#include "Baby StepsDoc.h"
#include "SimPropertiesDlg.h"
#include "Square.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CBabyStepsDoc

IMPLEMENT_DYNCREATE(CBabyStepsDoc, CDocument)

BEGIN_MESSAGE_MAP(CBabyStepsDoc, CDocument)
	//{{AFX_MSG_MAP(CBabyStepsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsDoc construction/destruction

CBabyStepsDoc::CBabyStepsDoc()
{
	// TODO: add one-time construction code here
	nRows = 0;
	nColumns = 0;
	squares = NULL;
	hotColor = RGB(255,0,0);
	coldColor = RGB(200,200,255);
}

CBabyStepsDoc::~CBabyStepsDoc()
{

}

BOOL CBabyStepsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	
	CSimPropertiesDlg propDlg;
	if (propDlg.DoModal()==IDCANCEL)
	{
		return FALSE;
	}

	nColumns = propDlg.m_nColumns;
	nRows = propDlg.m_nRows;

	if (squares)
	{
		delete [] squares;
	}
	squares = new Square[nRows * nColumns];
	state = Editting;
	hasStart = false;
	hasGoal = false;
	
	//square(2,3).top = 50;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBabyStepsDoc serialization

void CBabyStepsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsDoc diagnostics

#ifdef _DEBUG
void CBabyStepsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBabyStepsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBabyStepsDoc commands

void CBabyStepsDoc::OnCloseDocument() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (squares)
	{
		delete [] squares;
	}
	
	CDocument::OnCloseDocument();
}

void CBabyStepsDoc::SetSquareType(int x, int y, SquareType newType)
{
	if (x >= 0 && x < nColumns && y >= 0 && y <= nRows)
	{
		getSquare(x,y).SetType(newType);
		UpdateAllViews(NULL,1,(CObject *)&CPoint(x,y));
	}
}

void CBabyStepsDoc::SetGoal(int x, int y)
{
	if (hasGoal)
		ResetGoal();
	goalPoint.x = x;
	goalPoint.y = y;
	SetSquareType(x, y,Goal);
	hasGoal = true;
}

void CBabyStepsDoc::ResetGoal()
{
	if (hasGoal)
	{
		SetSquareType(goalPoint.x, goalPoint.y, Normal);
		hasGoal = false;
	}
}

void CBabyStepsDoc::SetStart(int x, int y)
{
	if (hasStart)
		ResetStart();
	startPoint.x = x;
	startPoint.y = y;
	SetSquareType(x, y,Start);
	hasStart = true;
}

void CBabyStepsDoc::ResetStart()
{
	if (hasStart)
	{
		SetSquareType(startPoint.x, startPoint.y, Normal);
		hasStart = false;
	}
}

void CBabyStepsDoc::UpdateSquare(int x, int y)
{
	UpdateAllViews(NULL,1,(CObject *)&CPoint(x,y));
}

void CBabyStepsDoc::UpdateAllSquares()
{
	UpdateAllViews(NULL,0,NULL);
}

void CBabyStepsDoc::RunAlgorithm()
{
	while (true)
	{
		int x = rand() % nColumns;
		int y = rand() % nRows;
		int side = rand() % 4;
		int change = rand() % 10;
		switch (side)
		{
		case 0: 
			{
			getSquare(x,y).top += change;
			if (getSquare(x,y).top < 0)
				getSquare(x,y).top = 0;
			if (getSquare(x,y).top > 100)
				getSquare(x,y).top = 100;
			} break;
		case 1:
			{
				getSquare(x,y).bottom += change;
			if (getSquare(x,y).bottom < 0)
				getSquare(x,y).bottom = 0;
			if (getSquare(x,y).bottom > 100)
				getSquare(x,y).bottom = 100;
			} break;
		case 2:
			{
				getSquare(x,y).right += change;
			if (getSquare(x,y).right < 0)
				getSquare(x,y).right = 0;
			if (getSquare(x,y).right > 100)
				getSquare(x,y).right = 100;
			} break;
		
		case 3:
			{
				getSquare(x,y).left += change;
			if (getSquare(x,y).left < 0)
				getSquare(x,y).left = 0;
			if (getSquare(x,y).left > 100)
				getSquare(x,y).left = 100;
			} break;
		}
		UpdateSquare(x,y);
		DoMessages();
		if (state != Running)
			return;
	}
}

void CBabyStepsDoc::DoMessages()
{
	MSG Msg;
		
	while (PeekMessage( &Msg,         // message information
		NULL,           // handle to window
		0,//WM_MOUSEFIRST,  // first message  
		0,//WM_MOUSELAST );  // last message
		PM_REMOVE /*| PM_NOYIELD*/)) //wRemoveMsg
		DispatchMessage( &Msg );  // message information);
}
