// Polygon.cpp: implementation of the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "Polygon.h"
#include "Vector3d.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPolygon::CPolygon()
{


}

CPolygon::CPolygon(int nVert, int * Vert, COLORREF sColor, CVector3d & nVector)
	: NormalVector(nVector)
{
	nVertices = nVert;
	Vertice = new int[nVertices];
	memcpy(Vertice,Vert,sizeof(int)*nVertices);
	shapeColor = sColor;
}

CPolygon::~CPolygon()
{
	delete [] Vertice;
}
