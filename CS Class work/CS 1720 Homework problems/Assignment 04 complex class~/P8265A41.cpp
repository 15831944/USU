//P8265A33.CPP
//Mark Salisbury
//Assignment 3.3
//CS 1720 
/*
CS1720 Assignment 4    Classes 2

A41. Modify your Complex class to include good identified output and input of complex 
numbers in the form a + bi, overload the +, -, *, /, <<, >>, >, <, <=, >=, ==, !=
operators so that basic complex number arithmetic can be done in the usual way such as:
z = x + y;
z = x - y,
z = x*y,
z = x/y, and 
cin >> x >> y;
cout << x << y; 
x == y; x != y; x >= y; x <= y; x < y; x > y; where x, y, and z are complex numbers.

A complex number is considered to be greater than another complex number if the 
magnitude of the first is greater than the second. Two complex numbers are == only if 
the real1 == real2 and imaginary1 == imaginary2. Be sure you use doubles for the real 
and imaginary part of the complex number.

I can now assume that your constructors work, so for A23, input several complex numbers 
and test all the functions with the numbers that are input by the user.
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
	bool operator==(const complex &) const;
	bool operator!=(const complex &) const;
	bool operator>(const complex &) const;
	bool operator>=(const complex &) const;
	bool operator<(const complex &) const;
	bool operator<=(const complex &) const;
	double magnitude() const;
private:
	double real;
	double imag;
};

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
		cout << "Is this correct? (y/n) ";
		cin >> answer;
		cin.ignore();
		
	} while (toupper(answer) != 'Y'); 

	cout << "The sum of these numbers is: " << num1 + num2 << endl;
	cout << "The difference of these numbers is: " << num1 - num2 << endl;
	cout << "The product of these numbers is: " << num1 * num2 << endl;
	cout << "The magnitude of the first number is: " << num1.magnitude() << endl;
	cout << "Test of operator ==: The first number " << 
		(num1 == num2 ? "is equal to":"is not equal to") << " the second." << endl; 
	cout << "Test of operator !=: The first number " << 
		(num1 != num2 ? "is not equal to":"is equal to") << " the second." << endl;
	cout << "Test of operator >: The first number " << 
		(num1 > num2 ? "is greater than":"is not greater than") << " the second." << endl;
	cout << "Test of operator >=: The first number " << 
		(num1 >= num2 ? "is greater than or equal to":"is not greater than or equal to") 
		<< " the second." << endl;
	cout << "Test of operator <: The first number " << 
		(num1 < num2 ? "is less than":"is not less than") << " the second." << endl;
	cout << "Test of operator <=: The first number " << 
		(num1 <= num2 ? "is less than or equal to":"is not less than or equal to") 
		<< " the second." << endl;
}

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

bool complex::operator==(const complex &right) const{
	return (real == right.real && imag == right.imag);
}

bool complex::operator!=(const complex &right) const{
	return !(*this == right);
}

bool complex::operator>(const complex &right) const{
	return (this->magnitude() > right.magnitude());
}

bool complex::operator>=(const complex &right) const{
	return (*this == right || *this > right);
}

bool complex::operator<(const complex &right) const{
	return (this->magnitude() < right.magnitude());
}

bool complex::operator<=(const complex &right) const{
	return (*this == right || *this < right);
}

double complex::magnitude() const{
	return sqrt(real * real + imag * imag);
}
