// DrawingDoc.cpp : implementation of the CDrawingDoc class
//

#include "stdafx.h"
#include "Drawing.h"

#include "DrawingDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawingDoc

IMPLEMENT_DYNCREATE(CDrawingDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawingDoc, CDocument)
	//{{AFX_MSG_MAP(CDrawingDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawingDoc construction/destruction

CDrawingDoc::CDrawingDoc()
{
	// TODO: add one-time construction code here

}

CDrawingDoc::~CDrawingDoc()
{
}

BOOL CDrawingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDrawingDoc serialization

void CDrawingDoc::Serialize(CArchive& ar)
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
// CDrawingDoc diagnostics

#ifdef _DEBUG
void CDrawingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawingDoc commands
