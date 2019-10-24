// Object3d.h: interface for the Object3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT3D_H__1759B360_581E_4596_9F18_8A04EF908CEA__INCLUDED_)
#define AFX_OBJECT3D_H__1759B360_581E_4596_9F18_8A04EF908CEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPolygon;
class CVector3d;

typedef int BOOL;

enum ShadingType {Lambert, Phong};
//typedef double[3] verticeType;
class Object3d  
{
public:
	ShadingType shadingStyle;
	BOOL useNormalVector;
	int nShapes;
	int nVertices;
	CPolygon * shapes;
	double (*vertices)[3];

	int (*neighboringFaces)[10];

	CVector3d * verticeVector;

	Object3d(int nVertices, int nShapes, BOOL useNormalVector, ShadingType sType);
	virtual ~Object3d();

};

#endif // !defined(AFX_OBJECT3D_H__1759B360_581E_4596_9F18_8A04EF908CEA__INCLUDED_)
