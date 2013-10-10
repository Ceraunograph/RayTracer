#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class Vector;

class Point {
public:
	float x, y, z;
	void setValue(float x, float y, float z);
	void addVector(Vector v);
	void subtractVector(Vector v);
};

#endif