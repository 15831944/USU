// This library is meant to create a window and allow the programmer to draw to it in 24-bit color.

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <math.h>
#include "Object3d.h"
#include "Vector3d.h"
#include "Polygon.h"
#include <mmsystem.h>


// Name of window.
#define NAME "Graphics Window"
#define TITLE "** Graphics Window **"

// Options for opening a window.
#define NORMAL_WINDOW 0
#define FULL_SCREEN 1
#define DOUBLE_BUFFER 2

typedef long int RGBColor;

extern DWORD startTime, currentTime, calculateTime, drawTime;

// *** Prototypes.  Main() is the function the user will provide.
long FAR PASCAL WindowProc( HWND hWnd, UINT message,WPARAM wParam, LPARAM lParam );
int Main();


// *** Here are the few global variables I use.
HINSTANCE gb_hInstance;
BOOL gb_bActive;
int gb_nCmdShow;

HWND last_win_closed = 0;


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
		
		void ProjectPoints(CVector3d rot, CVector3d offSet,  
							Object3d &object, CVector3d V, 
							CVector3d C, double viewDist);
        
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

void getRotAngle(double dx, double dy, double dz, double &sin1, double &cos1, double &sin2, double &cos2)
{
	double l = sqrt(dx * dx + dz * dz);
	if (l > 0)
	{
		sin1 = dx / l;
		cos1 = dz / l;
	}
	else
	{
		sin1 = 0.0;
		cos1 = 1.0;
	}

	double l2 = sqrt(l * l + dy * dy);
	if (l2 > 0)
	{
		sin2 = dy / l2;
		cos2 = l / l2;
	}
	else
	{
		sin2 = 0.0;
		cos2 = 1.0;
	}
}


void WindowClass::ProjectPoints
(CVector3d rot, CVector3d offSet,  
 Object3d & object, CVector3d V, 
 CVector3d C, double viewDist)
{
	static int screenX[400];
	static int screenY[400];
	// calculate sin and cos for rotations...
	static double tx, ty, tz, x, y, z, cx, cy, cz;
	static double sin1, cos1, sin2, cos2;
	static double rsin1, rcos1, rsin2, rcos2;
	static double d = 20;
	static double zoomFactor = 300;
	static double viewPlaneZ;
	static double den;
	static double dBehind;
	static int xBase, yBase;
	static COLORREF color;
	
	startTime = timeGetTime();

	cx = C.x;
	cy = C.y;
	cz = C.z;

	getRotAngle(cx - V.x, cy - V.y, cz - V.z, sin1, cos1, sin2, cos2);
	getRotAngle(rot.x, rot.y, rot.z, rsin1, rcos1, rsin2, rcos2);
	// if these angles are correct translating the point in the middle of the 
	// viewplane would have the coordinates 0,0,l2

	viewPlaneZ = viewDist - sqrt((cx - V.x)*(cx - V.x)+(cy - V.y)*(cy - V.y)+(cz - V.z)*(cz - V.z));

	xBase = Width / 2;
	yBase = Height / 2;
	for (int i = 1; i <= object.nVertices; i++)
	{
		tx = object.vertices[i][0] * rcos1 - object.vertices[i][2] * rsin1;
		ty = -rsin1 * rsin2 * object.vertices[i][0] + rcos2 * object.vertices[i][1] - rsin2 * rcos1 * object.vertices[i][2];
		tz = rsin1 * rcos2 * object.vertices[i][0] + rsin2 * object.vertices[i][1] + rcos1 * rcos2 * object.vertices[i][2];

		// Perform transformations...
		tx += (offSet.x - cx);
		ty += (offSet.y - cy);
		tz += (offSet.z - cz);

		x = tx * cos1 - tz * sin1;
		y = -sin1 * sin2 * tx + cos2 * ty - sin2 * cos1 * tz;
		z = sin1 * cos2 * tx + sin2 * ty + cos1 * cos2 * tz;
		
		dBehind = z - viewPlaneZ;
		
		if (dBehind < 0)
			dBehind = 0;
		den = dBehind / d + 1;
		x = x / den;
		y = y / den;
		screenX[i] = x * zoomFactor + xBase;
		screenY[i] = Height - (yBase + y * zoomFactor);
	}

	int p1, p2;
	POINT points[10];
	
	COLORREF lastColor = RGB(0,0,0);
	scratchpen = NULL;
	
	currentTime = timeGetTime();		
	calculateTime = currentTime - startTime; 
	startTime = currentTime;

	for ( i = 0; i < object.nShapes; i++)
	{
		p1 = object.shapes[i].Vertice[0];
		color = object.shapes[i].shapeColor;
		if (color != lastColor)
		{
			if (scratchpen)
				DeleteObject(scratchpen);
			HPEN scratchpen = CreatePen(PS_SOLID, 0, color);
		    SelectObject(hdc, scratchpen);
		}

		for (int wv = 0; wv < object.shapes[i].nVertices; wv++)
		{
			points[wv].x = screenX[object.shapes[i].Vertice[wv]];
			points[wv].y = screenY[object.shapes[i].Vertice[wv]];
		}
		Polyline(hdc,points,object.shapes[i].nVertices);
		
		/*
		for (int wV = 2; wV <= object.shapes[i].nVertices; wV++)
		{
			p2 = p1;
			p1 = shapes[i][wV];
			DrawLine(screenX[p1],screenY[p1],screenX[p2],screenY[p2], color);
		}
		*/
	}
	DeleteObject(scratchpen);
	drawTime += timeGetTime() - startTime;
}

/*	
					
void WindowClass::ProjectPoints(double yRot, double xOff, double yOff, double zOff, int P[][2], int nList, double points[][3], int nPoints, CVector3d V, CVector3d C, double viewDist, COLORREF color)
{
	//static CVector3d Plane[100];
	//static CVector3d Screen[100];
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
	
	CVector3d ScreenCenter;// = RotationMatrix.RotationDropZ(CVector3d(xp,yp,zp));
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
*/