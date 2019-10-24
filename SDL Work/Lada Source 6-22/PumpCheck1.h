#if !defined(AFX_PUMPCHECK1_H__9081BE61_5A16_11D5_8306_F93592EFF702__INCLUDED_)
#define AFX_PUMPCHECK1_H__9081BE61_5A16_11D5_8306_F93592EFF702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PumpCheck1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PumpCheck1 dialog

class PumpCheck1 : public CDialog
{
// Construction
public:
	PumpCheck1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PumpCheck1)
	enum { IDD = IDD_PUMP_CHECK_1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PumpCheck1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PumpCheck1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PUMPCHECK1_H__9081BE61_5A16_11D5_8306_F93592EFF702__INCLUDED_)
