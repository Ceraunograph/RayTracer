#include "GeometricPrimitive.h"

void GeometricPrimitive::setValue(Transformation& _objToWorld, Transformation& _worldToObj, Shape* _shape, Material* _mat){
	objToWorld = _objToWorld;	
	worldToObj = _worldToObj;
	shape = _shape;
	mat = _mat; 
}

bool GeometricPrimitive::intersect(Ray& ray, float* thit, Intersection* in) {
	Ray transformedRay = objToWorld * ray;
	LocalGeo transformedLocal;                                 
	if (!shape->intersect(transformedRay, thit, &transformedLocal))  
		return false;
	in->primitive = this;
	in->localGeo = transformedLocal;
	return true;
}

bool GeometricPrimitive::intersectP(Ray& ray) {
	Ray transformedRay = worldToObj * ray;
	return shape->intersectP(transformedRay);
}

void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF* brdf) {
	mat->getBRDF(local, brdf);
}
