#include <iostream.h>
#include <iomanip.h>

void bubble(int [], const int, int (*)(int, int));
int ascending(int,int);
int descending(int,int);

void main()
{
	const int arraySize = 10;
	int order,
		counter,
		a[arraySize] = {2,6,4,8,10,12,89,68,45,37};

	cout << "Enter 1 to sort in ascending order," << endl;
	cout << "Enter 2 to sort in descending order: ";
	cin >> order;
	cout << "Data items in original order:" << endl;

	for (counter = 0; counter < arraySize; counter++)
		cout << setw(4) << a[counter];

	if (order == 1) {
		bubble(a, arraySize, ascending);
		cout << endl << "Data items in ascending order" << endl;
	}
	else {
		bubble(a, arraySize, descending);
		cout << endl << "Data items in descending order" << endl;
	}

	for (counter = 0; counter < arraySize; counter++)
		cout << setw(4) << a[counter];

	cout << endl;
}

void bubble(int work[], const int size, int (*compare)(int,int))
{
	void swap(int *, int *);
	for (int pass = 1; pass < size; pass++)
		for (int count = 0; count < size - 1; count++)
			if ((*compare)(work[count], work[count + 1]))
				swap(&work[count], &work[count + 1]);
}

void swap(int *element1Ptr, int *element2Ptr)
{
	int temp;
	temp = *element1Ptr;
	*element1Ptr = *element2Ptr;
	*element2Ptr = temp;
}

int ascending(int a, int b)
{ 
	return b < a; // swap if b is less than a
}

int descending(int a, int b)
{
	return b > a; // swamp if b is greater than a
}

