// 362
// marks
// Mark Salisbury
// P362A71.cpp
/*
A71. (similiar to 3.41) Write three forms of a Fibonacci function. The first 
will be named fibonacciL, this function will calculate the nth Fibonacci 
number using a for loop. The second will be named fibonacciR and will 
calculate the nth fibonacci number recursively. The third will be named 
fibonacciF and will calculate the nth fibonacci number using the formula in 
lecture and in the notes. Write a driver program that will prompt for n and 
will calculate and output the Fibonacci sequence up to  the nth number using 
each of the three functions. You may have to adjust the beginning index on 
the loop version so your sequences match. Also have a function goldenratio 
that will calculate the golden ratio given two Fibonacci numbers. Output the 
list of golden ratios calculated using the formula versions of the Fibonacci
function for up to the nth Fibonacci number. You will want to use doubles 
throughout these calculations. */

#include <iostream.h>
#include<math.h>

//Iterative Solution:
double FibonacciI(double n){
    double p1 = 0, p2 = 1, t = 0;
    for(int i = 0; i < n; i++)
    {
        p1 = p2;
        p2 = t;
        t = p1 + p2;
    }
    return t;
}
//Recursive Solution:
double FibonacciR(double n){
    if(n==0)
        return 0;
    else if (n<=2)
        return 1;
    else
        return FibonacciR(n-1) + FibonacciR(n-2);
}
//Formula Solution:
double FibonacciF(double n){
    double r1 = (1 + sqrt(5))/2;
    double r2 = (1 - sqrt(5))/2;
    return (pow(r1,n) - pow(r2,n)) / sqrt(5);
}
inline double GoldenRatio(double n1, double n2){return FibonacciF(n1) / FibonacciF(n2);}

void main(void){

	double (*f[3])(double) = {FibonacciI, FibonacciR, FibonacciF};
	const char *endings[4] = {"st","nd","rd","th"};
	const char *choices[3] = {"iterative","recursive","formula"};
	double num;
	int choice;

	cout << "This program calculates the nth Fibonacci number.  It includes " << endl
		  << "an iterative, recursive, and formula method." << endl
		  << "Which Fibonacci number would you like to calculate? ";
	cin >> num;
	cout << "Enter your choice of method: " << endl
		  << "	1. Iterative" << endl
		  << "	2. Recursive" << endl
		  << "	3. Formula" << endl
		  << "	4. Calculate golden ratio up to number n" << endl
		  << "	5. Exit program" << endl;
	cin >> choice;
	while ((choice < 1) || (choice > 5)){
		cout << "Invalid choice entered.  Valid choices are 1-5." << endl
			  << "Please enter a new choice: ";
		cin >> choice;
	}

	if (choice > 0 && choice < 4){
		cout << "The " << num << (num < 4.0 ? endings[int(num) - 1] : endings[3]) 
			  << " fibonacci number using the " << choices[choice - 1] << " method is: " 
			  << (*f[choice - 1])(num) << endl;
	}
	else if (choice == 4){
		for (double i = 2; i <= num; i++){
			cout << "ratio " << i - 1.0 << (i < 4.0 ? endings[int(i - 1.0) - 1] : endings[3]) 
				  << " fibonacci number / " << i << (i < 4.0 ? endings[int(i) - 1] : endings[3]) 
				  << " fibonacci number = " << GoldenRatio(i-1.0, i) << endl;
		}
	}
}

