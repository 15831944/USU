// EditEvent.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditEvent.h"
#include "EditCondition.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// EditEvent dialog


EditEvent::EditEvent(Array<Event> *pEvents, CWnd* pParent /*=NULL*/)
	: CDialog(EditEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditEvent)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	Events = pEvents;
	
	whichEvent = 0;
	curEvent = &((*Events)[whichEvent]);
	// ProgramEvents is: Array<Event> *ProgramEvents

}


void EditEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditEvent)
	DDX_Control(pDX, IDC_CONTROL_LIST, m_CtrlList);
	DDX_Control(pDX, IDC_CONDITIONAL_LIST, m_ExpList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditEvent, CDialog)
	//{{AFX_MSG_MAP(EditEvent)
	ON_LBN_SELCHANGE(IDC_CONDITIONAL_LIST, OnSelchangeExpressionList)
	ON_LBN_DBLCLK(IDC_CONDITIONAL_LIST, OnDblclkExpressionList)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DELETE_STATEMENT, OnDeleteStatement)
	ON_BN_CLICKED(IDC_DELETE_TEST, OnDeleteTest)
	ON_CBN_SELCHANGE(IDC_EVENT_TITLE, OnSelchangeEventTitle)
	ON_BN_CLICKED(IDC_NEW_EVENT, OnNewEvent)
	ON_BN_CLICKED(IDC_NEW_TEST, OnNewTest)
	ON_BN_CLICKED(IDHELP, OnHelp)
	ON_BN_CLICKED(IDC_EDIT_STATEMENT, OnEditStatement)
	ON_BN_CLICKED(IDC_EDIT_TEST, OnEditTest)
	ON_BN_CLICKED(IDC_RENAME_EVENT, OnRenameEvent)
	ON_BN_CLICKED(IDC_NEW_STATEMENT, OnNewStatement)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditEvent message handlers

void EditEvent::OnSelchangeExpressionList() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnDblclkExpressionList() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL EditEvent::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	return CDialog::OnHelpInfo(pHelpInfo);
}

void EditEvent::OnDeleteStatement() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnDeleteTest() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnSelchangeEventTitle() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnNewEvent() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnNewTest() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void EditEvent::OnHelp() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

BOOL EditEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//ShowCurrentEventInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}


void EditEvent::ShowCurrentEventInfo(){
	m_ExpList.ResetContent();
	for (int i = 0; i < curEvent->nStatements; i++)
		m_ExpList.AddString(curEvent->Statements[i].ExpDescription 
		+ ": " + curEvent->Statements[i].ToString());

}

void EditEvent::OnEditStatement() 
{
	// TODO: Add your control notification handler code here
	/*
	int curSel;
	if ((curSel = m_ExpList.GetCurSel()) != LB_ERR){
		EditExpression editExpression(curEvent, curEvent->Statements[curSel], this);
		editExpression.DoModal();
		ShowCurrentEventInfo();	
	}	
	else 
		MessageBox("Please select a statement to edit it.",NULL,MB_ICONINFORMATION);
	*/
 }

void EditEvent::OnEditTest() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnRenameEvent() 
{
	// TODO: Add your control notification handler code here
	
}

void EditEvent::OnNewStatement() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	/*
	curEvent->nStatements++;
	if (curEvent->nStatements > curEvent->Statements.length)
		curEvent->Statements(curEvent->nStatements + 2);
	EditExpression newExpression(curEvent, curEvent->Statements[curEvent->nStatements - 1], this);
	newExpression.DoModal();
	ShowCurrentEventInfo();
	*/
	curEvent->nStatements++;
	EditExpression newExpression(curEvent, curEvent->Statements[curEvent->nStatements - 1], this);
	newExpression.DoModal();
}
