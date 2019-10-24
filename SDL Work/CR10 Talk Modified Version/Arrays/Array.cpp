#include "..\\Array.h"
#include <iostream.h>

int destructors = 0;
int creators = 0;

class color {
public:
	color(int R = 0, int G = 0, int B = 0);
	color(const color &c);
	~color();
	//void operator delete(void *){
	//	cout << "Delete called" << endl;
	//	//delete this;
	//}
	void showValue(){
		cout << " Red = " << Red ;
		cout << " Green = " << Green ;
		cout << " Blue = " << Blue << endl;
	}

	int Red;
	int Green;
	int Blue;
};

color::color(int R, int G, int B){
	Red = R;
	Green = G;
	Blue = B;
	creators++;
}

color::~color(){
	destructors++;
	//cout << "Destructor called" << endl;
}
// copy constructor
color::color(const color &c){
	int bytesToCopy = sizeof(color);
	memcpy(this,&c,bytesToCopy);
	creators++;
}

void main(){
	/*
	Array<double> intArray(20);
	intArray[5] = 5.067;
	intArray[4] = 3.023;
	cout << intArray[5] << endl;
	intArray[5] = 10.045;
	cout << intArray[5] << endl;
	intArray(12);
	intArray[5] = intArray[4];
	intArray[4] = 20.09;
	cout << intArray[5] << endl;
	cout << intArray[4] << endl;
	cout << "Length = " << intArray.length << endl;
	*/
	
	Array<color> myColors(6);
	cout << "Color 0: ";
	myColors[0] = color(12,45,69);
	myColors[0].showValue();
	myColors[4] = myColors[0];
	myColors[4].Blue = 25;
	cout << "Color 5: ";
	myColors[5].showValue();
	cout << endl;
	for (int wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor << ": "; 
		myColors[wColor].showValue();
	}
	cout << "sizeof(myColors)="<<sizeof(myColors)<<endl;
	myColors.Insert(color(12,34,56),0);
	cout << endl;
	myColors(10);
	for (wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor << ": "; 
		myColors[wColor].showValue();
	}
	cout << endl;
	myColors.Remove(2, 3);
	myColors.Remove(3, 4);
	myColors[20] = color(12,90,43);
	myColors[21] = color(12,15,21);

	for (wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor << ": "; 
		myColors[wColor].showValue();
	}

	/*
	myColors.Remove(3);
	for (wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor << ": "; 
		myColors[wColor].showValue();
	}
	myColors.Remove(4);
	for (wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor << ": "; 
		myColors[wColor].showValue();
	}
	for (wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor << ": "; 
		myColors[wColor].showValue();
	}
	cout << "sizeof(myColors)="<<sizeof(myColors)<<endl;
	*/
	/*
	myColors(20);
	for (wColor = 0; wColor < myColors.length; wColor++){
		cout << "Color " << wColor; 
		myColors[wColor].showValue();
	}
	*/

	
	//Test to see if I can eat up system memory
	
	/*
	for (int j = 0; j < 400; j++){
		cout << "j = " << j << endl;
		for (int i = 0; i < 100000; i++){
			
			//MyColors[i] = color(12,34,56);
			//if (i % 100 == 0)
			//MyColors(100000 + i / 100);
			
			MyColors.Insert(color(12,34,56),0);
			MyColors.Remove(1);
		}
	}
	*/
	/*
	Array<color> *colors;
	for (int i = 0; i < 200000; i++){
		colors = new Array<color>(100);
		for (int j = 0; j < 100; j++){
			(*colors)[j] = color(10,20,30);
		}
		//cout << "i=" << i << endl;
		delete colors;
	}*/
	myColors(0);
	myColors(0);
	cout << "Destructors=" << destructors << endl;
	cout << "Creators=" << creators << endl;
	
	
}