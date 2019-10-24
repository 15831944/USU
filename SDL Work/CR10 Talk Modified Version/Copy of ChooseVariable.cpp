// ChooseVariable.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "ChooseVariable.h"
#include "global defs.h"
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// CChooseVariable dialog


CChooseVariable::CChooseVariable(Array<ExpressionItem *> *PVars, Array<Event> *PEvents, ExpressionItem *&var, CWnd* pParent )
	: CDialog(CChooseVariable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseVariable)
	m_ConstValue = 0.0;
	//}}AFX_DATA_INIT
	EventSelected = FALSE;
	ProgVarSelected = FALSE;
	ProgVariables = PVars;
	ProgEvents = PEvents;
	curEventNum = 0;
	curEvent = &((*ProgEvents)[curEventNum]);
	newVariable = &var;
	
	// newVariable will be assigned the address of an 
	// object using 'new', possibly a subExpression or already
	// existing progVariable.  It could be assigned the address
	// of a constant, which would be known only to an action item.
}


void CChooseVariable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseVariable)
	DDX_Control(pDX, IDC_VAR_VALUE_TEXT, m_VarValueText);
	DDX_Control(pDX, IDC_VAR_VALUE, m_VarValue);
	DDX_Control(pDX, IDC_CONST_VAR, m_ConstVar);
	DDX_Control(pDX, IDC_DELETE, m_Delete);
	DDX_Control(pDX, IDC_EVENT, m_Event);
	DDX_Control(pDX, IDC_NEW, m_New);
	DDX_Control(pDX, IDC_EVENT_VAR, m_EventVar);
	DDX_Control(pDX, IDC_PROG_VAR, m_ProgVar);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
	DDX_Text(pDX, IDC_CONST_VAR, m_ConstValue);
	DDV_MinMaxDouble(pDX, m_ConstValue, -1000000., 1000000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseVariable, CDialog)
	//{{AFX_MSG_MAP(CChooseVariable)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_CBN_SELCHANGE(IDC_EVENT, OnSelchangeEvent)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_NOTIFY(NM_CLICK, IDC_EVENT_VAR, OnClickEventVar)
	ON_NOTIFY(NM_CLICK, IDC_PROG_VAR, OnClickProgVar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseVariable message handlers

void CChooseVariable::OnDelete() 
{
	// TODO: Add your control notification handler code here
	
}

void CChooseVariable::OnEdit() 
{
	// TODO: Add your control notification handler code here
	
}

void CChooseVariable::OnSelchangeEvent() 
{
	// TODO: Add your control notification handler code here
	int newEvent = m_Event.GetCurSel();
	if (newEvent != CB_ERR){
		curEventNum = newEvent;
		curEvent = &((*ProgEvents)[curEventNum]);
		ShowCurrentEventInfo();
	}
}

void CChooseVariable::OnNew() 
{
	// TODO: Add your control notification handler code here
	
}

void CChooseVariable::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	curVarType = ConstValue;
	SetControls();
}

void CChooseVariable::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	curVarType = EventExp;
	SetControls();
}

void CChooseVariable::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	curVarType = ProgVar;
	SetControls();
}

void CChooseVariable::OnOK() 
{
	// TODO: Add extra validation here
	if (UpdateData(FROMSCREEN)){
		switch (curVarType){
		case ConstValue:
			{
			if (m_ConstValue == (double)(int) m_ConstValue)
				*newVariable = new IntConstant(int(m_ConstValue));
			else
				*newVariable = new DoubConstant(m_ConstValue);
			} break;
		case EventExp:
			{
				int pos = ((int) m_EventVar.GetFirstSelectedItemPosition()) - 1;
				if (pos >= 0){
					*newVariable = new SubExpression(curEvent->Statements[pos], &curEvent->Statements[pos].ExpDescription);
						//+ (curEvent->Statements[pos].EvaluateTF() ? " (TRUE) " : " (FALSE) ")));
				}
			} break;
		case ProgVar:
			{
				int pos = ((int) m_ProgVar.GetFirstSelectedItemPosition()) - 1;
				if (pos >= 0){
					*newVariable = (*ProgVariables)[pos];
						//+ (curEvent->Statements[pos].EvaluateTF() ? " (TRUE) " : " (FALSE) ")));
				}
			} break;
		}
	}
	if (!(*newVariable)){
		if (MessageBox("No value selected.  Do you wish to cancel the current operation?",NULL,MB_ICONQUESTION |MB_YESNO) != IDYES)
			return;		
	}		
	CDialog::OnOK();
}

BOOL CChooseVariable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	curVarType = NoSelection;

	for (int i = 0; i < nPEvents; i++){
		m_Event.AddString((*ProgEvents)[i].Title);
	}
	
	m_EventVar.InsertColumn(0,"Number",LVCFMT_LEFT, 50, 1);
	m_EventVar.InsertColumn(1,"Title",LVCFMT_LEFT, 100, 2);
	m_EventVar.InsertColumn(2,"Value",LVCFMT_LEFT, 60, 3);

	m_ProgVar.InsertColumn(0,"Program Variable",LVCFMT_LEFT, 100, 1);
	m_ProgVar.InsertColumn(1,"Value",LVCFMT_LEFT, 80, 2);

	ShowCurrentEventInfo();
	ShowCurrentVariableInfo();
	SetControls();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChooseVariable::ShowCurrentVariableInfo(){
	m_ProgVar.DeleteAllItems();
	for (int i = 0; i < ProgVariables->length; i++){
		m_ProgVar.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, i, NULL, 0, LVIS_SELECTED, 0, 0);
		m_ProgVar.SetItemText(i, 0, *(*ProgVariables)[i]->GetItemText());
		m_ProgVar.SetItemText(i, 1, (*ProgVariables)[i]->ValueToString());
		
	}
}

void CChooseVariable::ShowCurrentEventInfo(){
	m_EventVar.DeleteAllItems();
	for (int i = 0; i < curEvent->nStatements; i++){
		char e[10];
		m_EventVar.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, i, NULL, 0, LVIS_SELECTED, 0, 0);
		wsprintf(e,"%i",i + 1);
		m_EventVar.SetItemText(i, 0, e);
		m_EventVar.SetItemText(i, 1, curEvent->Statements[i].ExpDescription);
		ExpressionItem *curValue = curEvent->Statements[i].Evaluate();
		m_EventVar.SetItemText(i, 2, (LPCSTR) *curValue->GetItemText());
	}
}

void CChooseVariable::SetControls()
{
	m_ConstVar.EnableWindow(curVarType == ConstValue);
	m_Event.EnableWindow(curVarType == EventExp);
	m_EventVar.EnableWindow(curVarType == EventExp);
	m_ProgVar.EnableWindow(curVarType == ProgVar);
	m_New.EnableWindow(curVarType == EventExp || curVarType == ProgVar);	
	m_Delete.EnableWindow(
		(curVarType == EventExp || curVarType == ProgVar) 
		&& (EventSelected || ProgVarSelected));
	m_Edit.EnableWindow(
		(curVarType == EventExp || curVarType == ProgVar) 
		&& (EventSelected || ProgVarSelected));
	m_VarValue.EnableWindow(curVarType != NoSelection);
	m_VarValue.ShowWindow((curVarType == ProgVar || curVarType == EventExp) ? SW_SHOW : SW_HIDE);
	m_VarValueText.ShowWindow((curVarType == ProgVar || curVarType == EventExp) ? SW_SHOW : SW_HIDE);

	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(curVarType == ConstValue);
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(curVarType == EventExp);
	((CButton *)GetDlgItem(IDC_RADIO3))->SetCheck(curVarType == ProgVar);
}

void CChooseVariable::ClickList(CListCtrl &wList){
	DWORD pos = GetMessagePos();
	CPoint pt(LOWORD(pos), HIWORD(pos));
	wList.ScreenToClient(&pt);

	// Get indexes of the first and last visible items in listview
	// control.
	int index = wList.GetTopIndex();
	int last_visible_index = index + wList.GetCountPerPage();
	if (last_visible_index > wList.GetItemCount())
	last_visible_index = wList.GetItemCount();

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
			wList.SetSelectionMark(index);
			break;
		}

		// Get the next item in listview control.
		index++;
	}

}

void CChooseVariable::OnClickEventVar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ClickList(m_EventVar);
	int pos = ((int) m_EventVar.GetFirstSelectedItemPosition()) - 1;
	EventSelected = (pos >= 0);
	SetControls();
	*pResult = 0;
}

void CChooseVariable::OnClickProgVar(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ClickList(m_ProgVar);
	int pos = ((int) m_ProgVar.GetFirstSelectedItemPosition()) - 1;
	ProgVarSelected = (pos >= 0);
	SetControls();
	*pResult = 0;
}
