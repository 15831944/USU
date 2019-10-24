#if !defined(AFX_CAMERASTATUS_H__41839A80_24FC_11D5_B690_0080AD8FBDCC__INCLUDED_)
#define AFX_CAMERASTATUS_H__41839A80_24FC_11D5_B690_0080AD8FBDCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCameraStatus dialog

class CCameraStatus : public CDialog
{
// Construction
public:
	void SetStartTime(CTime & time);
	void KillWindow();
	CTime StartTime;
	BOOL m_Initialized;
	int curMessageID;
	void SetStrings();
	void SetMessage(unsigned int messageID);
	void EnableCancelButton(BOOL Enable);
	BOOL * IsCanceled;
	CCameraStatus(BOOL *canceled, CWnd* pParent = NULL);   // standard constructor
	BOOL Create(UINT nID, CWnd * pWnd = NULL)					// Creates a progress bar
        { return CDialog::Create(nID,pWnd);}

// Dialog Data
	//{{AFX_DATA(CCameraStatus)
	enum { IDD = IDD_PICTURE_STATUS };
	CString	m_TimeElapsed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCameraStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCameraStatus)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERASTATUS_H__41839A80_24FC_11D5_B690_0080AD8FBDCC__INCLUDED_)
