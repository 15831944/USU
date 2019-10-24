/*CS1700 Assignment 9 Recursion and Nested loops

A91. Ackermann's function is defined for nonnegative n and m as follows:

                     | y + 1					  if x = 0,
A(x, y)    =			| A(x-1, 1)				  if y = 0,
                     | A(x-1, A(x, y-1)     otherwise

This function is of interest because it grows rapidly with respect to the sizes of m and n.

(Caution, Even for modest values of m and n, Ackermann's function requires many recursive calls. 
Do not allow m > 3 or n > 5) Write a C++ function for Ackermann's function along with a driver 
program that prompts for m and n. Set up a table of values for Ackermann's function and include 
it as a comment at the end of your source code before you turn it in. Also, search the Web for 
Ackermann's function and report your findings as a comment at the end of your source code.  
Determine by hand (no computer allowed) the value of Ack(2,1) and report it as a comment at the 
end of your code.*/

#include <iostream.h>
#include <iomanip.h>

int Auck(int x, int y);

void main(void){

	int AuckValues[4][6] = {0};
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 6; j++){
			cout << "Working on Auck(" << i << "," << j << ")..." << endl;
			AuckValues[i][j] = Auck(i, j);
		}
	}

	cout << "  Table of Auckermann function values: A(x,y)" << endl;
	cout << "   y   0   1   2   3   4   5  " << flush << endl;
	cout << "  x " << endl;
	
	for (i = 0; i < 4; i++){
		cout << "  " << i << " ";
		for (int j = 0; j < 6; j++){
			cout << setw(4) << AuckValues[i][j];
		}
		cout << endl;
	}
	
}

int Auck(int x, int y){
//	                  | y + 1					  if x = 0,
//A(x, y)    =			| A(x-1, 1)				  if y = 0,
//                   | A(x-1, A(x, y-1))    otherwise
	if ((x == 2) && (y == 1)){
		cout << "Here's the problem";
	}
	
	if (x == 0)
		return (y + 1);
	else if (y == 0)
		return Auck(x - 1, 1);
	else
		return Auck(x - 1, Auck(x, y - 1));

}

//  Table of Auckermann function values: A(x,y)
//   y   0   1   2   3   4   5
//  x
//  0    1   2   3   4   5   6
//  1    2   3   4   5   6   7
//  2    3   5   7   9  11  13
//  3    5  13  29  61 125 253
//
// Auck(2,1) return Auck(1, Auck(2, 0)); 
//                          return Auck(1, 1); 3
//                          return Auck(0, Auck(1, 0));  3 
//                                         return Auck(0,1); 2
//                          
//           

