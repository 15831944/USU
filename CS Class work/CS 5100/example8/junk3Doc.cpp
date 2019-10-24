// junk3Doc.cpp : implementation of the CJunk3Doc class
//

#include "stdafx.h"
#include "junk3.h"

#include "junk3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJunk3Doc

IMPLEMENT_DYNCREATE(CJunk3Doc, CDocument)

BEGIN_MESSAGE_MAP(CJunk3Doc, CDocument)
	//{{AFX_MSG_MAP(CJunk3Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJunk3Doc construction/destruction

CJunk3Doc::CJunk3Doc()
{
	// TODO: add one-time construction code here

}

CJunk3Doc::~CJunk3Doc()
{
}

BOOL CJunk3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CJunk3Doc serialization

void CJunk3Doc::Serialize(CArchive& ar)
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
// CJunk3Doc diagnostics

#ifdef _DEBUG
void CJunk3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJunk3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJunk3Doc commands
