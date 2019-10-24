#include <iostream.h>

void Print(char carray[], int max){
	for (int i = 0; i < max; i++)
		cout << carray[i] << endl;
}

void Initialize(char alpha[], int max){
	for (int i = 0; i < max; i++)
		alpha[i] = 'a' + i;
}

void main(){

	char Alphabet[26];
	Initialize(Alphabet, 26);
	Print(Alphabet, 26);

}
