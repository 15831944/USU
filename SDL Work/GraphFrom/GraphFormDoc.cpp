// GraphFormDoc.cpp : implementation of the CGraphFormDoc class
//

#include "stdafx.h"
#include "GraphForm.h"

#include "GraphFormDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphFormDoc

IMPLEMENT_DYNCREATE(CGraphFormDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphFormDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphFormDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphFormDoc construction/destruction

CGraphFormDoc::CGraphFormDoc()
{
	// TODO: add one-time construction code here
	nDataItems = 10;
	IsItemChecked = new BOOL[nDataItems];
	for (int i = 0; i < nDataItems; i++)
		IsItemChecked[i] = FALSE;
	
	graphData = new double[nDataItems][MAX_DATA_ITEMS];
	
	for (i = 0; i < 10; i++){
		for (int p = 0; p < 100; p++){
			graphData[i][p] = rand() % 1000 / 100 + i * 10;
		}
	}

}

CGraphFormDoc::~CGraphFormDoc()
{
}

BOOL CGraphFormDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphFormDoc serialization

void CGraphFormDoc::Serialize(CArchive& ar)
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
// CGraphFormDoc diagnostics

#ifdef _DEBUG
void CGraphFormDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphFormDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphFormDoc commands
