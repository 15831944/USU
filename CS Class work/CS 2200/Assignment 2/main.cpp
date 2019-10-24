#include <stdlib.h>
#include <time.h>
#include <iostream.h>
#include <windows.h>
#include <string.h>
#include <conio.h>


#define MAX_SIZE 1280
int comparisons = 0;

template< class queueType > class Queue;

template <class queueType>
class queueNode
{
	friend class Queue<queueType>;
private:
	queueType Item;
	queueNode<queueType> * Next;

public:
	queueNode() {};
	queueNode( queueType &content);
	queueType getData() ;
	
	
};

template <class queueType>
queueNode<queueType>::queueNode( queueType &content): Item(content), Next(0) {}

template <class queueType>
queueType queueNode<queueType>::getData() 
{
	return Item;
}

template <class queueType>
class Queue 
{
private:
	queueNode<queueType> * headPtr;
	queueNode<queueType> * tailPtr;
	
public:
	//constructors and destructor
	Queue();
	Queue( Queue &Q);
	~Queue();

	//queue operations
	void InitializeQueue();
	bool QueueIsEmpty() ;
	void Enqueue(queueType NewItem);
	bool Dequeue(queueType &qItem);
	void GetQueueFront (queueType &QueueFront) ;
	void print();


};

template <class queueType>
Queue<queueType>::Queue()
{
	InitializeQueue();	
}

template <class queueType>
void Queue<queueType>::InitializeQueue()
{
	headPtr = NULL;
	tailPtr = NULL;
}
 
template <class queueType>
Queue<queueType>::Queue( Queue &Q ) 
{
	if(Q.headPtr == NULL)
		headPtr = NULL;
	else
	{
		headPtr = new queueNode;
		assert(headPtr!= NULL);
		headPtr->Item = Q.headPtr->Item;

		queueNode* NewPtr = headPtr;
		for(queueNode* OrigPtr = Q.headPtr->Next; OrigPtr!= NULL; OrigPtr = OrigPtr->Next)
		{
			NewPtr->Next = new queueNode;
			NewPtr->Item = OrigPtr->Item;
		}
		NewPtr->Next = NULL;
	}
}

template <class queueType>
Queue<queueType>::~Queue()
{
	queueType dummy;
	while(Dequeue(dummy));
		
}
 
template <class queueType>
bool Queue<queueType>::QueueIsEmpty() 
{
	return (headPtr == NULL);
}

template <class queueType>
void Queue<queueType>::Enqueue( queueType NewItem )
{
	queueNode<queueType> *NewPtr = new queueNode<queueType>;

	NewPtr->Item = NewItem;
	NewPtr->Next = NULL;

	if(QueueIsEmpty())
		headPtr = tailPtr = NewPtr;
	else
	{
		tailPtr->Next = NewPtr;
		tailPtr = NewPtr;
	}
}
 
template <class queueType>
bool Queue<queueType>::Dequeue(queueType &qItem)
{
	queueNode<queueType> * FrontPtr = headPtr;
	if(!QueueIsEmpty())
	{
		qItem = headPtr->Item;
		if (headPtr == tailPtr)  
			headPtr = tailPtr = NULL;
		else
			headPtr = headPtr->Next;
		delete FrontPtr;
		return true;
	}
	return false;
}

template <class queueType>
void Queue<queueType>::GetQueueFront(queueType& QueueFront) 
{
	if(!QueueIsEmpty())
	{
		queueNode* tempPtr = headPtr;
		QueueFront = tempPtr->Item;
	}
}
 
template <class queueType>
void Queue<queueType>::print()
{
	if(QueueIsEmpty())
	{
		cout<<"The queue is empty."<<endl;
		return;
	}
	queueNode* CurPtr = headPtr;
	cout << "The queue is: ";
	while( CurPtr != NULL )
	{
		cout << CurPtr->Item << ' ';
		CurPtr = CurPtr->Next;
	}

}


void InsertionSort(int array[], int n){
	
	for (int Unsorted = 1; Unsorted < n; ++Unsorted){
		int nextItem = array[Unsorted];
		
		for (int Sorted = 0; Sorted < Unsorted; Sorted++){
			comparisons++;
			if (nextItem < array[Sorted]){
				comparisons++;
				int newPos = Sorted;
				for (int pos = Unsorted; pos > newPos; pos--){
					comparisons++;
					array[pos] = array[pos-1];

				}
				comparisons++;
				array[pos] = nextItem;
				break;
			}
		}
		comparisons++;
	}
}

void Merge(int data[], int first, int middle, int last){
	static int tempArray[MAX_SIZE];

	int leftPos = first;
	int rightPos = middle + 1;
	int tempPos = 0;

	while (leftPos <= middle && rightPos <= last){
		comparisons++;
		if (data[leftPos] < data[rightPos])
			tempArray[tempPos++] = data[leftPos++];
		else 
			tempArray[tempPos++] = data[rightPos++];
		comparisons++;	
	}
	comparisons++;	

	while (leftPos <= middle){
		comparisons++;	
		tempArray[tempPos++] = data[leftPos++];
	}
	comparisons++;	
	while (rightPos <= last){
		comparisons++;	
		tempArray[tempPos++] = data[rightPos++];
	}
	comparisons++;	

	for (int i = 0; i <= last - first; i++){
		comparisons++;	
		data[first + i] = tempArray[i];
	}
}

void MergeSort(int data[], int first, int last){
	
	if (first < last){
		comparisons++;	
		int middle = (first + last) / 2;
		MergeSort(data, first, middle);
		MergeSort(data, middle + 1, last);
		Merge(data, first, middle, last);
	}
	comparisons++;	
}

int getNum(int Number, int Digit){
	for (int i = 1; i < Digit; i++)
		Number /= 10;
	return Number % 10;

}


/*
void RadixSort(int data[], int n, int d){
	int holderArray[10][MAX_SIZE];
	int ArrayPos[10];
	int whichNumber;
	int DataPos;
	for (int i = 1; i <= d; i++){
		
		for (int j = 0; j < 10; j++)
			ArrayPos[j] = 0;
		for (int aPos = 0; aPos < n; aPos++){
			whichNumber = getNum(data[aPos], i);
			comparisons++;
			holderArray[whichNumber][ArrayPos[whichNumber]++] = data[aPos];
		}
		DataPos = 0;
		for (j = 0; j < 10; j++){
			for (int hPos = 0; hPos < ArrayPos[j]; hPos++){
				comparisons++;
				data[DataPos++] = holderArray[j][hPos];
			}
		}
	}

}
*/

void RadixSort(int data[], int n, int d){
	Queue<int> HQueues[10];
	int whichNumber;
	int DataPos;
	for (int i = 1; i <= d; i++){
		for (int aPos = 0; aPos < n; aPos++){
			whichNumber = getNum(data[aPos], i);
			comparisons++;
			HQueues[whichNumber].Enqueue(data[aPos]);
		}
		DataPos = 0;
		for (int j = 0; j < 10; j++){
			while(1){
				if (HQueues[j].Dequeue(whichNumber))
					data[DataPos++] = whichNumber;
				else break;
			}
		}	
	}

}

void main(){
	
	int datasizes [8] = {10, 20, 40, 80, 160, 320, 640, 1280};
	int data1[MAX_SIZE];
	int data2[MAX_SIZE];
	int data3[MAX_SIZE];
	int number;

	int results[3][8];

	for (int whichTest = 0; whichTest < 8; whichTest++){
	
		for (int i = 0; i < datasizes[whichTest]; i++){ 
			number = rand() % 900 + 100;
			data1[i] = number;
			data2[i] = number;
			data3[i] = number;
		}
		
		comparisons = 0;	
		InsertionSort(data1,datasizes[whichTest]);
		results[0][whichTest] = comparisons;
	
		comparisons = 0;	
		MergeSort(data2, 0, datasizes[whichTest] - 1);
		results[1][whichTest] = comparisons;
	
		comparisons = 0;
		RadixSort(data3, datasizes[whichTest], 3);
		results[2][whichTest] = comparisons;
			
	}

	char line[80];
	cout << "This program generates random data and compares 3 types of sorting algorithms." << endl << endl;
	cout << "The figures represent number of comparisons for insertion and merge sorts, and " << endl << endl
		 <<	"the number of queue insertions for the radix sort." << endl << endl;
	cout << "         		Number of Data Items " << endl << endl;
	cout << "Sort Name          10      20      40      80     160     320     640    1280" << endl << endl;
	
	for (int i = 0; i < 3; i++){
		if (i == 0) strcpy(line,"Insertion    ");
		if (i == 1) strcpy(line,"Merge        ");
		if (i == 2) strcpy(line,"Radix        ");
		for (int j = 0; j < 8; j++)
			wsprintf(line,"%s%8i",line,results[i][j]);
		cout << line << endl << endl;
	}
	cout << "Press any key to close program" << flush;
	while(!kbhit());
	
	
}