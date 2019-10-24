#include <iostream.h>
#include "triangle.h"
#include "point2.h"

ostream & operator<<(ostream & output, const triangle & t){
	cout << "Vertice 1: " << t.v1 
		<< "Vertice 2: " << t.v2 
		<< "Vertice 3: " << t.v3;
	return output;
}

triangle::triangle(point2 a, point2 b, point2 c){
	setTriangle(a, b, c);
}

void triangle::setTriangle(point2 a, point2 b, point2 c){
	v1 = a;
	v2 = b;
	v3 = c;
}

double triangle::perimeter(){
	return distance(v1, v2) + distance(v2, v3) + distance(v3, v1);
}

double triangle::area(){
	return area3Points(v1, v2, v3);
}
//
//}
