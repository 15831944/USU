#include <iostream.h>

//Given the following class, Point, the implementation for the function, add, and the 
//main function, write the implementation for the constructor and the function, print.

//Note: Your print function should output the Point, so that it looks like: (x, y, z),
//where x, y, and z are the actual values stored for the given Point. 

class Point
{
	public:
      Point(int = 0, int = 0, int = 0);
      Point add(Point);
      void print();
	private:
      int x;
      int y;
      int z;
};


Point::Point(int a, int b, int c){
	x = a;
	y = b;
	z = c;
}

Point Point::add(Point p)
{
	Point temp;
	temp.x = x + p.x;
	temp.y = y + p.y;
	temp.z = z + p.z;
	return temp;
}

void Point::print(){
	cout << "(" << x << "," << y << "," << z << ")" << endl;
}

void main()
{
	Point p1(1, 2, 3), p2(3, 2, 1), p3;
	cout << "p1 = "; p1.print();
	cout << "p2 = "; p2.print();
	cout << "p3 = "; p3.print();
	p3 = p1.add(p2);
	cout << "p1 + p2 = "; 
	p3.print();
}
