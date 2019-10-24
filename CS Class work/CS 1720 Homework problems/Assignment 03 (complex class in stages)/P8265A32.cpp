//P8265A32.CPP
//Mark Salisbury
//Assignment 3.2
//CS 1720 
/*
A32. Write a complete program including specification, driver (client) program and implementation using the class 
Complex with public attributes and functions that are falset members of the class. Be sure to include a function 
print that will print a complex number in the usual form. Also include a function input that will allow the input 
of a complex number in the usual form.
*/

#include <iostream.h>
#include <math.h>
#include <ctype.h>

class complex {
public:
	complex();
	complex(double, double);
	double real;
	double imag;
};

void print(const complex &);
void input(complex &);
complex add(const complex &, const complex &);
complex subtract(const complex &, const complex &);
complex multiply(const complex &, const complex &);
complex divide(const complex &, const complex &);
complex magnitude(const complex &);

void main(){
	complex num1;
	complex num2;
	char answer;
	
	do{
		cout << "Enter a complex number: ";
		input(num1);
		cout << "Enter a complex number: ";
		input(num2);
		cout << "The numbers you entered were ";
		print(num1);
		cout << " and "; 
		print(num2);
		cout << endl;
		cout << "Is this correct? (y/n) ";
		cin >> answer;
		cin.ignore();
	} while (toupper(answer) != 'Y'); 

	cout << "The sum of these numbers is: ";
	print(add(num1, num2));
	cout << endl;
	cout << "The difference of these numbers is: ";
	print(subtract(num1, num2));
	cout << endl;
	cout << "The product of these numbers is: ";
	print(multiply(num1,num2));
	cout << endl;
	cout << "The magnitude of the first number is: ";
	print(magnitude(num1));
	cout << endl;

}

complex::complex(){
	real = 0.0;
	imag = 0.0;
}
complex::complex(double a, double b){
	real = a;
	imag = b;
}

void print(const complex & right){
	cout << right.real;
	if (right.imag != 0.0)
		cout << (right.imag > 0.0 ? " + " : " - ") 
		       << (right.imag > 0.0 ? right.imag : -1.0 * right.imag) << "i";
}
void input(complex & right){
	char finput[20], input[20], ainput[10];
	cin.getline(finput, 20);
	int i = 0, a = 0; 

	while (finput[i] != '\0'){
		if(finput[i] != ' ')
			input[a++] = finput[i];
		i++;
	}
	input[a] = '\0';

	i = 0, a = 0;
	right.real = 0;
	right.imag = 0;

	do{
		while (isdigit(input[i]) || input[i] == '.' || input[i] == '-'){ 
			ainput[a++] = input[i];
			ainput[a] = '\0';
			if (!isdigit(input[i+1]) && input[i+1] != '.')
				break;
			i++;
		}
		
		if (input[i+1] == 'i' && input[i]== '-'){
			a = 0;	
			right.imag = -1.0;
		}
		else if (input[i] == 'i' && (i == 0 || input[i-1] == '+')){
			a = 0;
			right.imag = 1.0;
		}
		else if (a > 0) {
			if (input[i + 1] == 'i'){
				right.imag = atof(ainput);
				a = 0;
			}
			else{ 
				right.real = atof(ainput);
				a = 0;
			}
		}
		i++;
	} while (input[i] != '\0');

}

complex add(const complex & left, const complex & right){
	//(a+bi) + (c+di) = (a+c) + (b+d)i
	complex result;
	result.real = left.real + right.real;
	result.imag = left.imag + right.imag;
	return result;
}
complex subtract(const complex & left, const complex & right){
	//(a+bi) - (c+di) = (a-c) + (b-d)i  
	complex result;
	result.real = left.real - right.real;
	result.imag = left.imag - right.imag;
	return result;
}
complex multiply(const complex & left, const complex & right){
	//(a+bi)*(c+di) = (ac-bd) + (ad+bc)i
	complex result;
	result.real = left.real * right.real - left.imag * right.imag;
	result.imag = left.real * right.imag + left.imag * right.real;
	return result;
}
complex divide(const complex & left, const complex & right){
	//(a+bi)/(c+di) = (ac+bd)/(c^2+d^2) + (bc-ad)i/(c^2+d^2)   
	complex result;
	result.real = (left.real * right.real + left.imag * right.imag) / (right.real * right.real + right.imag * right.imag);
	result.imag = (left.imag * right.real - left.real * right.imag) / (right.real * right.real + right.imag * right.imag);
	return result;
}

complex magnitude(const complex & left){
	//magnitude(a+bi) = sqrt(a^2 + b^2)    
	complex result;
	result.real = sqrt(left.real * left.real + left.imag * left.imag);
	result.imag = 0;
	return result;
}      