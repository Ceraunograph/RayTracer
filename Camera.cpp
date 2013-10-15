#include "Camera.h"
#include <limits>
#include <math.h>

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
	Ray tempRay;

	Point origin;
	origin.setValue(0.0, 0.0, 0.0); // Let Pos of Camera to be the origin  (Camera Coordinate)

	float newx = ((2.0 * sample.x - width) / width ) * tan (fovx);
	float newy = ((2.0 * sample.y - height) / height) * tan (fovy); 

	Point samplePos;
	samplePos.setValue(newx,newy,-1.0);

	Vector direction;
	direction.createFromPoints(samplePos, origin);

	tempRay.setValue(origin, direction, 0.0, std::numeric_limits<float>::max());
	ray = &tempRay;
	
}
