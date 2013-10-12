#include "Camera.h"
#include <limits>

void Camera::setValue(	float _fromX,	float _fromY,	float _fromZ, 
						float _atX,		float _atY,		float _atZ, 
						float _upX,		float _upY,		float _upZ	) {
	fromX = _fromX;
	fromY = _fromY;
	fromZ = _fromZ;
	atX = _atX;
	atY = _atY;
	atZ = _atZ;
	upX = _upX;
	upY = _upY;
	upZ = _upZ;
}


void Camera::generateRay(Sample& sample, Ray* ray) {
	Ray tempRay;

	Point origin;
	origin.setValue(0.0, 0.0, 0.0); // Let Pos of Camera to be the origin

	Point samplePos;
	samplePos.setValue(sample.x,sample.y,-1.0);

	Vector direction;
	direction.createFromPoints(samplePos, origin);

	tempRay.setValue(origin, direction, 0.0, std::numeric_limits<float>::max());
	ray = &tempRay;
	
}
