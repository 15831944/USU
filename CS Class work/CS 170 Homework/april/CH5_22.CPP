//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  4-25-97
//  Chapter 5, Problem 5.22
//  Program description

#include <iostream.h>
#include <math.h>

int main() {
// lengths of the sides
float Side1;
float Side2;
float Side3;
// half the perimeter
float S;
// area of the triangle
float Area;

cout << "This program computes the area of a triangle" << endl
	  << "based on the lengths of the three sides." << endl;
cout << endl;
// input the lenghts of the three sides
cout << "Enter the length of side 1: " << flush;
cin >> Side1;
cout << "Enter the length of side 2: " << flush;
cin >> Side2;
cout << "Enter the length of side 3: " << flush;
cin >> Side3;
// store half the length of the perimeter in S
S = (Side1 + Side2 + Side3) / 2;

cout << endl;
// checks to see if the triangle cannot exist
if (Side1 >= S || Side2 >= S || Side3 >= S) {
	cout << "This triangle sucks.  It does not exist.    " << endl
		  << "Try again.  Hint (One side cannot be greater" << endl
		  << "than the sum of the other two sides).  9th  " << endl
		  << "grade math.  Mr. Ward's class.              " << endl;
	return (1);
}

// output the value of the area of the triangle
Area = sqrt(S*(S-Side1)*(S-Side2)*(S-Side3));
cout << "The area of your beautiful triangle is: " << Area << endl;

}



