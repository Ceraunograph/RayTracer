#ifndef LIGHT_H
#define LIGHT_H

#include "LocalGeo.h"
#include "Ray.h"
#include "Color.h"

class LocalGeo;
class Ray;
class Color;

class Light {
public:
	Point source;
	Vector dir;
	bool directional;
	bool point;
	Color color;
	void setValue(Point source, Vector dir, bool directional, bool point, Color color);
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor, float* dist, bool* pointLight);
};

#endif
