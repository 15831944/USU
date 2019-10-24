
#include <iostream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <math.h>

class complex {
	public:
		complex(){ImagP = RealP = 0.0;};
		complex PerformOp(const complex &, const char);
		void Input(complex &, char &);
		void PrintResult();
	private:
		double RealP;
		double ImagP;
};

void complex::Input(complex &a, char &Operator){
	char Command[40];
	cout << "Enter an operation in the form a + bi + c + di." << endl;
	cout << "valid operators are: +,-,*,/,magnitude(a + bi)" << endl;
	cout << "Enter an operation now: ";
	cin.getline(Command,40);
	if ((strcmp(Command,"exit") != 0) && (*Command != '\0')){
		char Astr[10];
		char *tokenPtr;
		if (*Command == 'm'){
			tokenPtr = strtok(Command, "(");
			tokenPtr = strtok(NULL, "+");
			strncpy(Astr, tokenPtr, 10);
			RealP = atof(Astr);
			tokenPtr = strtok(NULL, "i");
			strncpy(Astr, tokenPtr, 10);
			ImagP = atof(Astr);
			Operator = 'm';
		}
		else{
			tokenPtr = strtok(Command, " +*/i(");
			strncpy(Astr, tokenPtr, 10);
			RealP = atof(Astr);
			tokenPtr = strtok(NULL, " +*/i)");
			strncpy(Astr, tokenPtr, 10);
			ImagP = atof(Astr);
			tokenPtr = strtok(NULL, " ");    //if the user does not enter a space after the
			Operator = *tokenPtr;				//operator, an error will be generated here.
			tokenPtr = strtok(NULL, " +*/i(");
			strncpy(Astr, tokenPtr, 10);
			a.RealP = atof(Astr);
			tokenPtr = strtok(NULL, " +*/i)");
			strncpy(Astr, tokenPtr, 10);
			a.ImagP = atof(Astr);
		}
	}
}

complex complex::PerformOp(const complex &a, const char Operator){
	complex t;
	switch (Operator){
		case '+':
			t.RealP = RealP + a.RealP;
			t.ImagP = ImagP + a.ImagP;
			return t;//(RealP + a.RealP, ImagP + a.ImagP);//e = a + c; f = b + d;
		case '-':
			t.RealP = RealP - a.RealP;
			t.ImagP = ImagP - a.ImagP;
			return t;//(RealP - a.RealP, ImagP - a.ImagP);//e = a - c; f = b - d;
		case '*':
			t.RealP = RealP * a.RealP - ImagP * a.ImagP;
			t.ImagP = RealP * a.ImagP + ImagP * a.RealP;
			return t;//(RealP * a.RealP - ImagP * a.ImagP, RealP * a.ImagP + ImagP * a.RealP);
			//e = a * c - b * d; f = a * d + b * c;
		case '/':
			t.RealP = (RealP * a.RealP + ImagP * a.ImagP) / (a.RealP * a.RealP + a.ImagP * a.ImagP);
			t.ImagP = (ImagP * a.RealP - RealP * a.ImagP) / (a.RealP * a.RealP + a.ImagP * a.ImagP);
			return t;//((RealP * a.RealP + ImagP * a.ImagP) / (a.RealP * a.RealP + a.ImagP * a.ImagP),
				     //(ImagP * a.RealP - RealP * a.ImagP) / (a.RealP * a.RealP + a.ImagP * a.ImagP))
			//e = (a * c + b * d) / (c * c + d * d); f = (b * c - a * d) / (c * c + d * d);
		case 'm':
			t.RealP = sqrt(RealP * RealP + ImagP * ImagP);
			t.ImagP = 0.0;
			return t;//(sqrt(RealP * RealP + ImagP * ImagP), 0.0);//e = sqrt(a * a + b * b);f = 0.0;
		default:
			t.RealP = 0.0;
			t.ImagP = 0.0;
			return t;
		}
}
void complex::PrintResult(){
	cout << RealP;
	if (ImagP != 0.0)
		cout << " + " << ImagP << "i";
	cout << endl;

}

void main(void){
	complex a, b, c;
	char Operator;
	a.Input(b, Operator);
	c = a.PerformOp(b, Operator);
	c.PrintResult();
}