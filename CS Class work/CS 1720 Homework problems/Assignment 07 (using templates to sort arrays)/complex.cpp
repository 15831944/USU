//complex.cpp

#include <iostream.h>
#include <math.h>
#include <ctype.h>
#include "complex.h"

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
