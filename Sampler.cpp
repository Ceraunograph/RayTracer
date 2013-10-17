#include "Sampler.h"
#include <math.h>

void Sampler::setValue(float x, float y) {
	width = x;
	height = y;
	countX = countY = 0;
}

bool Sampler::getSample(Sample* sample) {
	Sample return_sample;
	float tempX, tempY;

	if (countY < height) {
		if (countX < width) {
			tempX = countX;
			tempY = countY;
			return_sample.setValue(tempX, tempY);
			countX++;
			sample = &return_sample;
			return true;
		} else {
			tempX = countX;
			tempY = countY;
			return_sample.setValue(tempX, tempY);
			countX = 0;
			countY++;
			sample = &return_sample;
			return true;
		}
	} else {
		return false;
	}
}
