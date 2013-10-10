#include "Normal.h"
#include <cmath>

void Normal::setValue(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;

	float length;
	length = sqrt(pow(x, 2.0)+pow(y, 2.0)+pow(z, 2.0));

	x /= length;
	y /= length;
	z /= length;
}

void Normal::add(Normal n) {
	x += n.x;
	y += n.y;
	z += n.z;

	float length;
	length = sqrt(pow(x, 2.0)+pow(y, 2.0)+pow(z, 2.0));

	x /= length;
	y /= length;
	z /= length;
}

void Normal::subtract(Normal n) {
	x -= n.x;
	y -= n.y;
	z -= n.z;

	float length;
	length = sqrt(pow(x, 2.0)+pow(y, 2.0)+pow(z, 2.0));

	x /= length;
	y /= length;
	z /= length;
}