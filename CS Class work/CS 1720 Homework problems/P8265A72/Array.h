#ifndef ARRAY_H
#define ARRAY_H

template< class T > class Array {
    friend void randomNumber( void *, int );
	public:
        Array( int = 0); // default array size is zero.
        ~Array(); // destructor
        void bubbleSort ( Array <class T> & );
		void printArray ( const Array<class T> & );
		void fillArray ( Array <class T> & );
		void testArray ( Array <class T> &, const char * );
			
    private:
        int size; //number of array elements
		T *arrayPtr;     // pointer to the array
};

#endif