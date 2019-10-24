// SDIOleDropView.cpp : implementation of the CSDIOleDropView class
//

#include "stdafx.h"
#include "SDIOleDrop.h"

#include "SDIOleDropDoc.h"
#include "CntrItem.h"
#include "SDIOleDropView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropView

IMPLEMENT_DYNCREATE(CSDIOleDropView, CView)

BEGIN_MESSAGE_MAP(CSDIOleDropView, CView)
	//{{AFX_MSG_MAP(CSDIOleDropView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropView construction/destruction

CSDIOleDropView::CSDIOleDropView()
{
	m_pSelection = NULL;
	// TODO: add construction code here

}

CSDIOleDropView::~CSDIOleDropView()
{
}

BOOL CSDIOleDropView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropView drawing

void CSDIOleDropView::OnDraw(CDC* pDC)
{
	CSDIOleDropDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CSDIOleDropCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

//pDC->TextOut(10, 10, buffer);
	pDC->DrawText(CString(buffer), CRect(10, 10, 300, 300), DT_LEFT);
}

void CSDIOleDropView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropView printing

BOOL CSDIOleDropView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDIOleDropView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDIOleDropView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSDIOleDropView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CSDIOleDropView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CSDIOleDropCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CSDIOleDropView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CSDIOleDropCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CSDIOleDropCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CSDIOleDropDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CSDIOleDropCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CSDIOleDropView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CSDIOleDropView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CSDIOleDropView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropView diagnostics

#ifdef _DEBUG
void CSDIOleDropView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIOleDropView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIOleDropDoc* CSDIOleDropView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIOleDropDoc)));
	return (CSDIOleDropDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIOleDropView message handlers

int CSDIOleDropView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_target.Register(this);
	buffer[0] = '\0';
	return 0;
}

DROPEFFECT CSDIOleDropView::OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	return OnDragOver(pDataObject, dwKeyState, point);
}

void CSDIOleDropView::OnDragLeave() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnDragLeave();
}

DROPEFFECT CSDIOleDropView::OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point) 
{
	// TODO: Add your specialized code here and/or call the base class
	DROPEFFECT de = DROPEFFECT_COPY;
	return de;
}

BOOL CSDIOleDropView::OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point) 
{
	STGMEDIUM struc;
	pDataObject->GetData(CF_TEXT, &struc);
	if (struc.tymed != TYMED_NULL)
	{
		const char ** p = (const char **)struc.hGlobal;
		strcpy(buffer, *p);
	}
	else
	{
		pDataObject->GetData(CF_HDROP, &struc);
		HDROP hdrop = (HDROP)GlobalLock(struc.hGlobal);
		int i = DragQueryFile(hdrop, 0, buffer, 99);
		GlobalUnlock(hdrop);
	}
	Invalidate();
	ReleaseStgMedium(&struc);
	return TRUE;
}
