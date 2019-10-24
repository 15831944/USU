/*****************************************************************************
*
*  File:          TestPackageDlg.h
*  Class:         TestPackageDlg
*  Project:       Distributed Calendaring System
*  Author:        Stephen W. Clyde
*  Last Modified: September 5, 2001
*
*  Modification History:
*  	Sep. 5, 2001	Initial version
*
*  Description:
*
*/

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CTestPackageDlg dialog

class CTestPackageDlg : public CDialog
{
// Construction
public:
	void DisplayMessage(const CString& msg);
	CTestPackageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestPackageDlg)
	enum { IDD = IDD_TESTPACKAGE_DIALOG };
	CEdit	m_ctl_log;
	BOOL	m_test_DString;
	BOOL	m_test_Event;
	BOOL	m_test_Configuration;
	BOOL	m_test_strdup;
	BOOL	m_test_ComChannel;
	BOOL	m_test_ClientComChannel;
	BOOL	m_test_ServerComChannel;
	BOOL	m_test_Building;
	BOOL	m_test_TimeOfDay;
	BOOL	m_test_Calendar;
	BOOL	m_test_CalendarDate;
	BOOL	m_test_TimeBlock;
	BOOL	m_test_User;
	BOOL	m_test_Location;
	BOOL	m_test_ReservedTime;
	BOOL	m_test_PersistentObjectSet;
	BOOL	m_test_LogicalClock;
	BOOL	m_test_SocketAddress;
	BOOL	m_test_Message;
	BOOL	m_test_MeetingPreference;
	BOOL	m_test_Reply;
	BOOL	m_test_Request;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPackageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestPackageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTestButton();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
