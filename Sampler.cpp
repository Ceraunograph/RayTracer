#include "Sampler.h"
#include <math.h>

void Sampler::setValue(float x, float y) {
	width = x;
	height = y;
	countX = countY = 0;
}

bool Sampler::getSample(Sample* sample) {
	float tempX, tempY;

	if (countY < height) {
		if (countX < width) {
			tempX = countX;
			tempY = countY;
			countX++;
			sample->setValue(tempX, tempY);
			return true;
		} else {
			tempX = countX;
			tempY = countY;
			countX = 0;
			countY++;
			sample->setValue(tempX, tempY);
			return true;
		}
	} else {
		return false;
	}
}
