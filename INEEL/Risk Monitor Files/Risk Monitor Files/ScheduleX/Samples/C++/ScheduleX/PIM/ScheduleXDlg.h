// ScheduleXDlg.h : header file
//
//{{AFX_INCLUDES()
#include "pvcalendar.h"
#include "pvtaskpad.h"
#include "pvdayview.h"
//}}AFX_INCLUDES

#if !defined(AFX_SCHEDULEXDLG_H__D058DDF7_0971_11D3_9C61_00A0CC3A1AD6__INCLUDED_)
#define AFX_SCHEDULEXDLG_H__D058DDF7_0971_11D3_9C61_00A0CC3A1AD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CScheduleXDlg dialog

class CScheduleXDlg : public CDialog
{
// Construction
public:
	CScheduleXDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScheduleXDlg)
	enum { IDD = IDD_SCHEDULEX_DIALOG };
	CPVCalendar	m_calendar;
	CPVTaskPad	m_taskpad;
	CPVDayView	m_dayview;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScheduleXDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	typedef struct tagHolidays
	{
		CString Holiday;
		COleDateTime Date;
	} HOLIDAYS;

	HOLIDAYS m_Holidays[23];
	HICON m_hIcon;
	void AddHolidays();
	void GetHolidays();

	// Generated message map functions
	//{{AFX_MSG(CScheduleXDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCHEDULEXDLG_H__D058DDF7_0971_11D3_9C61_00A0CC3A1AD6__INCLUDED_)
