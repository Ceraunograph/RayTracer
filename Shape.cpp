#include "Shape.h"
#include <cmath> 
#include <iostream>
using namespace std;

void Shape::setValue(float _x, float _y, float _z, float _radius, Point _v1, Point _v2, Point _v3, float shape) {
	if (shape == 0) {
		sphere = true;
		triangle = false;

		x = _x;
		y = _y;
		z = _z;
		radius = _radius;

		center.setValue(x, y, z);

	} else if (shape == 1) {
		sphere = false;
		triangle = true;
		
		v1 = _v1;
		v2 = _v2;
		v3 = _v3;  

	}else{
		// throw an exception
	}
}


bool Shape::intersectSphere(Ray& ray, float* thit, LocalGeo* local){
	// (P-C).(P-C) = r^2
	// (P0 + tD - C).(P0 + tD - C) = r^2
	// (d.d)t^2 + 2(P0-C).dt + (P0-C).(P0-C)-r^2 = 0
	// At^2 + Bt + C = 0
	Vector temp1;
	temp1.createFromPoints(center, ray.pos);

	// set up equation
	float A = ray.dir.dotProduct(ray.dir); // dot product for vector needed
	float B = 2.0 * (temp1.dotProduct(ray.dir));
	float C = temp1.dotProduct(ray.dir) - (radius * radius);

	// solve quadratic equation
	float D = B * B - 4 * A * C;
	if (D < 0.0) {
		return false;
	} else {
		*thit = (sqrt(D) - B) / (A * 2.0);
		if (*thit < ray.t_min || *thit > ray.t_max) {
			return false;
		} else {

		}
	}

	// get point and normal for local geo
	Point point;
	point.setValue(ray.pos.x + ray.dir.x * *thit, ray.pos.y + ray.dir.y * *thit, ray.pos.z + ray.dir.z * *thit);
	Normal normal;
	normal.setValue(point.x - center.x, point.y - center.y, center.z - center.z);

	local->setValue(point, normal);
	
	return true;

}

bool Shape::intersectTriangle(Ray& ray, float* thit, LocalGeo* local){

	Vector edge21;
	Vector edge32;
	Vector edge13;
	Vector edge31;
	Vector edge12;
	Vector edge23;
	
	edge21.setValue(v2.x-v1.x, v2.y-v1.y, v2.z-v1.z);   // one edge of the triangle
	edge32.setValue(v3.x-v2.x, v3.y-v2.y, v3.z-v2.z);   // another edge of the triangle     (counterclockwise fashion)
	edge13.setValue(v1.x-v3.x, v1.y-v3.y, v1.z-v3.z);   // third edge of the triangle
	edge31.setValue(-edge13.x, -edge13.y, -edge13.z);
	edge12.setValue(-edge21.x, -edge21.y, -edge21.z);
	edge23.setValue(-edge32.x, -edge32.y, -edge32.z);
	Vector normal = edge23.crossProduct(edge31);    // normal of the triangle's plane

	float A = normal.x;            // equation of the plane = Ax + By + Cz + D = 0
	float B = normal.y;
	float C = normal.z;

	Vector tempV;
	tempV.setValue(v1.x, v1.y, v1.z);

	float D = normal.dotProduct(tempV);

	Vector rayOrigin;
	rayOrigin.setValue(ray.pos.x, ray.pos.y, ray.pos.z);
	float num = normal.dotProduct(rayOrigin) + D;
	float denom = normal.dotProduct(ray.dir);

	if (denom == 0.0){   // the direction of the ray and the normal of the plane is perpendicular
		//cout << "perpendicular \n";
		return false;
	}

	*thit = - (num / denom);
	if (*thit < ray.t_min || *thit > ray.t_max){  // hit time outside of boundary
		
		//cout << "outside boundary \n";
		return false;
	}

	Point hitPoint;
	hitPoint.setValue(ray.pos.x + ray.dir.x * *thit, ray.pos.y + ray.dir.y * *thit, ray.pos.z + ray.dir.z * *thit);
	Vector vertexToPoint;


        
	vertexToPoint.createFromPoints(v1, hitPoint);
	float leftOfEdge1 = (edge21.crossProduct(edge31)).dotProduct(edge21.crossProduct(vertexToPoint));
	vertexToPoint.createFromPoints(v2, hitPoint);
	float leftOfEdge2 = (edge32.crossProduct(edge12)).dotProduct(edge32.crossProduct(vertexToPoint));
	vertexToPoint.createFromPoints(v3, hitPoint); 
	float leftOfEdge3 = (edge13.crossProduct(edge23)).dotProduct(edge13.crossProduct(vertexToPoint));
	
	//cout << leftOfEdge1 << "and" << leftOfEdge2 << "and" << leftOfEdge3;
	 
	if (leftOfEdge1 < 0.0 || leftOfEdge2 < 0.0 || leftOfEdge3 < 0.0){ // hit point not inside the triangle 
		//cout << "not inside the trianlge \n";
		return false;	
	}   


	Normal normalizedNormal;
	normalizedNormal.setValue(normal.x, normal.y, normal.z);

	local->setValue(hitPoint, normalizedNormal);

	return true;
}

bool Shape::intersect(Ray& ray, float* thit, LocalGeo* local){
	if (sphere == true){
		return intersectSphere(ray, thit, local);
	}else if (triangle == true){
		return intersectTriangle(ray, thit, local);
	}else{
		// throw and exception
	}
}

bool Shape::intersectP(Ray& ray){
	float *thit;
	LocalGeo *local;
	return intersect(ray, thit, local);
}



