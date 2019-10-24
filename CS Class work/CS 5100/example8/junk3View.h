// junk3View.h : interface of the CJunk3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JUNK3VIEW_H__797D85B2_BFA7_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_JUNK3VIEW_H__797D85B2_BFA7_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJunk3View : public CView
{
protected: // create from serialization only
	CJunk3View();
	DECLARE_DYNCREATE(CJunk3View)

// Attributes
public:
	CJunk3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJunk3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJunk3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJunk3View)
	afx_msg void OnPropsheet();
	afx_msg void OnFileSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in junk3View.cpp
inline CJunk3Doc* CJunk3View::GetDocument()
   { return (CJunk3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JUNK3VIEW_H__797D85B2_BFA7_11D4_B398_00A0CC548BE4__INCLUDED_)
