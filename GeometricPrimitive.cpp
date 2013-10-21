#include "GeometricPrimitive.h"

void GeometricPrimitive::setValue(Transformation& _objToWorld, Transformation& _worldToObj, Transformation& _toCamera, Transformation& _toCameraInverse, Shape* _shape, Material* _mat){
	objToWorld = _objToWorld;	
	worldToObj = _worldToObj;
	toCamera = _toCamera;
	toCameraInverse = _toCameraInverse;
	shape = _shape;
	mat = _mat; 
}

bool GeometricPrimitive::intersect(Ray& ray, float* thit, Intersection* in) {
	LocalGeo transformedLocal;                                 
	if (!shape->intersect(objToWorld * (toCameraInverse * ray), thit, &transformedLocal))  
		return false;
	in->primitive = this;
	in->localGeo = worldToObj * transformedLocal;
	return true;
}

bool GeometricPrimitive::intersectP(Ray& ray) {
	if (!shape->intersectP(objToWorld * ray))  {
		return false;
	}
	return true;
}

void GeometricPrimitive::getBRDF(LocalGeo& local, BRDF* brdf) {
	mat->getBRDF(local, brdf);
}
