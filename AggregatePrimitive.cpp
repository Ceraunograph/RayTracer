#include "AggregatePrimitive.h"

void AggregatePrimitive::setValue(std::vector<Primitive*>& _list){
	primitiveList = _list;
}

bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in){
	float minHit = std::numeric_limits<float>::max();
	Intersection minIntersection;
	float hit;
	Intersection intersection;

	for (std::vector<Primitive*>::iterator it = primitiveList.begin(); it != primitiveList.end(); it++){
		if ((**it).intersect(ray, &hit, &intersection)){
			if (hit < minHit){
				minHit = hit;
				minIntersection = intersection;
			}
		}
	}

	if (minHit == std::numeric_limits<float>::max()){
		return false;
	}else{
		thit = &minHit;
		in = &minIntersection;
		return true;
	}
}
bool AggregatePrimitive::intersectP(Ray& ray){
	float* thit;
	Intersection* in;
	return intersect(ray, thit, in);	
}
void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF* brdf){
	exit(1); // this method should never be called
}
