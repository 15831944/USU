// Object3d.cpp: implementation of the Object3d class.
//
//////////////////////////////////////////////////////////////////////

#include "Object3d.h"
#include "Polygon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "Polygon.h"

Object3d::Object3d(int nV, int nS, BOOL useN, ShadingType sType)
{
	shadingStyle = sType;
	useNormalVector = useN;
	nShapes = nS;
	nVertices = nV;
	vertices = new double[nVertices+1][3];
	neighboringFaces = new int[nVertices+1][10];
	memset(neighboringFaces, 0, sizeof(int) * (nVertices+1) * 10);
	shapes = new CPolygon[nShapes];

	if (shadingStyle == Phong)
	{
		verticeVector = new CVector3d[nVertices];
	}
	else
		verticeVector = NULL;

}

Object3d::~Object3d()
{
	delete [] shapes;
	delete [] vertices;
	delete [] neighboringFaces;
}
