// ChangeLocationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lada control module.h"
#include "ChangeLocationDlg.h"

#include "CommOperations.h"
#include "LADA Control ModuleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString ValueToString(double value, int dPlaces = 2);
/////////////////////////////////////////////////////////////////////////////
// CChangeLocationDlg dialog


CChangeLocationDlg::CChangeLocationDlg(CLADAControlModuleDoc *ptrDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CChangeLocationDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeLocationDlg)
	m_wLocation = 0;
	m_value = 0.0;
	m_newValue = 0.0;
	//}}AFX_DATA_INIT
	pDoc = ptrDoc;
	commObject = pDoc->commObject;
}


void CChangeLocationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeLocationDlg)
	DDX_Text(pDX, IDC_EDIT1, m_wLocation);
	DDV_MinMaxInt(pDX, m_wLocation, 1, 255);
	DDX_Text(pDX, IDC_EDIT2, m_value);
	DDX_Text(pDX, IDC_EDIT3, m_newValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeLocationDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeLocationDlg)
	ON_BN_CLICKED(IDC_GETVALUE, OnGetvalue)
	ON_BN_CLICKED(IDC_SETVALUE, OnSetvalue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeLocationDlg message handlers

void CChangeLocationDlg::OnGetvalue() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	pDoc->StartCommBlock();
	commObject->ExecuteICommand(m_wLocation, m_value, NULL);
	pDoc->EndCommBlock();
	UpdateData(FALSE);
}

void CChangeLocationDlg::OnSetvalue() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CString nValue = ValueToString(m_newValue,4);
	char *newValue = nValue.GetBufferSetLength(10);
	
	//wsprintf(newValue,"%i",12);
	pDoc->StartCommBlock();
	commObject->ExecuteICommand(m_wLocation, m_value, newValue);
	pDoc->EndCommBlock();
	UpdateData(FALSE);

}
