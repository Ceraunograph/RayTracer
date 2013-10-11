#ifndef SAMPLER_H
#define SAMPLER_H

#include "Sample.h"

class Sample;

class Sampler {
public:
	float width, height, countX, countY;
	void setValue(float x, float y);
	bool getSample(Sample* sample);
};

#endif 