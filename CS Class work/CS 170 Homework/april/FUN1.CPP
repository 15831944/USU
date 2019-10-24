//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-30-97
//  Chapter 5
//  fun learning functions #1

#include <iostream.h>
#include <bool.h>

int min(int a, int b);
int max(int a, int b);
int GetANumber();
void main() {
	int Num1 = GetANumber();
	int Num2 = GetANumber();
	cout << "The smaller number is: " << min(Num1,Num2) << endl;
	cout << "The larger number is: " << max(Num1,Num2);
}
//Min function
int min(int a, int b) {
if (a < b)
	return a;
else
	return b;
}
// max function
int max(int a, int b) {
if (a < b)
	return b;
else
	return a;
}
// get a number
int GetANumber () {
int Number;
cout << "Enter an integer: " << flush;
cin >> Number;
return Number;
}

