//Mark Salisbury
//marks
//P8265A111.cpp
//CS 1720
/*
For these problems, put all code for one program in one .cpp file and ftp the .cpp file and also 
a .exe that will execute by clicking on the icon. Be sure to put in the code to hold the window 
open. You thus have 8 files to ftp. ftp the .cpp's in ascii mode and the .exe in binary mode.

A111. The Eight Queens problem is covered in your text, see problems 4.35 and 4.26. Write a 
program that solves the Eight Queens problem recursively as we outlined in class. Have your 
program prompt for the position of the first queen in column 1 and have your program place on 
the screen a solution to the Eight Queens problem using textgraphics. For the non-chess
players this link may help:
*/

#include <iostream.h>
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

#define PAWN		'P'
#define	ROOK		'R' 
#define KNIGHT		'N'
#define BISHOP		'B'
#define QUEEN		'Q'
#define KING		'K'
#define EMPTY_SPACE	' '

#define H_SPACE		3	//number of spaces between each longitudnal line
#define V_SPACE		1	//number of spaces between each latitudnal line  

#define GRIDSIZE	8	//number of rows and columns
	
#define H_SCREEN_SZ	80
#define V_SCREEN_SZ	24

#define V_OFFSET	3
#define H_OFFSET	20

char screen[V_SCREEN_SZ][H_SCREEN_SZ + 1];
char chessBoard[8][8];

static int scalls = 0;

void clearScreen(); // clears all elements to ' '
void clearChessBoard(); // clears all elements to ' '
void showScreen(); // shows the screen as is stored in memory
void drawHLine(int &, int , int , int , int ); //used by drawGrid
void drawVLine(int &, int , int , bool = false); //used by drawGrid
void drawGrid(); // draws a grid into the screen array
void drawBoard(); // copies the pieces in chessBoard into the screen array
void solveProblem(int = 2); //solves the 8 queens problem
bool isSquareSafe(int row, int column, int QueenPosR[]);
void placePiece(char, int, int);

void main(){

	// it is interesting to note that if row 5 is chosen first, then there are only 40 calls 
	// to the check square function.  if row 1 is chosen first, then there are 891 calls.
	clearScreen();
	clearChessBoard();
	drawGrid();
	showScreen();
	int row;
	cout << "What row should the queen in column 1 occupy? ";
	cin >> row;
	while (row < 1 || row > 8){
		cout << "Invalid number.  Valid rows are 1-8.  Please enter another number." << endl;
		cin >> row;
	}
	
	solveProblem(row - 1);
	drawBoard();
	showScreen();
	cout << "Scalls = " << scalls << endl;
	cout << "Press any key to close the program..." << flush;
	while (!kbhit()) { }

}

void solveProblem(int startRow){
	static int currentColumn = 0;
	static int currentRow = startRow;
	static int QueenPosR[8];

	if (isSquareSafe(currentRow, currentColumn, QueenPosR)) {
		placePiece(QUEEN, currentRow, currentColumn);
		QueenPosR[currentColumn] = currentRow;
		currentColumn++;
		currentRow = 0;
	}
	else {
		currentRow++;
		if (currentRow > 7) {// time to backtrack
			currentColumn--;
			currentRow = QueenPosR[currentColumn] + 1;
			placePiece(EMPTY_SPACE, currentRow - 1, currentColumn);
		}
		else
			solveProblem();
	}

	if (currentColumn == 8)
		return;
	else
		solveProblem();
}

bool isSquareSafe(int row, int column, int QueenPosR[]){
	scalls++;
	if (row > 7 || row < 0)
		return false;
	for (int i = 0; i < column; i++){
		if (row == QueenPosR[i])
			return false;
		if (((row - QueenPosR[i]) == (i - column)) || ((row - QueenPosR[i]) == (column - i)))
			return false;
	}
	return true;	
}


void clearScreen(){
	for (int r = 0; r < V_SCREEN_SZ; r++){
		for (int c = 0; c < H_SCREEN_SZ; c++)
			screen[r][c] = ' ';
		screen[r][c] = '\0';
	}
}

void clearChessBoard(){
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			chessBoard[i][j] = ' ';
}

void showScreen(){
	for (int r = 0; r < V_SCREEN_SZ; r++)
		cout << screen[r];
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

void drawVLine(int &vpos, int hpos, int row, bool showSymbols ){
	
	screen[vpos][hpos++] = char(pv);
	int column = 1;
	do {
		for (int i = 0; i < H_SPACE; i++)
			screen[vpos][hpos++] = ((i == H_SPACE / 2) && showSymbols == true ? chessBoard[row - 1][column - 1] : ' '); 
		screen[vpos][hpos++] = char(pv);
		column++;
	} while (column <= GRIDSIZE);
	vpos++;
}

void drawGrid(){
	int vpos = V_OFFSET;
	for (int row = 1; row <= GRIDSIZE; row++){
		if (row == 1)
			drawHLine(vpos, H_OFFSET, p1, p2, p3);
		else
			drawHLine(vpos, H_OFFSET, p4, p5, p6);
		
		for (int i = 0; i < V_SPACE; i++)
			drawVLine(vpos, H_OFFSET, row, (i == V_SPACE / 2 ? true: false));
		
		if (row == GRIDSIZE)
			drawHLine(vpos, H_OFFSET, p7, p8, p9);
		if (vpos > 23) break;
	}

}

void drawBoard(){
	int vpos, hpos;
	for ( int row = 0; row < 8; row++){
		for ( int column = 0; column < 8; column++){
			vpos = V_OFFSET + row * (V_SPACE + 1) + int(.5 * V_SPACE) + 1;
			hpos = H_OFFSET + column * (H_SPACE + 1) + int(.5 * H_SPACE) + 1;
			if (vpos < V_SCREEN_SZ && hpos < H_SCREEN_SZ)
				screen[ vpos ][ hpos ] = chessBoard[row][column];
		}
	}
}

void placePiece(char piece, int row, int column){
	chessBoard[row][column] = piece;
}
