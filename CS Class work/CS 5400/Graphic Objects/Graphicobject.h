

class Vector3d 
{
public:
	Vector3d();
	Vector3d(double x, double y, double z, double = 1.0);
	void UpdateVector(); // this is provided in order to provide compatibility with 
						 // a derived class, class NonConstVector
	double x;
	double y;
	double z;
	double w;
protected:

};

class FourSquareMatrix
{
public:
	FourSquareMatrix();
	FourSquareMatrix(double, double, double, double, 
					 double, double, double, double, 
					 double, double, double, double,
					 double, double, double, double);
	FourSquareMatrix(double [][4]);
	
	Vector3d MatrixMultiply(Vector3d &Point);
public:
	double Matrix[4][4];
};


/*
class NonConstVector : public Vector3d {
public:
	NonConstVector();
	void NonConstVector(Func1Type * xValFunc, Func1Type * yValFunc, Func1Type * zValFunc);
	void UpdateVector();
protected:

}

class 3dObject {
public:
	3dObject();
	3dObject(Vector3d InitPosition, Vector3d *ptrVelocityObject,  
	~3dObject();

	void UpdatePosition();
	void UpdateRotationPosition();
	void ChangeObjectCenter();
	void SetObjectPoints(Vector3d *ObjectPoints, int nPoints);
	void ChangeVelocityObject(Vector3d *ptrNewVelocity);
	// this could be used if you wanted to split an object in half and have one half move
	// independent of the other half, or conversely, if you wanted to join two objects together.
	// You could do some neat things with physics.  If two objects get close enough, then they 
	// combine and their masses increase.  The resulting collision changes the resultant velocity
	// of the new object.  You would use it in conjunction with ChangeObjectCenter and 


	Vector3d Position;
	Vector3d *Velocity; // this is a ptr because it could be a NonConstVector
	Vector3d ObjectCenter; // by default this is 0,0,0 
	Vector3d RotationPosition;
	Vector3d *RotationVelocity; // this is a ptr because it could be a NonConstVector
	Vector3d *ObjectPoints;
	int		nPoints;
protected:

};

class World {
	friend class Vector3d;
public:
	Vector3d ViewPoint;
	Vector3d ViewDirection;
	

protected:
	int time;

}
*/