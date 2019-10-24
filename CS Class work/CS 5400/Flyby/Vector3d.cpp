// Vector3d.cpp: implementation of the CVector3d class.
//
//////////////////////////////////////////////////////////////////////

#include "Vector3d.h"

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
