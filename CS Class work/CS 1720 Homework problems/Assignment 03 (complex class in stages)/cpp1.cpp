/*
CS1720  Assignment 3     Classes 1

Arithmetic of complex numbers is defined by:

(a+bi) + (c+di) = (a+c) + (b+d)i                               // addition
(a+bi) - (c+di) = (a-c) + (b-d)i                                  // subtraction
(a+bi)*(c+di) = (ac-bd) + (ad+bc)i                           // multiplication
(a+bi)/(c+di) = (ac+bd)/(c^2+d^2) + (bc-ad)i/(c^2+d^2)         // division
magnitude(a+bi) = sqrt(a^2 + b^2)                            // magnitude

A31. Write a complete program including prototypes, a driver program, and the implementation which uses complex 
numbers without a class. This is similar to what we did first with rational numbers. The real and imaginary parts 
of the rational numbers should be of type double. Be sure to include a function print that will print a complex 
number in the usual form. Also include a function input that will allow the input of a complex number in the usual 
form. Complex numbers should be input in the form:
2.3 + 4.56i or 3.45 - 2.367i and falset 2.45 + (-2.367i) 
Complex numbers should be output in the same form. Be sure to take care of the + and - sign correctly. Use this 
form in input and output for all problems dealing with the complex number class.

A32. Write a complete program including specification, driver (client) program and implementation using the class 
Complex with public attributes and functions that are falset members of the class. Be sure to include a function 
print that will print a complex number in the usual form. Also include a function input that will allow the input 
of a complex number in the usual form.

A33. Write a complete program including specification, client program that completely tests the class, and 
implementation using the class Complex in which the attributes are private and the functions are members of the 
class. Include a function, print, that will print a complex number and use it to output the complex numbers that 
are calculated. Also include a function input that will allow the input of a complex number in the usual form.
*/


#include <iostream.h>
#include <math.h>
#include <ctype.h>


class complex {
	friend ostream & operator<<(ostream &, const complex &);
	friend istream & operator>>(istream &, complex &);
public:
	complex(double, double);
	complex();
	complex operator+(const complex &);
	complex operator-(const complex &);
	complex operator*(const complex &);
	complex operator/(const complex &);
	complex magnitude();
private:
	double real;
	double imag;
};

ostream & operator<<(ostream & output, const complex &right){
	
	output << right.real;
	if (right.imag != 0.0)
		output << (right.imag > 0.0 ? " + " : " - ") 
		       << (right.imag > 0.0 ? right.imag : -1.0 * right.imag) << "i";
	return output;
}

istream & operator>>(istream & source, complex &right){
	
	char finput[20], input[20], ainput[10];
	source.getline(finput, 20);
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
	return source;
}

complex::complex(double a, double b){
	real = a;
	imag = b;
}

complex::complex(){
	real = 0.0;
	imag = 0.0;
}

complex complex::operator+(const complex & right){
	//(a+bi) + (c+di) = (a+c) + (b+d)i
	complex result;
	result.real = real + right.real;
	result.imag = imag + right.imag;
	return result;
}
complex complex::operator-(const complex & right){
	//(a+bi) - (c+di) = (a-c) + (b-d)i  
	complex result;
	result.real = real - right.real;
	result.imag = imag - right.imag;
	return result;
}
complex complex::operator*(const complex & right){
	//(a+bi)*(c+di) = (ac-bd) + (ad+bc)i
	complex result;
	result.real = real * right.real - imag * right.imag;
	result.imag = real * right.imag + imag * right.real;
	return result;
}
complex complex::operator/(const complex & right){
	//(a+bi)/(c+di) = (ac+bd)/(c^2+d^2) + (bc-ad)i/(c^2+d^2)   
	complex result;
	result.real = (real * right.real + imag * right.imag) / (right.real * right.real + right.imag * right.imag);
	result.imag = (imag * right.real - real * right.imag) / (right.real * right.real + right.imag * right.imag);
	return result;
}

complex complex::magnitude(){
	//magnitude(a+bi) = sqrt(a^2 + b^2)    
	complex result;
	result.real = sqrt(real * real + imag * imag);
	result.imag = 0;
	return result;
}      

void main(){
	complex num1;
	complex num2;
	char answer;
	
	do{
		cout << "Enter a complex number: ";
		cin >> num1;
		cout << "Enter a complex number: ";
		cin >> num2;
		cout << "The numbers you entered were " << num1 << " and " << num2 << endl;
		cout << "Is this correct? (y/n)";
		cin >> answer;
	} while (toupper(answer) != 'Y'); 

	cout << "The sum of these numbers is: " << num1 + num2 << endl;
	cout << "The difference of these numbers is: " << num1 - num2 << endl;
	cout << "The product of these numbers is: " << num1 * num2 << endl;
	cout << "The magnitude of the first number is: " << num1.magnitude() << endl;

}