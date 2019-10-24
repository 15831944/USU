// CntrItem.cpp : implementation of the CMFCDocumentEditorCntrItem class
//

#include "stdafx.h"
#include "MFC Document Editor.h"

#include "MFC Document EditorDoc.h"
#include "MFC Document EditorView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorCntrItem implementation

IMPLEMENT_SERIAL(CMFCDocumentEditorCntrItem, CRichEditCntrItem, 0)

CMFCDocumentEditorCntrItem::CMFCDocumentEditorCntrItem(REOBJECT* preo, CMFCDocumentEditorDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
	
}

CMFCDocumentEditorCntrItem::~CMFCDocumentEditorCntrItem()
{
	// TODO: add cleanup code here
	
}

/////////////////////////////////////////////////////////////////////////////
// CMFCDocumentEditorCntrItem diagnostics

#ifdef _DEBUG
void CMFCDocumentEditorCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CMFCDocumentEditorCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
