//this is a test program
#include <iostream.h>

class color{
	friend ostream & operator<<( ostream&, const color &);
	friend istream & operator>>( istream&, color &);
public:
	color();
	color(int, int, int);
	color operator+(color &);
	color operator=(const color &);
private:
	int red;
	int green;
	int blue;

};

color::color(int r, int g, int b){
	red = r;
	green = g;
	blue = b;
}

color::color(){
	red = 0;
	green = 0;
	blue = 0;
}

color color::operator+(color &num2){
	color sum;
	sum.red = red + num2.red;
	sum.green = green + num2.green;
	sum.blue = blue+ num2.blue;
	return sum;
}

color color::operator=(const color & right){
	red = right.red;
	green = right.green;
	blue = right.blue;
	return *this;
}

ostream &operator<<( ostream &output, const color & thiscolor){
	output << "(" << thiscolor.red << "," << thiscolor.green << "," << thiscolor.blue << ")";
	return output;
}

istream &operator>>( istream &input, color & thiscolor){
	input >> thiscolor.red >> thiscolor.green >> thiscolor.blue;
	return input; 
}

void main(void){

	color yellow(0, 255, 255);
	cout << "yellow = " << yellow;
	cout << "Enter a new color: ";
	color newcolor;
	cin >> newcolor;
	color productcolor = newcolor + yellow;	
	cout << "The new color is: " << productcolor;

}