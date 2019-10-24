//Mark Salisbury
//CS 1720
//P8265A72.cpp
//Assignment 7.2
/*
A72. Write a program that uses the function template bubblesort or selectionsort with a class 
template Array. The template can instantiate an Array of any element type including elements of 
class Complex and class Rational. Initialize your arrays with 10 numbers. Write a driver program 
that demonstrates the usage for ints, doubles, and for Complex and Rational. Use a project with 
separate files for Rational.h, Complex.h, Rational.cpp, Complex.cpp, sort.h, and Array.h.  Use a 
template function to carry out the testing of each type. After you have created the project and 
completely debugged your code in the project, submit the PxxxxA72.dsp file to the homework site. 
After you have submitted it, then combine your .cpp files into one file, PxxxxA72.cpp, (be sure 
to comment out the proper #include's). Compile your program again to make sure all is well and 
then submit just the complete .cpp file.  I want to know that you worked on this as a project 
(the .dsp file from the project) but I also want to have an reasonable way for us to check your 
work and compile and run your program (the .cpp file). You must do this assignment with a project 
or you will receive a 0.
*/

#include <iostream.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

template< class T > class Array 
{
    friend void randomNumber( void *, int );
	friend ostream & operator<<(ostream &, Array<T> & );
	public:
        Array( int = 10 ); // default array size is 10.
        ~Array(); // destructor
        void bubbleSort ();
		void fillArray ();
	private:
        int size; //number of array elements
		T *arrayPtr;     // pointer to the array

};

class complex {
	friend ostream & operator<<(ostream &, const complex &);
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


template < class T > Array< T >::Array(int elements) {
	size = ( elements >= 0 ? elements : 0 );
	arrayPtr = new T[elements];
}

template < class T > Array< T >::~Array() {
	delete [] arrayPtr;
}

template < class T > void Array< T >::bubbleSort(){
	T hold;
	bool noswap = true;
	for (int pass = 1; pass < size; pass++){
		noswap = true;
		for (int i = 0; i < size - pass; i++){
			if (arrayPtr[i] > arrayPtr[i + 1]){
				noswap = false;
				hold = arrayPtr[i];
				arrayPtr[i] = arrayPtr[i + 1];
				arrayPtr[i + 1] = hold;
			}
		}
		if (noswap == true) // sorting is finished
			break;
	}
}

template < class T > ostream & operator<<(ostream & output, Array<T> & array){
	for (int i = 0; i < array.size; i++)
		cout << array.arrayPtr[i] << '\t';
	return output;
}

template <class T> void Array< T >::fillArray(){
	for (int i = 0; i < size; i++){
		randomNumber(&arrayPtr[i], sizeof(T));
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

bool complex::operator>(const complex &right) const{
	return (this->magnitude() > right.magnitude());
}

double complex::magnitude() const{
	return sqrt(real * real + imag * imag);
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
void testArray ( Array<T> & array, const char *type ){
	cout << endl << "Filling array with random values... (an array of " << type << ')' << endl;
	array.fillArray();
	cout << endl << "Array: " << array << endl;
	cout << endl << "Sorting array..." << endl;
	array.bubbleSort();
	cout << endl << "Array: " << array << endl;
}

void pause(){
	cout << endl << "Press any key to continue" << flush;
	while (!kbhit()) { }
	cin.ignore();
	cout << endl;
}


void main(void)
{
    Array<int> iarray1(10);
	testArray( iarray1, "integers");
	pause();       
    Array<double> darray1(10);
	testArray( darray1, "doubles");
	pause();
	Array<complex> carray1(10);
	testArray( carray1, "complex numbers");
	pause();
	Array<Rational> rarray1(10);
	testArray( rarray1, "rational numbers");
		
}

