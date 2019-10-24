#if !defined(AFX_CR10FINALSTORAGEDEBUGREPORT_H__83FE99C9_2752_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_CR10FINALSTORAGEDEBUGREPORT_H__83FE99C9_2752_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CR10FinalStorageDebugReport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCR10FinalStorageDebugReport dialog

class CLADAControlModuleDoc;
class CCR10FinalStorageDebugReport : public CDialog
{
// Construction
public:
	CLADAControlModuleDoc * pDoc;
	CCR10FinalStorageDebugReport(CLADAControlModuleDoc *doc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCR10FinalStorageDebugReport)
	enum { IDD = IDD_DIALOG4 };
	int		m_CR10Dsp;
	int		m_LastDSP;
	CString	m_CollectFinalStorage;
	int		m_nAttempted;
	int		m_nSuccessful;
	int		m_ArrayID;
	int		m_LastFailCode;
	int		m_LastRetrieved;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCR10FinalStorageDebugReport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCR10FinalStorageDebugReport)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CR10FINALSTORAGEDEBUGREPORT_H__83FE99C9_2752_11D5_B690_0080AD8FBDCC__INCLUDED_)
