#include "GeometricPrimitive.h"

void GeometrixPrimitive::setValue(Transformation _objToWorld, Transformation _worldToObj, Shape* _shape, Material* _mat){
	objToWorld = _objToWorld;	
	worldToObject = _worldToObject;
	shape = _shape;
	mat = _mat; 
}

bool GeometricPrimitve::intersect(Ray& ray, float* thit, Intersection* in){
	Ray transformedRay = worldToObj * ray;
        LocalGeo transformedLocal;                                 
        if (!shape->intersect(transformedRay, thit, &transformedLocal))  
	return false;
        in->primitive = this;
        in->local = objToWorld * transformedLocal;
        return true;   

}

bool GeometricPrimitive::intersectP(Ray& ray){
	Ray transformedRay = worldToObj * ray;
	return shape->intersectP(transformedRay);

}

void GeometricPrimitvie::getBRDF(LocalGeo& local, BRDF* brdf){
	mat->getBRDF(local, brdf);
}
