// This is Version 1.0 PLEASE DOCUMENT CHANGES
#if !defined(AFX_ILGROUPPROPERTIES_H__D3598550_161D_4431_92E7_25865A03C3B5__INCLUDED_)
#define AFX_ILGROUPPROPERTIES_H__D3598550_161D_4431_92E7_25865A03C3B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ILGroupProperties.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CILGroupProperties dialog

class CInputLocFileInfo;
class CLADAControlModuleDoc;

typedef void (CALLBACK EXPORT* lpfnTimerCallback) (HWND, UINT, UINT, DWORD);

class CILGroupProperties : public CDialog
{
// Construction
public:
	void ResetStrings();
	void SetStrings();
	int wGroup;
	void ShowAverageInstant();
	BOOL m_SaveByAverage;
	int * m_LocList;
	CLADAControlModuleDoc * pDoc;
	CInputLocFileInfo * m_ptrILFileInfo;
	CILGroupProperties(CLADAControlModuleDoc * pDoc, CInputLocFileInfo * ptrILFileInfo, int wGroup, CWnd* pParent = NULL);   // standard constructor
	~CILGroupProperties();
// Dialog Data
	//{{AFX_DATA(CILGroupProperties)
	enum { IDD = IDD_GROUP_PROPERTIES };
	CComboBox	m_F3;
	CComboBox	m_F2;
	CComboBox	m_F1;
	BOOL	m_SaveData;
	int		m_DataRetrFreq;
	CString	m_GroupName;
	int		m_NewILFileFreq;
	int		m_NIL;
	int		m_SaveDataFreq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CILGroupProperties)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CILGroupProperties)
	afx_msg void OnSaveData();
	afx_msg void OnChooseIllList();
	afx_msg void OnAverage();
	afx_msg void OnOneInstant();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ILGROUPPROPERTIES_H__D3598550_161D_4431_92E7_25865A03C3B5__INCLUDED_)
