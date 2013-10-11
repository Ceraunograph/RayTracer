#include "Shape.h"

void Shape::setValue(float _x, float _y, float _z, float _raidus, Vertex _v1, Vertex _v2, Vertex _v3, float shape) {
	if (shape == 0){
		sphere = true;
		triangle = false;

		x = _x;
		y = _y;
		z = _z;
		radius = _radius;

	}else if (shape == 1){
		sphere = false;
		triangle = true;
		
		v1 = _v1;
		v2 = _v2;
		v3 = _v3;

	}else{
		// throw and exception
	}
	
}

bool intersectSphere(Ray& ray, float* thit, LocalGeo* local){

}

bool intersectTriangle(Ray& ray, float* thit, LocalGeo* local){

}

bool intersect(Ray& ray, float* thit, LocalGeo* local){
	if (sphere == true){
		return intersectSphere(ray, thit, local);
	}else if (triangle == true){
		return intersectTriangle(ray, thit, local);
	}else{
		// throw and exception
	}
}

bool intersectP(Ray& ray){
	float *thit;
	LocalGeo *local;
	return intersect(ray, thit, local);
}


