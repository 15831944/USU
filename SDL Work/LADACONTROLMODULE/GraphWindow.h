#if !defined(AFX_GRAPHWINDOW_H__B5A7CFC7_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
#define AFX_GRAPHWINDOW_H__B5A7CFC7_72B9_11D4_98D9_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphWindow frame

class CGraphWindow : public CFrameWnd
{
	DECLARE_DYNCREATE(CGraphWindow)
protected:
	CGraphWindow();           // protected constructor used by dynamic creation

// Attributes
	CSplitterWnd m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphWindow)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CGraphWindow();

	// Generated message map functions
	//{{AFX_MSG(CGraphWindow)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHWINDOW_H__B5A7CFC7_72B9_11D4_98D9_00A076801ACD__INCLUDED_)
