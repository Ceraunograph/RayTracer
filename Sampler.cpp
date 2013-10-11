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
			tempX = (((countX + 0.5)/width)*2)-1;
			tempY = (((countY + 0.5)/height)*2)-1;
			countX++;
			sample = &return_sample;
			return true;
		} else {
			tempX = (((countX + 0.5)/width)*2)-1;
			tempY = (((countY + 0.5)/height)*2)-1;
			countX = 0;
			countY++;
			sample = &return_sample;
			return true;
		}
	} else {
		return false;
	}
}
