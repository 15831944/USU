//The implementation of the class Rational follows:
#include<iostream.h>
#include<stdlib.h>
#include "rational.h"


ostream & operator<<(ostream & output, const Rational & right){

	if((right.numerator < 0) && (right.denominator < 0))
		cout << abs(right.numerator) << '/' << abs(right.denominator);
	else if((right.numerator < 0) || (right.denominator < 0))
		cout << '-' << abs(right.numerator) << '/' << abs(right.denominator);
	else
		cout <<  right.numerator << '/' << right.denominator;
	return output;
}

Rational::Rational(int num, int denom)
{
  numerator = num;
  denominator = denom;
}

Rational Rational::Add(const Rational &a)
{
	Rational t;
	t.numerator = numerator*a.denominator + denominator*a.numerator;
	t.denominator = denominator*a.denominator;
	return t;
}

Rational Rational::Subtract(const Rational &s)
{
	Rational t;
	t.numerator = numerator*s.denominator - denominator*s.numerator;
	t.denominator = denominator*s.denominator;
	return t;
}

Rational Rational::Multiply(const Rational &m)
{
	Rational t;
	t.numerator = numerator*m.numerator;
	t.denominator = denominator*m.denominator;
	return t;
}

Rational Rational::Divide(const Rational &d)
{
	Rational t;
	t.numerator = numerator*d.denominator;
	t.denominator = denominator*d.numerator;
	return t;
}

double Rational::Value(void) const
{
  return double(numerator)/double(denominator);
}

void Rational::Input(void)
{
	char slash;
	cout << "Enter a rational number in the form A/B: ";
	cin >> numerator >> slash >> denominator;
}

bool Rational::operator<(const Rational & right) const {
	return (this->Value() < right.Value());
}

bool Rational::operator>(const Rational & right) const {
	return (this->Value() > right.Value());
}

// end of file rationalmf.cpp
