#ifndef COMPLEX_H
#define COMPLEX_H

class Complex {
		friend ostream & operator <<(ostream &, const Complex &);
		friend istream & operator >>(istream &, Complex &);
	public:
		Complex(double = 0.0, double = 0.0); //default constructor
		Complex operator+(const Complex &) const;
		Complex operator-(const Complex &) const;
		Complex operator*(const Complex &) const;
		Complex operator/(const Complex &) const;
		double Magnitude(void)const;
		int operator >(const Complex &) const;
		int operator <(const Complex &) const;
		int operator >=(const Complex &) const;
		int operator <=(const Complex &) const;
		int operator !=(const Complex &) const;
		int operator ==(const Complex &) const;
	private:
		double RealP;
		double ImagP;
};

#endif