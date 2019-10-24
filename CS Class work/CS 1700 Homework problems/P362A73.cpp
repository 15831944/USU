// 362
// marks
// Mark Salisbury
// P362A73.cpp

//A73. (3.45) Do problem 3.45 from your text. Have your driver program prompt for two 
//       integers and output the greatest common divisor. Turn in your driver program.
#include <iostream.h>

int gcd(int , int );
void main(){
	int x, y;
	cout << "Enter two numbers: ";
	cin >> x >> y;
	cout << "The gcd(" << x << "," << y << ") is: " << gcd(x,y) << endl;
}

int gcd(int x, int y){
	
	if (y == 0)
		return x;
	else
		return gcd(y, x % y);
}