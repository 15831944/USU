#ifndef POINT2_H
#define POINT2_H

#include <iostream.h>

class point2 {
	friend ostream & operator<<(ostream &, const point2 &);
public:
	point2(double = 0.0, double = 0.0);
	void setPoint(double, double);
	double area3Points(const point2 &, const point2 &, const point2 &);
	double distance(const point2 &, const point2 &); 
protected:
	double x;
	double y;
};

#endif