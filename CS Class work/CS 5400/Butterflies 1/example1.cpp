// This example program demonstrates drawing 3 lines of different colors.

#include <math.h>
#include "graphics.cpp"
#include <stdlib.h>

int Main()
{
    // Create a full screen window.
    WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, 1);
    if (!MyWindow.WindowIsOpen())
        return 255;

	RGBColor color;
    color = RGB(200, 200, 200);

    // Now draw the lines.
	double pi = 3.14159265359;
	double e = 2.71828182846;
	double x1 = 0.0;
	double y1 = 0.0;
	double x2;
	double y2;
	double xoffset = 500;
	double yoffset = 500;
	double scalefactor = 50;

	double theta = 0.0;
	double r;
	double increment = pi / 48;

	int g1 = 100;
	int r1 = 200;
	int b1 = 100;//50

	int g2 = 100;//120;
	int r2 = 100;//230;
	int b2 = 200;//255;
	
	DWORD starttime, time1, time2, time3;// = timeGetTime();
	DWORD calcTime = 0;
	DWORD drawTime = 0;
	starttime = timeGetTime();
	for (int b = 0; b < 60; b++)
	{
		theta = 0.0;
		xoffset = rand() % 800 + 150;
		yoffset = rand() % 700 + 150;
		r = scalefactor * (pow(e,cos(theta)) - 2 * cos (4 * theta) + pow(sin(theta / 12),5.0));
		x1 = xoffset + r * cos( theta + pi / 2);
		y1 = yoffset + r * sin( theta + pi / 2);
		theta += increment;
		for (; theta <= 24.0 * pi; theta += increment)
		{
			time1 = timeGetTime();
			color = RGB(r1 + (r2 - r1) * theta / 24,g1 + (g2 - g1) * theta / 24,b1 + (b2 - b1) * theta / 24);
			x2 = x1;
			y2 = y1;
			r = scalefactor * (pow(e,cos(theta)) - 2 * cos (4 * theta) + pow(sin(theta / 12),5.0));
			x1 = xoffset + r * cos( theta + pi / 2);
			y1 = yoffset + r * sin( theta + pi / 2);
			time2 = timeGetTime();
			MyWindow.DrawLine(x1, 1024 - y1, x2, 1024 - y2, color);
			time3 = timeGetTime();
			drawTime += time3 - time2;
			calcTime += time2 - time1;
			
		}

	}
	DWORD totalTime = timeGetTime() - starttime;
	char timeText[80];
	wsprintf(timeText,"Time required (miliseconds): %i",totalTime);
	MessageBox(NULL,timeText,"Classic Curves",MB_OK);
	wsprintf(timeText,"Calc time: %i Draw time: %i",calcTime,drawTime);
	MessageBox(NULL,timeText,"Classic Curves",MB_OK);
    while (MyWindow.WindowIsOpen())
    {
        // Wait for escape to be pressed.
        MyWindow.CheckEscape();
    }

    return 0;
}