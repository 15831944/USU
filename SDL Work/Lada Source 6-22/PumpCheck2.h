#if !defined(AFX_PUMPCHECK2_H__9081BE62_5A16_11D5_8306_F93592EFF702__INCLUDED_)
#define AFX_PUMPCHECK2_H__9081BE62_5A16_11D5_8306_F93592EFF702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PumpCheck2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PumpCheck2 dialog

class PumpCheck2 : public CDialog
{
// Construction
public:
	PumpCheck2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PumpCheck2)
	enum { IDD = IDD_PUMP_CHECK_2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PumpCheck2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PumpCheck2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUMPCHECK2_H__9081BE62_5A16_11D5_8306_F93592EFF702__INCLUDED_)
