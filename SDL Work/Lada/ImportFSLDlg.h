#if !defined(AFX_IMPORTFSLDLG_H__6D1A56A0_302A_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_IMPORTFSLDLG_H__6D1A56A0_302A_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportFSLDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportFSLDlg dialog
class CLADAControlModuleDoc;
class CFSInfo;
class CImportFSLDlg : public CDialog
{
// Construction
public:
	CFSInfo * m_ptrFSInfo;
	CLADAControlModuleDoc * pDoc;
	CImportFSLDlg(CLADAControlModuleDoc*, CFSInfo * pFSInfo, CWnd* pParent = NULL);   // standard constructor
	~CImportFSLDlg();
	CString *dataNames;
	int *ArrayID;
	int numIDs;
	int *nDataPoints;

// Dialog Data
	//{{AFX_DATA(CImportFSLDlg)
	enum { IDD = IDD_IMPORT_FSL };
	CComboBox	m_cArrayID;
	CListBox	m_FSList;
	CString	m_FileName;
	int		m_ArrayID;
	int		m_NumberDataPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportFSLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportFSLDlg)
	afx_msg void OnSelchangeArrayId();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTFSLDLG_H__6D1A56A0_302A_11D5_B690_0080AD8FBDCC__INCLUDED_)
