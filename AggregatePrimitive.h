#ifndef AGGREGATEPRIMITIVE_H
#define AGGREGATEPRIMITIVE_H

#include "GeometricPrimitive.h"
#include "Vector.h"
#include "Ray.h"
#include "Intersection.h"
#include "LocalGeo.h"
#include "BRDF.h"

#include <vector>

class Vector;

class AggregatePrimitive : public Primitive {
public:
	std::vector<GeometricPrimitive*, Eigen::aligned_allocator<GeometricPrimitive>> primitiveList;
	void setValue(std::vector<GeometricPrimitive*, Eigen::aligned_allocator<GeometricPrimitive>> _list);
	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray) ;
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif
