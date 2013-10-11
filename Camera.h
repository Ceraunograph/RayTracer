#ifndef CAMERA_H
#define CAMERA_H

#include "Sample.h"
#include "Ray.h"

class Camera {
public:
	float fromX, fromY, fromZ, atX, atY, atZ, upX, upY, upZ;
	void setValue(float _fromX, float _fromY, float _fromZ, 
		      float _atX, float _atY, float _atZ, 
		      float _upX, float _upY, float _upZ);
	void generateRay(Sample& sample, Ray* ray);
	
};

#endif
