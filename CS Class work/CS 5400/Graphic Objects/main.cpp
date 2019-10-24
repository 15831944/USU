#include <math.h>
#include "graphics.cpp"

#include "Graphicobject.h"

Vector3d TranslatePoint (Vector3d &Point, double tx, double ty, double tz)
{
	double cos1 = cos(tz);
	double cos2 = cos(tx);
	double cos3 = cos(ty);
	double sin1 = sin(tz);
	double sin2 = sin(tx);
	double sin3 = sin(ty);
	
	
	FourSquareMatrix RotationMatrix(cos1 * cos3 - sin1 * sin2 * sin3, -sin1 * cos2, cos1 * sin3 + sin1 * sin2 * cos3,0,
		 sin1 * cos3 + cos1 * sin2 * sin3, cos1 * cos2, sin1 * sin3 - cos3 * cos1 * sin2,0,
		 -cos2*sin3,sin2,cos2*cos3,0,
		 0,0,0,1.0);
	
	/*
	FourSquareMatrix RotationMatrix(cos1 * cos3 + sin1 * sin2 * sin3, -sin1 * cos2, -cos1 * sin3 + sin1 * sin2 * cos3,0,
		 sin1 * cos3 - cos1 * sin2 * sin3, cos1 * cos2, -sin1 * sin3 - cos3 * cos1 * sin2,0,
		 cos2 * sin3, sin2, cos2 * cos3, 0,
		 0.0, 0.0, 0.0, 1.0);
	*/
	/*
	FourSquareMatrix RotationMatrix(1, 0, 0, 0,
		 0,cos2,-sin2,0,
		 0,sin2,cos2,0,
		 0,0,0,1);
	*/
	return RotationMatrix.MatrixMultiply(Point);
}





const double pi = 3.141596;

//void __stdcall WinMain()
int Main()

{
	WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, 1);
	
    if (!MyWindow.WindowIsOpen())
        return 255;
	double xmax = GetSystemMetrics(SM_CXSCREEN);
	double ymax = GetSystemMetrics(SM_CYSCREEN);

	Vector3d Point1(100,100,100);
	Vector3d Point2;
	
	double theta = 0.0;
	int x1 = Point1.x + xmax / 2;
	int y1 = Point1.y + ymax / 2;
	int x2 = x1;
	int y2 = y1;
	COLORREF color = RGB(255,0,0);

	double theta2 = 0.0;

	while (MyWindow.WindowIsOpen())
    {
		// Wait for escape to be pressed.
		theta += pi / 32;
		theta2 += pi / 64;
		if (theta > 2 * pi)
			theta = 0.0;
		if (theta2 > 2 * pi)
			theta2 = 0.0;
			
		Point2 = TranslatePoint(Point1,0,0,theta);
		x1 = Point2.x + xmax / 2;
		y1 = Point2.y + ymax / 2;
		MyWindow.DrawLine(x1,y1,x2,y2, color);
		x2 = x1;
		y2 = y1;
		//Sleep(5);
		
        MyWindow.CheckEscape();
    }
    return 0;
}