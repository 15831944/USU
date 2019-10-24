//Lab 9
//Mark Salisbury
#include <iostream.h>

void swap(char &a, char&b){
	char temp = a;
	a = b;
	b = temp;
}

void main(void){
	char a, b, c;
	cout << "Enter 3 characters. " << endl
		  << "input:  ";
	cin >> a >> b >> c;

	if (a > b)
		swap(a, b);
	if (a > c)
		swap(a, c);
	if (b > c)
		swap(b, c);
	cout << "output: " << a << " " << b << " " << c << endl;
}
