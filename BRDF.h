#ifndef BRDF_H
#define BRDF_H

#include "Color.h"

class BRDF {
public:
	Color kd, ks, ka, kr;
	float shine;
	void setValue(Color kd, Color ks, Color ka, Color kr, float shine);
};

#endif