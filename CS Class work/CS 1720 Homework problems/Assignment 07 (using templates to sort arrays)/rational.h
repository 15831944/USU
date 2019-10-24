#ifndef RATIONAL_H
#define RATIONAL_H

#include<iostream.h>

class Rational
{
	friend ostream & operator<<(ostream & output, const Rational &); 
public:
	  Rational(int num = 0, int denom = 1); //default constructor
	  Rational Add(const Rational &);
	  Rational Subtract(const Rational &);
	  Rational Multiply(const Rational &);
	  Rational Divide(const Rational &);
	  double Value(void) const;
	  void Input(void);
	  bool operator<(const Rational &) const;
	  bool operator>(const Rational &) const;
  private:
	  int	numerator,
			denominator;

};

#endif