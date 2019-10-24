// 362
// marks
// Mark Salisbury
// P362A102.cpp
//Template functions must be implemented prior to their use, therefore, place the code for your
// template functions before main. 
//A102. (template functions) (min) Read section 3.21 then do problem 3.58 from your text.

#include <iostream.h>

template <class T>
T min(T val1, T val2){
	if (val1 < val2)
		return val1;
	else
		return val2;
}

void main(void){
	int a, b;
	char c, d;
	float e, f;

	cout << "Enter two integers: ";
	cin >> a >> b;
	cout << "The smaller of the two is: " << min(a, b) << endl;
	cout << "Enter two characters: ";
	cin >> c >> d;
	cout << "The smaller of the two is: " << min(c, d) << endl;
	cout << "Enter two floats: ";
	cin >> e >> f;
	cout << "The smaller of the two is: " << min(e, f) << endl;

}

