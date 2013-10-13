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
	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
	Point source;
	Vector dir;
	bool directional;
	bool point;
	Color color;

	void setValue(Point _source, bool _directional, bool _point);
	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
};

#endif
