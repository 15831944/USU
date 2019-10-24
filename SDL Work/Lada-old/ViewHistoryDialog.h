// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_VIEWHISTORYDIALOG_H__A3CB128A_82E7_4843_8D5C_15554B1FEC30__INCLUDED_)
#define AFX_VIEWHISTORYDIALOG_H__A3CB128A_82E7_4843_8D5C_15554B1FEC30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewHistoryDialog.h : header file
//

class CLADAControlModuleDoc;
class CHistoryClass;

/////////////////////////////////////////////////////////////////////////////
// CViewHistoryDialog dialog

class CViewHistoryDialog : public CDialog
{
// Construction
public:
	CViewHistoryDialog ** ptrHistoryDlg;
	CHistoryClass * ptrHistory;
	~CViewHistoryDialog();
	CViewHistoryDialog(CViewHistoryDialog ** ptrDlg, CHistoryClass * pHistory, CWnd* pParent = NULL);   // standard constructor
	BOOL Create(UINT nID, CWnd * pWnd = NULL)
        { return CDialog::Create(nID,pWnd);}
// Dialog Data
	//{{AFX_DATA(CViewHistoryDialog)
	enum { IDD = IDD_VIEWHISTORY };
	CListBox	m_ListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewHistoryDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewHistoryDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWHISTORYDIALOG_H__A3CB128A_82E7_4843_8D5C_15554B1FEC30__INCLUDED_)
