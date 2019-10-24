// NewEvent.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "NewEvent.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
/////////////////////////////////////////////////////////////////////////////
// NewEvent dialog


NewEvent::NewEvent(char *newTitle, CWnd* pParent /*=NULL*/)
	: CDialog(NewEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(NewEvent)
	m_EventTitle = _T("");
	//}}AFX_DATA_INIT
	m_EventTitle = newTitle;
	AddTitle = newTitle;
}


void NewEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NewEvent)
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Text(pDX, IDC_EDIT1, m_EventTitle);
	DDV_MaxChars(pDX, m_EventTitle, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NewEvent, CDialog)
	//{{AFX_MSG_MAP(NewEvent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewEvent message handlers

void NewEvent::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	strcpy(AddTitle, m_EventTitle);
	CDialog::OnOK();
}

void NewEvent::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL NewEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	UpdateData(FALSE);
	m_Edit1.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
