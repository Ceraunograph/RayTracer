#include "Vector.h"
#include <cmath>


void Vector::setValue(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Vector::createFromPoints(Point p1, Point p2) {
	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;
}

void Vector::add(Vector v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector::subtract(Vector v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector::multiply(float s) {
	x *= s;
	y *= s;
	z *= s;
}

void Vector::divide(float s) {
	x /= s;
	y /= s;
	z /= s;
}

void Vector::normalize() {
	float length;
	length = sqrt(pow(x, 2.0)+pow(y, 2.0)+pow(z, 2.0));
	x /= length;
	y /= length;
	z /= length;
}