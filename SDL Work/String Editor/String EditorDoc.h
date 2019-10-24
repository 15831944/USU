// String EditorDoc.h : interface of the CStringEditorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGEDITORDOC_H__16E7BB8D_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
#define AFX_STRINGEDITORDOC_H__16E7BB8D_9EBD_11D4_98E8_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Array.h"

class CStringInfo;

class CStringEditorDoc : public CDocument
{
protected: // create from serialization only
	CStringEditorDoc();
//	~CStringEditorDoc();
	DECLARE_DYNCREATE(CStringEditorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStringEditorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL hadH;
	int nextinternal;
	BOOL update;
	CString m_findfind;
	BOOL m_findstring;
	BOOL m_findlabel;
	int m_foundnumber;
	Array<CStringInfo> m_s;
	int m_nAllocatedStrings;
	int m_FontHeight;
//	CString * m_Strings;
//	int * m_StringID;
//	CString * m_Symbols;
	int m_nStrings;
	int m_CHARSET;
	CString m_FontName;
	CString * m_LanguageNames;
	int m_nLanguages;
	virtual ~CStringEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStringEditorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGEDITORDOC_H__16E7BB8D_9EBD_11D4_98E8_00A076801ACD__INCLUDED_)
