#include <iostream.h>

class animal{
public:
	void setfeatures(int, int);
	void printfeatures(const animal [][2]);
private:
	int legs;
	int eyes;
};

void animal::setfeatures(int l, int e){
	legs = l;
	eyes = e;
}
void animal::printfeatures(const animal a[][2]){
	cout << "This animal has " << legs << " legs and " << eyes << " eyes." << endl;
	cout << "Animal #4 has " << a[4][0].legs << " legs and " << a[4][0].eyes << " eyes." << endl;
}

void main(void){
	animal toad[50][2];
	toad[0][0].setfeatures(6, 3);
	toad[1][0].setfeatures(4, 2);
	toad[4][0].setfeatures(12, 12);
	toad[0][0].printfeatures(toad);
	toad[1][0].printfeatures(toad);

}