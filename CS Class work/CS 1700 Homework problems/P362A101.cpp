// 362
// marks
// Mark Salisbury
// P362A101.cpp
//  Sorry these are late.  I had them done last week but forgot to turn them in yesterday.  
//A101. (Craps) Read section 3.9 and then do problem 3.54 from your text. 

// Fig. 3.10: fig03_10.cpp
// Craps
#include <iostream.h>
#include <stdlib.h>
#include <time.h>

int rollDice( void );  // function prototype

enum Status { CONTINUE, WON, LOST };
Status game( void );
void printMessage(Status thisgame, int prevcredits, int credits, int bet);

void main( void ){
	int credits, bet, prevcredits;
	char response;
	Status thisgame;
	
	do {

		credits = 1000;
		cout << "Welcome to craps.  Today might just be your lucky day." << endl;

		do {
			cout << "You have " << credits << " dollars in credits." << endl;
			cout << "How much would you like to wager? ";
			cin >> bet;
			while (bet > credits || bet < 0){
				cout << "Your wager must be greater than zero and not greater than your credits." << endl
					  << "Enter a new wager: ";
				cin >> bet;
			}

			prevcredits = credits;

			thisgame = game();
			if (thisgame == WON)
				credits += bet;
			else
				credits -= bet;
			
			cout << "Your credits are " << credits << " dollars." << endl;
			
			printMessage(thisgame, prevcredits, credits, bet);
			
			if (credits > 0){
				cout << "Would you like to make another wager? (y/n) ";
				cin >> response;
				while (response != 'y' && response != 'Y' && response != 'n' && response != 'N'){
					cout << "Invalid response entered.  Valid response are y or n." << endl;
					cin >> response;
				}
			}
			else 
				cout << "Sorry.  You busted!" << endl;

		} while ((response == 'y' || response == 'Y') && credits > 0);
		
		cout << "Would you like to play again? (y/n) ";
		cin >> response;
		while (response != 'y' && response != 'Y' && response != 'n' && response != 'N'){
			cout << "Invalid response entered.  Valid response are y or n." << endl;
			cin >> response;
		}
		
		cout << endl;
	
	} while (response == 'y' || response == 'Y');
}

int rollDice( void )
{
   int die1, die2, workSum;

   die1 = 1 + rand() % 6;
   die2 = 1 + rand() % 6;
   workSum = die1 + die2;
   cout << "Player rolled " << die1 << " + " << die2
        << " = " << workSum << endl;

   return workSum;
}

Status game( void ){

   int sum, myPoint;
   Status gameStatus;

   srand( time( NULL ) );
   sum = rollDice();            // first roll of the dice

   switch ( sum ) {
      case 7: 
	  case 11:                  // win on first roll
         gameStatus = WON;
         break;
      case 2: 
	   case 3: 
	   case 12:                 // lose on first roll
         gameStatus = LOST;
         break;
      default:                 // remember point
         gameStatus = CONTINUE;
         myPoint = sum;
         cout << "Point is " << myPoint << endl;
         break;                // optional   
   }

   while ( gameStatus == CONTINUE ) {    // keep rolling
      sum = rollDice();

      if ( sum == myPoint )       // win by making point
         gameStatus = WON;
      else
         if ( sum == 7 )          // lose by rolling 7
            gameStatus = LOST;
   }

   if ( gameStatus == WON )
      cout << "Player wins" << endl;
   else
      cout << "Player loses" << endl;

   return gameStatus;
}

void printMessage(Status thisgame, int prevcredits, int credits, int bet){
	int message;
	if (thisgame == WON){
		if (prevcredits / bet > 4)
			message = rand() % 2 + 1;
		else if (credits > 5000)
			message = rand() % 4 + 4;
		else	
			message = rand() % 3 + 3;

		switch(message){
		case 1:
			cout << "You're too conservative.  Take a chance." << endl;
			break;
		case 2:
			cout << "Aw cmon, take a chance." << endl;
			break;
		case 3:
			cout << "Life's short. Live it up." << endl;
			break;
		case 4:
			cout << "Show me the money!" << endl;
			break;
		case 5:
			cout << "Oh yeah baby.  You're on a roll!" << endl;
			break;
		case 6:
			cout << "You're up big. Now's the time to cash in your chips" << endl;
			break;
		case 7:
			cout << "Money! Money! Money! Give me mo' money!" << endl;
			break;
		}
	}
	else{
		message = rand() % 3 + 1;
		switch(message){
		case 1:
			cout << "Oh, you're going for broke huh?" << endl;
			break;
		case 2:
			cout << "Keep playing like this and you'll be cleaning toilets soon." << endl;
			break;
		case 3:
			cout << "Sucks to be you!" << endl;
			break;
		case 4:
			cout << "My mother can roll better than that!" << endl;
			break;
		}
	}
}
