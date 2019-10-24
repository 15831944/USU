// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_GRAPHBUTTONFORM_H__B5A7CFC8_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_GRAPHBUTTONFORM_H__B5A7CFC8_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphButtonForm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphButtonForm form view

#ifndef __AFXEXT_H__
#ifdef _RAPID_TRANSLATION
#undef CString
#include<afxext.h>
#define CString __X_CString
#else
#include<afxext.h>
#endif
#endif

class CColorCheckButton;
class CLADAControlModuleDoc;

class CGraphButtonForm : public CFormView
{
	friend class CLADAControlModuleDoc;	// Allows access to the Document Class
protected:
	CGraphButtonForm();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CGraphButtonForm)

// Form Data
public:
	void OnClickNumberBox(UINT nID);
	int whichWindow;					// Which of the graphs this is displayed in
	int numControls;					// The number of controls
	CColorCheckButton **bCtrl;			// The pointer to an array of CColor Check Buttons
	CStatic **numberBoxes;				// The pointer to an array of CStatics
	BOOL Initialized;					// 
	//CFont *formFont;
	CBrush brush;
	//{{AFX_DATA(CGraphButtonForm)
	enum { IDD = IDD_GRAPHBUTTONFORM_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	BOOL IsPaneMaximized;

	CBitmapButton graphButton;
	CLADAControlModuleDoc * pDoc;
	void ClickCheckBox(UINT nID);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphButtonForm)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL
	

// Implementation
protected:
	virtual ~CGraphButtonForm();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	
	// Generated message map functions
	//{{AFX_MSG(CGraphButtonForm)
	afx_msg void OnGraphName();
	afx_msg void OnGraphSize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHBUTTONFORM_H__B5A7CFC8_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
