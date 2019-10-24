#ifndef PARALELLOGRAM_H
#define PARALELLOGRAM_H

#include <iostream.h>
#include "quatrilateral.h"
#include "point2.h"

class paralellogram : public quatrilateral {
	friend ostream & operator<<(ostream &, const paralellogram &);
public:
	paralellogram( point2 = point2(), point2 = point2(), point2 = point2(), point2 = point2());
	paralellogram( quatrilateral );
	void setparalellogram(point2, point2, point2, point2);
	double perimeter();
	double area();
protected:
	quatrilateral q;
};

#endif