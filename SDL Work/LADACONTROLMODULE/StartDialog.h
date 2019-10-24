#if !defined(AFX_STARTDIALOG_H__814DCC63_7F55_11D4_98DF_00A076801ACD__INCLUDED_)
#define AFX_STARTDIALOG_H__814DCC63_7F55_11D4_98DF_00A076801ACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartDialog.h : header file
//

#define IDC_BFRAME 1001

/////////////////////////////////////////////////////////////////////////////
// CStartDialog dialog

typedef struct {    
	WORD      dlgVer;   
	WORD      signature; 
	DWORD     helpID;   
	DWORD     exStyle;   
	DWORD     style; 
	WORD      cDlgItems;   
	short     x;   
	short     y;   
	short     cx; 
	short     cy;   
	WORD	  menu[1];   
	WORD	  windowClass[1]; 
	WCHAR     title[40]; 
// The following members exist only if the style member is 
// set to DS_SETFONT or DS_SHELLFONT.  
	WORD     pointsize;   
	WORD     weight; 
	BYTE     italic;  
	BYTE     charset;   
	WCHAR    typeface[40];  
} DLGTEMPLATEEX; 

class CStartDialog : public CDialog
{
// Construction
public:
	CStartDialog(UINT *r, CWnd* pParent = NULL);   // standard constructor
	void SetStrings();
	CBitmap * ProgramIcon;
	CStatic BitmapBorder;
	CStatic Border;
	CStatic Welcome;
	CStatic Button1Help;
	CStatic Button2Help;
	CStatic Button3Help;
	CStatic Button4Help;
	CStatic Button5Help;
	CStatic Button6Help;
	CStatic Button7Help;
	CButton Button1;
	CButton Button2;
	CButton Button3;
	CButton Button4;
	CButton Button5;
	CButton Button6;
	CButton Button7;
	UINT *result;
// Dialog Data
	//{{AFX_DATA(CStartDialog)
	enum { IDD = IDR_MAINFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStartDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	DLGTEMPLATEEX DlgTemplate;
	// Generated message map functions
	//{{AFX_MSG(CStartDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg void OnButton(UINT nID);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTDIALOG_H__814DCC63_7F55_11D4_98DF_00A076801ACD__INCLUDED_)
