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
	void transform(Point* v);
	void transform(Vector* v);
	void transform(Normal* v);
	void transform(Ray* v);
	void transform(LocalGeo* v);
};

#endif