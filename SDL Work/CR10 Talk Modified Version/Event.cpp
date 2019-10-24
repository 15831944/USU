#include <afxwin.h>
#include "Event.h"
#include "global defs.h"


CString ExpressionItems[] = {"Variable","Operator","Relational Operator",
"Parenthesis","Constant Value","Expression"};
CString ExpressionItemsSpecific[4][6] = 
{"Input Location","User Flag","Program Run Time","Timer","","",
"+ ","- ","* ","/ ","% ","",
"< (Less than)","> (greater than)",
"== (Equal)","!= (not equal)",
"<= (Less than or equal)",">= (greater than or equal)",
"( ",") ","","","",""};

CString InstructionText[] = {
"Please select the type of variable to add",
"Please select the operator to add to the expression",
"Please choose a relational operator to insert",
"Scroll cursor to insert location for parenthesis",
"Please enter a constant value",
"Select the event which contains the expression"};

CString RelationOperatorsText[] = { "< ","> ","== ","!= ","<= ",">= "};
Event::Event() /* :Timers(1), Statements(3)*/ {
	// Initialize Timers to one, Statements to three
	//Timers[1].SetParentEvent(this);
	nStatements = 0;
	nTests = 0;
	nTimers = 0;
	Title = "No name";
	curTest = 0;
}

Event::~Event() {
 	Timers(0);
	Statements(0);
	Tests(0);
}

BOOL Event::PerformTest(){
	//owTypes lastType;
	int lastResult = -1;
	
	for (int b = 0; b < Tests[curTest].nFlow; b++){
		if (Tests[curTest].BStatements[b].flowType == If){
			if (lastResult = Tests[curTest].BStatements[b].EvaluateTF())
				Tests[curTest].BStatements[b].PerformActions();
		}
		else if(Tests[curTest].BStatements[b].flowType == ElseIf && b > 1){
			if (lastResult == FALSE){
				if (lastResult = Tests[curTest].BStatements[b].EvaluateTF())
				Tests[curTest].BStatements[b].PerformActions();
			}
		}
		else if(Tests[curTest].BStatements[b].flowType == Else && b > 1){
			if (lastResult == FALSE){
				Tests[curTest].BStatements[b].PerformActions();
			}
		}
	}
	return TRUE;

}

Expression::Expression() /*: Items(3)*/ {
	// initially set the array to have 3 members.
	// for example i < 3 would take three objects of
	// class ExpressionItems.
	// this can expand if necessary.  
	nItems = 0;
	ExpDescription = "";
	IsComparison = FALSE;
}

Expression::Expression(Expression *source, int firstItem, int lastItem)
: Items(lastItem - firstItem + 1)
{
	int pos = 0;
	for (int i = firstItem; i < lastItem; i++, pos++){
		CopyItem(Items[pos],source->Items[i]);
	}
	nItems = lastItem - firstItem;
	IsComparison = FALSE;
}

Expression::Expression(const Expression &source)
: Items(source.nItems)
{
	for (int i = 0; i < source.nItems;  i++){
		CopyItem(Items[i],source.Items[i]);
	}
	nItems = source.nItems;
}

Expression::~Expression() {
	Items(0);
}


void Expression::CopyItem(ExpressionItem *&destination, const ExpressionItem *source){
	
	switch (source->whichItem) {
	case VariableItem:{
		switch (static_cast<const Variable *>(source)->vType){
		case InputLocation:{
			destination = new InputLoc (static_cast<const InputLoc *>(source)->whichLoc);
			break;}
		case FlagValue:{
			destination = new Flag ((static_cast<const Flag *>(source)->whichFlag) & 0x7F,
								 (static_cast<const Flag *>(source)->whichFlag) & 0x80);
			break;}
		case ProgramRunTimeVar:{
			destination = new ProgRunTime;
			break;}
		case TimerVariable:{
			destination = new Timer(static_cast<const Timer *>(source)->whichTimer + 1);
			break;}
		}
		break;}
	case OperatorItem: {
		destination = new Operator(static_cast<const Operator *>(source)->Operation);
		break;}
	case RelOperatorItem: {
		destination = new RelOperator(static_cast<const RelOperator *>(source)->Relation);
		break;}
	case IntegerConst: {
		destination = new IntConstant(static_cast<const IntConstant *>(source)->IntegerConstant);
		break;}
	case DoubleConst: {
		destination = new DoubConstant(static_cast<const DoubConstant *>(source)->DoubleConstant);
		break;}
	case LeftParenthesis: {
		destination = new LPthesis;
		break;}
	case RightParenthesis: {
		destination = new RPthesis;
		break;}
	case SubExpressionItem: {
		destination = new SubExpression(static_cast<const SubExpression *>(source)->whichExp);
		break;}
	}
}

void Expression::InsertItem(ExpressionItem *eItem, int whichPos){
	Items.Insert(eItem, whichPos);
	nItems++;
}

void Expression::RemoveItem(int whichPos){
	if (nItems > 0){	
		Items.Remove(whichPos);
		nItems--;
	}
}

BOOL Expression::EvaluateTF(){
// call Evaluate unless there is only one item.
// if there is only one item, decide if it
// is true or false
	
	ExpressionItem * result = Evaluate();

	if (result->whichItem == IntegerConst)
		return BOOL(static_cast<IntConstant *>(result)->IntegerConstant != 0);
	else //(result->whichItem == DoubleConst)
		return BOOL(static_cast<DoubConstant *>(result)->DoubleConstant != 0.0);
	
}

ExpressionItem * Expression::Evaluate(Expression *ExpEval){
	// look for parenthesis
	// evaluate sections with parenthesis
	BOOL returnExpression = (ExpEval != NULL);
	ExpressionItem *returnItem = NULL;
	ExpEval = new Expression(this, 0, nItems);

	int lpPos = 0;
	int pCount = 0;
	for (int pos = 0; pos < ExpEval->nItems; pos++){
		
		if (ExpEval->Items[pos]->whichItem == LeftParenthesis){
			lpPos = pos;
			pCount = 1;
			while (pCount > 0 && pos < ExpEval->nItems - 1){
				pos++;
				if (ExpEval->Items[pos]->whichItem == RightParenthesis){
					pCount--;
					if (pCount == 0){
						Expression subExp(ExpEval, lpPos + 1, pos);
						ExpEval->Items.Remove(lpPos, pos - lpPos + 1);
						if (subExp.nItems > 0){
							ExpressionItem * eItem = subExp.Evaluate();
							ExpEval->Items.Insert(eItem, lpPos);
						}
						ExpEval->nItems -= (pos - lpPos);
						pos -= (pos - lpPos);
					}
				}
				else if (ExpEval->Items[pos]->whichItem == LeftParenthesis)
					pCount++;
				
			}
			
		}

	}
	// look for multiply, divide, modulus,
	// if two numbers are found directly by each other, assume
	// it's because one was the result of parenthesis operation
	// and the user didn't enter the times symbol. (like this)
	// 5(2+3) evaluates to 25.  You don't need to write 5*(2+3),
	// they're the same.
	
	for (pos = 0; pos < ExpEval->nItems; pos++){
		//int endPos = nItems;
		if (ExpEval->Items[pos]->whichItem == OperatorItem &&
			(static_cast<Operator *>(ExpEval->Items[pos]))->GetOperator() > Subtract)
		{
			returnItem = ExpEval->Items[pos]->DoOperation(ExpEval->Items[pos - 1], ExpEval->Items[pos + 1]);
			ExpEval->Items.Remove(--pos, 3);
			ExpEval->Items.Insert(returnItem, pos);
			ExpEval->nItems -= 2;
		}
		else if (pos > 0 && ExpEval->Items[pos]->IsValue() && 
			ExpEval->Items[pos - 1]->IsValue())
		{
			returnItem = Operator(Multiply).DoOperation(ExpEval->Items[pos], ExpEval->Items[pos - 1]);
			ExpEval->Items.Remove(--pos, 2);
			ExpEval->Items.Insert(returnItem, pos);
			ExpEval->nItems -= 1;	
		}
	}

	// look for addition, subtraction
	for (pos = 0; pos < ExpEval->nItems; pos++){
		//int endPos = nItems;
		if (ExpEval->Items[pos]->whichItem == OperatorItem )
		{
			returnItem = ExpEval->Items[pos]->DoOperation(ExpEval->Items[pos - 1], ExpEval->Items[pos + 1]);
			ExpEval->Items.Remove(--pos, 3);
			ExpEval->Items.Insert(returnItem, pos);
			ExpEval->nItems -= 2;
		}
	}
	// look for relational operators
	for (pos = 0; pos < ExpEval->nItems; pos++){
		//int endPos = nItems;
		if (ExpEval->Items[pos]->whichItem == RelOperatorItem )
		{
			returnItem = ExpEval->Items[pos]->DoOperation(ExpEval->Items[pos - 1], ExpEval->Items[pos + 1]);
			ExpEval->Items.Remove(--pos, 3);
			ExpEval->Items.Insert(returnItem, pos);
			ExpEval->nItems -= 2;
		}
	}

	if (returnExpression){
		delete returnItem;
		returnItem = NULL;
	}
	else {
		if (returnItem == NULL){
			CopyItem(returnItem, ExpEval->Items[0]);	
		}
		delete ExpEval;
		ExpEval = NULL;
	}
	
	if (returnItem->whichItem != IntegerConst &&
		returnItem->whichItem != DoubleConst) {
		double value = returnItem->GetDoubValue();
		ExpressionItem *tempItem;
		if (value == (double)(int) value)
			tempItem = new IntConstant(int(value));
		else 
			tempItem = new DoubConstant(value);
		delete returnItem;
		returnItem = tempItem;
	}

	return returnItem;
}

BOOL Expression::CheckExpression(){
	// check for balanced paranthesis
	// check for value - operator - value

	// inbetween every parenthesis there must be items
	// before and after every operator there must be value items
	int lPs = 0;
	int rPs = 0;
	int cPs = 0;
	int valueItems = 0;
	ItemTypes lastItem = NullItem;
	ItemTypes currItem = NullItem;
	
	BOOL ExpIsGood = TRUE;
	for (int pos = 0; pos < nItems && ExpIsGood; pos++){
		currItem = Items[pos]->whichItem;
		
		switch (currItem){
		case LeftParenthesis:
			lPs++;
			cPs++;
			valueItems = 0;
			break;
		case RightParenthesis:
			rPs++;
			cPs--;
			if (cPs == 0){
				if (valueItems == 0){
					ExpIsGood = FALSE;
					break;
				}
				valueItems = 0;
			}
			break;
		case VariableItem:
		case IntegerConst:
		case DoubleConst:
		case SubExpressionItem:
			currItem = ValueItem;
			valueItems++;
			if (lastItem == ValueItem)
				ExpIsGood = FALSE;
			break;
		case RelOperatorItem: {IsComparison = TRUE;}
		case OperatorItem:
			{
			
			if ((lastItem == OperatorItem || lastItem == RelOperatorItem) || lastItem == LeftParenthesis ||
				pos == nItems - 1 || (!Items[pos + 1]->IsValue() && Items[pos + 1]->whichItem != LeftParenthesis))
				ExpIsGood = FALSE;
			break;
			}
		}
		lastItem = Items[pos]->whichItem;
	}
	if (ExpIsGood)
		return TRUE;
	if (lPs != rPs){
		MessageBox(NULL, "Cannot evaluate expression.  Parenthesis do not match.","Invalid Expression",MB_ICONINFORMATION);
		return FALSE;
	}
	else if (currItem == ValueItem){
		MessageBox(NULL, "Cannot evaluate expression.  Operator missing.","Invalid Expression",MB_ICONINFORMATION);
		return FALSE;
	}
	else {
		MessageBox(NULL, "Cannot evaluate expression.","Invalid Expression",MB_ICONINFORMATION);
		return FALSE;
	}
}

CString * Expression::GetText(int whichPos){
	return Items[whichPos]->GetItemText();
}

CString Expression::ToString(){
	//char newWord[80];
	CString tempString;
	
	for (int i = 0; i < nItems; i++){
		//strcpy(newWord,GetText(i));
		tempString+= *GetText(i);//newWord);
	}
	
	return tempString;
}


ExpressionItem::ExpressionItem(ItemTypes iType, CString *Text ){//= NULL = NULL
	whichItem = iType;
	
	ItemText = Text;
	if (ItemText != NULL){
		if ((*ItemText)[ItemText->GetLength() - 1] != ' ')
			ItemText->Insert(ItemText->GetLength(), " ");
	}
		/*
	ItemText = Text;
	if (ItemText){
		int textLength = strlen(Text);
		for (int i = textLength - 1; i > 0; i--){
			if (ItemText[i] != ' ') break;
		}
		if (i > 27)
			i = 27;
		ItemText[i+1] = ' ';
		ItemText[i + 2] = '\0';
	}*/
}

ExpressionItem::ExpressionItem(){
	whichItem = VariableItem;
	ItemText = new CString("Messed up dude");
	MessageBox(NULL, "Default Constructor called for expression item.  This should not happen","Error",MB_ICONEXCLAMATION);
}

ExpressionItem::~ExpressionItem(){
}

void ExpressionItem::SetText( CString * NewText ){
	
	//if (ItemText) 
	//	delete ItemText;
	ItemText = NewText;
	if ((*ItemText)[ItemText->GetLength() - 1] != ' ')
		ItemText->Insert(ItemText->GetLength(), " ");
	
	//ItemText = NewText;
	/*if (ItemText){
		int textLength = strlen(NewText);
		for (int i = textLength - 1; i > 0; i--){
			if (ItemText[i] != ' ') break;
		}
		if (i > 27)
			i = 27;
		ItemText[i+1] = ' ';
		ItemText[i + 2] = '\0';
	}*/
}

CString * ExpressionItem::GetItemText(){
	return ItemText;	
}

ExpressionItem *ExpressionItem::DoOperation(const ExpressionItem *left, const ExpressionItem *right) {
	int liValue = 0;
	double ldValue = 0.0;
	int riValue = 0;
	double rdValue = 0.0;
	//ExpressionItem *result;
	BOOL IsComp = FALSE;
	int OpType;


	if (whichItem == OperatorItem)
		OpType = (static_cast<Operator *>(this))->GetOperator();
	else if (whichItem == RelOperatorItem){
		OpType = (static_cast<RelOperator *>(this))->GetOperator();
		IsComp = TRUE;
	}
	else
		return NULL;
	
	if (left->whichItem == DoubleConst || right->whichItem == DoubleConst ||
		(left->whichItem == VariableItem && 
		((static_cast<const Variable*>(left))->vType == InputLocation || 
		(static_cast<const Variable*>(left))->vType == TimerVariable)) ||
		(right->whichItem == VariableItem && 
		((static_cast<const Variable*>(right))->vType == InputLocation || 
		(static_cast<const Variable*>(right))->vType == TimerVariable)))
	{
		rdValue = right->GetDoubValue();
		ldValue = left->GetDoubValue();
		// return a double type
		if (IsComp){
			int value = 0;
			switch (OpType) {
				case LessThan: {value = (ldValue < rdValue); break;}
				case GreaterThan: {value = (ldValue > rdValue); break; }
				case Equal: {value = (ldValue == rdValue); break;}
				case NotEqual: {value = (ldValue != rdValue); break; }
				case LessThanOrEqual: {value = (ldValue <= rdValue); break; }
				case GreaterThanOrEqual: {value = (ldValue >= rdValue); break; }
			}
			//return IntConstant(value);
			return new DoubConstant(value);
		}
		else {
			double value = 0.0;
			switch (OpType) {
				case Add: {value = ldValue + rdValue; break;}
				case Subtract: {value = ldValue - rdValue; break; }
				case Multiply: {value = ldValue * rdValue; break;}
				case Divide: {value = ldValue / rdValue; break; }
				case Modulus: {int ivalue = (int)ldValue % (int)rdValue; 
					return new IntConstant(ivalue); }
				}
				//return DoubConstant(value);
				return new DoubConstant(value);
			}
		} 
	else {  // return an integer type
		liValue = left->GetIntValue();
		riValue = right->GetIntValue();
		if (IsComp){
			int value = 0;
			switch (OpType) {
				case LessThan: {value = (liValue < riValue); break;}
				case GreaterThan: {value = (liValue > riValue); break; }
				case Equal: {value = (liValue == riValue); break;}
				case NotEqual: {value = (liValue != riValue); break; }
				case LessThanOrEqual: {value = (liValue <= riValue); break; }
				case GreaterThanOrEqual: {value = (liValue >= riValue); break; }
			}
			return new IntConstant(value);
			//return IntConstant(value);
		}
		else {
			int value = 0;
			switch (OpType) {
				case Add: {value = liValue + riValue; break;}
				case Subtract: {value = liValue - riValue; break; }
				case Multiply: {value = liValue * riValue; break;}
				case Divide: {value = liValue / riValue; break; }
				case Modulus: {value = liValue % riValue; break; }
			}
			return new IntConstant(value);
			//return IntConstant(value);
		}
	}
 
 	return NULL;
}

double ExpressionItem::GetDoubValue() const {
	MessageBox(NULL,"Warning:  GetDoubValue (base class function) in Class ExpressionItem called."
	"This function should be overridden in a derived class","Error",MB_ICONEXCLAMATION);
	return 0.0;
}

int ExpressionItem::GetIntValue() const {
	MessageBox(NULL,"Warning:  GetIntValue (base class function) in Class ExpressionItem called."
		"This function should be overridden in a derived class","Error",MB_ICONEXCLAMATION);
	return 0;
}

BOOL ExpressionItem::IsValue(){
	return (whichItem == VariableItem || whichItem == IntegerConst ||
		whichItem == DoubleConst || whichItem == ConstantValue || 
		whichItem == SubExpressionItem );
}

CString ExpressionItem::ValueToString(){
	return CString("problem");
}

Variable::Variable(VariableTypes v, CString *vText )//=NULL
: ExpressionItem(VariableItem, vText) {
	vType = v;
}

double Variable::GetDoubValue() const{
	MessageBox(NULL,"Warning:  GetDoubValue (base class function) in Class ExpressionItem called."
		"This function should be overridden in a derived class","Error",MB_ICONEXCLAMATION);
	return 0.0;
}
int Variable::GetIntValue() const {
	MessageBox(NULL,"Warning:  GetIntValue (base class function) in Class ExpressionItem called."
		"This function should be overridden in a derived class","Error",MB_ICONEXCLAMATION);
	return 0;
}

InputLoc::InputLoc(int whichLocation)
: Variable(InputLocation, &AvailableInputLocations[whichLocation] ) {
	whichLoc = whichLocation;
}

int InputLoc::GetIntValue() const{
	return (int) InputLocValue[whichLoc];
}

double InputLoc::GetDoubValue() const{
	return InputLocValue[whichLoc];
}

Flag::Flag(int wFlag, int wModify)
: Variable(FlagValue, &FlagNames[wFlag][wModify]) {
	whichFlag = wModify * 0x80 + wFlag;	
}

double Flag::GetDoubValue() const{
	return (double) FlagStatus[whichFlag & 0x7F][whichFlag & 0x80]; 
}
int Flag::GetIntValue() const {
	return FlagStatus[whichFlag & 0x7F][whichFlag & 0x80]; 
}

ProgRunTime::ProgRunTime()
: Variable(ProgramRunTimeVar, new CString("Prog Run Time")) {

}

double ProgRunTime::GetDoubValue() const{
	return (double) ProgramCounter;
}

int ProgRunTime::GetIntValue() const {
	return ProgramCounter;
}

Timer::Timer()
: Variable(TimerVariable) {
	parentEvent = NULL;
	whichTimer = 0;
}

Timer::Timer(int wTimer)
: Variable(TimerVariable) {
	parentEvent = NULL;
	char tText[20];
	wsprintf(tText,"Local Timer %i", wTimer);
	ExpressionItem::SetText(new CString(tText));
	whichTimer = wTimer - 1;
}

Timer::~Timer(){

}

double Timer::GetDoubValue() const{
	return (double) parentEvent->Timers[whichTimer];
}

int Timer::GetIntValue() const {
	return parentEvent->Timers[whichTimer];
}

void Timer::SetParentEvent(Event *pEvent){
	parentEvent = pEvent;
}

Operator::Operator(Operators Op)
: ExpressionItem(OperatorItem, &ExpressionItemsSpecific[1][Op]) {
	
	/*
	switch (Op){
	case Add: ExpressionItem::SetText("+"); break;
	case Subtract: ExpressionItem::SetText("-"); break;
	case Multiply: ExpressionItem::SetText("*"); break;
	case Divide: ExpressionItem::SetText("/"); break;
	case Modulus: ExpressionItem::SetText("%"); break;
	}
	*/
	Operation = Op;
}

Operators Operator::GetOperator(){
	return Operation;
}

RelOperator::RelOperator(RelOperators RelOp)
: ExpressionItem( RelOperatorItem, &RelationOperatorsText[RelOp] ) {
	/*
	switch (RelOp){
	case LessThan: ExpressionItem::SetText("<"); break;
	case GreaterThan: ExpressionItem::SetText(">"); break;
	case Equal: ExpressionItem::SetText("=="); break;
	case NotEqual: ExpressionItem::SetText("!="); break;
	case LessThanOrEqual: ExpressionItem::SetText("<="); break;
	case GreaterThanOrEqual: ExpressionItem::SetText(">="); break;
	}
	*/
	Relation = RelOp;
}

RelOperators RelOperator::GetOperator(){
	return Relation;
}

IntConstant::IntConstant(int value, CString *iText) 
: ExpressionItem (IntegerConst) {
	if (iText == NULL){
		char intText[30];
		wsprintf(intText,"%i",value);
		ExpressionItem::SetText(new CString(intText));
	}
	else
		ExpressionItem::SetText(iText);
	IntegerConstant = value;
}

double IntConstant::GetDoubValue() const{
	return (double) IntegerConstant;
}

int IntConstant::GetIntValue() const {
	return IntegerConstant;
}

CString IntConstant::ValueToString(){
	int nCopy = IntegerConstant;
	CString StringValue;
	do {
		StringValue.Insert(0,char(nCopy % 10 + '0'));
		nCopy /= 10;
	} while (nCopy > 0);
	return StringValue;
}

DoubConstant::DoubConstant(double value, CString * dText)
: ExpressionItem(DoubleConst) {
	if (dText == NULL){
		char doubText[15];
		int a = (int) value;
		int b = (int)((value - (double) a) * 10000.0);
		char doubText2[15];
		wsprintf(doubText2, "%i",b);
		
		//for (int i = 4; i >= 0; i--){
		//	if (doubText2[i] == '0'){
		//		doubText2[i] = '\0';
		//		break;
		//	}
		//	else
		//		break;
		//}
		
		wsprintf(doubText,"%i.%s",a,doubText2);
		ExpressionItem::SetText(new CString(doubText));
	}
	else 
		ExpressionItem::SetText(dText);

	DoubleConstant = value;
}

int DoubConstant::GetIntValue() const{
	return (int) DoubleConstant;
}

double DoubConstant::GetDoubValue() const{
	return DoubleConstant;
}

CString DoubConstant::ValueToString(){
	int nCopy = DoubleConstant * 10000;
	CString StringValue;
	int dPlace = 0;
	do {
		StringValue.Insert(0,char(nCopy % 10 + '0'));
		nCopy /= 10;
		dPlace++;
		if (dPlace == 4)
			StringValue.Insert(0,'.');
		if (nCopy == 0 && dPlace <= 4)
				StringValue.Insert(0,'0');
	} while (nCopy > 0);
	return StringValue;
}

LPthesis::LPthesis() 
: ExpressionItem(LeftParenthesis,&ExpressionItemsSpecific[3][0]) { }

RPthesis::RPthesis() 
: ExpressionItem(RightParenthesis,&ExpressionItemsSpecific[3][1]) { }

/*
Text::Text()
: ExpressionItem(TextItem, "") { }

Text::Text(CString t)
: ExpressionItem(TextItem, t) { }

Text::SetText(CString t){
	ExpressionItem::SetText(t);
}
*/

Test::Test() {
//Array<BoolExpression> BStatements;
	nFlow = 0;
}

BoolExpression::BoolExpression() {  
	nActions = 0;
	nItems = 0;
	ExpDescription = "";
}

void BoolExpression::SetType(FlowTypes F) { 
	flowType = F;
}

CString BoolExpression::ToString(){
	CString tempString;
	for (int i = 1; i < nItems; i++){
		tempString+= *GetText(i);
	}
	return tempString;
}

BOOL BoolExpression::ExpressionTF(){
	
	if (nItems > 1){
		Array<BoolOperators> boolArray(nItems-1);

		for (int i = 1; i < nItems; i++){
			switch (Items[i]->whichItem){
			case LeftParenthesis: boolArray[i-1] = LP; break;
			case RightParenthesis: boolArray[i-1] = RP; break;
			case SubExpressionItem: 
				boolArray[i-1] = (static_cast<SubExpression *>(Items[i])->EvaluateTF() ? True : False); break;
			case BoolOperatorItem: 
				boolArray[i-1] = (static_cast<BoolOperator *>(Items[i])->bOp); break;
			default: break;
			}
		}
		return ExpressionTFHelper(boolArray);
	}
	else
		return FALSE;
}

BOOL BoolExpression::ExpressionTFHelper(Array<BoolOperators> &bArray){

	int nItems = bArray.length;
	int lpPos = 1;
	int pCount = 0;
	for (int pos = 0; pos < nItems; pos++){
		
		if (bArray[pos] == LP){
			lpPos = pos;
			pCount = 1;
			while (pCount > 0 && pos < nItems - 1){
				pos++;
				if (bArray[pos] == RP){
					pCount--;
					if (pCount == 0){
						Array<BoolOperators> sBArray(pos - lpPos - 1);
						for (int i = 0;  i < pos - lpPos - 1; i++)
							sBArray[i] = bArray[i + lpPos + 1];
						bArray.Remove(lpPos, pos - lpPos + 1);
						if (nItems > 0){
							BoolOperators result = (ExpressionTFHelper(sBArray) == TRUE ? True : False);
							bArray.Insert(result, lpPos);
						}
						nItems -= (pos - lpPos);
						pos -= (pos - lpPos);
					}
				}
				else if (bArray[pos] == LP)
					pCount++;
				
			}
		}
	}
	
	for (pos = 1; pos < nItems && nItems > 2; pos++){
		
		if (bArray[pos] == And){
			BoolOperators result = ((bArray[pos-1] == True) && (bArray[pos+1] == True) ? True : False );
			bArray.Remove(--pos, 3);
			bArray.Insert(result, pos);
			nItems -= 2;	
		}
	}

	for (pos = 1; pos < nItems && nItems > 2; pos++){
		
		if (bArray[pos] == Or){
			BoolOperators result = ((bArray[pos-1] == True) || (bArray[pos+1] == True) ? True : False );
			bArray.Remove(--pos, 3);
			bArray.Insert(result, pos);
			nItems -= 2;	
		}
	}
	return (bArray[0] == True);
}

void BoolExpression::InsertAction(Action *aItem, int whichPos){
	Actions.Insert(aItem, whichPos);
	nActions++;
}

CString BoolExpression::GetActionText(int whichPos){
	if (whichPos < nActions) 
		return Actions[whichPos]->description;
	else
		return CString("");
}

BOOL BoolExpression::PerformActions(){
	for (int a = 0; a < nActions; a++){
		Actions[a]->DoAction();	
	}
	return TRUE;
}

/*	FlowTypes flowType; // to know if this BoolExpression is an if, elseif, or else type.
	// the 'if' or decision making part of the bool expression will inherit from Expression
	// the then making part will be handled by class Action
	Array<Action> Actions;
	int nActions;
*/


SubExpression::SubExpression() 
: ExpressionItem (SubExpressionItem /*,text */){
		whichExp = NULL;
}

SubExpression::SubExpression(Expression *wExp, CString *newText) 
: ExpressionItem (SubExpressionItem, newText) {
	whichExp = wExp;
}
	
SubExpression::SubExpression(Expression &wExp, CString *newText) 
: ExpressionItem (SubExpressionItem, newText) {
	whichExp = &wExp;
}

BOOL SubExpression::EvaluateTF(){
	return (whichExp->EvaluateTF());
}

double SubExpression::GetDoubValue() const {
	ExpressionItem *eItem = whichExp->Evaluate();
	return (eItem->GetDoubValue());
}

int SubExpression::GetIntValue() const {
	ExpressionItem *eItem = whichExp->Evaluate();
	return (eItem->GetIntValue());
}

BoolOperator::BoolOperator()
:ExpressionItem(BoolOperatorItem) {
	bOp = And;
}

BoolOperator::BoolOperator(BoolOperators b, CString *text)
:ExpressionItem(BoolOperatorItem, text){
	bOp = b;
}

FlowControl::FlowControl() 
:ExpressionItem(FlowControlItem){
	fType = If;
}

FlowControl::FlowControl(FlowTypes f, CString *text)
:ExpressionItem(FlowControlItem, text){
	fType = f;
}



