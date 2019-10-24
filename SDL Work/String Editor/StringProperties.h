#if !defined(AFX_STRINGPROPERTIES_H__62E92F40_A1C7_11D4_A404_F79FE1268537__INCLUDED_)
#define AFX_STRINGPROPERTIES_H__62E92F40_A1C7_11D4_A404_F79FE1268537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StringProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// StringProperties dialog
class CStringInfo;
class StringProperties : public CDialog
{
// Construction
public:
	CString* nlanguages;
	int mlang;
	int clang;
	CFont* propfont;
	StringProperties(CString* nlang,int lang,CStringInfo* dat,CFont* font,CWnd* pParent = NULL);   // standard constructor
	~StringProperties();
// Dialog Data
	//{{AFX_DATA(StringProperties)
	enum { IDD = IDD_PROPERTIES };
	CStatic	m_cl1;
	CEdit	m_cel1;
	CEdit	m_crussian;
	CEdit	m_cid;
	CString	m_id;
	CString	m_russian;
	CStringInfo* m_data;
	CString	m_vel1;
	CString	m_l1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StringProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StringProperties)
	virtual void OnOK();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnLnext();
	afx_msg void OnLprev();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STRINGPROPERTIES_H__62E92F40_A1C7_11D4_A404_F79FE1268537__INCLUDED_)
