//  Mark Salisbury
//  529-71-8265
//  2nd hour
//  3-31-97
//  Sequential, Decision & Looping Structures #3
//  quadrants

#include <iostream.h>

void main() {

float X = 0;
float Y = 0;
int i = 0;

for (i = 1; i <= 5; ++i) {
	cout << "Enter the x coordinate of point #" << i << ": " << flush;
	cin >> X;
	cout << "Enter the y coordinate of point #" << i << ": " << flush;
	cin >> Y;
	cout << "The point (" << X << "," << Y << ") lies " << flush;

	if (Y > 0) {
		if (X > 0)
			cout << "in quadrant 1" << endl;
		else if (X < 0)
			cout << "in quadrant 2" << endl;
		else
			cout << "on the Y-axis" << endl;
	}
	else if (Y < 0) {
		if (X > 0)
			cout << "in quadrant 4" << endl;
		else if (X < 0)
			cout << "in quadrant 3" << endl;
		else
			cout << "on the Y-axis" << endl;
	}
	else if (X != 0)
		cout << "on the X-axis" << endl;
	else
		cout << "on the origin" << endl;
}

}

