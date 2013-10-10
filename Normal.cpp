#include "Normal.h"

void Normal::setValue(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

void Normal::add(Normal n) {
	x += n.x;
	y += n.y;
	z += n.z;
}

void Normal::subtract(Normal n) {
	x -= n.x;
	y -= n.y;
	z -= n.z;

	float length;
}