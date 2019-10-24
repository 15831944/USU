#include <iostream.h>

class myClass {
public:
	myClass(int, int);
	myClass * GetSomething();
	myClass(myClass *);
protected:
	int &x;
	int &y;
};

myClass::myClass(int a, int b) : x(a), y(a) {

}

myClass::myClass(myClass *myClassObject){
	x = new int;
	y = new int;
	x = myClassObject->x;
	y = myClassObject->y;
}

myClass * myClass::GetSomething(){
	return this;
}

class mySubClass : public myClass {
public:
	mySubClass(double = 50.0);
	void printValues();
	void setz(double);
private:
	double z;
};

mySubClass::mySubClass(double a)
: myClass(10, 11) {
	z = a;
}

mySubClass::mySubClass(myClass * myClassPtr, double a)
:myClass(* myClassPtr){
	z = a;
}


void mySubClass::printValues(){
	cout << "x = " << x << " y = " << y << endl;
	cout << "z = " << z << endl;

}

void mySubClass::setz(double a) {
	z = a;
}

void main(){

	myClass q(4, 6);
	
	//mySubClass * mySubClassPtr;
	
	mySubClass * mySubClassPtr(q.GetSomething(), 9.5);
	

	mySubClassPtr->setz(56.3);
	mySubClassPtr->printValues();
	
}
