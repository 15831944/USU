// 362
// marks
// Mark Salisbury
// P362A83.cpp
// A83. (Coin Toss) Do problem 3.34 from your text.

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

int flip(void);

void main(void){
	int Tosses = 100;
	int HeadSum = 0;
	int TailSum = 0;

	srand(time(0));

	for (int i = 0; i < Tosses; i++){
		if (flip()){
			HeadSum++;
			cout << "Heads" << endl;}
		else{
			TailSum++;
			cout << "Tails" << endl;}
	}
	
	cout << "Heads was flipped " << HeadSum << " times and " << endl
		  << "tails was flipped " << TailSum << " times." << endl;
}

int flip(void){
	if ((rand() % 2) == 0) 
		return (1);
	else
		return (0);
}


