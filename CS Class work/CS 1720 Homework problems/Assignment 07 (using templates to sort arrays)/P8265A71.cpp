//Mark Salisbury
//CS 1720
//P8265A71.cpp
//Assignment 7.1
/*
CS1720 Assignment 7 Templates
A71.  Write a function template bubblesort or selectionsort. Write a driver program that outputs 
the unsorted arrays, sorts the arrays, and outputs the sorted arrays for an array of ints, an 
array of doubles, an array of complex numbers using the class Complex and an array of Rational 
numbers using the class Rational. Initialize all arrays with 10 numbers. Output both the unsorted 
arrays and the sorted arrays to the screen with as many numbers perline as will conveniently fit 
on a line. Use a project with separate files for Rational.h, Complex.h, Rational.cpp, Complex.cpp,
sort.h (which contains the template function). Use a template function to carry out the testing of
each type.  After you have created the project and completely debugged your code in the project, 
submit the PxxxxA71.dsp file to the homework site. After you have submitted it, then combine your
.cpp files into one file, PxxxxA71.cpp, (be sure to comment out the proper #include's). Compile 
your program again to make sure all is well and then submit just the complete .cpp file.  I want 
to know that you worked on this as a project (the .dsp file from the project) but I also want to 
have an reasonable way for us to check your work and compile and run your program (the .cpp file).
You must do this assignment with a project or you will receive a 0.
*/
#include <iostream.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <math.h>

class complex {
	friend ostream & operator<<(ostream &, const complex &);
	friend istream & operator>>(istream &, complex &);
public:
	complex(double, double);
	complex();
	bool operator>(const complex &) const;
	double magnitude() const;
private:
	double real;
	double imag;
};

class Rational
{
	friend ostream & operator<<(ostream & output, const Rational &); 
public:
	  Rational(int num = 0, int denom = 1); //default constructor
	  double Value(void) const;
	  bool operator>(const Rational &) const;
  private:
	  int	numerator,
			denominator;

};

ostream & operator<<(ostream & output, const complex &right){
	output << right.real;
	if (right.imag != 0.0)
		output << (right.imag > 0.0 ? " + " : " - ") 
		       << (right.imag > 0.0 ? right.imag : -1.0 * right.imag) << "i";
	return output;
}

complex::complex(double a, double b){
	real = a;
	imag = b;
}

complex::complex(){
	real = 0.0;
	imag = 0.0;
}

double complex::magnitude() const{
	return sqrt(real * real + imag * imag);
}

bool complex::operator>(const complex &right) const{
	return (this->magnitude() > right.magnitude());
}

ostream & operator<<(ostream & output, const Rational & right){
	if((right.numerator < 0) && (right.denominator < 0))
		cout << abs(right.numerator) << '/' << abs(right.denominator);
	else if((right.numerator < 0) || (right.denominator < 0))
		cout << '-' << abs(right.numerator) << '/' << abs(right.denominator);
	else
		cout <<  right.numerator << '/' << right.denominator;
	return output;
}

Rational::Rational(int num, int denom)
{
  numerator = num;
  denominator = denom;
}

double Rational::Value(void) const
{
  return double(numerator)/double(denominator);
}

bool Rational::operator>(const Rational & right) const {
	return (this->Value() > right.Value());
}

template <class T>
void bubbleSort(T *array, const int aSize){
	T hold;
	bool noswap = true;
	for (int pass = 1; pass < aSize; pass++){
		noswap = true;
		for (int i = 0; i < aSize - pass; i++){
			if (array[i] > array[i + 1]){
				noswap = false;
				hold = array[i];
				array[i] = array [i + 1];
				array[i + 1] = hold;
			}
		}
		if (noswap == true) // sorting is finished
			break;
	}
}

template <class T>
void printArray(const T *array, const int aSize){
	for (int i = 0; i < aSize; i++)
		cout << array[i] << '\t';
}

template <class T>
void fillArray(T *array, const int aSize){
	
	for (int i = 0; i < aSize; i++){
		randomNumber(&array[i], sizeof(T));
	}
}

void randomNumber(void *object, int bytes){ //places a specified number of random bytes
											//at wherever "object" points to.
	unsigned char *filler;
	filler = new unsigned char[bytes];
	for (int i = 0; i < bytes; i++){
		filler[i] = rand() % 256;
	}
	memcpy(object, filler, bytes); 
	delete filler;
}

void pause(){
	cout << endl << "Press any key to continue" << flush;
	while (!kbhit()) { }
	cin.ignore();
	cout << endl;
}

template <class T>
void testArray(T *array, const int aSize, const char *type){
	cout << endl << "Filling array with random values... (an array of " << type << ')' << endl;
	fillArray(array, aSize);
	cout << endl << "Array: " << endl;
	printArray(array, aSize);
	cout << endl << "Sorting array..." << endl;
	bubbleSort(array, aSize);
	cout << endl << "Array: " << endl;
	printArray(array, aSize);
}

void main(){
	//array of ints, an array of doubles, an array of complex numbers using the class 
	//Complex and an array of Rational numbers using the class Rational.
	//make a template to fill an array w/ random numbers;
	//make overloaded functions to return a random number of each type;

	srand(time(0));
	
	int array1[10];
	testArray(array1, 10, "integers");
	double array2[10];
	testArray(array2, 10, "doubles");

	pause();

	complex array3[10];
	testArray(array3, 10, "complex numbers");
	Rational array4[10];
	testArray(array4, 10, "rational numbers");

}

