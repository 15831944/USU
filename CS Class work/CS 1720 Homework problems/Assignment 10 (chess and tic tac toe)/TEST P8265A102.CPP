
#include <iostream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define GRIDSIZE		3

char Board[GRIDSIZE][GRIDSIZE];

void startGame(int &);
bool checkValidMoveC(int r, int c);
char checkForWin(int r = 4, int c = 4, char g = 'X');
void clearBoard(); // clears all elements to ' '
void placePiece(char, int, int);
void checkWayToWin( int &, int &, char );

void main(){
	
	bool gameover = false;
	bool useLogic = true;
	int curPlayer;
	int row, column;
	char p1Marker, p2Marker;
	char winner = '\0';
	int movesMade;
	int p1Wins = 0, p2Wins = 0, drawGames = 0;
	int p1WentFirstWins = 0, p2WentFirstWins = 0;
	int p1WentSecondWins = 0, p2WentSecondWins = 0;
	int gamesToPlay = 100000, gamesPlayed = 0;
	time_t   loopstart, curtime;
	
	int lc = 4;
	int lr = 4;
	int lc1 = 4;
	int lr1 = 4;

	int pdmiddlewins = 0;
	int pdmiddleloses = 0;
	bool pdmiddle;

	srand(time(0));
	time ( &loopstart );
   
	
	while (gamesPlayed < gamesToPlay){
		clearBoard();
		startGame(curPlayer);
		gameover = false;
		
		if ( curPlayer == 0 ){
			p1Marker = 'X';
			p2Marker = 'O';
		}
		else{
			p1Marker = 'O';
			p2Marker = 'X';
		}
		movesMade = 0;
		pdmiddle = false;

		while (gameover == false){
			
			winner = checkForWin();
			if (winner != 0 || movesMade == 9){ // the game is over
				gamesPlayed++;
				if (movesMade == 9 && winner == '\0'){ // it's a tie
					drawGames++;
				}
				else if (p1Marker == 'X' && winner == 'X' || p1Marker == 'O' && winner == 'O'){
					p1Wins++;
					if (pdmiddle == true)
						pdmiddleloses++;

					if (p1Marker == 'X') 
						p1WentFirstWins++; 
					else 
						p1WentSecondWins++;
				}
				else{
					p2Wins++;
					if (pdmiddle == true)
						pdmiddlewins++;

					if (p2Marker == 'X') 
						p2WentFirstWins++; 
					else 
						p2WentSecondWins++;
				}
				gameover = true;
			
			}
			
			if (gameover == true)
				break;

			if (curPlayer == 0){
				
				row = 4;
				column = 4;
				
				//find a way to win
				checkWayToWin(row, column, p1Marker);
				
				//find a way to block the other player from winning
				if (row == 4)
					checkWayToWin(row, column, p2Marker);

				if (useLogic == true){
					if (row == 4){
						if (((lr1 + lc1) % 2 == 0 && movesMade % 2 != 0) && !(movesMade == 1 && lr1 == 1 && lc1 == 1)){ 
							// player 1 either made a move in a corner or middle and
							// player 1 went first and 
							// player one's first move wasn't in the middle
							// try middle
							if (checkValidMoveC(1, 1)){
								// check for the middle
								row = 1;
								column = 1;
							}
							else{
								//try and find a valid move on the sides
								
								int hmove = (rand() % 2) * 2 - 1;
								int vmove = (rand() % 2) * 2 - 1;
								if (!checkValidMoveC(1, 1 + hmove)){
									if (!checkValidMoveC(1, 1 - hmove)){
										if (!checkValidMoveC(1 + vmove, 1)){
											if (checkValidMoveC(1 - vmove, 1)){
												row = 1 - vmove;
												column = 1;
											}
										}
										else{
											row = 1 + vmove;
											column = 1;
										}
									}
									else{
										row = 1;
										column = 1 - hmove;
									}
								}
								else{
									row = 1;
									column = 1 + hmove;
								}
							
							  
							}
							
						}
						else{ //players last move was on a side
							//try for a corner
							if (checkValidMoveC(1, 1) && (movesMade != 0 || rand() % 4 == 0)){
								// check for the middle
									row = 1;
									column = 1;
							}
							else if (checkValidMoveC(0,0) || checkValidMoveC(2,0)
								|| checkValidMoveC(0,2) || checkValidMoveC(2,2)){
								if ((Board[0][0] == p1Marker) && checkValidMoveC(2, 2)){
									row = 2; column = 2;
								}
								else if ((Board[2][2] == p1Marker) && checkValidMoveC(0, 0)){
									row = 0; column = 0;
								}
								else if ((Board[0][2] == p1Marker) && checkValidMoveC(2, 0)){
									row = 2; column = 0;
								}
								else if ((Board[2][0] == p1Marker) && checkValidMoveC(0, 2)){
									row = 0; column = 2;
								}
								else {
									do {
										row = (rand() % 2) * 2;
										column = (rand() % 2) * 2;
									} while(!checkValidMoveC(row, column));
								}							
							}
						}
					}
				}// if useLogic == true

				if (row == 4){
					//no good move has been found.  find a move randomly
					if(!checkValidMoveC(row, column)){
						do{
							row = rand() % 3;
							column = rand() % 3;
						}while(!checkValidMoveC(row, column));
					}
				}
				placePiece(p1Marker, row, column);
				lr = row;
				lc = column;
			
			}
			else{
				row = 4;
				column = 4;
					
				//find a way to win
				checkWayToWin(row, column, p2Marker);
				
				//find a way to block the other player from winning
				if (row == 4)
					checkWayToWin(row, column, p1Marker);
			
				
				if (row == 4){
					if (((lr + lc) % 2 == 0 && movesMade % 2 != 0) && !(movesMade == 1 && lr == 1 && lc == 1)){ 
						// player 1 either made a move in a corner or middle and
						// player 1 went first and 
						// player one's first move wasn't in the middle
						// try middle
						if (checkValidMoveC(1, 1)){
							// check for the middle
							row = 1;
							column = 1;

						}
						else{
							//try and find a valid move on the sides
							
							int hmove = (rand() % 2) * 2 - 1;
							int vmove = (rand() % 2) * 2 - 1;
							if (!checkValidMoveC(1, 1 + hmove)){
								if (!checkValidMoveC(1, 1 - hmove)){
									if (!checkValidMoveC(1 + vmove, 1)){
										if (checkValidMoveC(1 - vmove, 1)){
											row = 1 - vmove;
											column = 1;
										}
									}
									else{
										row = 1 + vmove;
										column = 1;
									}
								}
								else{
									row = 1;
									column = 1 - hmove;
								}
							}
							else{
								row = 1;
								column = 1 + hmove;
							}
						
						  
						}
						
					}
					else{ //players last move was on a side
						//try for a corner
						if (checkValidMoveC(1, 1)){
							// check for the middle
								row = 1;
								column = 1;
								pdmiddle = true;
						}
						else if (checkValidMoveC(0,0) || checkValidMoveC(2,0)
							|| checkValidMoveC(0,2) || checkValidMoveC(2,2)){
							if ((Board[0][0] == p2Marker) && checkValidMoveC(2, 2)){
								row = 2; column = 2;
							}
							else if ((Board[2][2] == p2Marker) && checkValidMoveC(0, 0)){
								row = 0; column = 0;
							}
							else if ((Board[0][2] == p2Marker) && checkValidMoveC(2, 0)){
								row = 2; column = 0;
							}
							else if ((Board[2][0] == p2Marker) && checkValidMoveC(0, 2)){
								row = 0; column = 2;
							}
							
							else {
								do {
									row = (rand() % 2) * 2;
									column = (rand() % 2) * 2;
								} while(!checkValidMoveC(row, column));
							}							
						}
					}	
					//no good move has been found.  find a move randomly
					if(!checkValidMoveC(row, column)){
						do{
							row = rand() % 3;
							column = rand() % 3;
						}while(!checkValidMoveC(row, column));
					}
				}
				
				placePiece(p2Marker, row, column);
				lr1 = row;
				lc1 = column;
			}
			
			curPlayer = (curPlayer == 1 ? 0 : 1);
			movesMade++;
		
		} // while gameover == false

	} // while gamesPlayed < gamesToPlay
	time ( &curtime );
	cout << endl << gamesPlayed << " games were played in " << difftime( curtime, loopstart ) 
		 << " seconds." << endl;
	cout << drawGames << " games resulted in a draw. " << endl << endl;
	cout << "Player 1, the computer using " << (useLogic == true ? "pre-programmed" : "random" ) 
		 << " logic, had " << p1Wins << " wins." << endl;
	cout << p1WentFirstWins << " wins were made with player 1 making the starting move." << endl;
	cout << p1WentSecondWins << " wins were made with player 1 making the second move." << endl << endl;

	cout << "Player 2, the computer using pre-programmed logic, had " << p2Wins << " wins." << endl;
	cout << p2WentFirstWins << " wins were made with player 2 making the starting move." << endl;
	cout << p2WentSecondWins << " wins were made with player 2 making the second move." << endl << endl;

	cout << "The number of wins for player 2 after he could put down in the middle was " <<
		 pdmiddlewins << ".  The number of loses was " << pdmiddleloses << endl;
	
}
  
void startGame(int &curPlayer){
	curPlayer = rand() % 2;
}

bool checkValidMoveC(int r, int c){
	return ( r >= 0 && r < 3 && c >= 0 && c < 3 && Board[r][c] == ' ');
}

char checkForWin(int r, int c, char g){
	int w[8];
	char temp;
	if (r < 4 && Board[r][c] != ' ')
		return char(0);
	else if (r < 4 && Board[r][c] == ' '){ // setting r and c equal to a row or column can be used to test for a possible victory
		temp = Board[r][c];
		Board[r][c] = g;
	}
	w[0] = Board[0][0] + Board[0][1] + Board[0][2];
	w[1] = Board[1][0] + Board[1][1] + Board[1][2];
	w[2] = Board[2][0] + Board[2][1] + Board[2][2];
	w[3] = Board[0][0] + Board[1][0] + Board[2][0];
	w[4] = Board[0][1] + Board[1][1] + Board[2][1];
	w[5] = Board[0][2] + Board[1][2] + Board[2][2];
	w[6] = Board[0][0] + Board[1][1] + Board[2][2];
	w[7] = Board[0][2] + Board[1][1] + Board[2][0];
	if (r < 4){
		Board[r][c] = temp;
	}
	for ( int i = 0; i < 8; i++) {
		if (w[i] == 'X' * 3 || w[i] == 'O' * 3)
			return char(w[i] / 3);
	}
	return char(0);	
}

void clearBoard(){
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			Board[i][j] = ' ';
}

void placePiece(char piece, int row, int column){
	Board[row][column] = piece;
}

void checkWayToWin( int &row, int &column, char marker){
	for (int r = 0; r < 3; r++){
		for(int c = 0; c < 3; c++){
			if (checkForWin(r, c, marker) == marker){
				row = r;
				column = c;
				return;
			}
		}
	}
}