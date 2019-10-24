// MFC Document EditorView.cpp : implementation of the CMFCDocumentEditorView class
//

#include "stdafx.h"
#include "MFC Document Editor.h"

#include "MFC Document EditorDoc.h"
#include "CntrItem.h"
#include "MFC Document EditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorView

IMPLEMENT_DYNCREATE(CMFCDocumentEditorView, CRichEditView)

BEGIN_MESSAGE_MAP(CMFCDocumentEditorView, CRichEditView)
	//{{AFX_MSG_MAP(CMFCDocumentEditorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorView construction/destruction

CMFCDocumentEditorView::CMFCDocumentEditorView()
{
	// TODO: add construction code here

}

CMFCDocumentEditorView::~CMFCDocumentEditorView()
{
}

BOOL CMFCDocumentEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CMFCDocumentEditorView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
}

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorView printing

BOOL CMFCDocumentEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CMFCDocumentEditorView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CRichEditView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorView diagnostics

#ifdef _DEBUG
void CMFCDocumentEditorView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMFCDocumentEditorView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CMFCDocumentEditorDoc* CMFCDocumentEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDocumentEditorDoc)));
	return (CMFCDocumentEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorView message handlers
