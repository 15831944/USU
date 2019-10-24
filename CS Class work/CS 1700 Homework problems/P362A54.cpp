// 362
// marks
// Mark Salisbury
// P362A54.cpp
/*
A54. Write a program that computes the duration of a projectile's flight and its height 
above the ground when it reaches the target. You must write and your program must call 
two functions, projectiletime that will calculate and return the time in seconds that 
the projectile is in flight, and projectileheight that will calculate and return the 
height of the projectile after a given time. The function projectiletime will require 
three parameters, the distance, the velocity and the angle. The function projectileheight 
will require three parmenters, the velocity, the angle and the time as calculated using 
projectiletime. Use doubles for all of your calculations.

The input consists of the distance to the target, the velocity and the elevation angle 
in degrees. You must have a function to convert degrees to radians. 2*pi radians =
360 degrees.

The output consists of the time of flight in seconds and the height above the target in feet.
If the height is <0 then the projectile ends up below the target.

Numbers to try: initial velocity 5000 ft/sec. angle of elevation 1 degree, distance to 
target 1 mile = 5280 ft.
*/
#include <iostream.h>
#include <math.h>

double const g = 32.17; //gravitational constant
double const pi = 3.14159; //pi

double ProjecttileHeight(double &velocity, double &angle, double &time);
//returns height of projectile at time t
double ProjecttileTime(double &distance, double &velocity, double &angle); 
// returns time projectile is in flight
double ConverToRadians(double &degrees);

void main(void)
{
	double initVelo,
		    Angle,
			 Dist,
			 Time,
			 Height;

	cout << "Enter the projectile's initial velocity (ft/s): ";
	cin >> initVelo;
	cout << "Enter the firing angle in degrees (must be less than 90): ";
	cin >> Angle;
	cout << "Enter the distance to target (ft): ";
	cin >> Dist;

	Angle = ConverToRadians(Angle);
	cout << "Time projectile was in flight: " << (Time = ProjecttileTime(Dist, initVelo, Angle)) << " seconds." << endl;
	
	Height = ProjecttileHeight(initVelo, Angle, Time);
	cout << "Projectile was " << Height << " feet " << ((Height > 0.0)? "above":"below") << " the target." << endl;

}

double ProjecttileHeight(double &velocity, double &angle, double &time)
{//returns height of projectile at time t
	return (velocity * time * sin(angle) - g * time * time / 2);
}
	
double ProjecttileTime(double &distance, double &velocity, double &angle) 
{// returns time projectile is in flight
	return (distance / (velocity * cos(angle)));
}

double ConverToRadians(double &degrees)
{
	return (pi * degrees / 180);
}

/*Formulas:
    t = d/(v*cos(theta)).
        where t is time in seconds, d is distance in feet, v is the initial velocity 
		  in feet/sec and theta is the angle of elevation in radians.

    h = v*t*sin(theta) - g*t2/2.
        where h is the height in feet and g is a constant, 32.17 ft/sec2.

The sin() and cos() functions are found in math.h.
*/