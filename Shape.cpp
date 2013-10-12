#include "Shape.h"
#include <math.h> 

void Shape::setValue(float _x, float _y, float _z, float _radius, Point _v1, Point _v2, Point _v3, float shape) {
	if (shape == 0){
		sphere = true;
		triangle = false;

		x = _x;
		y = _y;
		z = _z;
		radius = _radius;

		center.setValue(x, y, z);

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


bool Shape::intersectSphere(Ray& ray, float* thit, LocalGeo* local){
	// (P-C).(P-C) = r^2
	// (P0 + tD - C).(P0 + tD - C) = r^2
	// (d.d)t^2 + 2(P0-C).dt + (P0-C).(P0-C)-r^2 = 0
	// At^2 + Bt + C = 0
	Vector temp1;
	float root;
	temp1.createFromPoints(ray.pos, center);

	// set up equation
	float A = ray.dir.dotProduct(ray.dir); // dot product for vector needed
	float B = 2.0 * (temp1.dotProdcut(ray.dir));
	float C = temp1.dotProduct(ray.dir) - (radius * radius);

	// solve quadratic equation
	float D = B * B - 4 * A * C;
	if (D < 0.0) {
		return false;
	} else {
		root = (sqrt(D) - B) / (A * 2.0);
		if (root < ray.t_min || root > ray.t_max) {
			return false;
		} else {
			thit = &root;
		}
	}

	// get point and normal for local geo
	Point point;
	point.setValue(ray.pos.x + ray.dir.x * root, ray.pos.y + ray.dir.y * root, ray.pos.z + ray.dir.z * root);
	Normal normal;
	normal.setValue(point.x - center.x, point.y - center.y, center.z - center.z);
	LocalGeo geo;
	geo.setValue(point, normal);
	local = &geo;
	
	return true;

}

bool Shape::intersectTriangle(Ray& ray, float* thit, LocalGeo* local){

	Vector edge1;
	edge1.setValue(v1.x, v1.y, v1.z);
	Vector edge2;
	edge2.setValue(v2.x, v2.y, v2.z);
	Vector edge3;
	edge3.setValue(v3.x, v3.y, v3.z);
	Vector negativeEdge3;
	
	edge1.setValue(edge1.x-v3.x, edge1.y-v3.y, edge1.z-v3.z);   // one edge of the triangle
	edge2.setValue(edge2.x-v1.x, edge2.y-v1.y, edge2.z-v1.z);   // another edge of the triangle     (counterclockwise fashion)
	edge3.setValue(edge3.x-v2.x, edge3.y-v2.y, edge3.z-v2.z);   // third edge of the triangle
	negativeEdge3.setValue(-edge3.x, -edge3.y, -edge3.z);
	Vector normal = edge2.crossProduct(negativeEdge3);    // normal of the triangle's plane

	float A = normal.x;            // equation of the plane = Ax + By + Cz + D = 0
	float B = normal.y;
	float C = normal.z;

	Vector tempV;
	tempV.setValue(v1.x, v1.y, v1.z);

	float D = normal.dotProduct(tempV);

	Vector rayOrigin;
	rayOrigin.setValue(ray.pos.x, ray.pos.y, ray.pos.z);
	float num = normal.dotProduct(rayOrigin) + ray.dir;
	float denom = normal.dotProduct(ray.dir);

	if (denom == 0.0){   // the direction of the ray and the normal of the plane is perpendicular
		return false;
	}

	float hit = num / denom;

	if (hit < ray.t_min || hit > ray.t_max){  // hit time outside of boundary
		return false;
	}

	Point hitPoint;
	hitPoint.setValue(ray.pos.x + ray.dir.x * hit, ray.pos.y + ray.dir.y * hit, ray.pos.z + ray.dir.z * hit);
	Vector vertexToPoint;

	vertexToPoint.createFromPoints(hitPoint, v1);
	float leftOfEdge1 = normal.dotProduct(edge1.crossProduct(vertexToPoint));
	vertexToPoint.createFromPoints(hitPoint, v2);
	float leftOfEdge2 = normal.dotProduct(edge2.crossProduct(vertexToPoint));
	vertexToPoint.createFromPoints(hitPoint, v3); 
	float leftOfEdge3 = normal.dotProduct(edge3.crossProduct(vertexToPoint));
	
	if (leftOfEdge1 <= 0.0 || leftOfEdge2 <= 0.0 || leftOfEdge3 <= 0.0){ // hit point not inside the triangle 
		return false;	
	}

	thit = &hit;
	LocalGeo geo;
	Normal normalizedNormal;
	normalizedNormal.setValue(normal.x, normal.y, normal.z);
	geo.setValue(hitPoint, normalizedNormal);
	local = &geo;

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


