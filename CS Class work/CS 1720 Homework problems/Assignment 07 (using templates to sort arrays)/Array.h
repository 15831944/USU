
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream.h>

template< class T > class Array 
{
    friend void randomNumber( void *, int );
	friend ostream & operator<<(ostream &, Array<T> & );
	public:
        Array( int = 10 ); // default array size is 10.
        ~Array(); // destructor
        void bubbleSort ();
		//void printArray ();
		void fillArray ();
		void ANewFunction ();
		
    private:
        int size; //number of array elements
		T *arrayPtr;     // pointer to the array

};

#endif