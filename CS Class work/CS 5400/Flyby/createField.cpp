#include "Polygon.h"
#include "Object3d.h"

const double pi = 3.141596;

#define x		0
#define y		1
#define z		2

void CreateField(Object3d &field)
{
	double gridSize = 20.0;
	double xO = 0.0;
	double zO = 0.0;
	double height = 0;
	int nLines = field.nShapes / 2;// = 10
	int hLines = nLines / 2;

	for (int i = 0; i < nLines; i++)
	{
		field.vertices[i+1][x] = (i-hLines) * gridSize + xO;
		field.vertices[i+1][z] = (-hLines) * gridSize + zO;
		field.vertices[i+1][y] = height;
		field.vertices[i+nLines*2+1][x] = (i-hLines) * gridSize + xO;
		field.vertices[i+nLines*2+1][z] = (hLines) * gridSize + zO;
		field.vertices[i+nLines*2+1][y] = height;
		
		field.shapes[i].Vertice = new int[2];
		field.shapes[i].nVertices = 2;
		field.shapes[i].Vertice[0] = i+1;
		field.shapes[i].Vertice[1] = i+nLines*2+1;
		field.shapes[i].shapeColor = RGB(255,0,0);

		field.vertices[i+nLines+1][x] = (-hLines) * gridSize + xO;
		field.vertices[i+nLines+1][z] = (i-hLines) * gridSize + zO;
		field.vertices[i+nLines+1][y] = height;
		field.vertices[i+nLines*3+1][x] = (hLines) * gridSize + xO;
		field.vertices[i+nLines*3+1][z] = (i-hLines) * gridSize + zO;
		field.vertices[i+nLines*3+1][y] = height;
		
		field.shapes[i+nLines].Vertice = new int[2];
		field.shapes[i+nLines].nVertices = 2;
		field.shapes[i+nLines].Vertice[0] = i+nLines+1;
		field.shapes[i+nLines].Vertice[1] = i+nLines*3+1;
		field.shapes[i+nLines].shapeColor = RGB(0,0,255);
	}
}