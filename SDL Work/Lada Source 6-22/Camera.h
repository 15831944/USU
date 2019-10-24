#if !defined(AFX_CAMERA_H__3A746C00_F672_11D4_8BFB_0020781F78D7__INCLUDED_)
#define AFX_CAMERA_H__3A746C00_F672_11D4_8BFB_0020781F78D7__INCLUDED_
#include "LADA Control ModuleDoc.h"
#include "TwainCpp.h"
#include "DIB.h"	// Added by ClassView

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Camera.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCamera dialog
class CCameraStatus;
class CImageBuffer;
class CCamera : public CDialog, public CTwain
{
// Construction
public:
	void TestLoadPicture();
	BOOL m_TwainInitialized;
	HANDLE hStatusThread;
	BOOL isAutoPicture;
	void CloseStatusWindow();
	void CreateStatusWindow();
	BOOL IsCanceled;
	CTime startTime;
	CCameraStatus * m_ptrStatus;
	HANDLE cameraSuccessEvent;
	BOOL AutoPicture(int which_camera);
	BOOL TakePicture(int wChamber);
	void SendEnter();
	void SetStrings();
	CDIB m_Dib;
	void SetDocument(CLADAControlModuleDoc * doc);
	CLADAControlModuleDoc* pDoc;
	int m_nFiles;
	CString* m_PtrFileInfo;
	void GetFileList();
	BOOL Create(UINT nID, CWnd * pWnd = NULL)
        { return CDialog::Create(nID,pWnd);}
	
	CCamera(CLADAControlModuleDoc* doc, CWnd* pParent = NULL);   // standard constructor
	void LoadPicture(int a);
	CBitmap * ptrBitmap;
	CPalette* Palette;
	CString	m_SourceFolder;			//The String for the Source Folder
	virtual ~CCamera();
	virtual void CopyImage(HANDLE hBitmap,TW_IMAGEINFO& info);
	virtual void SetImage(HANDLE hBitmap,int bits);
	
// Dialog Data
	//{{AFX_DATA(CCamera)
	enum { IDD = IDD_CAMERA };
	CStatic	m_picture;
	CListCtrl	m_list;
	//}}AFX_DATA

public:
	CTime LastPictureTaken;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamera)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
protected:
// Implementation
//protected:

	// Generated message map functions
	//{{AFX_MSG(CCamera)
	public:
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnCameraa();
	afx_msg void OnCamerab();
	afx_msg void OnSave();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERA_H__3A746C00_F672_11D4_8BFB_0020781F78D7__INCLUDED_)
