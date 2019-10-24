#include "Graphicobject.h"
#include <string.h>

Vector3d::Vector3d()
{

}

Vector3d::Vector3d(double x1, double y1, double z1, double w1) // = 0.0
{
	x = x1;
	y = y1;
	z = z1;
	w = w1;
}

void Vector3d::UpdateVector()
{ // this is provided in order to provide compatibility with 
  // a derived class, class NonConstVector

}

FourSquareMatrix::FourSquareMatrix()
{

}

FourSquareMatrix::FourSquareMatrix(double a11, double a12, double a13, double a14, 
				 double a21, double a22, double a23, double a24, 
				 double a31, double a32, double a33, double a34,
				 double a41, double a42, double a43, double a44)
{
	Matrix[0][0] = a11;
	Matrix[0][1] = a12;
	Matrix[0][2] = a13;
	Matrix[0][3] = a14;
	Matrix[1][0] = a21;
	Matrix[1][1] = a22;
	Matrix[1][2] = a23;
	Matrix[1][3] = a24;
	Matrix[2][0] = a31;
	Matrix[2][1] = a32;
	Matrix[2][2] = a33;
	Matrix[2][3] = a34;
	Matrix[3][0] = a41;
	Matrix[3][1] = a42;
	Matrix[3][2] = a43;
	Matrix[3][3] = a44;
}

FourSquareMatrix::FourSquareMatrix(double M[][4])
{
	//for (int i = 0; i < 4; i++)
	//{
	//	for (int j = 0; j < 4; j++)
	//		Matrix[i][j] = 
	//}
	memcpy(Matrix,M,sizeof (double) * 16);
}

Vector3d FourSquareMatrix::MatrixMultiply(Vector3d &Point)
{
	double row1 = Matrix[0][0] * Point.x + 
				  Matrix[0][1] * Point.y + 
				  Matrix[0][2] * Point.z + 
				  Matrix[0][3] * Point.w;
	double row2 = Matrix[1][0] * Point.x + 
				  Matrix[1][1] * Point.y + 
				  Matrix[1][2] * Point.z + 
				  Matrix[1][3] * Point.w;
	double row3 = Matrix[2][0] * Point.x + 
				  Matrix[2][1] * Point.y + 
				  Matrix[2][2] * Point.z + 
				  Matrix[2][3] * Point.w;
	//double row4 = Matrix[3][0] * Point.x + 
	//			  Matrix[3][1] * Point.y + 
	//			  Matrix[3][2] * Point.z + 
	//			  Matrix[3][3] * Point.w;

	return Vector3d(row1, row2, row3);

}