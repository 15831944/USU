// 362
// marks
// Mark Salisbury
// P362A32.cpp

#include <iostream.h>

void main(void){
	
	double a,  
		    b,
			 c;

	cout << "This program tells you if a triangle with given lengths could exist." << endl;
	cout << "Please enter the lengths of the three sides: ";

	cin >> a >> b >> c;

	if (((a + b) > c) && ((a + c) > b) && ((b + c) > a))
		cout << "This triangle could exist." << endl;
	else
		cout << "This triangle could not exist." << endl;

}
