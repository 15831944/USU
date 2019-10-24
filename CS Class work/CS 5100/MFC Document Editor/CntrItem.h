// CntrItem.h : interface of the CMFCDocumentEditorCntrItem class
//

#if !defined(AFX_CNTRITEM_H__CF80B547_669C_489E_BABC_137288CACEBC__INCLUDED_)
#define AFX_CNTRITEM_H__CF80B547_669C_489E_BABC_137288CACEBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMFCDocumentEditorDoc;
class CMFCDocumentEditorView;

class CMFCDocumentEditorCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CMFCDocumentEditorCntrItem)

// Constructors
public:
	CMFCDocumentEditorCntrItem(REOBJECT* preo = NULL, CMFCDocumentEditorDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CMFCDocumentEditorDoc* GetDocument()
		{ return (CMFCDocumentEditorDoc*)CRichEditCntrItem::GetDocument(); }
	CMFCDocumentEditorView* GetActiveView()
		{ return (CMFCDocumentEditorView*)CRichEditCntrItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDocumentEditorCntrItem)
	public:
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	~CMFCDocumentEditorCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__CF80B547_669C_489E_BABC_137288CACEBC__INCLUDED_)
