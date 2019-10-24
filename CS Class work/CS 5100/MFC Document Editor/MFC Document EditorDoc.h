// MFC Document EditorDoc.h : interface of the CMFCDocumentEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDOCUMENTEDITORDOC_H__B5080D7C_E7C6_43D5_8AB4_C0D1BA7DFCFF__INCLUDED_)
#define AFX_MFCDOCUMENTEDITORDOC_H__B5080D7C_E7C6_43D5_8AB4_C0D1BA7DFCFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMFCDocumentEditorDoc : public CRichEditDoc
{
protected: // create from serialization only
	CMFCDocumentEditorDoc();
	DECLARE_DYNCREATE(CMFCDocumentEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDocumentEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	//}}AFX_VIRTUAL
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CMFCDocumentEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCDocumentEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDOCUMENTEDITORDOC_H__B5080D7C_E7C6_43D5_8AB4_C0D1BA7DFCFF__INCLUDED_)
