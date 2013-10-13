#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ray.h"
#include "Color.h"
#include "Light.h"

class RayTracer {
public:
	AggregatePrimitive ap;
	Light lights[];
	void setValue(AggregatePrimitive ap, Light lights[]);
	void trace(Ray& ray, int depth, Color* color);
};

#endif