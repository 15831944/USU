/*

A94. Do Problem 2.59, The diamond problem.*/

#include <iostream.h>
#include <iomanip.h>

void main(void){

	int rows, p = 0;
	cout << "Enter an odd number from 1 to 19: ";
	cin >> rows;
	int mid = (rows - 1) / 2;

	for (int r = 0; r < rows; r++){
		if (r > mid)
			p--;
		else
			p++;

		for (int i = 0; i < mid + 1 - p; i++)
			cout << ' ';
		for (i = 0; i < p * 2 - 1; i++)
			cout << '*';
		cout << endl;
	}
}

