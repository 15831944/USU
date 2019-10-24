// This library is meant to create a window and allow the programmer to draw to it in 24-bit color.

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>

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


/*------------------------------------------------------------------
Class WindowClass - declaration
Encapsulates open and closing, as well as basic drawing stuff.
--------------------------------------------------------------------*/

class WindowClass
{
    private:
        HWND hwnd;             // Window handle.
        BOOL IsOpen;
        BOOL DoubleBuffer;
        unsigned int Width;
        unsigned int Height;
        HPEN defaultpen;
        HPEN scratchpen;
        HBRUSH scratchbrush;
        HDC hdc;
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
          
        SelectObject(backbuff, bitmap);
        hdc = backbuff;
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
