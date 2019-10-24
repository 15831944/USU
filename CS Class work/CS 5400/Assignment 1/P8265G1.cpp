//Mark Salisbury
//CS 5400
//Student ID 529-71-8265

#include <math.h>
#include "graphics.cpp"
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define DELAY		20
double pi = 3.14159265359;
double e = 2.71828182846;

int g1;
int r1;
int b1;

int g2;
int r2;
int b2;

void drawButterfly(int xoffset, int yoffset, bool InColor, double scalefactor, WindowClass &MyWindow)
{
	static double x1;
	static double y1;
	static double x2;
	static double y2;
	static double theta;
	static double r;
	static double increment = pi / 48;
	static RGBColor color;
	

	theta = 0.0;
	r = scalefactor * (pow(e,cos(theta)) - 2 * cos (4 * theta) + pow(sin(theta / 12),5.0));
	x1 = xoffset + r * cos( theta + pi / 2);
	y1 = yoffset + r * sin( theta + pi / 2);
	theta += increment;
	color = RGB(0,0,0);
	for (; theta <= 24.0 * pi; theta += increment)
	{
		if (InColor)
			color = RGB(r1 + (r2 - r1) * theta / (24*pi),g1 + (g2 - g1) * theta / (24*pi),b1 + (b2 - b1) * theta / (24*pi));
		x2 = x1;
		y2 = y1;
		r = scalefactor * (pow(e,cos(theta)) - 2 * cos (4 * theta) + pow(sin(theta / 12),5.0));
		x1 = xoffset + r * cos( theta + pi / 2);
		y1 = yoffset + r * sin( theta + pi / 2);
		MyWindow.DrawLine(x1, 1024 - y1, x2, 1024 - y2, color);
	}
}

void drawDeltoid(int xoffset, int yoffset, bool InColor, double scalefactor, double rotation, WindowClass &MyWindow)
{
	static double x1;
	static double y1;
	static double x2;
	static double y2;
	static double theta;
	static double r;
	static double increment = pi / 48;
	static RGBColor color;

	theta = 0.0;
	r = scalefactor * theta;
	x1 = xoffset + r * cos( theta + rotation);
	y1 = yoffset + r * sin( theta + rotation);
	theta += increment;
	color = RGB(0,0,0);
	for (; theta <= 12.0 * pi; theta += increment)
	{
		if (InColor)
			color = RGB(r1 + (r2 - r1) * theta / (12.0*pi),g1 + (g2 - g1) * theta / (12.0*pi),b1 + (b2 - b1) * theta / (12.0*pi));
		x2 = x1;
		y2 = y1;
		r = scalefactor * theta;
		x1 = xoffset + r * cos( theta + rotation);
		y1 = yoffset + r * sin( theta + rotation);
		MyWindow.DrawLine(x1, 1024 - y1, x2, 1024 - y2, color);
	}



}
void drawStuff(int xoffset, int yoffset, bool InColor, double scalefactor, double rotation, WindowClass &MyWindow)
{
	static double x1;
	static double y1;
	static double x2;
	static double y2;
	static double theta;
	static double r;
	static double increment = pi / 48;
	static RGBColor color;

	theta = 0.0;
	
	x1 = xoffset + scalefactor * (3 * cos( theta + rotation) - 3 * cos (3 * theta + rotation));
	y1 = yoffset + scalefactor * (3 * sin( theta + rotation) - 3 * sin (3 * theta + rotation));
	theta += increment;
	color = RGB(0,0,0);
	for (; theta <= 12.0 * pi; theta += increment)
	{
		if (InColor)
			color = RGB(r1 + (r2 - r1) * theta / (12.0*pi),g1 + (g2 - g1) * theta / (12.0*pi),b1 + (b2 - b1) * theta / (12.0*pi));
		x2 = x1;
		y2 = y1;
		
		x1 = xoffset + scalefactor * (3 * cos( theta + rotation) - 3 * cos (3 * theta + rotation));
		y1 = yoffset + scalefactor * (3 * sin( theta + rotation) - 3 * sin (3 * theta + rotation));
		MyWindow.DrawLine(x1, 1024 - y1, x2, 1024 - y2, color);
	}

}


void drawOtherStuff(int xoffset, int yoffset, bool InColor, double scalefactor, double rotation, WindowClass &MyWindow)
{
	static double x1;
	static double y1;
	static double x2;
	static double y2;
	static double theta;
	static double r;
	static double increment = pi / 48;
	static RGBColor color;

	theta = 0.0;
	
	x1 = xoffset + scalefactor * (cos (theta-rotation) + theta * sin(theta+rotation));
	y1 = yoffset + scalefactor * (sin (theta-rotation) - theta * cos(theta+rotation));
	theta += increment;
	color = RGB(0,0,0);
	for (; theta <= 12.0 * pi; theta += increment)
	{
		if (InColor)
			color = RGB(r1 + (r2 - r1) * theta / (12.0*pi),g1 + (g2 - g1) * theta / (12.0*pi),b1 + (b2 - b1) * theta / (12.0*pi));
		x2 = x1;
		y2 = y1;
		x1 = xoffset + scalefactor * (cos (theta-rotation) + theta * sin(theta+rotation));
		y1 = yoffset + scalefactor * (sin (theta-rotation) - theta * cos(theta+rotation));
		MyWindow.DrawLine(x1, 1024 - y1, x2, 1024 - y2, color);
	}

}

int Main()
{
    // Create a full screen window.
    WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, 1);
    if (!MyWindow.WindowIsOpen())
        return 255;

	

    // Now draw the lines.
	int xoffset;
	int yoffset;
	double scalefactor;
	DWORD startTime;
	srand(time(0));
	int b;

	xoffset = 550;
	yoffset = 580;	
	scalefactor = 40.0;
	r1 = 100 + rand() % 150;
	g1 = 100 + rand() % 150;
	b1 = 100 + rand() % 150;
	r2 = 100 + rand() % 150;
	g2 = 100 + rand() % 150;
	b2 = 100 + rand() % 150;

	for ( b = 0; b < 40; b++)
		

		{
			startTime = timeGetTime();
			scalefactor *= 1.01;
			drawStuff(xoffset, yoffset, true, scalefactor, b / 5, MyWindow);
			
			do 
			{
				// Wait for escape to be pressed.
				MyWindow.CheckEscape(); 
				if (!MyWindow.WindowIsOpen())
					return 0;

			}
			while (timeGetTime() - startTime < DELAY * 3);
		}

	for (b = 0; b < 2; b++)
	{
		xoffset = rand() % 750 + 200;
		yoffset = rand() % 500 + 350;	
		scalefactor = 10.0 + rand() % 10;
		r1 = 100 + rand() % 150;
		g1 = 100 + rand() % 150;
		b1 = 100 + rand() % 150;
		r2 = 100 + rand() % 150;
		g2 = 100 + rand() % 150;
		b2 = 100 + rand() % 150;

		for ( int i = 0; i < 20; i++)
			

			{
				startTime = timeGetTime();
				scalefactor *= 1.01;
				drawOtherStuff(xoffset, yoffset, true, scalefactor, i / 4, MyWindow);
				
				do 
				{
					// Wait for escape to be pressed.
					MyWindow.CheckEscape(); 
					if (!MyWindow.WindowIsOpen())
						return 0;

				}
				while (timeGetTime() - startTime < DELAY * 4);
			}
	}

	for (int i = 0; i < 2; i++)
	{
		xoffset = rand() % 750 + 200;
		yoffset = rand() % 500 + 350;	
		scalefactor = 8 + rand() % 5;
		r1 = 100 + rand() % 150;
			g1 = 100 + rand() % 150;
			b1 = 100 + rand() % 150;

			r2 = 100 + rand() % 150;
			g2 = 100 + rand() % 150;
			b2 = 100 + rand() % 150;

		for (b = 0; b < 5; b++)
			{
				startTime = timeGetTime();
				//scalefactor *= 1.01;
				drawDeltoid(xoffset, yoffset, true, scalefactor, b / 2, MyWindow);
				
				do 
				{
					// Wait for escape to be pressed.
					MyWindow.CheckEscape(); 
					if (!MyWindow.WindowIsOpen())
						return 0;

				}
				while (timeGetTime() - startTime < DELAY * 4);
			}
	}

	
	for ( b = 0; b < 4; b++)
	{
		switch (b)
		{
		case 0:{
			xoffset = rand() % 250 + 200;
		yoffset = rand() % 250 + 250;	

			   } break;
		case 2:{
			xoffset = rand() % 250 + 600;
		yoffset = rand() % 250 + 600;	

			   } break;
		case 3:{
			xoffset = rand() % 250 + 600;
		yoffset = rand() % 500 + 250;	

			   } break;
		case 1:{
			xoffset = rand() % 250 + 200;
		yoffset = rand() % 250 + 600;	

			   } break;
		}

		
		scalefactor = 30 + rand() % 30;
		r1 = 100 + rand() % 150;
		g1 = 100 + rand() % 150;
		b1 = 100 + rand() % 150;

		r2 = 100 + rand() % 150;
		g2 = 100 + rand() % 150;
		b2 = 100 + rand() % 150;

		for (int i = 0; i < 10; i++)
		{
			startTime = timeGetTime();
			//drawButterfly(xoffset, yoffset, false, scalefactor, MyWindow);
			drawButterfly(xoffset, yoffset, true, scalefactor, MyWindow);
			xoffset++;
			do 
			{
				// Wait for escape to be pressed.
				MyWindow.CheckEscape(); 
				if (!MyWindow.WindowIsOpen())
					return 0;

			}
			while (timeGetTime() - startTime < DELAY);
		}
		drawButterfly(xoffset, yoffset, false, scalefactor, MyWindow);
	}

	
	

    while (MyWindow.WindowIsOpen())
    {
        // Wait for escape to be pressed.
       MyWindow.CheckEscape(); 
    }

    return 0;
}