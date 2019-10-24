
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

#define H_SPACE		3	//number of spaces between each longitudnal line
#define V_SPACE		1	//number of spaces between each latitudnal line  

#define GRIDSIZE	8	//number of rows and columns
	
#define H_SCREEN_SZ	80
#define V_SCREEN_SZ	25
#define H_OFFSET	20
#define V_OFFSET	3
char screen[V_SCREEN_SZ][H_SCREEN_SZ + 1];
void clearScreen(){
	for (int r = 0; r < V_SCREEN_SZ; r++){
		for (int c = 0; c < H_SCREEN_SZ; c++)
			screen[r][c] = ' ';
		screen[r][c] = '\0';
	}
}

void showScreen(){
	char c;
	for (int r = 0; r < V_SCREEN_SZ - 1; r++){
		cout << screen[r];
	}
}

void showExtended(){
	for (int i = 128; i < 256; i++){
		cout << i << ": " << char(i) << ' ';
		if (i % 8 == 0)
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

void drawVLine(int &vpos, int hpos, int row, bool showSymbols = false){
	screen[vpos][hpos++] = char(pv);
	int column = 1;
	do {
		for (int i = 0; i < H_SPACE; i++)
			screen[vpos][hpos++] = ((i == H_SPACE / 2) && showSymbols == true ? '*' : ' '); 
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
		
		for (int i = 0; i < V_SPACE; i++){
			
			drawVLine(vpos, H_OFFSET, row, (i == V_SPACE / 2 ? true: false));
		}
		
		if (row == GRIDSIZE)
			drawHLine(vpos, H_OFFSET, p7, p8, p9);
	}

}


void main(){
	clearScreen();
	drawGrid();
	showScreen();


}