#include "Sampler.h"
#include <math.h>

void Sampler::setValue(float x, float y) {
	width = x;
	height = y;
	countX = countY = 0;
}

bool Sampler::getSample(Sample* sample) {
	if (countY < height) {
		sample->setValue(countX, countY);
		countX++;
		if (countX >= width) {
			countX = 0;
			countY++;
		}
		return true;
	} else {
		return false;
	}
}
