#if !defined(AFX_MEASUREWATER_H__9081BE60_5A16_11D5_8306_F93592EFF702__INCLUDED_)
#define AFX_MEASUREWATER_H__9081BE60_5A16_11D5_8306_F93592EFF702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MeasureWater.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMeasureWater dialog

class CMeasureWater : public CDialog
{
// Construction
public:
	double * ptrVolume;
	CMeasureWater(CString text, double * volume, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeasureWater)
	enum { IDD = IDD_MEASUREWATER };
	double	m_volume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeasureWater)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeasureWater)
	afx_msg void OnChangeEdit1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEASUREWATER_H__9081BE60_5A16_11D5_8306_F93592EFF702__INCLUDED_)
