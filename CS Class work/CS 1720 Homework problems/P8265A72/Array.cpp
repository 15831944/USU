/*
#include "array.h"

#include <iostream.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

template < class T > Array<T>::Array(int elements) {
	size = ( elements >= 0 ? elements : 0 );
	arrayPtr = new T[elements];
}

template<class T>Array<T>::~Array() {
	delete [] arrayPtr;
}

template < class T > void Array< T >::bubbleSort( Array <class T> & array ){

	T hold;
	bool noswap = true;
	for (int pass = 1; pass < a.size; pass++){
		noswap = true;
		for (int i = 0; i < a.size - pass; i++){
			if (array.arrayPtr[i] > array.arrayPtr[i + 1]){
				noswap = false;
				hold = array.arrayPtr[i];
				array.arrayPtr[i] = array.arrayPtr[i + 1];
				array.arrayPtr[i + 1] = hold;
			}
		}
		if (noswap == true) // sorting is finished
			break;
	}
}

template <class T> void Array< T >::printArray(const Array <class T> & array){
	for (int i = 0; i < array.size; i++)
		cout << arrayPtr[i] << '\t';
}

template <class T> void Array< T >::fillArray( Array <class T> & array){
	for (int i = 0; i < array->size; i++){
		randomNumber(&array.arrayPtr[i], sizeof(T));
	}
}

void randomNumber(void *object, int bytes){ //places a specified number of random bytes
								//at wherever "object" points to.
	unsigned char *filler;
	filler = new unsigned char[bytes];
	for (int i = 0; i < bytes; i++){
		
		filler[i] = rand() % 256;
		if (bytes > 4) // it should be a double
		{
			if (i < 7)
				filler[i] = NULL;
		}
	}
	memcpy(object, filler, bytes); 
	delete filler;
}

template <class T> void Array< T >::testArray( Array <class T> & array, const char *type){
	cout << endl << "Filling array with random values... (an array of " << type << ')' << endl;
	fillArray(array);
	cout << endl << "Array: " << endl;
	printArray(array);
	cout << endl << "Sorting array..." << endl;
	bubbleSort(array);
	cout << endl << "Array: " << endl;
	printArray(array);
}
*/