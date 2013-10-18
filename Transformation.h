#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Point.h"
#include "Vector.h"
#include "Normal.h"
#include "Ray.h"
#include "LocalGeo.h"
#include <Eigen/LU>
#include <Eigen/Dense>
#include <Eigen/StdVector>

using namespace Eigen;

class Point;
class Vector;
class Normal;
class Ray;
class LocalGeo;

class Transformation {
public:
	Matrix4f m, minvt;
	void setValue(Matrix4f* m);
	Point operator * (Point p);
	Vector operator * (Vector v);
	Normal operator * (Normal n);
	Ray operator * (Ray r);
	LocalGeo operator * (LocalGeo g);
};

#endif