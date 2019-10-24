// GraphFormView.h : interface of the CGraphFormView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHFORMVIEW_H__96016264_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
#define AFX_GRAPHFORMVIEW_H__96016264_63D3_11D4_98D7_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphFormView : public CFormView
{
protected: // create from serialization only
	CGraphFormView();
	DECLARE_DYNCREATE(CGraphFormView)
	void OnClickCheckBox(UINT nID);

public:
	//{{AFX_DATA(CGraphFormView)
	enum{ IDD = IDD_GRAPHFORM_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CGraphFormDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphFormView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphFormView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphFormView.cpp
inline CGraphFormDoc* CGraphFormView::GetDocument()
   { return (CGraphFormDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHFORMVIEW_H__96016264_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
