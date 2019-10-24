// EditTest.cpp : implementation file
//

#include "stdafx.h"
#include "EditTest.h"
#include "ChooseVariable.h"
#include "ChooseItem.h"
#include "global defs.h"


/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

CString Items[] = {"Control Statement","Event Expression","Boolean Operator","Parenthesis","Action"};

CString CtrlItems[3] = {"If ","Else If ","Else "};
CString BoolItems[3] = {"And ","Or ","Not "};
CString PthsItems[] = {"( ",") "};
CString ActionItems[] = {"Set Input Location","Toggle Flag","Set Timer","Display Message","Write Log","Set Test","Set Variable","Write to File"};


/////////////////////////////////////////////////////////////////////////////
// EditTest dialog


EditTest::EditTest(Array<ExpressionItem *> *PVariables, Array<Event> *pEvents, Event *cEvent, Test &whichTest, int TestNum, CWnd* pParent /*=NULL*/)
	: CDialog(EditTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditTest)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	curEvent = cEvent;
	curTest = &whichTest;
	curTestNum = TestNum;
	curFlow = 0;
	ProgVariables = PVariables;
	progEvents = pEvents;
	
	controlPos[0] = 0;
	for (int flow = 1; flow < 20; flow++){
		if (flow <= curTest->nFlow)
			controlPos[flow] = (controlPos[flow-1] + 2 + (curTest->BStatements[flow-1].nActions > 0 ? curTest->BStatements[flow-1].nActions - 1 : 0 ));
		else
			controlPos[flow] = controlPos[flow - 1];
	}

	nChoices[ControlStatement] = 3;// = {3,0,3,2};
	nChoices[EventExpression] = curEvent->nStatements;
	nChoices[BooleanOperator] = 3;
	nChoices[Parenthesis] = 2;
	nChoices[ActionChoice] = 8;

	IsChoiceAvailable[ControlStatement] = TRUE;
	IsChoiceAvailable[EventExpression] = FALSE;
	IsChoiceAvailable[BooleanOperator] = FALSE;
	IsChoiceAvailable[Parenthesis] = FALSE;
	IsChoiceAvailable[ActionChoice] = FALSE;

	ShowFull = FALSE;

	curChoice = NullChoice;
	
}


void EditTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditTest)
	DDX_Control(pDX, IDC_FULL_EXPRESSION, m_FullExpression);
	DDX_Control(pDX, IDC_TESTS, m_TestNum);
	DDX_Control(pDX, IDC_TEST_TEXT, m_TestText);
	DDX_Control(pDX, IDC_TEST, m_Test);
	DDX_Control(pDX, IDC_CHOICES, m_Choices);
	DDX_Control(pDX, IDC_ITEMS, m_Items);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditTest, CDialog)
	//{{AFX_MSG_MAP(EditTest)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_CBN_SELCHANGE(IDC_TESTS, OnSelchangeTests)
	ON_LBN_SELCHANGE(IDC_ITEMS, OnSelchangeItems)
	ON_BN_CLICKED(IDC_FULL_EXPRESSION, OnFullExpression)
	ON_NOTIFY(NM_CLICK, IDC_TEST, OnClickTest)
	ON_NOTIFY(LVN_KEYDOWN, IDC_TEST, OnKeydownTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditTest message handlers

void EditTest::OnInsert() 
{
	// TODO: Add your control notification handler code here
	int pos = ((int) m_Choices.GetFirstSelectedItemPosition()) - 1;
	if (pos < 0){
		MessageBox("Please choose something to insert.");
		return;
	}
	int testPos = ((int) m_Test.GetFirstSelectedItemPosition()) - 1;
	if (testPos < 0){
		MessageBox("Please select a statement to insert into.");
		return;
	}
	MenuChoices m = curChoice;//MenuChoices(m_Items.GetCurSel());
	int position = 0;

		
	curFlow = curTest->nFlow;
	for (int t = 0; t < curTest->nFlow; t++){
		if (testPos < controlPos[t+1]) {
			curFlow = t;
			break;
		}
	}
	BoolExpression *curExp = &curTest->BStatements[curFlow];
	int nItemsAtStart = curExp->nItems;

	if (pos != -1 && pos < nChoices[m]) {
		ExpressionItem *s = NULL;
		switch (m) {
		case ControlStatement:{
			if (curFlow == curTest->nFlow ) {
				// we are inserting at the end...
				curExp->SetType(FlowTypes(pos));
				
				controlPos[curFlow] = curFlow == 0 ? 0 : ( controlPos[curFlow-1] + 2 +
					(curTest->BStatements[curFlow-1].nActions > 0 ? curTest->BStatements[curFlow-1].nActions - 1 : 0 ));
			}
			else {
				BoolExpression *object = new BoolExpression();
				object->SetType(FlowTypes(pos));
				curTest->BStatements.Insert(*object, curFlow);
				curExp = &curTest->BStatements[curFlow];
			}
			for (int i = 19; i > curFlow; i--){
					// The controlPos refers to the row number upon
					// which each If, Else, ElseIf, structure resides.
					// It is found by taking the row number of the previous
					// boolean control + the number of actions that accompany it.
					// curPos refers to the character position of the
					// insert cursor for each control statement.
					controlPos[i] = controlPos[i]+2;//+curTest->BStatements[curFlow-1].nActions;
			}
			//curPos[curFlow] = 0;
			//InsertPos = 0;
			
			curTest->nFlow++;
			
			s = new FlowControl(FlowTypes(pos), &CtrlItems[pos]);
			curExp->InsertItem(s, 0);//curPos[curFlow]);InsertPos
			//curExp->nItems++;
			
			m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, controlPos[curFlow]/*curTest->nFlow*/, NULL, 0, LVIS_SELECTED, 0, 0);
			m_Test.SetItemText(controlPos[curFlow]/*curFlow*/, 0, (LPCSTR) curExp->GetText(0));
			m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, controlPos[curFlow]+1/*curTest->nFlow*/, NULL, 0, LVIS_SELECTED, 0, 0);
			m_Test.SetItemText(controlPos[curFlow]+1/*curFlow*/, 0, "  Then");
		}	break;
		case EventExpression:{
			if (!s){
				if (ShowFull){
					
					s = new SubExpression(&curEvent->Statements[pos], new CString(curEvent->Statements[pos].ToString() 
					+ (curEvent->Statements[pos].EvaluateTF() ? " (TRUE) " : " (FALSE) ")));
				}
				else
					s = new SubExpression(&curEvent->Statements[pos], new CString(curEvent->Statements[pos].ExpDescription
					+ (curEvent->Statements[pos].EvaluateTF() ? " (TRUE) " : " (FALSE) ")));
			}
		}
		case BooleanOperator:{
			if (!s)
				s = new BoolOperator(BoolOperators(pos), &BoolItems[pos]);
		} 
		case Parenthesis:{
			if (!s) {
				if (pos == 0){
					s = new LPthesis();
				}
				else if (pos == 1){
					s = new RPthesis();
				}
			}
			
			if (!s){
				MessageBox("Please select a valid item.");
				return;
			}
			if (nItemsAtStart > 1) {// then choose insert position
				int n = nItemsAtStart;
				
				CString *words;
				words = new CString[n];
				for (int i = 1; i < n; i++){
					words[i-1] = *curExp->GetText(i);
				}
				words[i-1] = "        ";
				SelectTestObject IDlg(words, &position, n, FALSE, this);   // standard constructor
				if (IDlg.DoModal() == IDOK)
					curExp->InsertItem(s, position + 1);//InsertPos);//curPos[curFlow]);
				delete [] words;
			}
			else
				curExp->InsertItem(s, 1);//InsertPos);//curPos[curFlow]);
			break;
		}
		
		case ActionChoice:{
			//"Set Input Location","Toggle Flag","Set Timer",
			//"Display Message","Write Log","Set Test",
			//"Set Variable","Write to File"};
			Action *newItem = NULL;
			
			switch ((ActionTypes) pos) {
			case SetInputLocationItem: {
				
				int whichLocation = -1;
				CChooseItem selList(&whichLocation, InputLocSaveRequests, NULL, "Select Input Location",this); 
				selList.DoModal(); 
				if (whichLocation >= 0){		   
					ExpressionItem *var = NULL;
					CChooseVariable cDlg(ProgVariables, progEvents, var, this);
					if (cDlg.DoModal() == IDOK)
						newItem = new SetInputLocation(whichLocation, var);	
				}
				
				break;
			}
			case ToggleFlagItem: 
				//newItem = new ToggleFlag(int wSet, int wFlag, ExpressionItem *v);
				break;
			case SetTimerItem: 
				//newItem = new SetTimer(int wTimer);
				break;
			case DisplayMessageItem: 
				//newItem = new DisplayMessage(CString text, int mType);
				break;
			case WriteLogItem: 
				//newItem = new WriteLog (CString fName, Expression *m);
				break;
			case SetTestItem: 
				//newItem = new SetTest(int wTest);
				break;
			case SetVariableItem: 
				//newItem = new SetVariable(ExpressionItem *d, ExpressionItem *s);
				break;
			case WriteToFileItem: 
				//newItem = new WriteToFile(CString fileName);
				break;
			}
			if (newItem){
				if (curExp->nActions > 0) {// then choose insert position
					int n = curExp->nActions + 1;
					
					CString *words;
					words = new CString[n];
					for (int i = 0; i < n - 1; i++){
						words[i] = curExp->GetActionText(i);
					}
					words[i] = "        ";
					
					SelectTestObject IDlg(words, &position, n, FALSE, this);   // standard constructor
					if (IDlg.DoModal() == IDOK)
						curExp->InsertAction(newItem,position);
					for (i = 19; i > curFlow; i--)
						controlPos[i]++;// = controlPos[i]+1;	
					delete [] words;
				}
				else 
					curExp->InsertAction(newItem,0);
				
			}
			else
				MessageBox("Please select an action to insert");
						
		}
		}
	}

	
	ShowCurrentTestInfo();
}

void EditTest::OnOK() 
{
	// TODO: Add extra validation here
	// check to see that the test is valid...
	
	CDialog::OnOK();
}

void EditTest::OnDelete() 
{
	// TODO: Add your control notification handler code here
	// determine which flow statement...
	int n = curTest->BStatements[curFlow].nItems - 1;
	int choice = IDYES;
	
	if (n > 0)
		choice = MessageBox("Delete you want to delete this entire control statement?",NULL,MB_ICONQUESTION |MB_YESNOCANCEL);

	if (choice == IDYES){
	}
	else if (choice == IDNO){
		CString *words;
		
		words = new CString[n];
		for (int i = 1; i <= n; i++){
			words[i-1] = *curTest->BStatements[curFlow].GetText(i);
		}
		int *pos = new int[n];
		SelectTestObject selectObject(words, pos, n, TRUE, this);
		if (selectObject.DoModal() == IDOK){
			for (int i = n - 1; i >= 0; i--){
				curTest->BStatements[curFlow].Items.Remove(pos[i] + 1,1);
				curTest->BStatements[curFlow].nItems--;
			}
		}
		delete [] pos;
		ShowCurrentTestInfo();
	}
	
	
}

void EditTest::OnSelchangeTests() 
{
	// TODO: Add your control notification handler code here
	int curSel;
	if ((curSel = m_TestNum.GetCurSel()) != CB_ERR){
		curTest = &curEvent->Tests[curSel];
		curTestNum = curSel;
		nChoices[1] = curEvent->nStatements;
		m_Items.SetCurSel(ControlStatement);
		ShowChoices(ControlStatement);
		ShowCurrentTestInfo();
	}
}

void EditTest::ShowCurrentTestInfo(){
	
	m_Test.DeleteAllItems();
	int curRow = 0;
	for (int cFlow = 0; cFlow < curTest->nFlow; cFlow++){
		BoolExpression *curExp = &curTest->BStatements[cFlow];	
				
		for (int i = 1; i < curExp->nItems; i++){
			if (curExp->Items[i]->whichItem == SubExpressionItem){
				if (ShowFull)
					curExp->Items[i]->SetText( new CString(static_cast<SubExpression *>(curExp->Items[i])->whichExp->ToString()
					+ (static_cast<SubExpression *>(curExp->Items[i])->EvaluateTF() ? " (TRUE) " : " (FALSE) "))  );
				else
					curExp->Items[i]->SetText( new CString(static_cast<SubExpression *>(curExp->Items[i])->whichExp->ExpDescription
					+ (static_cast<SubExpression *>(curExp->Items[i])->EvaluateTF() ? " (TRUE) " : " (FALSE) "))  );
			}
		}
		m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, curRow++, NULL, 0, LVIS_SELECTED, 0, 0);
		m_Test.SetItemText(curRow - 1, 0, (LPCSTR) *curExp->GetText(0));
		m_Test.SetItemText(curRow - 1, 1, curExp->ToString());

		m_Test.SetItemText(curRow - 1, 2, (curExp->ExpressionTF() ? "True" : "False"));

		m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, curRow++, NULL, 0, LVIS_SELECTED, 0, 0);
		m_Test.SetItemText(curRow - 1, 0, "  Then");
		m_Test.SetItemText(curRow - 1, 1, "do this...");
		for (i = 0; i < curExp->nActions; i++){
			if (i > 0)
				m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, curRow++, NULL, 0, LVIS_SELECTED, 0, 0);
			m_Test.SetItemText(curRow - 1, 1, curExp->GetActionText(i));
		}
	}
	m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, curRow++, NULL, 0, LVIS_SELECTED, 0, 0);
	m_Test.SetItemText(curRow - 1, 0, "      ");

}

BOOL EditTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	char e[5];
	for (int i = 0; i < curEvent->nTests; i++){
		wsprintf(e,"%i",i+1);
		m_TestNum.AddString(e);
	}
	m_TestNum.SetCurSel(curTestNum);

	m_Test.InsertColumn(0,"Control",LVCFMT_LEFT, 60, 1);
	m_Test.InsertColumn(1,"Expression",LVCFMT_LEFT, 320, 2);
	m_Test.InsertColumn(2,"Bool Value",LVCFMT_LEFT, 80, 3);

	m_Test.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, 1, NULL, 0, LVIS_SELECTED, 0, 0);
	m_Test.SetItemText(0, 1, "      ");

	if (ShowFull)
		m_FullExpression.SetWindowText("Show Short Exp.");
	else
		m_FullExpression.SetWindowText("Full Expression");

	ShowCurrentTestInfo();
	UINT flag = LVIS_SELECTED | LVIS_FOCUSED;
	int index = m_Test.GetItemCount() - 1;
	m_Test.SetFocus();
    m_Test.SetItemState(index, flag, flag);
	m_Test.SetSelectionMark(index);

	FillMenuBox();

	m_Items.SetCurSel(ControlStatement);
	ShowChoices(ControlStatement);
	
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void EditTest::OnSelchangeItems() 
{
	// TODO: Add your control notification handler code here
	//m_Variable.ResetContent();
	
	MenuChoices CurSel;
	int c = 0;
	if ((CurSel = (MenuChoices) m_Items.GetCurSel()) != LB_ERR){
		for (int i = 0; i < 5; i++){
			if (CurSel == c)
				ShowChoices(MenuChoices(i));
			if (IsChoiceAvailable[i])
				c++;
		}
	}
	
}

void EditTest::FillMenuBox(){
	int t = -1;
	m_Items.ResetContent();
	for (int i = 0; i < 5; i++){
		if (IsChoiceAvailable[i]) 
			m_Items.AddString(Items[i]);
		else {
			if (curChoice == i) {
				for (t = 0; t < 5; t++){
					if (IsChoiceAvailable[t]){
						ShowChoices(MenuChoices(t));
						break;
					}
				}
			}
		}
	}
	if (t != -1)
		m_Items.SetCurSel(0);
	
}

void EditTest::ShowChoices(MenuChoices m){
	curChoice = m;
	m_Choices.DeleteAllItems();
	while (m_Choices.DeleteColumn(0));
	switch (m){
	case ControlStatement:
	case BooleanOperator:
	case Parenthesis:
	case ActionChoice:
		m_Choices.InsertColumn(0,Items[m],LVCFMT_LEFT, 120, 1);
		break;
	case EventExpression:
		m_Choices.InsertColumn(0,"Number",LVCFMT_LEFT, 20, 1);
		m_Choices.InsertColumn(1,"Title",LVCFMT_LEFT, 80, 2);
		m_Choices.InsertColumn(2,"Expression",LVCFMT_LEFT, 150, 3);
		m_Choices.InsertColumn(3,"Value",LVCFMT_LEFT, 60, 4);
		break;
	default:
		return;
	}

	for (int i = 0; i < nChoices[m]; i++){
		
		m_Choices.InsertItem(LVIR_BOUNDS|LVIF_TEXT|LVIF_STATE, i + 1, NULL, 0, LVIS_SELECTED, 0, 0);
		switch (m){
		case ControlStatement:
			m_Choices.SetItemText(i, 0, CtrlItems[i]);
			break;
		case BooleanOperator:
			m_Choices.SetItemText(i, 0, BoolItems[i]);
			break;
		case Parenthesis:
			m_Choices.SetItemText(i, 0, PthsItems[i]);
			break;
		case EventExpression:
			char e[5];
			wsprintf(e,"%i",i + 1);
			m_Choices.SetItemText(i, 0, e);
			m_Choices.SetItemText(i, 1, curEvent->Statements[i].ExpDescription);
			m_Choices.SetItemText(i, 2, curEvent->Statements[i].ToString());
			if (curEvent->Statements[i].IsComparison)
				m_Choices.SetItemText(i, 3, curEvent->Statements[i].EvaluateTF ? "True" : "False");
			else 
				m_Choices.SetItemText(i, 3, (LPCSTR) *curEvent->Statements[i].Evaluate()->GetItemText());
	
			break;
		case ActionChoice:
			m_Choices.SetItemText(i, 0, ActionItems[i]);
			break;
		}
	}


}

void EditTest::OnFullExpression() 
{
	// TODO: Add your control notification handler code here
	ShowFull = ShowFull ? FALSE : TRUE;
	if (ShowFull)
		m_FullExpression.SetWindowText("Show Short Exp.");
	else
		m_FullExpression.SetWindowText("Full Expression");

	ShowCurrentTestInfo();
	
}

void EditTest::ClickList(CListCtrl &wList){
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


void EditTest::OnClickTest(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	ClickList(m_Test);
	SelectControl();
	*pResult = 0;
}

void EditTest::SelectControl(){
	int testPos = ((int) m_Test.GetFirstSelectedItemPosition()) - 1;
	
	IsChoiceAvailable[ControlStatement] = TRUE;
	IsChoiceAvailable[EventExpression] = FALSE;
	IsChoiceAvailable[BooleanOperator] = FALSE;
	IsChoiceAvailable[Parenthesis] = FALSE;
	IsChoiceAvailable[ActionChoice] = FALSE;

	curFlow = curTest->nFlow;
	for (int t = 0; t < curTest->nFlow; t++){
		if (testPos < controlPos[t+1]) {
			curFlow = t;
			break;
		}
	}

	if (curFlow != curTest->nFlow)
	{
		if (testPos == controlPos[curFlow])
		{
			IsChoiceAvailable[EventExpression] = TRUE;
			IsChoiceAvailable[BooleanOperator] = TRUE;
			IsChoiceAvailable[Parenthesis] = TRUE;
		}
		else 
		{
			IsChoiceAvailable[ControlStatement] = FALSE;
			IsChoiceAvailable[ActionChoice] = TRUE;
		}
	}
	FillMenuBox();
}

void EditTest::OnKeydownTest(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	//SelectControl();
	*pResult = 1;//0;
}
