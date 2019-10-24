/*A111.  Download the file numbers.dat. In the file numbers.dat, the numbers are
stored in two columns, the first column is a column of doubles and the second
column is a column of integers. Write a complete program that will use a function
to read the doubles in the first column into an array of doubles and the integers
in the second column into an array of integers. Use the eof construct to terminate
the reading of the file. While reading the numbers from the file, determine how many
doubles there are in the file. This will also be the number of integers in the file.
There are no more than 200 numbers in the file. Your program will then use functions
to accomplish the following IN THIS ORDER! 

a. find the largest double in the list and output it to the screen.
b. find the smallest double in the list and output it to the screen.
c. find the average of the doubles in the list and output the average to the screen..
d. sort the array of doubles using the function template named sort. This function 
   will call a function template named swap.
e. output the sorted array to the screen, 10 numbers per line. Use %10 to accomplish this.
f. shuffle the numbers in the array of doubles.
g. output the shuffled array to the screen, 10 numbers per line.
h. output the shuffled array to the file numbers.out, 10 numbers per line. 
i. sort the array of integers using the template function named sort. This function will 
   call a template function swap that will swap integers.
j. output the sorted array of integers to the same file, numbers.out, 10 numbers per line.

The sort function, the swap function will templates functions. 

Each of these items must be done in a separate function. There will be at least 10 functions,
one function to input the data from the file into the arrays, one for parts a, b, c, two for d,
one for e, f, and h,  one for j. Notice that e. and g. use the same function as do h and j.

Correct parameters must be passed. Arrays must be passed as parameters.
Be sure to write and test each function independently from the other function.
As usual, just submit the source code, do not submit the output file!
Remember that template functions must be completely defined before they are used. */

#include <fstream.h>
#include <stdlib.h>

template <class T>
void swap(T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}

template < class T >
void sort(const T *array, const int &elements){
	
	for (int passes = 1; passes < elements; passes++){
		for (int i = 0; i < elements - passes; i++){
			if (array[i] > array[i + 1])
				swap(array[i], array[i + 1]);
		}
	}
}

/*template < class T > 
void printNumbers(const T *array, int elements, ostream & output){
	
	for (int i = 0; i < elements; i++){
		if ((i + 1) % 10 == 0)
			output << endl;
		output << array[i];
	}
}

void shuffleDoubles(double array[], int elements){
	int place;
	for (int i = 0; i < elements; i++){
		place = rand() % elements;
		swap(array[i], array[place]);
	}
}*/

//int readNumbers(double arrayD[], int arrayI[], istream & input);
//double findSmallestDouble(double array[], int elements);
//double findAverage(double array[], int elements);

ifstream fin("numbers.dat");
//ofstream fout("numbers.out");

void main(){

	double arrayD[200];
	int arrayI[200];
	swap (arrayD[0],arrayD[1]);
	//int elements = readNumbers(arrayD, arrayI, fin);
	//cout << "The smallest double is: " << findSmallestDouble(arrayD, elements) << endl;
	//cout << "The average of all the doubles is: " << findAverage(arrayD, elements) << endl;
	//sort(arrayD, elements);
	//printNumbers(arrayD, elements, cout);
	//cout << endl;
	//shuffleDoubles(arrayD, elements);
	//printNumbers(arrayD, elements, fout);
	//cout << endl;
	//sort(arrayI, elements);
	//printNumbers(arrayI, elements, fout);
	//cout << endl;

	//fin.close();
	//fout.close();

}
/*
int readNumbers(double arrayD[], int arrayI[], ifstream & input){ 
	
	int i = 0;
	while (input >> arrayD[i] >> arrayI[i])
		i++;
	return i;
}

/*double findSmallestDouble(double array[], int elements){
	double smallest = array[0];	
	for (int i = 1; i < elements; i++){
		if (array[i] < smallest)
			smallest = array[i];
	}
	return smallest;
}

double findAverage(double array[], int elements){

	double sum = 0;
	for (int i = 0; i < elements; i++ )
		sum += array[i];
	
	return sum / elements;

}*/

