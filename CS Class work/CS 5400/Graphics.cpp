// This library is meant to create a window and allow the programmer to draw to it in 24-bit color.

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>

// for my add-ins
#include "GraphicObject.h"
#include <math.h>
#include <string.h>


// Name of window.
#define NAME "Graphics Window"
#define TITLE "** Graphics Window **"

// Options for opening a window.
#define NORMAL_WINDOW 0
#define FULL_SCREEN 1
#define DOUBLE_BUFFER 2

typedef long int RGBColor;

// *** Prototypes.  Main() is the function the user will provide.
long FAR PASCAL WindowProc( HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam );
int Main();


// *** Here are the few global variables I use.
HINSTANCE gb_hInstance;
BOOL gb_bActive;
int gb_nCmdShow;

HWND last_win_closed = 0;

//____________________________________________________________________________________
//________________________ Class Declarations for my graphics stuff __________________

extern int ymax;
class Vector3d;
class FourSquareMatrix;

FourSquareMatrix GetTranslationMatrix (double tx, double ty, double tz, double xShift, double yShift, double zShift);

class Vector3d 
{
public:
	COLORREF LineColor;
	bool LineTo;
	Vector3d();
	Vector3d(double x, double y, double z, double = 1.0);
	void UpdateVector(); // this is provided in order to provide compatibility with 
						 // a derived class, class NonConstVector
	inline void SetVector(double x1 = 0.0, double y1 = 0.0, double z1 = 0.0, double w1 = 1.0)
	{
		x = x1;
		y = y1;
		z = z1;
		w = w1;
	}
	double x;
	double y;
	double z;
	double w;
protected:

};

class FourSquareMatrix
{
public:
	FourSquareMatrix(double = 0.0, double = 0.0, double = 0.0, double = 0.0, 
					 double = 0.0, double = 0.0, double = 0.0, double = 0.0, 
					 double = 0.0, double = 0.0, double = 0.0, double = 0.0,
					 double = 0.0, double = 0.0, double = 0.0, double = 0.0);
	FourSquareMatrix(double [][4]);
	
	void CreateRotationTranslationMatrix (double tx, double ty, double tz, double xShift, double yShift, double zShift);
	Vector3d MatrixMultiply(Vector3d &Point);
public:
	inline Vector3d RotationDropZ(Vector3d &point);
	
	double Matrix[4][4];
};


/*
class NonConstVector : public Vector3d {
public:
	NonConstVector();
	void NonConstVector(Func1Type * xValFunc, Func1Type * yValFunc, Func1Type * zValFunc);
	void UpdateVector();
protected:

}

class 3dObject {
public:
	3dObject();
	3dObject(Vector3d InitPosition, Vector3d *ptrVelocityObject,  
	~3dObject();

	void UpdatePosition();
	void UpdateRotationPosition();
	void ChangeObjectCenter();
	void SetObjectPoints(Vector3d *ObjectPoints, int nPoints);
	void ChangeVelocityObject(Vector3d *ptrNewVelocity);
	// this could be used if you wanted to split an object in half and have one half move
	// independent of the other half, or conversely, if you wanted to join two objects together.
	// You could do some neat things with physics.  If two objects get close enough, then they 
	// combine and their masses increase.  The resulting collision changes the resultant velocity
	// of the new object.  You would use it in conjunction with ChangeObjectCenter and 


	Vector3d Position;
	Vector3d *Velocity; // this is a ptr because it could be a NonConstVector
	Vector3d ObjectCenter; // by default this is 0,0,0 
	Vector3d RotationPosition;
	Vector3d *RotationVelocity; // this is a ptr because it could be a NonConstVector
	Vector3d *ObjectPoints;
	int		nPoints;
protected:

};

class World {
	friend class Vector3d;
public:
	Vector3d ViewPoint;
	Vector3d ViewDirection;
	

protected:
	int time;

}
*/

// graphicobject.cpp
//#include <string.h>
//#include <math.h>

Vector3d::Vector3d()
{

}

Vector3d::Vector3d(double x1, double y1, double z1, double w1) // = 1.0
{
	x = x1;
	y = y1;
	z = z1;
	w = w1;
}

void Vector3d::UpdateVector()
{ // this is provided in order to provide compatibility with 
  // a derived class, class NonConstVector

}

FourSquareMatrix::FourSquareMatrix(double a11, double a12, double a13, double a14, 
				 double a21, double a22, double a23, double a24, 
				 double a31, double a32, double a33, double a34,
				 double a41, double a42, double a43, double a44)
{
	Matrix[0][0] = a11;
	Matrix[0][1] = a12;
	Matrix[0][2] = a13;
	Matrix[0][3] = a14;
	Matrix[1][0] = a21;
	Matrix[1][1] = a22;
	Matrix[1][2] = a23;
	Matrix[1][3] = a24;
	Matrix[2][0] = a31;
	Matrix[2][1] = a32;
	Matrix[2][2] = a33;
	Matrix[2][3] = a34;
	Matrix[3][0] = a41;
	Matrix[3][1] = a42;
	Matrix[3][2] = a43;
	Matrix[3][3] = a44;
}

FourSquareMatrix::FourSquareMatrix(double M[][4])
{
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//		Matrix[i][j] = 
	//}
	memcpy(Matrix,M,sizeof (double) * 16);
}

Vector3d FourSquareMatrix::MatrixMultiply(Vector3d &Point)
{
	double row1 = Matrix[0][0] * Point.x + 
				  Matrix[0][1] * Point.y + 
				  Matrix[0][2] * Point.z + 
				  Matrix[0][3] * Point.w;
	double row2 = Matrix[1][0] * Point.x + 
				  Matrix[1][1] * Point.y + 
				  Matrix[1][2] * Point.z + 
				  Matrix[1][3] * Point.w;
	double row3 = Matrix[2][0] * Point.x + 
				  Matrix[2][1] * Point.y + 
				  Matrix[2][2] * Point.z + 
				  Matrix[2][3] * Point.w;
	//double row4 = Matrix[3][0] * Point.x + 
	//			  Matrix[3][1] * Point.y + 
	//			  Matrix[3][2] * Point.z + 
	//			  Matrix[3][3] * Point.w;

	return Vector3d(row1, row2, row3);

}

void FourSquareMatrix::CreateRotationTranslationMatrix (double tx, double ty, double tz, double xShift, double yShift, double zShift)
{
	double cos1 = cos(tz);
	double cos2 = cos(tx);
	double cos3 = cos(ty);
	double sin1 = sin(tz);
	double sin2 = sin(tx);
	double sin3 = sin(ty);
	
	Matrix[0][0] = cos1 * cos3 - sin1 * sin2 * sin3;
	Matrix[0][1] = -sin1 * cos2;
	Matrix[0][2] = cos1 * sin3 + sin1 * sin2 * cos3;
	Matrix[0][3] = xShift;
	Matrix[1][0] = sin1 * cos3 + cos1 * sin2 * sin3;
	Matrix[1][1] = cos1 * cos2;
	Matrix[1][2] = sin1 * sin3 - cos3 * cos1 * sin2;
	Matrix[1][3] = yShift;
	Matrix[2][0] = -cos2*sin3;
	Matrix[2][1] = sin2;
	Matrix[2][2] = cos2*cos3;
	Matrix[2][3] = zShift;
	Matrix[3][0] = 0;
	Matrix[3][1] = 0;
	Matrix[3][2] = 0;
	Matrix[3][3] = 1.0;
}

Vector3d FourSquareMatrix::RotationDropZ(Vector3d &point)
{
	return Vector3d(point.x * Matrix[0][0] + point.y * Matrix[0][1] + point.z * Matrix[0][2],
            point.x * Matrix[1][0] + point.y * Matrix[1][1] + point.z * Matrix[1][2],
			point.x * Matrix[2][0] + point.y * Matrix[2][1] + point.z * Matrix[2][2]);
}


/*------------------------------------------------------------------
Class WindowClass - declaration
Encapsulates open and closing, as well as basic drawing stuff.
--------------------------------------------------------------------*/

class WindowClass
{
	public:
        HWND hwnd;             // Window handle.
		HDC hdc;
		unsigned int Width;
        unsigned int Height;
	private:
		BOOL IsOpen;
        BOOL DoubleBuffer;
        HPEN defaultpen;
        HPEN scratchpen;
        HBRUSH scratchbrush;
        
        HDC frontbuff;         // HDC for front buffer (window).
        HDC backbuff;          // HDC for back buffer.
        HBITMAP bitmap;        // Bitmap (backbuffer) handle.
        unsigned char *buffer; // Direct access to back buffer.


    public:
        WindowClass();
        WindowClass(unsigned int width, unsigned int height, unsigned int pos_x, unsigned int pos_y, int options);
        ~WindowClass();

        void OpenWindow(unsigned int width, unsigned int height, unsigned int pos_x, unsigned int pos_y, int options);
        void CloseWindow();

        inline BOOL WindowIsOpen()
        {
            return IsOpen;
        }

        inline void DrawPixel(int x, int y, RGBColor color);
        inline void DrawLine(int x1, int y1, int x2, int y2, RGBColor color);
        inline void DrawPixel(int x, int y);
        inline void DrawLine(int x1, int y1, int x2, int y2);
        inline void DrawPoly(int x1, int y1, int x2, int y2, int x3, int y3, RGBColor color);
        inline void SetDefaultColor(RGBColor color);
		
		// my add-in functions
		inline void MoveTo(int x, int y);
		inline void DrawTo(int x, int y);
		inline void SetPen(COLORREF color);
		void ProjectPoints(double xOff, double yOff, double zOff, int P[][2], int nList, double points[][3], int nPoints, Vector3d V, Vector3d C, double viewDist);
        
		inline unsigned int GetWidth()
        {
            return Width;
        }
        inline unsigned int GetHeight()
        {
            return Height;
        }

        inline void ClearWindow();
        inline void ClearWindow(RGBColor color);
        inline void CheckEscape();
        inline void SwapBuffers();
};


/*------------------------------------------------------------------
Class WindowClass - Implementation
Shows some basic DirectDraw features
--------------------------------------------------------------------*/

WindowClass::WindowClass()
{
    IsOpen = FALSE;
    defaultpen = NULL;
    hdc = NULL;
    frontbuff = NULL;
    backbuff = NULL;
    buffer = NULL;
    scratchpen = CreatePen(PS_SOLID, 0, RGB(0,0,0));
    scratchbrush = CreateSolidBrush(RGB(0, 0, 0));
}


WindowClass::WindowClass(unsigned int width, unsigned int height, unsigned int pos_x, unsigned int pos_y, int options)
{
    IsOpen = FALSE;
    defaultpen = NULL;
    hdc = NULL;
    frontbuff = NULL;
    backbuff = NULL;
    buffer = NULL;
    scratchpen = CreatePen(PS_SOLID, 0, RGB(0,0,0));
    scratchbrush = CreateSolidBrush(RGB(0, 0, 0));

    OpenWindow(width, height, pos_x, pos_y, options);
}


WindowClass::~WindowClass()
{
    CloseWindow();
}


void WindowClass::OpenWindow(unsigned int width, unsigned int height, unsigned int pos_x, unsigned int pos_y, int options)
{
    if (IsOpen == TRUE)
        return;

    IsOpen = FALSE;

    WNDCLASS wc;

    // Create the Window class and the Window ...
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = gb_hInstance;
    wc.hIcon = LoadIcon( gb_hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;

    // This copies the window struct, ready to create the window.
    if(!RegisterClass( &wc ))
        return;

    DWORD exStyle = 0;
    //DWORD style = WS_CAPTION | WS_POPUP;    // This one for a border around the window.
    DWORD style = WS_POPUP;       // This one for no border.

    if (options & FULL_SCREEN)
    {
        hwnd = CreateWindowEx(exStyle,NAME,TITLE,style,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),NULL,NULL, gb_hInstance,NULL );
        if( !hwnd ) return;

        Width = GetSystemMetrics(SM_CXSCREEN);
        Height = GetSystemMetrics(SM_CYSCREEN);
    }
    else
    {
        hwnd = CreateWindowEx(exStyle,NAME,TITLE,style,pos_x,pos_y,width,height,NULL,NULL, gb_hInstance,NULL );
        if( !hwnd ) return;

        Width = width;
        Height = height;
    }

    frontbuff = GetDC(hwnd);

    // Now that we have our window, create back buffer.
    if (options & DOUBLE_BUFFER)
    {
        DoubleBuffer = TRUE;

        int depth = GetDeviceCaps(frontbuff, BITSPIXEL);

        BITMAPINFOHEADER bmih;
        memset(&bmih, 0, sizeof(BITMAPINFOHEADER));
        bmih.biSize = sizeof(BITMAPINFOHEADER);
        bmih.biWidth = Width;
        bmih.biHeight = Height;
        bmih.biPlanes = 1;
        bmih.biBitCount = depth;
        bmih.biCompression = BI_RGB;
        bmih.biSizeImage = Width * (depth / 8) * Height;

        backbuff = CreateCompatibleDC(NULL);
        bitmap = CreateDIBSection(backbuff, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS, (LPVOID *)&buffer, NULL, (DWORD)0);
        if (bitmap == NULL){
			MessageBox(NULL,"Not enough memory for double buffering.","Error",MB_OK);
			DoubleBuffer = FALSE;
			hdc = frontbuff;
		}
		else
		{
			SelectObject(backbuff, bitmap);
			hdc = backbuff;
		}
    }
	else
    {
        DoubleBuffer = FALSE;
        hdc = frontbuff;
    }

    // These make sure the window is visible, refreshed and active.
    ShowWindow(hwnd, gb_nCmdShow);
    UpdateWindow(hwnd);
    SetFocus(hwnd);

    IsOpen = TRUE;
}


void WindowClass::CloseWindow()
{
    if (IsOpen == TRUE)
    {
        PostMessage(hwnd, WM_CLOSE, 0, 0);
        IsOpen = FALSE;

        MSG msg;

        while (PeekMessage(&msg, hwnd, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
            {
                exit(0);
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}



/*-------------------------------------------------------------------
DrawPoly()

This function takes three points and draws a filled polygon of the
specified color.
---------------------------------------------------------------------*/

void WindowClass::DrawPoly(int x1, int y1, int x2, int y2, int x3, int y3, RGBColor color)
{
    static POINT pointlist[3];

    HPEN mypen = CreatePen(PS_SOLID, 0, color);
    SelectObject(hdc, mypen);

    HBRUSH mybrush = CreateSolidBrush(color);
    SelectObject(hdc, mybrush);

    pointlist[0].x = x1;
    pointlist[0].y = y1;
    pointlist[1].x = x2;
    pointlist[1].y = y2;
    pointlist[2].x = x3;
    pointlist[2].y = y3;

    Polygon(hdc, pointlist, 3);

    SelectObject(hdc, scratchpen);
    DeleteObject(mypen);

    SelectObject(hdc, scratchbrush);
    DeleteObject(mybrush);
}


/*-------------------------------------------------------------------
DrawPixel()

The bottom 3 bytes of parameter "color" (a long int) are used as the red, green,
and blue values for the color to be drawn.
---------------------------------------------------------------------*/

void WindowClass::DrawPixel(int x, int y, RGBColor color)
{
    MoveToEx(hdc, x, y, 0);

    HPEN mypen = CreatePen(PS_SOLID, 0, color);
    SelectObject(hdc, mypen);

    LineTo(hdc, x+1, y);      // Single pixel line.

    SelectObject(hdc, scratchpen);
    DeleteObject(mypen);
}
 

/*-------------------------------------------------------------------
DrawLine()
---------------------------------------------------------------------*/

void WindowClass::DrawLine(int x1, int y1, int x2, int y2, RGBColor color)
{
    MoveToEx(hdc, x1, y1, 0);

    HPEN mypen = CreatePen(PS_SOLID, 0, color);
    SelectObject(hdc, mypen);

    LineTo(hdc, x2, y2);

    SelectObject(hdc, scratchpen);
    DeleteObject(mypen);
}


/*-------------------------------------------------------------------
DrawPixel() - 2

With this draw function, we use the default color, speeding up drawing.
---------------------------------------------------------------------*/

void WindowClass::DrawPixel(int x, int y)
{
    MoveToEx(hdc, x, y, 0);
    LineTo(hdc, x+1, y);      // Single pixel line.
}


/*-------------------------------------------------------------------
DrawLine() - 2

With this drawline function, we use the default color.  Speed!
---------------------------------------------------------------------*/

void WindowClass::DrawLine(int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, 0);
    LineTo(hdc, x2, y2);
}

/*-------------------------------------------------------------------
My add-in functions.  More speed!
---------------------------------------------------------------------*/

void WindowClass::MoveTo(int x, int y)
{
	MoveToEx(hdc, x, y, 0);
}

void WindowClass::DrawTo(int x, int y)
{
	LineTo(hdc, x, y);
}

void WindowClass::SetPen(COLORREF color)
{
	HPEN mypen = CreatePen(PS_SOLID, 0, color);
    DeleteObject(SelectObject(hdc, mypen)); // selects a new pen and deletes the old.
}

/*-------------------------------------------------------------------
ClearWindow()
---------------------------------------------------------------------*/

void WindowClass::ClearWindow()
{
    BitBlt(hdc, 0, 0, Width, Height, NULL, 0, 0, BLACKNESS);
}


/*-------------------------------------------------------------------
ClearWindow() - 2
---------------------------------------------------------------------*/

void WindowClass::ClearWindow(RGBColor color)
{
    HBRUSH mybrush = CreateSolidBrush(color);
	HRGN hrgn = CreateRectRgn(0, 0, Width, Height);

	FillRgn(hdc, hrgn, mybrush);

    DeleteObject(mybrush);
	DeleteObject(hrgn);
}


/*-------------------------------------------------------------------
SwapBuffers()
---------------------------------------------------------------------*/

void WindowClass::SwapBuffers()
{
	if (DoubleBuffer)
		BitBlt(frontbuff, 0, 0, Width, Height, backbuff, 0, 0, SRCCOPY);
}


/*-------------------------------------------------------------------
CheckEscape()

If called, this function processes any messages from
the OS and kills the program if escape has been pressed.
---------------------------------------------------------------------*/

void WindowClass::CheckEscape()
{
    if (!IsOpen)
    return;

    MSG msg;

    if (PeekMessage(&msg, hwnd, 0, 0, PM_NOREMOVE))
    {
        if (!GetMessage(&msg, NULL, 0, 0))    // We have received a message to quit the program.
        {
            exit(0);
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if ((last_win_closed == hwnd) && (IsOpen == TRUE))
        IsOpen = FALSE;
}


void WindowClass::SetDefaultColor(RGBColor color)
{
    if (defaultpen != NULL)
    {
        SelectObject(hdc, scratchpen);  // We cannot delete pen while it's being used.
        DeleteObject(defaultpen);
    }
    defaultpen = CreatePen(PS_SOLID, 0, color);
    SelectObject(hdc, defaultpen);
}


/*-------------------------------------------------------------------
WindowProc -
Window procedure used by the Window created in WindowClass::Start()
---------------------------------------------------------------------*/

long FAR PASCAL WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_ACTIVATEAPP : gb_bActive = wParam;
                              break;
        case WM_SETCURSOR : SetCursor(NULL);    // To not clear mouse pointer, remove this.
                            return TRUE;
        case WM_CREATE : break;
        case WM_KEYDOWN: switch(wParam)
                         {
                             case VK_ESCAPE:
                             case VK_F12:
                                 PostMessage(hWnd, WM_CLOSE, 0, 0);
                                 last_win_closed = hWnd;
                                 break;
                         }
                         break;
	 case WM_DESTROY: PostQuitMessage(0);
                      //exit(0);
                      break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


/*-------------------------------------------------------------------
WinMain
---------------------------------------------------------------------*/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE prev_instance, LPSTR command_line, int nCmdShow)
{
    gb_hInstance = hInstance;
    gb_nCmdShow = nCmdShow;

    Main();

    return 0;
}

void WindowClass::ProjectPoints()
{
	// calculate sin and cos for rotations...
	static double dx, dy, dz, tx, ty, tz;
	static double l, l2, sin1, cos1, sin2, cos2;

	dx = cx - vx;
	dy = cy - vy;
	dz = cz - vz;

	l = sqrt(dx * dx + dz * dz);
	if (l > 0)
	{
		sin1 = dx / l;
		cos1 = dz / l;
	}
	else
	{
		sin1 = 0.0;
		cos1 = 0.0;
	}

	l2 = sqrt(l * l + dy * dy);
	if (l2 > 0)
	{
		sin2 = dy / l2;
		cos2 = l / l2;
	}
	else
	{
		sin2 = 0.0;
		cos2 = 0.0;
	}

	for (int i = 1; i <= nPoints; i++)
	{
		// Perform transformations...
		tx = points[i][0] + xOff;
		ty = points[i][1] + yOff;
		tz = points[i][2] + zOff;

		x = tx * cos1 - tz * sin1;
		y = -sin1 * sin2 * tx + cos2 * ty - sin2 * cos1 * tz;
		z = sin1 * cos2 * tx + sin2 * ty + cos1 * cos2 * tz;

		d = 
	}

void WindowClass::ProjectPoints(double xOff, double yOff, double zOff, int P[][2], int nList, double points[][3], int nPoints, Vector3d V, Vector3d C, double viewDist)
{
	//static Vector3d Plane[100];
	//static Vector3d Screen[100];
	static int screenX[100];
	static int screenY[100];

	double vx = V.x, vy = V.y, vz = V.z;
	double cx = C.x, cy = C.y, cz = C.z;

	double dx = cx - vx;
	double dy = cy - vy;
	double dz = cz - vz;
	
	double dist = sqrt(dx * dx + dy * dy + dz * dz);
	double t = viewDist / dist;
	double xp = vx + dx * t;
	double yp = vy + dy * t;
	double zp = vz + dz * t;

	double d = dx * xp + dy * yp + dz * zp;

	// now I have the equation of the viewplane
	// I can find the projected locations of all points in this plane.
	double pDx, pDy, pDz;
	double sin1, cos1, sin2, cos2;
	double vxzdist = sqrt(xp * xp + zp * zp);
	if (vxzdist > 0) 
		sin1 = xp / vxzdist;
	else
		sin1 = 0.0;
	if (vxzdist > 0)
		cos1 = zp / vxzdist;
	else
		cos1 = 0;
	
	Vector3d ScreenCenter;// = RotationMatrix.RotationDropZ(Vector3d(xp,yp,zp));
	double txp = xp;
	xp = (xp) * cos1 - (zp) * sin1;
	zp = (txp) * sin1 + (zp) * cos1;
	
	double vyzdist = sqrt(yp * yp + zp * zp);
	
	if (vyzdist > 0)
		sin2 = yp / vyzdist;
	else
		sin2 = 0;
	
	if (vyzdist > 0)
		cos2 = zp / vyzdist;
	else
		cos2 = 0;
	
	double typ = yp;
	yp = (yp) * cos2 - (zp) * sin2;	
	zp = (typ) * sin2 + (zp) * cos2;
	
	//FourSquareMatrix RotationMatrix(cos1,		0,		-sin1,		0,
	//								-sin1*sin2,	cos2,	-sin2*cos1,	0,
	//								sin1*cos2,	sin2,	cos1*cos2,	0,
	//								0,			0,		0,			1);

	double x, y, z;
	double tx, ty, tz;
	for (int i = 1; i <= nPoints; i++)
	{
		tx = points[i][0] + xOff;
		ty = points[i][1] + yOff;
		tz = points[i][2] + zOff;

		pDx = vx - tx;//x
		pDy = vy - ty;//y
		pDz = vz - tz;//z

		t = (d - dx * tx - dy * ty - dz * tz) / 
			(dx * pDx + dy * pDy + dz * pDz);

		//Screen[i].x = (P[i].x + pDx * t) * cos1 - (P[i].z + pDz * t) * sin1;
		//Screen[i].z = (P[i].x + pDx * t) * sin1 + (P[i].z + pDz * t) * cos1;
		//Screen[i].y = (P[i].y + pDy * t) * cos2 - (Screen[i].z) * sin2;
		//Screen[i].z = (P[i].y + pDy * t) * sin2 + (Screen[i].z) * cos2;
		x = (tx + pDx * t);
		y = (ty + pDy * t);
		z = (tz + pDz * t);
		screenX[i] = int(((x * cos1 - z * sin1) - xp) * 300.0) + Width / 2;
		screenY[i] = ymax - (int(((-sin1 * sin2 * x + cos2 * y - sin2 * cos1 * z) - yp) * 300.0) + Height / 2);
		//Screen[i].z = sin1 * cos2 * x + sin2 * y + cos1 * cos2 * z;
	}
	
	// now draw segments
	
	//SetPen(RGB(255,0,0));
	int xPoint;
	int yPoint;
	int p1, p2;
	for ( i = 0; i < nList; i++)
	{
		p1 = P[i][0];
		p2 = P[i][1];
		DrawLine(screenX[p1],screenY[p1],screenX[p2],screenY[p2],RGB(255,100,100));
		
	}
}
