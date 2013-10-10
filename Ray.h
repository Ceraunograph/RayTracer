#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Vector.h"

class Ray {
public:
	Point pos;
	Vector dir;
	float t_min, t_max;
	void setValue(Point p, Vector v, float min, float max);
};

#endif