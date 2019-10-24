#include "graphics.cpp"
#include "RunnerData.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>


int ymax;
int xmax;
double pi = 3.1415916;



double Distance(double xdist, double ydist)
{
	return sqrt(xdist * xdist + ydist * ydist);
}

void PolyLine(int xOff, int yOff, int x[], int y[], int n, COLORREF color, WindowClass &MyWindow)
{
	for (int i = 1; i < n; i++)
		MyWindow.DrawLine(xOff + x[i-1], ymax - (yOff + y[i-1]), xOff + x[i], ymax - (yOff + y[i]),color);
}

void Morph (WindowClass &MyWindow, int xOffSet, int yOffSet, int xPoint1[], int yPoint1[], int xPoint2[], int yPoint2[], int points, int steps, int stepnum, COLORREF color)
{
	/*
	if (erase && stepnum > 0)
	{
		int xp1, int yp1, int xp2, int yp2;
		xp1 = xOffSet + (xPoint2[0] - xPoint1[0]) * (stepnum - 1) / steps + xPoint1[0];
		yp1 = yOffSet + (yPoint2[0] - yPoint1[0]) * (stepnum - 1) / steps + yPoint1[0];
		for (int i = 1; i < points; i++)
		{
			xp2 = xp1;
			yp2 = yp1;
			xp1 = (xPoint2[i] - xPoint1[i]) * (stepnum - 1) / steps + xPoint1[i];
			yp1 = (yPoint2[i] - yPoint1[i]) * (stepnum - 1) / steps + yPoint1[i];
			MyWindow.DrawLine(xp1,ymax-yp1,xp2,ymax-yp2,RGB(0,0,0));			
		}
	}
	*/
	int xp1, int yp1, int xp2, int yp2;
	xp1 = xOffSet + (xPoint2[0] - xPoint1[0]) * (stepnum) / steps + xPoint1[0];
	yp1 = yOffSet + (yPoint2[0] - yPoint1[0]) * (stepnum) / steps + yPoint1[0];
	for (int i = 1; i < points; i++)
	{
		xp2 = xp1;
		yp2 = yp1;
		xp1 = xOffSet + (xPoint2[i] - xPoint1[i]) * (stepnum) / steps + xPoint1[i];
		yp1 = yOffSet + (yPoint2[i] - yPoint1[i]) * (stepnum) / steps + yPoint1[i];
		MyWindow.DrawLine(xp1,ymax-yp1,xp2,ymax-yp2,color);			
	}

}

void DrawRunner(int xOffSet, WindowClass &MyWindow, COLORREF color);
void DrawFinish(WindowClass &MyWindow);

int Main()
{
    // Create a full screen window.
	
    WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, 1);
	
    if (!MyWindow.WindowIsOpen())
        return 255;
	xmax = GetSystemMetrics(SM_CXSCREEN);
	ymax = GetSystemMetrics(SM_CYSCREEN);

	int xbase = xmax / 2;
	int ybase = ymax / 2;
	COLORREF color;
    // Now draw the lines.
	/*
	double theta = 0.0;
	int radius = 300;
	
	int r1 = 90;
	int b1 = 100;
	int g1 = 230;
	int r2 = 200;
	int b2 = 200;
	int g2 = 50;

	for (; theta < 2 * pi; theta += pi / 180)
	{
		int x2 = xbase + cos(theta) * radius;
		int y2 = ybase + sin(theta) * radius;
		color = RGB(r1 + (r2-r1) * theta / (2 * pi), 
					g1 + (g2-g1) * theta / (2 * pi),
					b1 + (b2-b1) * theta / (2 * pi));
		BLine(xbase,ybase,x2,y2,MyWindow,color);
	}

	
	//BLine(0, 300, 50, 0, MyWindow);

	int x1 = 300;
	int y1 = 300;
	int x2 = 300;
	int y2 = 300;
	int counter = 0;
	color = RGB(255,0,0);
	int bred = 155;
	int bblue = 255;
	int bgreen = 200;
	int red, green, blue;
	
	do
	{
		counter ++;
		
		red = bred + sin((counter % 101) * pi / 100) * 100;
		blue = bblue - sin((counter % 101) * pi / 100) * 100;
		green = bgreen;

		BLine(x1,y1,x2,y2,MyWindow,RGB(red,green,blue));
		if (y1 < ymax - 300)
			y1++;
		else 
			x1++;

		if (x2 < xmax - 300)
			x2++;
		else
			y2++;

	}
	while (x1 < xmax - 300 && y2 < ymax - 300);
		
	//color = RGB(0,255,0);

	ellipseMidpoint (xbase, ybase, 500, 400, MyWindow, color);
	
	int nObjects = 8;
	int maxObjects = nObjects * 2;
	double *xPos = new double[maxObjects];
	double *yPos = new double[maxObjects];
	double *Mass = new double[maxObjects];
	double *radius = new double[maxObjects];
	double *xA = new double[maxObjects];
	double *yA = new double[maxObjects];
	double *xV = new double[maxObjects];
	double *yV = new double[maxObjects];
	COLORREF *colors = new COLORREF[maxObjects];

	double distance;
	double xdist;
	double ydist;

	srand(time(0));

	for (int i = 0; i < nObjects; i++)
	{
		xV[i] = rand() % 6 - 3;
		yV[i] = rand() % 6 - 3;
		xPos[i] = rand() % (xmax * 4 / 6) + xmax / 6;
		yPos[i] = rand() % (ymax * 4 / 6) + ymax / 6;
		Mass[i] = rand() % 500 - 250;
		if (Mass[i] < 0)
			colors[i] = RGB(200 + rand() % 55, 150, 150);
		else
			colors[i] = RGB(150, 150, 200 + rand() % 55);

		radius[i] = sqrt(sqrt(Mass[i]*Mass[i])) * 1;
		DrawObject(xPos[i],yPos[i], radius[i], MyWindow, colors[i]);
	}

	DWORD startTime = timeGetTime();
	BOOL dirty = TRUE;
    while (MyWindow.WindowIsOpen())
    {
		DWORD timeNow = timeGetTime();
		if (dirty && timeNow - startTime > 30)
		{
			MyWindow.ClearWindow();
			dirty = FALSE;
		}

		// draw objects
		for (int i = 0; i < nObjects; i++)
		{
			xA[i] = 0.0;
			yA[i] = 0.0;
			for (int j = 0; j < nObjects; j++)
			{
				
				if (j == i)
					continue;
				
				if (xPos[i] > xmax / 2)
				{
					if (xPos[j] < xPos[i] - xmax / 2)
						xdist =  xPos[j] + xmax - xPos[i];	
					else
						xdist = xPos[j] - xPos[i];
				}
				else
				{
					if (xPos[j] > xPos[i] + xmax / 2)
						xdist =  xPos[i] + xmax - xPos[j];	
					else
						xdist = xPos[j] - xPos[i];
				}

				if (yPos[i] > ymax / 2)
				{
					if (yPos[j] < yPos[i] - ymax / 2)
						ydist =  yPos[j] + ymax - yPos[i];	
					else
						ydist = yPos[j] - yPos[i];
				}
				else
				{
					if (yPos[j] > yPos[i] + ymax / 2)
						ydist =  yPos[i] + ymax - yPos[j];	
					else
						ydist = yPos[j] - yPos[i];
				}
				
				distance = Distance(xdist,ydist);
				
				if (distance <= radius[i] + radius[j] && j > i)
				{
					// collision
					double vx = xV[i];
					double vy = yV[i];
					double idealDistance = radius[i] + radius[j];
					xV[i] = Mass[j] / Mass[i] * xV[j];
					yV[i] = Mass[j] / Mass[i] * yV[j];
					xV[j] = Mass[i] / Mass[j] * vx;
					yV[j] = Mass[i] / Mass[j] * vy;
					DrawObject(xPos[i],yPos[i], radius[i], MyWindow, RGB(0,0,0));
					xPos[i] = xPos[i] - (xdist * idealDistance / distance - xdist);
					yPos[i] = yPos[i] - (ydist * idealDistance / distance - ydist);
				}

				xA[i] += Mass[j] * xdist / pow(distance,3.0);
				yA[i] += Mass[j] * ydist / pow(distance,3.0);
			}
			xV[i] += xA[i];
			yV[i] += yA[i];
			DrawObject(xPos[i],yPos[i], radius[i], MyWindow, RGB(0,0,0));
			
			xPos[i] = xPos[i] + xV[i];
			yPos[i] = yPos[i] + yV[i];
			if (xPos[i] > xmax)
				xPos[i] -= xmax;
			else if (xPos[i] < 0)
				xPos[i] += xmax;
			
			if (yPos[i] > ymax)
				yPos[i] -= ymax;
			else if (yPos[i] < 0)
				yPos[i] += ymax;
			
			DrawObject(xPos[i],yPos[i], radius[i], MyWindow, colors[i]);
			//Mass[i]+=radius[i]/10;
		}

		// Wait for escape to be pressed.
        MyWindow.CheckEscape();
    }
	delete [] xPos;
	delete [] yPos;
	delete [] Mass;
	delete [] xA;
	delete [] yA;
	delete [] xV;
	delete [] yV;
	delete [] radius;
	delete [] colors;
	*/
/*
	int manX[] = {80,90,90,70,70,80,80,80,120,120,90,70,
					80,80,60,60,70,90,120,120,100,100,
					120,140,140,120,120,150,170,180,180,160,
					160,170,150,120,120,160,160,160,150,150,170,170,160,160,160};
	int manY[] = {20,20,0,0,20,20,20,20,120,230,230,140,
					140,120,120,140,140,230,230,250,260,300,
					310,300,260,250,230,230,140,140,120,120,
					140,140,230,230,120,20,20,20,20,0,0,20,20,20,20};

	int wManX[] = {90,100,100,80,80,90,90,50,120,120,90,70,
					80,80,60,60,70,90,120,120,100,100,
					120,140,140,120,120,150,170,180,180,160,
					160,170,150,120,120,190,150,150,140,140,160,160,160,160,160};
	int wManY[] = {20,20,0,0,20,20,50,50,140,230,230,140,
					140,120,120,140,140,230,230,250,260,300,
					310,300,260,250,230,230,140,140,120,120,
					140,140,230,230,140,50,50,20,20,0,0,20,20,20,20};
	*/
	

	int xLine[30];
	int yLine[30];
	for (int i = 0; i < 30; i++)
	{
		xLine[i] = i * xmax / 30;
		yLine[i] = 20;
	}

	

	//PolyLine(xOffSet,yOffSet,manX,manY,30,RGB(255,0,0),MyWindow);
	//PolyLine(xOffSet + 200 ,yOffSet,wManX,wManY,30,RGB(255,0,0),MyWindow);
	DWORD time1 = timeGetTime();

	int xOffSet = 0;
	int yOffSet = 0;
	

		
		//for ( i = 0; i <= 50; i++){
		//	MyWindow.ClearWindow();
		//	Morph (MyWindow, xOffSet, yOffSet, manXSide3, manYSide3, manXSide2, manYSide2, 30, 50, i,false);
		//	Sleep(20);
		//	xOffSet++;
		//}
		
	
	DWORD time2 = timeGetTime();

	
	DWORD time3 = timeGetTime();
	DWORD ttime1 = time2 - time1;
	DWORD ttime2 = time3 - time2;
	/*
	for ( i = 0; i <= 50; i++){
			MyWindow.ClearWindow();
			Morph (MyWindow, xOffSet, yOffSet, manX, manY, manXSide1, manYSide1, 30, 50, i,);
			Sleep(20);
			xOffSet++;
		}
	*/
	double R1Off = 0;
	double R2Off = 0;
	double R3Off = 0;

	double R1Speed = 2.30;
	double R2Speed = 2.15;
	double R3Speed = 2;

	COLORREF R1Color = RGB(0,255,255);
	COLORREF R2Color = RGB(255,0,0);
	COLORREF R3Color = RGB(0,255,0);

	int loop = 0;
	bool drawFinish = false;
	while (MyWindow.WindowIsOpen())
    {
		
		MyWindow.ClearWindow();
		DrawRunner(R1Off,MyWindow,R1Color);
		DrawRunner(R2Off,MyWindow,R2Color);
		DrawRunner(R3Off,MyWindow,R3Color);
		if (drawFinish)
			DrawFinish(MyWindow);

		R1Off += R1Speed;
		R2Off += R2Speed;
		R3Off += R3Speed;

		Sleep(8);
		if (R1Off >= xmax - 50)
			R1Off = 0;
		if (R2Off >= xmax - 50)
			R2Off = 0;
		if (R3Off >= xmax - 50)
		{
			loop++;
			if (loop == 2)
				drawFinish = true;
			R3Off = 0;
			if (R3Speed = 2)
				R3Speed = 2.53;
		}
	

		// Wait for escape to be pressed.
        MyWindow.CheckEscape();
    }
    return 0;
}

void DrawRunner(int xOffSet, WindowClass &MyWindow, COLORREF color)
{
	int Position = xOffSet % 80;
	int yOffSet = 0;
	int i = Position % 20;

	if  ( Position < 20 ){
		
		Morph (MyWindow, xOffSet, yOffSet, manXSide1, manYSide1, manXSide2, manYSide2, 30, 19, i,color);
	}
	else if ( Position < 40 ){
		
		Morph (MyWindow, xOffSet, yOffSet, manXSide2, manYSide2, manXSide3, manYSide3, 30, 19, i,color);
	}
	else if ( Position < 60 ){
		
		Morph (MyWindow, xOffSet, yOffSet, manXSide3, manYSide3, manXSide4, manYSide4, 30, 19, i,color);
	}
	else if ( Position < 80 ){
		
		Morph (MyWindow, xOffSet, yOffSet, manXSide4, manYSide4, manXSide1, manYSide1, 30, 19, i,color);
	}
}

void DrawFinish(WindowClass &MyWindow)
{



}