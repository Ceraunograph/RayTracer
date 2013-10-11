#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "BRDF.h"
#include "LocalGeo.h"

class Material {
public:
	BRDF brdf;
	void getBRDF(LocalGeo& local, BRDF* brdf);
        void setValue(BRDF _BRDF);
	
};

#endif
