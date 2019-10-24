// This example program demonstrates animation by rotating a square.
//  using matrix operations
#include "graphics.cpp"
#include <math.h>

#define DELAY 1
#define pi 3.1415926536
#define N 4


class Matrix4X4
{
    public:
        double _11, _12;
        double _21, _22;
};


class Matrix1X4
{
    public:
        double _11, _12;

    public:
        Matrix1X4 operator*(const Matrix4X4 &mat)
        {
            Matrix1X4 myreturn;

            myreturn._11 = _11 * mat._11 + _12 * mat._21;
            myreturn._12 = _11 * mat._12 + _12 * mat._22;

            return myreturn;
        }

        void operator=(const Matrix1X4 &mat)
        {
            _11 = mat._11;
            _12 = mat._12;
        }
};



int Main()
{
    int i, j;
    double x[N], y[N];
    int sx[2][N], sy[2][N];
    double theta, phi, s, c;

    Matrix4X4 comp;
    Matrix1X4 point, trans;


    // Create a fullscreen window.
    WindowClass Window;
    Window.OpenWindow(0, 0, 0, 0, 1);
    Window.CheckEscape();

    if (!Window.WindowIsOpen())
        return 255;

    int XMax = Window.GetWidth();
    int YMax = Window.GetHeight();
    int XCenter = XMax / 2;
    int YCenter = YMax / 2;

    // Each time we rotate, it will be by one degree.
    theta = 0.0;
    phi = 2*pi/360;

    // Coordinates of square, old [0] and new [1].
    x[0] = -0.1;
    y[0] = -0.1;
    x[1] = 0.1;
    y[1] = -0.1;
    x[2] = 0.1;
    y[2] = 0.1;
    x[3] = -0.1;
    y[3] = 0.1;

    // Set up our colors.
    RGBColor white = RGB(255, 255, 255);
    RGBColor black = RGB(0, 0, 0);


    // Now let's rotate our square for 720 degrees.
    for (i=0; i<720; i++)
    {
        theta += phi;

        for (j=0; j<N; j++)
        {
           // Calculate new world coordinates.
           s = sin(theta);
           c = cos(theta);
           comp._11 = s;
           comp._21 = c;
           comp._12 = c;
           comp._22 = -s;
           point._11 = x[j];
           point._12 = y[j];
       
           trans = point * comp;
    
            // Calculate new screen coordinates.
            sx[1][j] = (int) (XMax * trans._11 + XCenter);
            sy[1][j] = YMax - (int)(XMax * trans._12) - YCenter;
        }

        // Undraw the old line, draw the new line to the screen.
        for (j=0; j<N; j++)
        {
            Window.DrawLine(sx[0][j], sy[0][j], sx[0][(j+1)%N], sy[0][(j+1)%N], black);
            Window.DrawLine(sx[1][j], sy[1][j], sx[1][(j+1)%N], sy[1][(j+1)%N], white);
        }

        // Update the old coordinates.
        for (j=0; j<N; j++)
        {
            sx[0][j] = sx[1][j];
            sy[0][j] = sy[1][j];
        }

        // Delay for defined period so program doesn't go too fast.
        Sleep(DELAY);
    }


    Window.CloseWindow();

    return 0;
}

