// This library is meant to create a window and allow the programmer to draw to it in 24-bit color.

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <math.h>
#include "Object3d.h"
#include "Vector3d.h"
#include "Polygon.h"
#include <mmsystem.h>

////////////////////////////////////////////////////////////////////////////////////////////
// to sort an array of structures.
// 

#include <stdio.h>
#include <stdlib.h>

//#include "MergeSort.cpp"

struct polyDistance
{
public:
	polyDistance()
	{
		polyN = 0;
		dist = 0.0;
	}

	void set(int n, double d)
	{
		polyN = n;
		dist = d;
	}

	bool operator<(const polyDistance & right) const 
	{
		return (dist < right.dist);
	}

	polyDistance & operator=(const polyDistance & right)
	{
		polyN = right.polyN;
		dist = right.dist;
		return *this;
	}

	int polyN;
	double dist;
};

typedef int (*compfn)(const void*, const void*);

int compare(struct polyDistance *elem1, struct polyDistance *elem2)
{
  if ( elem1->dist > elem2->dist )
      return -1;

   else if (elem1->dist < elem2->dist )
      return 1;

   else
      return 0;
}

///////////////////////////////////////////////////////////////////////
// Name of window.
#define NAME "Graphics Window"
#define TITLE "** Graphics Window **"

// Options for opening a window.
#define NORMAL_WINDOW 0
#define FULL_SCREEN 1
#define DOUBLE_BUFFER 2

//#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#define RED(x)			(BYTE)(x % 0x100)
#define GREEN(x)		(BYTE)((x % 0x10000) / 0x100)
#define BLUE(x)			(BYTE)((x % 0x1000000) / 0x10000)

typedef long int RGBColor;
extern int *screenX;
extern int *screenY;


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
							CVector3d C);
        
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
 CVector3d C)
{
	
	// calculate sin and cos for rotations...
	static double tx, ty, tz, x, y, z, dx, dy, dz, vx, vy, vz;
	static double sin1, cos1, sin2, cos2;
	static double rsin1, rcos1, rsin2, rcos2, rsin3, rcos3;
	static double a1, a2, a3, b1, b2, b3, c1, c2, c3;
	static double pa1, pa2, pa3, pb1, pb2, pb3, pc1, pc2, pc3;
	static double xOff, yOff, zOff;
	static double d = 3;
	static double zoomFactor = 300;
	static double viewPlaneZ;
	static double den;
	static double dBehind;
	static int xBase, yBase;
	static COLORREF color;

	dx = C.x - V.x;
	dy = C.y - V.y;
	dz = C.z - V.z;

	// viewing rotation
	getRotAngle(dx, dy, dz, sin1, cos1, sin2, cos2);

	// object rotation
	rsin1 = sin(rot.x);
	rcos1 = cos(rot.x);
	rsin2 = sin(rot.y);
	rcos2 = cos(rot.y);
	rsin3 = sin(rot.z);
	rcos3 = cos(rot.z);
	
	// object rotation matrix
	a1 = rcos3 * rcos2;
	a2 = -rsin3 * rcos2;
	a3 = -rsin2;
	b1 = -rsin1 * rsin2 * rcos3 + rcos1 * rsin3;
	b2 = rsin1 * rsin2 * rsin3 + rcos1 * rcos3;
	b3 = -rsin1 * rcos2;
	c1 = rcos1 * rsin2 * rcos3 + rsin1 * rsin3;
	c2 = -rcos1 * rsin2 * rsin3 + rsin1 * rcos3;
	c3 = rcos1 * rcos2;

	// viewing rotation matrix (for projection)
	pa1 = cos1;
	pa2 = 0;
	pa3 = -sin1;
	pb1 = -sin1 * sin2;
	pb2 = cos2;
	pb3 = -sin2 * cos1;
	pc1 = sin1 * cos2;
	pc2 = sin2;
	pc3 = cos1 * cos2;

	// object translation
	xOff = offSet.x - C.x;
	yOff = offSet.y - C.y;
	zOff = offSet.z - C.z;

	viewPlaneZ = - sqrt( dx*dx + dy*dy + dz*dz );

	xBase = Width / 2;
	yBase = Height / 2;

	// perfrom opposite translations, rotations on view vector to keep it in line with original 
	// coordinates of object.
	// this will keep it in the same vector space as the objects' faces' normal vectors... 
	//CVector3d ViewVector(dx * a1 + dy * -a2 + dz * -a3, 
	//	dx * (rsin1 * -rsin2 * rcos3 + rcos1 * -rsin3) + dy * (-rsin1 * rsin2 * rsin3 + rcos1 * rcos3) + dz * -b3,
	//	dx * (rcos1 * -rsin2 * rcos3 + rsin1 * rsin3) + dy * (-rcos1 * rsin2 * rsin3 + -rsin1 * rcos3) + dz * c3);
	///
	//ViewVector.x += -xOff;
	//ViewVector.y += -yOff;
	//ViewVector.z += -zOff;
	//
	//ViewVector.SetVector(ViewVector.x *  pa1 + ViewVector.z * -pa3,
	//					 ViewVector.x *  pb1 + ViewVector.y *  pb2 + ViewVector.z * -pb3,
	//					 ViewVector.x * -pc1 + ViewVector.y * -pc2 + ViewVector.z * pc3);

	vx = V.x - offSet.x;
	vy = V.y - offSet.y;
	vz = V.z - offSet.z;
	CVector3d ViewPoint(vx * a1 + vy * -a2 + vz * -a3, 
		vx * (rsin1 * -rsin2 * rcos3 + rcos1 * -rsin3) + vy * (-rsin1 * rsin2 * rsin3 + rcos1 * rcos3) + vz * -b3,
		vx * (rcos1 * -rsin2 * rcos3 + rsin1 * rsin3) + vy * (-rcos1 * rsin2 * rsin3 + -rsin1 * rcos3) + vz * c3);

	for (int i = 1; i <= object.nVertices; i++)
	{
		// rotate object...
		tx = object.vertices[i][0] * a1 + object.vertices[i][1] * a2 + object.vertices[i][2] * a3;
		ty = object.vertices[i][0] * b1 + object.vertices[i][1] * b2 + object.vertices[i][2] * b3;
		tz = object.vertices[i][0] * c1 + object.vertices[i][1] * c2 + object.vertices[i][2] * c3;
	
		// Perform transformations...
		tx += xOff;
		ty += yOff;
		tz += zOff;

		// rotate object for projection...
		x = tx * pa1 + ty * pa2 + tz * pa3;
		y = tx * pb1 + ty * pb2 + tz * pb3;
		z = tx * pc1 + ty * pc2 + tz * pc3;
		
		// calculate perspective...
		// (view point is now at (0,0,-viewPlaneZ)
		dBehind = z - viewPlaneZ;
		if (dBehind < 0)
			dBehind = 0;
		den = dBehind / d + 1;
		x = x / den;
		y = y / den;
		
		// calculate screen coordinates...
		screenX[i] = x * zoomFactor + xBase;
		screenY[i] = Height - (yBase + y * zoomFactor);
	}

	POINT points[10];
	COLORREF lastColor = RGB(0,0,0);

	CVector3d ViewVector;
	int v;
	double cosTheta;
	BYTE newRed, newGreen, newBlue;

	polyDistance * polyList = new polyDistance[object.nShapes];

	int nList = 0;
	double dist;
	for ( i = 0; i < object.nShapes; i++)
	{
		v = object.shapes[i].Vertice[0];

		ViewVector.x = object.vertices[v][0] - ViewPoint.x;
		ViewVector.y = object.vertices[v][1] - ViewPoint.y;
		ViewVector.z = object.vertices[v][2] - ViewPoint.z;

		if (!object.useNormalVector || ViewVector * object.shapes[i].NormalVector > 0)
		{
			dist = sqrt( ViewVector.x*ViewVector.x + ViewVector.y*ViewVector.y + ViewVector.z*ViewVector.z );
			polyList[nList].set(i,dist);
			nList++;
		}
	}

	//msort(polyList, 0, nList);
	qsort((void *) polyList,              // Beginning address of array
		nList,                                 // Number of elements in array
		sizeof(struct polyDistance),              // Size of each element
		(compfn)compare );                  // Pointer to compare function

	for ( i = 0; i < nList && WindowIsOpen(); i++)
	{
		int wPoly = polyList[i].polyN;
		v = object.shapes[wPoly].Vertice[0];

		ViewVector.x = object.vertices[v][0] - ViewPoint.x;
		ViewVector.y = object.vertices[v][1] - ViewPoint.y;
		ViewVector.z = object.vertices[v][2] - ViewPoint.z;

		ViewVector.Normalize();

		color = object.shapes[wPoly].shapeColor;
		cosTheta = ViewVector * object.shapes[wPoly].NormalVector;
		newRed = (BYTE)(cosTheta * (double) RED(color));
		newGreen = (BYTE)(cosTheta * (double) GREEN(color));
		newBlue = (BYTE)(cosTheta * (double) BLUE(color));
		
		color = RGB(newRed,newGreen,newBlue);

		//if (color != lastColor)
		//{
		//	scratchpen = CreatePen(PS_SOLID, 0, color);
		//	DeleteObject(SelectObject(hdc, scratchpen));
		//}

		for (int wv = 0; wv < object.shapes[wPoly].nVertices; wv++)
		{
			points[wv].x = screenX[object.shapes[wPoly].Vertice[wv]];
			points[wv].y = screenY[object.shapes[wPoly].Vertice[wv]];
		}

		HPEN mypen = CreatePen(PS_SOLID, 0, color);
		SelectObject(hdc, mypen);

		HBRUSH mybrush = CreateSolidBrush(color);
		SelectObject(hdc, mybrush);

			//Polyline(hdc,points,object.shapes[wPoly].nVertices);
		Polygon(hdc,points,object.shapes[wPoly].nVertices);

		//Polygon(hdc, pointlist, 3);

		SelectObject(hdc, scratchpen);
		DeleteObject(mypen);

		SelectObject(hdc, scratchbrush);
		DeleteObject(mybrush);
		
		CheckEscape();
	}

	delete [] polyList;
	
}
