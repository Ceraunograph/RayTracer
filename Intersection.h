#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "LocalGeo.h"
#include "Primitive.h"

class Intersection {
public:
	LocalGeo localGeo;
	Primitive* primitive;
        void setValue(LocalGeo _localGeo, Primitive* _primitive);
	
};

#endif
