// This is Version 1.0 PLEASE DOCUMENT CHANGES
// This dialog allows you to set a min and a max for certain input location
#if !defined(AFX_MINMAX_H__0A44B88C_7224_45B0_8FE0_BD9CCE0D92BD__INCLUDED_)
#define AFX_MINMAX_H__0A44B88C_7224_45B0_8FE0_BD9CCE0D92BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MinMax.h : header file

class MinMax : public CDialog
{
// Construction
public:
	void SetStrings();								// Sets the text to the current language
	int number;										// The input location number
	MinMax(double, double, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MinMax)
	enum { IDD = IDD_MINMAX };
	double	m_vmax;									// the max value
	double	m_vmin;									// the min value
	BOOL	m_Validate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MinMax)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MinMax)
	virtual BOOL OnInitDialog();				// initialization stuff
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MINMAX_H__0A44B88C_7224_45B0_8FE0_BD9CCE0D92BD__INCLUDED_)
