#include "Point.h"

void Point::setValue(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Point::addVector(Vector v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

void Point::subtractVector(Vector v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}
