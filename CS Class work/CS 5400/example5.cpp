// This example program demonstrates double buffering.
// All drawing functions automatically work on the back
// buffer, which is copied to the window.
// ** Note: the larger the window, the slower double buffering is.

#include "graphics.cpp"

#define DELAY 120000

int Main()
{
    // Create a full screen, double-buffered window.
    WindowClass Window;
    Window.OpenWindow(0, 0, 0, 0, FULL_SCREEN | DOUBLE_BUFFER);
    if (!Window.WindowIsOpen())
        return 255;

    int width = Window.GetWidth();
    int height = Window.GetHeight();

    int xdir=5, ydir=5;
    int object[4][2] = {{10, 10}, {50, 10}, {50, 50}, {10, 50}};

    RGBColor white = RGB(255, 255, 255);
    RGBColor black = RGB(0, 0, 0);

    // Draw in object for first time.
    Window.SetDefaultColor(white);
    Window.DrawLine(object[0][0], object[0][1], object[1][0], object[1][1]);
    Window.DrawLine(object[1][0], object[1][1], object[2][0], object[2][1]);
    Window.DrawLine(object[2][0], object[2][1], object[3][0], object[3][1]);
    Window.DrawLine(object[3][0], object[3][1], object[0][0], object[0][1]);

    while (Window.WindowIsOpen())
    {
        // Undraw object.
        Window.SetDefaultColor(black);
        Window.DrawLine(object[0][0], object[0][1], object[1][0], object[1][1]);
        Window.DrawLine(object[1][0], object[1][1], object[2][0], object[2][1]);
        Window.DrawLine(object[2][0], object[2][1], object[3][0], object[3][1]);
        Window.DrawLine(object[3][0], object[3][1], object[0][0], object[0][1]);

        // Update object.
        object[0][0] += xdir;
        object[0][1] += ydir;
        object[1][0] += xdir;
        object[1][1] += ydir;
        object[2][0] += xdir;
        object[2][1] += ydir;
        object[3][0] += xdir;
        object[3][1] += ydir;
        if ((object[2][0] >= width-10) || (object[0][0] <= 10))
            xdir = -xdir;
        if ((object[2][1] >= height-10) || (object[0][1] <= 10))
            ydir = -ydir;

        // Draw object.
        Window.SetDefaultColor(white);
        Window.DrawLine(object[0][0], object[0][1], object[1][0], object[1][1]);
        Window.DrawLine(object[1][0], object[1][1], object[2][0], object[2][1]);
        Window.DrawLine(object[2][0], object[2][1], object[3][0], object[3][1]);
        Window.DrawLine(object[3][0], object[3][1], object[0][0], object[0][1]);

        // Copy back buffer to front buffer.
        Window.SwapBuffers();

        for (int i=0; i<DELAY; i++)
        {}

        Window.CheckEscape();
    }

    return 0;
}
