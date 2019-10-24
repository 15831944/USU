#include <math.h>
#include <iostream.h>
#include "Complex.h"

//overloaded operators and functions
Complex::Complex(double r, double i)
	: RealP(r), ImagP(i) { };
Complex Complex::operator+(const Complex &a) const {
	return Complex(a.RealP + RealP, a.ImagP + ImagP);
}
Complex Complex::operator-(const Complex &a) const{
	return Complex(a.RealP - RealP, a.ImagP - ImagP);
}
Complex Complex::operator*(const Complex &a) const{ 
	return Complex(a.RealP * RealP - ImagP * a.ImagP, RealP * a.ImagP + ImagP * a.RealP);}
Complex Complex::operator/(const Complex &a) const{ 
	return Complex((RealP * a.RealP + ImagP * a.ImagP) / (a.RealP * a.RealP + a.ImagP * a.ImagP),
						(ImagP * a.RealP - RealP * a.ImagP) / (a.RealP * a.RealP + a.ImagP * a.ImagP));}
double Complex::Magnitude(void) const  { return sqrt(RealP*RealP + ImagP*ImagP);}
int Complex::operator<(const Complex &a) const	{ return (Magnitude() < a.Magnitude());}
int Complex::operator>(const Complex &a) const	{ return (Magnitude() > a.Magnitude());}
int Complex::operator==(const Complex &right) const  { return ((RealP == right.RealP)&&(ImagP==right.ImagP));}
int Complex::operator!=(const Complex &right) const  { return ((RealP != right.RealP)||(ImagP!=right.ImagP));}
int Complex::operator>=(const Complex &right) const  { return ((*this > right) || (*this == right));}
int Complex::operator<=(const Complex &right) const  { return ((*this < right) || (*this == right));}

ostream & operator <<(ostream & output, const Complex &c)
{
	output << '(' << c.RealP;
	if(c.ImagP >= 0.0) output << '+';
	output << c.ImagP << "i)";
	return output;
}

istream & operator >>(istream & input, Complex &c)
{
	char sign, i;
	input >> c.RealP >> sign >> c.ImagP >> i;
	if(sign=='-') c.ImagP = -c.ImagP;
	return input;
}