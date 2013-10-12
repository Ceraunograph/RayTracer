#ifndef SHAPE_H
#define SHAPE_H

#include "Point.h"
#include "Ray.h"
#include "LocalGeo.h"

class Point;
class Vector;
class Ray;
class LocalGeo;

class Shape {
public:
	//tri v1 v2 v3
	//sphere x y z radius
	bool triangle;
	bool sphere;
	Point v1, v2, v3;
	float x, y, z, radius;
	Point center;

	void setValue(float _x, float _y, float _z, float _radius, Point _v1, Point _v2, Point _v3, float shape);
	bool intersectSphere(Ray& ray, float* thit, LocalGeo* local);
	bool intersectTriangle(Ray& ray, float* thit, LocalGeo* local);
	bool intersect(Ray& ray, float* thit, LocalGeo* local);  // thit = time hit               
	bool intersectP(Ray& ray);

	//world view = view relative to the camera
	//object view = view relative to the center of the object
};

#endif
