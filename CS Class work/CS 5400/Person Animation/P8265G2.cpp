#include "graphics.cpp"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <mmsystem.h>

/*
Symmetric Double Step Line Algorithm
by Brian Wyvill
from "Graphics Gems", Academic Press, 1990

user provides "setpixel()" function for output.
*/

#define swap(a,b)           {a^=b; b^=a; a^=b;}
#define absolute(i,j,k)     ( (i-j)*(k = ( (i-j)<0 ? -1 : 1)))

/* non-zero flag indicates the pixels needing swap back. */
void Plot(int x, int y, int flag, WindowClass &MyWindow, COLORREF color)
{
	if (flag)
		MyWindow.DrawPixel(y, x, color);
	else
		MyWindow.DrawPixel(x, y, color);
}


void DoubleLine(int a1, int b1, int a2, int b2, WindowClass & MyWindow, COLORREF color)
{
	int           dx, dy, incr1, incr2, D, x, y, xend, c, pixels_left;
	int           x1, y1;
	int           sign_x, sign_y, step, reverse, i;

	dx = absolute(a2, a1, sign_x);
	dy = absolute(b2, b1, sign_y);
	/* decide increment sign by the slope sign */
	if (sign_x == sign_y)
		step = 1;
	else
		step = -1;

	if (dy > dx) {		/* chooses axis of greatest movement (make
				 		 * dx) */
		swap(a1, b1);
		swap(a2, b2);
		swap(dx, dy);
		reverse = 1;
	} else
		reverse = 0;
	/* note error check for dx==0 should be included here */
	if (a1 > a2) {		/* start from the smaller coordinate */
		x = a2;
		y = b2;
		x1 = a1;
		y1 = b1;
	} else {
		x = a1;
		y = b1;
		x1 = a2;
		y1 = b2;
	}


	/* Note dx=n implies 0 - n or (dx+1) pixels to be set */
	/* Go round loop dx/4 times then Plot last 0,1,2 or 3 pixels */
	/* In fact (dx-1)/4 as 2 pixels are already Plotted */
	xend = (dx - 1) / 4;
	pixels_left = (dx - 1) % 4;	/* number of pixels left over at the
					 			 * end */
	Plot(x, y, reverse, MyWindow, color);
	if ( pixels_left < 0 ) return ;	/* Plot only one pixel for zero
							* length vectors */
	Plot(x1, y1, reverse, MyWindow, color);	/* Plot first two points */
	incr2 = 4 * dy - 2 * dx;
	if (incr2 < 0) {	/* slope less than 1/2 */
		c = 2 * dy;
		incr1 = 2 * c;
		D = incr1 - dx;

		for (i = 0; i < xend; i++) {	/* Plotting loop */
			++x;
			--x1;
			if (D < 0) {
                  			/* pattern 1 forwards */
				Plot(x, y, reverse, MyWindow, color);
				Plot(++x, y, reverse, MyWindow, color);
                                /* pattern 1 backwards */
				Plot(x1, y1, reverse, MyWindow, color);
				Plot(--x1, y1, reverse, MyWindow, color);
				D += incr1;
			} else {
				if (D < c) {
					/* pattern 2 forwards */
					Plot(x, y, reverse, MyWindow, color);
					Plot(++x, y += step, reverse, MyWindow, color);
					/* pattern 2 backwards */
					Plot(x1, y1, reverse, MyWindow, color);
					Plot(--x1, y1 -= step, reverse, MyWindow, color);	
				} else {
				        /* pattern 3 forwards */
					Plot(x, y += step, reverse, MyWindow, color);
					Plot(++x, y, reverse, MyWindow, color);
					/* pattern 3 backwards */
					Plot(x1, y1 -= step, reverse, MyWindow, color);
					Plot(--x1, y1, reverse, MyWindow, color);
				}
				D += incr2;
			}
		}		/* end for */

		/* Plot last pattern */
		if (pixels_left) {
			if (D < 0) {
				Plot(++x, y, reverse, MyWindow, color);	/* pattern 1 */
				if (pixels_left > 1)
					Plot(++x, y, reverse, MyWindow, color);
				if (pixels_left > 2)
					Plot(--x1, y1, reverse, MyWindow, color);
			} else {
				if (D < c) {
					Plot(++x, y, reverse, MyWindow, color);	/* pattern 2  */
					if (pixels_left > 1){
						y += step;
						Plot(++x, y, reverse, MyWindow, color);
					}
					if (pixels_left > 2)
						Plot(--x1, y1, reverse, MyWindow, color);
				} else {
				  /* pattern 3 */
					y += step;
					Plot(++x, y, reverse, MyWindow, color);
					if (pixels_left > 1)
						Plot(++x, y, reverse, MyWindow, color);
					if (pixels_left > 2)
						Plot(--x1, y1 -= step, reverse, MyWindow, color);
				}
			}
		}		/* end if pixels_left */
	}
	/* end slope < 1/2 */
	else {			/* slope greater than 1/2 */
		c = 2 * (dy - dx);
		incr1 = 2 * c;
		D = incr1 + dx;
		for (i = 0; i < xend; i++) {
			++x;
			--x1;
			if (D > 0) {
			  /* pattern 4 forwards */
				Plot(x, y += step, reverse, MyWindow, color);
				Plot(++x, y += step, reverse, MyWindow, color);
			  /* pattern 4 backwards */
				Plot(x1, y1 -= step, reverse, MyWindow, color);
				Plot(--x1, y1 -= step, reverse, MyWindow, color);
				D += incr1;
			} else {
				if (D < c) {
				  /* pattern 2 forwards */
					Plot(x, y, reverse, MyWindow, color);
					Plot(++x, y += step, reverse, MyWindow, color);

 				  /* pattern 2 backwards */
					Plot(x1, y1, reverse, MyWindow, color);
					Plot(--x1, y1 -= step, reverse, MyWindow, color);
				} else {
				  /* pattern 3 forwards */
					Plot(x, y += step, reverse, MyWindow, color);
					Plot(++x, y, reverse, MyWindow, color);
				  /* pattern 3 backwards */
					Plot(x1, y1 -= step, reverse, MyWindow, color);
					Plot(--x1, y1, reverse, MyWindow, color);
				}
				D += incr2;
			}
		}		/* end for */
		/* Plot last pattern */
		if (pixels_left) {
			if (D > 0) {
				Plot(++x, y += step, reverse, MyWindow, color);	/* pattern 4 */
				if (pixels_left > 1)
					Plot(++x, y += step, reverse, MyWindow, color);
				if (pixels_left > 2)
					Plot(--x1, y1 -= step, reverse, MyWindow, color);
			} else {
				if (D < c) {
					Plot(++x, y, reverse, MyWindow, color);	/* pattern 2  */
					if (pixels_left > 1)
						Plot(++x, y += step, reverse, MyWindow, color);
					if (pixels_left > 2)
						Plot(--x1, y1, reverse, MyWindow, color);
				} else {
				  /* pattern 3 */
					Plot(++x, y += step, reverse, MyWindow, color);
					if (pixels_left > 1)
						Plot(++x, y, reverse, MyWindow, color);
					if (pixels_left > 2) {
						if (D > c) /* step 3 */
						   Plot(--x1, y1 -= step, reverse, MyWindow, color);
						else /* step 2 */
							Plot(--x1, y1, reverse, MyWindow, color);
                         		}
				}
			}
		}
	}
}

int ymax;
int xmax;
double pi = 3.1415916;

void Pause(WindowClass &MyWindow)
{
	MSG m;
	GetMessage(&m, MyWindow.hwnd, WM_KEYFIRST, WM_KEYLAST );
}

void MyLine(int x1, int y1, int x2, int y2, WindowClass &MyWindow, COLORREF color)
{
	
	int dy = y2 - y1;
	int dx = x2 - x1;


	int baseStep = dx / dy;
	//if (baseStep > maxBaseStep)
	//	maxBaseStep = baseStep;
	int nExtraSteps = dx % dy;
	//int whichLine = dy / nExtraSteps + 1;

	//if (nExtraSetps == 0)
	for (;y1 <= y2; y1++)
	{
		for (int i = 0; i < baseStep; i++)
			MyWindow.DrawPixel(x1++,y1, color);
		
		if (y1 * nExtraSteps % dy < nExtraSteps) // y1 % whichLine
			MyWindow.DrawPixel(x1++,y1, color);
	}
}

void BLine(int x1, int y1, int x2, int y2, WindowClass &MyWindow, COLORREF color)
{
	if (fabs(x2 - x1) > fabs(y2 - y1))
	{
		if (x2 < x1)
		{
			int ytemp = y1;
			int xtemp = x1;
			x1 = x2;
			y1 = y2;
			x2 = xtemp;
			y2 = ytemp;
		}
		
		int increment = 1;
		int dx = x2 - x1;
		int dy = y2 - y1;		
		
		if (dy < 0){
			dy *= -1;
			increment = -1;
		}	
		int twoDyDx = 2 * (dy - dx);
		int twoDy = 2 * dy;
		int di = 2 * dy - dx;
		MyWindow.DrawPixel(x1++, ymax-y1, color);

		for (; x1 < x2; x1++)
		{
			if (di >= 0){
				y1+=increment;
				di += twoDyDx;
			}
			else 
				di += twoDy;

			MyWindow.DrawPixel(x1, ymax-y1, color);
		}
	}
	else
	{
		if (y2 < y1)
		{
			int ytemp = y1;
			int xtemp = x1;
			x1 = x2;
			y1 = y2;
			x2 = xtemp;
			y2 = ytemp;
		}

		int increment = 1;
		int dx = x2 - x1;
		int dy = y2 - y1;
		
		if (dx < 0){
			dx *= -1;
			increment = -1;
		}

		int di = 2 * dx - dy;
		int twoDxDy = 2 * (dx - dy);
		int twoDx = 2 * dx;
	
		MyWindow.DrawPixel(x1, ymax-y1++, color);

		for (; y1 < y2; y1++)
		{
			if (di >= 0){
				x1+=increment;
				di += twoDxDy;
			}
			else 
				di += twoDx;

			MyWindow.DrawPixel(x1, ymax-y1, color);
		}
	}
}

void ellipseMidpoint (int xCenter, int yCenter, int Rx, int Ry, WindowClass &MyWindow, COLORREF color)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;
	void ellipsePlotPoints (int, int, int, int, WindowClass &, COLORREF);

	ellipsePlotPoints (xCenter, yCenter, x, y, MyWindow, color);
	
	/*Region 1*/
	
	p = (int)(Ry2 - Rx2 * Ry + 0.25 * Rx2 + .5);
	while (px < py)
	{
		px += twoRy2;
		x++;
		if (p < 0)
			p += Ry2 + px;
		else
		{
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		
		ellipsePlotPoints(xCenter, yCenter, x, y, MyWindow, color);
	}

	p = (int)(Ry2 * ( x * x + x + .25 ) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2 + 0.5);
	while ( y > 0 )
	{
		y--;
		py -= twoRx2;
		if (p > 0)
			p += Rx2 - py;
		else
		{
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y, MyWindow, color);
	}
}

void ellipsePlotPoints (int xCenter, int yCenter, int x, int y, WindowClass &MyWindow, COLORREF color)
{
	MyWindow.DrawPixel(xCenter + x, yCenter + y, color);
	MyWindow.DrawPixel(xCenter - x, yCenter + y, color);
	MyWindow.DrawPixel(xCenter + x, yCenter - y, color);
	MyWindow.DrawPixel(xCenter - x, yCenter - y, color);
}

void DrawObject(int xCenter, int yCenter, int Size, WindowClass &MyWindow, COLORREF color)
{
	ellipseMidpoint (xCenter, yCenter, Size, Size, MyWindow, color);	
	
}

double Distance(double xdist, double ydist)
{
	return sqrt(xdist * xdist + ydist * ydist);
}

void PolyLine(int xOff, int yOff, int x[], int y[], int n, COLORREF color, WindowClass &MyWindow)
{
	for (int i = 1; i < n; i++)
		BLine(xOff + x[i-1], yOff + y[i-1], xOff + x[i], yOff + y[i],MyWindow,color);
}

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

	int xOffSet = 120;
	int yOffSet = 10;

	PolyLine(xOffSet,yOffSet,manX,manY,45,RGB(255,0,0),MyWindow);
	PolyLine(xOffSet + 200 ,yOffSet,wManX,wManY,45,RGB(255,0,0),MyWindow);
	*/
// u = 53
	
	srand(44);
	DWORD time[2];

	for (int whichAlgorithm = 0; whichAlgorithm < 2  && MyWindow.WindowIsOpen(); whichAlgorithm++)
	{
		DWORD startTime = timeGetTime();

		for (int legs = 4; legs < 7 && MyWindow.WindowIsOpen(); legs++)
		{
			double degreeStep = 360 / legs;
			int positions = 30;

			double *LegX = new double[legs];
			double *LegY = new double[legs];
			int size = 200;
			
			for (int i = 0 ; i < legs; i++)
			{
				double degreePosition = (360 * i / legs + 90) % 360;
				LegX[i] = cos(degreePosition * pi / 180);
				LegY[i] = sin(degreePosition * pi / 180);
			}

			int x1, y1, y2, y3, x2, x3;
			int xoff = rand() % (xmax - size * 2) + size;
			int yoff = rand() % (ymax - size * 2) + size;

			switch (legs){
			case 4:{
				xoff = 200;
				yoff = 200;
				}break;
			case 5:{
				xoff = xmax - 200;
				yoff = ymax - 200;
				}break;
			case 6:{
				xoff = xmax / 2;
				yoff = ymax / 2;
				}break;
			}

			color = RGB(rand() % 255,rand() % 255,rand() % 255);
			x1 = xoff;
			y1 = yoff;
			
			int r1 = 50 + rand() % 200;
			int r2 = 50 + rand() % 200;
			int g1 = 50 + rand() % 200;
			int g2 = 50 + rand() % 200;
			int b1 = 50 + rand() % 200;
			int b2 = 50 + rand() % 200;
			
			for (i = 0; i < legs; i++)
			{
				x2 = xoff + LegX[i] * size; 			
				y2 = yoff + LegY[i] * size;
				if (whichAlgorithm)
					DoubleLine(x1,y1,x2,y2,MyWindow,RGB(r1,g1,b1));
				else
					BLine(x1,y1,x2,y2,MyWindow,RGB(r1,g1,b1));
			}

			for (int p = 0; p < positions && MyWindow.WindowIsOpen(); p++)
			{
				int curLeg = 0;
				while (MyWindow.WindowIsOpen())
				{
					COLORREF color1 = RGB((r2-r1) * (p+1) / positions +r1,
										  (g2-g1) * (p+1) / positions +g1,
										  (b2-b1) * (p+1) / positions +b1);
					COLORREF color2 = RGB((r1-r2) * (p+1) / positions +r2,
										  (g1-g2) * (p+1) / positions +g2,
										  (r1-r2) * (p+1) / positions +b2);

					x1 = xoff + LegX[curLeg % legs] * (positions - p) / positions * size; 			
					y1 = yoff + LegY[curLeg % legs] * (positions - p) / positions * size; 			
					x2 = xoff + LegX[(curLeg + 1) % legs] * (p + 1) / positions * size; 			
					y2 = yoff + LegY[(curLeg + 1) % legs] * (p + 1) / positions * size;
					x3 = xoff + LegX[(curLeg + 2) % legs] * (positions - p) / positions * size; 			
					y3 = yoff + LegY[(curLeg + 2) % legs] * (positions - p) / positions * size;
					if (whichAlgorithm)
					{
						DoubleLine(x1,y1,x2,y2,MyWindow,color1);
						DoubleLine(x2,y2,x3,y3,MyWindow,color2);
					}
					else
					{
						BLine(x1,y1,x2,y2,MyWindow,color1);
						BLine(x2,y2,x3,y3,MyWindow,color2);
					}
					
					curLeg += 2;
					if (curLeg == legs)
						break;
					else 
						curLeg %= legs;
					MyWindow.CheckEscape();
				}
			}
			delete [] LegX;
			delete [] LegY;
		}
		time[whichAlgorithm] = timeGetTime() - startTime;
	}
	//MyWindow.ClearWindow();
	char text[100];
	wsprintf(text, "Time required for Bresenham algorithm: %i \n"
			       "Time required for Symmetric Double-Step: %i ",time[0],time[1]);

	MessageBox(NULL,text,"Time Required for Two Line Algorithms",MB_ICONINFORMATION);
	
	MyWindow.ClearWindow();

	int counter = 0;
		
	while ( MyWindow.WindowIsOpen())
	{
		int xCenter = rand() % (xmax - 200) + 100;
		int yCenter = rand() % (ymax - 200) + 100;
		int ellipseSizeA = rand() % 50 + 20;
		int ellipseSizeB = rand() % 50 + 20;
		
		int nSteps = (ellipseSizeA > ellipseSizeB ? ellipseSizeA : ellipseSizeB);
		int Rx;
		int Ry;
		
		int r1 = rand() % 200 + 50;
		int r2 = rand() % 200 + 50;
		int g1 = rand() % 100 + 50;
		int g2 = rand() % 100 + 50;
		int b1 = rand() % 200 + 50;
		int b2 = rand() % 200 + 50;
		for (int i = 0; i < nSteps; i++)
		{
			counter++;
			Rx = ellipseSizeA * i / (nSteps-1);
			Ry = ellipseSizeB * i / (nSteps-1);
			
			ellipseMidpoint (xCenter, yCenter, Rx, Ry, MyWindow, 
				RGB(r1 + (r2 - r1) * sin(i * pi/ (nSteps - 1) ),
					g1 + (g2 - g1) * sin(i * pi/ (nSteps - 1) ),
					b1 + (b2 - b1) * sin(i * pi/ (nSteps - 1) )));
			ellipseMidpoint (xCenter, yCenter+1, Rx, Ry, MyWindow, 
				RGB(r1 + (r2 - r1) * sin(i * pi/ (nSteps - 1) ),
					g1 + (g2 - g1) * sin(i * pi/ (nSteps - 1) ),
					b1 + (b2 - b1) * sin(i * pi/ (nSteps - 1) )));
		}
		MyWindow.CheckEscape();
	}

	while (MyWindow.WindowIsOpen())
    {
		// Wait for escape to be pressed.
        MyWindow.CheckEscape();
    }
    return 0;
}
