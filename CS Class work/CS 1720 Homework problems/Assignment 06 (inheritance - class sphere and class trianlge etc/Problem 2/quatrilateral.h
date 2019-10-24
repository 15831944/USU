#ifndef quatrilateral_H
#define quatrilateral_H

#include <iostream.h>
#include "point2.h"

class quatrilateral : public point2 {
	friend ostream & operator<<(ostream &, const quatrilateral &);
public:
	quatrilateral(point2 = point2(), point2 = point2(), point2 = point2(), point2 = point2());
	void setquatrilateral(point2, point2, point2, point2);
	point2 getv1();
	point2 getv2();
	point2 getv3();
	point2 getv4();
	double perimeter();
	double area();
protected:
	point2 v1;
	point2 v2;
	point2 v3;
	point2 v4;
};

#endif