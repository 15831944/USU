//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  5-DD-97
//  Chapter x, Problem x.xx
//  Program description

#include <iostream.h>
int Fib(int n);

void main() {
int n;
cout << "What term of the Fibonacci sequence: " << flush;
cin >> n;
cout << "The fibonacci number is: " << Fib(n-1);
}
int Fib(int n) {
if (n < 2)
	return 1;
else
	return Fib(n-1)+Fib(n-2);
}
