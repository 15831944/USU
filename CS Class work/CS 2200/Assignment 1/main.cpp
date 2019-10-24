#include <iostream.h>

int solutions = 0;

bool IsSquareSafe(int Row, int Col,int QueenRow[]){
	for (int whichQueen = 0; whichQueen < Col; whichQueen++){
		if (QueenRow[whichQueen] == Row)
			return false;
		if (Row - QueenRow[whichQueen] == Col - whichQueen ||
			QueenRow[whichQueen] - Row == Col - whichQueen )
			return false;
	}
	return true;
}

void Solve8Queens(int QueensPos[] = NULL, int CurrColumn = 0){

	cout << "CurrColumn " << CurrColumn << endl;
	for (int Row = 0; Row < 8; Row++){
	
		if (IsSquareSafe(Row, CurrColumn, QueensPos)){
			int QueenRow[8];
			for (int i = 0; i < CurrColumn; i++)
				QueenRow[i] = QueensPos[i];
			
			QueenRow[CurrColumn] = Row;
			if (CurrColumn == 7){
				solutions++;
			}
			else
			{
				Solve8Queens(QueenRow, ++CurrColumn);
				CurrColumn--;
			}
		}
	}
}

/*How many backtracks occur?  how many times does the program remove a queen from the board.
how many calls to is under attack are there?
how many recursive calls to place queens are there?





void main(){
	
	Solve8Queens();
	cout << "total solutions=" << solutions << endl;
	//ChessBoard board;
	//board[0][0] = QUEEN;
	//Solve8Queens();

}