// SDIFileDropDoc.h : interface of the CSDIFileDropDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIFILEDROPDOC_H__F9DC4170_121D_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_SDIFILEDROPDOC_H__F9DC4170_121D_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIFileDropDoc : public CDocument
{
protected: // create from serialization only
	CSDIFileDropDoc();
	DECLARE_DYNCREATE(CSDIFileDropDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIFileDropDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIFileDropDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIFileDropDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIFILEDROPDOC_H__F9DC4170_121D_11D4_B398_00A0CC548BE4__INCLUDED_)
