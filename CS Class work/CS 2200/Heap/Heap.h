#ifndef MY_HEAP_H
#define MY_HEAP_H

#include <stddef.h>

typedef int BOOL;
#define TRUE	1
#define FALSE	0

template <class HeapType>
class Heap {
public:
	Heap(int nItems);
	BOOL HeapInsert(HeapType h);
	BOOL PopNextItem(HeapType &largestValue);
private:
	void TrickleDown(int Pos);
	int MaxSize;
	int Size;
	HeapType *HeapArray;
};

template <class QType>
class PriorityQueue {
public:
	PriorityQueue(int maxQSize);
	BOOL Insert(QType q);
	BOOL Pop(QType &q);
private:
	Heap<QType> h;
};

template <class T>
void swap(T &a, T &b){
	T temp = a;
	a = b;
	b = temp;
}


template <class HeapType>
Heap<HeapType>::Heap(int nItems){
	MaxSize = nItems;
	HeapArray = new HeapType[nItems];
	Size = 0;
}

template <class HeapType>
BOOL Heap<HeapType>::PopNextItem(HeapType &largestValue){
	if (Size > 0){
		Size--;
		largestValue = HeapArray[0];
		if (Size > 0){
			HeapArray[0] = HeapArray[Size];
		}
		TrickleDown(0);
		return TRUE;
	}
	else
		return FALSE;

}

template <class HeapType>
void Heap<HeapType>::TrickleDown(int Pos){
	int Child = Pos * 2 + 1;
	if (Child <= Size){ // then it is not a leaf
		if (Child + 1 <= Size){ // then it has a right child also
			if (HeapArray[Child + 1] > HeapArray[Child])
				Child++;
		}
		if (HeapArray[Pos] < HeapArray[Child]){
			swap(HeapArray[Pos], HeapArray[Child]);
			TrickleDown(Child);
		}
	}
}

template <class HeapType>
BOOL Heap<HeapType>::HeapInsert(HeapType h){
	if (Size < MaxSize) {
		
		HeapArray[Size] = h;
		int Place = Size;
		int Parent = (Place - 1) / 2;
		while (Parent >= 0 && (HeapArray[Place] > HeapArray[Parent])){
			swap(HeapArray[Place], HeapArray[Parent]);
			Place = Parent;
			Parent = (Place - 1) / 2;
		}
		Size++;
		return TRUE;
	}
	return FALSE;
}


template <class QType>
PriorityQueue<QType>::PriorityQueue(int maxSize)
: h(maxSize)
{
}

template <class QType>
BOOL PriorityQueue<QType>::Insert(QType q){
	return h.HeapInsert(q);
}

template <class QType>
BOOL PriorityQueue<QType>::Pop(QType &q){
	return h.PopNextItem(q);
}




#define MAX_SIZE		100
//#define TRUE			1
//#define FALSE			0
//typedef int BOOL;

template <class dataType, class KeyType>
class TableEntry {
public:
	TableEntry();
	TableEntry(dataType d, KeyType k);
	BOOL operator>(const TableEntry &right) const;
	BOOL operator<(const TableEntry &right) const;
	BOOL operator==(const TableEntry &right) const;
	KeyType GetKeyValue();
	dataType GetData();
private:
	dataType dataItem;
	KeyType key;
};



template <class dataType, class KeyType>
class Table {
public:
	Table();
	BOOL Insert(TableEntry<dataType,KeyType> T);
	BOOL Remove(TableEntry<dataType,KeyType> T);
	BOOL Remove(KeyType k);
	BOOL IsTableEmpty();
	int  GetTableLength();
	void Traverse();
private:
	TableEntry<dataType, KeyType> TArray[MAX_SIZE];
	int nItems;
};







// Implementation for class TableEntry
template <class dataType, class KeyType>
TableEntry<dataType, KeyType>::TableEntry() : dataItem(0), key(0) { }

template <class dataType, class KeyType>
TableEntry<dataType, KeyType>::TableEntry(dataType d, KeyType k){
	dataItem = d;
	key = k;
}

template <class dataType, class KeyType>
KeyType TableEntry<dataType, KeyType>::GetKeyValue(){
	return key;
}

template <class dataType, class KeyType>
dataType TableEntry<dataType, KeyType>::GetData(){
	return dataItem;
}

template <class dataType, class KeyType>
BOOL TableEntry<dataType, KeyType>::operator>(const TableEntry &right) const{ return BOOL(key > right.key); }

template <class dataType, class KeyType>
BOOL TableEntry<dataType, KeyType>::operator<(const TableEntry &right) const{ return BOOL(key < right.key); }

template <class dataType, class KeyType>
BOOL TableEntry<dataType, KeyType>::operator==(const TableEntry &right) const{ return BOOL(key == right.key); }

// Implemenation for class Table 

template <class dataType, class KeyType>
Table<dataType, KeyType>::Table(){
	TableEntry<dataType, KeyType> TArray[100];
	nItems = 0;
}

template <class dataType, class KeyType>
BOOL Table<dataType, KeyType>::Insert(TableEntry<dataType,KeyType> T){
	if (nItems < MAX_SIZE){
		for (int i = nItems; i > 0; i--){
			if (i == 0 || T > TArray[i - 1]){
				TArray[i] = T;
				break;
			}
			else
				TArray[i] = TArray[i - 1];
		}
		nItems++;
		return TRUE;
	}
	return FALSE;
}

template <class dataType, class KeyType>
BOOL Table<dataType, KeyType>::Remove(TableEntry<dataType,KeyType> T){
	for (int i = 0; i < nItems - 1; i++){
		if (TArray[i] == d){
			nItems--;
			for (; i < nItems - 1; i++)	
				TArray[i] = TArray[i + 1];
			return TRUE;
		}
	}
	return FALSE;
}

template <class dataType, class KeyType>
BOOL Table<dataType, KeyType>::Remove(KeyType k){
	for (int i = 0; i < nItems - 1; i++){
		if (TArray[i].GetKeyValue() == k){
			nItems--;
			for (; i < nItems - 1; i++)	
				TArray[i] = TArray[i + 1];
			return TRUE;
		}
	}
	return FALSE;
}

template <class dataType, class KeyType>
BOOL Table<dataType, KeyType>::IsTableEmpty(){
	return (nItems == 0);
}

template <class dataType, class KeyType>
BOOL Table<dataType, KeyType>::GetTableLength(){
	return (nItems);
}

template <class dataType, class KeyType>
void Table<dataType, KeyType>::Traverse(){
	for (int i = 0; i < nItems; i++){
		cout << TArray[i].GetData() << '\t';
	}
}
  
#endif