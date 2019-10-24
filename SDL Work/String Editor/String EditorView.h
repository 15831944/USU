// String EditorView.h : interface of the CStringEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGEDITORVIEW_H__16E7BB8F_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
#define AFX_STRINGEDITORVIEW_H__16E7BB8F_9EBD_11D4_98E8_00A076801ACD__INCLUDED_

#include "StringInfo.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringEditorDoc;

class CStringEditorView : public CListView
{
protected: // create from serialization only
	CStringEditorView();
	DECLARE_DYNCREATE(CStringEditorView)

// Attributes
public:
	CStringEditorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStringEditorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFont* printfont;
	int current;
	int lh;
	CFont* pfont;
	int lpp;
	int m_buffercount;
	BOOL IsInside(CString a,CString b);
	CFont docfont;
	void load(int num);
	void DeleteWindowContents();
	void CheckForDuplicate();
	void Reset();
	CStringInfo* m_buffer;
	void NewString(int nitem);
	POINT m_messPoint;
	void OnNewString();
	CMenu * rightClickMenu;
	CStringEditorDoc * pDoc;
	virtual ~CStringEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStringEditorView)
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditCopy();
	afx_msg void OnPaste();
	afx_msg void OnProperties();
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in String EditorView.cpp
inline CStringEditorDoc* CStringEditorView::GetDocument()
   { return (CStringEditorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGEDITORVIEW_H__16E7BB8F_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
