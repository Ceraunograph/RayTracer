#ifndef BRDF_H
#define BRDF_H

#include "Color.h"

class BRDF {
public:
	Color kd, ks, ka, kr;
	void setValue(Color kd, Color ks, Color ka, Color kr);
};

#endif