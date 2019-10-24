#include <afxwin.h>
#include "Event.h"
#include "global defs.h"


char * ExpressionItems[] = {"Variable","Operator","Relational Operator",
"Parenthesis","Constant Value"};
char * ExpressionItemsSpecific[4][6] = 
{"Input Location","User Flag","Program Run Time","Timer","","",
"+","-","*","/","%","",
"< (Less than)","> (greater than)",
"== (Equal)","!= (not equal)",
"<= (Less than or equal)",">= (greater than or equal)",
"(",")","","","",""};

char * InstructionText[] = {
"Please select the type of variable to add",
"Please select the operator to add to the expression",
"Please choose a relational operator to insert",
"Scroll cursor to insert location for parenthesis",
"Please enter a constant value"};

Event::Event() :/* Timers(1),*/ Statements(3) {
	// Initialize Timers to one, Statements to three
	//Timers[1].SetParentEvent(this);
	nStatements = 0;
	//nTimers = 0;
}

Event::~Event() {
 	//Timers(0);
	//Statements(0);
}

/*
void Event::CreateExpression(ItemTypes itemType){
	// Do I really need this function
}

const Event & Event::operator=(const Event &rEvent){
	nStatements = rEvent.nStatements;
	Statements = rEvent.Statements;
	return *this;
}
*/
Expression::Expression() /*: Items(3)*/ {
	// initially set the array to have 3 members.
	// for example i < 3 would take three objects of
	// class ExpressionItems.
	// this can expand if necessary.  
	//nItems = 0;
	//ExpDescription = "";
}

Expression::~Expression() {
	//Items(0);
}

/*
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

	}
}

Expression::Expression(Expression *source, int firstItem, int lastItem)
: Items(lastItem - firstItem + 1)
{
	int pos = 0;
	for (int i = firstItem; i < lastItem; i++, pos++){
		//memcpy(Items[pos], source->Items[i], sizeof(ExpressionItem)); 
		CopyItem(Items[pos],source->Items[i]);
	}
	nItems = lastItem - firstItem;
}

/*
Expression::Expression(Expression *pExpression, int firstItem, int lastItem)
: Items(lastItem - firstItem + 1)
{
	int iPos = 0;
	int nItems = 0;
	for (int i = firstItem; i <= lastItem; i++){
		Items[iPos++] = pExpression->Items[i];
		nItems++;
	}
}
*/
/*
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
	return TRUE;
}
*/
/*
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
			while (pCount > 0 && pos < ExpEval->nItems){
				pos++;
				if (ExpEval->Items[pos]->whichItem == RightParenthesis){
					pCount--;
					if (pCount == 0){
						Expression subExp(ExpEval, lpPos + 1, pos);
						ExpEval->Items.Remove(lpPos, pos - lpPos + 1);
						ExpEval->Items.Insert(subExp.Evaluate(), lpPos);
						ExpEval->nItems -= (pos - lpPos);
						pos -= (pos - lpPos);
					}
				}
				else if (ExpEval->Items[pos]->whichItem == LeftParenthesis)
					pCount++;
				
			}
			
			//Expression subExpression(this, pos + 1, endPos - 1);
			//subExpression.Evaluate();
			
			//Items[pos] = subExpression.Evaluate();
			//Items.Remove(pos + 1, endPos - pos + 1);
			//Items.Remove(pos, endPos - pos + 1);
			//nItems -= 2;//(endPos - pos);
			//Items.Insert(sExp, pos);
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
	
	return returnItem;
}

BOOL Expression::CheckExpression(){
	// check for balanced paranthesis
	// check for value - operator - value
	int lPs = 0;
	int rPs = 0;
	ItemTypes lastItem = NullItem;
	ItemTypes currItem = NullItem;
	
	BOOL ExpIsGood = TRUE;
	for (int pos = 0; pos < nItems && ExpIsGood; pos++){
		currItem = Items[pos]->whichItem;
		
		switch (currItem){
		case LeftParenthesis:
			lPs++;
			break;
		case RightParenthesis:
			rPs++;
			break;
		case VariableItem:
		case IntegerConst:
		case DoubleConst:
			currItem = ValueItem;
			if (lastItem == ValueItem)
				ExpIsGood = FALSE;
			break;
		case OperatorItem:
		case RelOperatorItem:
			if (lastItem == OperatorItem || lastItem == RelOperatorItem)
				ExpIsGood = FALSE;
			break;
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
		MessageBox(NULL, "Cannot evaluate expression.  Value missing.","Invalid Expression",MB_ICONINFORMATION);
		return FALSE;
	}
}

const char * Expression::GetText(int whichPos){
	return Items[whichPos]->GetItemText();
}
*/
CString Expression::ToString(){
	char newWord[30];
	CString tempString;
	int textPos = 0;
	/*
	for (int i = 0; i < nItems; i++){
		strcpy(newWord,GetText(i));
		tempString.Insert(textPos,newWord);
		textPos += strlen(newWord);
	}
	*/
	return tempString;
}

/*
ExpressionItem::ExpressionItem(ItemTypes iType, const char *Text , int AInfo ){//= NULL = NULL
	whichItem = iType;
	if (Text){
		strcpy(ItemText, Text);
		int textLength = strlen(ItemText);
		for (int i = textLength - 1; i > 0; i--){
			if (ItemText[i] != ' ') break;
		}
		ItemText[i+1] = ' ';
		ItemText[i + 2] = '\0';
	}
	AddInfo = AInfo;
}

ExpressionItem::ExpressionItem(){
	whichItem = VariableItem;
	strcpy(ItemText,"Messed up dude");
	MessageBox(NULL, "Default Constructor called for expression item.  This should not happen","Error",MB_ICONEXCLAMATION);
}

ExpressionItem::~ExpressionItem(){
}

void ExpressionItem::SetText( const char * NewText ){
	strcpy(ItemText, NewText);
	int textLength = strlen(ItemText);
	for (int i = textLength - 1; i > 0; i--){
		if (ItemText[i] != ' ') break;
	}
	ItemText[i+1] = ' ';
	ItemText[i + 2] = '\0';
	
}

const char * ExpressionItem::GetItemText(){
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
			int value;
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
			double value;
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
			int value;
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
			int value;
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
		whichItem == DoubleConst || whichItem == ConstantValue );
}

Variable::Variable(VariableTypes v, const char *vText )//=NULL
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
: Variable(InputLocation, &AvailableInputLocations[whichLocation][4] ) {
	whichLoc = whichLocation;
}

int InputLoc::GetIntValue() const{
	return (int) InputLocValue[whichLoc];
}

double InputLoc::GetDoubValue() const{
	return InputLocValue[whichLoc];
}

Flag::Flag(int wFlag, int wModify)
: Variable(FlagValue, FlagNames[wFlag][wModify]) {
	whichFlag = wModify * 0x80 + wFlag;	
}

double Flag::GetDoubValue() const{
	return (double) FlagStatus[whichFlag & 0x7F][whichFlag & 0x80]; 
}
int Flag::GetIntValue() const {
	return FlagStatus[whichFlag & 0x7F][whichFlag & 0x80]; 
}

ProgRunTime::ProgRunTime()
: Variable(ProgramRunTimeVar, "Prog Run Time") {

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
	ExpressionItem::SetText(tText);
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
: ExpressionItem(OperatorItem, NULL, Op) {
	
	switch (Op){
	case Add: ExpressionItem::SetText("+"); break;
	case Subtract: ExpressionItem::SetText("-"); break;
	case Multiply: ExpressionItem::SetText("*"); break;
	case Divide: ExpressionItem::SetText("/"); break;
	case Modulus: ExpressionItem::SetText("%"); break;
	}

	Operation = Op;
}

Operators Operator::GetOperator(){
	return Operation;
}

RelOperator::RelOperator(RelOperators RelOp)
: ExpressionItem( RelOperatorItem, NULL, RelOp) {
	switch (RelOp){
	case LessThan: ExpressionItem::SetText("<"); break;
	case GreaterThan: ExpressionItem::SetText(">"); break;
	case Equal: ExpressionItem::SetText("=="); break;
	case NotEqual: ExpressionItem::SetText("!="); break;
	case LessThanOrEqual: ExpressionItem::SetText("<="); break;
	case GreaterThanOrEqual: ExpressionItem::SetText(">="); break;
	}
	Relation = RelOp;
}

RelOperators RelOperator::GetOperator(){
	return Relation;
}

IntConstant::IntConstant(int value, const char *iText) 
: ExpressionItem (IntegerConst) {
	if (iText == NULL){
		char intText[8];
		wsprintf(intText,"%i",value);
		ExpressionItem::SetText(intText);
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

DoubConstant::DoubConstant(double value, const char * dText)
: ExpressionItem(DoubleConst) {
	if (dText == NULL){
		char doubText[12];
		int a = (int) value;
		int b = (value - (double) a) * 10000;
		char doubText2[5];
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
		ExpressionItem::SetText(doubText);
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

LPthesis::LPthesis() 
: ExpressionItem(LeftParenthesis,"(") { }

RPthesis::RPthesis() 
: ExpressionItem(RightParenthesis,")") { }

*/

