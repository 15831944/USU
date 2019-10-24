#if !defined(AFX_INPUTLOCATIONSPAGE_H__4D1AD4A0_2CE3_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_INPUTLOCATIONSPAGE_H__4D1AD4A0_2CE3_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputLocationsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputLocationsPage dialog

class CInputLocationsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CInputLocationsPage)

// Construction
public:
	BOOL IsModified;
	void SetModified(BOOL=TRUE);
	CInputLocationsPage();
	~CInputLocationsPage();

	void ResetGroupTimer();							// input locations page
	void SetTimeSensitiveLocationsData();			// input locations page
	void EnableInputLocations(BOOL enable);			// input locations page
	void SetLocationsData(BOOL updateData = TRUE);	// input locations page
	void SetDocument(CLADAControlModuleDoc * doc);
	void SetStrings(BOOL updateData = TRUE);		// all

	CLADAControlModuleDoc * pDoc;					// all

// Dialog Data
	//{{AFX_DATA(CInputLocationsPage)
	enum { IDD = IDD_PAGE_INPUT_LOCATIONS };
	CListCtrl	m_InputLocations;
	CComboBox	m_cGroup;
	int		m_wGroup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CInputLocationsPage)
	public:
	virtual BOOL OnKillActive();
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CInputLocationsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnProperties();
	afx_msg void OnNew();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTLOCATIONSPAGE_H__4D1AD4A0_2CE3_11D5_B690_0080AD8FBDCC__INCLUDED_)
