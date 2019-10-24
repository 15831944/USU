//Mark Salisbury
//CS 1720
//P8265A61.cpp
//Assignment 6.1
/*
A61. Revise class Point to be three dimensional (Point3), so the 
attributes are double x, y, z, and create a derived class Sphere
that will inherit class Point3. Provide constructors, destructors, 
setPoint, setRadius, area, and volume functions. Be sure to
overload the << operator. The surface area of a sphere is 4*pi*r*r. 
The volume of a sphere is 4*pi*r*r*r/3. Test all of your functions 
including the constructors and destructors. Do not make your program 
interactive, just hard code the coordinates.  Create separate files 
forPxxxxA61Point3.h (the xxxx is your PIN), PxxxxA61Sphere.h, 
PxxxxA61Point3.cpp, PxxxxA61Sphere.cpp and PxxxxA61prog.cpp 
(the program) and use a project for this programming. Name your 
project PxxxxA61. There will be a PxxxxA61.dsp file created for the 
project, it is a small text file and contains the information for 
the project. After you have created the project and completely 
debugged your code in the project,  submit the PxxxxA61.dsp file to
the homework site. After you have submitted it, then combine your 
.cpp files into one file, PxxxxA61.cpp, (be sure to comment out the 
proper #include's). Compile your program again to make sure all is 
well and then submit just the complete .cpp file.  I want to know 
that you worked on this as a project (the .dsp file from the project) 
but I also want to have an reasonable way for us to check your work 
and compile and run your program (the .cpp file). You must do this 
assignment with a project or you will receive a 0.
*/



#include <iostream.h>
#include <iomanip.h>
//#include "P8265A61point3.h"
// point3.h
// Definition of class Point3
//#ifndef POINT3_H
//#define POINT3_H

class Point3 {
   friend ostream &operator<<( ostream &, const Point3 & );
public:
   Point3( double = 0.0, double = 0.0, double = 0.0 );      // default constructor
   void setPoint( double, double, double );      // set coordinates
protected:         // accessible by derived classes
   double x, y, z;       // x, y, and z coordinates of the Point
};

//#endif

// point3.cpp
// Member functions for class Point3
//#include <iostream.h>
//#include "P8265A61point3.h"

// Constructor for class Point3
Point3::Point3( double a, double b, double c ) { setPoint( a, b, c ); }

// Set x, y, and z coordinates of Point
void Point3::setPoint( double a, double b, double c )
{
   x = a;
   y = b;
   z = c;
}

// Output Point3 (with overloaded stream insertion operator)
ostream &operator<<( ostream &output, const Point3 &p )
{
   output << '[' << p.x << ", " << p.y << ", " << p.z << ']';

   return output;   // enables cascaded calls
}


//#include "P8265A61sphere.h"
// sphere.h
// Definition of class Sphere
//#ifndef SPHERE_H
//#define SPHERE_H

//#include <iostream.h>
//#include <iomanip.h>
//#include "P8265A61point3.h"

class Sphere : public Point3 {  // Sphere inherits from Point3
   friend ostream &operator<<( ostream &, const Sphere & );
public:
   // default constructor
   Sphere( double r = 0.0, double x = 0.0, 
	       double y = 0.0, double z = 0.0 );

   void setRadius( double );   // set radius
   double volume( const Sphere &);
   double surfaceArea( const Sphere &);
protected:
   double radius;
};

//#endif

// sphere.cpp
// Member function definitions for class Sphere
//#include "P8265A61sphere.h"

Sphere::Sphere( double r, double a, double b, double c )
   : Point3( a, b, c )       // call base-class constructor
{ setRadius( r ); }

void Sphere::setRadius( double r ) { 
	radius = ( r >= 0.0 ? r : 0.0 ) ; 
}

double Sphere::volume( const Sphere & s) {
	return 4.0 * 3.14159 * s.radius * s.radius * s.radius / 3.0 ;
}

double Sphere::surfaceArea( const Sphere & s) {
	return 4.0 * 3.14159 * s.radius * s.radius ;
}

ostream &operator<<( ostream &output, const Sphere &c ) {
   output << "Center = " << static_cast< Point3 >( c ) 
          << "; Radius = " 
          << setiosflags( ios::fixed | ios::showpoint )
          << setprecision( 2 ) << c.radius;

   return output;   // enables cascaded calls
}

void main()
{
   Point3 *pointPtr = 0, p( 30, 50 );
   Sphere *spherePtr = 0, c( 4, 120, 89 ); // radius, x, y, z

   cout << "Point p: " << p << "\nSphere c: " << c << endl;

   cout << "Volume of c: " << c.volume(c) << " Surface area of c: " 
	    << c.surfaceArea(c) << endl;
}
