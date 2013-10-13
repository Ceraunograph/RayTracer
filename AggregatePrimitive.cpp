#include "AggregatePrimitive.h"

void setValue(vector<Primitive*> _list){
	primitiveList = _list;
}

bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in){
	float minHit = std::numeric_limits<float>::max();
	Intersection minIntersection;
	float *hit;
	Intersection *intersection;
	for (int i = 0; i < primitiveList.size(); i++){
		if (primitiveList[i]->intersect(ray, hit, intersection)){
			if (hit < minHit){
				minHit = &hit;
				minIntersection = &intersection
			}
		}
	}
	if (minHit == std::numeric_limits<float>::max()){
		return false;
	}else{
		thit = &minHit;
		in = &minIntersection
		return true;
	}
}
bool AggregatePrimitive::intersectP(Ray& ray){
	float* thit;
	Intersection* in;
	return intersect(ray, thit, in);	
}
void AggregatePrimitve::getBRDF(LocalGeo& local, BRDF* brdf){
	exit(1); // this method should never be called
}
