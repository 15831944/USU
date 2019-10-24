#ifndef MY_EVENT_H
#define MY_EVENT_H

#include <afx.h>
#include "Array.h"

#define	FROMSCREEN	TRUE
#define TOSCREEN	FALSE


typedef int		BOOL;
/*
int __stdcall MessageBoxA(
    HWND hWnd ,
    LPCSTR lpText,
    LPCSTR lpCaption,
    UINT uType);
*/

enum ItemTypes {VariableItem, OperatorItem, RelOperatorItem, Parenthesis,
	ConstantValue, SubExpressionItem, IntegerConst, DoubleConst, LeftParenthesis, RightParenthesis, 
	ValueItem, FlowControlItem, BoolOperatorItem, TextItem, NullItem };
enum VariableTypes {InputLocation, FlagValue, ProgramRunTimeVar, TimerVariable };
enum Operators {Add, Subtract, Multiply, Divide, Modulus};
enum RelOperators {LessThan, GreaterThan, Equal, NotEqual, LessThanOrEqual, GreaterThanOrEqual};
enum BoolOperators {And, Or, Not, Xor, False, True, LP, RP};
enum FlowTypes {If, ElseIf, Else};
enum ActionTypes {SetInputLocationItem,ToggleFlagItem,SetTimerItem,DisplayMessageItem,
	WriteLogItem,SetTestItem,SetVariableItem,WriteToFileItem};

extern CString ExpressionItems[];
extern CString ExpressionItemsSpecific[][6];
extern CString InstructionText[];

class Expression;
class ExpressionItem;
class Timer;
class BoolExpression;
class Test;
class Action;

class Event {
	friend class EditExpression;
	friend class Timer;
	friend class EditEvent;
	friend class CChooseVariable;
public:
	Event();
	~Event();
	BOOL PerformTest();
	//void CreateExpression(ItemTypes itemType);
	//const Event & operator=(const Event &rEvent);

	Array<Expression> Statements;
	int nStatements;
	
	Array<Test> Tests;
	int nTests;
	int curTest;

protected:
	Array<int> Timers;
	int nTimers;
	CString Title;
private:

	// make new array class
};

class Expression {
	friend class EditExpression;
	friend class EditEvent;
	friend class EditTest;
	friend class CChooseVariable;
public:
	Expression();
	Expression(const Expression &source);
	~Expression();
	Expression(Expression *pExpression, int firstItem, int lastItem);
	ExpressionItem * Evaluate(Expression *ExpEval = NULL);
	BOOL EvaluateTF();
	void InsertItem(ExpressionItem *eItem, int whichPos);
	void RemoveItem(int whichPos);
	CString * GetText(int whichPos);
	BOOL CheckExpression();
	void CopyItem(ExpressionItem *&destination, const ExpressionItem *source);	
	virtual CString ToString();
	BOOL IsComparison;
protected:
	Array <ExpressionItem *> Items;
	int nItems;
	CString ExpDescription;

};

class Test {
	friend class EditTest;
	friend class EditEvent;
	friend class Event;
public:
	Test();

protected:
	Array<BoolExpression> BStatements;
	int nFlow;
};

class BoolExpression : public Expression {
	friend class EditTest;
	friend class EditEvent;
	friend class Event;
public:
	BoolExpression();
	void SetType(FlowTypes F);
	virtual CString ToString();
	BOOL ExpressionTF();
	BOOL ExpressionTFHelper(Array<BoolOperators> &bArray);
	void InsertAction(Action *aItem, int whichPos);
	CString GetActionText(int whichPos);
	BOOL PerformActions();
protected:
	FlowTypes flowType; // to know if this BoolExpression is an if, elseif, or else type.
	// the 'if' or decision making part of the bool expression will inherit from Expression
	// the then making part will be handled by class Action
	Array<Action *> Actions;
	int nActions;
};

class Action {
	friend class BoolExpression;
public:
	class SetInputLocation;
	class ToggleFlag;
	class SetTimer;
	class DisplayMessage;
	class WriteLog;
	class SetTest;
	class SetVariable;
	class WriteToFile;

	Action();
	Action(ActionTypes a, CString c = "");
	SetDescription(CString);
	virtual void DoAction();
protected:
	ActionTypes aItem;
	CString description;
};

class SetInputLocation : public Action {
public:
	SetInputLocation();
	SetInputLocation(int wLocation, ExpressionItem *v);
	virtual void DoAction();
protected:
	int whichLocation;
	ExpressionItem *value;
};

class ToggleFlag : public Action {
public:
	ToggleFlag();
	ToggleFlag(int wSet, int wFlag, ExpressionItem *v);
	virtual void DoAction();
protected:
	int whichSet;
	int whichFlag;
	ExpressionItem *value;
};

class SetTimer : public Action {
public:
	SetTimer();
	SetTimer(int wTimer);
	virtual void DoAction();
protected:
	int whichTimer;
};

class DisplayMessage : public Action {
public:
	DisplayMessage();
	DisplayMessage(CString text, int mType);
	virtual void DoAction();
protected:
	CString MessageText;
	int MessageType;
};

class WriteLog : public Action {
public:
	WriteLog();
	WriteLog (CString fName, Expression *m);
	virtual void DoAction();
protected:
	CString fileName;
	Expression *Message;
};

class SetTest : public Action {
public:
	SetTest();
	SetTest(int wTest);
	virtual void DoAction();
protected:
	int whichTest;
};

class SetVariable : public Action {
public:
	SetVariable();
	SetVariable(ExpressionItem *d, ExpressionItem *s); 
	virtual void DoAction();
protected:
	ExpressionItem *destination;
	ExpressionItem *source;
};

class WriteToFile : public Action {
public: // write Input Locations to a file?  I'm not sure
		// what I want this action to do yet.
	WriteToFile();
	WriteToFile(CString fileName);
	virtual void DoAction();
protected:
	CString fileName;
};



class ExpressionItem {
	friend class Expression;
	friend class EditExpression;
	friend class EditTest;
	friend class BoolExpression;
public:
	
	ExpressionItem(ItemTypes iType, CString *Text = NULL);
	ExpressionItem();
	virtual ~ExpressionItem();
	ExpressionItem *DoOperation(const ExpressionItem *left, const ExpressionItem *right);
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
	virtual CString ValueToString();
	//virtual int GetAddInfo() const;
	
	CString * GetItemText();
	void SetText(CString *);
	BOOL IsValue();
	
private:
	
	ItemTypes whichItem;
	CString * ItemText;
	//int AddInfo;
	
};


class Variable : public ExpressionItem {
	friend class ExpressionItem;
	friend class Expression;
public:
	Variable(VariableTypes v, CString *vText = NULL);
	//virtual ~Variable(); no dynamic objects, no need for special
	// destructor
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
private:
	VariableTypes vType;
};

class InputLoc : public Variable {
	friend class Expression;
public:
	InputLoc(int whichLocation);
	virtual int GetIntValue() const;
	virtual double GetDoubValue() const;
private:
	int whichLoc;
};

class Flag : public Variable {
	friend class Expression;
public:
	Flag(int whichFlag, int whichModify);
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
private:
	int whichFlag;
};

class ProgRunTime : public Variable {
public:
	ProgRunTime();
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
};

class Timer : public Variable {
	friend class Expression;
public:
	Timer();
	Timer(int wTimer);
	void SetParentEvent(Event *pEvent);
	virtual ~Timer();
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
protected:
	Event *parentEvent;
	int whichTimer;

};

/*
class ProgramVariable : public Variable {
	friend class Expression;
	friend class ProgramVariables;
public:
	ProgramVariable();
	ProgramVariable(int value);
	ProgramVariable
*/

class Operator : public ExpressionItem {
	friend class Expression;
public:
	Operator(Operators Op);
	Operators GetOperator();
protected:
	Operators Operation;
};

class RelOperator : public ExpressionItem {
	friend class Expression;
public:
	RelOperator(RelOperators RelOp);
	RelOperators GetOperator();
protected:
	RelOperators Relation;
};

class IntConstant : public ExpressionItem {
	friend class Expression;
public:
	IntConstant(int value, CString * iText = NULL); 
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
	virtual CString ValueToString();
protected:
	int IntegerConstant;
};

class DoubConstant : public ExpressionItem {
	friend class Expression;
public:
	DoubConstant(double value, CString * dText = NULL); 
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
	virtual CString ValueToString();
protected:
	double DoubleConstant;
};

class LPthesis : public ExpressionItem {
public:
	LPthesis();
};

class RPthesis : public ExpressionItem {
public:
	RPthesis();
};

class SubExpression : public ExpressionItem {
	friend class EditTest;
	friend class Expression;
public:
	SubExpression();
	SubExpression(Expression *wExp, CString *newText = NULL); 
	SubExpression(Expression &wExp, CString *text = NULL);
	BOOL EvaluateTF();
	double GetDoubValue() const;
	int GetIntValue() const;
private:
	Expression *whichExp;
};

class BoolOperator : public ExpressionItem {
	friend BoolExpression;
public:
	BoolOperator();
	BoolOperator(BoolOperators b, CString * text = NULL);
private:
	BoolOperators bOp;
};

class FlowControl : public ExpressionItem {
public:
	FlowControl();
	FlowControl(FlowTypes f, CString *text = NULL);
private:
	FlowTypes fType;
};

/*
class Text : public ExpressionItem {
public:
	Text();
	Text(CString t);
	SetText(CString t);
private:
};
*/


#endif