#include "Sampler.h"
#include <math.h>

void Sampler::setValue(float x, float y) {
	width = x;
	height = y;
	count = 0;
}

bool Sampler::getSample(Sample* sample) {
	Sample return_sample;
	if (count < width*height) {
		return_sample.setValue(static_cast<int> (count) % static_cast<int> (width), count / width);
		count++;
		sample = &return_sample;
		return true;
	} else {
		return false;
	}
}
