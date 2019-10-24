#include "graphics.cpp"

int xmax;
int ymax;
const double pi = 3.141596;

#define x		0
#define y		1
#define z		2

void GetPosition(int &rev, double &pos, double &xOff, double &zOff, double &yRot){
	
	if (pos >= 36.0 + 11.0 * pi){
		pos -= (36.0 + 11.0 * pi);
		rev++;
	}

	if (pos < 18.0)
	{
		yRot = 0.0;
		xOff = 24.5;
		zOff = 34.0 - pos;
	}
	else if (pos < 18 + 5.5 * pi)
	{
		yRot = -(pos - 18.0) * pi / 18;
		xOff = cos((pos - 18.0) * pi / 18) * 5.5 + 19.0;
		zOff = -sin((pos - 18.0) * pi / 18) * 5.5 + 16.0;
	}
	else if (pos < 36 + 5.5 * pi)
	{
		yRot = pi;
		xOff = 13.5;
		zOff = 16.0 + pos-36;
	}
	else //(pos < 36 + 11 * pi)
	{
		yRot = pi - (pos - (36+5.5*pi)) * pi / 18;
		xOff = -cos((pos - (36+5.5*pi)) * pi / 18) * 5.5 + 19.0;
		zOff = sin((pos - (36+5.5*pi)) * pi / 18) * 5.5 + 34.0;
	}
}

void Morph (double newPoints[][3], double startPoints[][3], double finalPoints[][3], int nPoints, int nSteps, int stepnum)
{
	for (int n = 1; n <= nPoints; n++){
		for (int i = 0; i < 3; i ++)
		{
			newPoints[n][i] = startPoints[n][i] + (finalPoints[n][i] - startPoints[n][i]) * double (stepnum+1) / double(nSteps);

		}
	}
}

int Main()
{

	double points[81][3];
	double flatPoints[81][3];

	points[1][x] = 27;
	points[1][y] = 28;
	points[1][z] = 5;
	points[2][x] = 30;
	points[2][y] = 33;
	points[2][z] = 42;
	points[3][x] = 25;
	points[3][y] = 52;
	points[3][z] = 58;
	points[4][x] = 25;
	points[4][y] = 52;
	points[4][z] = 89;
	points[5][x] = 30;
	points[5][y] = 33;
	points[5][z] = 92;
	points[6][x] = 30;
	points[6][y] = 33;
	points[6][z] = 135;
	points[7][x] = 30;
	points[7][y] = 10;
	points[7][z] = 135;
	points[8][x] = 30;
	points[8][y] = 10;
	points[8][z] = 115;
	points[9][x] = 30;
	points[9][y] = 14;
	points[9][z] = 115;         
	points[10][x] = 30;
	points[10][y] = 19;
	points[10][z] = 110;
	points[11][x] = 30;
	points[11][y] = 19;
	points[11][z] = 100;
	points[12][x] = 30;
	points[12][y] = 14;
	points[12][z] = 95;
	points[13][x] = 30;
	points[13][y] = 10;
	points[13][z] = 95; 
	points[14][x] = 30;
	points[14][y] = 10;
	points[14][z] = 42;
	points[15][x] = 29.5;
	points[15][y] = 10;
	points[15][z] = 35;
	points[16][x] = 29.5;
	points[16][y] = 14;
	points[16][z] = 35;
	points[17][x] = 29.0;
	points[17][y] = 19;
	points[17][z] = 30;
	points[18][x] = 28.2;
	points[18][y] = 19;
	points[18][z] = 20;
	points[19][x] = 27.7;
	points[19][y] = 14;
	points[19][z] = 15;
	points[20][x] = 27.7;
	points[20][y] = 10;
	points[20][z] = 15;
	points[21][x] = 27;
	points[21][y] = 10;
	points[21][z] = 5;

	points[22][x] = 25;
	points[22][y] = 52;
	points[22][z] = 73;
	points[23][x] = 30;
	points[23][y] = 33;
	points[23][z] = 73;
	points[24][x] = 30;
	points[24][y] = 10;
	points[24][z] = 73;
            
	points[25][x] = 32;
	points[25][y] = 8 + 8;
	points[25][z] = 105 + 0;
	points[26][x] = 32;
	points[26][y] = 8 + 5.65;
	points[26][z] = 105 + 5.65;
	points[27][x] = 32;
	points[27][y] = 8 + 0;
	points[27][z] = 105 + 8;
	points[28][x] = 32;
	points[28][y] = 8 - 5.65;
	points[28][z] = 105 + 5.65;
	points[29][x] = 32;
	points[29][y] = 8 - 8;
	points[29][z] = 105 + 0;
	points[30][x] = 32;
	points[30][y] = 8 - 5.65;
	points[30][z] = 105 - 5.65;
	points[31][x] = 32;
	points[31][y] = 8 + 0;
	points[31][z] = 105 - 8;
	points[32][x] = 32;
	points[32][y] = 8 + 5.65;
	points[32][z] = 105 - 5.65;        

	points[33][x] = 32;
	points[33][y] = 8 + 8;
	points[33][z] = 20 + 0;
	points[34][x] = 32;
	points[34][y] = 8 + 5.65;
	points[34][z] = 20 + 5.65;
	points[35][x] = 32;
	points[35][y] = 8 + 0;
	points[35][z] = 20 + 8;
	points[36][x] = 32;
	points[36][y] = 8 - 5.65;
	points[36][z] = 20 + 5.65;
	points[37][x] = 32;
	points[37][y] = 8 - 8;
	points[37][z] = 20 + 0;
	points[38][x] = 32;
	points[38][y] = 8 - 5.65;
	points[38][z] = 20 - 5.65;
	points[39][x] = 32;
	points[39][y] = 8 + 0;
	points[39][z] = 20 - 8;
	points[40][x] = 32;
	points[40][y] = 8 + 5.65;
	points[40][z] = 20 - 5.65; 

    // Create a full screen window.
	
    WindowClass MyWindow;
    MyWindow.OpenWindow(0, 0, 0, 0, FULL_SCREEN | DOUBLE_BUFFER);
	//open window width, heigth, posx, posy, options
	//MyWindow.OpenWindow(500,500, 100, 100, NORMAL_WINDOW | DOUBLE_BUFFER);
    if (!MyWindow.WindowIsOpen())
        return 255;
	xmax = MyWindow.Width;
	ymax = MyWindow.Height;

	COLORREF color;

    for (int i = 41; i < 81; i++)
	{
		points[i][x] = points[i - 40][x] * -1.0;
		points[i][y] = points[i - 40][y];
		points[i][z] = points[i - 40][z];
	}

	for ( i = 0; i < 81; i++)
	{
		points[i][x] /= (140.0*1.1);
		points[i][y] -= 25.0;
		points[i][y] /= 140.0;
		points[i][z] -= 70.0;
		points[i][z] /= 140.0;
		flatPoints[i][x] = points[i][x];
		flatPoints[i][y] = 0.0;
		flatPoints[i][z] = points[i][z];
	}
	// this makes the car one unit long, with the center in the exact middle....
	
	int pointList[100][2];

	for ( i = 1; i < 22; i++)
	{
		pointList[i - 1][0] = i;
		pointList[i - 1][1] = i + 1;
		pointList[i - 1 + 21][0] = i + 40;
		pointList[i - 1 + 21][1] = i + 1 + 40;

	}
	pointList[20][1] = 1;
	pointList[41][1] = 41;

	pointList[42][0] = 1;
	pointList[42][1] = 41;
	pointList[43][0] = 21;
	pointList[43][1] = 61;

	pointList[44][0] = 2;
	pointList[44][1] = 42;
	pointList[45][0] = 3;
	pointList[45][1] = 43;

	pointList[46][0] = 4;
	pointList[46][1] = 44;
	pointList[47][0] = 5;
	pointList[47][1] = 45;

	pointList[48][0] = 6;
	pointList[48][1] = 46;
	pointList[49][0] = 7;
	pointList[49][1] = 47;

	for ( i = 0; i < 8; i++)
	{
		pointList[i+50][0] = 25+i;
		pointList[i+50][1] = 26+i;
		pointList[i+58][0] = 33+i;
		pointList[i+58][1] = 34+i;
		pointList[i+66][0] = 25+40+i;
		pointList[i+66][1] = 26+40+i;
		pointList[i+74][0] = 33+40+i;
		pointList[i+74][1] = 34+40+i;
	}
	pointList[57][1] = 25;
	pointList[65][1] = 33;
	pointList[73][1] = 25+40;
	pointList[81][1] = 33+40;

	int fieldList[48][2];
	double fieldPoints[49][3];

	for ( i = 1; i <= 12; i++)
	{
		fieldPoints[i][x] = sin(pi / 2.0 - (i-1) / 11.0 * pi) * 6.5 + 19;
		fieldPoints[i][y] = 0;
		fieldPoints[i][z] = cos(pi / 2.0 - (i-1) / 11.0 * pi) * 6.5 + 34;
		fieldPoints[i+12][x] = 38.0 - fieldPoints[i][x];
		fieldPoints[i+12][y] = 0;
		fieldPoints[i+12][z] = 50.0 - fieldPoints[i][z];
		fieldPoints[i+24][x] = sin(pi / 2.0 - (i-1) / 11.0 * pi) * 4.5 + 19;
		fieldPoints[i+24][y] = 0;
		fieldPoints[i+24][z] = cos(pi / 2.0 - (i-1) / 11.0 * pi) * 4.5 + 34;
		fieldPoints[i+36][x] = 38.0 - fieldPoints[i+24][x];
		fieldPoints[i+36][y] = 0;
		fieldPoints[i+36][z] = 50.0 - fieldPoints[i+24][z];
	}

	for ( i = 0; i < 24; i++)
	{
		fieldList[i][0] = i + 1;
		fieldList[i][1] = i + 2;
		fieldList[i+24][0] = i + 25;
		fieldList[i+24][1] = i + 26;
	}
	fieldList[23][1] = 1;
	fieldList[47][1] = 25;

	double theta = pi/4;
	//double viewx = cos(theta) * 5.0;
	//double viewz = sin(theta) * 5.0;
	
	double bxOff,byOff,bzOff;
		
	double byRot = 0.0;

	double rxOff,ryOff,rzOff;
		
	double ryRot = 0.0;

	byOff = .16;
	ryOff = .16;

	//xOff = 24.5; yOff = .16; zOff = 34.0;

	//Vector3d ViewPoint(viewx,2,viewz);
	Vector3d ViewPoint(8,4,8);
	Vector3d CenterPoint(19,0,24);

	double bPos = 2;
	double rPos = 15;
	double fallAcceleration = 0.006;
	double fallSpeed = 0;
	int bRev = 0;
	int rRev = 0;
	double rSpeed = .3;
	double bSpeed = .35;

	while (MyWindow.WindowIsOpen())
    {
		// Wait for escape to be pressed
		//viewx = cos(theta) * 5.0;
		//viewz = sin(theta) * 5.0;
		if (bRev < 2){
			GetPosition(bRev, rPos, rxOff, rzOff, ryRot);
			GetPosition(rRev, bPos, bxOff, bzOff, byRot);
			
		}
		
		if (bRev > 0 && bRev < 2)
			byOff += 0.015;
		else if (bRev >= 2)
		{
			fallSpeed += fallAcceleration;
			byOff -= fallSpeed;
			ViewPoint.UpdateVector(0.17,0,0.17);
			if (byOff <= 0.1)
			{
				double newPoints[81][3];

				for (int i = 0; i < 10 && MyWindow.WindowIsOpen(); i++)
				{
					if (rSpeed > 0)
					{
						rSpeed -= 0.2;
						rPos += rSpeed;
						GetPosition(bRev, rPos, rxOff, rzOff, ryRot);
					}
					MyWindow.ClearWindow();
					Morph (newPoints, points, flatPoints, 80, 10, i);
					//ProjectPoints(int P[][2], int nList, double points[][3], int nPoints, Vector3d V, Vector3d C, double viewDist)
					MyWindow.ProjectPoints(0,0,0,0,fieldList,49,fieldPoints,48,ViewPoint,CenterPoint,1,RGB(100,100,100));
					MyWindow.ProjectPoints(ryRot,rxOff,ryOff,rzOff,pointList,82,points,81,ViewPoint,CenterPoint,1,RGB(255,50,50));
					MyWindow.ProjectPoints(byRot,bxOff,byOff,bzOff,pointList,82,newPoints,81,ViewPoint,CenterPoint,1,RGB(50,50,255));
					
					MyWindow.SwapBuffers();
					//theta += pi / 64;
					//if (theta >= pi * 2)
					//	theta = 0;

					MyWindow.CheckEscape();
				}
				while (MyWindow.WindowIsOpen())
				{
					MyWindow.CheckEscape();
				}
				return 0;
			}
		}

		
		CenterPoint.SetVector(bxOff,byOff,bzOff);
		//Vector3d CenterPoint(0,0,0);
		MyWindow.ClearWindow();
		//ProjectPoints(int P[][2], int nList, double points[][3], int nPoints, Vector3d V, Vector3d C, double viewDist)
		MyWindow.ProjectPoints(0,0,0,0,fieldList,49,fieldPoints,48,ViewPoint,CenterPoint,1,RGB(100,100,100));
		MyWindow.ProjectPoints(ryRot,rxOff,ryOff,rzOff,pointList,82,points,81,ViewPoint,CenterPoint,1,RGB(255,50,50));
		MyWindow.ProjectPoints(byRot,bxOff,byOff,bzOff,pointList,82,points,81,ViewPoint,CenterPoint,1,RGB(50,50,255));
		
		MyWindow.SwapBuffers();
        //theta += pi / 64;
		//if (theta >= pi * 2)
		//	theta = 0;

		MyWindow.CheckEscape();
		//Sleep(500);
		bPos += bSpeed;
		rPos += rSpeed;
    }

    return 0;
}