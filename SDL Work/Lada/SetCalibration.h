#if !defined(AFX_SETCALIBRATION_H__CAA8FDE0_5676_11D5_B692_0080AD8FBDCC__INCLUDED_)
#define AFX_SETCALIBRATION_H__CAA8FDE0_5676_11D5_B692_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCalibration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SetCalibration dialog
class CLADAControlModuleDoc;
class SetCalibration : public CDialog
{
// Construction
public:
	void Save();
	void Display();
	int Chamber;
	double stringtodouble(CString string);
	CLADAControlModuleDoc* pDoc;
	SetCalibration(CLADAControlModuleDoc* doc,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SetCalibration)
	enum { IDD = IDD_SET_CALIBRATION };
	double	m_mult;
	double	m_off;
	double	A2;
	double	B2;
	double	B1;
	double	A1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetCalibration)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetCalibration)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCalculate();
	afx_msg void OnChambera();
	afx_msg void OnChamberb();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCALIBRATION_H__CAA8FDE0_5676_11D5_B692_0080AD8FBDCC__INCLUDED_)
