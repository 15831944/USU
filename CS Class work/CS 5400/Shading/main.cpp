#include <afx.h>
#include "graphics.cpp"
#include <fstream.h>
#include "Object3d.h"

const double pi = 3.141596;

extern bool ReadObject(CString fileName, Object3d &object);
extern void CreateField(Object3d &field);

void GetShuttlePos(double pos, CVector3d &offSet, CVector3d &rotation);

int *screenX;
int *screenY;

int Main()
{
	DWORD startTime;

	//Object3d spaceShuttle(310, 393, TRUE);
	//ReadObject("shuttle.obj", spaceShuttle);

	Object3d dragon(4922, 6039, TRUE, Phong);
	ReadObject("dragon.obj", dragon);

	screenX = new int[4922];
	screenY = new int[4922];

	Object3d field(169, 144, TRUE, Lambert); // nLines 2 + 2 * nLines
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

	while (MyWindow.WindowIsOpen())
	{
		theta += 0.1;
		shuttleRotation.SetVector(0,theta,0);//(pi/2.0,pi,0);

		MyWindow.ClearWindow();
		CenterPoint.SetVector(shuttlePos);
		ViewPoint.SetVector(16,7,16);
		//MyWindow.ProjectPoints(CVector3d(0,0,0),CVector3d(0,0,0), field, ViewPoint, CenterPoint);
		//MyWindow.CheckEscape();
		MyWindow.ProjectPoints(shuttleRotation, shuttlePos, dragon, ViewPoint, CenterPoint);
		MyWindow.SwapBuffers();	
		MyWindow.CheckEscape();
	}

	while (MyWindow.WindowIsOpen())
	{
		MyWindow.CheckEscape();
	}
	
	return 0;
}

