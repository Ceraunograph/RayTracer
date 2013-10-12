#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include "Point.h"
#include "Vector.h"
#include "Normal.h"
#include "Ray.h"
#include "LocalGeo.h"

class Matrix;
class Point;
class Vector;
class Normal;
class Ray;
class LocalGeo;

class Transformation {
public:
	Matrix m, minvt;
	void setValue(Matrix m);
	Point operator * (Point p);
	Vector operator * (Vector v);
	Normal operator * (Normal n);
	Ray operator * (Ray r);
	LocalGeo operator * (LocalGeo g);
};

#endif