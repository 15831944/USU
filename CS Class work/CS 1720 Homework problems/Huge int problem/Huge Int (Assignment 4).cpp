// will this save changes to assignment 3 as well?
/*
A31. {similar to 8.16} A machine with 32 bit integers can represent integers 
in the range of approximately -2 billion to + 2 billion.  This fixed-size 
restriction is rarely troublesome. But there are applications in which we 
would like to be able to use a much wider range of integers. This is what 
C++ was built to do, namely create powerful new data types. Consider class 
HugeInt of Fig 8.8.  Study the class carefully, then
        a. Overload the * multiplication operator.
        b. Overload all the relational and equality operators.
*/

/* this program will be designed to handle numbers of any size, the only limits 
are the computers memory and the time required for data entry.*/



#include <iostream.h>
#include <iomanip.h>
#include "huge int(Assignment 4).h"

void main(void){

	hugeint num1 = "7253491260";
	hugeint num2 = "378";
	//cout << "Enter two numbers as large as you like (you can try up to 1000 digits):" << endl;
	//cin >> num1 >> num2;
	//cout << "The first number plus the second is: " << endl
	//     << num1 + num2 << endl
	//	  << "The first number times the second is: " << endl
	//     << num1 * num2 << endl;
	cout << "Num1 / Num2 = " << num1 / num2;
}