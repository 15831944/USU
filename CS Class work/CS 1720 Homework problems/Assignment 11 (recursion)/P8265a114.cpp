//Mark Salisbury
//marks
//P8265A114.cpp
//CS 1720
/*
A114. (recursive selection sort) Do problem 4.31 from your text. Be sure to make this a template 
function so it will be general. Test it on an array of ints and an array of doubles. Initialize 
the arrays in your program.
*/

#include <iostream.h>
#include <conio.h>
#include <string.h>

template <class T>
void swap(T &x, T &y){
	T temp = x;
	x = y;
	y = temp;
}

template <class T>
void sortArray(T array[], int first, int last){
	
	int indexSmallest = first;
	for (int i = first; i < last; i++){
		if (array[i] < array[indexSmallest])
			indexSmallest = i;
	}
	swap (array[first], array[indexSmallest]);

	if (first == last - 2)
		return;
	else
		sortArray(array, first + 1, last);
}

template <class T>
void printArray(T array[], int size){
	for (int i = 0; i < size; i++){
		cout << array[i] << '\t'; 
	}
	cout << endl;
}

void main(){
	double darray[] = {1.2, 2.3, 8.9, 0.4, -0.2, 5.6, 7.1, -3.5, 2.5};
	cout << "Before sorting, an array of doubles is:" << endl;
	printArray(darray, 9);
	sortArray(darray, 0, 9);
	cout << "After sorting, the array of doubles is:" << endl;
	printArray(darray, 9);
	cout << endl;

	int iarray[] = {12, 26, 86, 40, -13, 53, 78, -35, 25};
	cout << "Before sorting, an array of integers is:" << endl;
	printArray(iarray, 9);
	sortArray(iarray, 0, 9);
	cout << "After sorting, the array of integers is:" << endl;
	printArray(iarray, 9);
	cout << endl;

	char carray[] = {'a', 't', 'u', '7', 'f', 'l', 'z', 'e', '2'};
	cout << "Before sorting, an array of char is:" << endl;
	printArray(carray, 9);
	sortArray(carray, 0, 9);
	cout << "After sorting, the array of char is:" << endl;
	printArray(carray, 9);
	cout << endl;

	cout << "Press any key to close the program..." << flush;
	while (!kbhit()) { }
}