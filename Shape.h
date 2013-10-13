#ifndef SHAPE_H
#define SHAPE_H

#include ""
#include ""

class Point;
class Vector;

class Shape {
public:
	//tri v1 v2 v3
	//sphere x y z radius
	bool triangle;
	bool sphere;
	Vertex v1, v2, v3;
	float x, y, z, radius;
	Point center;
	

	void setValue(Point p, Vector v, float min, float max); 
	bool intersectSphere(Ray& ray, float* thit, LocalGeo* local);
	bool intersectTrianlge(Ray& ray, float* thit, LocalGeo* local);
	bool intersect(Ray& ray, float* thit, LocalGeo* local);  // thit = time hit               
	bool intersectP(Ray& ray);

	//world view = view relative to the camera
	//object view = view relative to the center of the object
};

#endif
