// EditExpression.cpp : implementation file
//

#include "stdafx.h"
#include "EditCondition.h"
#include "ChooseItem.h"
#include "global defs.h"
#include "Event.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

/////////////////////////////////////////////////////////////////////////////
// EditExpression dialog


EditExpression::EditExpression(Array<Event> *pEvents, Event *cEvent, Expression &whichExpression, CWnd *pParent /*= NULL*/, char * expDesc/*=NULL*/) 
	: CDialog(EditExpression::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditExpression)
	m_ExpDescription = _T("");
	m_Double = 0.0;
	//}}AFX_DATA_INIT
	
	/**/
	curExpression = &whichExpression;
	if (expDesc)
		curExpression->ExpDescription = expDesc;
	curEvent = cEvent;
	curItem = 0;
	progEvents = pEvents;
	IsEventSelected = FALSE;
	EventSelected = NULL;
	TextPos[0] = 0;
	
	for (int i = 1; i < 20; i++){
		if (i < curExpression->nItems + 1){
			TextPos[i] = TextPos[i - 1] + curExpression->GetText(i - 1)->GetLength();
			condText.Insert(TextPos[i - 1],(*curExpression->GetText(i - 1)));
		}
		else
			TextPos[i] = TextPos[i - 1];
	}
	
}

BOOL EditExpression::OnInitDialog(){
	CDialog::OnInitDialog();
	
	for (int i = 0; i < 6; i++){
	
		//int rValue = 
		m_Item_List.AddString(ExpressionItems[i]);
	}
	m_Spin1.SetRange(-10, 20);
	
	m_ExpDescWnd.SetWindowText(curExpression->ExpDescription);
	m_CStatement.SetWindowText(curExpression->ToString());
	//m_Item_List.SetCurSel(VariableItem);
	
	//OnSelchangeItemList();

	return TRUE;//FALSE; // unless the focus is explicitly set to a control
}

void EditExpression::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditExpression)
	DDX_Control(pDX, IDC_RENAME_STATEMENT, m_ExpDescWnd);
	DDX_Control(pDX, IDC_VALUE, m_Value);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_EDIT_NUMBER, m_EditNumber);
	DDX_Control(pDX, IDC_CONDITIONAL_STATEMENT, m_CStatement);
	DDX_Control(pDX, IDC_DIRECTION_TEXT, m_DirectionText);
	DDX_Control(pDX, IDC_VARIABLE, m_Variable);
	DDX_Control(pDX, IDC_ITEM_LIST, m_Item_List);
	DDX_Text(pDX, IDC_RENAME_STATEMENT, m_ExpDescription);
	DDV_MaxChars(pDX, m_ExpDescription, 30);
	DDX_Text(pDX, IDC_EDIT_NUMBER, m_Double);
	DDV_MinMaxDouble(pDX, m_Double, -100000000., 100000000.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditExpression, CDialog)
	//{{AFX_MSG_MAP(EditExpression)
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, OnSelchangeItemList)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EVALUATE, OnEvaluate)
	ON_CBN_SELCHANGE(IDC_VARIABLE, OnSelchangeVariable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditExpression message handlers

void EditExpression::OnSelchangeItemList() 
{
	//m_Item_List.SetFocus();
	m_Variable.ResetContent();
	int CurSel;
	if ((CurSel = m_Item_List.GetCurSel()) != LB_ERR){
		switch (CurSel){
		case VariableItem: 
		case OperatorItem: 
		case RelOperatorItem: 
		case Parenthesis:
			{
 			m_Variable.EnableWindow(TRUE);
			m_Variable.ShowWindow(SW_SHOW);
			m_EditNumber.EnableWindow(FALSE);
			m_EditNumber.ShowWindow(SW_HIDE);
			for (int i = 0; i < 6; i++)
				m_Variable.AddString(ExpressionItemsSpecific[CurSel][i]);
			m_Variable.SetFocus();
			m_Variable.SetCurSel(0);
			}
			break;
		case ConstantValue:
			{
			m_Variable.EnableWindow(FALSE);
			m_Variable.ShowWindow(SW_HIDE);
			m_EditNumber.SetWindowText("");
			m_EditNumber.EnableWindow(TRUE);
			m_EditNumber.ShowWindow(SW_SHOW);
			m_EditNumber.SetFocus();
			}
			break;
		case SubExpressionItem:
			{
			m_Variable.EnableWindow(TRUE);
			m_Variable.ShowWindow(SW_SHOW);
			m_EditNumber.EnableWindow(FALSE);
			m_EditNumber.ShowWindow(SW_HIDE);
			for (int i = 0; i < nPEvents; i++)
				m_Variable.AddString((*progEvents)[i].Title);
			}
			break;
		}
		IsEventSelected = FALSE;
		m_DirectionText.SetWindowText(InstructionText[CurSel]);
	
	}
}

void EditExpression::OnInsert() 
{
	// TODO: Add your control notification handler code here
	
	int ListItem = m_Item_List.GetCurSel();
	int List2Item = m_Variable.GetCurSel();
	
	int nItemsAtStart = curExpression->nItems ;
	ExpressionItem *newItem = NULL;

	switch (ListItem){
	case VariableItem:
		switch (List2Item){
		case InputLocation:
			{// choose which input location
			int whichLocation = -1;
			CChooseItem selList(&whichLocation, InputLocSaveRequests, NULL, "Select Input Location",this); 
			selList.DoModal(); 
			if (whichLocation >= 0)// add to the list		   
				newItem = new InputLoc(whichLocation);
			}
			break;
		case FlagValue:
			{// choose flag
			int whichFlag = -1;
			CString FlagList[16];
			for (int i = 0; i < 2; i++){
				for (int j = 0; j < 8; j++){
					FlagList[i*8+j] = FlagNames[j][i];
				}
			}
			CChooseItem selList(&whichFlag, 16, FlagList,"Select Flag",this);
			selList.DoModal();
			if (whichFlag >= 0)
				newItem = new Flag(whichFlag % 8, whichFlag / 8);
			}
			break;
		case ProgramRunTimeVar:
			{
			newItem = new ProgRunTime;
			}
			break;
		case TimerVariable:
			{
			CString TimerList[6];
			char tText[10];
			for (int i = 0; i < curEvent->nTimers; i++){
				wsprintf(tText,"Timer %i",i+1);
				//strcpy(TimerList[i],tText);
				TimerList[i] = tText;
			}
			if (i < 5) // i < MAX_TIMERS
				TimerList[i] = "Create New Timer";
			int tChoice = -1;
			CChooseItem selList(&tChoice, i+1, TimerList,"Select Timer",this);
			selList.DoModal();
			if (tChoice >= 0){
				if (tChoice == curEvent->nTimers) {
					// then we should create a new timer
				}
				
				newItem = new Timer(tChoice + 1);
			}
			}
			break;
		}
		break;
	case OperatorItem:
		{
		if (List2Item > Modulus)
			break;
		newItem = new Operator((Operators)List2Item);
		}break;
	case RelOperatorItem:
		{
		if (List2Item > GreaterThanOrEqual){
			MessageBox("Please select a valid list box item");
			break;
		}
		newItem = new RelOperator((RelOperators)List2Item);
		}
		break;
	case ConstantValue:
		{
		if (UpdateData(TRUE)){
			if (m_Double == (double)(int)m_Double)
				newItem = new IntConstant(int(m_Double));
			else 
				newItem = new DoubConstant(m_Double);//, intBuf);
		}
		}
		break;
	case Parenthesis:
		{
		if (List2Item == 0)
			newItem = new LPthesis;
		else if (List2Item == 1)
			newItem = new RPthesis;
		}
		break;
	case SubExpressionItem:
		{
			if (IsEventSelected && List2Item < EventSelected->nStatements)
				newItem = new SubExpression(&EventSelected->Statements[List2Item],&EventSelected->Statements[List2Item].ExpDescription);
		}
		break;
	}
	
	if (newItem)
		curExpression->InsertItem(newItem, curItem);
	else 
		MessageBox("Please select a valid list box item");
	

	if (curExpression->nItems != nItemsAtStart){
		
		int wordLength = curExpression->GetText(curItem)->GetLength();
		condText.Insert(TextPos[curItem],(*curExpression->GetText(curItem)) );
		for (int i = 19; i > curItem; i--){
			TextPos[i] = TextPos[i-1] + wordLength;
		}
		m_CStatement.SetWindowText(condText);
		if (curItem == curExpression->nItems - 1)
			curItem++;
		ShowHighlightedItem();
	}
	
}

void EditExpression::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	if (curExpression->nItems > 0){
		curItem += pNMUpDown->iDelta;
		if (curItem > curExpression->nItems)
			curItem = curExpression->nItems;
		if (curItem < 1)
			curItem = 0;
		ShowHighlightedItem();
	}
	
	*pResult = 1;
}

void EditExpression::ShowHighlightedItem(){
	m_CStatement.SetSel(TextPos[curItem], TextPos[curItem + 1]);
}

void EditExpression::OnDelete() 
{
	// TODO: Add your control notification handler code here
	
	if (curExpression->nItems > 0 && curItem < curExpression->nItems) {
		//char newWord[30];
		//strcpy(newWord,curExpression->GetText(curItem));
		int wordLength = curExpression->GetText(curItem)->GetLength();
		//strlen(newWord);
		condText.Delete(TextPos[curItem],wordLength);
		for (int i = curItem + 1; i < 20; i++){
			TextPos[i] = TextPos[i+1] - wordLength;
		}
		m_CStatement.SetWindowText(condText);
		curExpression->RemoveItem(curItem);
		ShowHighlightedItem();
	}
	
}

void EditExpression::OnEvaluate() 
{
	// TODO: Add your control notification handler code here
	
	if (curExpression->CheckExpression()){
		ExpressionItem * result = curExpression->Evaluate();	
		ShowItem(&m_Value, result);
	}
	
	
}

void EditExpression::ShowExpression(CWnd * textWnd, Expression * whichExp ){
	textWnd->SetWindowText(whichExp->ToString());
}

void EditExpression::ShowItem(CWnd * textWnd, ExpressionItem * eItem){
	//const char *text = eItem->GetItemText();
	textWnd->SetWindowText(*eItem->GetItemText());//text);
}



void EditExpression::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(FROMSCREEN);
	curExpression->ExpDescription = m_ExpDescription;
	
	if (!curExpression->CheckExpression()){
		if (MessageBox("The current expression cannot be evaluated.  Exit anyway?","Error",MB_ICONQUESTION | MB_YESNO) != IDYES)
			return;
	}
	CDialog::OnOK();
}

void EditExpression::OnSelchangeVariable() 
{
	// TODO: Add your control notification handler code here
	int CurSel;
	if ((CurSel = m_Item_List.GetCurSel()) != LB_ERR){
		switch (CurSel){
		case VariableItem: 
		case OperatorItem: 
		case RelOperatorItem: 
		case Parenthesis:
		case ConstantValue:
			break;
		case SubExpressionItem:
			{
			if ((CurSel = m_Variable.GetCurSel()) != LB_ERR && IsEventSelected == FALSE)
			{
				EventSelected = &(*progEvents)[CurSel];
				if (EventSelected->nStatements > 0){
					IsEventSelected = TRUE;
					m_Variable.ResetContent();
					for (int i = 0; i < EventSelected->nStatements; i++)
						m_Variable.AddString(EventSelected->Statements[i].ToString());
					m_Variable.SetFocus();
					m_Variable.SetCurSel(0);
					m_DirectionText.SetWindowText("Please select an expression");
				} else
					MessageBox("There are no events associated with this event.");
			
				return;
			}
			break;
			}
		}
	}

}
