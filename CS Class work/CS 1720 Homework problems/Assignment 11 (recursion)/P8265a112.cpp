//Mark Salisbury
//marks
//P8265A112.cpp
//CS 1720
/*
A112. (Sieve of Eratosthenes) Do problem 4.29 of your text.
*/

#include <iostream.h>
#include <conio.h>

#define MAX_ELEMENTS 1000

void main(){
	bool array[MAX_ELEMENTS];
	int t;
	for (int i = 0; i < MAX_ELEMENTS; i++)
		array[i] = 1;
	for (int s = 2; s < MAX_ELEMENTS; s++){
		t = s;
		while (t + s < MAX_ELEMENTS){
			t += s;
			array[t] = 0;
		}
	}
	for (i = 0; i < MAX_ELEMENTS; i++){
		if (array[i] == 1)
			cout << i << '\t';
	}
	cout << "Press any key to close the program..." << flush;
	while (!kbhit()) { }
}
