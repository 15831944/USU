#include <iostream.h>
#include "rect.h"

int ApiMain() {
	// Construct and open window for displaying rectangles and set constants
	const float Size = 10;
	SimpleWindow W("Concentricity", Size, Size);
	W.Open();
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
		RectangleShape R3(W, Cx + Offset, Cy - Offset, C, Side, Side);
		RectangleShape R4(W, Cx - Offset, Cy + Offset, C, Side, Side);
		RectangleShape R5(W, Cx, Cy, C, Side, Side);
		// Draw rectangles
		R1.Draw();
		R2.Draw();
		R3.Draw();
		R4.Draw();
		R5.Draw();
		// Update rectangle side length
		Side = Side * Scaling;
	}
	cout <<  "Use mouse to terminate.  " << flush;
	cin.get();
	return 0;
}
