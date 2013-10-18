#ifndef GEOMETRICPRIMITIVE_H
#define GEOMETRICPRIMITIVE_H

#include "Primitive.h"
#include "Transformation.h"
#include "Shape.h"
#include "Material.h"
#include "LocalGeo.h"

class Transformation;
class Shape;
class Material;
class LocalGeo;

class GeometricPrimitive : public Primitive {
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	Transformation objToWorld, worldToObj;
	Shape* shape;
	Material* mat;
	
	void setValue(Transformation& _objToWorld, Transformation& _worldToObj, Shape* shape, Material* mat);
	bool intersect(Ray& ray, float* thit, Intersection* in);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif
