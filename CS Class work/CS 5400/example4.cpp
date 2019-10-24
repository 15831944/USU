// This example program demonstrates animation by rotating a square.

#include "graphics.cpp"
#include <math.h>

#define DELAY 1
#define pi 3.1415926536
#define N 4

int Main()
{
    int i, j;
    double x[2][N], y[2][N], xc, yc;
    int sx[2][N], sy[2][N];
    double theta, c, s, xcs, xcc, ycs, ycc;

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
    theta = 2*pi/360;
    c = cos(theta);
    s = sin(theta);

    // Coordinates of square, old [0] and new [1].
    x[0][0] = -0.1;
    y[0][0] = -0.1;
    x[0][1] = 0.1;
    y[0][1] = -0.1;
    x[0][2] = 0.1;
    y[0][2] = 0.1;
    x[0][3] = -0.1;
    y[0][3] = 0.1;

    // Center of square.
    xc = 0.0;
    yc = 0.0;

    xcs = xc*s;
    xcc = xc*c;
    ycs = yc*s;
    ycc = yc*c;

    // Set up our colors.
    RGBColor white = RGB(255, 255, 255);
    RGBColor black = RGB(0, 0, 0);

    // Now let's rotate our square for 720 degrees.
    for (i=0; i<720; i++)
    {
        for (j=0; j<N; j++)
        {
            // Calculate new world coordinates.
            x[1][j] = x[0][j]*c - y[0][j]*s - xcc + ycs + xc;
            y[1][j] = x[0][j]*s + y[0][j]*c - xcs - ycc + yc;

            // Calculate new screen coordinates.
            sx[1][j] = (int) (XMax * x[1][j] + XCenter);
            sy[1][j] = YMax - (int)(XMax * y[1][j]) - YCenter;
        }

        for (j=0; j<N; j++)
        {
            // Undraw the old line, draw the new line to the screen.
            Window.DrawLine(sx[0][j], sy[0][j], sx[0][(j+1)%N], sy[0][(j+1)%N], black);
            Window.DrawLine(sx[1][j], sy[1][j], sx[1][(j+1)%N], sy[1][(j+1)%N], white);
        }

        // Update the old coordinates.
        for (j=0; j<N; j++)
        {
            x[0][j] = x[1][j];
            y[0][j] = y[1][j];

            sx[0][j] = sx[1][j];
            sy[0][j] = sy[1][j];
        }

        // Delay for defined period so program doesn't go too fast.
        Sleep(DELAY);
    }


    Window.CloseWindow();

    return 0;
}
