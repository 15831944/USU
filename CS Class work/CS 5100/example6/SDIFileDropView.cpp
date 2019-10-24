// SDIFileDropView.cpp : implementation of the CSDIFileDropView class
//

#include "stdafx.h"
#include "SDIFileDrop.h"

#include "SDIFileDropDoc.h"
#include "SDIFileDropView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropView

IMPLEMENT_DYNCREATE(CSDIFileDropView, CView)

BEGIN_MESSAGE_MAP(CSDIFileDropView, CView)
	//{{AFX_MSG_MAP(CSDIFileDropView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropView construction/destruction

CSDIFileDropView::CSDIFileDropView()
{
	// TODO: add construction code here
	buffer[0] = '\0';
}

CSDIFileDropView::~CSDIFileDropView()
{
}

BOOL CSDIFileDropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropView drawing

void CSDIFileDropView::OnDraw(CDC* pDC)
{
	CSDIFileDropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(10, 10, CString(buffer));
}

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropView diagnostics

#ifdef _DEBUG
void CSDIFileDropView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIFileDropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIFileDropDoc* CSDIFileDropView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIFileDropDoc)));
	return (CSDIFileDropDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIFileDropView message handlers
