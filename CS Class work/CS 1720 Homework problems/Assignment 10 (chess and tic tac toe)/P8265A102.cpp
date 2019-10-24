//Mark Salisbury
//marks
//P8265A102.cpp
//CS 1720

/*
A102. Write a program that uses Textgraphics and will play a game of Tic-Tac-Toe, one player 
against another player. Have each player input their play by indicating the row and column of 
the Tic-Tac-Toe board, also allow the option for one person to play against the computer with 
either the computer or the person making the first move. Put all of your code in one .cpp file.
Be sure to place code at the end of your program that will hold the output window open on the 
screen.  Before turning in your program, be sure to execute your program by clicking on the 
.exe icon
*/


#include <iostream.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define	p1			218
#define	p2			194
#define	p3			191
#define	p4			195
#define	p5			197
#define	p6			180
#define	p7			192
#define	p8			193
#define	p9			217
#define ph			196
#define pv			179

#define H_SPACE		5	//number of spaces between each longitudnal line
#define V_SPACE		3	//number of spaces between each latitudnal line  

#define GRIDSIZE	3	//number of rows and columns
	
#define H_SCREEN_SZ	80
#define V_SCREEN_SZ	24
#define H_OFFSET	8
#define V_OFFSET	7

char screen[V_SCREEN_SZ][H_SCREEN_SZ + 1];
char Board[GRIDSIZE][GRIDSIZE];

char startGame(char, int &, char [], char []);
bool checkValidMoveH(int &r, int &c);
bool checkValidMoveC(int r, int c);
char checkForWin(int r = 4, int c = 4, char g = 'X');
void clearScreen(); // clears all elements to ' '
void clearBoard(); // clears all elements to ' '
void showScreen(); // shows the screen as is stored in memory
void drawHLine(int &, int , int , int , int ); //used by drawGrid
void drawVLine(int &, int , int); //used by drawGrid
void drawGrid(); // draws a grid into the screen array
void drawBoard(); // copies the pieces in the Board into the screen array
void placePiece(char, int, int);

void main(){
	
	bool gameover = false;
	bool playAgain;
	double wait;
	char gametype = 'N';
	char prevgametype = '\0';
	int curPlayer;
	int row, column;
	char p1Marker, p2Marker;
	char winner = '\0';
	char p1Name[20];
	char p2Name[20];

	time_t   loopstart, curtime;
	int movesMade;
	char c;
	int lc = 4;
	int lr = 4;
	int p1wins = 0, p2wins = 0;


	srand(time(0));
   
	clearScreen();
	drawGrid();
	
	while (gameover == false){
		clearBoard();
		drawBoard();
		prevgametype = gametype;
		gametype = startGame(gametype, curPlayer, p1Name, p2Name);
		
		if (gametype != prevgametype){ // a new type of game was started.
			p1wins = 0;
			p2wins = 0;
		}

		if ( curPlayer == 0 ){
			p1Marker = 'X';
			p2Marker = 'O';
		}
		else{
			p1Marker = 'O';
			p2Marker = 'X';
		}
		movesMade = 0;

		while (gameover == false){
			showScreen();
			time( &loopstart );
			winner = checkForWin();
			if (winner != 0 || movesMade == 9){ // the game is over
				if (movesMade == 9 && winner == '\0'){ // it's a tie
					cout << "Draw.  No one won." << endl;
				}
				else if (p1Marker == 'X' && winner == 'X' || p1Marker == 'O' && winner == 'O'){
					if (gametype == 'H')
						cout << p1Name << " is the winner!" << endl;
					else
						cout << "You are the winner!" << endl;
					p1wins++;
				}
				else{
					if (gametype == 'H')
						cout << p2Name << " is the winner!" << endl;
					else
						cout << "The computer is the winner!" << endl;
					p2wins++;
				}
				cout << ( gametype == 'H' ? p1Name : "You " ) 
					 << ( gametype == 'H' ? " has " : " have " ) << p1wins << " wins and " 
					 << ( gametype == 'H' ? p2Name : "the computer" ) << " has " 
					 << p2wins << " wins." << endl;
				cout << "Would you like to play again? (enter Y or N) ";
				if (cin.peek() != EOF){
					cin.ignore();
				}
				cin >> c;
				c = toupper(c);
				while (c != 'Y' && c != 'N'){
					cout << "Invalid input.  Enter Y or N. ";
					cin >> c;
					c = toupper(c);
				}
				if (c == 'Y')
					playAgain = true;
				else
					playAgain = false;
				gameover = true;
				
			}
			
			if (gameover == true)
				break;

			if (curPlayer == 0){
				cout << p1Name << ", please enter the row and column of your move: ";
				cin >> row >> column;
				row--;
				column--;
				checkValidMoveH(row, column);
				placePiece(p1Marker, row, column);
				lr = row;
				lc = column;
			
			}
			else{
				if (gametype == 'H'){
					cout << p2Name << ", please enter the row and column of your move: ";
					cin >> row >> column;
					row--;
					column--;
					checkValidMoveH(row, column);
					placePiece(p2Marker, row, column);
				}
				else {
					wait = 1.0 + double( rand() % 10 ) / 5;
					cout << "Computer: I'm making my move now..." << endl;
					row = 4;
					column = 4;
					
					// check for way to win
					for (int r = 0; r < 3; r++){
						for(int c = 0; c < 3; c++){
							if (checkForWin(r, c, p2Marker) == p2Marker){
								row = r;
								column = c;
							}
						}
					}
					// check to block other players move
					for (r = 0; r < 3 && row == 4; r++){
						for(c = 0; c < 3; c++){
							if (checkForWin(r, c, p1Marker) == p1Marker){
								row = r;
								column = c;
							}
						}
					}
					if (row == 4){
						if (((lr + lc) % 2 == 0 && movesMade != 0 && movesMade != 2) && !(movesMade == 1 && lr == 1 && lc == 1)){ // player one's last move was in a corner or the middle
							//try middle
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
							if (checkValidMoveC(1, 1) && (movesMade != 0 || movesMade != 2)){
							// check for the middle
								row = 1;
								column = 1;
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
					
					do { time ( &curtime ); }
					while (difftime( curtime, loopstart ) < wait);

				}
			}
			
			curPlayer = (curPlayer == 1 ? 0 : 1);
			movesMade++;
			drawBoard();
		} // while gameover == false

		if (playAgain == true)
			gameover = false;
	} // while gameover == false
	
}
  
char startGame(char c, int &curPlayer, char p1N[], char p2N[]){
	char prevc = c;
	do {
		showScreen();
		cout << "What type of game would you like to play?" << endl
			 << "To play against the computer, enter C.   " << endl
			 << "To play against another human, enter H.  " << endl;
		cin >> c;
		c = toupper(c);
	} while (c != 'C' && c != 'H');
	
	curPlayer = rand() % 2;

	if (c != prevc) {
		cout << "Please enter player 1's name: ";
		cin.ignore();
		cin.getline(p1N, 19, '\n');
	}
	
	if (c == 'H'){
		if (c != prevc){
			cout << "Please enter player 2's name: ";
			cin.getline(p2N, 19, '\n');
		}
		if (curPlayer == 1)
			cout << p2N << " will go first." << endl;
		else
			cout << p1N << " will go first." << endl;
	} 
	else { 
		if (curPlayer == 1)
			cout << "The computer will go first." << endl;
		else
			cout << "You will go first." << endl;
	}
	cout << "Press any key to continue..." << endl;
	while (!kbhit()) {}
	cin.ignore();
	cout << endl;
	return c;
}

bool checkValidMoveH(int &r, int &c){
	while ( r < 0 || r > 2 || c < 0 || c > 2 || Board[r][c] != ' '){
		cout << endl << "Invalid move.  Enter a different move (row, column): ";
		if (cin.peek() != EOF){
			cin.ignore();
		}
		cin >> r >> c;
		r--;
		c--;
	}
	return true;
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

void clearScreen(){
	for (int r = 0; r < V_SCREEN_SZ; r++){
		for (int c = 0; c < H_SCREEN_SZ; c++)
			screen[r][c] = ' ';
		screen[r][c] = '\0';
	}
}

void clearBoard(){
	for (int i = 0; i < GRIDSIZE; i++)
		for (int j = 0; j < GRIDSIZE; j++)
			Board[i][j] = ' ';
}

void showScreen(){
	for (int r = 0; r < V_SCREEN_SZ; r++){
		cout << screen[r];
		if (strlen(screen[r]) < H_SCREEN_SZ)
			cout << endl;
	}
}

void drawHLine(int &vpos, int hpos, int a, int b, int c){
	screen[vpos][hpos++] = char(a);
	
	for (int i = 0; i < H_SPACE; i++)
		screen[vpos][hpos++] = char(ph);

	for (int column = 1; column < GRIDSIZE; column++){
		screen[vpos][hpos++] = char(b);
		for (int i = 0; i < H_SPACE; i++)
			screen[vpos][hpos++] = char(ph);
	}
	screen[vpos][hpos++] = char(c);
	vpos++;
}

void drawVLine(int &vpos, int hpos, int row ){
	
	screen[vpos][hpos++] = char(pv);
	int column = 1;
	do {
		for (int i = 0; i < H_SPACE; i++)
			screen[vpos][hpos++] = ' '; 
		screen[vpos][hpos++] = char(pv);
		column++;
	} while (column <= GRIDSIZE);
	vpos++;
}

void drawGrid(){
	int vpos = V_OFFSET;
	if (V_OFFSET > 0)
		strcpy(screen[V_OFFSET - 1], "            Tic-Tac-Toe"); 
	for (int row = 1; row <= GRIDSIZE; row++){
		if (row == 1)
			drawHLine(vpos, H_OFFSET, p1, p2, p3);
		else
			drawHLine(vpos, H_OFFSET, p4, p5, p6);
		
		for (int i = 0; i < V_SPACE; i++)
			drawVLine(vpos, H_OFFSET, row);
		
		if (row == GRIDSIZE)
			drawHLine(vpos, H_OFFSET, p7, p8, p9);
		if (vpos > 23) break;
	}

}

void drawBoard(){
	int vpos, hpos;
	for ( int row = 0; row < GRIDSIZE; row++){
		for ( int column = 0; column < GRIDSIZE; column++){
			vpos = V_OFFSET + row * (V_SPACE + 1) + int(.5 * V_SPACE) + 1;
			hpos = H_OFFSET + column * (H_SPACE + 1) + int(.5 * V_SPACE) + 2;
			if (vpos < H_SCREEN_SZ && hpos < V_SCREEN_SZ)
				screen[ vpos ][ hpos ] = Board[row][column];
		}
	}
}


void placePiece(char piece, int row, int column){
	Board[row][column] = piece;
}
