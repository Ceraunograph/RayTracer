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
};

#endif