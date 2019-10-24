// This example program show how to draw filled polygons.

#include "graphics.cpp"

int Main()
{
    // Create a full screen, double-buffered window.
    WindowClass Window;
    Window.OpenWindow(400, 400, 10, 10, NORMAL_WINDOW);
    if (!Window.WindowIsOpen())
        return 255;

    int width = Window.GetWidth();
    int height = Window.GetHeight();

    // Now let's draw our polygons.
    RGBColor color = RGB(25, 255, 31);
    Window.DrawPoly(10, 12, 312, 24, 79, 115, color);
    
    color = RGB(241, 10, 255);
    Window.DrawPoly(290, 170, 390, 170, 330, 190, color);

    color = RGB(0, 5, 255);
    Window.DrawPoly(100, 390, 100, 200, 315, 305, color);

    while (Window.WindowIsOpen())
        Window.CheckEscape();

    return 0;
}
