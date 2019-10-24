// EditEvent.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "EditEvent.h"
#include "EditCondition.h"
#include "EditTest.h"
#include "NewEvent.h"
#include "global defs.h"
#include "RenameLocation.h"
#include "ProgramVariables.h"


/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// EditEvent dialog


EditEvent::EditEvent(Array<ExpressionItem *> *PVariables, Array<Event> *pEvents, CWnd* pParent /*=NULL*/)
	: CDialog(EditEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditEvent)
	//}}AFX_DATA_INIT
	Events = pEvents;
	ProgVariables = PVariables;
		
	whichEvent = 0;
	curEvent = &((*Events)[whichEvent]);
	// ProgramEvents is: Array<Event> *ProgramEvents
	wStatus = 0;

}


void EditEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditEvent)
	DDX_Control(pDX, IDC_CONTROL_LIST, m_CtrlList);
	DDX_Control(pDX, IDC_EXPRESSION_LIST, m_ExpList);
	DDX_Control(pDX, IDC_RENAME_EVENT, m_RenameEvent);
	DDX_Control(pDX, IDC_NEW_TEST, m_NewTest);
	DDX_Control(pDX, IDC_NEW_STATEMENT, m_NewStatement);
	DDX_Control(pDX, IDC_NEW_EVENT, m_NewEvent);
	DDX_Control(pDX, IDC_EDIT_TEST, m_EditTest);
	DDX_Control(pDX, IDC_EDIT_STATEMENT, m_EditStatement);
	DDX_Control(pDX, IDC_DELETE_TEST, m_DeleteTest);
	DDX_Control(pDX, IDC_DELETE_STATEMENT, m_DeleteStatement);
	DDX_Control(pDX, IDC_EVENT_TITLE, m_EventTitle);
	DDX_Control(pDX, IDC_EVENT_NUMBER, m_EventNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditEvent, CDialog)
	//{{AFX_MSG_MAP(EditEvent)
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
	ON_NOTIFY(NM_CLICK, IDC_EXPRESSION_LIST, OnClickExpressionList)
	ON_NOTIFY(NM_CLICK, IDC_CONTROL_LIST, OnClickControlList)
	ON_BN_CLICKED(IDC_PROGRAM_VARIABLES, OnProgramVariables)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditEvent message handlers

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
	int newEvent = m_EventTitle.GetCurSel();
	if (newEvent != CB_ERR){
		whichEvent = newEvent;
		curEvent = &((*Events)[whichEvent]);
		// ProgramEvents is: Array<Event> *ProgramEvents
		wStatus = 0;
		ShowCurrentEventInfo();
	}
}

void EditEvent::OnNewEvent() 
{
	// TODO: Add your control notification handler code here
	char NewTitle[31];
	wsprintf(NewTitle, "Event %i",nPEvents + 1);
	NewEvent NewEventDlg(NewTitle, this);
	if (NewEventDlg.DoModal() == IDOK){
		whichEvent = nPEvents;
		curEvent = &((*Events)[whichEvent]);
		curEvent->Title = NewTitle;
		m_EventTitle.AddString(NewTitle);	
		
		// ProgramEvents is: Array<Event> *ProgramEvents
		wStatus = 0;
		nPEvents++;
		ShowCurrentEventInfo();
	}
	
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
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	m_ExpList.InsertColumn(0,"Number",LVCFMT_LEFT, 20, 1);
	m_ExpList.InsertColumn(1,"Title",LVCFMT_LEFT, 80, 2);
	m_ExpList.InsertColumn(2,"Expression",LVCFMT_LEFT, 150, 3);
	m_ExpList.InsertColumn(3,"Value",LVCFMT_LEFT, 60, 4);

	m_CtrlList.InsertColumn(0,"Number",LVCFMT_LEFT, 50, 1);
	m_CtrlList.InsertColumn(1,"Description",LVCFMT_LEFT, 250, 2);
	
	for (int i = 0; i < nPEvents; i++){
		m_EventTitle.AddString((*Events)[i].Title);
	}

	
	ShowCurrentEventInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void EditEvent::ShowCurrentEventInfo(){
	if (nPEvents > 0){
		char eNumber[3];
		wsprintf(eNumber,"%i",whichEvent + 1);
		m_EventNumber.SetWindowText(eNumber);

		m_EventTitle.SetCurSel(whichEvent);
		m_ExpList.DeleteAllItems();//ResetContent(); // THIS ALSO CLEARS A SELECTION, IF ONE IS MADE
		m_CtrlList.DeleteAllItems();
		for (int i = 0; i < curEvent->nStatements; i++){
			//m_ExpList.AddString(curEvent->Statements[i].ExpDescription 
			//+ ": " + curEvent->Statements[i].ToString());
			char e[5];
			m_ExpList.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, i, NULL, 0, LVIS_SELECTED, 0, 0);
			wsprintf(e,"%i",i + 1);
			m_ExpList.SetItemText(i, 0, e);
			m_ExpList.SetItemText(i, 1, curEvent->Statements[i].ExpDescription);
			m_ExpList.SetItemText(i, 2, curEvent->Statements[i].ToString());
			if (curEvent->Statements[i].IsComparison)
				m_ExpList.SetItemText(i, 3, curEvent->Statements[i].EvaluateTF() ? "True" : "False");
			else 
				m_ExpList.SetItemText(i, 3, *curEvent->Statements[i].Evaluate()->GetItemText());
	
		}

		int row = 0;
		for (i = 0; i < curEvent->nTests; i++){
			char e[5];
			m_CtrlList.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, row++, NULL, 0, LVIS_SELECTED, 0, 0);
			wsprintf(e,"%i",i + 1);
			m_CtrlList.SetItemText(row - 1, 0, e);
			for (int j = 0; j < curEvent->Tests[i].nFlow; j++){
				BoolExpression *curExp = &curEvent->Tests[i].BStatements[j];
				m_CtrlList.SetItemText(row - 1, 1,curExp->Expression::ToString());
				//for (int a = 0; a < curEvent->Tests[i].BStatements[j].nActions; a++){
				//	m_CtrlList.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, row++, NULL, 0, LVIS_SELECTED, 0, 0);
				//	m_CtrlList.SetItemText(row - 1, 1, "Do this..."/*curEvent->Statements[i].ToString()*/);
				//}
				m_CtrlList.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, row++, NULL, 0, LVIS_SELECTED, 0, 0);
				char firstline[200];
				wsprintf(firstline, "  Then %s", (curExp->nActions > 0 ? curExp->GetActionText(0) : " [do nothing]"));
				m_CtrlList.SetItemText(row - 1, 1, firstline);
				
				for (int a = 1; a < curExp->nActions; a++){
					m_CtrlList.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, row++, NULL, 0, LVIS_SELECTED, 0, 0);
					m_CtrlList.SetItemText(row - 1, 1, curExp->GetActionText(a));
				}
				testPos[i] = row - 1;
			}
			
		}
		wStatus |= EVENTENABLED;

		// if statements is below maxStatements
			wStatus |= NEWSTATEMENTS;
		// if tests is below maxTests
			wStatus |= NEWTESTS;
		
		// if a statement is selected
		if ( m_ExpList.GetFirstSelectedItemPosition())//m_ExpList.GetCurSel() != LB_ERR)
			wStatus |= STATEMENTSELECTED;
		else
			wStatus &= ~STATEMENTSELECTED;

		// if a test is selected
		if (m_CtrlList.GetFirstSelectedItemPosition())//trlList.GetCurSel() != LB_ERR)
			wStatus |= TESTSELECTED;
		else
			wStatus &= ~TESTSELECTED;


		SetButtonStatus(EVERYTHING);
	}
	else {
		SetButtonStatus(NOEVENTS);

	}
}

void EditEvent::SetButtonStatus(DWORD dwFlags){
	if (dwFlags == NOEVENTS){
		m_EventNumber.EnableWindow(FALSE);
		m_EventTitle.EnableWindow(FALSE);
		m_RenameEvent.EnableWindow(FALSE);
		m_ExpList.EnableWindow(FALSE);
		m_CtrlList.EnableWindow(FALSE);
		m_NewStatement.EnableWindow(FALSE);
		m_EditStatement.EnableWindow(FALSE);
		m_DeleteStatement.EnableWindow(FALSE);
		m_NewTest.EnableWindow(FALSE);
		m_EditTest.EnableWindow(FALSE);
		m_DeleteTest.EnableWindow(FALSE);
	}
	else {
		if (dwFlags & EVENTENABLED){
			m_ExpList.EnableWindow(wStatus & EVENTENABLED);
			m_CtrlList.EnableWindow(wStatus & EVENTENABLED);
			m_EventNumber.EnableWindow(wStatus & EVENTENABLED);
			m_EventTitle.EnableWindow(wStatus & EVENTENABLED);
			m_RenameEvent.EnableWindow(wStatus & EVENTENABLED);
		}
		
		if (dwFlags & STATEMENTSELECTED) {
			m_EditStatement.EnableWindow(wStatus & STATEMENTSELECTED);
			m_DeleteStatement.EnableWindow(wStatus & STATEMENTSELECTED);
		}
		if (dwFlags & NEWSTATEMENTS)
			m_NewStatement.EnableWindow(wStatus & NEWSTATEMENTS);

		if (dwFlags & TESTSELECTED) {
			m_EditTest.EnableWindow(wStatus & TESTSELECTED);
		m_DeleteTest.EnableWindow(wStatus & TESTSELECTED);
		}
		if (dwFlags & NEWTESTS)
			m_NewTest.EnableWindow(wStatus & NEWTESTS);
	}
}


void EditEvent::OnEditStatement() 
{
	// TODO: Add your control notification handler code here
	
	int curSel = (int) m_ExpList.GetFirstSelectedItemPosition();
	if (curSel){
		EditExpression editExpression(Events, curEvent, curEvent->Statements[curSel - 1], this);
		editExpression.DoModal();
		ShowCurrentEventInfo();	
	}	
	else 
		MessageBox("Please select a statement to edit it.",NULL,MB_ICONINFORMATION);
	
}

void EditEvent::OnEditTest() 
{
	// TODO: Add your control notification handler code here
	int cursPos = (int) m_CtrlList.GetFirstSelectedItemPosition();
	int curSel = curEvent->nTests;
	for (int i = 0; i < curEvent->nTests; i++){
		if (cursPos <= testPos[i]){
			curSel = i;
			break;
		}
	}
	if (curSel >= 0){
		EditTest editTest(ProgVariables, Events, curEvent, curEvent->Tests[curSel], curSel - 1, this);
		editTest.DoModal();
		ShowCurrentEventInfo();	
	}	
	else 
		MessageBox("Please select a test to edit it.",NULL,MB_ICONINFORMATION);
}

void EditEvent::OnRenameEvent() 
{
	// TODO: Add your control notification handler code here
	CString OldName = curEvent->Title;
	char newName[30] = {""};
	CRenameLocation cNewName(OldName, newName,
		"Event Title", "Rename Event Dialog", whichEvent + 1, TRUE, this );
	
	cNewName.DoModal();
	int selIndex = m_EventTitle.GetCurSel();
	m_EventTitle.DeleteString(selIndex);
	m_EventTitle.InsertString(selIndex, newName);
	m_EventTitle.SetCurSel(selIndex);
	curEvent->Title = newName;
}

void EditEvent::OnNewStatement() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	
	char e[20];
	wsprintf(e,"Expression %i",curEvent->nStatements + 1);
	EditExpression newExpression(Events, curEvent, curEvent->Statements[curEvent->nStatements], this, e);
	newExpression.DoModal();
	if (curEvent->Statements[curEvent->nStatements].nItems > 0)
		curEvent->nStatements++;
	ShowCurrentEventInfo();
}

void EditEvent::OnNewTest() 
{
	// TODO: Add your control notification handler code here
	curEvent->nTests++;
	//char e[20];
	//wsprintf(e,"Expression %i",curEvent->nStatements);
	EditTest newTest(ProgVariables, Events, curEvent, curEvent->Tests[curEvent->nTests - 1], curEvent->nTests - 1, this);
	newTest.DoModal();
	ShowCurrentEventInfo();
}

void EditEvent::ClickList(CListCtrl &wList, DWORD mask){
	DWORD pos = GetMessagePos();
      CPoint pt(LOWORD(pos), HIWORD(pos));
      wList.ScreenToClient(&pt);

      // Get indexes of the first and last visible items in listview
      // control.
      int index = wList.GetTopIndex();
      int last_visible_index = index + wList.GetCountPerPage();
      if (last_visible_index > wList.GetItemCount())
          last_visible_index = wList.GetItemCount();

	  wStatus &= ~mask;

      // Loop until number visible items has been reached.
      while (index <= last_visible_index)
      {
         // Get the bounding rectangle of an item. If the mouse
          // location is within the bounding rectangle of the item,
          // you know you have found the item that was being clicked.
          CRect r;
          wList.GetItemRect(index, &r, LVIR_BOUNDS);
          if (r.PtInRect(pt))
          {
              UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
              wList.SetItemState(index, flag, flag);
			  wStatus |= mask;
			  wList.SetSelectionMark(index);
              break;
          }

          // Get the next item in listview control.
          index++;
      }
	SetButtonStatus(mask);

}

void EditEvent::OnClickExpressionList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	// Get the current mouse location and convert it to client
      // coordinates.
    ClickList(m_ExpList,STATEMENTSELECTED);
	*pResult = 0;
}

void EditEvent::OnClickControlList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ClickList(m_CtrlList,TESTSELECTED);
	*pResult = 0;
}

void EditEvent::OnProgramVariables() 
{
	// TODO: Add your control notification handler code here
	ProgramVariables pDialog( ProgVariables, this);
	pDialog.DoModal();
}
