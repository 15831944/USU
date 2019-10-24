#include <iostream.h>
#include <stdlib.h>
#include <time.h>

void swap(int &a, int &b)
{
	int temp = a;
    a = b;
	b = temp;
}

void print_numbers(int numbers[], int size)
{
	for ( int i = 0; i < size; i++)
	{
		cout << "numbers[" << i + 1 << "] = " << numbers[i] << endl;
	}
}


void main()
{
	int number_count = 10000;

    int * numbers = new int[number_count];

	srand(time(0));

	for (int i = 0; i < number_count; i++)
		numbers[i] = rand() % (number_count * 2) + 1;

	cout << "Before sort:" << endl;
	print_numbers(numbers, number_count);

	for ( i = 0; i < number_count - 1; i++)
	{
		int smallest_index = i;
		for ( int j = i + 1; j < number_count; j++)
		{
           if (numbers[j] < numbers[smallest_index])
		   {
				smallest_index = j;
		   }
		}
		if (smallest_index != i)
			swap (numbers[smallest_index], numbers[i]);
	}
	cout << "After sort:" << endl;
	print_numbers(numbers, number_count);

	delete [] numbers;
}