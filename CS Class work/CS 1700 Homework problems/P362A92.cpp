// 362
// marks
// Mark Salisbury
// P362A92.cpp
//A92. Do Problem 2.47, the extra credit part. It says "Combine your code from the four separate problems into a single program that prints all four patterns side by
//side making clever use of nested for loops.

#include <iostream.h>

void PrintChars(int, int, char, char);

void main(){
	for (int i = 1; i <= 10; i++){
		PrintChars(i, 10 - i, '*',' ');
		PrintChars(11 - i, i - 1, '*',' ');
		PrintChars(i - 1, 11 - i, ' ','*');
		PrintChars(10 - i, i, ' ','*');
		cout << endl;
	}
}

void PrintChars(int j, int k, char c, char d){
	for (int i = 0; i < j; i++)
		cout << c;
	for (i = 0; i < k; i++)
		cout << d;
}