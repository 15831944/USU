// GraphFormDoc.h : interface of the CGraphFormDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHFORMDOC_H__96016262_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
#define AFX_GRAPHFORMDOC_H__96016262_63D3_11D4_98D7_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_DATA_ITEMS	5000

class CGraphFormDoc : public CDocument
{
protected: // create from serialization only
	CGraphFormDoc();
	DECLARE_DYNCREATE(CGraphFormDoc)

// Attributes
public:
	int nDataItems;
	BOOL *IsItemChecked;
	double (*graphData)[MAX_DATA_ITEMS];
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphFormDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphFormDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphFormDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHFORMDOC_H__96016262_63D3_11D4_98D7_00A076801ACD__INCLUDED_)
