#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

class Point;

class Vector {
public:
	float x, y, z;
	void setValue(float x, float y, float z);
	void createFromPoints(Point p1, Point p2);
	void add(Vector v);
	void subtract(Vector v);
	void multiply(float s);
	void divide(float s);
	void normalize();
	float dotProduct(Vector v);
	Vector crossProduct(Vector v);
};

#endif