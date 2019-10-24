// junk3View.cpp : implementation of the CJunk3View class
//

#include "stdafx.h"
#include "junk3.h"

#include "junk3Doc.h"
#include "junk3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJunk3View

IMPLEMENT_DYNCREATE(CJunk3View, CView)

BEGIN_MESSAGE_MAP(CJunk3View, CView)
	//{{AFX_MSG_MAP(CJunk3View)
	ON_COMMAND(ID_PROPSHEET, OnPropsheet)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJunk3View construction/destruction
#include "propSheet.h"
CJunk3View::CJunk3View()
{
	// TODO: add construction code here

}

CJunk3View::~CJunk3View()
{
}

BOOL CJunk3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CJunk3View drawing

void CJunk3View::OnDraw(CDC* pDC)
{
	CJunk3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CJunk3View printing

BOOL CJunk3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJunk3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJunk3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CJunk3View diagnostics

#ifdef _DEBUG
void CJunk3View::AssertValid() const
{
	CView::AssertValid();
}

void CJunk3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJunk3Doc* CJunk3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJunk3Doc)));
	return (CJunk3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJunk3View message handlers

void CJunk3View::OnPropsheet() 
{

	CpropSheet propSheet("MINE");
	propSheet.SetWizardMode(); //WIZARD
	int result = propSheet.DoModal();
}


void CJunk3View::OnFileSave() 
{
	CFileDialog d(FALSE);
	d.DoModal();
	
}
