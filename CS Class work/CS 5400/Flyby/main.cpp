#include <afx.h>
#include "graphics.cpp"
#include <fstream.h>
#include "Object3d.h"

const double pi = 3.141596;

extern bool ReadObject(CString fileName, Object3d &object);
extern void CreateField(Object3d &field);

void GetShuttlePos(double pos, CVector3d &offSet, CVector3d &rotation);

int Main()
{
	DWORD startTime;

	Object3d spaceShuttle(310, 393, TRUE);
	ReadObject("shuttle.obj", spaceShuttle);

	Object3d field(60, 26, FALSE); // nLines 2 + 2 * nLines
	CreateField(field);	

	WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, FULL_SCREEN | DOUBLE_BUFFER);
	if (!MyWindow.WindowIsOpen())
        return 255;

	double theta = 0.0;

	CVector3d shuttlePos;
	CVector3d shuttleRotation;
	CVector3d ViewPoint(100,100,50);
	CVector3d CenterPoint(0,0,0);

	shuttleRotation.SetVector(pi/2.0,pi,0);

	for (double pos = 1; pos < 14 && MyWindow.WindowIsOpen(); pos+= 0.1)
	{
		startTime = timeGetTime();
		theta += pi/64;
		MyWindow.ClearWindow();
		GetShuttlePos(pos,shuttlePos,shuttleRotation);
		CenterPoint.SetVector(shuttlePos);
		ViewPoint.SetVector(sin(theta+pi / 2)*90.0,80,cos(theta+pi / 2)*90.0+20);
		MyWindow.ProjectPoints(CVector3d(0,0,0),CVector3d(0,0,0), field, ViewPoint, CenterPoint);
		MyWindow.ProjectPoints(shuttleRotation, shuttlePos, spaceShuttle, ViewPoint, CenterPoint);
		MyWindow.SwapBuffers();	
		MyWindow.CheckEscape();
		while (timeGetTime() - startTime < 1000/30); // 30 frames per second
	}		

	for ( pos = 1; pos < 14 && MyWindow.WindowIsOpen(); pos+= 0.1)
	{
		startTime = timeGetTime();
		theta += pi/64;
		MyWindow.ClearWindow();
		GetShuttlePos(pos,shuttlePos,shuttleRotation);
		CenterPoint.SetVector(shuttlePos);
		ViewPoint.SetVector(0,120,200);
		MyWindow.ProjectPoints(CVector3d(0,0,0),CVector3d(0,0,0), field, ViewPoint, CenterPoint);
		MyWindow.ProjectPoints(shuttleRotation, shuttlePos, spaceShuttle, ViewPoint, CenterPoint);
		MyWindow.SwapBuffers();	
		MyWindow.CheckEscape();
		while (timeGetTime() - startTime < 1000/30); // 30 frames per second
	}		
	
	for ( pos = 1; pos < 14 && MyWindow.WindowIsOpen(); pos+= 0.1)
	{
		startTime = timeGetTime();
		theta += pi/64;
		MyWindow.ClearWindow();
		GetShuttlePos(pos,shuttlePos,shuttleRotation);
		CenterPoint.SetVector(shuttlePos);
		ViewPoint.SetVector(120+theta * 20,120,-200);
		MyWindow.ProjectPoints(CVector3d(0,0,0),CVector3d(0,0,0), field, ViewPoint, CenterPoint);
		MyWindow.ProjectPoints(shuttleRotation, shuttlePos, spaceShuttle, ViewPoint, CenterPoint);
		MyWindow.SwapBuffers();	
		MyWindow.CheckEscape();
		while (timeGetTime() - startTime < 1000/30); // 30 frames per second
	}	
	while (MyWindow.WindowIsOpen())
	{
		MyWindow.CheckEscape();
	}
	
	return 0;
}

