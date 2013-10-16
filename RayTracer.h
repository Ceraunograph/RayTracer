#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
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
	std::vector<Light> lights;

	void setValue(AggregatePrimitive ap, int max_depth);
	void trace(Ray& ray, int depth, Color* color);
	Ray createReflectRay(LocalGeo local, Ray ray);
	Color shading(LocalGeo local, BRDF brdf, Color color);
};

#endif