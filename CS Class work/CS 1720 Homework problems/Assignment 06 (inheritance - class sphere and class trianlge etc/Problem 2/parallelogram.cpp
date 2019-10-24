#include <iostream.h>
#include "point2.h"
#include "parallelogram.h"


ostream & operator<<(ostream & output, const paralellogram & p){
	cout <<  static_cast<quatrilateral>(p);
	return output;
}

paralellogram::paralellogram( point2 a, point2 b, point2 c, point2 d)
: quatrilateral( a, b, c, d) { }

paralellogram::paralellogram( quatrilateral q1)
: quatrilateral( q1.getv1(), q1.getv2(), q1.getv3(), q1.getv4()) { }

void paralellogram::setparalellogram(point2 a, point2 b, point2 c, point2 d){
	v1 = a;
	v2 = b;
	v3 = c;
	v4 = d;
}

double paralellogram::perimeter(){
	return distance(v1, v2) + distance(v2, v3) + distance(v3, v4) + distance(v4, v1);
}

double paralellogram::area(){
	return area3Points(v1, v2, v3) + area3Points(v1, v3, v4);
}
//
//}