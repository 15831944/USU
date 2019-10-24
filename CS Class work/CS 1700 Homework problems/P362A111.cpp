//P362
//marks
//Mark Salisbury
//P362A111.cpp

#include <fstream.h>
#include <stdlib.h>
#include <iomanip.h>

template < class T > void swap(T &a, T &b);
template < class T > void sort(T *array, const int &elements);
template < class T > void printNumbers(const T *array, int elements, ostream & output);
void shuffleDoubles(double array[], int elements);
int readNumbers(double arrayD[], int arrayI[], istream & input);
double findLargestDouble(double array[], int elements);
double findSmallestDouble(double array[], int elements);
double findAverage(double array[], int elements);

void pause(){
	cin.get();
}

ifstream fin("numbers.dat");
ofstream fout("numbers.out");

void main(){

	double arrayD[200];
	int arrayI[200];
	int elements = readNumbers(arrayD, arrayI, fin);
	//a. find the largest double in the list and output it to the screen.
	cout << "The largest double is: " << findLargestDouble(arrayD, elements) << endl;
	//b. find the smallest double in the list and output it to the screen.
	cout << "The smallest double is: " << findSmallestDouble(arrayD, elements) << endl;
	//c. find the average of the doubles in the list and output the average to the screen..
	cout << "The average of all the doubles is: " << findAverage(arrayD, elements) << endl;
	//d. sort the array of doubles using the function template named sort. This function 
   //   will call a function template named swap.
	sort(arrayD, elements);
	//e. output the sorted array to the screen, 10 numbers per line. Use %10 to accomplish this.
	cout << "The doubles sorted in ascending order are:" << endl;
	printNumbers(arrayD, elements, cout);
	pause();
	//f. shuffle the numbers in the array of doubles.
	shuffleDoubles(arrayD, elements);
	//g. output the shuffled array to the screen, 10 numbers per line.
	cout << "The doubles shuffled are:" << endl;
	printNumbers(arrayD, elements, cout);
	//h. output the shuffled array to the file numbers.out, 10 numbers per line. 
	printNumbers(arrayD, elements, fout);
	//i. sort the array of integers using the template function named sort. This function will 
   //call a template function swap that will swap integers.
	sort(arrayI, elements);
	//j. output the sorted array of integers to the same file, numbers.out, 10 numbers per line.
	printNumbers(arrayI, elements, fout);

	fin.close();
	fout.close();

}

template < class T >
void swap(T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}

template < class T >
void sort(T *array, const int &elements){
	for (int passes = 1; passes < elements; passes++){
		for (int i = 0; i < elements - passes; i++){
			if (array[i] > array[i + 1])
				swap(array[i], array[i + 1]);
		}
	}
}

template < class T > 
void printNumbers(const T *array, int elements, ostream & output){
	for (int i = 0; i < elements; i++){
		if ((i + 1) % 10 == 0)
			output << endl;
		output << setiosflags(ios::left) << setw(8) << array[i];
	}
	output << endl;
}

void shuffleDoubles(double array[], int elements){
	int place;
	for (int i = 0; i < elements; i++){
		place = rand() % elements;
		swap(array[i], array[place]);
	}
}

int readNumbers(double arrayD[], int arrayI[], istream & input){ 
	int i = 0;
	while (input >> arrayD[i] >> arrayI[i])
		i++;
	return i;
}

double findLargestDouble(double array[], int elements){
	double largest = array[0];	
	for (int i = 1; i < elements; i++){
		if (array[i] > largest)
			largest = array[i];
	}
	return largest;
}

double findSmallestDouble(double array[], int elements){
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
}

