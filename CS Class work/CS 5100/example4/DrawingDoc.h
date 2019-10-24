// DrawingDoc.h : interface of the CDrawingDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWINGDOC_H__D5A17BB7_064F_11D4_949F_000086520C5B__INCLUDED_)
#define AFX_DRAWINGDOC_H__D5A17BB7_064F_11D4_949F_000086520C5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawingDoc : public CDocument
{
protected: // create from serialization only
	CDrawingDoc();
	DECLARE_DYNCREATE(CDrawingDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawingDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawingDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWINGDOC_H__D5A17BB7_064F_11D4_949F_000086520C5B__INCLUDED_)
