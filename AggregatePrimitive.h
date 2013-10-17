#ifndef AGGREGATEPRIMITIVE_H
#define AGGREGATEPRIMITIVE_H

#include "Primitive.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "LocalGeo.h"
#include "BRDF.h"

#include <vector>

class Vector;

class AggregatePrimitive : public Primitive {
public:
	std::vector<Primitive*> primitiveList;

	void setValue(std::vector<Primitive*> _list);
	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif
