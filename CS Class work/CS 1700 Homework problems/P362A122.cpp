// 362
// marks
// Mark Salisbury
// P362A122.cpp

/*
A122. Utilize the screen for text graphics by implementing a function 
InitializeChessboard that will place all 32 chess pieces in their correct 
starting positions. Use the following:

P - pawn
R - rook
N - knight
B - bishop
Q - queen
K - king */

// chessboard.cpp
// a program to display a chessboard for the 8 queens problem
// programmed by Larre Egbert 5/9/97

#include<iostream.h>
#include<stdio.h> // for getchar()
const int NumRows = 24;
const int NumColumns = 80;

typedef char MonitorScreen[NumRows][NumColumns];

const int offset = 20;

void Initialize(MonitorScreen);
void Display(MonitorScreen);
void DrawBox(MonitorScreen,int Top,int Left,int Bottom, int Right,char FillChar);
void DrawChessBoard(MonitorScreen);
void InitializeChessBoard(MonitorScreen);

void main(void)
{
    MonitorScreen Board;
    Initialize(Board);
    DrawChessBoard(Board);
       
	InitializeChessBoard(Board);
	Display(Board);
}

void Initialize(MonitorScreen Board)
{
    for(int row = 0; row < NumRows; row++)
        for(int col = 0; col < NumColumns; col++)
            Board[row][col] = ' ';
}

void Display(MonitorScreen Board)
{
    for(int row = 0; row < NumRows; row++)
    {
        for(int col = 0; col < NumColumns; col++)
        cout.put(Board[row][col]);
    }
// use the following to hold the screen in Borland 5.0.
// cout<< "Click in the window and press any key to continue.";
// char c = getchar();
}

void DrawBox(MonitorScreen Board, int Top, int Left, int Bottom, int Right, char FillChar)
{
    for(int col = Left; col <= Right; col++)
        Board[Top][col] = Board[Bottom][col] = FillChar;

    for(int row = Top; row <= Bottom; row++)
        Board[row][Left] = Board[row][Right] = FillChar;
}

void DrawChessBoard(MonitorScreen Board)
{
    for(int row = 2; row < 8*3; row+=3) // draw Horiz lines
        for(int col=offset+0; col < offset+8*5; col++)
            Board[row][col] = '_';

    for(int col = offset; col <= offset+8*5; col += 5) // draw vert lines
        for(int row = 0; row < 8*3; row++)
            Board[row][col] = '|';
}

void InitializeChessBoard(MonitorScreen Board)
{
    int drow, dcol;
	for(int row = 0; row < 8; row++){
        for(int col = 0; col < 8; col++){
            drow = 1 + row * 3;
			dcol = offset + 2 + col * 5;
			if (row == 0 || row == 7){
				switch(col){
					case 0: 
						Board[drow][dcol] = 'R';
						break;
					case 1: 
						Board[drow][dcol] = 'N';
						break;
					case 2: 
						Board[drow][dcol] = 'B';
						break;
					case 3: 
						Board[drow][dcol] = 'Q';
						break;
					case 4: 
						Board[drow][dcol] = 'K';
						break;
					case 5: 
						Board[drow][dcol] = 'B';
						break;
					case 6: 
						Board[drow][dcol] = 'N';
						break;
					case 7: 
						Board[drow][dcol] = 'R';
						break;
				}
			}
			else if(row == 1 || row == 6){
				Board[drow][dcol] = 'P';
			}
		}
	}
}
