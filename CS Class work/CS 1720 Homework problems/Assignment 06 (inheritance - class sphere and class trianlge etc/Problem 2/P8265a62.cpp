/*
A62. Create a class Triangle that inherits class Point (two 
dimensional). Provide constructors, destructors, setPoint, 
setTriangle, area and perimeter of the triangle. Be sure to overload 
the << operator. Also create a class Quadrilateral that inherits the 
class Point and has four points as attributes, write the constructors, 
destructors and a setQuad function to set the 4 points. Also create 
two classes that inherit the class Quatrilateral, class Square and 
class Parallelogram along with constructors, destructors, area and 
perimeter functions. Your program must test all functions including 
constructors and destructors. Do not make your program interactive, 
just hard code the coordinates.  
point, 
	triangle, 
	quatrilateral, 
		square, 
		parallelogram, 
Create separate files for
PxxxxA62Point.h (the xxxx is your PIN), PxxxxA62Triangle.h, 
PxxxxA62Quatrilateral.h, PxxxxA62Square.h, PxxxxA62Parallelogram.h, 
PxxxxA62Point.cpp , PxxxxA62Triangle.cpp, PxxxxA62Quatrilateral.cpp, 
PxxxxA62Square.cpp, PxxxxA62Parallelogram.cpp, and PxxxxA62prog.cpp 
(the program) and use a project for this programming. Name your project 
PxxxxA62. There will be a PxxxxA62.dsp file created for the project, 
it is a small text file and contains the information for the project. 
After you have created the project and completely debugged your code 
in the project, submit the PxxxxA62.dsp file to the homework site. 
After you have submitted it, then combine your .cpp files into one file, 
PxxxxA62.cpp, (be sure to comment out the proper #include's).  Compile 
your program again to make sure all is well and then submit just the 
complete .cpp file.  I want to know that you worked on this as a project
(the .dsp file from the project) but I also want to have an reasonable 
way for us to check your work and compile and run your programs. You 
must do this assignment with a project or you will receive a 0.

A zero (0) will be recorded if the above instructions are not followed.
*/
#include <iostream.h>
#include "triangle.h"
#include "quatrilateral.h"
#include "parallelogram.h"
#include "point2.h"

void main(){

	triangle t1(point2(0,0), point2(4,0), point2(4,4));
	cout << "Triangle t1 = " << endl << t1 << endl;
	cout << "Perimeter of t1 = " << t1.perimeter() << endl;
	cout << "Area of t1 = " << t1.area() << endl;

	triangle t2;
	cout << "Triangle t2 = " << endl << t2 << endl;

	quatrilateral q1(point2(0,0), point2(4,0), point2(4,4), point2(0,4));
	cout << "Quatrilateral q1 = " << endl << q1 << endl;
	cout << "Perimeter of q1 = " << q1.perimeter() << endl;
	cout << "Area of q1 = " << q1.area() << endl;

	quatrilateral q2;
	cout << "Quatrilateral q2 = " << endl << q2 << endl;

	paralellogram p1(point2(0,0), point2(12,0), point2(4,6), point2(0,4));
	cout << "Paralellogram p1 = " << endl << p1 << endl;
	cout << "Perimeter of p1 = " << p1.perimeter() << endl;
	cout << "Area of p1 = " << p1.area() << endl;

	paralellogram p2(q1);
	cout << "Paralellogram p2 = " << endl << p2 << endl;
	

}