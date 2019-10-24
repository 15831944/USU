// 362
// marks
// Mark Salisbury
// P362A74.cpp
//A74. (3.44) Do problem 3.44 from your text.
// Fig. 3.14: fig03_14.cpp
// Recursive factorial function
#include <iostream.h>
#include <iomanip.h>
static int indlevel = 0;
static int LineCount = 0;
unsigned long factorial( unsigned long );
void PrintTabs(int);

void Pause(){
	cin.get();
	LineCount = 0;
}

int main()
{
   unsigned long fact;
	for ( int i = 0; i <= 10; i++ ){
      fact = factorial(i);
		PrintTabs(indlevel);
		cout << setw( 2 ) << i << "! = " << fact << endl << endl;
		LineCount += 2;
		indlevel = 0;
	}

   return 0;
}

// print tabs function
void PrintTabs(int n){
	for (int i = 0; i < n; i++)
		cout << "   ";
}
// Recursive definition of function factorial
unsigned long factorial( unsigned long number )
{
 	if (LineCount >= 24)
		Pause();
	
	PrintTabs(indlevel);
	LineCount+=2;
	cout << "number = " << number << endl;
	
	if ( number <= 1 ){  // base case
      PrintTabs(indlevel);
		cout << "return 1" << endl;
		indlevel++;
		return 1;
	}
   else{                // recursive case
      PrintTabs(indlevel);
		cout << "return " << number << " * factorial( " << number << " - 1 );" << endl;
		indlevel++;
		return number * factorial( number - 1 );
	}
}