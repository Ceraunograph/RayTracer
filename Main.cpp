#include "Shape.h"
#include "LocalGeo.h"
#include "Normal.h"
#include "Point.h"
#include "Ray.h"
#include "Vector.h"
#include <iostream>
using namespace std;

int main( int argc, const char* argv[] )
{
	/*

	Point pos;
	pos.setValue(8.0, 10.0, 36.0);
	Vector dir;
	dir.setValue(-8.0, -10.0, -36.0);
	dir.normalize();
	Ray ray;
	ray.setValue(pos, dir, 0.0, 100000.0);

	float thit;
	LocalGeo local;

	Shape sphere;
	sphere.setValue(0.0, 0.0, 0.0, 3.0, pos, pos, pos, 0.0);
	
	if (sphere.intersect(ray, &thit, &local)){
		cout << "Intersection \n";
		cout << local.pos.x;
	}else {
		cout << "No Intersection \n";
	}
	return 0; */


	Point one;
	one.setValue(6.0, 0.0, 0.0);
	Point two;
	two.setValue(-6.0, 0.0, 0.0);
	Point three;
	three.setValue(0.0, 0.0, 6.0);

	Shape triangle;
	triangle.setValue(0.0, 0.0, 0.0, 0.0, one, two, three, 1.0);

	Point pos;
	pos.setValue(0.0, 5.0, 3.0);
	Vector dir;
	dir.setValue(0.0, -3.0, 0.0);
	dir.normalize();
	Ray ray;
	ray.setValue(pos, dir, 0.0, 100000.0);

	float thit;
	LocalGeo local;

	if (triangle.intersect(ray, &thit, &local)){
		cout << "Intersection \n";
	}else {
		cout << "No Intersection \n";
	}
	return 0;


}


