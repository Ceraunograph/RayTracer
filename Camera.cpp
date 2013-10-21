#include "Camera.h"
#include <limits>
#include <cmath>

void Camera::setValue(	float _fromX,	float _fromY,	float _fromZ, 
						float _atX,		float _atY,		float _atZ, 
						float _upX,		float _upY,		float _upZ, float _fovy, float _width, float _height	) {
	fromX = _fromX;
	fromY = _fromY;
	fromZ = _fromZ;
	atX = _atX;
	atY = _atY;
	atZ = _atZ;
	upX = _upX;
	upY = _upY;
	upZ = _upZ;
	width = _width;
	height = _height;
	fovy = _fovy;
	fovx = fovy * width / height;
	
}


void Camera::generateRay(Sample& sample, Ray* ray) {
	Point* origin = new Point;
	origin->setValue(0.0, 0.0, 0.0); // Let Pos of Camera to be the origin  (Camera Coordinate)

	float newx = ((2.0*sample.x/width) - 1.0)* tan(fovx/2.0 * 3.14159265/180.0);
	float newy = (1.0 - (2.0*sample.y/height))* tan(fovy/2.0 * 3.14159265/180.0);

	Point* samplePos = new Point;
	samplePos->setValue(newx,newy,-1.0);

	Vector* direction = new Vector;
	direction->createFromPoints(*origin, *samplePos);
	//direction.normalize();

	ray->setValue(*origin, *direction, 1.0, std::numeric_limits<float>::max());
	
}
