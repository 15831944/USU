// 362
// marks
// Mark Salisbury
// P362A103.cpp
//Template functions must be implemented prior to their use, therefore, place the code for your
// template functions before main. 
//A103. (template functions) (max) do problem 3.59 from your text.

#include <iostream.h>

template <class T>
T max(T val1, T val2, T val3){
	if ((val1 > val2) && (val1 > val3))
		return val1;
	else if ((val2 > val1) && (val2 > val3))
		return val2;
	else
		return val3;
}

void main(void){
	int a[3];
	char b[3];
	float c[3];

	cout << "Enter three integers: ";
	cin >> a[0] >> a[1] >> a[2];
	cout << "The largest of them is: " << max(a[0], a[1], a[2]) << endl;
	cout << "Enter three characters: ";
	cin >> b[0] >> b[1] >> b[2];
	cout << "The largest of them is: " << max(b[0], b[1], b[2]) << endl;
	cout << "Enter three floats: ";
	cin >> c[0] >> c[1] >> c[2];
	cout << "The largest of them is: " << max(c[0], c[1], c[2]) << endl;

}

