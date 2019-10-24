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


EditExpression::EditExpression(Event *cEvent, Expression &whichExpression, CWnd *pParent /*= NULL*/)
	: CDialog(EditExpression::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditExpression)
	m_ExpDescription = _T("");
	//}}AFX_DATA_INIT
	
	curExpression = &whichExpression;
	curEvent = cEvent;
	curItem = 0;
	
	
	TextPos[0] = 0;
	for (int i = 0; i < 20; i++){
		if (i < curExpression->nItems)
			TextPos[i + 1] = strlen(curExpression->GetText(i));
		else
			TextPos[i + 1] = TextPos[i];
	}
	
}

BOOL EditExpression::OnInitDialog(){
	CDialog::OnInitDialog();
	
	for (int i = 0; i < 5; i++){
	
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditExpression, CDialog)
	//{{AFX_MSG_MAP(EditExpression)
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, OnSelchangeItemList)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, OnDeltaposSpin1)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_EVALUATE, OnEvaluate)
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
		if (CurSel < ConstantValue){
			m_Variable.EnableWindow(TRUE);
			m_Variable.ShowWindow(SW_SHOW);
			m_EditNumber.EnableWindow(FALSE);
			m_EditNumber.ShowWindow(SW_HIDE);
			for (int i = 0; i < 6; i++)
				m_Variable.AddString(ExpressionItemsSpecific[CurSel][i]);
			m_Variable.SetFocus();
			m_Variable.SetCurSel(0);
		}
		else {
			m_Variable.EnableWindow(FALSE);
			m_Variable.ShowWindow(SW_HIDE);
			m_EditNumber.SetWindowText("");
			m_EditNumber.EnableWindow(TRUE);
			m_EditNumber.ShowWindow(SW_SHOW);
			m_EditNumber.SetFocus();

		}
		
		m_DirectionText.SetWindowText(InstructionText[CurSel]);
	
	}
}

void EditExpression::OnInsert() 
{
	// TODO: Add your control notification handler code here
	
	int ListItem = m_Item_List.GetCurSel();
	int List2Item = m_Variable.GetCurSel();
	
	int nItemsAtStart = curExpression->nItems ;

	switch (ListItem){
	case VariableItem:
		switch (List2Item){
		case InputLocation:{
			// choose which input location
			int whichLocation = -1;
			CChooseItem selList(&whichLocation, InputLocSaveRequests, NULL, "Select Input Location",this); 
			selList.DoModal(); 
			if (whichLocation >= 0){		   
			   // add to the list
				ExpressionItem *iLoc = new InputLoc(whichLocation);
				curExpression->InsertItem(iLoc,curItem);
			}
			}break;
		case FlagValue:{
			// choose flag
			int whichFlag = -1;
			char *FlagList[16];
			for (int i = 0; i < 2; i++){
				for (int j = 0; j < 8; j++){
					FlagList[i*8+j] = FlagNames[j][i];
				}
			}
			CChooseItem selList(&whichFlag, 16, FlagList,"Select Flag",this);
			selList.DoModal();
			if (whichFlag >= 0){
				ExpressionItem *nFlag = new Flag(whichFlag % 8, whichFlag / 8);
				curExpression->InsertItem(nFlag,curItem);
			}
			}break;
		case ProgramRunTimeVar:{
			ExpressionItem *pRTime = new ProgRunTime;
			curExpression->InsertItem(pRTime, curItem);
			}break;
		case TimerVariable:{
			char *TimerList[6];
			char tText[10];
			for (int i = 0; i < curEvent->nTimers; i++){
				wsprintf(tText,"Timer %i",i+1);
				strcpy(TimerList[i],tText);
			}
			if (i < 5) // i < MAX_TIMERS
				strcpy(TimerList[i],"Create New Timer");
			int tChoice = -1;
			CChooseItem selList(&tChoice, i+1, TimerList,"Select Timer",this);
			selList.DoModal();
			if (tChoice >= 0){
				if (tChoice == curEvent->nTimers) {
					// then we should create a new timer
				}
				
				ExpressionItem *t = new Timer(tChoice + 1);
				curExpression->InsertItem(t, curItem);
			}
			}break;
		default:
			MessageBox("Please select a valid list box item");
		}
		break;
	case OperatorItem:{
		if (List2Item > Modulus){
			MessageBox("Please select a valid list box item");
			break;
		}
		ExpressionItem *o = new Operator((Operators)List2Item);
		curExpression->InsertItem(o, curItem);
		}break;
	case RelOperatorItem:{
		if (List2Item > GreaterThanOrEqual){
			MessageBox("Please select a valid list box item");
			break;
		}
		ExpressionItem *o = new RelOperator((RelOperators)List2Item);
		curExpression->InsertItem(o, curItem);
		}break;
	case ConstantValue:{
		char intBuf[10];
		m_EditNumber.GetWindowText(intBuf, 9);
		int value = 0;
		int digpos = 0;
		int totaldigs = 0;
		BOOL IsDouble = FALSE;
		for (int i = 0; i < 9 && intBuf[i] != '\0'; i++){
			if (intBuf[i] >= '0' && intBuf[i] <= '9'){
				value *= 10;
				value += intBuf[i] - '0';
				totaldigs++;
				if (digpos != 0 && intBuf[i] != '0')
					IsDouble = TRUE;
			}
			else if (intBuf[i] == '.'){
				digpos = totaldigs;	
			}
		}
		double dvalue = (double) value;
		for (i = totaldigs; digpos > 0 && i > digpos; i--){
			dvalue /= 10;
			value /= 10;
		}
		if (IsDouble){
			ExpressionItem *dItem = new DoubConstant(dvalue, intBuf);
			curExpression->InsertItem(dItem, curItem);
		} 
		else {
			ExpressionItem *iItem = new IntConstant(value);
			curExpression->InsertItem(iItem, curItem);
		}
		}break;
	case Parenthesis:
		if (List2Item == 0){
			ExpressionItem *l = new LPthesis;
			curExpression->InsertItem(l, curItem);
		}
		else if (List2Item == 1){
			ExpressionItem *r = new RPthesis;
			curExpression->InsertItem(r, curItem);
		}
		else {
			MessageBox("Please select a valid list box item");
		}
		break;
	}

	if (curExpression->nItems != nItemsAtStart){
		char newWord[30];
		strcpy(newWord,curExpression->GetText(curItem));
		//AddText(newWord);
		int wordLength = strlen(newWord);
		condText.Insert(TextPos[curItem],newWord);
		for (int i = 18; i >= curItem; i--){
			TextPos[i+1] = TextPos[i] + wordLength;
		}
		m_CStatement.SetWindowText(condText);
		if (curItem == curExpression->nItems - 1)
			curItem++;
		ShowHighlightedItem();
	}
	
}

//void EditExpression::AddText(const char * winText, int whichItem){
//	condText
//}
/*
int Delete( int nIndex, int nCount = 1 )
throw( CMemoryException );

Return Value

The length of the changed string. 

Parameters

nIndex

The index of the first character to delete.

nCount

The number of characters to be removed.
*/

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
		char newWord[30];
		strcpy(newWord,curExpression->GetText(curItem));
		int wordLength = strlen(newWord);
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
		
		Expression testExp((*curExpression));
		curExpression->Evaluate();
		ShowExpression(&m_Value, &testExp);
	}
	
	
}

void EditExpression::ShowExpression(CWnd * textWnd, Expression * whichExp ){
	textWnd->SetWindowText(whichExp->ToString());
}

void EditExpression::ShowItem(CWnd * textWnd, ExpressionItem * eItem){
	const char *text = eItem->GetItemText();
	textWnd->SetWindowText(text);
}
*/


void EditExpression::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(FROMSCREEN);
	curExpression->ExpDescription = m_ExpDescription;

	CDialog::OnOK();
}
