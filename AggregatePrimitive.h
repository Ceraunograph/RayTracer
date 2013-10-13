#ifndef AGGREGATEPRIMITIVE_H
#define AGGREGATEPRIMITIVE_H

#include "Primitive.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "LocalGeo.h"
#include "BRDF.h"

#include <list>

class Vector;

class AggregatePrimitive : public Primitive {
public:
	std::list<Primitive*> primitiveList;

	void setValue(std::list<Primitive*> _list);
	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif
