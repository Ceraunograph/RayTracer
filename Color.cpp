#include "Color.h"

void Color::setValue(float _r, float _g, float _b) {
	r = _r;
	g = _g;
	b = _b;
}

void Color::add(Color c) {
	r += c.r;
	g += c.g;
	b += c.b;
}

void Color::subtract(Color c) {
	r -= c.r;
	g -= c.g;
	b -= c.b;
}

void Color::multiply(float s) {
	r *= s;
	g *= s;
	b *= s;
}

void Color::divide(float s) {
	r /= s;
	g /= s;
	b /= s;
}