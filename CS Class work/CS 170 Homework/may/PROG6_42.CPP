#include <iostream.h>
#include "rect.h"

int Fibonacci(int NumA, int NumB);

int ApiMain() {


int Squares;
cout << "How many squares would you like to display: " << flush;
cin >> Squares;
// a ugly window
const int Width = 12;
const int Heigth = 12;
SimpleWindow W("Fibonacci Squares", Width, Heigth);
W.Open();
const int Left = 1;
const int Bottom = 2;
const int Right = 3;
const int Top = 4;
int CurrentSide = Left;
float LeftSide = Width / 2;
float BottomSide = Heigth / 2;
int NumA = 1;
int NumB = 1;
int NumC = Fibonacci(NumA, NumB);

for(int i = 0;i < Squares;++i) {
Cx = (LeftSide + RightSide) / 2.00;
Cy = (TopSide + BottomSide) / 2.00
RectangleShape R(W, Cx, Cy, C, NumA, NumA);
		// Draw rectangles
		R1.Draw();
int NumA = NumB;
int NumB = NumC;
int NumC = Fibonacci(NumA, NumB);

switch (CurrentSide) {
case Left:
TopSide = BottomSide;
BottomSide = BottomSide + NumC;
RightSide = LeftSide + NumC;
break;
case Bottom:
LeftSide = RightSide;
RightSide = RightSide + NumC;
TopSide = BottomSide - NumC;
break;
case Right:
TopSide = TopSide - NumC;
LeftSide = RightSide - NumC;
BottomSide = TopSide;
break;
case Top:
RightSide = LeftSide;
LeftSide = LeftSide - NumC;
BottomSide = TopSide + NumC;
break;
}
++CurrentSide;
if (CurrentSide > Top)
	CurrentSide = Left;

}

Fibonacci(int NumA, int NumB) {
return (NumA + NumB);
}

	const float Cx = Size/2;
	const float Cy = Size/2;
	const float Offset = Size/4;
	const float n = 15;
	const float Scaling = 0.8;
	// Determine initial size of concentric rectangles
	float Side = Size;
	// Iteratively display concentric rectangles
	for (int i = 1; i <= n; ++i) {
			// Determine color of rectangles for this iteration
		color C;
		if (i % 2 == 0)
			C = Yellow;
		else
			C = Blue;
		// Construct rectangles
		RectangleShape R1(W, Cx - Offset, Cy - Offset, C, Side, Side);
		RectangleShape R2(W, Cx + Offset, Cy + Offset, C, Side, Side);
		RectangleShape R3(W, Cx, Cy, C, Side, Side);
		// Draw rectangles
		R1.Draw();
		R2.Draw();
		R3.Draw();
		// Update rectangle side length
		Side = Side * Scaling;
	}
	cout <<  "Use mouse to terminate.  " << flush;
	cin.get();
	return 0;
}
