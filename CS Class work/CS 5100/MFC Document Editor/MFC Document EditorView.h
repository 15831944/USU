// MFC Document EditorView.h : interface of the CMFCDocumentEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDOCUMENTEDITORVIEW_H__F59C193C_343C_477C_817C_071C2A1ED535__INCLUDED_)
#define AFX_MFCDOCUMENTEDITORVIEW_H__F59C193C_343C_477C_817C_071C2A1ED535__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMFCDocumentEditorCntrItem;
class CMFCDocumentEditorDoc;

class CMFCDocumentEditorView : public CRichEditView
{
protected: // create from serialization only
	CMFCDocumentEditorView();
	DECLARE_DYNCREATE(CMFCDocumentEditorView)

// Attributes
public:
	CMFCDocumentEditorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDocumentEditorView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCDocumentEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCDocumentEditorView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFC Document EditorView.cpp
inline CMFCDocumentEditorDoc* CMFCDocumentEditorView::GetDocument()
   { return (CMFCDocumentEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDOCUMENTEDITORVIEW_H__F59C193C_343C_477C_817C_071C2A1ED535__INCLUDED_)
