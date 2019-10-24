//Mark Salisbury
//marks
//P8265A113.cpp
//CS 1720
/*
A113. (recursive binary search) Do problem 4.34 from your text. Be sure to make this a template 
function so it will be general.  Test it on an array of ints and an array of doubles. Initialize 
the arrays in your program.
*/

// Fig. 4.20: fig04_20.cpp
// Binary search of an array
#include <iomanip.h>
#include <iostream.h>
#include <conio.h>

int binarySearch( int [], int, int, int, int );
void printHeader( int );
void printRow( int [], int, int, int, int );

int main()
{
   const int arraySize = 15;
   int a[ arraySize ], key, result;

   for ( int i = 0; i < arraySize; i++ )
      a[ i ] = 2 * i;   // place some data in array

   cout << "Enter a number between 0 and 28: ";
   cin >> key;

   printHeader( arraySize );
   result = binarySearch( a, key, 0, arraySize - 1, arraySize );

   if ( result != -1 )
      cout << '\n' << key << " found in array element "
           << result << endl;
   else
      cout << '\n' << key << " not found" << endl;
   cout << "Press any key to close the program..." << flush;
	while (!kbhit()) { }
   return 0;
}

// Binary search
int binarySearch( int b[], int searchKey, int low, int high, 
                  int size )
{
	int middle;
 
	while ( low <= high ) {
		middle = ( low + high ) / 2;
		printRow( b, low, middle, high, size );

		if ( searchKey == b[ middle ] )  // match
			return middle;//binarySearch(b, searchKey, low, high, size);
		else if ( searchKey < b[ middle ] )
			middle = binarySearch(b, searchKey, low, middle - 1, size);
			//high = middle - 1;        // search low end of array
		else
			middle = binarySearch(b, searchKey, middle + 1, high, size);
			//low = middle + 1;         // search high end of array
		if (searchKey == b[ middle ]);
			return middle;
	}

   return -1;   // searchKey not found
}

// Print a header for the output
void printHeader( int size )
{
   cout << "\nSubscripts:\n";
   for ( int i = 0; i < size; i++ )
      cout << setw( 3 ) << i << ' ';

   cout << '\n';

   for ( i = 1; i <= 4 * size; i++ )
      cout << '-';

   cout << endl;
}

// Print one row of output showing the current
// part of the array being processed.
void printRow( int b[], int low, int mid, int high, int size )
{
   for ( int i = 0; i < size; i++ )
      if ( i < low || i > high )
         cout << "    ";
      else if ( i == mid )           // mark middle value
         cout << setw( 3 ) << b[ i ] << '*';  
      else
         cout << setw( 3 ) << b[ i ] << ' ';

   cout << endl;
}


