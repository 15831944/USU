#include "vector3d.h"
#include <math.h>

const double pi = 3.141596;

void GetShuttlePos(double pos, CVector3d &offSet, CVector3d &rotation)
{
	static double loopStart = 4.0;
	static double xValue = -4.0; // radians
	static double zValue = 0.0;
	static double height = 2.0;
	static double scale  = 20.0;
	static double radius = 1.0;

	offSet.z = zValue;

	if (pos < loopStart)
	{
		offSet.y = height * scale;
		offSet.x = (pos + xValue) * scale;
	}
	else if (pos < 2 * pi + loopStart)
	{
		offSet.y = (radius + height- cos(pos - loopStart) * radius) * scale;
		offSet.x = (xValue + loopStart + sin(pos - loopStart) * radius) * scale;
		rotation.y = -(pi + pos - loopStart);
	}
	else
	{
		offSet.y = height * scale;
		offSet.x = (xValue + loopStart + pos - (2 * pi+loopStart)) * scale;
	}

}