// 362
// marks
// Mark Salisbury
// P362A72.cpp
//A72. {similiar to 3.42) Amaze your friends by solving the Towers of Hanoi problem. Solve it recursively as shown in the notes and in class. Prompt for the number
//of disks and have your program output the sequence of steps to solve the problem.
#include <iostream.h>

void CheckPause(){
static int LinesOnScreen = 0;
	LinesOnScreen++;
	if (LinesOnScreen > 23){
		cin.get();
		LinesOnScreen = 0;
	}
}
void MoveDisk(char N,char S,char D,char H); 

void main(void){

	const char Disks = 4;
	char Source = 1;
	char Destination = 3;
	char Holding = 2;

	MoveDisk(Disks, Source, Destination, Holding);
	
}

void MoveDisk(char N,char S,char D,char H){
	if (N == 1){
		cout << "Moving disk from " << int(S) << " to " << int(D) << endl;
		//CheckPause();
	}
	else{
		MoveDisk(N - 1, S, H, D);
		MoveDisk(1, S, D, H);
		MoveDisk(N - 1, H, D, S);
	}



}