//Mark Salisbury
//marks
//P8265A101.cpp
//CS 1720
/*
A101. Write a program that uses Textgraphics and place chessmen in their starting position on 
the board. Use the following: P for pawn, R for rook, N for Knight, B for Bishop, Q for queen, 
and K for King. Put all of your code in one .cpp file.  Be sure to place code at the end of your 
program that will hold the output window open on the screen.  Before turning in your program, 
be sure to execute your program by clicking on the .exe icon

Download chessboard.cpp
*/

#include <iostream.h>

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
#define H_OFFSET	20
#define V_OFFSET	3

char screen[V_SCREEN_SZ][H_SCREEN_SZ + 1];
char chessBoard[8][8];

void clearScreen(); // clears all elements to ' '
void clearChessBoard(); // clears all elements to ' '
void showScreen(); // shows the screen as is stored in memory
void drawHLine(int &, int , int , int , int ); //used by drawGrid
void drawVLine(int &, int , int , bool = false); //used by drawGrid
void drawGrid(); // draws a grid into the screen array
void drawBoard(); // copies the pieces in chessBoard into the screen array
void placePiecesStartingPosition(); // places pieces onto chessBoard
void placePiece(char, int, int);


void showExtended(){
	for (int i = 128; i < 256; i++){
		cout << i << ": " << char(i) << ' ';
		if (i % 8 == 0)
			cout << endl;
	}
}


void main(){
	clearScreen();
	clearChessBoard();
	placePiecesStartingPosition();
	drawGrid();
	showScreen();

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
			hpos = H_OFFSET + column * (H_SPACE + 1) + int(.5 * V_SPACE) + 1;
			if (vpos < H_SCREEN_SZ && hpos < V_SCREEN_SZ)
				screen[ vpos ][ hpos ] = chessBoard[row][column];
		}
	}
}

void placePiecesStartingPosition(){
	for (int i = 0; i < 8; i++){
		placePiece(PAWN, 1, i);
		placePiece(PAWN, 6, i);
		switch (i){
		case 0:
			placePiece(ROOK, 0, i);
			placePiece(ROOK, 7, i);
			break;
		case 1:
			placePiece(KNIGHT, 0, i);
			placePiece(KNIGHT, 7, i);
			break;
		case 2:
			placePiece(BISHOP, 0, i);
			placePiece(BISHOP, 7, i);
			break;
		case 3:
			placePiece(QUEEN, 0, i);
			placePiece(QUEEN, 7, i);
			break;
		case 4:
			placePiece(KING, 0, i);
			placePiece(KING, 7, i);
			break;
		case 5:
			placePiece(BISHOP, 0, i);
			placePiece(BISHOP, 7, i);
			break;
		case 6:
			placePiece(KNIGHT, 0, i);
			placePiece(KNIGHT, 7, i);
			break;
		case 7:
			placePiece(ROOK, 0, i);
			placePiece(ROOK, 7, i);
			break;
		}
	}
}

void placePiece(char piece, int row, int column){
	chessBoard[row][column] = piece;
}
