#include <afx.h>
#include <fstream.h>
#include "Polygon.h"
#include "Object3d.h"

const double pi = 3.141596;

#define x		0
#define y		1
#define z		2



bool ReadObject(CString fileName, Object3d &object)
{
	ifstream fin(fileName);
		
	//double (*shuttlePoints)[3] = new double[nVertices][3];
	//double shuttlePoints[311][3];
	int vertice = 1;
	char line[81];
	char type;
	int n;
	int numbers[10];
	int nNumbers = 0;
	int wShape = 0;
	COLORREF color = RGB(0,255,0);
	char * colors[] = {"glass","bone","fldkdkgrey","redbrick","black","brass","dkdkgrey"};
	COLORREF colorValues[] = {RGB(200,200,255), RGB(240,240,255), RGB(150,150,150),
							  RGB(200,80,80),   RGB(50,50,50),    RGB(100,200,200), RGB(120,120,120)};
	
	//Vector3d normVectors[393];

	while (fin >> type)
	{
		
		if (type == 'v')
		{
			fin >> object.vertices[vertice][x] >> object.vertices[vertice][y] >> object.vertices[vertice][z];
			vertice++;
		}
		else if (type == 'f')
		{
			fin.getline(line,80);
			n = 0;
			nNumbers = 0;
			
			for (int i = 1; line[i-1] != '\0'; i++)
			{
				if (line[i] >= '0' && line[i] <= '9')
				{
					n *= 10;
					n += line[i] - '0';
				}
				else if (n != 0)
				{
					numbers[nNumbers] = n;
					n = 0;
					nNumbers++;
				}
			}

			object.shapes[wShape].nVertices = nNumbers;
			object.shapes[wShape].shapeColor = color;
			object.shapes[wShape].Vertice = new int[nNumbers];
			memcpy(object.shapes[wShape].Vertice, numbers, sizeof(int)*nNumbers);

			int p1 = numbers[0];
			int p2 = numbers[1];
			int p3 = numbers[2];
		
			double a1 = object.vertices[p1][x] - object.vertices[p2][x];
			double b1 = object.vertices[p1][y] - object.vertices[p2][y];
			double c1 = object.vertices[p1][z] - object.vertices[p2][z];

			double a2 = object.vertices[p3][x] - object.vertices[p2][x];
			double b2 = object.vertices[p3][y] - object.vertices[p2][y];
			double c2 = object.vertices[p3][z] - object.vertices[p2][z];

			object.shapes[wShape].NormalVector.SetVector(b1 * c2 - c1 * b2,
												 c1 * a2 - a1 * c2,
												 a1 * b2 - b1 * a2);
			wShape++;

		}
		else if (type == 'u')
		{
			fin.getline(line,80);

			if (strncmp(line,"semtl ",6) == 0)
			{
				for (int i = 0; i < 7; i++)
				{
					if (strcmp(&line[6],colors[i]) == 0)
					{
						color = colorValues[i];
						break;
					}
				}
			}
		}
		else
		{
			fin.getline(line,80);
		}
	}
	return true;
}