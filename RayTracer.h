#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Ray.h"
#include "Color.h"
#include "Light.h"
#include "LocalGeo.h"
#include "AggregatePrimitive.h"


class RayTracer {
public:
	AggregatePrimitive primitive;
	int max_depth;
	float thit;
	Intersection in;
	BRDF brdf;
	Ray reflectRay;

	void setValue(AggregatePrimitive ap, int max_depth);
	void trace(Ray& ray, int depth, Color* color);
	Ray createReflectRay(LocalGeo local, Ray ray);
	void shading(LocalGeo local, BRDF brdf, Color color);
};

#endif