// This example program demonstrates drawing 3 lines of different colors.

#include "graphics.cpp"

int Main()
{
    // Create a full screen window.
    WindowClass *MyWindow = new WindowClass(0, 0, 0, 0, 1);
    if (!MyWindow->WindowIsOpen())
        return 255;

    int width = MyWindow->GetWidth();
    int height = MyWindow->GetHeight();


    // Now draw the lines.
    MyWindow->ClearWindow();

    RGBColor color;
    color = RGB(200, 200, 200);
    MyWindow->DrawLine(5, 5, 700, 150, color);

    color = RGB(0, 0, 255);
    MyWindow->DrawLine(187, 2, 1, 1000, color);

    color = RGB(0, 255, 0);
    MyWindow->DrawLine(25, 29, 731, 30, color);


    // Step 3.
    Sleep(3000);

	color = RGB(0, 255, 0);
    MyWindow->ClearWindow(color);

    color = RGB(200, 0, 200);
    MyWindow->DrawLine(434, 532, 3, 150, color);

    color = RGB(200, 100, 255);
    MyWindow->DrawLine(4, 5, 300, 150, color);


    // Step 2
    Sleep(3000);

	color = RGB(50, 50, 50);
    MyWindow->ClearWindow(color);

    color = RGB(0, 100, 200);
    MyWindow->DrawLine(15, 25, 700, 150, color);


    // Finish up.
    Sleep(3000);
    MyWindow->CloseWindow();
    delete MyWindow;


    return 0;
}
