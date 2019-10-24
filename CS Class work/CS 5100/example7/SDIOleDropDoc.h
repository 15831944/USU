// SDIOleDropDoc.h : interface of the CSDIOleDropDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIOLEDROPDOC_H__41A55BAC_16B3_11D4_B398_00A0CC548BE4__INCLUDED_)
#define AFX_SDIOLEDROPDOC_H__41A55BAC_16B3_11D4_B398_00A0CC548BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDIOleDropDoc : public COleDocument
{
protected: // create from serialization only
	CSDIOleDropDoc();
	DECLARE_DYNCREATE(CSDIOleDropDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDIOleDropDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSDIOleDropDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDIOleDropDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIOLEDROPDOC_H__41A55BAC_16B3_11D4_B398_00A0CC548BE4__INCLUDED_)
