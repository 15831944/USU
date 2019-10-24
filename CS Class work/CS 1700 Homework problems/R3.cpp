//this is for a three dimensional graphics program.
//created by Mark Salisbury.

#include <fstream.h>
#include <iomanip.h>
#include <math.h>

const double pi = 3.1459;
const int DistToOrigin = 25;
const double ViewAngle = pi / 4;
const double screenh = 12.0;
const double screenw = 16.0;

class R3 {
	public:
		R3();
		int GetPoints(R3 [], const char *, int);
		void ShowPoints(const R3 [], int);
		void DrawFigure(const R3 [], int);
		
	private:
		
		int x[2];
		int y[2];
		int z[2];	
};

R3::R3(){
	double x[2] = {0,0};
	double y[2] = {0,0};
	double z[2] = {0,0};
}

int R3::GetPoints(R3 system[], const char *filename, int lines){
	ifstream file1(filename, ios::in);

	if(!file1){
		cerr << "File could not be opened" << endl;
		return (0);
	}
	
	for (int i = 0; i < lines; i++){
		for (int j = 0; j < 2; j++){
			file1 >> system[i].x[j];
			file1 >> system[i].y[j];
			file1 >> system[i].z[j];
		}
	}
	file1.close();
	return (1);
}
void R3::ShowPoints(const R3 system[], int lines){

	for (int i = 0; i < lines; i++){
		for (int j = 0; j < 2; j++){
			cout << setw(10) << "(" 
				  << system[i].x[j] << "," 
				  << system[i].y[j] << "," 
			     << system[i].z[j] << ")";
		}
		cout << endl;
	}
}
void R3::DrawFigure(const R3 system[], int lines){
	double xe = cos(ViewAngle) * DistToOrigin;
	double ye = sin(ViewAngle) * DistToOrigin;
	double ze = screenh;
	double a = xe / 2;
	double b = ye / 2;
	double c = ze / 2;
	double d = a * a + b * b + c * c;
	double t, xi, yi, zi;
	double xv, yv, zv;

	for (int i = 0; i < lines; i++){
		xv = (xe - system[i].x[0]);
		yv = (ye - system[i].y[0]);
		zv = (ze - system[i].z[0]);
		//t = (a * system[i].x[0] + b * system[i].y[0] + c * system[i].z[0]) /
		//	 (a * xv + b * yv + c * zv);
		t = (d - (a * system[i].x[0] + b * system[i].y[0] + c * system[i].z[0])) /
			 (a * xv + b * yv + c * zv);
		xi = system[i].x[0] + t * xv;
		yi = system[i].y[0] + t * yv;
		zi = system[i].z[0] + t * zv;
		cout << setprecision(4) << setiosflags(ios::fixed);
		cout << "xi = " << setw(7) << xi;
		cout << " yi = " << setw(7) << yi;
		cout << " zi = " << setw(7) << zi << endl;
	}
}

void main(void){
	
	R3 House[17];
	
	const char filename[] = {"house1.dat"};
	int lines = 17;

	if (House[0].GetPoints(House, filename, lines)){
		House[0].ShowPoints(House, lines);
		cin.get();
		House[0].DrawFigure(House, lines);
	}
}