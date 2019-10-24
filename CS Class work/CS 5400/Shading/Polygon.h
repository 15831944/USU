// Polygon.h: interface for the CPolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLYGON_H__80072CE1_3E61_4754_A706_9CB9A9CF5370__INCLUDED_)
#define AFX_POLYGON_H__80072CE1_3E61_4754_A706_9CB9A9CF5370__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include "Vector3d.h"

class CPolygon {
public:
	CPolygon();
	CPolygon(int nVert, int * Vert, COLORREF sColor, CVector3d & nVector);
	~CPolygon();

	int nVertices;
	int * Vertice;
	COLORREF shapeColor;
	CVector3d NormalVector;
};

#endif // !defined(AFX_POLYGON_H__80072CE1_3E61_4754_A706_9CB9A9CF5370__INCLUDED_)
