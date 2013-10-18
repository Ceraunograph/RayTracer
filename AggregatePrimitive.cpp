#include "AggregatePrimitive.h"

void AggregatePrimitive::setValue(std::vector<GeometricPrimitive, Eigen::aligned_allocator<GeometricPrimitive>> _list){
	primitiveList = _list;
}

bool AggregatePrimitive::intersect(Ray& ray, float* thit, Intersection* in){
	float minHit = std::numeric_limits<float>::max();
	Intersection minIntersection;
	float hit;
	Intersection intersection;

	for (std::vector<GeometricPrimitive, Eigen::aligned_allocator<GeometricPrimitive>>::iterator it = primitiveList.begin(); it != primitiveList.end(); it++){
		if ((*it).intersect(ray, &hit, &intersection)){
			if (hit < minHit){
				minHit = hit;
				minIntersection = intersection;
			}
		}
	}

	if (minHit == std::numeric_limits<float>::max()){
		return false;
	}else{
		*thit = minHit;
		*in = minIntersection;
		return true;
	}
}

bool AggregatePrimitive::intersectP(Ray& ray, float thitOne, Intersection inOne) {
	float* thit = new float;
	Intersection* in = new Intersection;
	if (intersect(ray, thit, in)){
		if (in->localGeo.pos.x == inOne.localGeo.pos.x && in->localGeo.pos.y == inOne.localGeo.pos.y && in->localGeo.pos.z == inOne.localGeo.pos.z){    
			return false;
		}else{
			return true;
		}
	}else{
		return false;
	}
}

void AggregatePrimitive::getBRDF(LocalGeo& local, BRDF* brdf){
	exit(1); // this method should never be called
}
