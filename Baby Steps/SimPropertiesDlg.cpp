// SimPropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Baby Steps.h"
#include "SimPropertiesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_ROWS	200
#define MAX_COLUMNS 200
/////////////////////////////////////////////////////////////////////////////
// CSimPropertiesDlg dialog


CSimPropertiesDlg::CSimPropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimPropertiesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSimPropertiesDlg)
	m_nColumns = 50;
	m_nRows = 50;
	//}}AFX_DATA_INIT
}


void CSimPropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSimPropertiesDlg)
	DDX_Text(pDX, IDC_N_COLUMNS, m_nColumns);
	DDX_Text(pDX, IDC_N_ROWS, m_nRows);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSimPropertiesDlg, CDialog)
	//{{AFX_MSG_MAP(CSimPropertiesDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimPropertiesDlg message handlers

void CSimPropertiesDlg::OnOK() 
{
	UpdateData();
	if (m_nRows < 2 || m_nRows >= MAX_ROWS)
	{	
		CString message;
		message.Format("Number of rows must be between 2 and %i",MAX_ROWS);
		MessageBox(message,"Input Error",MB_ICONINFORMATION);
		return;
	}
	if (m_nColumns < 2 || m_nColumns >= MAX_COLUMNS)
	{	
		CString message;
		message.Format("Number of columns must be between 2 and %i",MAX_ROWS);
		MessageBox(message,"Input Error",MB_ICONINFORMATION);
		return;
	}
	CDialog::OnOK();
}
