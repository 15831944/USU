#include <iostream.h>
#include <math.h>
#include "point2.h"


ostream & operator<<(ostream & output, const point2 & p1){
	cout << '[' << p1.x << ", " << p1.y << ']' << endl;
	return output;
}

point2::point2(double a, double b){
	setPoint(a, b);
}

void point2::setPoint(double a, double b){
	x = a;
	y = b;
}


double point2::distance(const point2 & p1, const point2 & p2){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return sqrt(dx * dx + dy * dy);
}

double point2::area3Points(const point2 & v1, const point2 & v2, const point2 & v3){
	double a = v2.y - v1.y;
	double b = v1.x - v2.x;
	double c = v1.y * v2.x - v1.x * v2.y;
	double height = fabs(a * v3.x + b * v3.y + c) / sqrt(a * a + b * b);
	double base = distance(v1, v2);
	return base * height / 2;
}

/*
double point2::distance(point2 p1, point2 p2){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return sqrt(dx * dx + dy * dy);
}
*/