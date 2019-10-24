#if !defined(AFX_ILPROPERTIES_H__BE22CCE0_0F36_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_ILPROPERTIES_H__BE22CCE0_0F36_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ILProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CILProperties dialog
class CLADAControlModuleDoc;
class CInputLocFileInfo;

class CILProperties : public CDialog
{
// Construction
public:
	bool doResetTimer;
	~CILProperties();
	int * m_LocList;
	int wGroup;
	CInputLocFileInfo * m_ptrILFileInfo;
	CLADAControlModuleDoc * pDoc;
	BOOL m_ByAverage;
	void SetStrings(BOOL updateData = TRUE);
	CILProperties(CLADAControlModuleDoc * doc, CInputLocFileInfo * ptrIlFileInfo, int wGroup, CWnd* pParent = NULL);   // standard constructor
	void ShowAverageInstant();
// Dialog Data
	//{{AFX_DATA(CILProperties)
	enum { IDD = IDD_IL_PROPERTIES };
	CButton	m_Instant;
	CButton	m_Average;
	CComboBox	m_F2;
	CComboBox	m_F3;
	CComboBox	m_F1;
	int		m_DataRetrFreq;
	CString	m_GroupName;
	int		m_NewILFileFreq;
	BOOL	m_SaveData;
	int		m_SaveDataFreq;
	int		m_NIL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CILProperties)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CILProperties)
	afx_msg void OnAverage();
	afx_msg void OnOneInstant();
	afx_msg void OnChooseIllList();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ILPROPERTIES_H__BE22CCE0_0F36_11D5_B690_0080AD8FBDCC__INCLUDED_)
