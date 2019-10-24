// Assignment 3Dlg.h : header file
//


#if !defined(AFX_ASSIGNMENT3DLG_H__07ED1466_4F76_11D4_B01D_C9D7E1D3C933__INCLUDED_)
#define AFX_ASSIGNMENT3DLG_H__07ED1466_4F76_11D4_B01D_C9D7E1D3C933__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "record.h"
#include "Binary Search Tree.h"
#include "Resource.h"

/////////////////////////////////////////////////////////////////////////////
// CAssignment3Dlg dialog
#define		TOSCREEN	FALSE
#define		FROMSCREEN	TRUE

#define		NColumns	6

class CAssignment3Dlg : public CDialog
{
// Construction
public:
	CAssignment3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAssignment3Dlg)
	enum { IDD = IDD_ASSIGNMENT3_DIALOG };
	CButton	m_Save;
	CButton	m_SaveAs;
	CListCtrl	m_Names;
	CString	m_BirthDate;
	CString	m_FirstName;
	CString	m_Address1;
	CString	m_Address2;
	CString	m_PhoneNumber;
	CString	m_LastName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAssignment3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void ShowAllRecords();
	void Close();
	void ShowRecord(CString array[], int pos);
	int BinFindText(Record searchKey, int start, int end);
	void EnableSave(BOOL e = TRUE);
protected:
	HICON m_hIcon;
	BinarySearchTree< Record > AddressBook;
	int m_nRecords;
	BOOL PerformUpdate;
	CString filePath;
	BOOL Modified;
	void UpdateRecord(int pos);
	
	// Generated message map functions
	//{{AFX_MSG(CAssignment3Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddRecord();
	afx_msg void OnRemove();
	afx_msg void OnOpen();
	afx_msg void OnSave();
	afx_msg void OnSaveas();
	afx_msg void OnExit();
	afx_msg void OnClickNames(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateRecord();
	afx_msg void OnEditUpdaterecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASSIGNMENT3DLG_H__07ED1466_4F76_11D4_B01D_C9D7E1D3C933__INCLUDED_)
