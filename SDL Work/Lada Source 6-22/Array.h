// This is Version 1.0 PLEASE DOCUMENT CHANGES
#ifndef MY_ARRAY_CLASS
#define MY_ARRAY_CLASS

#include <afxwin.h>
#include <string.h>


template <class ArrayType> 
class Array {
	public:
		Array(int size);
		Array();
		~Array();
		ArrayType & operator[](int Subscript); //used to access an element
		ArrayType & operator[](int Subscript) const;
		Array &operator=(const Array &rArray);
		void operator()(int newSize); //used to re-dim the array
		void Insert(const ArrayType &iObject, int Subscript = -1);
		void Remove(int Subscript, int nItems = 1 );
		//ArrayType &operator=(const ArrayType &rObject);//used to assign locations to pointers
		int length;
	private:
		ArrayType **pPtrs;
};

template <class ArrayType>
Array<ArrayType>::Array(int size){
	if (size < 1){
		length = 0;
		pPtrs = 0;
	}
	else {
		pPtrs = new ArrayType*[size];
		for (int i = 0; i < size; i++)
			pPtrs[i] = 0;
		length = size;
	}
}

template <class ArrayType>
Array<ArrayType>::Array(){
	length = 0;
	pPtrs = 0;
}

template <class ArrayType>
Array<ArrayType>::~Array(){
static int whichD = 0;
	whichD++;
	TRACE( "\nwhichD = %d, length = %d, pPtrs = %d", whichD, length, pPtrs);
	for (int i = 0; i < length; i++){
		if (pPtrs[i] != NULL)
			delete pPtrs[i];
	}
	delete [] pPtrs;	
}

template <class ArrayType>
ArrayType &Array<ArrayType>::operator [](int Subscript){
	if (Subscript >= length)
		operator()(Subscript+1);
	// if you try and access an element beyond the length of
	// the array, the array automatically re-dimensions itself.
	if (pPtrs[Subscript] == NULL)
		pPtrs[Subscript] = new ArrayType;
	return *pPtrs[Subscript];
}

template <class ArrayType>
ArrayType &Array<ArrayType>::operator [](int Subscript) const{
	//if (Subscript >= length)
	//	operator()(Subscript+1);
	// if you try and access an element beyond the length of
	// the array, the array automatically re-dimensions itself.
	if (pPtrs[Subscript] == NULL)
		pPtrs[Subscript] = new ArrayType;
	return *pPtrs[Subscript];
}

template <class ArrayType>
void Array<ArrayType>::operator ()(int newSize){
	ArrayType **tempPtr = pPtrs;
	
	if (newSize > 0)
		pPtrs = new ArrayType*[newSize];
	else
		pPtrs = 0;

	if (length > 0 && newSize > 0){
		size_t tempPtrSize = sizeof(tempPtr) * length;
		size_t pPtrsSize = sizeof(pPtrs) * newSize;
		size_t bytesToCopy = tempPtrSize < pPtrsSize ? tempPtrSize : pPtrsSize;
		memcpy(pPtrs,tempPtr,bytesToCopy);
	}
	for (int i = length; i < newSize; i++)
		pPtrs[i] = 0;
	for (i = newSize; i < length; i++)
		delete tempPtr[i];
	length = newSize;

	delete [] tempPtr;
}

template <class ArrayType>
Array<ArrayType> &Array<ArrayType>::operator=(const Array<ArrayType> &rArray){
	// this is a shallow assignment operator
	delete pPtrs;
	pPtrs = rArray.pPtrs;
	length = rArray.length;
	return *this;
}

template <class ArrayType>
void Array<ArrayType>::Insert(const ArrayType &iObject, int Subscript /*= -1*/){
	(*this)(length + 1);
	if (Subscript == -1) // then insert at the end
		Subscript = length - 1;
	for (int i = length - 1; i > Subscript; i--)
		pPtrs[i] = pPtrs[i-1];
	pPtrs[i] = new ArrayType(iObject); // copy constructor
}

template <class ArrayType>
void Array<ArrayType>::Remove(int Subscript, int nItems /*=1*/){
	if (Subscript + nItems > length)
		nItems = length;
	for (int i = Subscript; i < Subscript + nItems; i++)
		delete pPtrs[i];
	for (i = Subscript; i < length - nItems; i++)
		pPtrs[i] = pPtrs[i+nItems];
	for (; i < length; i++)
		pPtrs[i] = 0;
	(*this)(length - nItems);
}


#endif
