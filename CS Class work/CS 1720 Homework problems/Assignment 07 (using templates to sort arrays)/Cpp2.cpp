#include <iostream.h>

void main(){

	cout << "enter the number of elements for the next array: ";
	int x;
	cin >> x;

	double *dPtr;

	
	dPtr = new double[x];

	cout << "dPtr = " << dPtr << endl;
}