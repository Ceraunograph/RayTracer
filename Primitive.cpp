#include "Primitive.h"

bool Primitive::intersect(Ray& ray, float* thit, Intersection* in) {
	return false;
}

bool Primitive::intersectP(Ray& ray) {
	return false;
}

void Primitive::getBRDF(LocalGeo& local, BRDF* brdf) {
}