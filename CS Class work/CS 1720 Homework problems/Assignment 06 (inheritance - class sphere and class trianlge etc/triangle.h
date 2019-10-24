#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream.h>
#include "point2.h"

class triangle : public point2 {
	friend ostream & operator<<(ostream &, const triangle &);
public:
	triangle(point2 = point2(), point2 = point2(), point2 = point2());
	void setTriangle(point2, point2, point2);
	double perimeter();
	double area();
protected:
	point2 v1;
	point2 v2;
	point2 v3;
};

#endif