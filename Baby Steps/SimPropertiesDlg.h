#if !defined(AFX_SIMPROPERTIESDLG_H__090E1B03_C26B_4D6A_82EF_269590E5AE4F__INCLUDED_)
#define AFX_SIMPROPERTIESDLG_H__090E1B03_C26B_4D6A_82EF_269590E5AE4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SimPropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSimPropertiesDlg dialog

class CSimPropertiesDlg : public CDialog
{
// Construction
public:
	CSimPropertiesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSimPropertiesDlg)
	enum { IDD = IDD_GRID_PROPERTIES };
	int		m_nColumns;
	int		m_nRows;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSimPropertiesDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPROPERTIESDLG_H__090E1B03_C26B_4D6A_82EF_269590E5AE4F__INCLUDED_)
