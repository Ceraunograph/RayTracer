#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Ray.h"
#include "Intersection.h"
#include "LocalGeo.h"
#include "BRDF.h"

class Ray;
class Intersection;
class LocalGeo;
class BRDF;

class Primitive {
public:
	virtual bool intersect(Ray& ray, float* thit, Intersection* in) = 0;
	//virtual bool intersectP(Ray& ray) = 0;
    virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
};

#endif