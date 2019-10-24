// 362
// marks
// Mark Salisbury
// P362A62.cpp

#include <iostream.h>
#include <math.h>
#include <iomanip.h> 

double round(double x, int n);

void main(){

	double x;
	int n;
	cout << "Enter a number to be rounded: ";
	cin >> x;
	cout << "How many decimal places would you like to you to? ";
	cin >> n;
	
	cout << setprecision(15)
		  << "The original number: " << x << endl 
		  << " The number rounded: " << round(x,n) << endl;


}

double round(double x, int n){
return floor(x * pow(10, n) + 0.5) / pow(10, n); 
}
