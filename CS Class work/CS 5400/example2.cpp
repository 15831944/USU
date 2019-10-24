// This example program demonstrates drawing ramdom pixels within a window.

#include "graphics.cpp"
#include <time.h>

int Main()
{
    // Create a window.  Set last parameter to 1 for the window to be full screen.
    WindowClass MyWindow;
    MyWindow.OpenWindow(200, 200, 100, 100, 0);
    if (!MyWindow.WindowIsOpen())
        return 255;

    int width = MyWindow.GetWidth();
    int height = MyWindow.GetHeight();

    // Now draw the pixels.
    RGBColor color;
    srand((unsigned) time(NULL));

    while (MyWindow.WindowIsOpen())
    {
        // Now draw random pixels until escape is hit.
        color = RGB((unsigned char) rand(), (unsigned char) rand(), (unsigned char) rand());
        MyWindow.DrawPixel((unsigned char) rand()%width, (unsigned char) rand()%height, color);

        MyWindow.CheckEscape();
    }

    return 0;
}
