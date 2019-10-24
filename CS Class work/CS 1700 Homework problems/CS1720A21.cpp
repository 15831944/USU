//A21. Write a complete program including specification, driver (client) program and 
//implementation using the class Complex with public attributes and functions that 
//are not members of the class. Be sure to include a function print that will print
//a complex number in the usual form. Also include a function input that will allow 
//the input of a complex number in the usual form.
#include <iostream.h>

class Complex {
	public:
		Complex();
		void PerformOp(const char Operator);
		void Input();
		void Print();
private:
		double RealP;
		double ImagP;
}

Complex::Complex(){
	RealP = 0;
	ImagP = 0;
}

Complex Complex::Input(){
	char Command[40];
	cout << "Enter an operation in the form a + bi + c + di." << endl;
	cout << "valid operators are: +,-,*,/,magnitude(a + bi)" << endl;
	cout << "Enter an operation now: ";
	cin.getline(Command,40);
	if (strcmp(Command,"exit") == 0 || *Command == '\0')
			break;
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

void main(void){
}

/*
A22. Modify your Complex class so that the attributes are private and the functions are members of the class.
Include a function, print, that will print a complex number and use it to output the complex numbers that are
calculated. Also include a function input that will allow the input of a complex number in the usual form.

A23. Modify your Complex class to include good identified output and input of complex numbers in the form a + bi, overload
the +, -, *, /, <<, >>, >, <, <=, >=, ==, !=operators so that basic complex number arithmetic can be done in the usual way such as:
z = x + y;
z = x - y,
z = x*y,
z = x/y, and 
cin >> x >> y;
cout << x << y; 
x == y; x != y; x >= y; x <= y; x < y; x > y; where x, y, and z are complex numbers.

A complex number is considered to be greater than another complex number if the magnitude of the first is greater than the
second. Two complex numbers are == only if the real1 == real2 and imaginary1 == imaginary2. Be sure you use doubles for the
real and imaginary part of the complex number.

I can now assume that your constructors work, so for A23, input several complex numbers and test all the functions with the
numbers that are input by the user.

A24. {6.8} Modify the Time class of Fig. 6.10 to include a tick member function that increments the time stored in a Time object
by one second. The time object should always remain in a consistent state. Write a driver program that tests the tick member
function in a loop that prints the time in standard format during each iteration of the loop to illustrate that the tick member
function works correctly. Be sure to test the following cases:
    a) Incrementing into the next minute.
    b) Incrementing into the next hour.
    c) Incrementing into the next day (i.e. 12:59:59 PM to 12:00:00 AM). */