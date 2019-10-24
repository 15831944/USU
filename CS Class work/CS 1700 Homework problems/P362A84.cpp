// 362
// marks
// Mark Salisbury
// P362A84.cpp
//A84. (Guess the Number) Do problem 3.39 from your text*/
#include <iostream.h>
#include <stdlib.h>
#include <time.h>


void main(void){
	int GuessSum = 1;
	int Guess;
	char choice = 'y';

	while (choice == 'y'){
		srand(time(0));

		int Number = ((rand() % 1000) + 1);
		GuessSum = 1;

		cout << "I have a number between 1 and 1000." << endl
			  << "Can you guess my number?" << endl
			  << "Please type your first guess: ";
		cin >> Guess; 
		
		while (Guess != Number){
			if (Guess > Number)
				cout << "Too high. Try again" << endl;
			else
				cout << "Too low. Try again" << endl;
			cout << "Please type another guess: ";
			cin >> Guess;
			GuessSum++;
		}
		
		cout << "Excellent!  You guessed the number in " << GuessSum << " guesses." << endl;
		
		if (GuessSum > 10)
			cout << "You should be able to do better!" << endl;
		if (GuessSum == 10)
			cout << "Ahah!  You know the secret!" << endl;
		else if (GuessSum < 10)
			cout << "Either you know the secret or you got lucky!" << endl;

		cout << "Would you like to play again (y or n)? ";
		cin >> choice;
	}
}




