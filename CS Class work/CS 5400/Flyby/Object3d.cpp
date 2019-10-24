// Object3d.cpp: implementation of the Object3d class.
//
//////////////////////////////////////////////////////////////////////

#include "Object3d.h"
#include "Polygon.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "Polygon.h"

Object3d::Object3d(int nV, int nS, BOOL useN)
{
	useNormalVector = useN;
	nShapes = nS;
	nVertices = nV;
	vertices = new double[nVertices+1][3];
	shapes = new CPolygon[nShapes];
}

Object3d::~Object3d()
{
	delete [] shapes;
	delete [] vertices;
}
