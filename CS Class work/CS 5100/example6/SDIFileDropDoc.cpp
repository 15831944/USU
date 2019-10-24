// SDIFileDropDoc.cpp : implementation of the CSDIFileDropDoc class
//

#include "stdafx.h"
#include "SDIFileDrop.h"

#include "SDIFileDropDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropDoc

IMPLEMENT_DYNCREATE(CSDIFileDropDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIFileDropDoc, CDocument)
	//{{AFX_MSG_MAP(CSDIFileDropDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropDoc construction/destruction

CSDIFileDropDoc::CSDIFileDropDoc()
{
	// TODO: add one-time construction code here

}

CSDIFileDropDoc::~CSDIFileDropDoc()
{
}

BOOL CSDIFileDropDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropDoc serialization

void CSDIFileDropDoc::Serialize(CArchive& ar)
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
// CSDIFileDropDoc diagnostics

#ifdef _DEBUG
void CSDIFileDropDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIFileDropDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropDoc commands
