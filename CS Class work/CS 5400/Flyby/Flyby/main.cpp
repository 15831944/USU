#include <afx.h>
#include "graphics.cpp"
#include <fstream.h>
#include "Object3d.h"

const double pi = 3.141596;

extern bool ReadObject(CString fileName, Object3d &object);

DWORD startTime, currentTime, calculateTime, drawTime;

int Main()
{
	Object3d spaceShuttle(310, 393);
	ReadObject("shuttle.obj", spaceShuttle);

	WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, FULL_SCREEN | DOUBLE_BUFFER);
	if (!MyWindow.WindowIsOpen())
        return 255;
	
	CVector3d ViewPoint(50,50,50);
	CVector3d CenterPoint(0,0,0);

	double theta = 0.0;

	calculateTime = 0;
	drawTime = 0;

	while (MyWindow.WindowIsOpen())
	{
		theta += pi / 32;
		MyWindow.ClearWindow();
		MyWindow.ProjectPoints(CVector3d(sin(theta),cos(theta),0), CVector3d(0,0,0), spaceShuttle, ViewPoint, CenterPoint, 1);
 
		MyWindow.SwapBuffers();	
		MyWindow.CheckEscape();
	}		
	char message[80];
	
	TRACE("DrawTime = %i CalculateTime = %i",drawTime,calculateTime);
	
	return 0;
}