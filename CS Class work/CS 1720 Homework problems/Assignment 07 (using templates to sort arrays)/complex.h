//complex.h
#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream.h>

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

#endif
