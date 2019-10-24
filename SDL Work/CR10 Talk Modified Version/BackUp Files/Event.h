#ifndef MY_EVENT_H
#define MY_EVENT_H


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
	ConstantValue, IntegerConst, DoubleConst, LeftParenthesis, RightParenthesis, 
	ValueItem, NullItem };
enum VariableTypes {InputLocation, FlagValue, ProgramRunTimeVar, TimerVariable };
enum Operators {Add, Subtract, Multiply, Divide, Modulus};
enum RelOperators {LessThan, GreaterThan, Equal, NotEqual, LessThanOrEqual, GreaterThanOrEqual};

extern char * ExpressionItems[];
extern char * ExpressionItemsSpecific[][6];
extern char * InstructionText[];


class Expression;
class ExpressionItem;
class Timer;

class Event {
	friend class EditExpression;
	friend class Timer;
public:
	Event();
	~Event();
	//void CreateExpression(ItemTypes itemType);
	//const Event & operator=(const Event &rEvent);

	Array<Expression> Statements;
	int nStatements;
protected:
	//Array<int> Timers;
	//int nTimers;
private:

	// make new array class
};

class Expression {
	friend class EditExpression;
	friend class EditEvent;
public:
	Expression();
	//Expression(const Expression &source);
	~Expression();
	//Expression(Expression *pExpression, int firstItem, int lastItem);
	//ExpressionItem * Evaluate(Expression *ExpEval = NULL);
	//BOOL EvaluateTF();
	//void InsertItem(ExpressionItem *eItem, int whichPos);
	//void RemoveItem(int whichPos);
	//const char * GetText(int whichPos);
	//BOOL CheckExpression();
	//void CopyItem(ExpressionItem *&destination, const ExpressionItem *source);	
	CString ToString();
protected:
	//Array <ExpressionItem *> Items;
	//int nItems;
	CString ExpDescription;
};

class ExpressionItem {
	friend class Expression;
	friend class EditExpression;
public:
	/*
	ExpressionItem(ItemTypes iType, const char *Text = NULL, int AInfo = NULL);
	ExpressionItem();
	virtual ~ExpressionItem();
	ExpressionItem *DoOperation(const ExpressionItem *left, const ExpressionItem *right);
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
	//virtual int GetAddInfo() const;
	
	const char * GetItemText();
	void SetText(const char *);
	BOOL IsValue();
	*/
private:
	/*
	ItemTypes whichItem;
	char ItemText[31];
	int AddInfo;
	*/
};

/*
class Variable : public ExpressionItem {
	friend class ExpressionItem;
	friend class Expression;
public:
	Variable(VariableTypes v, const char *vText = NULL);
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
	IntConstant(int value, const char * iText = NULL); 
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
protected:
	int IntegerConstant;
};

class DoubConstant : public ExpressionItem {
	friend class Expression;
public:
	DoubConstant(double value, const char * dText = NULL); 
	virtual double GetDoubValue() const;
	virtual int GetIntValue() const;
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

*/


#endif