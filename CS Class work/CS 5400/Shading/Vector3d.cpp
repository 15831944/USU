// Vector3d.cpp: implementation of the CVector3d class.
//
//////////////////////////////////////////////////////////////////////

#include "Vector3d.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector3d::CVector3d()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

CVector3d::CVector3d(double x1, double y1, double z1, double w1)
{
	x = x1;
	y = y1;
	z = z1;
	w = w1;
}

CVector3d::~CVector3d()
{
	
}

void CVector3d::Normalize()
{
	double length = sqrt(x*x+y*y+z*z);
	x /= length;
	y /= length;
	z /= length;
}

double CVector3d::operator*(const CVector3d & right) const
{
	return x * right.x + y * right.y + z * right.z;
}

CVector3d CVector3d::operator+(const CVector3d & right) const
{
	return CVector3d(x + right.x, y + right.y, z + right.z);
}

CVector3d & CVector3d::operator/=(int right)
{
	x /= right;
	y /= right;
	z /= right;
	return *this;
}

CVector3d & CVector3d::operator+=(const CVector3d & right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
}