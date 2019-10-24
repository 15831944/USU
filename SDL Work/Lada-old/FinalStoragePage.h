#if !defined(AFX_FINALSTORAGEPAGE_H__85E90368_2CDE_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_FINALSTORAGEPAGE_H__85E90368_2CDE_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FinalStoragePage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFinalStoragePage dialog

class CFSInfo;

class CFinalStoragePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CFinalStoragePage)

// Construction
public:
	int m_InitialCR10Freq;

	BOOL IsModified;
	void SetModified(BOOL=TRUE);
	CFinalStoragePage();
	~CFinalStoragePage();

	void SetTimeSensitiveChamberData();				// final storage
	void EnableFinalStorage(BOOL enable = FALSE);	// final storage
	void SetChamberData(BOOL updateData = TRUE);	// final storage
	void SetDocument(CLADAControlModuleDoc *doc);
	void SetStrings(BOOL updateData = TRUE);		// all
	
	int m_InitialSaveFreq;							// final storage
	CFSInfo * m_ptrFSInfo;							// final storage
	CLADAControlModuleDoc * pDoc;					// all

// Dialog Data
	//{{AFX_DATA(CFinalStoragePage)
	enum { IDD = IDD_PAGE_FINAL_STORAGE };
	CListBox	m_FSList;
	int		m_CR10WriteFSFreq;
	int		m_SaveFSFreq;
	int		m_wChamber;
	int		m_nDataPoints;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFinalStoragePage)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFinalStoragePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeWChamber();
	afx_msg void OnSelchangeNewFsFile();
	afx_msg void OnImportFsl();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeFsFrequency();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINALSTORAGEPAGE_H__85E90368_2CDE_11D5_B690_0080AD8FBDCC__INCLUDED_)
