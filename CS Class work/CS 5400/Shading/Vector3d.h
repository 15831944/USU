// Vector3d.h: interface for the CVector3d class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR3D_H__FD228C17_C05E_437C_B3D5_9C30260A8C74__INCLUDED_)
#define AFX_VECTOR3D_H__FD228C17_C05E_437C_B3D5_9C30260A8C74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CVector3d 
{
public:
	CVector3d & operator+=(const CVector3d & right);
	CVector3d & operator/=(int right);
	CVector3d operator+(const CVector3d & right) const;
	double operator*(const CVector3d & right) const;
	CVector3d();
	CVector3d(double x, double y, double z, double = 1.0);
	~CVector3d();
	void UpdateVector(double, double, double, double = 0.0); // this is provided in order to provide compatibility with 
						 // a derived class, class NonConstVector
	inline void SetVector(double x1 = 0.0, double y1 = 0.0, double z1 = 0.0, double w1 = 1.0)
	{
		x = x1;
		y = y1;
		z = z1;
		w = w1;
	}
	inline void SetVector(CVector3d & vector)
	{
		x = vector.x;
		y = vector.y;
		z = vector.z;
		w = vector.w;
	}
public:
	void Normalize();
	double x;
	double y;
	double z;
	double w;
protected:

};

#endif // !defined(AFX_VECTOR3D_H__FD228C17_C05E_437C_B3D5_9C30260A8C74__INCLUDED_)
