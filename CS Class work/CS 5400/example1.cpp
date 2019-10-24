// This example program demonstrates drawing 3 lines of different colors.

#include "graphics.cpp"

int Main()
{
    // Create a full screen window.
    WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, 1);
    if (!MyWindow.WindowIsOpen())
        return 255;

    // Now draw the lines.
    RGBColor color;
    color = RGB(200, 200, 200);
    MyWindow.DrawLine(5, 5, 700, 150, color);

    color = RGB(0, 0, 255);
    MyWindow.DrawLine(187, 2, 1, 1000, color);

    color = RGB(0, 255, 0);
    MyWindow.DrawLine(25, 29, 731, 30, color);

    while (MyWindow.WindowIsOpen())
    {
        // Wait for escape to be pressed.
        MyWindow.CheckEscape();
    }

    return 0;
}