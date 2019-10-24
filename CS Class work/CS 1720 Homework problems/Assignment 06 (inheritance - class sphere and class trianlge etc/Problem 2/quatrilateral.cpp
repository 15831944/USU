#include <iostream.h>
#include "point2.h"
#include "quatrilateral.h"


ostream & operator<<(ostream & output, const quatrilateral & q){
	cout << "Vertice 1: " << q.v1 
		<< "Vertice 2: " << q.v2 
		<< "Vertice 3: " << q.v3
		<< "Vertice 4: " << q.v4;
	return output;
}

quatrilateral::quatrilateral(point2 a, point2 b, point2 c, point2 d)
: point2(0, 0) {
	setquatrilateral(a, b, c, d);
}

void quatrilateral::setquatrilateral(point2 a, point2 b, point2 c, point2 d){
	v1 = a;
	v2 = b;
	v3 = c;
	v4 = d;
}

double quatrilateral::perimeter(){
	return distance(v1, v2) + distance(v2, v3) + distance(v3, v4) + distance(v4, v1);
}

double quatrilateral::area(){
	return area3Points(v1, v2, v3) + area3Points(v1, v3, v4);
}

point2 quatrilateral::getv1(){ return v1; }

point2 quatrilateral::getv2(){ return v2; }

point2 quatrilateral::getv3(){ return v3; }

point2 quatrilateral::getv4(){ return v4; }
//
//}