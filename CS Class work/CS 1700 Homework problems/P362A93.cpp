//362
//Mark Salisbury
//marks
//P362A93.cpp
//A93. Do Problem 2.55, Pathagorean Triples.

#include <iostream.h>

void main(void){

	for (int i = 1; i < 501; i++){
		for (int j = 1; j < 501; j++){
			for (int k = 1; k < 501; k++){
				if (i * i + j * j == k * k)
					cout << "Side A:" << i << " Side B: " << j << " Hypotenuse: " << k << endl;
			}
		}
	}
}
