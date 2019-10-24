// SDIFileDropView.h : interface of the CSDIFileDropView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIFILEDROPVIEW_H__F9DC4172_121D_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_SDIFILEDROPVIEW_H__F9DC4172_121D_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIFileDropView : public CView
{
protected: // create from serialization only
	CSDIFileDropView();
	DECLARE_DYNCREATE(CSDIFileDropView)

// Attributes
public:
	CSDIFileDropDoc* GetDocument();
	char buffer[100];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIFileDropView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIFileDropView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIFileDropView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SDIFileDropView.cpp
inline CSDIFileDropDoc* CSDIFileDropView::GetDocument()
   { return (CSDIFileDropDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIFILEDROPVIEW_H__F9DC4172_121D_11D4_B398_00A0CC548BE4__INCLUDED_)
