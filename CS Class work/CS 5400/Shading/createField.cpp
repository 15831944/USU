#include "Polygon.h"
#include "Object3d.h"

const double pi = 3.141596;

#define x		0
#define y		1
#define z		2

/*
void CreateField(Object3d &field)
{
	double gridSize = 20.0;
	double xO = -50.0;
	double zO = -50.0;
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
*/

void CreateField(Object3d &field)
{
	double gridSize = 20.0;
	double xO = -50.0;
	double zO = -50.0;
	double height = 0;
	int nLines = field.nShapes / 2;
	int hLines = nLines / 2;

	nLines = 13;

	int v = 1;
	for (int j = 0; j < nLines; j++)
	{
		for (int i = 0; i < nLines; i++)
		{
			field.vertices[v][x] =	field.vertices[i+1][x] = (i-hLines) * gridSize + xO;
			field.vertices[v][z] = (j-hLines) * gridSize + zO;
			field.vertices[v][y] = height;
			v++;
		}
	}

	int s = 0;
	for ( j = 0; j < nLines - 1; j++)
	{
		for (int i = 0; i < nLines - 1; i++)
		{
			field.shapes[s].Vertice = new int[4];
			field.shapes[s].nVertices = 4;
			field.shapes[s].Vertice[0] = i + 1 + j * nLines;
			field.shapes[s].Vertice[1] = i + 2 + j * nLines;
			field.shapes[s].Vertice[2] = i + 2 + (j+1) * nLines;
			field.shapes[s].Vertice[3] = i + 2 + (j+1) * nLines;
			field.shapes[s].shapeColor = RGB(255,0,0);

			double a1 = field.vertices[i + 1 + j * nLines][x] - field.vertices[i + 2 + j * nLines][x];
			double c1 = field.vertices[i + 1 + j * nLines][y] - field.vertices[i + 2 + j * nLines][y];
			double b1 = field.vertices[i + 1 + j * nLines][z] - field.vertices[i + 2 + j * nLines][z];

			double a2 = field.vertices[i + 2 + (j+1) * nLines][x] - field.vertices[i + 2 + j * nLines][x];
			double c2 = field.vertices[i + 2 + (j+1) * nLines][y] - field.vertices[i + 2 + j * nLines][y];
			double b2 = field.vertices[i + 2 + (j+1) * nLines][z] - field.vertices[i + 2 + j * nLines][z];

			// take the cross product of the two vectors
			field.shapes[s].NormalVector.SetVector(b1 * c2 - c1 * b2, c1 * a2 - a1 * c2, a1 * b2 - b1 * a2);


			// normalize this vector
			field.shapes[s].NormalVector.Normalize();

			s++;
		}
	}
	
}