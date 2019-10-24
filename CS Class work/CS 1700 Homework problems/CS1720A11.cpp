/*CS1720  Assignment 1


A11. Write a complete program including prototypes, a driver program, and the implementation
which uses complex numbers without a class. This is similar to what we did first with rational
numbers. The real and imaginary parts of the complex numbers should be of type double. 
Be sure to include a function print that will print a complex number in the usual form. 
Also include a function input that will allow the input of a complex number in the usual form.
Input and output should be as you would expect for complex numbers, for example 2.3+5.4i,
 -2.3+5.4i, 2.6-5.6i, -5.4-7.53i. In other words your I/O should look just as it would on a 
sheet of paper where you were writing complex numbers.*/

#include <iostream.h>
#include <iomanip.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void AssignValues(char *, double &, double &, double &, double &, char &);
void PerformOperation(const double &a, const double &b, const double &c, const double &d, 
							 const char &Operator, double &e, double &f);
void PrintResult(const double &e, const double &f);

void main(void){
	
	double a, b, c, d;
	double e, f;
	char Operator;
	char Command[40];
	
	cout << "This program performs operations using complex numbers." << endl;
	while (1){
		cout << "Enter an operation in the form a + bi + c + di." << endl;
		cout << "valid operators are: +,-,*,/,magnitude(a + bi)" << endl;
		cout << "Enter an operation now: ";
		cin.getline(Command,40);
		
		if (strcmp(Command,"exit") == 0 || *Command == '\0')
			break;
		
		AssignValues(Command, a, b, c, d, Operator);
		PerformOperation(a, b, c, d, Operator, e, f);
		cout << "Result = ";
		PrintResult(e, f);
		
	}

}

void AssignValues(char *Command, double &a, double &b, double &c, double &d, char &Operator){
	char Astr[10];
	char *tokenPtr;
	if (*Command == 'm'){
		tokenPtr = strtok(Command, "(");
		tokenPtr = strtok(NULL, "+");
		strncpy(Astr, tokenPtr, 10);
		a = atof(Astr);
		tokenPtr = strtok(NULL, "i");
		strncpy(Astr, tokenPtr, 10);
		b = atof(Astr);
		Operator = 'm';
	}
	else{
		tokenPtr = strtok(Command, " +*/i(");
		strncpy(Astr, tokenPtr, 10);
		a = atof(Astr);
		tokenPtr = strtok(NULL, " +*/i)");
		strncpy(Astr, tokenPtr, 10);
		b = atof(Astr);
		tokenPtr = strtok(NULL, " ");    //if the user does not enter a space after the
		Operator = *tokenPtr;				//operator, an error will be generated here.
		tokenPtr = strtok(NULL, " +*/i(");
		strncpy(Astr, tokenPtr, 10);
		c = atof(Astr);
		tokenPtr = strtok(NULL, " +*/i)");
		strncpy(Astr, tokenPtr, 10);
		d = atof(Astr);
	}
}

void PerformOperation(const double &a, const double &b, const double &c, const double &d, 
							 const char &Operator, double &e, double &f){
	/*Arithmetic of complex numbers is defined by:

	(a+bi) + (c+di) = (a+c) + (b+d)i                                       // addition
	(a+bi) - (c+di) = (a-c) + (b-d)i                                          // subtraction
	(a+bi)*(c+di) = (ac-bd) + (ad+bc)i                                   // multiplication
	(a+bi)/(c+di) = (ac+bd)/(c2+d2)  + ((bc-ad)/(c2+d2))i         // division
	magnitude(a+bi) = sqrt(a2 + b2)                                        // magnitude*/
	switch (Operator){
		case '+':
		e = a + c;
		f = b + d;
		break;
		case '-':
		e = a - c;
		f = b - d;
		break;
		case '*':
		e = a * c - b * d;
		f = a * d + b * c;
		break;
		case '/':
		e = (a * c + b * d) / (c * c + d * d);
		f = (b * c - a * d) / (c * c + d * d);
		break;
		case 'm':
		e = sqrt(a * a + b * b);
		f = 0.0;
		break;
	}
}
void PrintResult(const double &e, const double &f){
	cout << e;
	if (f != 0.0)
		cout << " + " << f << "i";
	cout << endl;

}

